/* --profile FILE: a sampling profile of the whole process.
 *
 * A timer on the process's CPU time raises SIGPROF as CPU time is used (asked
 * for every millisecond; the kernel delivers at its tick, typically every 4 ms),
 * on a thread that is using it; the handler notes the program counter.
 * At exit the samples are written as text, one "address count" line per
 * distinct program counter, relative to the start of the executable (so that
 * the addresses are those `nm` prints, also for a position-independent build).
 * Samples outside the executable (libc, SDL, the kernel's vdso) are counted
 * under the address 0. tools/profile_report.py turns the file into a table. */
#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#if defined(__APPLE__)
#include <sys/ucontext.h>
#include <mach-o/dyld.h>
#include <mach-o/getsect.h>
#include <sys/time.h>
#else
#include <link.h>
#include <ucontext.h>
#endif

#include "rt.h"

#define MAX_SAMPLES (1u << 21)
static uintptr_t *samples;
static unsigned nsamples;
static uintptr_t exe_base, exe_lo, exe_hi;
#if !defined(__APPLE__)
extern char __executable_start[], etext[];
#endif

static void on_prof(int sig, siginfo_t *si, void *ctx) {
    (void)sig, (void)si;
    ucontext_t *uc = ctx;
#if defined(__APPLE__) && defined(__aarch64__)
    uintptr_t pc = (uintptr_t)uc->uc_mcontext->__ss.__pc;
#elif defined(__APPLE__) && defined(__x86_64__)
    uintptr_t pc = (uintptr_t)uc->uc_mcontext->__ss.__rip;
#elif defined(__x86_64__)
    uintptr_t pc = (uintptr_t)uc->uc_mcontext.gregs[REG_RIP];
#elif defined(__aarch64__)
    uintptr_t pc = (uintptr_t)uc->uc_mcontext.pc;
#else
    uintptr_t pc = 0;
    (void)uc;
#endif
    unsigned i = __atomic_fetch_add(&nsamples, 1, __ATOMIC_RELAXED);
    if (i < MAX_SAMPLES) samples[i] = pc;
}

#if !defined(__APPLE__)
static int find_base(struct dl_phdr_info *info, size_t size, void *data) {
    (void)size, (void)data;
    exe_base = info->dlpi_addr; /* the first object is the executable */
    return 1;
}
#endif

void rt_profile_start(void) {
    if (!g_opt.profile[0]) return;
    samples = calloc(MAX_SAMPLES, sizeof *samples);
    if (!samples) return;
#if defined(__APPLE__)
    /* addresses as nm prints them: unslid, from the image's own __TEXT */
    unsigned long size = 0;
    uint8_t *text = getsegmentdata((const struct mach_header_64 *)_dyld_get_image_header(0), "__TEXT", &size);
    exe_base = (uintptr_t)_dyld_get_image_vmaddr_slide(0);
    exe_lo = (uintptr_t)text;
    exe_hi = exe_lo + size;
#else
    dl_iterate_phdr(find_base, NULL);
    exe_lo = (uintptr_t)__executable_start;
    exe_hi = (uintptr_t)etext;
#endif
    struct sigaction sa;
    memset(&sa, 0, sizeof sa);
    sa.sa_sigaction = on_prof;
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    sigaction(SIGPROF, &sa, NULL);
#if defined(__APPLE__)
    /* no POSIX timers: the process's CPU-time interval timer raises SIGPROF the same way */
    struct itimerval itv = {{0, 1000}, {0, 1000}};
    if (setitimer(ITIMER_PROF, &itv, NULL) != 0) rt_log("recomp: --profile: cannot start the timer\n");
#else
    timer_t t;
    struct sigevent se;
    memset(&se, 0, sizeof se);
    se.sigev_notify = SIGEV_SIGNAL;
    se.sigev_signo = SIGPROF;
    struct itimerspec its = {{0, 1000000}, {0, 1000000}};
    if (timer_create(CLOCK_PROCESS_CPUTIME_ID, &se, &t) != 0 || timer_settime(t, 0, &its, NULL) != 0)
        rt_log("recomp: --profile: cannot start the timer\n");
#endif
}

static int cmp_addr(const void *a, const void *b) {
    uintptr_t x = *(const uintptr_t *)a, y = *(const uintptr_t *)b;
    return x < y ? -1 : x > y;
}

void rt_profile_write(void) {
    if (!samples) return;
    signal(SIGPROF, SIG_IGN);
    unsigned n = __atomic_load_n(&nsamples, __ATOMIC_RELAXED);
    if (n > MAX_SAMPLES) n = MAX_SAMPLES;
    FILE *f = fopen(g_opt.profile, "w");
    if (!f) {
        rt_log("recomp: cannot write %s\n", g_opt.profile);
        return;
    }
    for (unsigned i = 0; i < n; i++)
        samples[i] = samples[i] >= exe_lo && samples[i] < exe_hi ? samples[i] - exe_base : 0;
    qsort(samples, n, sizeof *samples, cmp_addr);
    fprintf(f, "# samples %u, taken at even intervals of CPU time; address count\n", n);
    for (unsigned i = 0; i < n;) {
        unsigned j = i;
        while (j < n && samples[j] == samples[i]) j++;
        fprintf(f, "%lx %u\n", (unsigned long)samples[i], j - i);
        i = j;
    }
    fclose(f);
    rt_log("recomp: %u profile samples written to %s\n", n, g_opt.profile);
}
