/* Guest CPU state and the inline helpers the lifted code is written against.
 *
 * Everything the lifter emits is expressed with the names defined here, so the
 * representation (registers in a struct, eager flags, literal guest stack) can be
 * changed later without touching the lifter's instruction semantics.
 */
#ifndef RECOMP_CPU_H
#define RECOMP_CPU_H

#include <math.h>
#include <stdint.h>
#include <string.h>

typedef union Reg {
    uint32_t d;
    uint16_t w;
    struct { uint8_t l, h; } b;
} Reg;

typedef struct CPU {
    Reg r[8];                 /* eax ecx edx ebx esp ebp esi edi */
    uint8_t cf, pf, af, zf, sf, of, df, pad0;
    uint32_t eip;             /* address popped by the most recent guest `ret` */
    uint32_t fs_base;         /* guest address of this thread's TEB */
    uint32_t ftop;            /* x87 top-of-stack, 0..7 */
    uint16_t fcw, fsw;        /* x87 control and status words (fsw without the TOP field) */
    uint8_t ftag;             /* bit i set: physical x87 register i holds a value */
    uint8_t pad1[3];
    double st[8];             /* x87 registers, physical order */
    uint32_t eflags_hi;       /* EFLAGS bits the lifted code does not model (ID, AC, ...) */
    uint32_t thread_id;
    uint32_t ret_sp;          /* guest address of the stack slot the most recent `ret` popped */
    uint32_t nl_eip, nl_slot; /* pending non-local return: target address and the slot it was popped from */
    void *thread;             /* runtime bookkeeping for this guest thread (RtThread) */
} CPU;

#define EAX (c->r[0].d)
#define ECX (c->r[1].d)
#define EDX (c->r[2].d)
#define EBX (c->r[3].d)
#define ESP (c->r[4].d)
#define EBP (c->r[5].d)
#define ESI (c->r[6].d)
#define EDI (c->r[7].d)
#define AX (c->r[0].w)
#define CX (c->r[1].w)
#define DX (c->r[2].w)
#define BX (c->r[3].w)
#define SP (c->r[4].w)
#define BP (c->r[5].w)
#define SI (c->r[6].w)
#define DI (c->r[7].w)
#define AL (c->r[0].b.l)
#define CL (c->r[1].b.l)
#define DL (c->r[2].b.l)
#define BL (c->r[3].b.l)
#define AH (c->r[0].b.h)
#define CH (c->r[1].b.h)
#define DH (c->r[2].b.h)
#define BH (c->r[3].b.h)

/* ------------------------------------------------------------------ memory */
/* Guest address a lives at host address G(a). The mapping sits at a fixed host
 * address by default so that the base is a compile-time constant. */
#ifndef RT_GUEST_BASE
#define RT_GUEST_BASE 0x100000000ULL
#endif
#ifdef RT_DYNAMIC_BASE
extern uint8_t *g_mem;
#define G(a) (g_mem + (uint32_t)(a))
#else
#define G(a) ((uint8_t *)(RT_GUEST_BASE + (uint64_t)(uint32_t)(a)))
#endif

static inline uint8_t ld8(uint32_t a) { return *G(a); }
static inline uint16_t ld16(uint32_t a) { uint16_t v; memcpy(&v, G(a), 2); return v; }
static inline uint32_t ld32(uint32_t a) { uint32_t v; memcpy(&v, G(a), 4); return v; }
static inline uint64_t ld64(uint32_t a) { uint64_t v; memcpy(&v, G(a), 8); return v; }
static inline void st8(uint32_t a, uint8_t v) { *G(a) = v; }
static inline void st16(uint32_t a, uint16_t v) { memcpy(G(a), &v, 2); }
static inline void st32(uint32_t a, uint32_t v) { memcpy(G(a), &v, 4); }
static inline void st64(uint32_t a, uint64_t v) { memcpy(G(a), &v, 8); }
static inline double ldf32(uint32_t a) { float v; memcpy(&v, G(a), 4); return v; }
static inline double ldf64(uint32_t a) { double v; memcpy(&v, G(a), 8); return v; }
static inline void stf32(uint32_t a, double d) { float v = (float)d; memcpy(G(a), &v, 4); }
static inline void stf64(uint32_t a, double d) { memcpy(G(a), &d, 8); }

/* ------------------------------------------------------- runtime interface */
typedef void (*GuestFn)(CPU *);

extern GuestFn *g_ftab;       /* dense table: g_ftab[addr - g_ftab_base] */
extern uint32_t g_ftab_base, g_ftab_size;

