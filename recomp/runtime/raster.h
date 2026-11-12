/* Software rasteriser for Direct3D 7 primitives made of screen-space (XYZRHW) vertices. */
#ifndef RECOMP_RASTER_H
#define RECOMP_RASTER_H

#include <stdint.h>

typedef struct RasterSurface {
    uint8_t *pixels;
    int w, h, pitch, bits;
    uint32_t rmask, gmask, bmask, amask;
} RasterSurface;

typedef struct RasterVertex {
    float x, y, z;
    uint32_t diffuse; /* ARGB */
    float u, v;
} RasterVertex;

/* The Direct3D state that affects a pixel; values are the D3D constants. */
typedef struct RasterState {
    int blend_enable;
    uint32_t src_blend, dst_blend;       /* D3DBLEND_* */
    int alpha_test;
    uint32_t alpha_ref, alpha_func;      /* D3DCMP_* */
    uint32_t color_op, color_arg1, color_arg2; /* stage 0, D3DTOP_* and D3DTA_* */
    uint32_t alpha_op, alpha_arg1, alpha_arg2;
    uint32_t texture_factor;
    int bilinear;
    uint32_t address_u, address_v;       /* D3DTADDRESS_* */
    uint32_t cull;                       /* D3DCULL_* */
    int flat;                            /* flat shading: the first vertex's colour */
    int colorkey_enable;
    uint32_t colorkey;                   /* raw texel value */
    int z_enable, z_write;
    uint32_t z_func;                     /* D3DCMP_* */
} RasterState;

/* Draws one triangle. tex and zbuf may be NULL; zbuf is a 16-bit depth surface of
 * the target's size. Returns 0 if some part of the state is not supported (*why
 * names it); the triangle is still drawn with the nearest behaviour. */
int rt_raster_triangle(const RasterSurface *dst, const RasterSurface *zbuf, const RasterSurface *tex,
                       const RasterState *st, const RasterVertex v[3], const char **why);

#endif
