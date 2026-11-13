/* Game controller and touch input (see pad.h).
 *
 * Everything here is independent of SDL: video.c feeds it button, stick and
 * finger changes (from SDL's game controller and touch events, or from the
 * input script) and it answers with the same pointer, key and character events
 * a mouse and a keyboard would produce. Video thread only. */
#define _GNU_SOURCE
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "pad.h"
#include "rt.h"
#include "video.h"

/* ---------------------------------------------------------------- names */
static const char *const button_names[RT_PAD_NBUTTONS] = {
    "a", "b", "x", "y", "back", "guide", "start", "ls", "rs", "lb", "rb",
    "dpup", "dpdown", "dpleft", "dpright", "lt", "rt",
};
/* Other spellings people use. */
static const struct { const char *alias, *name; } button_aliases[] = {
    {"select", "back"}, {"l1", "lb"}, {"r1", "rb"}, {"l2", "lt"}, {"r2", "rt"}, {"l3", "ls"}, {"r3", "rs"},
    {"up", "dpup"}, {"down", "dpdown"}, {"left", "dpleft"}, {"right", "dpright"},
    {"leftshoulder", "lb"}, {"rightshoulder", "rb"}, {"lefttrigger", "lt"}, {"righttrigger", "rt"},
    {"leftstick", "ls"}, {"rightstick", "rs"}, {"mode", "guide"},
};

int rt_pad_button_by_name(const char *name) {
    for (size_t i = 0; i < RT_COUNTOF(button_aliases); i++)
        if (!strcasecmp(name, button_aliases[i].alias)) name = button_aliases[i].name;
    for (int i = 0; i < RT_PAD_NBUTTONS; i++)
        if (!strcasecmp(name, button_names[i])) return i;
    return -1;
}

/* Key names for the configuration: Windows virtual key and DirectInput code. */
static const struct { const char *name; uint8_t vk, dik; } key_names[] = {
    {"space", 0x20, 0x39}, {"enter", 0x0D, 0x1C}, {"return", 0x0D, 0x1C}, {"escape", 0x1B, 0x01}, {"esc", 0x1B, 0x01},
    {"tab", 0x09, 0x0F}, {"backspace", 0x08, 0x0E}, {"up", 0x26, 0xC8}, {"down", 0x28, 0xD0},
    {"left", 0x25, 0xCB}, {"right", 0x27, 0xCD}, {"shift", 0x10, 0x2A}, {"ctrl", 0x11, 0x1D}, {"alt", 0x12, 0x38},
    {"pageup", 0x21, 0xC9}, {"pagedown", 0x22, 0xD1}, {"home", 0x24, 0xC7}, {"end", 0x23, 0xCF},
    {"insert", 0x2D, 0xD2}, {"delete", 0x2E, 0xD3},
    {"f1", 0x70, 0x3B}, {"f2", 0x71, 0x3C}, {"f3", 0x72, 0x3D}, {"f4", 0x73, 0x3E}, {"f5", 0x74, 0x3F},
    {"f6", 0x75, 0x40}, {"f7", 0x76, 0x41}, {"f8", 0x77, 0x42}, {"f9", 0x78, 0x43}, {"f10", 0x79, 0x44},
    {"f11", 0x7A, 0x57}, {"f12", 0x7B, 0x58},
    {"1", '1', 0x02}, {"2", '2', 0x03}, {"3", '3', 0x04}, {"4", '4', 0x05}, {"5", '5', 0x06},
    {"6", '6', 0x07}, {"7", '7', 0x08}, {"8", '8', 0x09}, {"9", '9', 0x0A}, {"0", '0', 0x0B},
    {"a", 'A', 0x1E}, {"b", 'B', 0x30}, {"c", 'C', 0x2E}, {"d", 'D', 0x20}, {"e", 'E', 0x12}, {"f", 'F', 0x21},
    {"g", 'G', 0x22}, {"h", 'H', 0x23}, {"i", 'I', 0x17}, {"j", 'J', 0x24}, {"k", 'K', 0x25}, {"l", 'L', 0x26},
    {"m", 'M', 0x32}, {"n", 'N', 0x31}, {"o", 'O', 0x18}, {"p", 'P', 0x19}, {"q", 'Q', 0x10}, {"r", 'R', 0x13},
    {"s", 'S', 0x1F}, {"t", 'T', 0x14}, {"u", 'U', 0x16}, {"v", 'V', 0x2F}, {"w", 'W', 0x11}, {"x", 'X', 0x2D},
    {"y", 'Y', 0x15}, {"z", 'Z', 0x2C},
};

