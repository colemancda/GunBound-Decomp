/* ddraw.dll: DirectDraw 7 and the parts of Direct3D 7 the game needs to start.
 *
 * The game asks for IDirectDraw7, sets an exclusive 800x600 16-bit mode, creates
 * a primary surface with one back buffer, and draws most screens itself into the
 * locked back buffer; Flip presents it. Surface pixels live in guest memory, so
 * Lock hands out real pointers. The primary surface is shown through video.c.
 *
 * It also creates a Direct3D 7 device on the back buffer and draws through it
 * with pre-transformed (XYZRHW) vertices: screen wipes, and the sprites of the
 * battle screens. Triangles are rasterised in software (raster.c) from the
 * device's blend, alpha-test, depth and stage-0 texture state. Untransformed
 * vertices, lines, points and a second texture stage are not implemented; each
 * is reported the first time it is asked for.
 */
#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "com.h"
#include "raster.h"
#include "rt.h"
#include "video.h"

#define DD_OK 0u
#define DDERR_INVALIDPARAMS 0x80070057u
#define DDERR_UNSUPPORTED 0x80004001u
#define DDERR_NOTFOUND 0x887600FFu
#define DDERR_SURFACEBUSY 0x887601AEu
#define DDERR_NOCLIPPERATTACHED 0x887600CDu
#define DDERR_NOCOLORKEY 0x887600D7u

#define DDSD_CAPS 0x1u
#define DDSD_HEIGHT 0x2u
#define DDSD_WIDTH 0x4u
#define DDSD_PITCH 0x8u
#define DDSD_BACKBUFFERCOUNT 0x20u
#define DDSD_LPSURFACE 0x800u
#define DDSD_PIXELFORMAT 0x1000u
#define DDSD_REFRESHRATE 0x40000u

#define DDSCAPS_BACKBUFFER 0x4u
#define DDSCAPS_COMPLEX 0x8u
#define DDSCAPS_FLIP 0x10u
#define DDSCAPS_FRONTBUFFER 0x20u
#define DDSCAPS_PRIMARYSURFACE 0x200u
#define DDSCAPS_TEXTURE 0x1000u
#define DDSCAPS_ZBUFFER 0x20000u

#define DDPF_ALPHAPIXELS 0x1u
#define DDPF_RGB 0x40u
#define DDPF_ZBUFFER 0x400u

#define DDBLT_COLORFILL 0x400u
#define DDBLT_KEYSRC 0x8000u
#define DDBLT_KEYSRCOVERRIDE 0x10000u
#define DDBLTFAST_SRCCOLORKEY 0x1u

#define MAGIC_DDRAW 0x44443700u   /* "DD7" */
#define MAGIC_SURFACE 0x53524600u /* "SRF" */
#define MAGIC_CLIPPER 0x434C5000u /* "CLP" */
#define MAGIC_D3D 0x44334400u     /* "D3D" */
#define MAGIC_DEVICE 0x44455600u  /* "DEV" */

typedef struct PixFmt {
    uint32_t flags, bits, rmask, gmask, bmask, amask;
} PixFmt;

typedef struct Surface {
    int used, refs;
    uint32_t obj;
    uint32_t caps;
    int w, h, pitch;
    PixFmt pf;
    uint32_t pixels; /* guest address */
    int back, zbuf;  /* indices of attached surfaces, -1 if none */
    int implicit;    /* created as part of another surface's flip chain */
    int has_ckey;
    uint32_t ckey;
    uint32_t clipper;
} Surface;

#define MAX_SURFACES 4096
static Surface surfaces[MAX_SURFACES];
static pthread_mutex_t dd_mu = PTHREAD_MUTEX_INITIALIZER;
static uint32_t vt_ddraw, vt_surface, vt_clipper, vt_d3d, vt_device;
static int mode_w = 800, mode_h = 600, mode_bpp = 16;
static const PixFmt fmt_565 = {DDPF_RGB, 16, 0xF800, 0x07E0, 0x001F, 0};
static const PixFmt fmt_4444 = {DDPF_RGB | DDPF_ALPHAPIXELS, 16, 0x0F00, 0x00F0, 0x000F, 0xF000};
static const PixFmt fmt_1555 = {DDPF_RGB | DDPF_ALPHAPIXELS, 16, 0x7C00, 0x03E0, 0x001F, 0x8000};
static const PixFmt fmt_z16 = {DDPF_ZBUFFER, 16, 0, 0xFFFF, 0, 0}; /* gmask slot holds dwZBitMask */

static struct {
    int render_target;      /* surface index */
    uint32_t render_state[256];
    uint32_t stage_state[8][32];
    uint32_t texture[8];
    uint32_t viewport[6];
    int in_scene;
} dev;

/* ------------------------------------------------------------ COM helpers */
uint32_t rt_com_vtable(const char *dll, const char *iface, const ComMethod *methods, unsigned count) {
    uint32_t vt = rt_heap_alloc(4 * count, 1);
    for (unsigned i = 0; i < count; i++) {
        char name[96];
        snprintf(name, sizeof name, "%s::%s", iface, methods[i].name);
        st32(vt + 4 * i, rt_host_fn(dll, name, methods[i].fn, methods[i].nargs));
    }
    return vt;
}

uint32_t rt_com_object(uint32_t vtable, uint32_t index, uint32_t magic) {
    uint32_t o = rt_heap_alloc(16, 1);
    st32(o, vtable);
    st32(o + 4, index);
    st32(o + 8, magic);
    return o;
}

int rt_com_index(uint32_t obj, uint32_t magic) {
    if (!obj || !rt_guest_readable(obj, 12) || ld32(obj + 8) != magic) return -1;
    return (int)ld32(obj + 4);
}

void rt_com_free(uint32_t obj) {
    st32(obj + 8, 0);
    rt_heap_free(obj);
}

const char *rt_guid_str(uint32_t g, char buf[40]) {
    snprintf(buf, 40, "{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}", ld32(g), ld16(g + 4), ld16(g + 6),
             ld8(g + 8), ld8(g + 9), ld8(g + 10), ld8(g + 11), ld8(g + 12), ld8(g + 13), ld8(g + 14), ld8(g + 15));
    return buf;
}

int rt_guid_eq(uint32_t g, const uint8_t ref[16]) { return g && memcmp(G(g), ref, 16) == 0; }

static const uint8_t IID_IUnknown[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0xC0, 0, 0, 0, 0, 0, 0, 0x46};
static const uint8_t IID_IDirectDraw7[16] = {0xC0, 0x5E, 0xE6, 0x15, 0x9C, 0x3B, 0xD2, 0x11,
                                              0xB9, 0x2F, 0x00, 0x60, 0x97, 0x97, 0xEA, 0x5B};
static const uint8_t IID_IDirect3D7[16] = {0x77, 0x9E, 0x04, 0xF5, 0x61, 0x48, 0xD2, 0x11,
                                            0xA4, 0x07, 0x00, 0xA0, 0xC9, 0x06, 0x29, 0xA8};
static const uint8_t IID_IDirectDrawSurface7[16] = {0x80, 0x5A, 0x67, 0x06, 0x9B, 0x3B, 0xD2, 0x11,
                                                     0xB9, 0x2F, 0x00, 0x60, 0x97, 0x97, 0xEA, 0x5B};
/* Device class IDs a program can pass to IDirect3D7::CreateDevice. */
static const uint8_t IID_IDirect3DHALDevice[16] = {0xE0, 0x3D, 0xE6, 0x84, 0xAA, 0x46, 0xCF, 0x11,
                                                    0x81, 0x6F, 0x00, 0x00, 0xC0, 0x20, 0x15, 0x6E};
static const uint8_t IID_IDirect3DTnLHalDevice[16] = {0x78, 0x9E, 0x04, 0xF5, 0x61, 0x48, 0xD2, 0x11,
                                                       0xA4, 0x07, 0x00, 0xA0, 0xC9, 0x06, 0x29, 0xA8};
