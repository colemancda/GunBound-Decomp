/* Host video and input (see video.h). Built without SDL when RT_NO_SDL is defined;
 * the program is then headless only. */
#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rt.h"
#include "video.h"

#ifndef RT_NO_SDL
#include <SDL.h>
#endif

uint8_t rt_vk_state[256];
uint8_t rt_dik_state[256];
uint8_t rt_mouse_buttons;
int rt_mouse_x, rt_mouse_y;

static pthread_mutex_t frame_mu = PTHREAD_MUTEX_INITIALIZER;
static uint16_t *frame_px;          /* staged frame, RGB565, tightly packed */
static int frame_w, frame_h, frame_dirty;
static unsigned frame_count;
static int motion_dx, motion_dy, motion_dz;
static int video_open;
static pthread_t video_thread;
static int screen_w = 800, screen_h = 600;

unsigned rt_video_frames(void) { return __atomic_load_n(&frame_count, __ATOMIC_RELAXED); }
int rt_video_is_open(void) { return video_open; }
int rt_video_on_video_thread(void) { return video_open && pthread_equal(pthread_self(), video_thread); }

void rt_mouse_take_motion(int *dx, int *dy, int *dz) {
    pthread_mutex_lock(&frame_mu);
    *dx = motion_dx;
    *dy = motion_dy;
    *dz = motion_dz;
    motion_dx = motion_dy = motion_dz = 0;
    pthread_mutex_unlock(&frame_mu);
}

/* --------------------------------------------------------- raw input log */
#define RAW_LOG 512
static RtRawInput raw_log[RAW_LOG];
static unsigned raw_head; /* total number of events ever logged */

static void raw_push(int kind, int code, int value) {
    pthread_mutex_lock(&frame_mu);
    RtRawInput *e = &raw_log[raw_head % RAW_LOG];
    e->kind = kind;
    e->code = code;
    e->value = value;
    e->time_ms = (uint32_t)(rt_mono_ns() / 1000000ull);
    e->seq = raw_head;
    raw_head++;
    pthread_mutex_unlock(&frame_mu);
}

unsigned rt_input_position(void) {
    pthread_mutex_lock(&frame_mu);
    unsigned h = raw_head;
    pthread_mutex_unlock(&frame_mu);
    return h;
}

int rt_input_read(unsigned *cursor, RtRawInput *out, int *overflow) {
    int ok = 0;
    pthread_mutex_lock(&frame_mu);
    if (raw_head - *cursor > RAW_LOG) {
        *cursor = raw_head - RAW_LOG;
        if (overflow) *overflow = 1;
    }
    if (*cursor != raw_head) {
        *out = raw_log[*cursor % RAW_LOG];
        (*cursor)++;
        ok = 1;
    }
    pthread_mutex_unlock(&frame_mu);
    return ok;
}

/* ------------------------------------------------------------------- PNG
 * Stored (uncompressed) deflate blocks: no zlib needed, and the files are small
 * enough at 800x600. */
static uint32_t crc_table[256];

static uint32_t crc_update(uint32_t crc, const uint8_t *p, size_t n) {
    if (!crc_table[1]) {
        for (uint32_t i = 0; i < 256; i++) {
            uint32_t c = i;
            for (int k = 0; k < 8; k++) c = (c & 1) ? 0xEDB88320u ^ (c >> 1) : c >> 1;
            crc_table[i] = c;
        }
    }
    while (n--) crc = crc_table[(crc ^ *p++) & 0xFF] ^ (crc >> 8);
    return crc;
}

static void put_be32(uint8_t *p, uint32_t v) {
    p[0] = (uint8_t)(v >> 24);
    p[1] = (uint8_t)(v >> 16);
    p[2] = (uint8_t)(v >> 8);
    p[3] = (uint8_t)v;
}

static int png_chunk(FILE *f, const char *type, const uint8_t *data, uint32_t len) {
    uint8_t hdr[8], tail[4];
    put_be32(hdr, len);
    memcpy(hdr + 4, type, 4);
    uint32_t crc = crc_update(0xFFFFFFFFu, hdr + 4, 4);
    if (len) crc = crc_update(crc, data, len);
    put_be32(tail, ~crc);
    return fwrite(hdr, 1, 8, f) == 8 && (!len || fwrite(data, 1, len, f) == len) && fwrite(tail, 1, 4, f) == 4;
}