/* ------------------------------------------------------------- mapping */
enum { ACT_NONE = 0, ACT_KEY, ACT_MOUSE };
typedef struct Action {
    uint8_t kind;
    uint8_t vk, dik; /* ACT_KEY */
    uint8_t button;  /* ACT_MOUSE: 1 left, 2 middle, 3 right */
} Action;

enum { STICK_NONE = 0, STICK_POINTER, STICK_ARROWS };
typedef struct StickRole {
    int kind;
    float scale; /* STICK_POINTER: fraction of the pointer speed */
} StickRole;

#define KEY(vk, dik) {ACT_KEY, vk, dik, 0}
#define MOUSE(b) {ACT_MOUSE, 0, 0, b}
static Action map[RT_PAD_NBUTTONS] = {
    [RT_PAD_A] = KEY(0x20, 0x39),       /* space: charge and fire */
    [RT_PAD_B] = KEY(0x1B, 0x01),       /* escape */
    [RT_PAD_X] = MOUSE(1),
    [RT_PAD_Y] = MOUSE(3),
    [RT_PAD_BACK] = KEY(0x09, 0x0F),    /* tab: next text field */
    [RT_PAD_START] = KEY(0x0D, 0x1C),   /* enter */
    [RT_PAD_LS] = MOUSE(1),
    [RT_PAD_LB] = KEY(0x76, 0x41),      /* F7 */
    [RT_PAD_RB] = KEY(0x77, 0x42),      /* F8 */
    [RT_PAD_DPUP] = KEY(0x26, 0xC8),
    [RT_PAD_DPDOWN] = KEY(0x28, 0xD0),
    [RT_PAD_DPLEFT] = KEY(0x25, 0xCB),
    [RT_PAD_DPRIGHT] = KEY(0x27, 0xCD),
    [RT_PAD_LT] = MOUSE(3),
    [RT_PAD_RT] = MOUSE(1),
};
static StickRole sticks[2] = {{STICK_POINTER, 1.0f}, {STICK_POINTER, 0.35f}};
static float cfg_speed = 600.0f;   /* guest pixels per second at full deflection */
static float cfg_deadzone = 0.15f; /* fraction of the stick's travel */
static float cfg_curve = 2.0f;     /* exponent of the response curve */
static int quit_combo[2] = {RT_PAD_BACK, RT_PAD_START};

static const char *key_name(uint8_t vk, uint8_t dik) {
    for (size_t i = 0; i < RT_COUNTOF(key_names); i++)
        if (key_names[i].vk == vk && key_names[i].dik == dik) return key_names[i].name;
    return NULL;
}

static void action_text(const Action *a, char *buf, size_t n) {
    static const char *const mb[] = {"?", "left", "middle", "right"};
    if (a->kind == ACT_KEY) {
        const char *k = key_name(a->vk, a->dik);
        if (k) snprintf(buf, n, "key %s", k);
        else snprintf(buf, n, "key 0x%02x 0x%02x", a->vk, a->dik);
    } else if (a->kind == ACT_MOUSE) {
        snprintf(buf, n, "mouse %s", mb[a->button & 3]);
    } else {
        snprintf(buf, n, "none");
    }
}

void rt_pad_print_config(FILE *f) {
    char buf[64];
    fprintf(f, "# Game controller mapping. Buttons are named as SDL's game controller API names\n"
               "# them: a is the bottom face button, b the right one, x left, y top.\n"
               "# button = key NAME | key 0xVK 0xDIK | mouse left|right|middle | none\n");
    for (int i = 0; i < RT_PAD_NBUTTONS; i++) {
        action_text(&map[i], buf, sizeof buf);
        fprintf(f, "%s = %s\n", button_names[i], buf);
    }
    for (int s = 0; s < 2; s++) {
        fprintf(f, "%s = ", s ? "rstick" : "lstick");
        if (sticks[s].kind == STICK_POINTER) fprintf(f, "pointer %.2f\n", (double)sticks[s].scale);
        else fprintf(f, "%s\n", sticks[s].kind == STICK_ARROWS ? "arrows" : "none");
    }
    fprintf(f, "# pointer speed in game pixels per second at full deflection (the screen is 800x600)\n"
               "speed = %.0f\ndeadzone = %.2f\ncurve = %.1f\n", (double)cfg_speed, (double)cfg_deadzone, (double)cfg_curve);
    if (quit_combo[0] >= 0)
        fprintf(f, "# held together: close the game; it is ended outright if it has not closed two seconds later\n"
                   "quit = %s+%s\n", button_names[quit_combo[0]], button_names[quit_combo[1]]);
    else fprintf(f, "quit = none\n");
}