static const uint8_t IID_IDirect3DRGBDevice[16] = {0x60, 0x5C, 0x66, 0xA4, 0x73, 0x26, 0xCF, 0x11,
                                                    0xA3, 0x1A, 0x00, 0xAA, 0x00, 0xB9, 0x33, 0x56};

/* ---------------------------------------------------------------- surfaces */
static Surface *surf_of(uint32_t obj) {
    int i = rt_com_index(obj, MAGIC_SURFACE);
    if (i < 0 || i >= MAX_SURFACES || !surfaces[i].used) return NULL;
    return &surfaces[i];
}

static int surf_new(uint32_t caps, int w, int h, const PixFmt *pf) {
    pthread_mutex_lock(&dd_mu);
    int i;
    for (i = 0; i < MAX_SURFACES; i++)
        if (!surfaces[i].used) break;
    if (i == MAX_SURFACES) {
        pthread_mutex_unlock(&dd_mu);
        return -1;
    }
    Surface *s = &surfaces[i];
    memset(s, 0, sizeof *s);
    s->used = 1;
    pthread_mutex_unlock(&dd_mu);
    s->refs = 1;
    s->caps = caps;
    s->w = w;
    s->h = h;
    s->pf = *pf;
    s->pitch = (w * (int)(pf->bits / 8) + 3) & ~3;
    s->back = s->zbuf = -1;
    s->pixels = rt_heap_alloc((uint32_t)(s->pitch * h) + 16, 1);
    if (!s->pixels) {
        s->used = 0;
        return -1;
    }
    s->obj = rt_com_object(vt_surface, (uint32_t)i, MAGIC_SURFACE);
    return i;
}

static void surf_destroy(Surface *s) {
    if (s->back >= 0 && surfaces[s->back].implicit) surf_destroy(&surfaces[s->back]);
    rt_heap_free(s->pixels);
    rt_com_free(s->obj);
    if (dev.render_target == (int)(s - surfaces)) dev.render_target = -1;
    s->used = 0;
}

static void write_pixfmt(uint32_t p, const PixFmt *pf) {
    memset(G(p), 0, 32);
    st32(p, 32);
    st32(p + 4, pf->flags);
    st32(p + 12, pf->bits);
    st32(p + 16, pf->rmask);
    st32(p + 20, pf->gmask);
    st32(p + 24, pf->bmask);
    st32(p + 28, pf->amask);
}

static void read_pixfmt(uint32_t p, PixFmt *pf) {
    pf->flags = ld32(p + 4);
    pf->bits = ld32(p + 12);
    pf->rmask = ld32(p + 16);
    pf->gmask = ld32(p + 20);
    pf->bmask = ld32(p + 24);
    pf->amask = ld32(p + 28);
}

/* Fill a DDSURFACEDESC2 (the caller's dwSize is kept). */
static void write_desc(uint32_t d, const Surface *s) {
    uint32_t size = ld32(d);
    if (size != 124 && size != 108) size = 124; /* DDSURFACEDESC2 or the old DDSURFACEDESC */
    memset(G(d), 0, size);
    st32(d, size);
    st32(d + 4, DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PITCH | DDSD_PIXELFORMAT |
                (s->back >= 0 ? DDSD_BACKBUFFERCOUNT : 0));
    st32(d + 8, (uint32_t)s->h);
    st32(d + 12, (uint32_t)s->w);
    st32(d + 16, (uint32_t)s->pitch);
    st32(d + 20, s->back >= 0 ? 1 : 0);
    write_pixfmt(d + 72, &s->pf);
    st32(d + 104, s->caps);
}

static void present(const Surface *s) {
    if (s->pf.bits != 16) return;
    rt_video_present(G(s->pixels), s->w, s->h, s->pitch, s->pf.gmask == 0x03E0);
}

H(surf_QueryInterface) {
    UNUSED;
    Surface *s = surf_of(a[0]);
    char buf[40];
    if (!s || !a[2]) return E_POINTER;
    if (rt_guid_eq(a[1], IID_IUnknown) || rt_guid_eq(a[1], IID_IDirectDrawSurface7)) {
        s->refs++;
        st32(a[2], a[0]);
        return S_OK;
    }
    rt_log("recomp: IDirectDrawSurface7::QueryInterface(%s) is not supported\n", rt_guid_str(a[1], buf));
    st32(a[2], 0);
    return E_NOINTERFACE;
}

H(surf_AddRef) {
    UNUSED;
    Surface *s = surf_of(a[0]);
    return s ? (uint32_t)++s->refs : 0;
}

H(surf_Release) {
    UNUSED;
    Surface *s = surf_of(a[0]);
    if (!s) return 0;
    if (--s->refs > 0) return (uint32_t)s->refs;
    if (s->implicit) {
        s->refs = 0; /* lives as long as the surface it is attached to */
        return 0;
    }
    surf_destroy(s);
    return 0;
}

H(surf_AddAttachedSurface) {
    UNUSED;
    Surface *s = surf_of(a[0]), *t = surf_of(a[1]);
    if (!s || !t) return DDERR_INVALIDPARAMS;
    if (t->caps & DDSCAPS_ZBUFFER) s->zbuf = (int)(t - surfaces);
    else s->back = (int)(t - surfaces);
    t->refs++;
    return DD_OK;
}

H(surf_GetAttachedSurface) {
    UNUSED;
    Surface *s = surf_of(a[0]);
    if (!s || !a[1] || !a[2]) return DDERR_INVALIDPARAMS;
    uint32_t want = ld32(a[1]);
    int i = (want & DDSCAPS_ZBUFFER) ? s->zbuf : (want & DDSCAPS_BACKBUFFER) ? s->back : -1;
    if (i < 0) {
        st32(a[2], 0);
        return DDERR_NOTFOUND;
    }
    surfaces[i].refs++;
    st32(a[2], surfaces[i].obj);
    return DD_OK;
}

typedef struct Rect {
    int l, t, r, b;
} Rect;

static Rect rect_of(uint32_t p, const Surface *s) {
    Rect r = {0, 0, s->w, s->h};
    if (p) {
        r.l = (int32_t)ld32(p);
        r.t = (int32_t)ld32(p + 4);
        r.r = (int32_t)ld32(p + 8);
        r.b = (int32_t)ld32(p + 12);
    }
    return r;
}

static uint32_t get_px(const uint8_t *p, int bpp) {
    switch (bpp) {
    case 1: return *p;
    case 2: { uint16_t v; memcpy(&v, p, 2); return v; }
    case 3: return p[0] | (p[1] << 8) | ((uint32_t)p[2] << 16);
    default: { uint32_t v; memcpy(&v, p, 4); return v; }
    }
}

static void put_px(uint8_t *p, int bpp, uint32_t v) {
    switch (bpp) {
    case 1: *p = (uint8_t)v; break;
    case 2: { uint16_t w = (uint16_t)v; memcpy(p, &w, 2); break; }
    case 3: p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8); p[2] = (uint8_t)(v >> 16); break;
    default: memcpy(p, &v, 4); break;
    }
}

/* Copy sr of src to dr of dst with nearest-neighbour scaling, clipped to dst. */
static void blit(Surface *dst, Rect dr, const Surface *src, Rect sr, int use_key, uint32_t key) {
    int bpp = (int)dst->pf.bits / 8;
    int dw = dr.r - dr.l, dh = dr.b - dr.t, sw = sr.r - sr.l, sh = sr.b - sr.t;
    if (dw <= 0 || dh <= 0 || sw <= 0 || sh <= 0 || bpp != (int)src->pf.bits / 8) return;
    uint8_t *dp = G(dst->pixels);
    const uint8_t *sp = G(src->pixels);
    int same = dw == sw && dh == sh;
    for (int y = 0; y < dh; y++) {
        int dy = dr.t + y, sy = sr.t + (same ? y : (int)((int64_t)y * sh / dh));
        if (dy < 0 || dy >= dst->h || sy < 0 || sy >= src->h) continue;
        uint8_t *drow = dp + (size_t)dy * (size_t)dst->pitch;
        const uint8_t *srow = sp + (size_t)sy * (size_t)src->pitch;
        if (same && !use_key) {
            int x0 = 0, x1 = dw;
            if (dr.l < 0) x0 = -dr.l;
            if (sr.l + x0 < 0) x0 = -sr.l;
            if (dr.l + x1 > dst->w) x1 = dst->w - dr.l;
            if (sr.l + x1 > src->w) x1 = src->w - sr.l;
            if (x1 > x0)
                memmove(drow + (size_t)(dr.l + x0) * (size_t)bpp, srow + (size_t)(sr.l + x0) * (size_t)bpp,
                        (size_t)(x1 - x0) * (size_t)bpp);
            continue;
        }
        for (int x = 0; x < dw; x++) {
            int dx = dr.l + x, sx = sr.l + (same ? x : (int)((int64_t)x * sw / dw));
            if (dx < 0 || dx >= dst->w || sx < 0 || sx >= src->w) continue;
            uint32_t v = get_px(srow + (size_t)sx * (size_t)bpp, bpp);
            if (use_key && v == key) continue;
            put_px(drow + (size_t)dx * (size_t)bpp, bpp, v);
        }
    }
}

