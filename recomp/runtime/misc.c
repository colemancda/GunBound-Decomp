/* Modules (LoadLibrary/GetProcAddress) and the small imports that belong nowhere else. */
#define _GNU_SOURCE
#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

#include "com.h"
#include "rt.h"

/* ----------------------------------------------------------------- modules
 * A module handle is a fake address; its exports are whatever handlers the
 * runtime has for that DLL name. System DLLs are always "loaded". */
typedef struct Module {
    const char *name;
    int system; /* part of every process: GetModuleHandle finds it without LoadLibrary */
    int loaded;
} Module;

static Module modules[] = {
    {"kernel32.dll", 1, 0}, {"user32.dll", 1, 0},  {"gdi32.dll", 1, 0},    {"advapi32.dll", 1, 0},
    {"ntdll.dll", 1, 0},    {"ws2_32.dll", 1, 0},  {"winmm.dll", 1, 0},    {"imm32.dll", 1, 0},
    {"ole32.dll", 1, 0},    {"oleaut32.dll", 1, 0}, {"shell32.dll", 1, 0}, {"ddraw.dll", 0, 0},
    {"dsound.dll", 0, 0},   {"dinput8.dll", 0, 0},
};
#define MODULE_BASE 0x70000000u
#define MODULE_STEP 0x00100000u

static int module_index(const char *path) {
    const char *base = strrchr(path, '\\');
    const char *fs = strrchr(path, '/');
    if (fs > base) base = fs;
    base = base ? base + 1 : path;
    char name[64];
    snprintf(name, sizeof name, "%s%s", base, strchr(base, '.') ? "" : ".dll");
    for (size_t i = 0; i < RT_COUNTOF(modules); i++)
        if (!strcasecmp(modules[i].name, name)) return (int)i;
    return -1;
}

static const Module *module_of(uint32_t h) {
    uint32_t i = (h - MODULE_BASE) / MODULE_STEP;
    if (h < MODULE_BASE || (h - MODULE_BASE) % MODULE_STEP || i >= RT_COUNTOF(modules)) return NULL;
    return &modules[i];
}

H(k32_GetModuleHandleA) {
    if (!a[0]) return g_image.base;
    const char *name = rt_gstr(a[0]);
    const char *base = strrchr(name, '\\');
    base = base ? base + 1 : name;
    const char *self = strrchr(g_image.guest_path, '\\') + 1;
    if (!strcasecmp(base, self)) return g_image.base;
    int i = module_index(name);
    if (i >= 0 && (modules[i].system || modules[i].loaded)) return MODULE_BASE + (uint32_t)i * MODULE_STEP;
    rt_set_last_error(c, 126); /* ERROR_MOD_NOT_FOUND */
    return 0;
}

H(k32_LoadLibraryA) {
    const char *name = rt_gstr(a[0]);
    int i = module_index(name);
    if (i < 0) {
        rt_log("recomp: LoadLibraryA(\"%s\"): no such module in the runtime\n", name);
        rt_set_last_error(c, 126);
        return 0;
    }
    modules[i].loaded = 1;
    if (g_opt.verbose || g_trace_imports) rt_log("[module] \"%s\" loaded\n", name);
    return MODULE_BASE + (uint32_t)i * MODULE_STEP;
}

H(k32_FreeLibrary) { UNUSED; return 1; }

H(k32_GetProcAddress) {
    const Module *m = module_of(a[0]);
    if (!m && a[0] == g_image.base) {
        rt_set_last_error(c, 127);
        return 0;
    }
    if (!m) {
        rt_set_last_error(c, 6);
        return 0;
    }
    if (a[1] < 0x10000) {
        rt_log("recomp: GetProcAddress(%s, ordinal %u) is not supported\n", m->name, a[1]);
        rt_set_last_error(c, 127);
        return 0;
    }
    const char *name = rt_gstr(a[1]);
    const ImportDef *def = rt_find_import_def(m->name, name);
    if (!def) {
        /* The C run-time probes kernel32 for optional functions and copes without them. */
        if (g_opt.verbose || g_trace_imports || !m->system)
            rt_log("recomp: GetProcAddress(%s, \"%s\"): not provided\n", m->name, name);
        rt_set_last_error(c, 127); /* ERROR_PROC_NOT_FOUND */
        return 0;
    }
    if (def->is_cdecl) {
        rt_log("recomp: GetProcAddress(%s, \"%s\"): cdecl functions cannot be looked up by name\n", m->name, name);
        rt_set_last_error(c, 127);
        return 0;
    }
    return rt_host_fn(m->name, name, def->fn, def->nargs);
}

