/* Structured exception handling for software exceptions.
 *
 * RaiseException walks the guest's SEH registration chain (fs:[0]) and calls
 * each handler as Windows does; RtlUnwind runs the handlers again with the
 * unwinding flag and unlinks the frames. That is all the MSVC run-time needs:
 * _except_handler3 and __CxxFrameHandler do the rest in lifted guest code, and
 * the resulting transfer into a catch block or __except block is a non-local
 * return that the lifted call sites resolve (RT_RETCHECK in cpu.h).
 *
 * Hardware exceptions (access violation, divide error, breakpoint) are not
 * turned into guest exceptions: they stop the program with a diagnostic.
 */
#include <stdio.h>
#include <stdlib.h>

#include "rt.h"

#define EXCEPTION_NONCONTINUABLE 1u
#define EXCEPTION_UNWINDING 2u
#define EXCEPTION_EXIT_UNWIND 4u
#define STATUS_UNWIND 0xC0000027u
#define CXX_EXCEPTION 0xE06D7363u

#define REC_SIZE 0x50u
#define CTX_SIZE 0x2CCu
#define CHAIN_END 0xFFFFFFFFu

static uint32_t unhandled_filter;

static void fill_context(CPU *c, uint32_t ctx, uint32_t eip, uint32_t esp) {
    memset(G(ctx), 0, CTX_SIZE);
    st32(ctx + 0x00, 0x0001003Fu); /* CONTEXT_FULL | debug | float | extended */
    st32(ctx + 0x8C, 0x2B);        /* gs */
    st32(ctx + 0x90, 0x53);        /* fs */
    st32(ctx + 0x94, 0x2B);
    st32(ctx + 0x98, 0x2B);
    st32(ctx + 0x9C, EDI);
    st32(ctx + 0xA0, ESI);
    st32(ctx + 0xA4, EBX);
    st32(ctx + 0xA8, EDX);
    st32(ctx + 0xAC, ECX);
    st32(ctx + 0xB0, EAX);
    st32(ctx + 0xB4, EBP);
    st32(ctx + 0xB8, eip);
    st32(ctx + 0xBC, 0x23);
    st32(ctx + 0xC0, rt_get_eflags(c));
    st32(ctx + 0xC4, esp);
    st32(ctx + 0xC8, 0x2B);
    st32(ctx + 0x1C, c->fcw | 0xFFFF0000u);         /* FloatSave.ControlWord */
    st32(ctx + 0x20, rt_fnstsw(c) | 0xFFFF0000u);   /* FloatSave.StatusWord */
}

static int frame_valid(CPU *c, uint32_t frame) {
    RtThread *th = rt_thread_of(c);
    uint32_t lo = th ? th->stack_low : GUEST_STACK_LOW, top = th ? th->stack_top : GUEST_STACK_TOP;
    return (frame & 3) == 0 && frame >= lo && frame + 8 <= top;
}

/* The mangled type names of a C++ exception's catchable types, for diagnostics. */
static void describe_cxx(uint32_t rec) {
    if (ld32(rec) != CXX_EXCEPTION || ld32(rec + 0x10) < 3) return;
    uint32_t throw_info = ld32(rec + 0x14 + 8);
    if (!rt_guest_readable(throw_info, 16)) return;
    uint32_t types = ld32(throw_info + 12);
    if (!rt_guest_readable(types, 8)) return;
    uint32_t n = ld32(types);
    fprintf(stderr, "  C++ exception object at %08x, catchable types:", ld32(rec + 0x14 + 4));
    for (uint32_t i = 0; i < n && i < 8; i++) {
        uint32_t ct = ld32(types + 4 + 4 * i);
        if (!rt_guest_readable(ct, 8)) break;
        uint32_t ti = ld32(ct + 4);
        if (!rt_guest_readable(ti, 16)) break;
        fprintf(stderr, " %s", (const char *)G(ti + 8));
    }
    fprintf(stderr, "\n");
}

