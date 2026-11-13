/* Runtime-internal interface: guest memory layout, loader, dispatch, imports. */
#ifndef RECOMP_RT_H
#define RECOMP_RT_H

#include "cpu.h"

/* ---- tables emitted by the lifter (tables.c) ---- */
typedef struct RtFuncDesc {
    uint32_t addr;
    GuestFn fn;
    const char *name;
} RtFuncDesc;

extern const RtFuncDesc rt_funcs[];
extern const uint32_t rt_nfuncs;
extern const uint32_t rt_retsites[];
extern const uint32_t rt_nretsites;
extern const uint32_t rt_text_base, rt_text_size, rt_entry, rt_text_crc;
extern const uint32_t rt_patches[][2]; /* {address, value} words the loader rewrites */
extern const uint32_t rt_npatches;

/* ---- guest address space layout (all inside one GUEST_SIZE mapping) ---- */
#define GUEST_SIZE      0x40000000u /* 1 GiB */
#define GUEST_NULL_GUARD 0x00010000u
#define GUEST_SYS_BASE  0x00020000u /* PEB, TEB, command line, environment */
#define GUEST_SYS_SIZE  0x00010000u
#define GUEST_PEB       0x00020000u
#define GUEST_TEB       0x00021000u
#define GUEST_STR_BASE  0x00023000u /* bump area for process strings */
#define GUEST_STACK_LOW 0x00030000u
#define GUEST_STACK_TOP 0x00130000u /* 1 MiB main-thread stack, as on Windows XP */
#define GUEST_HEAP_BASE 0x01000000u
#define GUEST_HEAP_END  0x20000000u
#define GUEST_VA_BASE   0x20000000u /* VirtualAlloc arena */
#define GUEST_VA_END    0x3F000000u
#define GUEST_IMP_BASE  0x3FF00000u /* fake host-function entry points, 16 bytes apart */
#define GUEST_IMP_SIZE  0x00010000u
#define GUEST_EXIT_ADDR 0x3FFF0000u /* return address of the entry point */
#define GUEST_CB_RET    0x3FFF0010u /* return address of a host-to-guest call */
#define GUEST_THREAD_RET 0x3FFF0020u /* return address of a thread start routine */

#define TEB_LAST_ERROR  0x34u
#define TEB_TLS_SLOTS   0xE10u
#define TLS_SLOT_COUNT  64
#define TEB_SIZE        0x1000u

/* ---- memory (mem.c); the allocators are thread safe ---- */
void rt_mem_init(void);
void rt_mem_commit(uint32_t addr, uint32_t size); /* make [addr, addr+size) read/write */
uint32_t rt_sys_alloc(uint32_t size);              /* bump allocation in the system area */
uint32_t rt_sys_strdup(const char *s);

uint32_t rt_heap_alloc(uint32_t size, int zero);
void rt_heap_free(uint32_t p);
uint32_t rt_heap_realloc(uint32_t p, uint32_t size, int zero);
uint32_t rt_heap_size(uint32_t p);                 /* 0xFFFFFFFF if p is not a live block */

uint32_t rt_valloc(uint32_t addr, uint32_t size, uint32_t type, uint32_t protect);
int rt_vfree(uint32_t addr, uint32_t size, uint32_t type);
int rt_vquery(uint32_t addr, uint32_t *base, uint32_t *size); /* region containing addr; 0 if none */
int rt_guest_readable(uint32_t addr, uint32_t size);

/* ---- loader (loader.c) ---- */
typedef struct RtImage {
    uint32_t base, size, entry, headers_size, stack_reserve;
    uint32_t rsrc_rva, rsrc_size; /* resource directory */
    char path[512];      /* host path of the executable */
    char guest_path[260]; /* what GetModuleFileNameA reports */
} RtImage;
extern RtImage g_image;
void rt_load_pe(const char *path);

/* ---- host functions: imports, COM methods, GetProcAddress results (dispatch.c) ----
 * Every host-implemented entry point has a fake guest address in the import area.
 * A handler receives its arguments in a[] and returns the EAX value; the
 * dispatcher pops the arguments (stdcall) unless is_cdecl is set. */
