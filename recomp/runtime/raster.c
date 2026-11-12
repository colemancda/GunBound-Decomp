/* Software rasteriser (see raster.h).
 *
 * Follows the Direct3D 7 rules that decide which pixels a triangle touches and
 * what a texture lookup returns: pixel centres are at integer coordinates, the
 * top-left fill rule decides shared edges, and texel (i, j) covers
 * [i, i+1) x [j, j+1) of the texture, so bilinear filtering samples at
 * u * width - 0.5. Coverage is computed in 28.4 fixed point. Colour and texture
 * coordinates are interpolated without perspective correction: the vertices are
 * already in screen space and the game draws flat sprites.
 *
 * The target is a 16-bit surface; the depth buffer, when there is one, holds
 * 16-bit values. There is no fog and no specular colour.
 */
#include <math.h>
#include <string.h>

#include "raster.h"

typedef struct Chan {
    int shift, bits;
} Chan;

static Chan chan_of(uint32_t mask) {
    Chan c = {0, 0};
    if (!mask) return c;
    while (!((mask >> c.shift) & 1)) c.shift++;
    while ((mask >> (c.shift + c.bits)) & 1) c.bits++;
    return c;
}

static inline int expand(uint32_t raw, Chan c) {
    if (!c.bits) return 255;
    uint32_t v = (raw >> c.shift) & ((1u << c.bits) - 1);
    if (c.bits >= 8) return (int)(v >> (c.bits - 8));
    v <<= 8 - c.bits;
    return (int)(v | (v >> c.bits) | (c.bits < 4 ? v >> (2 * c.bits) : 0));
}

typedef struct Tex {
    const RasterSurface *s;
    Chan r, g, b, a;
    int bpp;
} Tex;

static inline uint32_t tex_raw(const Tex *t, int x, int y) {
    const uint8_t *p = t->s->pixels + (size_t)y * (size_t)t->s->pitch + (size_t)x * (size_t)t->bpp;
    switch (t->bpp) {
    case 1: return *p;
    case 2: { uint16_t v; memcpy(&v, p, 2); return v; }
    case 3: return p[0] | (p[1] << 8) | ((uint32_t)p[2] << 16);
    default: { uint32_t v; memcpy(&v, p, 4); return v; }
    }
}

static inline int wrap_coord(int i, int n, uint32_t mode) {
    switch (mode) {
    case 3: /* D3DTADDRESS_CLAMP */
    case 4: /* BORDER: treated as clamp */
        return i < 0 ? 0 : i >= n ? n - 1 : i;
    case 2: { /* MIRROR */
        int m = i % (2 * n);
        if (m < 0) m += 2 * n;
        return m < n ? m : 2 * n - 1 - m;
    }
    default: { /* WRAP */
        int m = i % n;
        return m < 0 ? m + n : m;
    }
    }
}

/* Texel as {r, g, b, a} in 0..255. A colour-keyed texel has alpha 0 and *keyed set. */
static inline void texel(const Tex *t, const RasterState *st, int x, int y, int out[4], int *keyed) {
    x = wrap_coord(x, t->s->w, st->address_u);
    y = wrap_coord(y, t->s->h, st->address_v);
    uint32_t raw = tex_raw(t, x, y);
    out[0] = expand(raw, t->r);
    out[1] = expand(raw, t->g);
    out[2] = expand(raw, t->b);
    out[3] = expand(raw, t->a);
    if (st->colorkey_enable && raw == st->colorkey) {
        out[3] = 0;
        *keyed = 1;
    }
}

static void sample(const Tex *t, const RasterState *st, float u, float v, int out[4], int *keyed) {
    float fx = u * (float)t->s->w, fy = v * (float)t->s->h;
    if (!st->bilinear) {
        texel(t, st, (int)floorf(fx), (int)floorf(fy), out, keyed);
        return;
    }
    fx -= 0.5f;
    fy -= 0.5f;
    int x0 = (int)floorf(fx), y0 = (int)floorf(fy);
    int wx = (int)((fx - (float)x0) * 256.0f), wy = (int)((fy - (float)y0) * 256.0f);
    int c00[4], c10[4], c01[4], c11[4], k = 0;
    texel(t, st, x0, y0, c00, &k);
    if (wx == 0 && wy == 0) { /* exactly on a texel centre: the common 1:1 sprite case */
        memcpy(out, c00, sizeof c00);
        *keyed |= k;
        return;
    }
    texel(t, st, x0 + 1, y0, c10, &k);
    texel(t, st, x0, y0 + 1, c01, &k);
    texel(t, st, x0 + 1, y0 + 1, c11, &k);
    for (int i = 0; i < 4; i++) {
        int top = c00[i] * (256 - wx) + c10[i] * wx;
        int bot = c01[i] * (256 - wx) + c11[i] * wx;
        out[i] = (top * (256 - wy) + bot * wy + 32768) >> 16;
    }
    if (k && out[3] == 0) *keyed = 1;
}