/* ------------------------------------------------------------ winmm, ole32 */
H(winmm_timeGetTime) { UNUSED; return (uint32_t)(rt_mono_ns() / 1000000ull); }
H(ole_CoInitialize) { UNUSED; return S_OK; }
H(ole_CoUninitialize) { UNUSED; return 0; }

/* VariantClear(VARIANT *): only plain values are expected; anything holding a
 * reference would need releasing, which is reported. */
H(oleaut_VariantClear) {
    UNUSED;
    uint16_t vt = ld16(a[0]);
    if (vt == 8 || vt == 9 || vt == 13 || (vt & 0x2000))
        rt_log("recomp: VariantClear of a reference type (vt %#x): the reference is not released\n", vt);
    memset(G(a[0]), 0, 16);
    return S_OK;
}

/* ShellExecuteA(hwnd, verb, file, parameters, directory, show) */
H(shell_ShellExecuteA) {
    UNUSED;
    rt_log("recomp: ShellExecuteA(%s, \"%s\", \"%s\") is not carried out\n", a[1] ? rt_gstr(a[1]) : "open",
           rt_gstr(a[2]), a[3] ? rt_gstr(a[3]) : "");
    return 2; /* ERROR_FILE_NOT_FOUND: values of 32 or less are failures */
}

/* ----------------------------------------------------------------- kernel32 */
static uint32_t copy_name(CPU *c, const uint32_t *a, const char *name) {
    uint32_t n = (uint32_t)strlen(name);
    if (!a[1]) return 0;
    if (ld32(a[1]) <= n) {
        st32(a[1], n + 1);
        rt_set_last_error(c, 122); /* ERROR_INSUFFICIENT_BUFFER */
        return 0;
    }
    memcpy(G(a[0]), name, n + 1);
    return n;
}

H(k32_GetComputerNameA) {
    uint32_t n = copy_name(c, a, "RECOMP");
    if (n) st32(a[1], n);
    return n != 0;
}

H(adv_GetUserNameA) {
    uint32_t n = copy_name(c, a, "player");
    if (n) st32(a[1], n + 1);
    return n != 0;
}

/* VirtualQuery(address, MEMORY_BASIC_INFORMATION *, length) */
H(k32_VirtualQuery) {
    UNUSED;
    if (a[2] < 28) return 0;
    uint32_t base, size, page = a[0] & ~0xFFFu;
    memset(G(a[1]), 0, 28);
    st32(a[1], page);
    if (rt_vquery(a[0], &base, &size)) {
        st32(a[1] + 4, base);                    /* AllocationBase */
        st32(a[1] + 8, 4);                       /* AllocationProtect: PAGE_READWRITE */
        st32(a[1] + 12, base + size - page);     /* RegionSize */
        st32(a[1] + 16, 0x1000);                 /* MEM_COMMIT */
        st32(a[1] + 20, a[0] >= rt_text_base && a[0] - rt_text_base < rt_text_size ? 0x20 : 4);
        st32(a[1] + 24, a[0] >= g_image.base && a[0] - g_image.base < g_image.size ? 0x1000000 : 0x20000);
    } else {
        st32(a[1] + 12, 0x10000);
        st32(a[1] + 16, 0x10000); /* MEM_FREE */
        st32(a[1] + 20, 1);       /* PAGE_NOACCESS */
    }
    return 28;
}

H(k32_LocalFree) { UNUSED; return 0; }