static void fill(Surface *dst, Rect dr, uint32_t color) {
    int bpp = (int)dst->pf.bits / 8;
    if (dr.l < 0) dr.l = 0;
    if (dr.t < 0) dr.t = 0;
    if (dr.r > dst->w) dr.r = dst->w;
    if (dr.b > dst->h) dr.b = dst->h;
    for (int y = dr.t; y < dr.b; y++) {
        uint8_t *row = G(dst->pixels) + (size_t)y * (size_t)dst->pitch;
        if (bpp == 2) {
            uint16_t *p = (uint16_t *)(void *)row;
            for (int x = dr.l; x < dr.r; x++) p[x] = (uint16_t)color;
        } else {
            for (int x = dr.l; x < dr.r; x++) put_px(row + (size_t)x * (size_t)bpp, bpp, color);
        }
    }
}

/* Blt(this, destRect, src, srcRect, flags, bltFx) */
H(surf_Blt) {
    UNUSED;
    Surface *dst = surf_of(a[0]);
    if (!dst) return DDERR_INVALIDPARAMS;
    Rect dr = rect_of(a[1], dst);
    if (a[4] & DDBLT_COLORFILL) {
        if (!a[5]) return DDERR_INVALIDPARAMS;
        fill(dst, dr, ld32(a[5] + 80)); /* DDBLTFX.dwFillColor */
    } else {
        Surface *src = surf_of(a[2]);
        if (!src) return DDERR_INVALIDPARAMS;
        Rect sr = rect_of(a[3], src);
        int use_key = 0;
        uint32_t key = 0;
        if ((a[4] & DDBLT_KEYSRC) && src->has_ckey) {
            use_key = 1;
            key = src->ckey;
        } else if ((a[4] & DDBLT_KEYSRCOVERRIDE) && a[5]) {
            use_key = 1;
            key = ld32(a[5] + 92); /* DDBLTFX.ddckSrcColorkey.low */
        }
        if (src->pf.bits != dst->pf.bits) {
            rt_log("recomp: IDirectDrawSurface7::Blt between %u-bit and %u-bit surfaces is not supported\n",
                   src->pf.bits, dst->pf.bits);
            return DDERR_UNSUPPORTED;
        }
        blit(dst, dr, src, sr, use_key, key);
    }
    if (dst->caps & DDSCAPS_PRIMARYSURFACE) present(dst);
    return DD_OK;
}

/* BltFast(this, x, y, src, srcRect, trans) */
H(surf_BltFast) {
    UNUSED;
    Surface *dst = surf_of(a[0]), *src = surf_of(a[3]);
    if (!dst || !src) return DDERR_INVALIDPARAMS;
    Rect sr = rect_of(a[4], src);
    Rect dr = {(int32_t)a[1], (int32_t)a[2], (int32_t)a[1] + (sr.r - sr.l), (int32_t)a[2] + (sr.b - sr.t)};
    if (src->pf.bits != dst->pf.bits) return DDERR_UNSUPPORTED;
    blit(dst, dr, src, sr, (a[5] & DDBLTFAST_SRCCOLORKEY) && src->has_ckey, src->ckey);
    if (dst->caps & DDSCAPS_PRIMARYSURFACE) present(dst);
    return DD_OK;
}

/* Flip(this, targetOverride, flags): the back buffer becomes visible and the
 * old front buffer becomes the back buffer, by exchanging their memory. */
H(surf_Flip) {
    UNUSED;
    Surface *s = surf_of(a[0]);
    if (!s || s->back < 0) return DDERR_INVALIDPARAMS;
    Surface *b = &surfaces[s->back];
    uint32_t t = s->pixels;
    s->pixels = b->pixels;
    b->pixels = t;
    present(s);
    return DD_OK;
}

H(surf_GetCaps) {
    UNUSED;
    Surface *s = surf_of(a[0]);
    if (!s || !a[1]) return DDERR_INVALIDPARAMS;
    memset(G(a[1]), 0, 16);
    st32(a[1], s->caps);
    return DD_OK;
}

H(surf_GetPixelFormat) {
    UNUSED;
    Surface *s = surf_of(a[0]);
    if (!s || !a[1]) return DDERR_INVALIDPARAMS;
    write_pixfmt(a[1], &s->pf);
    return DD_OK;
}

H(surf_GetSurfaceDesc) {
    UNUSED;
    Surface *s = surf_of(a[0]);
    if (!s || !a[1]) return DDERR_INVALIDPARAMS;
    write_desc(a[1], s);
    return DD_OK;
}

/* Lock(this, rect, desc, flags, event) */
H(surf_Lock) {
    UNUSED;
    Surface *s = surf_of(a[0]);
    if (!s || !a[2]) return DDERR_INVALIDPARAMS;
    write_desc(a[2], s);
    uint32_t p = s->pixels;
    if (a[1]) {
        Rect r = rect_of(a[1], s);
        if (r.l < 0 || r.t < 0 || r.r > s->w || r.b > s->h || r.l > r.r || r.t > r.b) return DDERR_INVALIDPARAMS;
        p += (uint32_t)(r.t * s->pitch + r.l * (int)(s->pf.bits / 8));
    }
    st32(a[2] + 4, ld32(a[2] + 4) | DDSD_LPSURFACE);
    st32(a[2] + 36, p);
    return DD_OK;
}

H(surf_Unlock) {
    UNUSED;
    Surface *s = surf_of(a[0]);
    if (!s) return DDERR_INVALIDPARAMS;
    if (s->caps & DDSCAPS_PRIMARYSURFACE) present(s);
    return DD_OK;
}

H(surf_IsLost) { UNUSED; return DD_OK; }
H(surf_Restore) { UNUSED; return DD_OK; }
H(surf_GetBltStatus) { UNUSED; return DD_OK; }
H(surf_GetFlipStatus) { UNUSED; return DD_OK; }

H(surf_SetClipper) {
    UNUSED;
    Surface *s = surf_of(a[0]);
    if (!s) return DDERR_INVALIDPARAMS;
    s->clipper = a[1];
    return DD_OK;
}

H(surf_GetClipper) {
    UNUSED;
    Surface *s = surf_of(a[0]);
    if (!s || !a[1]) return DDERR_INVALIDPARAMS;
    st32(a[1], s->clipper);
    return s->clipper ? DD_OK : DDERR_NOCLIPPERATTACHED;
}

/* SetColorKey(this, flags, colorKey{low, high}) */
H(surf_SetColorKey) {
    UNUSED;
    Surface *s = surf_of(a[0]);
    if (!s) return DDERR_INVALIDPARAMS;
    s->has_ckey = a[2] != 0;
    if (a[2]) s->ckey = ld32(a[2]);
    return DD_OK;
}

H(surf_GetColorKey) {
    UNUSED;
    Surface *s = surf_of(a[0]);
    if (!s || !a[2]) return DDERR_INVALIDPARAMS;
    if (!s->has_ckey) return DDERR_NOCOLORKEY;
    st32(a[2], s->ckey);
    st32(a[2] + 4, s->ckey);
    return DD_OK;
}