void rt_call_slow(CPU *c, uint32_t addr);
void rt_jmp_slow(CPU *c, uint32_t addr, uint32_t from);
int rt_ret_mismatch(CPU *c, uint32_t expected, uint32_t slot);
void rt_unimplemented_insn(CPU *c, uint32_t addr, const char *mnemonic) __attribute__((noreturn));
void rt_bad_code(CPU *c, uint32_t from, uint32_t target) __attribute__((noreturn));
void rt_divide_error(CPU *c, uint32_t addr) __attribute__((noreturn));
void rt_cpuid(CPU *c);
void rt_rdtsc(CPU *c);
double rt_ld80(uint32_t a);
void rt_st80(uint32_t a, double v);
void rt_fnstenv(CPU *c, uint32_t a);
void rt_fldenv(CPU *c, uint32_t a);
void rt_fnsave(CPU *c, uint32_t a);
void rt_frstor(CPU *c, uint32_t a);
void rt_fprem(CPU *c, int ieee);
void rt_fxam(CPU *c);
void rt_fxtract(CPU *c);

/* Indirect guest call/jump: lifted functions are found through the dense table,
 * everything else (imports, unknown code) is handled by the slow path. */
static inline void rt_call(CPU *c, uint32_t a) {
    uint32_t i = a - g_ftab_base;
    if (i < g_ftab_size && g_ftab[i]) g_ftab[i](c);
    else rt_call_slow(c, a);
}
static inline void rt_jmp(CPU *c, uint32_t a, uint32_t from) {
    uint32_t i = a - g_ftab_base;
    if (i < g_ftab_size && g_ftab[i]) g_ftab[i](c);
    else rt_jmp_slow(c, a, from);
}

/* After a guest call returns, the address its `ret` popped must be the one the
 * call pushed. A mismatch is a non-local return: the callee (or something below
 * it) unwound the guest stack, as an SEH handler or a C++ catch does when it
 * resumes in an outer function and that function then returns to *its* caller.
 * Lifted functions keep no state in host locals, so the host stack is unwound by
 * returning from every C frame until the one whose call pushed the address that
 * was finally popped: the frame whose return address and stack slot both match.
 *
 * rt_ret_mismatch() implements the search. The first frame to see a mismatch
 * records the real target in nl_eip/nl_slot and poisons eip with RT_NL_PENDING,
 * which no call site expects, so every outer frame takes the slow path as well.
 * It returns 1 in the frame that should resume and 0 where the frame must
 * return. Matching on the slot keeps a recursive activation of the same call
 * site from claiming a return that belongs to an outer one. */
#define RT_NL_PENDING 0xFFFFFFF1u

#define RT_RETCHECK(ra, slot) \
    do { if (__builtin_expect(c->eip != (ra), 0) && !rt_ret_mismatch(c, (ra), (slot))) return; } while (0)

#define PUSH32(v) do { uint32_t v_ = (v); ESP -= 4; st32(ESP, v_); } while (0)
#define PUSH16(v) do { uint16_t v_ = (uint16_t)(v); ESP -= 2; st16(ESP, v_); } while (0)
#define CALLF(fn, ra) \
    do { uint32_t s_ = ESP - 4; ESP = s_; st32(s_, (ra)); fn(c); RT_RETCHECK(ra, s_); } while (0)
#define CALLI(t, ra) \
    do { uint32_t t_ = (t); uint32_t s_ = ESP - 4; ESP = s_; st32(s_, (ra)); rt_call(c, t_); RT_RETCHECK(ra, s_); } while (0)
#define RET(n) do { uint32_t s_ = ESP; c->ret_sp = s_; c->eip = ld32(s_); ESP = s_ + 4 + (n); return; } while (0)

