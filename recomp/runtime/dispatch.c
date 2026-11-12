/* Indirect call dispatch, import dispatch and diagnostics. */
#define _GNU_SOURCE
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#include "rt.h"

GuestFn *g_ftab;
uint32_t g_ftab_base, g_ftab_size;
Import *g_imports;
uint32_t g_nimports;
int g_trace_imports;
CPU *g_cpu;

static uint32_t imports_cap;

void rt_build_ftab(void) {
    g_ftab_base = rt_text_base;
    g_ftab_size = rt_text_size;
    g_ftab = calloc(rt_text_size, sizeof(GuestFn));
    if (!g_ftab) {
        perror("recomp: function table");
        exit(2);
    }
    for (uint32_t i = 0; i < rt_nfuncs; i++) g_ftab[rt_funcs[i].addr - rt_text_base] = rt_funcs[i].fn;
}

/* ------------------------------------------------------------- imports */
uint32_t rt_register_import(const char *dll, const char *name, uint32_t iat_va) {
    if (g_nimports == imports_cap) {
        imports_cap = imports_cap ? imports_cap * 2 : 256;
        g_imports = realloc(g_imports, imports_cap * sizeof(Import));
    }
    if ((g_nimports + 1) * 16 > GUEST_IMP_SIZE) {
        fprintf(stderr, "recomp: too many imports\n");
        exit(2);
    }
    Import *im = &g_imports[g_nimports];
    memset(im, 0, sizeof *im);
    im->dll = strdup(dll);
    im->name = strdup(name);
    im->iat_va = iat_va;
    const ImportDef *def = rt_find_import_def(dll, name);
    if (def) {
        im->fn = def->fn;
        im->nargs = def->nargs;
        im->is_cdecl = def->is_cdecl;
    }
    return GUEST_IMP_BASE + 16 * g_nimports++;
}

void rt_import_call(CPU *c, uint32_t idx) {
    Import *im = &g_imports[idx];
    uint32_t ra = ld32(ESP);
    im->calls++;
    if (!im->fn) {
        fflush(stdout);
        fprintf(stderr, "\nUNIMPLEMENTED import %s!%s\n", im->dll, im->name);
        fprintf(stderr, "  called from 0x%08x; first stack arguments: %08x %08x %08x %08x %08x %08x\n", ra,
                ld32(ESP + 4), ld32(ESP + 8), ld32(ESP + 12), ld32(ESP + 16), ld32(ESP + 20), ld32(ESP + 24));
        rt_backtrace(c);
        rt_print_import_stats();
        exit(3);
    }
    uint32_t args[16];
    int n = im->nargs > 16 ? 16 : im->nargs;
    for (int i = 0; i < n; i++) args[i] = ld32(ESP + 4 + 4 * (uint32_t)i);
    if (g_trace_imports) {
        fprintf(stderr, "[import] %s!%s(", im->dll, im->name);
        for (int i = 0; i < n; i++) fprintf(stderr, i ? ", %#x" : "%#x", args[i]);
        fprintf(stderr, ")");
        fflush(stderr);
    }
    uint32_t ret = im->fn(c, args);
    if (g_trace_imports) fprintf(stderr, " -> %#x   [from %08x]\n", ret, ra);
    EAX = ret;
    ESP += 4 + (im->is_cdecl ? 0 : 4 * (uint32_t)im->nargs);
    c->eip = ra;
}

void rt_print_import_stats(void) {
    unsigned used = 0, impl = 0;
    for (uint32_t i = 0; i < g_nimports; i++) {
        if (g_imports[i].fn) impl++;
        if (g_imports[i].calls) used++;
    }
    fprintf(stderr, "imports: %u in the image, %u with handlers, %u distinct called so far:\n ", g_nimports, impl,
            used);
    for (uint32_t i = 0; i < g_nimports; i++)
        if (g_imports[i].calls)
            fprintf(stderr, " %s%s(%llu)", g_imports[i].fn ? "" : "!", g_imports[i].name,
                    (unsigned long long)g_imports[i].calls);
    fprintf(stderr, "\n");
}

static int import_index(uint32_t addr) {
    uint32_t off = addr - GUEST_IMP_BASE;
    if (off < 16 * g_nimports && (off & 15) == 0) return (int)(off / 16);
    return -1;
}

void rt_call_slow(CPU *c, uint32_t addr) {
    int idx = import_index(addr);
    if (idx >= 0) {
        rt_import_call(c, (uint32_t)idx);
        return;
    }
    /* Hook: a later milestone falls back to an interpreter for code the lifter did not see. */
    rt_fatal(c, 4, "indirect call to 0x%08x, which is not a lifted function (return address 0x%08x)", addr,
             ld32(ESP));
}

void rt_jmp_slow(CPU *c, uint32_t addr, uint32_t from) {
    int idx = import_index(addr);
    if (idx >= 0) {
        rt_import_call(c, (uint32_t)idx);
        return;
    }
    rt_fatal(c, 4, "indirect jump from 0x%08x to 0x%08x, which is not a lifted function entry", from, addr);
}

void rt_ret_mismatch(CPU *c, uint32_t expected) {
    rt_fatal(c, 4,
             "guest returned to 0x%08x but the call site expected 0x%08x "
             "(non-local control flow: SEH unwind, longjmp or a rewritten return address)",
             c->eip, expected);
}

void rt_unimplemented_insn(CPU *c, uint32_t addr, const char *mnemonic) {
    rt_fatal(c, 4, "UNIMPLEMENTED instruction `%s` at 0x%08x", mnemonic, addr);
}