H(surf_ok1) { UNUSED; return DD_OK; }

static const ComMethod surface_methods[] = {
    {"QueryInterface", surf_QueryInterface, 3}, {"AddRef", surf_AddRef, 1}, {"Release", surf_Release, 1},
    {"AddAttachedSurface", surf_AddAttachedSurface, 2}, {"AddOverlayDirtyRect", NULL, 2}, {"Blt", surf_Blt, 6},
    {"BltBatch", NULL, 4}, {"BltFast", surf_BltFast, 6}, {"DeleteAttachedSurface", NULL, 3},
    {"EnumAttachedSurfaces", NULL, 3}, {"EnumOverlayZOrders", NULL, 4}, {"Flip", surf_Flip, 3},
    {"GetAttachedSurface", surf_GetAttachedSurface, 3}, {"GetBltStatus", surf_GetBltStatus, 2},
    {"GetCaps", surf_GetCaps, 2}, {"GetClipper", surf_GetClipper, 2}, {"GetColorKey", surf_GetColorKey, 3},
    {"GetDC", NULL, 2}, {"GetFlipStatus", surf_GetFlipStatus, 2}, {"GetOverlayPosition", NULL, 3},
    {"GetPalette", NULL, 2}, {"GetPixelFormat", surf_GetPixelFormat, 2},
    {"GetSurfaceDesc", surf_GetSurfaceDesc, 2}, {"Initialize", NULL, 3}, {"IsLost", surf_IsLost, 1},
    {"Lock", surf_Lock, 5}, {"ReleaseDC", NULL, 2}, {"Restore", surf_Restore, 1},
    {"SetClipper", surf_SetClipper, 2}, {"SetColorKey", surf_SetColorKey, 3}, {"SetOverlayPosition", NULL, 3},
    {"SetPalette", NULL, 2}, {"Unlock", surf_Unlock, 2}, {"UpdateOverlay", NULL, 6},
    {"UpdateOverlayDisplay", NULL, 2}, {"UpdateOverlayZOrder", NULL, 3}, {"GetDDInterface", NULL, 2},
    {"PageLock", surf_ok1, 2}, {"PageUnlock", surf_ok1, 2}, {"SetSurfaceDesc", NULL, 3},
    {"SetPrivateData", NULL, 5}, {"GetPrivateData", NULL, 4}, {"FreePrivateData", NULL, 2},
    {"GetUniquenessValue", NULL, 2}, {"ChangeUniquenessValue", NULL, 1}, {"SetPriority", surf_ok1, 2},
    {"GetPriority", NULL, 2}, {"SetLOD", surf_ok1, 2}, {"GetLOD", NULL, 2},
};

/* ----------------------------------------------------------------- clipper */
H(clip_QueryInterface) { UNUSED; if (a[2]) st32(a[2], 0); return E_NOINTERFACE; }
H(clip_AddRef) { UNUSED; uint32_t n = ld32(a[0] + 12) + 1; st32(a[0] + 12, n); return n; }
H(clip_Release) {
    UNUSED;
    if (rt_com_index(a[0], MAGIC_CLIPPER) < 0) return 0;
    uint32_t n = ld32(a[0] + 12) - 1;
    st32(a[0] + 12, n);
    if (n == 0) rt_com_free(a[0]);
    return n;
}
H(clip_GetHWnd) { UNUSED; if (a[1]) st32(a[1], ld32(a[0] + 4)); return DD_OK; }
H(clip_SetHWnd) { UNUSED; st32(a[0] + 4, a[2]); return DD_OK; }
H(clip_IsClipListChanged) { UNUSED; if (a[1]) st32(a[1], 0); return DD_OK; }

static const ComMethod clipper_methods[] = {
    {"QueryInterface", clip_QueryInterface, 3}, {"AddRef", clip_AddRef, 1}, {"Release", clip_Release, 1},
    {"GetClipList", NULL, 4}, {"GetHWnd", clip_GetHWnd, 2}, {"Initialize", NULL, 3},
    {"IsClipListChanged", clip_IsClipListChanged, 2}, {"SetClipList", NULL, 3}, {"SetHWnd", clip_SetHWnd, 3},
};

/* ------------------------------------------------------------- IDirectDraw7 */
static uint32_t d3d_obj, ddraw_obj;

H(dd_QueryInterface) {
    UNUSED;
    char buf[40];
    if (!a[2]) return E_POINTER;
    if (rt_guid_eq(a[1], IID_IUnknown) || rt_guid_eq(a[1], IID_IDirectDraw7)) {
        st32(a[0] + 12, ld32(a[0] + 12) + 1);
        st32(a[2], a[0]);
        return S_OK;
    }
    if (rt_guid_eq(a[1], IID_IDirect3D7)) {
        if (!d3d_obj) d3d_obj = rt_com_object(vt_d3d, 0, MAGIC_D3D);
        st32(d3d_obj + 12, ld32(d3d_obj + 12) + 1);
        st32(a[2], d3d_obj);
        return S_OK;
    }
    rt_log("recomp: IDirectDraw7::QueryInterface(%s) is not supported\n", rt_guid_str(a[1], buf));
    st32(a[2], 0);
    return E_NOINTERFACE;
}

H(dd_AddRef) { UNUSED; uint32_t n = ld32(a[0] + 12) + 1; st32(a[0] + 12, n); return n; }
H(dd_Release) {
    UNUSED;
    uint32_t n = ld32(a[0] + 12);
    if (n) st32(a[0] + 12, --n);
    return n; /* the singleton object itself is kept */
}

/* CreateClipper(this, flags, &clipper, outer) */
H(dd_CreateClipper) {
    UNUSED;
    if (!a[2]) return DDERR_INVALIDPARAMS;
    uint32_t o = rt_com_object(vt_clipper, 0, MAGIC_CLIPPER);
    st32(o + 12, 1);
    st32(a[2], o);
    return DD_OK;
}

/* CreateSurface(this, desc, &surface, outer) */
H(dd_CreateSurface) {
    UNUSED;
    uint32_t d = a[1];
    if (!d || !a[2] || (ld32(d) != 124 && ld32(d) != 108)) return DDERR_INVALIDPARAMS;
    uint32_t flags = ld32(d + 4), caps = (flags & DDSD_CAPS) ? ld32(d + 104) : 0;
    PixFmt pf = fmt_565;
    int w = mode_w, h = mode_h;
    if (!(caps & DDSCAPS_PRIMARYSURFACE)) {
        if (!(flags & DDSD_WIDTH) || !(flags & DDSD_HEIGHT)) return DDERR_INVALIDPARAMS;
        w = (int32_t)ld32(d + 12);
        h = (int32_t)ld32(d + 8);
        if (flags & DDSD_PIXELFORMAT) read_pixfmt(d + 72, &pf);
        if (w <= 0 || h <= 0 || w > 8192 || h > 8192 || (pf.bits != 8 && pf.bits != 16 && pf.bits != 24 && pf.bits != 32)) {
            rt_log("recomp: IDirectDraw7::CreateSurface: unsupported surface %dx%d, %u bits\n", w, h, pf.bits);
            return DDERR_INVALIDPARAMS;
        }
    }
    int i = surf_new(caps, w, h, &pf);
    if (i < 0) return E_OUTOFMEMORY;
    Surface *s = &surfaces[i];
    if (caps & DDSCAPS_PRIMARYSURFACE) {
        s->caps |= DDSCAPS_FRONTBUFFER;
        uint32_t nback = (flags & DDSD_BACKBUFFERCOUNT) ? ld32(d + 20) : 0;
        if (nback > 1) rt_log("recomp: flip chain with %u back buffers requested; one is provided\n", nback);
        if (nback) {
            uint32_t bcaps = (caps & ~(DDSCAPS_PRIMARYSURFACE | DDSCAPS_FRONTBUFFER)) | DDSCAPS_BACKBUFFER;
            int b = surf_new(bcaps, w, h, &pf);
            if (b < 0) {
                surf_destroy(s);
                return E_OUTOFMEMORY;
            }
            surfaces[b].implicit = 1;
            surfaces[b].refs = 0;
            s->back = b;
        }
    }
    if (g_opt.verbose)
        rt_log("[ddraw] surface %x: %dx%d %u bits, caps %08x, masks %x/%x/%x/%x\n", s->obj, w, h, pf.bits, s->caps,
               pf.rmask, pf.gmask, pf.bmask, pf.amask);
    st32(a[2], s->obj);
    return DD_OK;
}