int rt_write_png(const char *path, const uint8_t *rgb, int width, int height) {
    size_t row = 1 + (size_t)width * 3, raw_len = row * (size_t)height;
    size_t nblocks = (raw_len + 65534) / 65535;
    size_t zlen = 2 + raw_len + 5 * nblocks + 4;
    uint8_t *z = malloc(zlen);
    FILE *f = fopen(path, "wb");
    if (!z || !f) {
        free(z);
        if (f) fclose(f);
        return 0;
    }
    size_t o = 0;
    z[o++] = 0x78;
    z[o++] = 0x01;
    uint32_t s1 = 1, s2 = 0; /* Adler-32 of the raw scanlines */
    size_t done = 0, block_left = 0;
    for (int y = 0; y < height; y++) {
        for (size_t k = 0; k < row; k++) {
            if (block_left == 0) {
                size_t n = raw_len - done > 65535 ? 65535 : raw_len - done;
                z[o++] = done + n == raw_len;
                z[o++] = (uint8_t)n;
                z[o++] = (uint8_t)(n >> 8);
                z[o++] = (uint8_t)~n;
                z[o++] = (uint8_t)(~n >> 8);
                block_left = n;
            }
            uint8_t b = k == 0 ? 0 : rgb[(size_t)y * (size_t)width * 3 + k - 1];
            z[o++] = b;
            s1 = (s1 + b) % 65521u;
            s2 = (s2 + s1) % 65521u;
            done++;
            block_left--;
        }
    }
    put_be32(z + o, (s2 << 16) | s1);
    o += 4;
    static const uint8_t sig[8] = {0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A};
    uint8_t ihdr[13];
    put_be32(ihdr, (uint32_t)width);
    put_be32(ihdr + 4, (uint32_t)height);
    ihdr[8] = 8;  /* bit depth */
    ihdr[9] = 2;  /* truecolour */
    ihdr[10] = ihdr[11] = ihdr[12] = 0;
    int ok = fwrite(sig, 1, 8, f) == 8 && png_chunk(f, "IHDR", ihdr, 13) && png_chunk(f, "IDAT", z, (uint32_t)o) &&
             png_chunk(f, "IEND", NULL, 0);
    ok = fclose(f) == 0 && ok;
    free(z);
    return ok;
}

static void dump_frame(const uint16_t *px, int w, int h) {
    uint8_t *rgb = malloc((size_t)w * (size_t)h * 3);
    if (!rgb) return;
    unsigned nonblack = 0;
    for (int i = 0; i < w * h; i++) {
        uint16_t p = px[i];
        unsigned r = (p >> 11) & 31, g = (p >> 5) & 63, b = p & 31;
        rgb[3 * i] = (uint8_t)((r << 3) | (r >> 2));
        rgb[3 * i + 1] = (uint8_t)((g << 2) | (g >> 4));
        rgb[3 * i + 2] = (uint8_t)((b << 3) | (b >> 2));
        nonblack += p != 0;
    }
    if (rt_write_png(g_opt.dump_path, rgb, w, h))
        rt_log("recomp: frame %u written to %s (%dx%d, %u of %d pixels not black)\n", frame_count, g_opt.dump_path, w,
               h, nonblack, w * h);
    else
        rt_log("recomp: could not write frame %u to %s\n", frame_count, g_opt.dump_path);
    free(rgb);
}

/* ------------------------------------------------------------------- SDL */
#ifndef RT_NO_SDL
static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *texture;
static int tex_w, tex_h;
static RtInputEvent pending[8];
static int npending;

