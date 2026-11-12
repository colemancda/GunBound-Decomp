/* Test list and vector driver shared by the native 32-bit reference (ref_main.c)
 * and the lifted harness (lifted_main.c). Freestanding: no libc is used here.
 *
 * The includer provides:
 *   void put_str(const char *s);
 *   void test_call(int index, u32 a, u32 b, u32 c, u32 d, u32 out[8]);
 */
#ifndef RECOMP_TESTS_H
#define RECOMP_TESTS_H

typedef unsigned int u32;
typedef unsigned long long u64;

/* status flags the lifter models: CF PF AF ZF SF OF */
#define F_CF 0x001u
#define F_AF 0x010u
#define F_OF 0x800u
#define F_ALL 0x8D5u
#define F_BASE 0x202u /* reserved bit 1 and IF, as a user-mode process sees them */

enum Kind {
    K_ARITH2, /* (a, b, flags-in) -> out[0] value, out[1] flags (all defined) */
    K_LOGIC2, /* same, AF undefined */
    K_ARITH1, /* (a, -, flags-in) */
    K_NOFLAG1, /* (a, -, flags-in): flags must come out unchanged */
    K_SHIFT,  /* (a, count, flags-in); p1 = width, p2 = class */
    K_SHIFT1, /* (a, -, flags-in); p2 = class */
    K_PAIR,   /* (a, b) over the value list, no flag slots */
    K_CUSTOM  /* vectors and fix-up supplied by a function */
};
enum { SH_LOGICAL, SH_ARITH, SH_ROT, SH_RC };