/* RaiseException(code, flags, argCount, args) */
H(k32_RaiseException) {
    uint32_t sp = ESP;
    uint32_t ra = ld32(sp);
    uint32_t base = (sp - REC_SIZE - CTX_SIZE - 16) & ~15u;
    uint32_t rec = base, ctx = base + REC_SIZE, dctx = base + REC_SIZE + CTX_SIZE;

    memset(G(rec), 0, REC_SIZE);
    st32(rec + 0x00, a[0]);
    st32(rec + 0x04, a[1] & EXCEPTION_NONCONTINUABLE);
    st32(rec + 0x0C, ra);
    uint32_t n = a[3] ? (a[2] > 15 ? 15 : a[2]) : 0;
    st32(rec + 0x10, n);
    for (uint32_t i = 0; i < n; i++) st32(rec + 0x14 + 4 * i, ld32(a[3] + 4 * i));
    fill_context(c, ctx, ra, sp + 20);
    if (g_trace_imports) rt_log("[seh %x] RaiseException code %08x from %08x\n", c->thread_id, a[0], ra);

    ESP = base - 16;
    uint32_t frame = ld32(c->fs_base);
    while (frame != CHAIN_END) {
        if (!frame_valid(c, frame)) {
            ESP = sp;
            rt_fatal(c, 4, "RaiseException(%#x): corrupt SEH chain, registration at 0x%08x", a[0], frame);
        }
        uint32_t handler = ld32(frame + 4);
        uint32_t args[4] = {rec, frame, ctx, dctx}, disp = 0;
        if (g_trace_imports) rt_log("[seh %x]   frame %08x handler %08x\n", c->thread_id, frame, handler);
        if (!rt_call_guest(c, handler, RT_CDECL, 4, args, &disp)) return 0; /* a handler took the exception */
        if (disp == 0) { /* ExceptionContinueExecution */
            if (ld32(rec + 4) & EXCEPTION_NONCONTINUABLE) {
                ESP = sp;
                rt_fatal(c, 4, "a handler asked to continue the non-continuable exception %#x", a[0]);
            }
            ESP = sp;
            return EAX;
        }
        frame = ld32(frame); /* ContinueSearch, or a nested/collided disposition: keep looking */
    }

    /* Nothing handled it. Windows would now consult the unhandled exception filter. */
    if (unhandled_filter) {
        st32(dctx, rec);
        st32(dctx + 4, ctx);
        uint32_t args[1] = {dctx}, r = 0;
        if (!rt_call_guest(c, unhandled_filter, RT_STDCALL, 1, args, &r)) return 0;
        if (r == 0xFFFFFFFFu) { /* EXCEPTION_CONTINUE_EXECUTION */
            ESP = sp;
            return EAX;
        }
    }
    ESP = sp;
    fflush(stdout);
    fprintf(stderr, "\nrecomp: unhandled guest exception %08x raised at 0x%08x (%u parameters)\n", a[0], ra, n);
    describe_cxx(rec);
    rt_backtrace(c);
    rt_exit(4);
}

/* RtlUnwind(targetFrame, targetIp, exceptionRecord, returnValue) */
H(k32_RtlUnwind) {
    uint32_t sp = ESP;
    uint32_t target = a[0];
    uint32_t base = (sp - REC_SIZE - CTX_SIZE - 16) & ~15u;
    uint32_t rec = a[2], ctx = base + REC_SIZE, dctx = base + REC_SIZE + CTX_SIZE;
    if (!rec) {
        rec = base;
        memset(G(rec), 0, REC_SIZE);
        st32(rec, STATUS_UNWIND);
        st32(rec + 0x0C, ld32(sp));
    }
    st32(rec + 4, ld32(rec + 4) | EXCEPTION_UNWINDING | (target ? 0 : EXCEPTION_EXIT_UNWIND));
    fill_context(c, ctx, ld32(sp), sp + 20);
    st32(ctx + 0xB0, a[3]);
    if (g_trace_imports) rt_log("[seh %x] RtlUnwind to frame %08x\n", c->thread_id, target);

    ESP = base - 16;
    uint32_t frame = ld32(c->fs_base);
    while (frame != CHAIN_END && frame != target) {
        if (!frame_valid(c, frame) || (target && frame > target)) {
            ESP = sp;
            rt_fatal(c, 4, "RtlUnwind: registration 0x%08x is not below the target frame 0x%08x", frame, target);
        }
        uint32_t handler = ld32(frame + 4);
        uint32_t args[4] = {rec, frame, ctx, dctx}, disp = 0;
        if (g_trace_imports) rt_log("[seh %x]   unwind frame %08x handler %08x\n", c->thread_id, frame, handler);
        if (!rt_call_guest(c, handler, RT_CDECL, 4, args, &disp)) return 0;
        uint32_t next = disp == 3 ? ld32(dctx) : ld32(frame); /* ExceptionCollidedUnwind names the frame to go on from */
        st32(c->fs_base, next);
        frame = next;
    }
    ESP = sp;
    return a[3];
}

H(k32_SetUnhandledExceptionFilter) {
    UNUSED;
    return __atomic_exchange_n(&unhandled_filter, a[0], __ATOMIC_SEQ_CST);
}

/* The CRT's own last-chance filters end here. Report the exception and let the
 * caller run its handler (which terminates the program). */
H(k32_UnhandledExceptionFilter) {
    uint32_t rec = a[0] ? ld32(a[0]) : 0;
    fflush(stdout);
    if (rec && rt_guest_readable(rec, REC_SIZE)) {
        fprintf(stderr, "\nrecomp: guest called UnhandledExceptionFilter: exception %08x at 0x%08x\n", ld32(rec),
                ld32(rec + 0x0C));
        describe_cxx(rec);
    } else {
        fprintf(stderr, "\nrecomp: guest called UnhandledExceptionFilter\n");
    }
    rt_backtrace(c);
    return 1; /* EXCEPTION_EXECUTE_HANDLER */
}

static const ImportDef defs[] = {
    {"kernel32.dll", "RaiseException", k32_RaiseException, 4, 0},
    {"kernel32.dll", "RtlUnwind", k32_RtlUnwind, 4, 0},
    {"kernel32.dll", "SetUnhandledExceptionFilter", k32_SetUnhandledExceptionFilter, 1, 0},
    {"kernel32.dll", "UnhandledExceptionFilter", k32_UnhandledExceptionFilter, 1, 0},
};
RT_EXPORT_IMPORTS(rt_imports_seh, defs);