/* SDL scancode -> {Windows virtual key, DirectInput key code}. */
static const struct { uint8_t vk, dik; } keymap[SDL_NUM_SCANCODES] = {
    [SDL_SCANCODE_A] = {'A', 0x1E}, [SDL_SCANCODE_B] = {'B', 0x30}, [SDL_SCANCODE_C] = {'C', 0x2E},
    [SDL_SCANCODE_D] = {'D', 0x20}, [SDL_SCANCODE_E] = {'E', 0x12}, [SDL_SCANCODE_F] = {'F', 0x21},
    [SDL_SCANCODE_G] = {'G', 0x22}, [SDL_SCANCODE_H] = {'H', 0x23}, [SDL_SCANCODE_I] = {'I', 0x17},
    [SDL_SCANCODE_J] = {'J', 0x24}, [SDL_SCANCODE_K] = {'K', 0x25}, [SDL_SCANCODE_L] = {'L', 0x26},
    [SDL_SCANCODE_M] = {'M', 0x32}, [SDL_SCANCODE_N] = {'N', 0x31}, [SDL_SCANCODE_O] = {'O', 0x18},
    [SDL_SCANCODE_P] = {'P', 0x19}, [SDL_SCANCODE_Q] = {'Q', 0x10}, [SDL_SCANCODE_R] = {'R', 0x13},
    [SDL_SCANCODE_S] = {'S', 0x1F}, [SDL_SCANCODE_T] = {'T', 0x14}, [SDL_SCANCODE_U] = {'U', 0x16},
    [SDL_SCANCODE_V] = {'V', 0x2F}, [SDL_SCANCODE_W] = {'W', 0x11}, [SDL_SCANCODE_X] = {'X', 0x2D},
    [SDL_SCANCODE_Y] = {'Y', 0x15}, [SDL_SCANCODE_Z] = {'Z', 0x2C},
    [SDL_SCANCODE_1] = {'1', 0x02}, [SDL_SCANCODE_2] = {'2', 0x03}, [SDL_SCANCODE_3] = {'3', 0x04},
    [SDL_SCANCODE_4] = {'4', 0x05}, [SDL_SCANCODE_5] = {'5', 0x06}, [SDL_SCANCODE_6] = {'6', 0x07},
    [SDL_SCANCODE_7] = {'7', 0x08}, [SDL_SCANCODE_8] = {'8', 0x09}, [SDL_SCANCODE_9] = {'9', 0x0A},
    [SDL_SCANCODE_0] = {'0', 0x0B},
    [SDL_SCANCODE_RETURN] = {0x0D, 0x1C}, [SDL_SCANCODE_ESCAPE] = {0x1B, 0x01},
    [SDL_SCANCODE_BACKSPACE] = {0x08, 0x0E}, [SDL_SCANCODE_TAB] = {0x09, 0x0F},
    [SDL_SCANCODE_SPACE] = {0x20, 0x39}, [SDL_SCANCODE_MINUS] = {0xBD, 0x0C},
    [SDL_SCANCODE_EQUALS] = {0xBB, 0x0D}, [SDL_SCANCODE_LEFTBRACKET] = {0xDB, 0x1A},
    [SDL_SCANCODE_RIGHTBRACKET] = {0xDD, 0x1B}, [SDL_SCANCODE_BACKSLASH] = {0xDC, 0x2B},
    [SDL_SCANCODE_SEMICOLON] = {0xBA, 0x27}, [SDL_SCANCODE_APOSTROPHE] = {0xDE, 0x28},
    [SDL_SCANCODE_GRAVE] = {0xC0, 0x29}, [SDL_SCANCODE_COMMA] = {0xBC, 0x33},
    [SDL_SCANCODE_PERIOD] = {0xBE, 0x34}, [SDL_SCANCODE_SLASH] = {0xBF, 0x35},
    [SDL_SCANCODE_CAPSLOCK] = {0x14, 0x3A},
    [SDL_SCANCODE_F1] = {0x70, 0x3B}, [SDL_SCANCODE_F2] = {0x71, 0x3C}, [SDL_SCANCODE_F3] = {0x72, 0x3D},
    [SDL_SCANCODE_F4] = {0x73, 0x3E}, [SDL_SCANCODE_F5] = {0x74, 0x3F}, [SDL_SCANCODE_F6] = {0x75, 0x40},
    [SDL_SCANCODE_F7] = {0x76, 0x41}, [SDL_SCANCODE_F8] = {0x77, 0x42}, [SDL_SCANCODE_F9] = {0x78, 0x43},
    [SDL_SCANCODE_F10] = {0x79, 0x44}, [SDL_SCANCODE_F11] = {0x7A, 0x57}, [SDL_SCANCODE_F12] = {0x7B, 0x58},
    [SDL_SCANCODE_PRINTSCREEN] = {0x2C, 0xB7}, [SDL_SCANCODE_SCROLLLOCK] = {0x91, 0x46},
    [SDL_SCANCODE_PAUSE] = {0x13, 0xC5}, [SDL_SCANCODE_INSERT] = {0x2D, 0xD2},
    [SDL_SCANCODE_HOME] = {0x24, 0xC7}, [SDL_SCANCODE_PAGEUP] = {0x21, 0xC9},
    [SDL_SCANCODE_DELETE] = {0x2E, 0xD3}, [SDL_SCANCODE_END] = {0x23, 0xCF},
    [SDL_SCANCODE_PAGEDOWN] = {0x22, 0xD1}, [SDL_SCANCODE_RIGHT] = {0x27, 0xCD},
    [SDL_SCANCODE_LEFT] = {0x25, 0xCB}, [SDL_SCANCODE_DOWN] = {0x28, 0xD0}, [SDL_SCANCODE_UP] = {0x26, 0xC8},
    [SDL_SCANCODE_NUMLOCKCLEAR] = {0x90, 0x45}, [SDL_SCANCODE_KP_DIVIDE] = {0x6F, 0xB5},
    [SDL_SCANCODE_KP_MULTIPLY] = {0x6A, 0x37}, [SDL_SCANCODE_KP_MINUS] = {0x6D, 0x4A},
    [SDL_SCANCODE_KP_PLUS] = {0x6B, 0x4E}, [SDL_SCANCODE_KP_ENTER] = {0x0D, 0x9C},
    [SDL_SCANCODE_KP_1] = {0x61, 0x4F}, [SDL_SCANCODE_KP_2] = {0x62, 0x50}, [SDL_SCANCODE_KP_3] = {0x63, 0x51},
    [SDL_SCANCODE_KP_4] = {0x64, 0x4B}, [SDL_SCANCODE_KP_5] = {0x65, 0x4C}, [SDL_SCANCODE_KP_6] = {0x66, 0x4D},
    [SDL_SCANCODE_KP_7] = {0x67, 0x47}, [SDL_SCANCODE_KP_8] = {0x68, 0x48}, [SDL_SCANCODE_KP_9] = {0x69, 0x49},
    [SDL_SCANCODE_KP_0] = {0x60, 0x52}, [SDL_SCANCODE_KP_PERIOD] = {0x6E, 0x53},
    [SDL_SCANCODE_LCTRL] = {0x11, 0x1D}, [SDL_SCANCODE_LSHIFT] = {0x10, 0x2A}, [SDL_SCANCODE_LALT] = {0x12, 0x38},
    [SDL_SCANCODE_LGUI] = {0x5B, 0xDB}, [SDL_SCANCODE_RCTRL] = {0x11, 0x9D}, [SDL_SCANCODE_RSHIFT] = {0x10, 0x36},
    [SDL_SCANCODE_RALT] = {0x12, 0xB8}, [SDL_SCANCODE_RGUI] = {0x5C, 0xDC},
};