/* name, kind, p1, p2 */
#define TESTS(T) \
    T(t_add32, K_ARITH2, 0, 0) T(t_adc32, K_ARITH2, 0, 0) T(t_sub32, K_ARITH2, 0, 0) T(t_sbb32, K_ARITH2, 0, 0) \
    T(t_cmp32, K_ARITH2, 0, 0) T(t_and32, K_LOGIC2, 0, 0) T(t_or32, K_LOGIC2, 0, 0) T(t_xor32, K_LOGIC2, 0, 0) \
    T(t_test32, K_LOGIC2, 0, 0) T(t_add16, K_ARITH2, 0, 0) T(t_adc16, K_ARITH2, 0, 0) T(t_sub16, K_ARITH2, 0, 0) \
    T(t_sbb16, K_ARITH2, 0, 0) T(t_cmp16, K_ARITH2, 0, 0) T(t_and16, K_LOGIC2, 0, 0) T(t_add8, K_ARITH2, 0, 0) \
    T(t_adc8, K_ARITH2, 0, 0) T(t_sub8, K_ARITH2, 0, 0) T(t_sbb8, K_ARITH2, 0, 0) T(t_cmp8, K_ARITH2, 0, 0) \
    T(t_xor8, K_LOGIC2, 0, 0) T(t_addm32, K_ARITH2, 0, 0) T(t_adcm32, K_ARITH2, 0, 0) T(t_sbbm16, K_ARITH2, 0, 0) \
    T(t_subm8, K_ARITH2, 0, 0) T(t_xorm8h, K_LOGIC2, 0, 0) \
    T(t_inc32, K_ARITH1, 0, 0) T(t_dec32, K_ARITH1, 0, 0) T(t_neg32, K_ARITH1, 0, 0) T(t_not32, K_NOFLAG1, 0, 0) \
    T(t_inc16, K_ARITH1, 0, 0) T(t_dec16, K_ARITH1, 0, 0) T(t_neg16, K_ARITH1, 0, 0) T(t_inc8, K_ARITH1, 0, 0) \
    T(t_dec8, K_ARITH1, 0, 0) T(t_neg8, K_ARITH1, 0, 0) T(t_inc8h, K_ARITH1, 0, 0) T(t_not8h, K_NOFLAG1, 0, 0) \
    T(t_shl32, K_SHIFT, 32, SH_LOGICAL) T(t_shr32, K_SHIFT, 32, SH_LOGICAL) T(t_sar32, K_SHIFT, 32, SH_ARITH) \
    T(t_rol32, K_SHIFT, 32, SH_ROT) T(t_ror32, K_SHIFT, 32, SH_ROT) T(t_rcl32, K_SHIFT, 32, SH_RC) \
    T(t_rcr32, K_SHIFT, 32, SH_RC) T(t_shl16, K_SHIFT, 16, SH_LOGICAL) T(t_shr16, K_SHIFT, 16, SH_LOGICAL) \
    T(t_sar16, K_SHIFT, 16, SH_ARITH) T(t_rol16, K_SHIFT, 16, SH_ROT) T(t_ror16, K_SHIFT, 16, SH_ROT) \
    T(t_rcl16, K_SHIFT, 16, SH_RC) T(t_rcr16, K_SHIFT, 16, SH_RC) T(t_shl8, K_SHIFT, 8, SH_LOGICAL) \
    T(t_shr8, K_SHIFT, 8, SH_LOGICAL) T(t_sar8, K_SHIFT, 8, SH_ARITH) T(t_rol8, K_SHIFT, 8, SH_ROT) \
    T(t_ror8, K_SHIFT, 8, SH_ROT) T(t_rcl8, K_SHIFT, 8, SH_RC) T(t_rcr8, K_SHIFT, 8, SH_RC) \
    T(t_shl32_1, K_SHIFT1, 0, SH_LOGICAL) T(t_shr32_1, K_SHIFT1, 0, SH_LOGICAL) T(t_sar32_1, K_SHIFT1, 0, SH_ARITH) \
    T(t_rol32_1, K_SHIFT1, 0, SH_ROT) T(t_ror32_1, K_SHIFT1, 0, SH_ROT) T(t_rcl32_1, K_SHIFT1, 0, SH_RC) \
    T(t_rcr32_1, K_SHIFT1, 0, SH_RC) T(t_shl8_1, K_SHIFT1, 0, SH_LOGICAL) T(t_sar16_1, K_SHIFT1, 0, SH_ARITH) \
    T(t_ror8_1, K_SHIFT1, 0, SH_ROT) T(t_rcr16_1, K_SHIFT1, 0, SH_RC) \
    T(t_shift_imm, K_CUSTOM, 0, 0) T(t_shld32, K_CUSTOM, 0, 0) \
    T(t_mul32, K_CUSTOM, 0, 0) T(t_mul16, K_CUSTOM, 0, 0) T(t_mul8, K_CUSTOM, 0, 0) T(t_imul3, K_CUSTOM, 0, 0) \
    T(t_div32, K_CUSTOM, 0, 0) T(t_idiv32, K_CUSTOM, 0, 0) T(t_cdq_idiv, K_CUSTOM, 0, 0) T(t_div16, K_CUSTOM, 0, 0) \
    T(t_idiv16, K_CUSTOM, 0, 0) T(t_div8, K_CUSTOM, 0, 0) T(t_idiv8, K_CUSTOM, 0, 0) \
    T(t_setcc_cmp, K_PAIR, 0, 0) T(t_setcc_flags, K_CUSTOM, 0, 0) T(t_jcc_flags, K_CUSTOM, 0, 0) \
    T(t_lahf_sahf, K_CUSTOM, 0, 0) \
    T(t_rep_movsb, K_CUSTOM, 0, 0) T(t_rep_movsd, K_CUSTOM, 0, 0) T(t_rep_stos, K_CUSTOM, 0, 0) \
    T(t_strlen, K_CUSTOM, 0, 0) T(t_scas_bounded, K_CUSTOM, 0, 0) T(t_memcmp, K_CUSTOM, 0, 0) \
    T(t_extend, K_PAIR, 0, 0) T(t_bits, K_CUSTOM, 0, 0) T(t_xadd_cmpxchg, K_CUSTOM, 0, 0) \
    T(t_wide_arith, K_CUSTOM, 0, 0) T(t_stack, K_PAIR, 0, 0) T(t_calls, K_PAIR, 0, 0) \
    T(t_nonlocal, K_CUSTOM, 0, 0) \
    T(t_switch, K_CUSTOM, 0, 0) T(t_switch2, K_CUSTOM, 0, 0) T(t_loops, K_CUSTOM, 0, 0) \
    T(t_fist, K_CUSTOM, 0, 0) T(t_farith_mem, K_CUSTOM, 0, 0) T(t_farith_memr, K_CUSTOM, 0, 0) \
    T(t_farith_pop, K_CUSTOM, 0, 0) T(t_farith_st0, K_CUSTOM, 0, 0) T(t_farith_sti, K_CUSTOM, 0, 0) \
    T(t_fmisc, K_CUSTOM, 0, 0) T(t_fcom, K_CUSTOM, 0, 0) T(t_fprem, K_CUSTOM, 0, 0) T(t_fscale, K_CUSTOM, 0, 0) \
    T(t_fint, K_CUSTOM, 0, 0)