/* One argument of a texture stage operation, as {r, g, b, a}. */
static inline void stage_arg(uint32_t arg, const int tex[4], const int dif[4], uint32_t factor, int out[4]) {
    switch (arg & 0xF) {
    case 2: memcpy(out, tex, 4 * sizeof(int)); break; /* D3DTA_TEXTURE */
    case 3: /* D3DTA_TFACTOR */
        out[0] = (factor >> 16) & 255;
        out[1] = (factor >> 8) & 255;
        out[2] = factor & 255;
        out[3] = factor >> 24;
        break;
    default: memcpy(out, dif, 4 * sizeof(int)); break; /* DIFFUSE, CURRENT (stage 0), SPECULAR */
    }
    if (arg & 0x10) /* D3DTA_COMPLEMENT */
        for (int i = 0; i < 4; i++) out[i] = 255 - out[i];
    if (arg & 0x20) /* D3DTA_ALPHAREPLICATE */
        out[0] = out[1] = out[2] = out[3];
}

static inline int clamp255(int v) { return v < 0 ? 0 : v > 255 ? 255 : v; }

static inline int stage_op(uint32_t op, int a, int b, int *ok) {
    switch (op) {
    case 2: return a;                             /* SELECTARG1 */
    case 3: return b;                             /* SELECTARG2 */
    case 4: return (a * b + 127) / 255;           /* MODULATE */
    case 5: return clamp255((a * b * 2 + 127) / 255); /* MODULATE2X */
    case 6: return clamp255((a * b * 4 + 127) / 255); /* MODULATE4X */
    case 7: return clamp255(a + b);               /* ADD */
    case 8: return clamp255(a + b - 128);         /* ADDSIGNED */
    case 10: return clamp255(a - b);              /* SUBTRACT */
    case 11: return clamp255(a + b - (a * b + 127) / 255); /* ADDSMOOTH */
    default:
        *ok = 0;
        return a;
    }
}

static inline void blend_factor(uint32_t f, const int src[4], const int dst[3], int out[3], int *ok) {
    switch (f) {
    case 1: out[0] = out[1] = out[2] = 0; break;                   /* ZERO */
    case 2: out[0] = out[1] = out[2] = 255; break;                 /* ONE */
    case 3: out[0] = src[0]; out[1] = src[1]; out[2] = src[2]; break; /* SRCCOLOR */
    case 4: out[0] = 255 - src[0]; out[1] = 255 - src[1]; out[2] = 255 - src[2]; break;
    case 5: out[0] = out[1] = out[2] = src[3]; break;              /* SRCALPHA */
    case 6: out[0] = out[1] = out[2] = 255 - src[3]; break;        /* INVSRCALPHA */
    case 7: out[0] = out[1] = out[2] = 255; break;                 /* DESTALPHA: the target has none */
    case 8: out[0] = out[1] = out[2] = 0; break;                   /* INVDESTALPHA */
    case 9: out[0] = dst[0]; out[1] = dst[1]; out[2] = dst[2]; break; /* DESTCOLOR */
    case 10: out[0] = 255 - dst[0]; out[1] = 255 - dst[1]; out[2] = 255 - dst[2]; break;
    default:
        *ok = 0;
        out[0] = out[1] = out[2] = 255;
        break;
    }
}

static inline int compare(uint32_t func, int a, int ref) {
    switch (func) {
    case 1: return 0;        /* NEVER */
    case 2: return a < ref;
    case 3: return a == ref;
    case 4: return a <= ref;
    case 5: return a > ref;
    case 6: return a != ref;
    case 7: return a >= ref;
    default: return 1;       /* ALWAYS */
    }
}