static void write_mode_desc(uint32_t d, int w, int h) {
    memset(G(d), 0, 124);
    st32(d, 124);
    st32(d + 4, DDSD_HEIGHT | DDSD_WIDTH | DDSD_PITCH | DDSD_PIXELFORMAT | DDSD_REFRESHRATE);
    st32(d + 8, (uint32_t)h);
    st32(d + 12, (uint32_t)w);
    st32(d + 16, (uint32_t)w * 2);
    st32(d + 24, 60);
    write_pixfmt(d + 72, &fmt_565);
}

/* EnumDisplayModes(this, flags, desc, context, callback) */
H(dd_EnumDisplayModes) {
    static const int modes[][2] = {{640, 480}, {800, 600}, {1024, 768}};
    uint32_t sp = ESP;
    uint32_t d = rt_stack_alloc(c, 124);
    for (size_t i = 0; i < RT_COUNTOF(modes); i++) {
        if (a[2]) { /* filter: only modes matching the given description */
            uint32_t ff = ld32(a[2] + 4);
            if ((ff & DDSD_WIDTH) && (int)ld32(a[2] + 12) != modes[i][0]) continue;
            if ((ff & DDSD_HEIGHT) && (int)ld32(a[2] + 8) != modes[i][1]) continue;
            if ((ff & DDSD_PIXELFORMAT) && ld32(a[2] + 72 + 12) != 16) continue;
        }
        write_mode_desc(d, modes[i][0], modes[i][1]);
        uint32_t args[2] = {d, a[3]}, r = 0;
        if (!rt_call_guest(c, a[4], RT_STDCALL, 2, args, &r)) return 0;
        if (!r) break; /* DDENUMRET_CANCEL */
    }
    ESP = sp;
    return DD_OK;
}

H(dd_GetCaps) {
    UNUSED;
    for (int k = 1; k <= 2; k++) {
        uint32_t p = a[k];
        if (!p) continue;
        uint32_t size = ld32(p);
        if (size < 16 || size > 380) return DDERR_INVALIDPARAMS;
        memset(G(p + 4), 0, size - 4);
        st32(p + 4, 0x00000001u | 0x00000040u | 0x00400000u | 0x04000000u); /* 3D, BLT, COLORKEY, BLTCOLORFILL */
        st32(p + 8, 0x00080000u);  /* DDCAPS2_CANRENDERWINDOWED */
        st32(p + 12, 0x00000001u); /* DDCKEYCAPS_SRCBLT ... */
        if (size >= 0x40) {
            st32(p + 0x3C, 64u << 20); /* dwVidMemTotal */
            st32(p + 0x40, 64u << 20); /* dwVidMemFree */
        }
    }
    return DD_OK;
}

H(dd_GetDisplayMode) {
    UNUSED;
    if (!a[1]) return DDERR_INVALIDPARAMS;
    write_mode_desc(a[1], mode_w, mode_h);
    return DD_OK;
}

H(dd_GetMonitorFrequency) { UNUSED; if (a[1]) st32(a[1], 60); return DD_OK; }
H(dd_RestoreDisplayMode) { UNUSED; return DD_OK; }
H(dd_ok1) { UNUSED; return DD_OK; }

/* SetCooperativeLevel(this, hwnd, flags) */
H(dd_SetCooperativeLevel) {
    UNUSED;
    if (g_opt.verbose) rt_log("[ddraw] SetCooperativeLevel(hwnd %x, flags %#x)\n", a[1], a[2]);
    return DD_OK;
}

/* SetDisplayMode(this, width, height, bpp, refresh, flags) */
H(dd_SetDisplayMode) {
    UNUSED;
    rt_log("recomp: display mode %ux%u, %u bits, %u Hz requested\n", a[1], a[2], a[3], a[4]);
    if (a[3] != 16) {
        rt_log("recomp: only 16-bit display modes are supported\n");
        return DDERR_UNSUPPORTED;
    }
    mode_w = (int)a[1];
    mode_h = (int)a[2];
    mode_bpp = (int)a[3];
    rt_video_open("GunBound", mode_w, mode_h);
    return DD_OK;
}

H(dd_WaitForVerticalBlank) {
    UNUSED;
    struct timespec ts = {0, 1000000L};
    nanosleep(&ts, NULL);
    return DD_OK;
}

/* GetAvailableVidMem(this, caps, &total, &free) */
H(dd_GetAvailableVidMem) {
    UNUSED;
    if (a[2]) st32(a[2], 64u << 20);
    if (a[3]) st32(a[3], 64u << 20);
    return DD_OK;
}

H(dd_GetDeviceIdentifier) {
    UNUSED;
    if (!a[1]) return DDERR_INVALIDPARAMS;
    memset(G(a[1]), 0, 1068);
    strcpy((char *)G(a[1]), "recomp.dll");
    strcpy((char *)G(a[1] + 512), "GunBound recompilation software display");
    return DD_OK;
}

static const ComMethod ddraw_methods[] = {
    {"QueryInterface", dd_QueryInterface, 3}, {"AddRef", dd_AddRef, 1}, {"Release", dd_Release, 1},
    {"Compact", dd_ok1, 1}, {"CreateClipper", dd_CreateClipper, 4}, {"CreatePalette", NULL, 5},
    {"CreateSurface", dd_CreateSurface, 4}, {"DuplicateSurface", NULL, 3},
    {"EnumDisplayModes", dd_EnumDisplayModes, 5}, {"EnumSurfaces", NULL, 5}, {"FlipToGDISurface", dd_ok1, 1},
    {"GetCaps", dd_GetCaps, 3}, {"GetDisplayMode", dd_GetDisplayMode, 2}, {"GetFourCCCodes", NULL, 3},
    {"GetGDISurface", NULL, 2}, {"GetMonitorFrequency", dd_GetMonitorFrequency, 2}, {"GetScanLine", NULL, 2},
    {"GetVerticalBlankStatus", NULL, 2}, {"Initialize", NULL, 2}, {"RestoreDisplayMode", dd_RestoreDisplayMode, 1},
    {"SetCooperativeLevel", dd_SetCooperativeLevel, 3}, {"SetDisplayMode", dd_SetDisplayMode, 6},
    {"WaitForVerticalBlank", dd_WaitForVerticalBlank, 3}, {"GetAvailableVidMem", dd_GetAvailableVidMem, 4},
    {"GetSurfaceFromDC", NULL, 3}, {"RestoreAllSurfaces", dd_ok1, 1}, {"TestCooperativeLevel", dd_ok1, 1},
    {"GetDeviceIdentifier", dd_GetDeviceIdentifier, 3}, {"StartModeTest", NULL, 4}, {"EvaluateMode", NULL, 3},
};

/* --------------------------------------------------------------- IDirect3D7 */
H(d3d_QueryInterface) { UNUSED; if (a[2]) st32(a[2], 0); return E_NOINTERFACE; }
H(d3d_AddRef) { UNUSED; uint32_t n = ld32(a[0] + 12) + 1; st32(a[0] + 12, n); return n; }
H(d3d_Release) { UNUSED; uint32_t n = ld32(a[0] + 12); if (n) st32(a[0] + 12, --n); return n; }