static int parse_action(const char *v, Action *out) {
    char w1[32] = "", w2[32] = "", w3[32] = "";
    int n = sscanf(v, "%31s %31s %31s", w1, w2, w3);
    memset(out, 0, sizeof *out);
    if (n >= 1 && !strcasecmp(w1, "none")) return 1;
    if (n >= 2 && !strcasecmp(w1, "mouse")) {
        out->kind = ACT_MOUSE;
        out->button = !strcasecmp(w2, "left") ? 1 : !strcasecmp(w2, "right") ? 3 : !strcasecmp(w2, "middle") ? 2 : 0;
        return out->button != 0;
    }
    if (n >= 2 && !strcasecmp(w1, "key")) {
        out->kind = ACT_KEY;
        if (n == 3) {
            out->vk = (uint8_t)strtoul(w2, NULL, 16);
            out->dik = (uint8_t)strtoul(w3, NULL, 16);
            return out->vk != 0;
        }
        for (size_t i = 0; i < RT_COUNTOF(key_names); i++) {
            if (!strcasecmp(w2, key_names[i].name)) {
                out->vk = key_names[i].vk;
                out->dik = key_names[i].dik;
                return 1;
            }
        }
    }
    return 0;
}

int rt_pad_load_config(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) {
        rt_log("recomp: cannot read the controller configuration %s\n", path);
        return 0;
    }
    char line[256];
    int lineno = 0, ok = 1;
    while (fgets(line, sizeof line, f)) {
        lineno++;
        char *hash = strchr(line, '#');
        if (hash) *hash = 0;
        char *eq = strchr(line, '=');
        char name[32] = "";
        if (!eq) {
            if (sscanf(line, "%31s", name) == 1) goto bad;
            continue;
        }
        *eq = 0;
        const char *v = eq + 1 + strspn(eq + 1, " \t");
        if (sscanf(line, "%31s", name) != 1) goto bad;
        int b = rt_pad_button_by_name(name);
        if (!strcasecmp(name, "lstick") || !strcasecmp(name, "rstick")) {
            StickRole *s = &sticks[tolower((unsigned char)name[0]) == 'r'];
            char w[32] = "";
            float scale = 1.0f;
            int n = sscanf(v, "%31s %f", w, &scale);
            if (n >= 1 && !strcasecmp(w, "pointer")) *s = (StickRole){STICK_POINTER, scale > 0 ? scale : 1.0f};
            else if (n >= 1 && !strcasecmp(w, "arrows")) *s = (StickRole){STICK_ARROWS, 0};
            else if (n >= 1 && !strcasecmp(w, "none")) *s = (StickRole){STICK_NONE, 0};
            else goto bad;
        } else if (!strcasecmp(name, "speed")) {
            if (atof(v) <= 0) goto bad;
            cfg_speed = (float)atof(v);
        } else if (!strcasecmp(name, "deadzone")) {
            cfg_deadzone = (float)atof(v);
            if (cfg_deadzone < 0 || cfg_deadzone > 0.9f) goto bad;
        } else if (!strcasecmp(name, "curve")) {
            cfg_curve = (float)atof(v);
            if (cfg_curve < 0.5f || cfg_curve > 5) goto bad;
        } else if (!strcasecmp(name, "quit")) {
            char b1[32] = "", b2[32] = "";
            if (sscanf(v, " %31[^+ \t\r\n] + %31s", b1, b2) == 2 && rt_pad_button_by_name(b1) >= 0 &&
                rt_pad_button_by_name(b2) >= 0) {
                quit_combo[0] = rt_pad_button_by_name(b1);
                quit_combo[1] = rt_pad_button_by_name(b2);
            } else if (!strcasecmp(b1, "none")) {
                quit_combo[0] = quit_combo[1] = -1;
            } else goto bad;
        } else if (b >= 0) {
            Action act;
            if (!parse_action(v, &act)) goto bad;
            map[b] = act;
        } else goto bad;
        continue;
    bad:
        rt_log("recomp: %s:%d: not understood\n", path, lineno);
        ok = 0;
    }
    fclose(f);
    return ok;
}

void rt_pad_set_speed(double px_per_second) {
    if (px_per_second > 0) cfg_speed = (float)px_per_second;
}