/* `lock`-prefixed read-modify-write instructions and `xchg` with memory are atomic. */
static inline uint32_t rt_atomic_xadd32(uint32_t a, uint32_t v) {
    return __atomic_fetch_add((uint32_t *)G(a), v, __ATOMIC_SEQ_CST);
}
static inline uint32_t rt_atomic_xchg32(uint32_t a, uint32_t v) {
    return __atomic_exchange_n((uint32_t *)G(a), v, __ATOMIC_SEQ_CST);
}
/* Returns the value found at a; the exchange happened if that equals expect. */
static inline uint32_t rt_atomic_cmpxchg32(uint32_t a, uint32_t expect, uint32_t v) {
    __atomic_compare_exchange_n((uint32_t *)G(a), &expect, v, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    return expect;
}

/* ------------------------------------------------------------------- flags */
static inline uint8_t rt_pf(uint32_t r) { return (uint8_t)!__builtin_parity(r & 0xff); }

static inline uint32_t rt_get_eflags(const CPU *c) {
    return (uint32_t)c->cf | 2u | ((uint32_t)c->pf << 2) | ((uint32_t)c->af << 4) | ((uint32_t)c->zf << 6) |
           ((uint32_t)c->sf << 7) | 0x200u | ((uint32_t)c->df << 10) | ((uint32_t)c->of << 11) | c->eflags_hi;
}
static inline void rt_set_eflags(CPU *c, uint32_t f) {
    c->cf = f & 1; c->pf = (f >> 2) & 1; c->af = (f >> 4) & 1; c->zf = (f >> 6) & 1;
    c->sf = (f >> 7) & 1; c->df = (f >> 10) & 1; c->of = (f >> 11) & 1;
    c->eflags_hi = f & 0x00240000u; /* AC and ID are freely togglable on a CPUID-capable CPU */
}
static inline uint8_t rt_lahf(const CPU *c) {
    return (uint8_t)(c->cf | 2u | (c->pf << 2) | (c->af << 4) | (c->zf << 6) | (c->sf << 7));
}
static inline void rt_sahf(CPU *c, uint8_t f) {
    c->cf = f & 1; c->pf = (f >> 2) & 1; c->af = (f >> 4) & 1; c->zf = (f >> 6) & 1; c->sf = (f >> 7) & 1;
}

/* Rotates through carry and double shifts are rare; they live here rather than inline. */
static inline uint32_t rt_rcl(CPU *c, uint32_t a, uint32_t count, unsigned bits) {
    uint32_t n = (count & 31) % (bits + 1);
    uint32_t msb = 1u << (bits - 1), mask = msb | (msb - 1);
    if ((count & 31) == 0) return a;
    for (uint32_t i = 0; i < n; i++) {
        uint32_t out = (a & msb) != 0;
        a = ((a << 1) | c->cf) & mask;
        c->cf = (uint8_t)out;
    }
    c->of = (uint8_t)(((a & msb) != 0) ^ c->cf);
    return a;
}
static inline uint32_t rt_rcr(CPU *c, uint32_t a, uint32_t count, unsigned bits) {
    uint32_t n = (count & 31) % (bits + 1);
    uint32_t msb = 1u << (bits - 1);
    if ((count & 31) == 0) return a;
    c->of = (uint8_t)(((a & msb) != 0) ^ c->cf); /* defined for count 1: msb of result ^ next bit */
    for (uint32_t i = 0; i < n; i++) {
        uint32_t out = a & 1;
        a = (a >> 1) | (c->cf ? msb : 0);
        c->cf = (uint8_t)out;
    }
    return a;
}
static inline void rt_szp(CPU *c, uint32_t r, unsigned bits) {
    c->zf = r == 0; c->sf = (r >> (bits - 1)) & 1; c->pf = rt_pf(r);
}
static inline uint32_t rt_shld(CPU *c, uint32_t a, uint32_t b, uint32_t count, unsigned bits) {
    uint32_t n = count & 31;
    if (n == 0) return a;
    if (n > bits) return a; /* undefined for 16-bit operands; leave unchanged */
    uint32_t mask = bits == 32 ? 0xffffffffu : (1u << bits) - 1;
    uint64_t t = (((uint64_t)a << bits) | b) << n;
    uint32_t r = (uint32_t)(t >> bits) & mask;
    c->cf = (uint8_t)((a >> (bits - n)) & 1);
    c->of = (uint8_t)(((a ^ r) >> (bits - 1)) & 1);
    c->af = 0;
    rt_szp(c, r, bits);
    return r;
}
static inline uint32_t rt_shrd(CPU *c, uint32_t a, uint32_t b, uint32_t count, unsigned bits) {
    uint32_t n = count & 31;
    if (n == 0) return a;
    if (n > bits) return a;
    uint32_t mask = bits == 32 ? 0xffffffffu : (1u << bits) - 1;
    uint64_t t = (((uint64_t)b << bits) | a) >> n;
    uint32_t r = (uint32_t)t & mask;
    c->cf = (uint8_t)((a >> (n - 1)) & 1);
    c->of = (uint8_t)(((a ^ r) >> (bits - 1)) & 1);
    c->af = 0;
    rt_szp(c, r, bits);
    return r;
}

/* ------------------------------------------------------- multiply / divide */
static inline void rt_div8(CPU *c, uint32_t d, uint32_t addr) {
    uint32_t n = AX;
    if (d == 0 || n / d > 0xff) rt_divide_error(c, addr);
    uint32_t q = n / d, r = n % d;
    AL = (uint8_t)q; AH = (uint8_t)r;
}
static inline void rt_div16(CPU *c, uint32_t d, uint32_t addr) {
    uint32_t n = ((uint32_t)DX << 16) | AX;
    if (d == 0 || n / d > 0xffff) rt_divide_error(c, addr);
    uint32_t q = n / d, r = n % d;
    AX = (uint16_t)q; DX = (uint16_t)r;
}
static inline void rt_div32(CPU *c, uint32_t d, uint32_t addr) {
    uint64_t n = ((uint64_t)EDX << 32) | EAX;
    if (d == 0 || n / d > 0xffffffffu) rt_divide_error(c, addr);
    uint64_t q = n / d, r = n % d;
    EAX = (uint32_t)q; EDX = (uint32_t)r;
}
static inline void rt_idiv8(CPU *c, uint32_t d8, uint32_t addr) {
    int32_t n = (int16_t)AX, d = (int8_t)d8;
    if (d == 0) rt_divide_error(c, addr);
    int32_t q = n / d, r = n % d;
    if (q > 127 || q < -128) rt_divide_error(c, addr);
    AL = (uint8_t)q; AH = (uint8_t)r;
}
static inline void rt_idiv16(CPU *c, uint32_t d16, uint32_t addr) {
    int32_t n = (int32_t)(((uint32_t)DX << 16) | AX), d = (int16_t)d16;
    if (d == 0 || (n == INT32_MIN && d == -1)) rt_divide_error(c, addr);
    int32_t q = n / d, r = n % d;
    if (q > 32767 || q < -32768) rt_divide_error(c, addr);
    AX = (uint16_t)q; DX = (uint16_t)r;
}
static inline void rt_idiv32(CPU *c, uint32_t d32, uint32_t addr) {
    int64_t n = (int64_t)(((uint64_t)EDX << 32) | EAX), d = (int32_t)d32;
    if (d == 0 || (n == INT64_MIN && d == -1)) rt_divide_error(c, addr);
    int64_t q = n / d, r = n % d;
    if (q > INT32_MAX || q < INT32_MIN) rt_divide_error(c, addr);
    EAX = (uint32_t)q; EDX = (uint32_t)r;
}

/* ------------------------------------------------------------- string ops */
#define RT_STRING_OPS(N, T, LD, ST)                                                         \
    static inline void rt_movs##N(CPU *c) {                                                 \
        ST(EDI, LD(ESI));                                                                   \
        uint32_t d = c->df ? (uint32_t)-(int)sizeof(T) : (uint32_t)sizeof(T);               \
        ESI += d; EDI += d;                                                                 \
    }                                                                                       \
    static inline void rt_rep_movs##N(CPU *c) {                                             \
        uint32_t d = c->df ? (uint32_t)-(int)sizeof(T) : (uint32_t)sizeof(T);               \
        while (ECX) { ST(EDI, LD(ESI)); ESI += d; EDI += d; ECX--; }                        \
    }                                                                                       \
    static inline void rt_stos##N(CPU *c) {                                                 \
        ST(EDI, (T)EAX);                                                                    \
        EDI += c->df ? (uint32_t)-(int)sizeof(T) : (uint32_t)sizeof(T);                     \
    }                                                                                       \
    static inline void rt_rep_stos##N(CPU *c) {                                             \
        uint32_t d = c->df ? (uint32_t)-(int)sizeof(T) : (uint32_t)sizeof(T);               \
        T v = (T)EAX;                                                                       \
        while (ECX) { ST(EDI, v); EDI += d; ECX--; }                                        \
    }                                                                                       \
    static inline T rt_lods##N(CPU *c) {                                                    \
        T v = LD(ESI);                                                                      \
        ESI += c->df ? (uint32_t)-(int)sizeof(T) : (uint32_t)sizeof(T);                     \
        return v;                                                                           \
    }                                                                                       \
    static inline void rt_cmpflags##N(CPU *c, T a, T b) {                                   \
        T r = (T)(a - b);                                                                   \
        unsigned bits = sizeof(T) * 8;                                                      \
        c->cf = a < b; c->zf = r == 0; c->sf = (r >> (bits - 1)) & 1;                       \
        c->of = (((a ^ b) & (a ^ r)) >> (bits - 1)) & 1;                                    \
        c->af = ((a ^ b ^ r) >> 4) & 1; c->pf = rt_pf(r);                                   \
    }                                                                                       \
    static inline void rt_cmps##N(CPU *c) {                                                 \
        T a = LD(ESI), b = LD(EDI);                                                         \
        uint32_t d = c->df ? (uint32_t)-(int)sizeof(T) : (uint32_t)sizeof(T);               \
        ESI += d; EDI += d;                                                                 \
        rt_cmpflags##N(c, a, b);                                                            \
    }                                                                                       \
    static inline void rt_scas##N(CPU *c) {                                                 \
        T a = (T)EAX, b = LD(EDI);                                                          \
        EDI += c->df ? (uint32_t)-(int)sizeof(T) : (uint32_t)sizeof(T);                     \
        rt_cmpflags##N(c, a, b);                                                            \
    }                                                                                       \
    /* want_zf: 1 for repe (continue while equal), 0 for repne */                           \
    static inline void rt_rep_cmps##N(CPU *c, int want_zf) {                                \
        while (ECX) { rt_cmps##N(c); ECX--; if (c->zf != want_zf) break; }                  \
    }                                                                                       \
    static inline void rt_rep_scas##N(CPU *c, int want_zf) {                                \
        while (ECX) { rt_scas##N(c); ECX--; if (c->zf != want_zf) break; }                  \
    }