/* D3DDEVICEDESC7 of the one device there is. */
static void write_device_desc(uint32_t p) {
    memset(G(p), 0, 0xEC);
    st32(p + 0, 0x00000001u | 0x00000100u | 0x00001000u | 0x00000400u); /* dwDevCaps: FLOATTLVERTEX, texture and
                                                                          TL vertices in system memory, DRAWPRIMTLVERTEX */
    for (uint32_t prim = p + 4; prim <= p + 4 + 56; prim += 56) { /* dpcLineCaps, dpcTriCaps */
        st32(prim + 0, 56);
        st32(prim + 4, 0x00000002u | 0x00000010u | 0x00000020u | 0x00000040u); /* misc: MASKZ, CULLNONE/CW/CCW */
        st32(prim + 8, 0x00000001u);   /* raster: DITHER */
        st32(prim + 12, 0x000000FFu);  /* Z compare: all functions */
        st32(prim + 16, 0x00001FFFu);  /* source blend factors */
        st32(prim + 20, 0x00001FFFu);  /* destination blend factors */
        st32(prim + 24, 0x000000FFu);  /* alpha compare */
        st32(prim + 28, 0x00000008u | 0x00000001u); /* shade: gouraud and flat colour */
        st32(prim + 32, 0x00000001u | 0x00000004u | 0x00000002u); /* texture: PERSPECTIVE, ALPHA, POW2 */
        st32(prim + 36, 0x0000003Fu);  /* texture filters: nearest/linear and mip variants */
        st32(prim + 40, 0x000000FFu);  /* texture blend */
        st32(prim + 44, 0x0000001Fu);  /* texture address modes */
    }
    st32(p + 0x74, 0x00000400u | 0x00000200u); /* dwDeviceRenderBitDepth: DDBD_16 | DDBD_24 */
    st32(p + 0x78, 0x00000400u);               /* dwDeviceZBufferBitDepth: DDBD_16 */
    st32(p + 0x7C, 1);                         /* dwMinTextureWidth */
    st32(p + 0x80, 1);
    st32(p + 0x84, 1024);                      /* dwMaxTextureWidth */
    st32(p + 0x88, 1024);
    st32(p + 0x8C, 1024);                      /* dwMaxTextureRepeat */
    st32(p + 0x90, 1024);                      /* dwMaxTextureAspectRatio */
    st32(p + 0x94, 1);                         /* dwMaxAnisotropy */
    st32(p + 0xB0, 2);                         /* dwFVFCaps: two texture coordinate sets */
    st32(p + 0xB4, 0x000000FFu);               /* dwTextureOpCaps: disable .. modulate4x, add */
    st16(p + 0xB8, 2);                         /* wMaxTextureBlendStages */
    st16(p + 0xBA, 2);                         /* wMaxSimultaneousTextures */
    stf32(p + 0xC0, 1.0e10);                   /* dvMaxVertexW */
    memcpy(G(p + 0xC4), IID_IDirect3DHALDevice, 16); /* deviceGUID */
}

/* EnumDevices(this, callback(desc, name, D3DDEVICEDESC7 *, context), context) */
H(d3d_EnumDevices) {
    uint32_t sp = ESP;
    uint32_t desc = rt_stack_alloc(c, 0xEC + 96);
    uint32_t s1 = desc + 0xEC, s2 = s1 + 64;
    write_device_desc(desc);
    strcpy((char *)G(s1), "GunBound recompilation software device");
    strcpy((char *)G(s2), "Direct3D HAL");
    uint32_t args[4] = {s1, s2, desc, a[2]}, r = 0;
    if (!rt_call_guest(c, a[1], RT_STDCALL, 4, args, &r)) return 0;
    ESP = sp;
    return DD_OK;
}

/* CreateDevice(this, classId, renderTarget, &device) */
H(d3d_CreateDevice) {
    UNUSED;
    char buf[40];
    Surface *rt = surf_of(a[2]);
    if (!rt || !a[3]) return DDERR_INVALIDPARAMS;
    if (!rt_guid_eq(a[1], IID_IDirect3DHALDevice) && !rt_guid_eq(a[1], IID_IDirect3DTnLHalDevice) &&
        !rt_guid_eq(a[1], IID_IDirect3DRGBDevice))
        rt_log("recomp: IDirect3D7::CreateDevice: unknown device class %s; creating the software device anyway\n",
               rt_guid_str(a[1], buf));
    else if (g_opt.verbose)
        rt_log("[d3d] CreateDevice(%s) on surface %x\n", rt_guid_str(a[1], buf), a[2]);
    memset(&dev, 0, sizeof dev);
    dev.render_target = (int)(rt - surfaces);
    /* Direct3D 7 defaults for the state the rasteriser reads. */
    dev.render_state[7] = rt->zbuf >= 0; /* ZENABLE: on only if a depth buffer is attached at creation */
    dev.render_state[14] = 1;  /* ZWRITEENABLE */
    dev.render_state[9] = 2;   /* SHADEMODE: Gouraud */
    dev.render_state[19] = 2;  /* SRCBLEND: ONE */
    dev.render_state[20] = 1;  /* DESTBLEND: ZERO */
    dev.render_state[22] = 3;  /* CULLMODE: counter-clockwise */
    dev.render_state[23] = 4;  /* ZFUNC: LESSEQUAL */
    dev.render_state[25] = 8;  /* ALPHAFUNC: ALWAYS */
    dev.render_state[60] = 0xFFFFFFFFu; /* TEXTUREFACTOR */
    for (int stage = 0; stage < 8; stage++) {
        uint32_t *t = dev.stage_state[stage];
        t[1] = stage ? 1 : 4; /* COLOROP: MODULATE on stage 0, DISABLE elsewhere */
        t[2] = 2;             /* COLORARG1: TEXTURE */
        t[3] = 1;             /* COLORARG2: CURRENT */
        t[4] = stage ? 1 : 2; /* ALPHAOP: SELECTARG1 on stage 0 */
        t[5] = 2;
        t[6] = 1;
        t[12] = t[13] = t[14] = 1; /* ADDRESS: WRAP */
        t[16] = t[17] = 1;         /* MAG/MINFILTER: POINT */
    }
    uint32_t o = rt_com_object(vt_device, 0, MAGIC_DEVICE);
    st32(o + 12, 1);
    st32(a[3], o);
    return DD_OK;
}

/* EnumZBufferFormats(this, deviceClass, callback(DDPIXELFORMAT *, context), context) */
H(d3d_EnumZBufferFormats) {
    uint32_t sp = ESP;
    uint32_t pf = rt_stack_alloc(c, 32);
    write_pixfmt(pf, &fmt_z16);
    st32(pf + 16, 0);      /* dwStencilBitDepth */
    st32(pf + 20, 0xFFFF); /* dwZBitMask */
    uint32_t args[2] = {pf, a[3]}, r = 0;
    if (!rt_call_guest(c, a[2], RT_STDCALL, 2, args, &r)) return 0;
    ESP = sp;
    return DD_OK;
}

H(d3d_EvictManagedTextures) { UNUSED; return DD_OK; }

static const ComMethod d3d_methods[] = {
    {"QueryInterface", d3d_QueryInterface, 3}, {"AddRef", d3d_AddRef, 1}, {"Release", d3d_Release, 1},
    {"EnumDevices", d3d_EnumDevices, 3}, {"CreateDevice", d3d_CreateDevice, 4}, {"CreateVertexBuffer", NULL, 4},
    {"EnumZBufferFormats", d3d_EnumZBufferFormats, 4}, {"EvictManagedTextures", d3d_EvictManagedTextures, 1},
};

/* --------------------------------------------------------- IDirect3DDevice7 */
H(dev_QueryInterface) { UNUSED; if (a[2]) st32(a[2], 0); return E_NOINTERFACE; }
H(dev_AddRef) { UNUSED; uint32_t n = ld32(a[0] + 12) + 1; st32(a[0] + 12, n); return n; }
H(dev_Release) {
    UNUSED;
    if (rt_com_index(a[0], MAGIC_DEVICE) < 0) return 0;
    uint32_t n = ld32(a[0] + 12) - 1;
    st32(a[0] + 12, n);
    if (n == 0) rt_com_free(a[0]);
    return n;
}

H(dev_GetCaps) {
    UNUSED;
    if (!a[1]) return DDERR_INVALIDPARAMS;
    write_device_desc(a[1]);
    return DD_OK;
}