/* --------------------------------------------------------------- state */
static uint8_t btn_down[RT_PAD_NBUTTONS];
static Action btn_action[RT_PAD_NBUTTONS]; /* what the button pressed, so that its release undoes that */
static float stick_x[2], stick_y[2];
static uint8_t stick_arrow[2][4];          /* STICK_ARROWS: up, down, left, right held */
static int key_holds[256];                 /* by DirectInput code: how many sources hold the key */
static uint8_t key_vk[256];
static int mouse_holds[4];
static unsigned mouse_pressed_at[4];       /* frame of the press */
static uint8_t mouse_release_due[4];
static uint64_t repeat_at;                 /* guest time of the next repeat of repeat_dik, 0 = none */
static uint8_t repeat_dik;
static uint64_t last_tick_ns;
static double frac_x, frac_y;              /* pointer motion not yet a whole pixel */
static int quit_sent;
static uint64_t quit_deadline;
static int touch_down;

#define REPEAT_DELAY_NS 400000000ull
#define REPEAT_EVERY_NS 40000000ull
#define MIN_CLICK_FRAMES 2 /* the game samples the buttons once a frame */

static int key_char(uint8_t vk) {
    if (vk == 0x20) return ' ';
    if (vk >= '0' && vk <= '9') return vk;
    if (vk >= 'A' && vk <= 'Z') return vk + 32;
    return 0;
}

static void hold_key(uint8_t vk, uint8_t dik, int down) {
    if (down) {
        if (key_holds[dik]++ == 0) {
            key_vk[dik] = vk;
            rt_in_key(vk, dik, 1, 0);
            if (key_char(vk)) rt_in_char(key_char(vk));
            repeat_dik = dik;
            repeat_at = rt_mono_ns() + REPEAT_DELAY_NS;
        }
    } else if (key_holds[dik] > 0 && --key_holds[dik] == 0) {
        rt_in_key(vk, dik, 0, 0);
        if (repeat_dik == dik) repeat_at = 0;
    }
}

static void hold_mouse(int button, int down) {
    if (down) {
        if (mouse_holds[button]++ == 0) {
            if (mouse_release_due[button]) {
                /* pressed again before the delayed release of the last press went out */
                mouse_release_due[button] = 0;
                rt_in_mouse_button(button, 0, 1);
            }
            rt_in_mouse_button(button, 1, 1);
            mouse_pressed_at[button] = rt_video_frames();
        }
    } else if (mouse_holds[button] > 0 && --mouse_holds[button] == 0) {
        if (rt_video_frames() < mouse_pressed_at[button] + MIN_CLICK_FRAMES) mouse_release_due[button] = 1;
        else rt_in_mouse_button(button, 0, 1);
    }
}

static void apply(const Action *a, int down) {
    if (a->kind == ACT_KEY) hold_key(a->vk, a->dik, down);
    else if (a->kind == ACT_MOUSE) hold_mouse(a->button, down);
}

void rt_pad_button(int button, int down) {
    if (button < 0 || button >= RT_PAD_NBUTTONS || btn_down[button] == (down != 0)) return;
    btn_down[button] = down != 0;
    if (g_opt.trace_input) rt_log("[pad] %s %s\n", button_names[button], down ? "down" : "up");
    if (down) {
        btn_action[button] = map[button];
        /* the quit combination: its second button does not also act */
        if (quit_combo[0] >= 0 && btn_down[quit_combo[0]] && btn_down[quit_combo[1]] &&
            (button == quit_combo[0] || button == quit_combo[1])) {
            btn_action[button].kind = ACT_NONE;
            int other = button == quit_combo[0] ? quit_combo[1] : quit_combo[0];
            apply(&btn_action[other], 0);
            btn_action[other].kind = ACT_NONE;
            if (!quit_sent) {
                rt_log("recomp: controller: %s+%s, closing the game\n", button_names[quit_combo[0]],
                       button_names[quit_combo[1]]);
                quit_sent = 1;
                quit_deadline = rt_host_ns() + 2000000000ull;
                rt_in_quit();
            }
            return;
        }
        apply(&btn_action[button], 1);
    } else {
        apply(&btn_action[button], 0);
    }
}

void rt_pad_trigger(int which, double value) {
    /* a trigger is a button with hysteresis */
    int b = which ? RT_PAD_RT : RT_PAD_LT;
    if (!btn_down[b] && value > 0.5) rt_pad_button(b, 1);
    else if (btn_down[b] && value < 0.3) rt_pad_button(b, 0);
}