RT_STRING_OPS(8, uint8_t, ld8, st8)
RT_STRING_OPS(16, uint16_t, ld16, st16)
RT_STRING_OPS(32, uint32_t, ld32, st32)

/* --------------------------------------------------------------------- x87 */
#define FSW_C0 0x0100
#define FSW_C1 0x0200
#define FSW_C2 0x0400
#define FSW_C3 0x4000
#define FSW_CC (FSW_C0 | FSW_C1 | FSW_C2 | FSW_C3)

#define ST(i) (c->st[(c->ftop + (i)) & 7])

static inline void fpush(CPU *c, double v) {
    c->ftop = (c->ftop - 1) & 7;
    c->st[c->ftop] = v;
    c->ftag |= (uint8_t)(1u << c->ftop);
}
static inline void fpop(CPU *c) {
    c->ftag &= (uint8_t)~(1u << c->ftop);
    c->ftop = (c->ftop + 1) & 7;
}
/* Result of an arithmetic operation under the current precision control:
 * 24-bit precision rounds to float; 53- and 64-bit are both computed as double. */
static inline double rt_fpr(const CPU *c, double v) {
    return (c->fcw & 0x300) ? v : (double)(float)v;
}
static inline void rt_fcom(CPU *c, double a, double b) {
    uint16_t cc;
    if (a > b) cc = 0;
    else if (a < b) cc = FSW_C0;
    else if (a == b) cc = FSW_C3;
    else cc = FSW_C3 | FSW_C2 | FSW_C0;
    c->fsw = (uint16_t)((c->fsw & ~(FSW_C0 | FSW_C2 | FSW_C3)) | cc);
}
static inline void rt_fcomi(CPU *c, double a, double b) {
    if (a > b) { c->zf = 0; c->pf = 0; c->cf = 0; }
    else if (a < b) { c->zf = 0; c->pf = 0; c->cf = 1; }
    else if (a == b) { c->zf = 1; c->pf = 0; c->cf = 0; }
    else { c->zf = 1; c->pf = 1; c->cf = 1; }
    c->of = 0; c->sf = 0; c->af = 0;
}
static inline uint16_t rt_fnstsw(const CPU *c) {
    return (uint16_t)((c->fsw & ~0x3800) | (c->ftop << 11));
}
/* Round to an integral value in the rounding mode selected by the control word. */
static inline double rt_fround(const CPU *c, double v) {
    switch ((c->fcw >> 10) & 3) {
    case 0: return nearbyint(v); /* host stays in round-to-nearest-even */
    case 1: return floor(v);
    case 2: return ceil(v);
    default: return trunc(v);
    }
}
static inline uint16_t rt_fist16(const CPU *c, double v) {
    double r = rt_fround(c, v);
    if (!(r >= -32768.0 && r <= 32767.0)) return 0x8000;
    return (uint16_t)(int16_t)r;
}
static inline uint32_t rt_fist32(const CPU *c, double v) {
    double r = rt_fround(c, v);
    if (!(r >= -2147483648.0 && r <= 2147483647.0)) return 0x80000000u;
    return (uint32_t)(int32_t)r;
}
static inline uint64_t rt_fist64(const CPU *c, double v) {
    double r = rt_fround(c, v);
    if (!(r >= -9223372036854775808.0 && r < 9223372036854775808.0)) return 0x8000000000000000ull;
    return (uint64_t)(int64_t)r;
}

#endif /* RECOMP_CPU_H */
