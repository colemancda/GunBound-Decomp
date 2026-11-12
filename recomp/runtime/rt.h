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
#define GUEST_IMP_BASE  0x3FF00000u /* fake import entry points, 16 bytes apart */
#define GUEST_IMP_SIZE  0x00010000u
#define GUEST_EXIT_ADDR 0x3FFF0000u /* return address of the entry point */

#define TEB_TLS_SLOTS   0xE10u
#define TLS_SLOT_COUNT  64

/* ---- memory (mem.c) ---- */
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
int rt_guest_readable(uint32_t addr, uint32_t size);

/* ---- loader (loader.c) ---- */
typedef struct RtImage {
    uint32_t base, size, entry, headers_size, stack_reserve;
    char path[512];      /* host path of the executable */
    char guest_path[260]; /* what GetModuleFileNameA reports */
} RtImage;
extern RtImage g_image;
void rt_load_pe(const char *path);

/* ---- imports (imports.c, dispatch.c) ---- */
typedef uint32_t (*ImportFn)(CPU *c, const uint32_t *a);
typedef struct ImportDef {
    const char *dll, *name;
    ImportFn fn;
    int nargs;     /* stdcall argument count (dwords) */
    int is_cdecl;  /* caller pops (wsprintfA) */
} ImportDef;
typedef struct Import {
    const char *dll, *name;
    ImportFn fn;
    int nargs, is_cdecl;
    uint32_t iat_va;
    uint64_t calls;
} Import;
extern Import *g_imports;
extern uint32_t g_nimports;
const ImportDef *rt_find_import_def(const char *dll, const char *name);
uint32_t rt_register_import(const char *dll, const char *name, uint32_t iat_va); /* returns fake address */
void rt_import_call(CPU *c, uint32_t idx);

/* ---- dispatch / diagnostics (dispatch.c) ---- */
extern int g_trace_imports;
extern CPU *g_cpu; /* the (single, for now) guest thread */
void rt_build_ftab(void);
const char *rt_func_name(uint32_t addr, uint32_t *start);
void rt_dump_state(CPU *c);
void rt_backtrace(CPU *c);
void rt_fatal(CPU *c, int code, const char *fmt, ...) __attribute__((noreturn, format(printf, 3, 4)));
void rt_install_fault_handler(void);
void rt_print_import_stats(void);

/* ---- process state shared by import handlers ---- */
typedef struct RtProcess {
    uint32_t cmdline_a;      /* guest address of the ANSI command line */
    uint32_t env_a, env_w;   /* guest environment blocks */
    uint32_t last_error_dummy;
    uint32_t process_heap;
} RtProcess;
extern RtProcess g_proc;

#endif