void rt_video_open(const char *title, int width, int height) {
    screen_w = width;
    screen_h = height;
    if (video_open || g_opt.headless) return;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        rt_log("recomp: SDL_Init failed (%s); continuing without a window\n", SDL_GetError());
        g_opt.headless = 1;
        return;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    uint32_t flags = SDL_WINDOW_RESIZABLE;
    int w = width, h = height;
    SDL_DisplayMode dm;
    if (g_opt.scale > 0) {
        w *= g_opt.scale;
        h *= g_opt.scale;
    } else if (g_opt.fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    } else if (SDL_GetDesktopDisplayMode(0, &dm) == 0 && dm.w >= width * 2 + 64 && dm.h >= height * 2 + 64) {
        w *= 2;
        h *= 2;
    }
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
    if (window) renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (window && !renderer) renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!window || !renderer) {
        rt_log("recomp: cannot create the SDL window (%s); continuing without one\n", SDL_GetError());
        g_opt.headless = 1;
        return;
    }
    SDL_RenderSetLogicalSize(renderer, width, height);
    SDL_StartTextInput();
    video_thread = pthread_self();
    video_open = 1;
    rt_log("recomp: SDL window %dx%d for a %dx%d guest screen, video driver %s\n", w, h, width, height,
           SDL_GetCurrentVideoDriver());
}