typedef uint32_t (*ImportFn)(CPU *c, const uint32_t *a);
typedef struct ImportDef {
    const char *dll, *name;
    ImportFn fn;
    int nargs;     /* argument count (dwords) */
    int is_cdecl;  /* caller pops (wsprintfA) */
} ImportDef;
typedef struct Import {
    const char *dll, *name;
    ImportFn fn;
    int nargs, is_cdecl;
    uint32_t iat_va;
    uint64_t calls;
} Import;
#define RT_MAX_IMPORTS (GUEST_IMP_SIZE / 16)
extern Import g_imports[RT_MAX_IMPORTS];
extern uint32_t g_nimports;
const ImportDef *rt_find_import_def(const char *dll, const char *name);
uint32_t rt_register_import(const char *dll, const char *name, uint32_t iat_va); /* returns the fake address */
/* Fake address for a host function that is not in the import table. fn == NULL
 * makes a stub that stops with "UNIMPLEMENTED dll!name" when called. Repeated
 * calls with the same dll and name return the same address. */
uint32_t rt_host_fn(const char *dll, const char *name, ImportFn fn, int nargs);
void rt_import_call(CPU *c, uint32_t idx);

/* Handler tables, one per runtime source file. */
typedef struct ImportTable {
    const ImportDef *defs;
    unsigned count;
} ImportTable;
#define RT_COUNTOF(a) (sizeof(a) / sizeof((a)[0]))
#define RT_EXPORT_IMPORTS(sym, defs) const ImportTable sym = {defs, RT_COUNTOF(defs)}
extern const ImportTable rt_imports_kernel, rt_imports_thread, rt_imports_seh, rt_imports_user, rt_imports_file,
    rt_imports_registry, rt_imports_misc, rt_imports_winsock, rt_imports_ddraw, rt_imports_dinput, rt_imports_dsound;

#define H(name) static uint32_t name(CPU *c, const uint32_t *a)
#define UNUSED (void)c, (void)a

/* ---- host-to-guest calls (dispatch.c) ----
 * Calls the guest function fn with nargs dword arguments. Returns 1 when the
 * function returned normally, with its EAX in *result (if not NULL). Returns 0
 * when a non-local return (SEH unwind, C++ catch) passed through the call: the
 * guest stack was unwound past the host caller, which must return to the import
 * dispatcher at once without touching guest state. */
#define RT_STDCALL 0
#define RT_CDECL 1
int rt_call_guest(CPU *c, uint32_t fn, int conv, int nargs, const uint32_t *args, uint32_t *result);