enum TestIndex {
#define T(name, kind, p1, p2) IX_##name,
    TESTS(T)
#undef T
    N_TESTS
};

typedef struct TestDesc {
    const char *name;
    int kind, p1, p2;
} TestDesc;

static const TestDesc test_descs[N_TESTS] = {
#define T(name, kind, p1, p2) {#name, kind, p1, p2},
    TESTS(T)
#undef T
};

void put_str(const char *s);
void test_call(int index, u32 a, u32 b, u32 c, u32 d, u32 out[8]);

/* ------------------------------------------------------------- vectors */
static const u32 VALS[] = {
    0, 1, 2, 3, 0x7f, 0x80, 0x81, 0xff, 0x100, 0x7fff, 0x8000, 0xffff, 0x10000, 0x7fffffff, 0x80000000u,
    0x80000001u, 0xffffffffu, 0xfffffffeu, 0x12345678, 0xdeadbeefu, 0x0f0f0f0f, 0xaaaa5555u,
};
#define NVALS (sizeof VALS / sizeof VALS[0])
static const u32 FLAGS_IN[] = {F_BASE, F_BASE | F_CF, F_BASE | F_ALL};
static const u32 COUNTS[] = {0, 1, 2, 3, 4, 7, 8, 9, 15, 16, 17, 24, 31, 32, 33, 63, 255};
#define NCOUNTS (sizeof COUNTS / sizeof COUNTS[0])

typedef union { double d; u32 w[2]; } DBits;
static const double DVALS[] = {
    0.0, -0.0, 0.5, -0.5, 1.5, -1.5, 2.5, -2.5, 3.5, 0.49999999999999994, 1.0, -1.0, 3.0, 7.25, -7.75,
    1e10, -1e10, 2147483647.5, -2147483648.5, 2147483648.0, 32767.5, -32768.5, 65536.0, 1e19, -1e19,
    123456789.123, 1e-10, 0.1, __builtin_inf(), -__builtin_inf(), __builtin_nan(""),
};
#define NDVALS (sizeof DVALS / sizeof DVALS[0])
static const double PVALS[] = {1.0, 3.0, 5.5, -7.25, 10.0, 100.5, 1000000.5, -1000000.0, 0.3, 123456789.123};
#define NPVALS (sizeof PVALS / sizeof PVALS[0])

/* ---------------------------------------------------------- reporting */
static u32 t_hash, t_count;
static int t_verbose;

static void put_hex(u32 v) {
    char b[9];
    for (int i = 0; i < 8; i++) {
        u32 n = (v >> (28 - 4 * i)) & 15;
        b[i] = (char)(n < 10 ? '0' + n : 'a' + n - 10);
    }
    b[8] = 0;
    put_str(b);
}
static void put_dec(u32 v) {
    char b[12];
    int i = 11;
    b[i] = 0;
    do { b[--i] = (char)('0' + v % 10); v /= 10; } while (v);
    put_str(b + i);
}
static void mix(u32 v) {
    for (int i = 0; i < 4; i++) {
        t_hash ^= (v >> (8 * i)) & 0xff;
        t_hash *= 16777619u;
    }
}

/* Replace any NaN stored as a double at out[i], out[i+1] by one canonical NaN:
 * the sign and payload of a generated NaN are host-specific. */
static void canon_nan(u32 *out, int i) {
    if ((out[i + 1] & 0x7ff00000u) == 0x7ff00000u && ((out[i + 1] & 0xfffffu) | out[i])) {
        out[i] = 0;
        out[i + 1] = 0x7ff80000u;
    }
}

