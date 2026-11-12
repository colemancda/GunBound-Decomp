/* Entry point of the recompiled program: build the guest process and run it from the PE entry. */
#include <stdio.h>
#include <stdlib.h>

#include "rt.h"

static void usage(const char *argv0) {
    fprintf(stderr,
            "usage: %s [--exe PATH] [--trace-imports] [--] [guest command line arguments...]\n"
            "  --exe PATH        the original executable (default: $RECOMP_EXE, then ./GunBound.gme)\n"
            "  --trace-imports   log every Win32 import call with its arguments and result\n",
            argv0);
}

static void build_process(int argc, char **argv, int first_guest_arg) {
    /* Command line: quoted module path followed by the guest arguments. */
    char cmd[2048];
    size_t n = (size_t)snprintf(cmd, sizeof cmd, "\"%s\"", g_image.guest_path);
    for (int i = first_guest_arg; i < argc && n < sizeof cmd; i++)
        n += (size_t)snprintf(cmd + n, sizeof cmd - n, " %s", argv[i]);
    g_proc.cmdline_a = rt_sys_strdup(cmd);

    /* Environment: a small fixed block, in ANSI and UTF-16 form. */
    static const char *const env[] = {
        "ALLUSERSPROFILE=C:\\Documents and Settings\\All Users",
        "COMPUTERNAME=RECOMP",
        "OS=Windows_NT",
        "PATH=C:\\WINDOWS\\system32;C:\\WINDOWS",
        "SystemDrive=C:",
        "SystemRoot=C:\\WINDOWS",
        "TEMP=C:\\TEMP",
        "TMP=C:\\TEMP",
        "USERNAME=player",
        "windir=C:\\WINDOWS",
    };
    uint32_t total = 1;
    for (size_t i = 0; i < sizeof env / sizeof env[0]; i++) total += (uint32_t)strlen(env[i]) + 1;
    g_proc.env_a = rt_sys_alloc(total);
    g_proc.env_w = rt_sys_alloc(total * 2);
    uint32_t o = 0;
    for (size_t i = 0; i < sizeof env / sizeof env[0]; i++) {
        for (const char *p = env[i];; p++) {
            st8(g_proc.env_a + o, (uint8_t)*p);
            st16(g_proc.env_w + 2 * o, (uint8_t)*p);
            o++;
            if (!*p) break;
        }
    }
    st8(g_proc.env_a + o, 0);
    st16(g_proc.env_w + 2 * o, 0);

    /* PEB and TEB: only the fields user-mode code commonly reads directly. */
    st8(GUEST_PEB + 2, 0);                    /* BeingDebugged */
    st32(GUEST_PEB + 8, g_image.base);        /* ImageBaseAddress */
    st32(GUEST_PEB + 0x18, 0x00140000);       /* ProcessHeap */
    st32(GUEST_TEB + 0x00, 0xFFFFFFFFu);      /* SEH chain: end marker */
    st32(GUEST_TEB + 0x04, GUEST_STACK_TOP);  /* StackBase */
    st32(GUEST_TEB + 0x08, GUEST_STACK_LOW);  /* StackLimit */
    st32(GUEST_TEB + 0x18, GUEST_TEB);        /* Self */
    st32(GUEST_TEB + 0x20, 0x00000A28);       /* process id */
    st32(GUEST_TEB + 0x24, 0x00000A2C);       /* thread id */
    st32(GUEST_TEB + 0x2C, GUEST_TEB + TEB_TLS_SLOTS); /* ThreadLocalStoragePointer */
    st32(GUEST_TEB + 0x30, GUEST_PEB);
}

int main(int argc, char **argv) {
    const char *exe = getenv("RECOMP_EXE");
    int i = 1;
    for (; i < argc; i++) {
        if (!strcmp(argv[i], "--trace-imports")) g_trace_imports = 1;
        else if (!strcmp(argv[i], "--exe") && i + 1 < argc) exe = argv[++i];
        else if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) { usage(argv[0]); return 0; }
        else if (!strcmp(argv[i], "--")) { i++; break; }
        else if (argv[i][0] == '-' && argv[i][1] == '-') { usage(argv[0]); return 2; }
        else break;
    }
    if (!exe) exe = "GunBound.gme";

    setvbuf(stderr, NULL, _IOLBF, 0);
    rt_mem_init();
    snprintf(g_image.guest_path, sizeof g_image.guest_path, "C:\\GunBound\\GunBound.gme");
    rt_build_ftab();
    rt_load_pe(exe);
    build_process(argc, argv, i);
    rt_install_fault_handler();

    static CPU cpu;
    CPU *c = &cpu;
    g_cpu = c;
    c->fs_base = GUEST_TEB;
    c->thread_id = 0x00000A2C;
    c->fcw = 0x027F; /* Windows default: 53-bit precision, round to nearest, exceptions masked */
    c->eflags_hi = 0;
    ESP = GUEST_STACK_TOP - 0x40;
    EBX = GUEST_PEB;
    PUSH32(GUEST_EXIT_ADDR);

    fprintf(stderr, "recomp: %u lifted functions, image %s mapped at 0x%08x, entry 0x%08x\n", rt_nfuncs, exe,
            g_image.base, g_image.entry);
    rt_call(c, g_image.entry);

    if (c->eip != GUEST_EXIT_ADDR)
        rt_fatal(c, 4, "entry point returned to 0x%08x instead of the exit address", c->eip);
    fprintf(stderr, "\nguest entry point returned, eax=%u\n", EAX);
    return (int)(EAX & 0xFF);
}