/* GetTimeZoneInformation(TIME_ZONE_INFORMATION *) */
H(k32_GetTimeZoneInformation) {
    UNUSED;
    time_t now = time(NULL);
    struct tm tm;
    localtime_r(&now, &tm);
    memset(G(a[0]), 0, 172);
    st32(a[0], (uint32_t)-((tm.tm_gmtoff - (tm.tm_isdst > 0 ? 3600 : 0)) / 60)); /* Bias: UTC - local standard time */
    st32(a[0] + 168, (uint32_t)-60);                                             /* DaylightBias */
    return tm.tm_isdst > 0 ? 2 : 1; /* TIME_ZONE_ID_DAYLIGHT / STANDARD */
}

static int cmp_chars(unsigned x, unsigned y, uint32_t flags) {
    if (flags & 1) { /* NORM_IGNORECASE */
        if (x < 0x80) x = (unsigned)tolower((int)x);
        if (y < 0x80) y = (unsigned)tolower((int)y);
    }
    return (int)x - (int)y;
}

/* CompareString(locale, flags, s1, n1, s2, n2): 1 less, 2 equal, 3 greater. */
static uint32_t compare_string(const uint32_t *a, int wide) {
    int32_t n1 = (int32_t)a[3], n2 = (int32_t)a[5];
    uint32_t i = 0;
    for (;; i++) {
        unsigned x = wide ? ld16(a[2] + 2 * i) : ld8(a[2] + i);
        unsigned y = wide ? ld16(a[4] + 2 * i) : ld8(a[4] + i);
        int e1 = n1 < 0 ? x == 0 : (int32_t)i >= n1;
        int e2 = n2 < 0 ? y == 0 : (int32_t)i >= n2;
        if (e1 || e2) return e1 && e2 ? 2 : e1 ? 1 : 3;
        int d = cmp_chars(x, y, a[1]);
        if (d) return d < 0 ? 1 : 3;
    }
}

H(k32_CompareStringA) { UNUSED; return compare_string(a, 0); }
H(k32_CompareStringW) { UNUSED; return compare_string(a, 1); }

/* The C run-time keeps its own copy of the environment; the process block is not updated. */
H(k32_SetEnvironmentVariableA) { UNUSED; return 1; }

/* CreateProcessA(application, commandLine, ...): there are no other programs to run. */
H(k32_CreateProcessA) {
    rt_log("recomp: CreateProcessA(\"%s\", \"%s\") refused: no such program\n", a[0] ? rt_gstr(a[0]) : "",
           a[1] ? rt_gstr(a[1]) : "");
    rt_set_last_error(c, 2);
    return 0;
}

static const ImportDef defs[] = {
    {"kernel32.dll", "GetModuleHandleA", k32_GetModuleHandleA, 1, 0},
    {"kernel32.dll", "LoadLibraryA", k32_LoadLibraryA, 1, 0},
    {"kernel32.dll", "FreeLibrary", k32_FreeLibrary, 1, 0},
    {"kernel32.dll", "GetProcAddress", k32_GetProcAddress, 2, 0},
    {"winmm.dll", "timeGetTime", winmm_timeGetTime, 0, 0},
    {"ole32.dll", "CoInitialize", ole_CoInitialize, 1, 0},
    {"ole32.dll", "CoUninitialize", ole_CoUninitialize, 0, 0},
    {"oleaut32.dll", "VariantClear", oleaut_VariantClear, 1, 0},
    {"shell32.dll", "ShellExecuteA", shell_ShellExecuteA, 6, 0},
    {"kernel32.dll", "GetComputerNameA", k32_GetComputerNameA, 2, 0},
    {"advapi32.dll", "GetUserNameA", adv_GetUserNameA, 2, 0},
    {"kernel32.dll", "VirtualQuery", k32_VirtualQuery, 3, 0},
    {"kernel32.dll", "LocalFree", k32_LocalFree, 1, 0},
    {"kernel32.dll", "GetTimeZoneInformation", k32_GetTimeZoneInformation, 1, 0},
    {"kernel32.dll", "CompareStringA", k32_CompareStringA, 6, 0},
    {"kernel32.dll", "CompareStringW", k32_CompareStringW, 6, 0},
    {"kernel32.dll", "SetEnvironmentVariableA", k32_SetEnvironmentVariableA, 2, 0},
    {"kernel32.dll", "CreateProcessA", k32_CreateProcessA, 10, 0},
};
RT_EXPORT_IMPORTS(rt_imports_misc, defs);