static u32 shift_mask(const TestDesc *t, u32 count) {
    u32 n = count & 31;
    if (n == 0) return F_ALL; /* nothing may change */
    u32 m;
    if (t->p2 == SH_ROT || t->p2 == SH_RC) {
        m = F_ALL & ~F_OF; /* only CF and OF change; the rest must be preserved */
    } else {
        m = F_ALL & ~F_OF & ~F_AF;
        if (t->p2 == SH_LOGICAL && n >= (u32)t->p1) m &= ~F_CF; /* undefined when count >= width */
    }
    if (n == 1) m |= F_OF;
    return m;
}

static void one(int ix, u32 a, u32 b, u32 c, u32 d, u32 m1) {
    const TestDesc *t = &test_descs[ix];
    u32 out[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    test_call(ix, a, b, c, d, out);
    switch (t->kind) {
    case K_ARITH2: case K_ARITH1: case K_NOFLAG1: out[1] &= F_ALL; break;
    case K_LOGIC2: out[1] &= F_ALL & ~F_AF; break;
    case K_SHIFT: out[1] &= shift_mask(t, b); break;
    case K_SHIFT1: out[1] &= (t->p2 == SH_ROT || t->p2 == SH_RC) ? F_ALL : (F_ALL & ~F_AF); break;
    default: break;
    }
    switch (ix) {
    case IX_t_shift_imm: out[6] &= 0xC5; out[7] &= 0xC5; break;
    case IX_t_shld32: out[1] &= m1; out[3] &= m1; break;
    case IX_t_mul32: case IX_t_mul16: out[2] &= 0x801; out[5] &= 0x801; out[7] &= 0x801; break;
    case IX_t_mul8: out[1] &= 0x801; out[3] &= 0x801; break;
    case IX_t_imul3: out[1] &= 0x801; out[3] &= 0x801; out[6] &= 0x801; break;
    case IX_t_lahf_sahf: for (int i = 1; i < 6; i++) out[i] &= F_ALL; break;
    case IX_t_strlen: case IX_t_scas_bounded: case IX_t_memcmp: out[7] &= F_ALL; break;
    case IX_t_xadd_cmpxchg: out[2] &= F_ALL; out[5] &= F_ALL; break;
    case IX_t_fist: canon_nan(out, 4); out[7] &= 0xffff; break;
    case IX_t_farith_mem: case IX_t_farith_pop: case IX_t_farith_st0: case IX_t_farith_sti:
        canon_nan(out, 0); canon_nan(out, 2); canon_nan(out, 4); canon_nan(out, 6); break;
    case IX_t_farith_memr: canon_nan(out, 0); canon_nan(out, 2); canon_nan(out, 6); break;
    case IX_t_fmisc: canon_nan(out, 0); canon_nan(out, 2); canon_nan(out, 5); break;
    case IX_t_fcom: out[0] &= 0x4500; out[3] &= 0x4500; out[4] &= 0x4500; out[5] &= 0x4700; break;
    case IX_t_fprem: canon_nan(out, 0); canon_nan(out, 2); out[6] &= 0x4700; out[7] &= 0x4700; break;
    case IX_t_fscale: canon_nan(out, 0); break;
    case IX_t_fint: canon_nan(out, 0); canon_nan(out, 2); out[5] &= 0x4500; break;
    default: break;
    }
    mix(a); mix(b); mix(c); mix(d);
    for (int i = 0; i < 8; i++) mix(out[i]);
    t_count++;
    if (t_verbose) {
        put_str(t->name);
        put_str(" ");
        put_hex(a); put_str(" "); put_hex(b); put_str(" "); put_hex(c); put_str(" "); put_hex(d);
        put_str(" ->");
        for (int i = 0; i < 8; i++) { put_str(" "); put_hex(out[i]); }
        put_str("\n");
    }
}

static u32 flag_pattern(u32 i) { /* 6 bits -> CF PF AF ZF SF OF */
    return F_BASE | (i & 1) | ((i & 2) << 1) | ((i & 4) << 2) | ((i & 8) << 3) | ((i & 16) << 3) | ((i & 32) << 6);
}

static double dabs(double x) { return x < 0 ? -x : x; }

static void custom(int ix) {
    DBits x, y;
    switch (ix) {
    case IX_t_shift_imm:
        for (u32 i = 0; i < NVALS; i++) one(ix, VALS[i], 0, 0, 0, 0);
        break;
    case IX_t_shld32:
        for (u32 i = 0; i < NVALS; i++)
            for (u32 j = 0; j < NVALS; j += 3)
                for (u32 k = 0; k < NCOUNTS; k++) {
                    u32 n = COUNTS[k] & 31;
                    u32 m = n == 0 ? F_ALL : (0xC5u | (n == 1 ? F_OF : 0));
                    one(ix, VALS[i], VALS[j], COUNTS[k], 0, m);
                }
        break;
    case IX_t_mul32: case IX_t_mul16: case IX_t_mul8:
        for (u32 i = 0; i < NVALS; i++)
            for (u32 j = 0; j < NVALS; j++) one(ix, VALS[i], VALS[j], 0, 0, 0);
        break;
    case IX_t_imul3: case IX_t_switch:
        for (u32 i = 0; i < NVALS; i++) one(ix, VALS[i], 0, 0, 0, 0);
        for (u32 i = 4; i < 9; i++) one(ix, i, 0, 0, 0, 0);
        break;
    case IX_t_switch2: case IX_t_loops:
        for (u32 i = 0; i < 42; i++) one(ix, i, 0, 0, 0, 0);
        one(ix, 0xffffffffu, 0, 0, 0, 0);
        break;
    case IX_t_div32: /* unsigned b:a / c is defined when b < c */
        for (u32 i = 0; i < NVALS; i++)
            for (u32 j = 0; j < NVALS; j++)
                for (u32 k = 0; k < NVALS; k++)
                    if (VALS[j] < VALS[k]) one(ix, VALS[i], VALS[j], VALS[k], 0, 0);
        break;
    case IX_t_idiv32: /* sign-extended dividends always fit, plus a few wide ones */
        for (u32 i = 0; i < NVALS; i++)
            for (u32 k = 0; k < NVALS; k++) {
                u32 a = VALS[i], c = VALS[k];
                if (c == 0 || (a == 0x80000000u && c == 0xffffffffu)) continue;
                one(ix, a, (a & 0x80000000u) ? 0xffffffffu : 0, c, 0, 0);
            }
        one(ix, 0, 1, 4, 0, 0);
        one(ix, 0, 0xfffffffeu, 4, 0, 0);
        one(ix, 0x12345678, 0x1234, 0x7fffffff, 0, 0);
        one(ix, 0x9abcdef0u, 0xffffff00u, 0x80000000u, 0, 0);
        one(ix, 5, 3, 0xfffffff9u, 0, 0);
        break;
    case IX_t_cdq_idiv:
        for (u32 i = 0; i < NVALS; i++)
            for (u32 k = 0; k < NVALS; k++) {
                u32 a = VALS[i], c = VALS[k];
                if (c == 0 || (a == 0x80000000u && c == 0xffffffffu)) continue;
                one(ix, a, c, 0, 0, 0);
            }
        break;
    case IX_t_div16: /* dx:ax = a; defined when (a >> 16) < (c & 0xffff) */
        for (u32 i = 0; i < NVALS; i++)
            for (u32 k = 0; k < NVALS; k++)
                if ((VALS[i] >> 16) < (VALS[k] & 0xffff)) one(ix, VALS[i], 0, VALS[k], 0, 0);
        break;
    case IX_t_idiv16: /* dividends that are sign-extended 16-bit values */
        for (u32 i = 0; i < NVALS; i++)
            for (u32 k = 0; k < NVALS; k++) {
                u32 lo = VALS[i] & 0xffff, c = VALS[k] & 0xffff;
                u32 a = (lo & 0x8000) ? (0xffff0000u | lo) : lo;
                if (c == 0 || (lo == 0x8000 && c == 0xffff)) continue;
                one(ix, a, 0, VALS[k], 0, 0);
            }
        one(ix, 0x00010000, 0, 4, 0, 0);
        one(ix, 0xfffe0000u, 0, 4, 0, 0);
        break;
    case IX_t_div8: /* ax = a; defined when ah < divisor */
        for (u32 i = 0; i < NVALS; i++)
            for (u32 k = 0; k < NVALS; k++)
                if (((VALS[i] >> 8) & 0xff) < (VALS[k] & 0xff)) one(ix, VALS[i], 0, VALS[k], 0, 0);
        break;
    case IX_t_idiv8:
        for (u32 i = 0; i < NVALS; i++)
            for (u32 k = 0; k < NVALS; k++) {
                u32 lo = VALS[i] & 0xff, c = VALS[k] & 0xff;
                u32 a = (VALS[i] & 0xffff0000u) | ((lo & 0x80) ? (0xff00u | lo) : lo);
                if (c == 0 || (lo == 0x80 && c == 0xff)) continue;
                one(ix, a, 0, VALS[k], 0, 0);
            }
        break;
    case IX_t_setcc_flags: case IX_t_jcc_flags:
        for (u32 i = 0; i < 64; i++) one(ix, 0, 0, flag_pattern(i), 0, 0);
        break;
    case IX_t_lahf_sahf: {
        static const u32 ah[] = {0x00, 0x01, 0x04, 0x10, 0x40, 0x80, 0xD5, 0xFF, 0x2A};
        for (u32 i = 0; i < sizeof ah / sizeof ah[0]; i++)
            for (u32 j = 0; j < 64; j += 7) one(ix, ah[i] << 8, 0, flag_pattern(j), 0, 0);
        break;
    }
    case IX_t_rep_movsb:
        for (u32 n = 0; n <= 16; n++)
            for (u32 dir = 0; dir < 2; dir++) {
                one(ix, 0x04030201, 0x08070605, n, dir, 0);
                one(ix, 0x11223344, 0xAABBCCDDu, n, dir, 0);
            }
        break;
    case IX_t_rep_movsd:
        for (u32 n = 0; n <= 4; n++)
            for (u32 dir = 0; dir < 2; dir++) {
                one(ix, 0x04030201, 0x08070605, n, dir, 0);
                one(ix, 0x11223344, 0xAABBCCDDu, n, dir, 0);
            }
        break;
    case IX_t_rep_stos:
        for (u32 n = 0; n <= 4; n++) {
            one(ix, 0x04030201, 0x08070605, n, 0, 0);
            one(ix, 0xA1B2C3D4u, 0x11223344, n, 0, 0);
        }
        break;
    case IX_t_strlen: {
        static const u32 sa[] = {0x64636261, 0x00636261, 0x61000000, 0, 0x01010101};
        static const u32 sb[] = {0x68676665, 0x00000065, 0};
        for (u32 i = 0; i < 5; i++)
            for (u32 j = 0; j < 3; j++) one(ix, sa[i], sb[j], 0, 0, 0);
        break;
    }
    case IX_t_scas_bounded: {
        static const u32 cnt[] = {0, 1, 3, 8, 20};
        static const u32 ch[] = {0x61, 0x65, 0x00, 0xFF, 0x9A, 0x9E};
        for (u32 i = 0; i < 5; i++)
            for (u32 j = 0; j < 6; j++) one(ix, 0x64636261, 0x68676665, cnt[i], ch[j], 0);
        break;
    }
    case IX_t_memcmp: {
        static const u32 mv[] = {0x64636261, 0x64636361, 0xE4636261u, 0};
        for (u32 i = 0; i < 256; i++) one(ix, mv[i & 3], mv[(i >> 2) & 3], mv[(i >> 4) & 3], mv[(i >> 6) & 3], 0);
        break;
    }
    case IX_t_bits:
        for (u32 i = 0; i < NVALS; i++)
            for (u32 n = 0; n < 64; n += (n < 8 ? 1 : 5)) one(ix, VALS[i], n, 0, 0, 0);
        break;
    case IX_t_xadd_cmpxchg:
        for (u32 i = 0; i < NVALS; i++)
            for (u32 j = 0; j < NVALS; j++) {
                one(ix, VALS[i], VALS[j], VALS[i], 0, 0);
                one(ix, VALS[i], VALS[j], VALS[j] + 1, 0, 0);
            }
        break;
    case IX_t_nonlocal:
        for (u32 i = 0; i < NVALS; i += 3)
            for (u32 n = 0; n < 8; n++)
                for (u32 m = 0; m < 8; m++) one(ix, VALS[i], n | (m << 4), 0, 0, 0);
        break;
    case IX_t_wide_arith:
        for (u32 i = 0; i < NVALS; i += 2)
            for (u32 j = 1; j < NVALS; j += 3)
                for (u32 k = 0; k < NVALS; k += 2)
                    for (u32 l = 2; l < NVALS; l += 3) one(ix, VALS[i], VALS[j], VALS[k], VALS[l], 0);
        break;
    case IX_t_fist: {
        static const u32 cw[] = {0x27F, 0x67F, 0xA7F, 0xE7F};
        for (u32 i = 0; i < NDVALS; i++)
            for (u32 j = 0; j < 4; j++) {
                x.d = DVALS[i];
                one(ix, x.w[0], x.w[1], cw[j], 0, 0);
            }
        break;
    }
    case IX_t_farith_mem: case IX_t_farith_memr: case IX_t_farith_pop: case IX_t_farith_st0:
    case IX_t_farith_sti: case IX_t_fmisc: case IX_t_fcom:
        for (u32 i = 0; i < NDVALS; i++)
            for (u32 j = 0; j < NDVALS; j++) {
                x.d = DVALS[i];
                y.d = DVALS[j];
                one(ix, x.w[0], x.w[1], y.w[0], y.w[1], 0);
            }
        break;
    case IX_t_fprem:
        for (u32 i = 0; i < NPVALS; i++)
            for (u32 j = 0; j < NPVALS; j++) {
                x.d = PVALS[i];
                y.d = PVALS[j];
                if (dabs(x.d) > dabs(y.d) * 1e15) continue; /* x87 would need several reduction steps */
                one(ix, x.w[0], x.w[1], y.w[0], y.w[1], 0);
            }
        break;
    case IX_t_fscale: {
        static const u32 sc[] = {0, 1, 0xffffffffu, 10, 0xfffffff6u, 100, 0xffffff9cu};
        for (u32 i = 0; i < NPVALS; i++)
            for (u32 j = 0; j < 7; j++) {
                x.d = PVALS[i];
                one(ix, x.w[0], x.w[1], sc[j], 0, 0);
            }
        break;
    }
    case IX_t_fint: {
        /* (b:a) as int64 stays below 2^53 so that a double holds it exactly */
        static const u32 hi[] = {0, 1, 0xffffffffu, 0x000fffff};
        static const u32 dv[] = {1, 3, 0xfffffffdu, 1000, 0x7fffffff};
        for (u32 i = 0; i < NVALS; i++)
            for (u32 j = 0; j < 4; j++)
                for (u32 k = 0; k < 5; k++) one(ix, VALS[i], hi[j], dv[k], 0, 0);
        break;
    }
    default:
        break;
    }
}

/* Runs every test; prints one summary line per test (or every vector when verbose). */
static void run_tests(int verbose) {
    t_verbose = verbose;
    for (int ix = 0; ix < N_TESTS; ix++) {
        const TestDesc *t = &test_descs[ix];
        t_hash = 2166136261u;
        t_count = 0;
        switch (t->kind) {
        case K_ARITH2: case K_LOGIC2:
            for (u32 i = 0; i < NVALS; i++)
                for (u32 j = 0; j < NVALS; j++)
                    for (u32 k = 0; k < 3; k++) one(ix, VALS[i], VALS[j], FLAGS_IN[k], 0, 0);
            break;
        case K_ARITH1: case K_NOFLAG1: case K_SHIFT1:
            for (u32 i = 0; i < NVALS; i++)
                for (u32 k = 0; k < 3; k++) one(ix, VALS[i], 0, FLAGS_IN[k], 0, 0);
            break;
        case K_SHIFT:
            for (u32 i = 0; i < NVALS; i++)
                for (u32 j = 0; j < NCOUNTS; j++)
                    for (u32 k = 0; k < 3; k++) one(ix, VALS[i], COUNTS[j], FLAGS_IN[k], 0, 0);
            break;
        case K_PAIR:
            for (u32 i = 0; i < NVALS; i++)
                for (u32 j = 0; j < NVALS; j++) one(ix, VALS[i], VALS[j], 0, 0, 0);
            break;
        default:
            custom(ix);
            break;
        }
        if (!verbose) {
            put_str(t->name);
            put_str(" vectors=");
            put_dec(t_count);
            put_str(" hash=");
            put_hex(t_hash);
            put_str("\n");
        }
    }
}

#endif