void rt_pad_stick(int which, double x, double y) {
    which = which != 0;
    stick_x[which] = (float)(x < -1 ? -1 : x > 1 ? 1 : x);
    stick_y[which] = (float)(y < -1 ? -1 : y > 1 ? 1 : y);
    if (g_opt.trace_input) rt_log("[pad] %s stick %.2f %.2f\n", which ? "right" : "left", x, y);
    if (sticks[which].kind == STICK_ARROWS) {
        static const uint8_t keys[4][2] = {{0x26, 0xC8}, {0x28, 0xD0}, {0x25, 0xCB}, {0x27, 0xCD}};
        float v[4] = {-stick_y[which], stick_y[which], -stick_x[which], stick_x[which]};
        for (int i = 0; i < 4; i++) {
            int want = stick_arrow[which][i] ? v[i] > 0.35f : v[i] > 0.55f;
            if (want != stick_arrow[which][i]) {
                stick_arrow[which][i] = (uint8_t)want;
                hold_key(keys[i][0], keys[i][1], want);
            }
        }
    }
}

void rt_pad_release_all(void) {
    for (int b = 0; b < RT_PAD_NBUTTONS; b++)
        if (btn_down[b]) rt_pad_button(b, 0);
    rt_pad_stick(0, 0, 0);
    rt_pad_stick(1, 0, 0);
}

/* Stick deflection to pointer velocity: nothing inside the dead zone, then the
 * remaining travel raised to the curve's exponent, so that small deflections
 * are slow and precise and the rim is fast. */
static void stick_velocity(int s, double *vx, double *vy) {
    double x = stick_x[s], y = stick_y[s], m = sqrt(x * x + y * y);
    if (sticks[s].kind != STICK_POINTER || m <= cfg_deadzone) return;
    double t = (m - cfg_deadzone) / (1.0 - cfg_deadzone);
    if (t > 1) t = 1;
    double v = pow(t, cfg_curve) * cfg_speed * sticks[s].scale;
    *vx += x / m * v;
    *vy += y / m * v;
}

void rt_pad_tick(void) {
    for (int b = 1; b <= 3; b++) {
        if (mouse_release_due[b] && rt_video_frames() >= mouse_pressed_at[b] + MIN_CLICK_FRAMES) {
            mouse_release_due[b] = 0;
            rt_in_mouse_button(b, 0, 1);
        }
    }
    if (quit_sent && rt_host_ns() >= quit_deadline) {
        rt_log("recomp: controller: the game did not close; ending it\n");
        rt_exit(0);
    }
    uint64_t now = rt_mono_ns();
    if (repeat_at && now >= repeat_at) {
        if (key_holds[repeat_dik] > 0) {
            rt_in_key(key_vk[repeat_dik], repeat_dik, 1, 1);
            if (key_char(key_vk[repeat_dik])) rt_in_char(key_char(key_vk[repeat_dik]));
            repeat_at = now + REPEAT_EVERY_NS;
        } else {
            repeat_at = 0;
        }
    }
    double vx = 0, vy = 0;
    stick_velocity(0, &vx, &vy);
    stick_velocity(1, &vx, &vy);
    if (vx == 0 && vy == 0) {
        last_tick_ns = 0;
        frac_x = frac_y = 0;
        return;
    }
    if (!last_tick_ns) {
        last_tick_ns = now;
        return;
    }
    uint64_t dt = now - last_tick_ns;
    if (dt < 4000000ull) return; /* at most 250 steps a second */
    last_tick_ns = now;
    if (dt > 100000000ull) dt = 100000000ull;
    frac_x += vx * (double)dt / 1e9;
    frac_y += vy * (double)dt / 1e9;
    int dx = (int)frac_x, dy = (int)frac_y;
    if (!dx && !dy) return;
    frac_x -= dx;
    frac_y -= dy;
    rt_in_mouse_move_by(dx, dy);
}

/* ---------------------------------------------------------------- touch
 * One finger is the pointer with its left button held. */
void rt_touch(int phase, int x, int y) {
    if (g_opt.trace_input) rt_log("[touch] %s %d %d\n", phase == RT_TOUCH_DOWN ? "down" : phase == RT_TOUCH_UP ? "up" : "move", x, y);
    if (phase == RT_TOUCH_UP) {
        if (touch_down) hold_mouse(1, 0);
        touch_down = 0;
        return;
    }
    if (phase == RT_TOUCH_MOVE && !touch_down) return;
    rt_in_mouse_move_to(x, y);
    if (phase == RT_TOUCH_DOWN && !touch_down) {
        touch_down = 1;
        hold_mouse(1, 1);
    }
}