void rt_bad_code(CPU *c, uint32_t from, uint32_t target) {
    rt_fatal(c, 4, "control reached 0x%08x (from 0x%08x), which the lifter could not decode", target, from);
}

void rt_divide_error(CPU *c, uint32_t addr) {
    rt_fatal(c, 4, "guest divide error (#DE) at 0x%08x; guest exception dispatch is not implemented", addr);
}

/* --------------------------------------------------------- diagnostics */
const char *rt_func_name(uint32_t addr, uint32_t *start) {
    if (rt_nfuncs == 0 || addr < rt_funcs[0].addr || addr >= rt_text_base + rt_text_size) return NULL;
    uint32_t lo = 0, hi = rt_nfuncs;
    while (hi - lo > 1) {
        uint32_t mid = (lo + hi) / 2;
        if (rt_funcs[mid].addr <= addr) lo = mid;
        else hi = mid;
    }
    if (start) *start = rt_funcs[lo].addr;
    return rt_funcs[lo].name;
}

static int is_retsite(uint32_t v) {
    uint32_t lo = 0, hi = rt_nretsites;
    while (lo < hi) {
        uint32_t mid = (lo + hi) / 2;
        if (rt_retsites[mid] == v) return 1;
        if (rt_retsites[mid] < v) lo = mid + 1;
        else hi = mid;
    }
    return 0;
}

static void print_code_addr(uint32_t a) {
    uint32_t start = 0;
    const char *name = rt_func_name(a, &start);
    if (name) fprintf(stderr, "0x%08x  %s+0x%x", a, name, a - start);
    else fprintf(stderr, "0x%08x", a);
}

void rt_dump_state(CPU *c) {
    fprintf(stderr, "  eax=%08x ebx=%08x ecx=%08x edx=%08x esi=%08x edi=%08x\n", EAX, EBX, ECX, EDX, ESI, EDI);
    fprintf(stderr, "  esp=%08x ebp=%08x eflags=%08x fs=%08x x87: top=%u cw=%04x sw=%04x\n", ESP, EBP,
            rt_get_eflags(c), c->fs_base, c->ftop, c->fcw, rt_fnstsw(c));
}

/* Guest call stack: every stack slot holding an address that follows a call
 * instruction is reported; slots that are also on the EBP frame chain are
 * marked with '*'. Stale return addresses can appear; frames are never missed. */
void rt_backtrace(CPU *c) {
    uint32_t chain[64];
    unsigned nchain = 0;
    uint32_t bp = EBP;
    while (nchain < 64 && bp >= ESP && bp + 8 <= GUEST_STACK_TOP && (bp & 3) == 0) {
        chain[nchain++] = bp + 4;
        uint32_t next = ld32(bp);
        if (next <= bp) break;
        bp = next;
    }
    fprintf(stderr, "guest state:\n");
    rt_dump_state(c);
    fprintf(stderr, "guest call stack (most recent first):\n");
    if (ESP < GUEST_STACK_LOW || ESP >= GUEST_STACK_TOP) {
        fprintf(stderr, "  (esp is outside the guest stack)\n");
        return;
    }
    unsigned shown = 0;
    for (uint32_t sp = ESP & ~3u; sp + 4 <= GUEST_STACK_TOP && shown < 48; sp += 4) {
        uint32_t v = ld32(sp);
        if (!is_retsite(v)) continue;
        int on_chain = 0;
        for (unsigned i = 0; i < nchain; i++) on_chain |= chain[i] == sp;
        fprintf(stderr, "  %c#%-2u [%08x] ", on_chain ? '*' : ' ', shown, sp);
        print_code_addr(v);
        fprintf(stderr, "\n");
        shown++;
    }
    if (!shown) fprintf(stderr, "  (no return addresses found)\n");
}

void rt_fatal(CPU *c, int code, const char *fmt, ...) {
    va_list ap;
    fflush(stdout);
    fprintf(stderr, "\nrecomp: fatal: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, "\n");
    if (c) rt_backtrace(c);
    exit(code);
}

static void fault_handler(int sig, siginfo_t *si, void *ctx) {
    (void)ctx;
    static volatile sig_atomic_t busy;
    if (busy) _exit(5);
    busy = 1;
    uintptr_t host = (uintptr_t)si->si_addr;
    uintptr_t base = (uintptr_t)G(0);
    fprintf(stderr, "\nrecomp: fatal: host signal %d (%s)", sig, sig == SIGSEGV ? "SIGSEGV" : sig == SIGBUS ? "SIGBUS" : "SIGFPE");
    if (sig != SIGFPE) {
        if (host >= base && host - base <= 0xFFFFFFFFull)
            fprintf(stderr, ": guest access to 0x%08x", (uint32_t)(host - base));
        else
            fprintf(stderr, ": host address %p (not a guest access; runtime bug or host stack overflow)", si->si_addr);
    }
    fprintf(stderr, "\n");
    if (g_cpu) rt_backtrace(g_cpu);
    _exit(5);
}

void rt_install_fault_handler(void) {
    static uint8_t altstack[1 << 16];
    stack_t ss = {.ss_sp = altstack, .ss_size = sizeof altstack, .ss_flags = 0};
    sigaltstack(&ss, NULL);
    struct sigaction sa;
    memset(&sa, 0, sizeof sa);
    sa.sa_sigaction = fault_handler;
    sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGBUS, &sa, NULL);
    sigaction(SIGFPE, &sa, NULL);
}