static void flush_frame(void) {
    pthread_mutex_lock(&frame_mu);
    if (frame_dirty && frame_px) {
        if (!texture || tex_w != frame_w || tex_h != frame_h) {
            if (texture) SDL_DestroyTexture(texture);
            texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STREAMING, frame_w, frame_h);
            tex_w = frame_w;
            tex_h = frame_h;
        }
        if (texture) SDL_UpdateTexture(texture, NULL, frame_px, frame_w * 2);
        frame_dirty = 0;
        pthread_mutex_unlock(&frame_mu);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        if (texture) SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        return;
    }
    pthread_mutex_unlock(&frame_mu);
}

static void queue_event(const RtInputEvent *ev) {
    if (npending < (int)RT_COUNTOF(pending)) pending[npending++] = *ev;
}

static int clampi(int v, int lo, int hi) { return v < lo ? lo : v > hi ? hi : v; }

/* Translate one SDL event; returns the number of events queued. */
static void translate(const SDL_Event *e) {
    RtInputEvent ev;
    memset(&ev, 0, sizeof ev);
    switch (e->type) {
    case SDL_QUIT:
        ev.type = RT_EV_QUIT;
        queue_event(&ev);
        break;
    case SDL_WINDOWEVENT:
        if (e->window.event == SDL_WINDOWEVENT_FOCUS_GAINED || e->window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
            ev.type = RT_EV_FOCUS;
            ev.down = e->window.event == SDL_WINDOWEVENT_FOCUS_GAINED;
            queue_event(&ev);
        } else if (e->window.event == SDL_WINDOWEVENT_EXPOSED || e->window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
            pthread_mutex_lock(&frame_mu);
            frame_dirty = frame_px != NULL;
            pthread_mutex_unlock(&frame_mu);
        }
        break;
    case SDL_MOUSEMOTION:
        ev.type = RT_EV_MOUSE_MOVE;
        ev.x = rt_mouse_x = clampi(e->motion.x, 0, screen_w - 1);
        ev.y = rt_mouse_y = clampi(e->motion.y, 0, screen_h - 1);
        pthread_mutex_lock(&frame_mu);
        motion_dx += e->motion.xrel;
        motion_dy += e->motion.yrel;
        pthread_mutex_unlock(&frame_mu);
        if (e->motion.xrel) raw_push(RT_RAW_AXIS, 0, e->motion.xrel);
        if (e->motion.yrel) raw_push(RT_RAW_AXIS, 1, e->motion.yrel);
        queue_event(&ev);
        break;
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP: {
        int b = e->button.button == SDL_BUTTON_LEFT ? 1 : e->button.button == SDL_BUTTON_RIGHT ? 3 :
                e->button.button == SDL_BUTTON_MIDDLE ? 2 : 0;
        if (!b) break;
        ev.type = RT_EV_MOUSE_BUTTON;
        ev.x = rt_mouse_x = clampi(e->button.x, 0, screen_w - 1);
        ev.y = rt_mouse_y = clampi(e->button.y, 0, screen_h - 1);
        ev.code = b;
        ev.down = e->type == SDL_MOUSEBUTTONDOWN;
        ev.repeat = e->button.clicks;
        uint8_t bit = b == 1 ? 1 : b == 3 ? 2 : 4;
        if (ev.down) rt_mouse_buttons |= bit;
        else rt_mouse_buttons &= (uint8_t)~bit;
        raw_push(RT_RAW_BUTTON, b == 1 ? 0 : b == 3 ? 1 : 2, ev.down ? 0x80 : 0);
        queue_event(&ev);
        break;
    }
    case SDL_MOUSEWHEEL:
        pthread_mutex_lock(&frame_mu);
        motion_dz += e->wheel.y * 120;
        pthread_mutex_unlock(&frame_mu);
        raw_push(RT_RAW_AXIS, 2, e->wheel.y * 120);
        break;
    case SDL_KEYDOWN:
    case SDL_KEYUP: {
        SDL_Scancode sc = e->key.keysym.scancode;
        if (sc >= SDL_NUM_SCANCODES || !keymap[sc].vk) break;
        ev.type = RT_EV_KEY;
        ev.code = keymap[sc].vk;
        ev.scan = keymap[sc].dik;
        ev.down = e->type == SDL_KEYDOWN;
        ev.repeat = e->key.repeat;
        if (ev.down) {
            if (!e->key.repeat) rt_vk_state[ev.code] ^= 1;
            rt_vk_state[ev.code] |= 0x80;
            rt_dik_state[ev.scan] = 0x80;
        } else {
            rt_vk_state[ev.code] &= 0x7F;
            rt_dik_state[ev.scan] = 0;
        }
        if (!e->key.repeat) raw_push(RT_RAW_KEY, ev.scan, ev.down ? 0x80 : 0);
        queue_event(&ev);
        break;
    }
    case SDL_TEXTINPUT: {
        /* UTF-8 to Latin-1, the guest's code page; other characters are dropped. */
        const uint8_t *p = (const uint8_t *)e->text.text;
        while (*p) {
            unsigned ch = *p++;
            if (ch >= 0xC0 && ch < 0xE0 && (*p & 0xC0) == 0x80) ch = ((ch & 0x1F) << 6) | (*p++ & 0x3F);
            else if (ch >= 0x80) {
                while ((*p & 0xC0) == 0x80) p++;
                continue;
            }
            if (ch < 0x20 || ch > 0xFF) continue;
            ev.type = RT_EV_CHAR;
            ev.code = (int)ch;
            queue_event(&ev);
        }
        break;
    }
    default:
        break;
    }
}