/* ---- dispatch / diagnostics (dispatch.c) ---- */
extern int g_trace_imports;
CPU *rt_cpu(void);          /* the calling host thread's guest CPU (NULL outside guest threads) */
void rt_set_cpu(CPU *c);
void rt_build_ftab(void);
const char *rt_func_name(uint32_t addr, uint32_t *start);
void rt_dump_state(CPU *c);
void rt_backtrace(CPU *c);
void rt_fatal(CPU *c, int code, const char *fmt, ...) __attribute__((noreturn, format(printf, 3, 4)));
void rt_install_fault_handler(void); /* call once on every host thread that runs guest code */
void rt_print_import_stats(void);
void rt_audio_report(void);          /* dsound.c: how much was mixed, and finish the WAV file */
void rt_profile_start(void);         /* profile.c: --profile */
void rt_profile_write(void);
/* login.c: the 96-digit session token for --login; 0 (after a message) if it cannot be made */
int rt_login_token(const char *user, const char *password, const char *key_file, char token[97]);
void rt_exit(int code) __attribute__((noreturn)); /* leave the process from any thread */
void rt_log(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

/* ---- threads, handles and waitable objects (thread.c) ---- */
typedef struct RtWaitable RtWaitable;
typedef struct RtThread {
    CPU cpu;
    uint32_t tid, teb, stack_low, stack_top;
    uint32_t start, param;
    RtWaitable *done; /* signalled when the thread has exited */
    void *msgq;       /* user32 message queue, created on demand (user32.c) */
    int is_main;
} RtThread;
static inline RtThread *rt_thread_of(CPU *c) { return (RtThread *)c->thread; }
RtThread *rt_thread_init_main(void);
void rt_teb_init(uint32_t teb, uint32_t stack_low, uint32_t stack_top, uint32_t tid);

enum { RT_H_FREE = 0, RT_H_WAITABLE, RT_H_FILE, RT_H_FIND, RT_H_OTHER };
uint32_t rt_handle_alloc(int type, void *obj, void (*close)(void *obj));
void *rt_handle_get(uint32_t h, int type); /* NULL when h is not a live handle of that type */
int rt_handle_close(uint32_t h);

enum { RT_W_EVENT = 1, RT_W_MUTEX, RT_W_THREAD, RT_W_PROCESS };
RtWaitable *rt_waitable_new(int kind, int manual_reset, int signaled);
void rt_waitable_signal(RtWaitable *w);
void rt_waitable_reset(RtWaitable *w);
void rt_waitable_ref(RtWaitable *w);
void rt_waitable_unref(void *w);
void rt_waitable_set_exit_code(RtWaitable *w, uint32_t code);

static inline void rt_set_last_error(CPU *c, uint32_t e) { st32(c->fs_base + TEB_LAST_ERROR, e); }
static inline const char *rt_gstr(uint32_t a) { return a ? (const char *)G(a) : "(null)"; }
uint64_t rt_mono_ns(void);        /* the guest's monotonic clock */
uint64_t rt_host_ns(void);
/* --guest-cpu: the guest's threads all run on one CPU (see thread.c). */
void rt_affinity_init(void);        /* once, on the main thread, before any other thread exists */
void rt_affinity_host(int enter);   /* 1: lift the confinement while host threads are started; 0: restore it */        /* real time, also on the virtual clock */
void rt_sleep_ns(uint64_t ns);    /* let guest time pass on the calling thread */

/* ---- process state shared by import handlers ---- */
typedef struct RtProcess {
    uint32_t cmdline_a;      /* guest address of the ANSI command line */
    uint32_t env_a, env_w;   /* guest environment blocks */
    uint32_t process_heap;
} RtProcess;
extern RtProcess g_proc;

/* ---- run-time options (main.c) ---- */
typedef struct RtOptions {
    char exedir[512];      /* directory of the original executable */
    char gamedir[512];     /* host directory holding the game's files */
    char savedir[512];     /* where the guest's writes go; an overlay when it differs from gamedir */
    char regfile[512];     /* registry backing file */
    int headless;          /* no window; frames can still be dumped */
    int dump_frames[64];   /* 1-based presented frames to dump */
    int ndump_frames;
    int dump_every;        /* also dump every Nth frame, 0 = no */
    char dump_path[512];
    int exit_after_frame;  /* stop after this many presented frames, 0 = never */
    int scale;             /* window size as a multiple of the guest screen, 0 = automatic */
    int window_w, window_h; /* window size in pixels, 0 = from scale */
    int fullscreen;        /* start as a borderless full-screen window */
    int scale_mode;        /* RT_SCALE_*: how the picture is fitted into the window */
    int filter;            /* RT_FILTER_*: how it is sampled */
    int dump_window;       /* frame dumps also write what the window shows, after scaling */
    int verbose;           /* log window messages and COM calls */
    char input_script[16384]; /* synthetic input, see video.c */
    int virtual_clock;     /* guest time is a counter advanced by the main thread */
    int trace_net;         /* log every datagram and stream chunk sent or received */
    int no_sound;          /* DirectSoundCreate8 reports that there is no sound device */
    char dump_audio[512];  /* WAV file the mixed sound is written to instead of a device */
    char broker[160];      /* HOST[:PORT] written to the registry as the game's server (registry.c) */
    int pad;               /* game controllers are used (default) */
    int pad_virtual;       /* attach an SDL virtual controller for the input script to drive */
    int trace_input;       /* log controller, touch and key events on their way to the game */
    int guest_cpu;         /* CPU the guest's threads are confined to; -1 = not confined (thread.c) */
    char profile[512];     /* file the sampling profile is written to (profile.c) */
    char local_address[32]; /* IPv4 address sockets are bound to, "" = any (winsock.c) */
} RtOptions;
extern RtOptions g_opt;
enum { RT_SCALE_FIT = 0, RT_SCALE_INTEGER, RT_SCALE_STRETCH };
enum { RT_FILTER_SHARP = 0, RT_FILTER_NEAREST, RT_FILTER_LINEAR };

#endif