/* EnumTextureFormats(this, callback(DDPIXELFORMAT *, context), context) */
H(dev_EnumTextureFormats) {
    static const PixFmt *const fmts[] = {&fmt_565, &fmt_1555, &fmt_4444};
    uint32_t sp = ESP;
    uint32_t pf = rt_stack_alloc(c, 32);
    for (size_t i = 0; i < RT_COUNTOF(fmts); i++) {
        write_pixfmt(pf, fmts[i]);
        uint32_t args[2] = {pf, a[2]}, r = 0;
        if (!rt_call_guest(c, a[1], RT_STDCALL, 2, args, &r)) return 0;
        if (!r) break;
    }
    ESP = sp;
    return DD_OK;
}

H(dev_BeginScene) { UNUSED; dev.in_scene = 1; return DD_OK; }
H(dev_EndScene) { UNUSED; dev.in_scene = 0; return DD_OK; }

H(dev_GetDirect3D) {
    UNUSED;
    if (!a[1] || !d3d_obj) return DDERR_INVALIDPARAMS;
    st32(d3d_obj + 12, ld32(d3d_obj + 12) + 1);
    st32(a[1], d3d_obj);
    return DD_OK;
}

H(dev_SetRenderTarget) {
    UNUSED;
    Surface *s = surf_of(a[1]);
    if (!s) return DDERR_INVALIDPARAMS;
    dev.render_target = (int)(s - surfaces);
    return DD_OK;
}

H(dev_GetRenderTarget) {
    UNUSED;
    if (!a[1] || dev.render_target < 0) return DDERR_INVALIDPARAMS;
    surfaces[dev.render_target].refs++;
    st32(a[1], surfaces[dev.render_target].obj);
    return DD_OK;
}