int rt_video_poll(RtInputEvent *ev) {
    if (!rt_video_on_video_thread()) return 0;
    flush_frame();
    SDL_Event e;
    while (npending == 0 && SDL_PollEvent(&e)) translate(&e);
    if (npending == 0) return 0;
    *ev = pending[0];
    npending--;
    memmove(pending, pending + 1, (size_t)npending * sizeof pending[0]);
    return 1;
}

void rt_video_warp_mouse(int x, int y) {
    if (!rt_video_on_video_thread()) return;
    int wx, wy;
    SDL_RenderLogicalToWindow(renderer, (float)x, (float)y, &wx, &wy);
    SDL_WarpMouseInWindow(window, wx, wy);
}

void rt_video_show_cursor(int show) {
    if (rt_video_on_video_thread()) SDL_ShowCursor(show ? SDL_ENABLE : SDL_DISABLE);
}

void rt_video_set_title(const char *title) {
    if (rt_video_on_video_thread()) SDL_SetWindowTitle(window, title);
}

void rt_video_message_box(const char *caption, const char *text) {
    if (rt_video_on_video_thread()) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, caption, text, window);
}

#else /* RT_NO_SDL */

void rt_video_open(const char *title, int width, int height) {
    (void)title;
    screen_w = width;
    screen_h = height;
    g_opt.headless = 1;
}
static void flush_frame(void) {}
int rt_video_poll(RtInputEvent *ev) { (void)ev; return 0; }
void rt_video_warp_mouse(int x, int y) { (void)x, (void)y; }
void rt_video_show_cursor(int show) { (void)show; }
void rt_video_set_title(const char *title) { (void)title; }
void rt_video_message_box(const char *caption, const char *text) { (void)caption, (void)text; }

#endif

void rt_video_present(const void *pixels, int width, int height, int pitch, int is555) {
    pthread_mutex_lock(&frame_mu);
    if (!frame_px || frame_w != width || frame_h != height) {
        free(frame_px);
        frame_px = malloc((size_t)width * (size_t)height * 2);
        frame_w = width;
        frame_h = height;
    }
    for (int y = 0; y < height; y++) {
        const uint16_t *src = (const uint16_t *)((const uint8_t *)pixels + (size_t)y * (size_t)pitch);
        uint16_t *dst = frame_px + (size_t)y * (size_t)width;
        if (is555) {
            for (int x = 0; x < width; x++) dst[x] = (uint16_t)(((src[x] & 0x7FE0) << 1) | (src[x] & 0x1F));
        } else {
            memcpy(dst, src, (size_t)width * 2);
        }
    }
    frame_dirty = 1;
    unsigned n = __atomic_add_fetch(&frame_count, 1, __ATOMIC_RELAXED);
    if (n == 1) rt_log("recomp: first frame presented (%dx%d)\n", width, height);
    if (g_opt.dump_frame > 0 && n == (unsigned)g_opt.dump_frame) dump_frame(frame_px, width, height);
    pthread_mutex_unlock(&frame_mu);
    if (rt_video_on_video_thread()) flush_frame();
    if (g_opt.exit_after_frame > 0 && n >= (unsigned)g_opt.exit_after_frame) {
        rt_log("\nrecomp: stopping after %u presented frames (--frames)\n", n);
        rt_print_import_stats();
        rt_exit(0);
    }
}