int rt_raster_triangle(const RasterSurface *dst, const RasterSurface *zbuf, const RasterSurface *texs,
                       const RasterState *st, const RasterVertex vin[3], const char **why) {
    int ok = 1;
    if (dst->bits != 16) {
        *why = "render target is not 16-bit";
        return 0;
    }
    RasterVertex v[3] = {vin[0], vin[1], vin[2]};
    int64_t X[3], Y[3];
    for (int i = 0; i < 3; i++) {
        if (!isfinite(v[i].x) || !isfinite(v[i].y) || fabsf(v[i].x) > 1.0e6f || fabsf(v[i].y) > 1.0e6f) return 1;
        X[i] = (int64_t)lrintf(v[i].x * 16.0f);
        Y[i] = (int64_t)lrintf(v[i].y * 16.0f);
    }
    /* Positive for a triangle that is clockwise on the screen (y grows downwards). */
    int64_t area = (X[1] - X[0]) * (Y[2] - Y[0]) - (X[2] - X[0]) * (Y[1] - Y[0]);
    if (area == 0) return 1;
    if ((st->cull == 2 && area > 0) || (st->cull == 3 && area < 0)) return 1; /* D3DCULL_CW / CCW */
    if (area < 0) { /* make it clockwise; the weights follow the vertices */
        RasterVertex tv = v[1];
        v[1] = v[2];
        v[2] = tv;
        int64_t t = X[1]; X[1] = X[2]; X[2] = t;
        t = Y[1]; Y[1] = Y[2]; Y[2] = t;
        area = -area;
    }
    int64_t minx = X[0], maxx = X[0], miny = Y[0], maxy = Y[0];
    for (int i = 1; i < 3; i++) {
        if (X[i] < minx) minx = X[i];
        if (X[i] > maxx) maxx = X[i];
        if (Y[i] < miny) miny = Y[i];
        if (Y[i] > maxy) maxy = Y[i];
    }
    int x0 = (int)((minx + 15) >> 4), x1 = (int)(maxx >> 4), y0 = (int)((miny + 15) >> 4), y1 = (int)(maxy >> 4);
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 >= dst->w) x1 = dst->w - 1;
    if (y1 >= dst->h) y1 = dst->h - 1;
    if (x0 > x1 || y0 > y1) return 1;

    /* Edge i runs from vertex i to vertex i+1 and carries the weight of vertex i+2. */
    int64_t ex[3], ey[3], bias[3];
    for (int i = 0; i < 3; i++) {
        int j = (i + 1) % 3;
        ex[i] = X[j] - X[i];
        ey[i] = Y[j] - Y[i];
        int top_left = ey[i] < 0 || (ey[i] == 0 && ex[i] > 0);
        bias[i] = top_left ? 0 : -1;
    }

    Tex tex;
    memset(&tex, 0, sizeof tex);
    int use_tex = texs != NULL && texs->pixels != NULL && st->color_op != 1;
    if (use_tex) {
        tex.s = texs;
        tex.r = chan_of(texs->rmask);
        tex.g = chan_of(texs->gmask);
        tex.b = chan_of(texs->bmask);
        tex.a = chan_of(texs->amask);
        tex.bpp = texs->bits / 8;
    }
    int dif[3][4];
    for (int i = 0; i < 3; i++) {
        uint32_t d = v[i].diffuse;
        dif[i][0] = (d >> 16) & 255;
        dif[i][1] = (d >> 8) & 255;
        dif[i][2] = d & 255;
        dif[i][3] = d >> 24;
    }
    if (st->flat) {
        uint32_t d = vin[0].diffuse;
        for (int i = 0; i < 3; i++) {
            dif[i][0] = (d >> 16) & 255;
            dif[i][1] = (d >> 8) & 255;
            dif[i][2] = d & 255;
            dif[i][3] = d >> 24;
        }
    }
    int same_color = !memcmp(dif[0], dif[1], sizeof dif[0]) && !memcmp(dif[0], dif[2], sizeof dif[0]);
    int is555 = dst->gmask == 0x03E0;
    int use_z = st->z_enable && zbuf && zbuf->pixels && zbuf->bits == 16 && zbuf->w >= dst->w && zbuf->h >= dst->h;
    float inv_area = 1.0f / (float)area;
    static const int white[4] = {255, 255, 255, 255};

    for (int y = y0; y <= y1; y++) {
        uint16_t *row = (uint16_t *)(void *)(dst->pixels + (size_t)y * (size_t)dst->pitch);
        uint16_t *zrow = use_z ? (uint16_t *)(void *)(zbuf->pixels + (size_t)y * (size_t)zbuf->pitch) : NULL;
        int64_t py = (int64_t)y << 4;
        for (int x = x0; x <= x1; x++) {
            int64_t px = (int64_t)x << 4;
            int64_t e0 = ex[0] * (py - Y[0]) - ey[0] * (px - X[0]);
            int64_t e1 = ex[1] * (py - Y[1]) - ey[1] * (px - X[1]);
            int64_t e2 = ex[2] * (py - Y[2]) - ey[2] * (px - X[2]);
            if (e0 + bias[0] < 0 || e1 + bias[1] < 0 || e2 + bias[2] < 0) continue;
            float w2 = (float)e0 * inv_area, w0 = (float)e1 * inv_area, w1 = (float)e2 * inv_area;
            int zi = 0;
            if (use_z) {
                float z = v[0].z * w0 + v[1].z * w1 + v[2].z * w2;
                zi = z <= 0.0f ? 0 : z >= 1.0f ? 65535 : (int)(z * 65535.0f + 0.5f);
                if (!compare(st->z_func, zi, zrow[x])) continue;
            }

            int d[4], t[4], keyed = 0;
            if (same_color) {
                memcpy(d, dif[0], sizeof d);
            } else {
                for (int i = 0; i < 4; i++)
                    d[i] = clamp255((int)((float)dif[0][i] * w0 + (float)dif[1][i] * w1 + (float)dif[2][i] * w2 + 0.5f));
            }
            if (use_tex) {
                float u = v[0].u * w0 + v[1].u * w1 + v[2].u * w2;
                float vv = v[0].v * w0 + v[1].v * w1 + v[2].v * w2;
                sample(&tex, st, u, vv, t, &keyed);
                if (keyed) continue; /* colour-keyed texels are not drawn */
            } else {
                memcpy(t, white, sizeof t);
            }

            int src[4];
            if (st->color_op == 1) { /* stage disabled: the diffuse colour passes through */
                memcpy(src, d, sizeof src);
            } else {
                int a1[4], a2[4];
                stage_arg(st->color_arg1, t, d, st->texture_factor, a1);
                stage_arg(st->color_arg2, t, d, st->texture_factor, a2);
                for (int i = 0; i < 3; i++) src[i] = stage_op(st->color_op, a1[i], a2[i], &ok);
                if (st->alpha_op == 1) {
                    src[3] = d[3];
                } else {
                    stage_arg(st->alpha_arg1, t, d, st->texture_factor, a1);
                    stage_arg(st->alpha_arg2, t, d, st->texture_factor, a2);
                    src[3] = stage_op(st->alpha_op, a1[3], a2[3], &ok);
                }
            }
            if (st->alpha_test && !compare(st->alpha_func, src[3], (int)(st->alpha_ref & 255))) continue;
            if (use_z && st->z_write) zrow[x] = (uint16_t)zi;

            int out[3];
            if (st->blend_enable) {
                uint16_t p = row[x];
                int dc[3], sf[3], df[3];
                if (is555) {
                    dc[0] = (p >> 10) & 31; dc[1] = (p >> 5) & 31; dc[2] = p & 31;
                    dc[0] = (dc[0] << 3) | (dc[0] >> 2);
                    dc[1] = (dc[1] << 3) | (dc[1] >> 2);
                } else {
                    dc[0] = (p >> 11) & 31; dc[1] = (p >> 5) & 63; dc[2] = p & 31;
                    dc[0] = (dc[0] << 3) | (dc[0] >> 2);
                    dc[1] = (dc[1] << 2) | (dc[1] >> 4);
                }
                dc[2] = (dc[2] << 3) | (dc[2] >> 2);
                blend_factor(st->src_blend, src, dc, sf, &ok);
                blend_factor(st->dst_blend, src, dc, df, &ok);
                for (int i = 0; i < 3; i++) out[i] = clamp255((src[i] * sf[i] + dc[i] * df[i] + 127) / 255);
            } else {
                out[0] = src[0];
                out[1] = src[1];
                out[2] = src[2];
            }
            row[x] = is555 ? (uint16_t)(((out[0] >> 3) << 10) | ((out[1] >> 3) << 5) | (out[2] >> 3))
                           : (uint16_t)(((out[0] >> 3) << 11) | ((out[1] >> 2) << 5) | (out[2] >> 3));
        }
    }
    if (!ok) *why = "a texture operation or blend factor that is not implemented";
    return ok;
}
