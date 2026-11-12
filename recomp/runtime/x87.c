/* Out-of-line x87 helpers and the few CPU-identification instructions. */
#define _GNU_SOURCE
#include <time.h>

#include "rt.h"

/* 80-bit extended <-> double. Values outside double range saturate to infinity;
 * precision beyond 53 bits is lost (the guest CRT runs the FPU in 53-bit mode). */
double rt_ld80(uint32_t a) {
    uint64_t mant = ld64(a);
    uint16_t se = ld16(a + 8);
    int sign = se >> 15;
    int exp = se & 0x7FFF;
    double v;
    if (exp == 0x7FFF) v = (mant << 1) ? NAN : INFINITY;
    else if (mant == 0) v = 0.0;
    else v = ldexp((double)mant, exp - 16383 - 63);
    return sign ? -v : v;
}

void rt_st80(uint32_t a, double v) {
    uint64_t mant;
    uint16_t se = signbit(v) ? 0x8000 : 0;
    if (isnan(v)) {
        mant = 0xC000000000000000ull;
        se |= 0x7FFF;
    } else if (isinf(v)) {
        mant = 0x8000000000000000ull;
        se |= 0x7FFF;
    } else if (v == 0.0) {
        mant = 0;
    } else {
        int e;
        double f = frexp(fabs(v), &e); /* f in [0.5, 1) */
        mant = (uint64_t)ldexp(f, 64);
        se |= (uint16_t)(e - 1 + 16383);
    }
    st64(a, mant);
    st16(a + 8, se);
}

static uint16_t full_tag_word(const CPU *c) {
    uint16_t tw = 0;
    for (int i = 0; i < 8; i++) {
        unsigned tag;
        if (!(c->ftag & (1u << i))) tag = 3;
        else if (c->st[i] == 0.0) tag = 1;
        else if (isnan(c->st[i]) || isinf(c->st[i])) tag = 2;
        else tag = 0;
        tw |= (uint16_t)(tag << (2 * i));
    }
    return tw;
}

void rt_fnstenv(CPU *c, uint32_t a) {
    st32(a, 0xFFFF0000u | c->fcw);
    st32(a + 4, 0xFFFF0000u | rt_fnstsw(c));
    st32(a + 8, 0xFFFF0000u | full_tag_word(c));
    st32(a + 12, 0);
    st32(a + 16, 0);
    st32(a + 20, 0);
    st32(a + 24, 0xFFFF0000u);
    c->fcw |= 0x3F; /* fnstenv masks all exceptions */
}

void rt_fldenv(CPU *c, uint32_t a) {
    c->fcw = ld16(a);
    uint16_t sw = ld16(a + 4);
    c->ftop = (sw >> 11) & 7;
    c->fsw = sw & ~0x3800;
    uint16_t tw = ld16(a + 8);
    c->ftag = 0;
    for (int i = 0; i < 8; i++)
        if (((tw >> (2 * i)) & 3) != 3) c->ftag |= (uint8_t)(1u << i);
}

void rt_fnsave(CPU *c, uint32_t a) {
    rt_fnstenv(c, a);
    for (int i = 0; i < 8; i++) rt_st80(a + 28 + 10 * (uint32_t)i, ST(i));
    c->fcw = 0x37F;
    c->fsw = 0;
    c->ftop = 0;
    c->ftag = 0;
}

void rt_frstor(CPU *c, uint32_t a) {
    rt_fldenv(c, a);
    for (int i = 0; i < 8; i++) ST(i) = rt_ld80(a + 28 + 10 * (uint32_t)i);
}

/* fprem (truncating) / fprem1 (round to nearest): always completes in one step. */
void rt_fprem(CPU *c, int ieee) {
    double a = ST(0), b = ST(1), r;
    unsigned q = 0;
    if (ieee) {
        int quo = 0;
        r = remquo(a, b, &quo);
        q = (unsigned)(quo < 0 ? -quo : quo);
    } else {
        r = fmod(a, b);
        if (isfinite(a) && isfinite(b) && b != 0.0) q = (unsigned)trunc(fmod(fabs(a), 8.0 * fabs(b)) / fabs(b));
    }
    c->fsw &= (uint16_t)~FSW_CC;
    if (q & 4) c->fsw |= FSW_C0;
    if (q & 2) c->fsw |= FSW_C3;
    if (q & 1) c->fsw |= FSW_C1;
    ST(0) = r;
}

void rt_fxam(CPU *c) {
    double v = ST(0);
    uint16_t cc;
    if (!(c->ftag & (1u << c->ftop))) cc = FSW_C3 | FSW_C0;        /* empty */
    else if (isnan(v)) cc = FSW_C0;
    else if (isinf(v)) cc = FSW_C2 | FSW_C0;
    else if (v == 0.0) cc = FSW_C3;
    else if (fpclassify(v) == FP_SUBNORMAL) cc = FSW_C3 | FSW_C2;
    else cc = FSW_C2;                                             /* normal */
    if (signbit(v)) cc |= FSW_C1;
    c->fsw = (uint16_t)((c->fsw & ~FSW_CC) | cc);
}

void rt_fxtract(CPU *c) {
    double v = ST(0);
    if (v == 0.0) {
        ST(0) = -INFINITY;
        fpush(c, v);
    } else if (!isfinite(v)) {
        ST(0) = isinf(v) ? INFINITY : v;
        fpush(c, v);
    } else {
        int e;
        double f = frexp(v, &e); /* v = f * 2^e, |f| in [0.5, 1) */
        ST(0) = (double)(e - 1);
        fpush(c, f * 2.0);
    }
}

/* Report a plain Pentium Pro class CPU: FPU, TSC, CX8, CMOV. No MMX/SSE/SSE2, so the
 * guest CRT stays on its x87 paths (the SSE2 math routines are not lifted). */
void rt_cpuid(CPU *c) {
    switch (EAX) {
    case 0:
        EAX = 1;
        EBX = 0x756E6547; /* "Genu" */
        EDX = 0x49656E69; /* "ineI" */
        ECX = 0x6C65746E; /* "ntel" */
        break;
    case 1:
        EAX = 0x00000619;
        EBX = 0;
        ECX = 0;
        EDX = (1u << 0) | (1u << 4) | (1u << 8) | (1u << 15);
        break;
    default:
        EAX = EBX = ECX = EDX = 0;
        break;
    }
}

void rt_rdtsc(CPU *c) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    uint64_t t = ((uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec) * 2; /* pretend 2 GHz */
    EAX = (uint32_t)t;
    EDX = (uint32_t)(t >> 32);
}
