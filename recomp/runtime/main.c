/* Entry point of the recompiled program: build the guest process and run it from the PE entry. */
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

#include "rt.h"

static void usage(const char *argv0) {
    fprintf(stderr,
            "usage: %s [options] [--] [guest command line arguments...]\n"
            "  --exe PATH          the original executable (default: $RECOMP_EXE, then ./GunBound.gme)\n"
            "  --gamedir DIR       directory with the game's files, the guest's C:\\GunBound\n"
            "                      (default: the directory of --exe)\n"
            "  --cmdline STRING    the guest command line, verbatim. The launcher starts the game\n"
            "                      with a command line that is only its 96-character session token.\n"
            "  --registry FILE     registry backing file (default: recomp-registry.txt in --gamedir)\n"
            "  --headless          do not open a window\n"
            "  --dump-frame N      write presented frame N (1 = first) as a PNG\n"
            "  --dump-path FILE    where --dump-frame writes (default: frame.png)\n"
            "  --frames N          exit after N presented frames\n"
            "  --scale N           window size as a multiple of 800x600 (default: 2 on a large display)\n"
            "  --fullscreen        full-screen window with the picture scaled to fit\n"
            "  --trace-imports     log every Win32 import call with its arguments and result\n"
            "  --verbose           log window messages, COM calls and file access\n",
            argv0);
}

static void build_process(int argc, char **argv, int first_guest_arg, const char *raw_cmdline) {
    /* Command line: quoted module path followed by the guest arguments, unless given verbatim. */
    char cmd[2048];
    if (raw_cmdline) {
        snprintf(cmd, sizeof cmd, "%s", raw_cmdline);
    } else {
        size_t n = (size_t)snprintf(cmd, sizeof cmd, "\"%s\"", g_image.guest_path);
        for (int i = first_guest_arg; i < argc && n < sizeof cmd; i++)
            n += (size_t)snprintf(cmd + n, sizeof cmd - n, " %s", argv[i]);
    }
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

    /* PEB: only the fields user-mode code commonly reads directly. The TEB is set up per thread. */
    st8(GUEST_PEB + 2, 0);                    /* BeingDebugged */
    st32(GUEST_PEB + 8, g_image.base);        /* ImageBaseAddress */
    st32(GUEST_PEB + 0x18, 0x00140000);       /* ProcessHeap */
}

int main(int argc, char **argv) {
    const char *exe = getenv("RECOMP_EXE");
    const char *raw_cmdline = NULL;
    int i = 1;
    snprintf(g_opt.dump_path, sizeof g_opt.dump_path, "frame.png");
    for (; i < argc; i++) {
        const char *o = argv[i];
        int has = i + 1 < argc;
        if (!strcmp(o, "--trace-imports")) g_trace_imports = 1;
        else if (!strcmp(o, "--verbose")) g_opt.verbose = 1;
        else if (!strcmp(o, "--headless")) g_opt.headless = 1;
        else if (!strcmp(o, "--exe") && has) exe = argv[++i];
        else if (!strcmp(o, "--gamedir") && has) snprintf(g_opt.gamedir, sizeof g_opt.gamedir, "%s", argv[++i]);
        else if (!strcmp(o, "--registry") && has) snprintf(g_opt.regfile, sizeof g_opt.regfile, "%s", argv[++i]);
        else if (!strcmp(o, "--cmdline") && has) raw_cmdline = argv[++i];
        else if (!strcmp(o, "--dump-frame") && has) g_opt.dump_frame = atoi(argv[++i]);
        else if (!strcmp(o, "--dump-path") && has) snprintf(g_opt.dump_path, sizeof g_opt.dump_path, "%s", argv[++i]);
        else if (!strcmp(o, "--frames") && has) g_opt.exit_after_frame = atoi(argv[++i]);
        else if (!strcmp(o, "--scale") && has) g_opt.scale = atoi(argv[++i]);
        else if (!strcmp(o, "--fullscreen")) g_opt.fullscreen = 1;
        else if (!strcmp(o, "--help") || !strcmp(o, "-h")) { usage(argv[0]); return 0; }
        else if (!strcmp(o, "--")) { i++; break; }
        else if (o[0] == '-' && o[1] == '-') { usage(argv[0]); return 2; }
        else break;
    }
    if (!exe) exe = "GunBound.gme";
    if (!g_opt.gamedir[0]) {
        char tmp[512];
        snprintf(tmp, sizeof tmp, "%s", exe);
        snprintf(g_opt.gamedir, sizeof g_opt.gamedir, "%s", dirname(tmp));
    }
    if (!g_opt.regfile[0]) {
        size_t n = strlen(g_opt.gamedir);
        snprintf(g_opt.regfile, sizeof g_opt.regfile, "%.*s/recomp-registry.txt", (int)(n > 480 ? 480 : n),
                 g_opt.gamedir);
    }

    setvbuf(stderr, NULL, _IOLBF, 0);
    rt_mem_init();
    snprintf(g_image.guest_path, sizeof g_image.guest_path, "C:\\GunBound\\GunBound.gme");
    rt_build_ftab();
    rt_load_pe(exe);
    build_process(argc, argv, i, raw_cmdline);
    rt_install_fault_handler();

    RtThread *th = rt_thread_init_main();
    CPU *c = &th->cpu;
    ESP = GUEST_STACK_TOP - 0x40;
    EBX = GUEST_PEB;
    PUSH32(GUEST_EXIT_ADDR);
    uint32_t slot = ESP;

    fprintf(stderr, "recomp: %u lifted functions, image %s mapped at 0x%08x, entry 0x%08x\n", rt_nfuncs, exe,
            g_image.base, g_image.entry);
    rt_call(c, g_image.entry);

    if (c->eip != GUEST_EXIT_ADDR || c->ret_sp != slot)
        rt_fatal(c, 4, "entry point returned to 0x%08x instead of the exit address",
                 c->eip == RT_NL_PENDING ? c->nl_eip : c->eip);
    rt_log("\nguest entry point returned, eax=%u\n", EAX);
    rt_print_import_stats();
    rt_exit((int)(EAX & 0xFF));
}