static uint32_t color_to_surface(const Surface *s, uint32_t argb) {
    uint32_t r = (argb >> 16) & 0xFF, g = (argb >> 8) & 0xFF, b = argb & 0xFF;
    if (s->pf.bits != 16) return argb;
    if (s->pf.gmask == 0x03E0) return ((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3);
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

/* Clear(this, count, rects, flags, colour, z, stencil) */
H(dev_Clear) {
    UNUSED;
    if (dev.render_target < 0) return DDERR_INVALIDPARAMS;
    Surface *s = &surfaces[dev.render_target];
    Surface *zs = s->zbuf >= 0 ? &surfaces[s->zbuf] : NULL;
    float zf;
    memcpy(&zf, &a[5], 4);
    uint32_t color = color_to_surface(s, a[4]);
    uint32_t zv = zf <= 0.0f ? 0 : zf >= 1.0f ? 65535 : (uint32_t)(zf * 65535.0f + 0.5f);
    uint32_t n = a[1] && a[2] ? a[1] : 1;
    for (uint32_t i = 0; i < n; i++) {
        Rect whole = {0, 0, s->w, s->h};
        Rect r = a[1] && a[2] ? rect_of(a[2] + 16 * i, s) : whole;
        if (a[3] & 1) fill(s, r, color);                              /* D3DCLEAR_TARGET */
        if ((a[3] & 2) && zs && zs->pf.bits == 16) fill(zs, r, zv);   /* D3DCLEAR_ZBUFFER */
    }
    return DD_OK;
}

H(dev_SetViewport) {
    UNUSED;
    if (!a[1]) return DDERR_INVALIDPARAMS;
    for (int i = 0; i < 6; i++) dev.viewport[i] = ld32(a[1] + 4 * (uint32_t)i);
    return DD_OK;
}

H(dev_GetViewport) {
    UNUSED;
    if (!a[1]) return DDERR_INVALIDPARAMS;
    for (int i = 0; i < 6; i++) st32(a[1] + 4 * (uint32_t)i, dev.viewport[i]);
    return DD_OK;
}

H(dev_SetRenderState) {
    UNUSED;
    if (a[1] < 256) dev.render_state[a[1]] = a[2];
    return DD_OK;
}

H(dev_GetRenderState) {
    UNUSED;
    if (!a[2]) return DDERR_INVALIDPARAMS;
    st32(a[2], a[1] < 256 ? dev.render_state[a[1]] : 0);
    return DD_OK;
}

H(dev_SetTexture) {
    UNUSED;
    if (a[1] < 8) dev.texture[a[1]] = a[2];
    return DD_OK;
}

H(dev_SetTextureStageState) {
    UNUSED;
    if (a[1] < 8 && a[2] < 32) {
        dev.stage_state[a[1]][a[2]] = a[3];
        if (a[2] == 12) dev.stage_state[a[1]][13] = dev.stage_state[a[1]][14] = a[3]; /* ADDRESS sets U and V */
    }
    return DD_OK;
}

H(dev_GetTextureStageState) {
    UNUSED;
    if (!a[3]) return DDERR_INVALIDPARAMS;
    st32(a[3], a[1] < 8 && a[2] < 32 ? dev.stage_state[a[1]][a[2]] : 0);
    return DD_OK;
}

/* Report something unsupported once per distinct message. */
static void unsupported(const char *what, uint32_t value) {
    static struct { const char *what; uint32_t value; } seen[64];
    static unsigned nseen;
    pthread_mutex_lock(&dd_mu);
    for (unsigned i = 0; i < nseen; i++) {
        if (!strcmp(seen[i].what, what) && seen[i].value == value) {
            pthread_mutex_unlock(&dd_mu);
            return;
        }
    }
    if (nseen < RT_COUNTOF(seen)) {
        seen[nseen].what = what;
        seen[nseen].value = value;
        nseen++;
    }
    pthread_mutex_unlock(&dd_mu);
    rt_log("recomp: Direct3D: %s (%#x) is not implemented; the output will differ from the original\n", what, value);
}

static void raster_surface(RasterSurface *r, const Surface *s) {
    r->pixels = G(s->pixels);
    r->w = s->w;
    r->h = s->h;
    r->pitch = s->pitch;
    r->bits = (int)s->pf.bits;
    r->rmask = s->pf.rmask;
    r->gmask = s->pf.gmask;
    r->bmask = s->pf.bmask;
    r->amask = (s->pf.flags & DDPF_ALPHAPIXELS) ? s->pf.amask : 0;
}

/* Common part of DrawPrimitive and DrawIndexedPrimitive. indices == 0: sequential. */
static uint32_t draw(uint32_t type, uint32_t fvf, uint32_t verts, uint32_t nverts, uint32_t indices, uint32_t count) {
    if (dev.render_target < 0) return DDERR_INVALIDPARAMS;
    if ((fvf & 0x00E) != 0x004) { /* position must be D3DFVF_XYZRHW */
        unsupported("vertex format without pre-transformed positions", fvf);
        return DD_OK;
    }
    if (type < 4 || type > 6) {
        unsupported("point and line primitives, primitive type", type);
        return DD_OK;
    }
    uint32_t stride = 16, off_diffuse = 0, off_tex = 0, ntex = (fvf >> 8) & 0xF;
    if (fvf & 0x010) stride += 12; /* normal */
    if (fvf & 0x040) { off_diffuse = stride; stride += 4; }
    if (fvf & 0x080) stride += 4;  /* specular: not used */
    if (ntex) off_tex = stride;
    stride += 8 * ntex;

    const uint32_t *rs = dev.render_state;
    const uint32_t *ts = dev.stage_state[0];
    RasterState st;
    memset(&st, 0, sizeof st);
    st.blend_enable = rs[27] != 0;
    st.src_blend = rs[19];
    st.dst_blend = rs[20];
    st.alpha_test = rs[15] != 0;
    st.alpha_ref = rs[24];
    st.alpha_func = rs[25];
    st.cull = rs[22];
    st.flat = rs[9] == 1;
    st.texture_factor = rs[60];
    st.color_op = ts[1];
    st.color_arg1 = ts[2];
    st.color_arg2 = ts[3];
    st.alpha_op = ts[4];
    st.alpha_arg1 = ts[5];
    st.alpha_arg2 = ts[6];
    st.address_u = ts[13];
    st.address_v = ts[14];
    st.bilinear = ts[16] > 1;
    st.z_enable = rs[7] != 0;
    st.z_write = rs[14] != 0;
    st.z_func = rs[23];
    if (dev.stage_state[1][1] > 1 && dev.texture[1]) unsupported("a second texture stage, colour operation", dev.stage_state[1][1]);

    RasterSurface target, texture, depth, *tex = NULL, *zb = NULL;
    raster_surface(&target, &surfaces[dev.render_target]);
    if (surfaces[dev.render_target].zbuf >= 0) {
        raster_surface(&depth, &surfaces[surfaces[dev.render_target].zbuf]);
        zb = &depth;
    }
    Surface *ts0 = dev.texture[0] ? surf_of(dev.texture[0]) : NULL;
    if (ts0 && ntex) {
        raster_surface(&texture, ts0);
        tex = &texture;
        st.colorkey_enable = rs[41] && ts0->has_ckey;
        st.colorkey = ts0->ckey;
    }

    uint32_t ntri = type == 4 ? count / 3 : count >= 3 ? count - 2 : 0;
    for (uint32_t t = 0; t < ntri; t++) {
        uint32_t idx[3];
        if (type == 4) {
            idx[0] = 3 * t; idx[1] = 3 * t + 1; idx[2] = 3 * t + 2;
        } else if (type == 5) { /* strip: every other triangle is wound the other way */
            idx[0] = t; idx[1] = (t & 1) ? t + 2 : t + 1; idx[2] = (t & 1) ? t + 1 : t + 2;
        } else {
            idx[0] = t + 1; idx[1] = t + 2; idx[2] = 0; /* fan: Direct3D takes the flat colour from the first of these */
        }
        RasterVertex v[3];
        for (int k = 0; k < 3; k++) {
            uint32_t i = indices ? ld16(indices + 2 * idx[k]) : idx[k];
            if (i >= nverts) return DDERR_INVALIDPARAMS;
            uint32_t p = verts + i * stride;
            memcpy(&v[k].x, G(p), 4);
            memcpy(&v[k].y, G(p + 4), 4);
            memcpy(&v[k].z, G(p + 8), 4);
            v[k].diffuse = off_diffuse ? ld32(p + off_diffuse) : 0xFFFFFFFFu;
            v[k].u = v[k].v = 0;
            if (ntex) {
                memcpy(&v[k].u, G(p + off_tex), 4);
                memcpy(&v[k].v, G(p + off_tex + 4), 4);
            }
        }
        const char *why = NULL;
        if (!rt_raster_triangle(&target, zb, tex, &st, v, &why)) unsupported(why, (ts[1] << 16) | (rs[19] << 8) | rs[20]);
    }
    return DD_OK;
}

/* DrawPrimitive(this, type, fvf, vertices, count, flags) */
H(dev_DrawPrimitive) {
    UNUSED;
    return draw(a[1], a[2], a[3], a[4], 0, a[4]);
}

/* DrawIndexedPrimitive(this, type, fvf, vertices, vertexCount, indices, indexCount, flags) */
H(dev_DrawIndexedPrimitive) {
    UNUSED;
    return draw(a[1], a[2], a[3], a[4], a[5], a[6]);
}

H(dev_GetTexture) {
    UNUSED;
    if (!a[2] || a[1] >= 8) return DDERR_INVALIDPARAMS;
    Surface *s = dev.texture[a[1]] ? surf_of(dev.texture[a[1]]) : NULL;
    if (s) s->refs++;
    st32(a[2], s ? s->obj : 0);
    return DD_OK;
}

static const ComMethod device_methods[] = {
    {"QueryInterface", dev_QueryInterface, 3}, {"AddRef", dev_AddRef, 1}, {"Release", dev_Release, 1},
    {"GetCaps", dev_GetCaps, 2}, {"EnumTextureFormats", dev_EnumTextureFormats, 3},
    {"BeginScene", dev_BeginScene, 1}, {"EndScene", dev_EndScene, 1}, {"GetDirect3D", dev_GetDirect3D, 2},
    {"SetRenderTarget", dev_SetRenderTarget, 3}, {"GetRenderTarget", dev_GetRenderTarget, 2},
    {"Clear", dev_Clear, 7}, {"SetTransform", NULL, 3}, {"GetTransform", NULL, 3},
    {"SetViewport", dev_SetViewport, 2}, {"MultiplyTransform", NULL, 3}, {"GetViewport", dev_GetViewport, 2},
    {"SetMaterial", NULL, 2}, {"GetMaterial", NULL, 2}, {"SetLight", NULL, 3}, {"GetLight", NULL, 3},
    {"SetRenderState", dev_SetRenderState, 3}, {"GetRenderState", dev_GetRenderState, 3},
    {"BeginStateBlock", NULL, 1}, {"EndStateBlock", NULL, 2}, {"PreLoad", NULL, 2},
    {"DrawPrimitive", dev_DrawPrimitive, 6}, {"DrawIndexedPrimitive", dev_DrawIndexedPrimitive, 8},
    {"SetClipStatus", NULL, 2},
    {"GetClipStatus", NULL, 2}, {"DrawPrimitiveStrided", NULL, 6}, {"DrawIndexedPrimitiveStrided", NULL, 8},
    {"DrawPrimitiveVB", NULL, 6}, {"DrawIndexedPrimitiveVB", NULL, 8}, {"ComputeSphereVisibility", NULL, 6},
    {"GetTexture", dev_GetTexture, 3}, {"SetTexture", dev_SetTexture, 3},
    {"GetTextureStageState", dev_GetTextureStageState, 4}, {"SetTextureStageState", dev_SetTextureStageState, 4},
    {"ValidateDevice", NULL, 2}, {"ApplyStateBlock", NULL, 2}, {"CaptureStateBlock", NULL, 2},
    {"DeleteStateBlock", NULL, 2}, {"CreateStateBlock", NULL, 3}, {"Load", NULL, 6}, {"LightEnable", NULL, 3},
    {"GetLightEnable", NULL, 3}, {"SetClipPlane", NULL, 3}, {"GetClipPlane", NULL, 3}, {"GetInfo", NULL, 4},
};

/* ------------------------------------------------------------------ exports */
static pthread_once_t dd_once = PTHREAD_ONCE_INIT;

static void dd_init(void) {
    vt_ddraw = rt_com_vtable("ddraw.dll", "IDirectDraw7", ddraw_methods, RT_COUNTOF(ddraw_methods));
    vt_surface = rt_com_vtable("ddraw.dll", "IDirectDrawSurface7", surface_methods, RT_COUNTOF(surface_methods));
    vt_clipper = rt_com_vtable("ddraw.dll", "IDirectDrawClipper", clipper_methods, RT_COUNTOF(clipper_methods));
    vt_d3d = rt_com_vtable("ddraw.dll", "IDirect3D7", d3d_methods, RT_COUNTOF(d3d_methods));
    vt_device = rt_com_vtable("ddraw.dll", "IDirect3DDevice7", device_methods, RT_COUNTOF(device_methods));
    dev.render_target = -1;
}

/* DirectDrawCreateEx(guid, &ddraw, iid, outer) */
H(dd_DirectDrawCreateEx) {
    UNUSED;
    char buf[40];
    pthread_once(&dd_once, dd_init);
    if (!a[1]) return DDERR_INVALIDPARAMS;
    if (!rt_guid_eq(a[2], IID_IDirectDraw7)) {
        rt_log("recomp: DirectDrawCreateEx: interface %s is not supported\n", rt_guid_str(a[2], buf));
        st32(a[1], 0);
        return DDERR_INVALIDPARAMS;
    }
    if (!ddraw_obj) ddraw_obj = rt_com_object(vt_ddraw, 0, MAGIC_DDRAW);
    st32(ddraw_obj + 12, ld32(ddraw_obj + 12) + 1);
    st32(a[1], ddraw_obj);
    return DD_OK;
}

static const ImportDef defs[] = {
    {"ddraw.dll", "DirectDrawCreateEx", dd_DirectDrawCreateEx, 4, 0},
};
RT_EXPORT_IMPORTS(rt_imports_ddraw, defs);
