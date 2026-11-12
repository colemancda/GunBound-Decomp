/* Win32 import handlers: the subset that MSVC CRT startup needs.
 *
 * A handler receives its stdcall arguments in a[] and returns the EAX value; the
 * dispatcher pops the arguments. Imports without a handler stop the program with
 * a diagnostic (see rt_import_call).
 */
#define _GNU_SOURCE
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

#include "rt.h"

RtProcess g_proc;

#define INVALID_HANDLE 0xFFFFFFFFu
#define H_STDIN 0x00000010u
#define H_STDOUT 0x00000014u
#define H_STDERR 0x00000018u
#define H_PROCESS_HEAP 0x00140000u
#define H_FAKE_MODULE 0x7C800000u
#define H_GENERIC 0x00000100u

#define set_last_error rt_set_last_error
#define gstr rt_gstr

/* ------------------------------------------------------------ version */
H(k32_GetVersion) { UNUSED; return 0x0A280105u; /* Windows XP 5.1 build 2600 */ }

H(k32_GetVersionExA) {
    UNUSED;
    uint32_t p = a[0];
    uint32_t size = ld32(p);
    if (size < 148) return 0;
    st32(p + 4, 5);
    st32(p + 8, 1);
    st32(p + 12, 2600);
    st32(p + 16, 2); /* VER_PLATFORM_WIN32_NT */
    memset(G(p + 20), 0, 128);
    strcpy((char *)G(p + 20), "Service Pack 2");
    if (size >= 156) {
        st16(p + 148, 2); /* wServicePackMajor */
        st16(p + 150, 0);
        st16(p + 152, 0x100); /* VER_SUITE_SINGLEUSERTS */
        st8(p + 154, 1);      /* VER_NT_WORKSTATION */
        st8(p + 155, 0);
    }
    return 1;
}

/* ------------------------------------------------------------ modules */
H(k32_GetModuleHandleA) {
    UNUSED;
    if (!a[0]) return g_image.base;
    if (g_trace_imports) fprintf(stderr, " {\"%s\"}", gstr(a[0]));
    const char *base = strrchr(gstr(a[0]), '\\');
    base = base ? base + 1 : gstr(a[0]);
    const char *self = strrchr(g_image.guest_path, '\\') + 1;
    if (!strcasecmp(base, self)) return g_image.base;
    if (!strncasecmp(base, "kernel32", 8)) return H_FAKE_MODULE;
    set_last_error(c, 126); /* ERROR_MOD_NOT_FOUND */
    return 0;
}

H(k32_GetModuleFileNameA) {
    UNUSED;
    uint32_t n = (uint32_t)strlen(g_image.guest_path);
    if (a[2] == 0) return 0;
    if (n >= a[2]) n = a[2] - 1;
    memcpy(G(a[1]), g_image.guest_path, n);
    st8(a[1] + n, 0);
    return n;
}

/* No other modules exist yet: every lookup fails, which sends the CRT down its fallback paths. */
H(k32_GetProcAddress) {
    UNUSED;
    if (g_trace_imports) {
        if (a[1] > 0xFFFF) fprintf(stderr, " {\"%s\"}", gstr(a[1]));
        else fprintf(stderr, " {#%u}", a[1]);
    }
    set_last_error(c, 127); /* ERROR_PROC_NOT_FOUND */
    return 0;
}

H(k32_LoadLibraryA) {
    UNUSED;
    if (g_trace_imports) fprintf(stderr, " {\"%s\"}", gstr(a[0]));
    set_last_error(c, 126);
    return 0;
}

H(k32_FreeLibrary) { UNUSED; return 1; }

/* -------------------------------------------------- process parameters */
H(k32_GetCommandLineA) { UNUSED; return g_proc.cmdline_a; }

H(k32_GetStartupInfoA) {
    UNUSED;
    memset(G(a[0]), 0, 68);
    st32(a[0], 68);
    st32(a[0] + 56, H_STDIN);
    st32(a[0] + 60, H_STDOUT);
    st32(a[0] + 64, H_STDERR);
    return 0;
}

H(k32_GetEnvironmentStringsW) { UNUSED; return g_proc.env_w; }
H(k32_GetEnvironmentStrings) { UNUSED; return g_proc.env_a; }
H(k32_FreeEnvironmentStrings) { UNUSED; return 1; }

H(k32_GetStdHandle) {
    UNUSED;
    switch (a[0]) {
    case 0xFFFFFFF6u: return H_STDIN;
    case 0xFFFFFFF5u: return H_STDOUT;
    case 0xFFFFFFF4u: return H_STDERR;
    }
    set_last_error(c, 6);
    return INVALID_HANDLE;
}

H(k32_SetStdHandle) { UNUSED; return 1; }

H(k32_GetFileType) {
    UNUSED;
    if (a[0] == H_STDIN || a[0] == H_STDOUT || a[0] == H_STDERR) return 2; /* FILE_TYPE_CHAR */
    return 0;
}

H(k32_GetCurrentProcessId) { UNUSED; return 0x00000A28u; }
H(k32_GetCurrentProcess) { UNUSED; return 0xFFFFFFFFu; }

H(k32_GetLastError) { UNUSED; return ld32(c->fs_base + TEB_LAST_ERROR); }
H(k32_SetLastError) { set_last_error(c, a[0]); return 0; }

H(k32_ExitProcess) {
    UNUSED;
    fflush(stdout);
    rt_log("\nguest called ExitProcess(%u)\n", a[0]);
    rt_print_import_stats();
    rt_exit((int)(a[0] & 0xFF));
}

H(k32_TerminateProcess) {
    UNUSED;
    fflush(stdout);
    rt_log("\nguest called TerminateProcess(%#x, %u)\n", a[0], a[1]);
    rt_print_import_stats();
    rt_exit((int)(a[1] & 0xFF));
}

/* --------------------------------------------------------------- heap */
H(k32_HeapCreate) { UNUSED; return H_PROCESS_HEAP + 0x10000; }
H(k32_HeapDestroy) { UNUSED; return 1; }
H(k32_GetProcessHeap) { UNUSED; return H_PROCESS_HEAP; }

H(k32_HeapAlloc) {
    UNUSED;
    uint32_t p = rt_heap_alloc(a[2], (a[1] & 8) != 0);
    if (!p) set_last_error(c, 8); /* ERROR_NOT_ENOUGH_MEMORY */
    return p;
}

H(k32_HeapFree) {
    UNUSED;
    rt_heap_free(a[2]);
    return 1;
}

H(k32_HeapReAlloc) {
    UNUSED;
    uint32_t p = rt_heap_realloc(a[2], a[3], (a[1] & 8) != 0);
    if (!p) set_last_error(c, 8);
    return p;
}

H(k32_HeapSize) { UNUSED; return rt_heap_size(a[2]); }

H(k32_VirtualAlloc) {
    UNUSED;
    uint32_t p = rt_valloc(a[0], a[1], a[2], a[3]);
    if (!p) set_last_error(c, 8);
    return p;
}

H(k32_VirtualFree) { UNUSED; return (uint32_t)rt_vfree(a[0], a[1], a[2]); }

H(k32_VirtualProtect) {
    UNUSED;
    if (a[3]) st32(a[3], 4); /* old protection: PAGE_READWRITE */
    return 1;
}

H(k32_IsBadReadPtr) { UNUSED; return !rt_guest_readable(a[0], a[1] ? a[1] : 1); }
H(k32_IsBadWritePtr) { UNUSED; return !rt_guest_readable(a[0], a[1] ? a[1] : 1); }
H(k32_IsBadCodePtr) { UNUSED; return !(a[0] >= rt_text_base && a[0] - rt_text_base < rt_text_size); }

/* --------------------------------------------------------------- time */
#define mono_ns rt_mono_ns

H(k32_GetTickCount) { UNUSED; return (uint32_t)(mono_ns() / 1000000ull); }

H(k32_QueryPerformanceCounter) {
    UNUSED;
    st64(a[0], mono_ns() / 100); /* 10 MHz counter */
    return 1;
}

H(k32_GetSystemTimeAsFileTime) {
    UNUSED;
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    uint64_t ft = ((uint64_t)ts.tv_sec + 11644473600ull) * 10000000ull + (uint64_t)ts.tv_nsec / 100;
    st64(a[0], ft);
    return 0;
}

H(k32_GetLocalTime) {
    UNUSED;
    struct timespec ts;
    struct tm tm;
    clock_gettime(CLOCK_REALTIME, &ts);
    localtime_r(&ts.tv_sec, &tm);
    st16(a[0], (uint16_t)(tm.tm_year + 1900));
    st16(a[0] + 2, (uint16_t)(tm.tm_mon + 1));
    st16(a[0] + 4, (uint16_t)tm.tm_wday);
    st16(a[0] + 6, (uint16_t)tm.tm_mday);
    st16(a[0] + 8, (uint16_t)tm.tm_hour);
    st16(a[0] + 10, (uint16_t)tm.tm_min);
    st16(a[0] + 12, (uint16_t)tm.tm_sec);
    st16(a[0] + 14, (uint16_t)(ts.tv_nsec / 1000000));
    return 0;
}

H(k32_GetSystemInfo) {
    UNUSED;
    uint32_t p = a[0];
    memset(G(p), 0, 36);
    st32(p + 4, 0x1000);       /* dwPageSize */
    st32(p + 8, 0x00010000);   /* lpMinimumApplicationAddress */
    st32(p + 12, 0x7FFEFFFF);  /* lpMaximumApplicationAddress */
    st32(p + 16, 1);           /* dwActiveProcessorMask */
    st32(p + 20, 1);           /* dwNumberOfProcessors */
    st32(p + 24, 586);         /* dwProcessorType */
    st32(p + 28, 0x10000);     /* dwAllocationGranularity */
    st16(p + 32, 6);           /* wProcessorLevel */
    st16(p + 34, 0x0102);      /* wProcessorRevision */
    return 0;
}

/* ------------------------------------------------- code pages / strings
 * Single-byte Latin-1 semantics throughout (ACP 1252): enough for the CRT's
 * startup conversions; real code-page handling comes with the text milestone. */
H(k32_GetACP) { UNUSED; return 1252; }
H(k32_GetOEMCP) { UNUSED; return 437; }
H(k32_GetThreadLocale) { UNUSED; return 0x0409; }

H(k32_GetCPInfo) {
    UNUSED;
    memset(G(a[1]), 0, 18);
    st32(a[1], 1);     /* MaxCharSize */
    st8(a[1] + 4, '?'); /* DefaultChar */
    return 1;
}

H(k32_WideCharToMultiByte) {
    UNUSED;
    uint32_t src = a[2], dst = a[4];
    int32_t n = (int32_t)a[3];
    uint32_t dstn = a[5];
    uint32_t len = 0;
    if (n < 0) {
        while (ld16(src + 2 * len)) len++;
        len++; /* include the terminator */
    } else {
        len = (uint32_t)n;
    }
    if (dstn == 0) return len;
    if (len > dstn) {
        set_last_error(c, 122); /* ERROR_INSUFFICIENT_BUFFER */
        return 0;
    }
    for (uint32_t i = 0; i < len; i++) {
        uint16_t w = ld16(src + 2 * i);
        st8(dst + i, w < 0x100 ? (uint8_t)w : '?');
    }
    return len;
}

H(k32_MultiByteToWideChar) {
    UNUSED;
    uint32_t src = a[2], dst = a[4];
    int32_t n = (int32_t)a[3];
    uint32_t dstn = a[5];
    uint32_t len = n < 0 ? (uint32_t)strlen((const char *)G(src)) + 1 : (uint32_t)n;
    if (dstn == 0) return len;
    if (len > dstn) {
        set_last_error(c, 122);
        return 0;
    }
    for (uint32_t i = 0; i < len; i++) st16(dst + 2 * i, ld8(src + i));
    return len;
}

/* CT_CTYPE1 classification bits for a Latin-1 character. */
static uint16_t ctype1(unsigned ch) {
    uint16_t t = 0;
    if (ch < 0x80) {
        if (isupper(ch)) t |= 0x001;
        if (islower(ch)) t |= 0x002;
        if (isdigit(ch)) t |= 0x004;
        if (isspace(ch)) t |= 0x008;
        if (ispunct(ch)) t |= 0x010;
        if (iscntrl(ch)) t |= 0x020;
        if (ch == ' ' || ch == '\t') t |= 0x040;
        if (isxdigit(ch)) t |= 0x080;
        if (isalpha(ch)) t |= 0x100;
    } else if (ch < 0xA0) {
        t = 0x020;
    } else if (ch == 0xA0) {
        t = 0x008 | 0x040;
    } else if (ch >= 0xC0 && ch != 0xD7 && ch != 0xF7 && ch < 0x100) {
        t = 0x100 | (ch >= 0xDF ? 0x002 : 0x001);
    } else if (ch < 0x100) {
        t = 0x010;
    }
    return t;
}

static uint32_t get_string_type(uint32_t type, uint32_t src, int32_t n, uint32_t out, int wide) {
    if (type != 1) { /* only CT_CTYPE1 */
        return 0;
    }
    uint32_t len;
    if (n < 0) {
        len = 0;
        while (wide ? ld16(src + 2 * len) : ld8(src + len)) len++;
        len++;
    } else {
        len = (uint32_t)n;
    }
    for (uint32_t i = 0; i < len; i++) {
        unsigned ch = wide ? ld16(src + 2 * i) : ld8(src + i);
        st16(out + 2 * i, ctype1(ch));
    }
    return 1;
}

H(k32_GetStringTypeW) { UNUSED; return get_string_type(a[0], a[1], (int32_t)a[2], a[3], 1); }
H(k32_GetStringTypeA) { UNUSED; return get_string_type(a[1], a[2], (int32_t)a[3], a[4], 0); }

static unsigned map_char(unsigned ch, uint32_t flags) {
    int latin = (ch >= 0xC0 && ch <= 0xDE && ch != 0xD7) || (ch >= 0xE0 && ch <= 0xFE && ch != 0xF7);
    if (flags & 0x100) { /* LCMAP_LOWERCASE */
        if (ch < 0x80) return (unsigned)tolower((int)ch);
        if (latin && ch < 0xE0) return ch + 0x20;
    } else if (flags & 0x200) { /* LCMAP_UPPERCASE */
        if (ch < 0x80) return (unsigned)toupper((int)ch);
        if (latin && ch >= 0xE0) return ch - 0x20;
    }
    return ch;
}

static uint32_t lcmap(CPU *c, const uint32_t *a, int wide) {
    uint32_t flags = a[1], src = a[2], dst = a[4], dstn = a[5];
    int32_t n = (int32_t)a[3];
    uint32_t len;
    if (flags & 0x400) { /* LCMAP_SORTKEY is not supported */
        set_last_error(c, 87);
        return 0;
    }
    if (n < 0) {
        len = 0;
        while (wide ? ld16(src + 2 * len) : ld8(src + len)) len++;
        len++;
    } else {
        len = (uint32_t)n;
    }
    if (dstn == 0) return len;
    if (len > dstn) {
        set_last_error(c, 122);
        return 0;
    }
    for (uint32_t i = 0; i < len; i++) {
        if (wide) st16(dst + 2 * i, (uint16_t)map_char(ld16(src + 2 * i), flags));
        else st8(dst + i, (uint8_t)map_char(ld8(src + i), flags));
    }
    return len;
}

H(k32_LCMapStringW) { return lcmap(c, a, 1); }
H(k32_LCMapStringA) { return lcmap(c, a, 0); }

H(k32_lstrlenA) { UNUSED; return a[0] ? (uint32_t)strlen((const char *)G(a[0])) : 0; }
H(k32_lstrcmpA) { UNUSED; int r = strcmp(gstr(a[0]), gstr(a[1])); return (uint32_t)(r < 0 ? -1 : r > 0); }
H(k32_lstrcatA) { UNUSED; strcat((char *)G(a[0]), (const char *)G(a[1])); return a[0]; }

/* LockResource and SetHandleCount are the same "return the argument" routine in NT's
 * kernel32, and the import rebuilder that produced this dump named both IAT slots
 * LockResource. The slot the CRT's _ioinit calls is really SetHandleCount. */
H(k32_LockResource) { UNUSED; return a[0]; }

/* -------------------------------------------------------------- table */
static const ImportDef defs[] = {
    {"kernel32.dll", "GetVersion", k32_GetVersion, 0, 0},
    {"kernel32.dll", "GetVersionExA", k32_GetVersionExA, 1, 0},
    {"kernel32.dll", "GetModuleHandleA", k32_GetModuleHandleA, 1, 0},
    {"kernel32.dll", "GetModuleFileNameA", k32_GetModuleFileNameA, 3, 0},
    {"kernel32.dll", "GetProcAddress", k32_GetProcAddress, 2, 0},
    {"kernel32.dll", "LoadLibraryA", k32_LoadLibraryA, 1, 0},
    {"kernel32.dll", "FreeLibrary", k32_FreeLibrary, 1, 0},
    {"kernel32.dll", "GetCommandLineA", k32_GetCommandLineA, 0, 0},
    {"kernel32.dll", "GetStartupInfoA", k32_GetStartupInfoA, 1, 0},
    {"kernel32.dll", "GetEnvironmentStringsW", k32_GetEnvironmentStringsW, 0, 0},
    {"kernel32.dll", "GetEnvironmentStrings", k32_GetEnvironmentStrings, 0, 0},
    {"kernel32.dll", "FreeEnvironmentStringsW", k32_FreeEnvironmentStrings, 1, 0},
    {"kernel32.dll", "FreeEnvironmentStringsA", k32_FreeEnvironmentStrings, 1, 0},
    {"kernel32.dll", "GetStdHandle", k32_GetStdHandle, 1, 0},
    {"kernel32.dll", "SetStdHandle", k32_SetStdHandle, 2, 0},
    {"kernel32.dll", "GetFileType", k32_GetFileType, 1, 0},
    {"kernel32.dll", "GetCurrentProcessId", k32_GetCurrentProcessId, 0, 0},
    {"kernel32.dll", "GetCurrentProcess", k32_GetCurrentProcess, 0, 0},
    {"kernel32.dll", "GetLastError", k32_GetLastError, 0, 0},
    {"kernel32.dll", "SetLastError", k32_SetLastError, 1, 0},
    {"kernel32.dll", "ExitProcess", k32_ExitProcess, 1, 0},
    {"kernel32.dll", "TerminateProcess", k32_TerminateProcess, 2, 0},
    {"kernel32.dll", "HeapCreate", k32_HeapCreate, 3, 0},
    {"kernel32.dll", "HeapDestroy", k32_HeapDestroy, 1, 0},
    {"kernel32.dll", "GetProcessHeap", k32_GetProcessHeap, 0, 0},
    {"kernel32.dll", "HeapAlloc", k32_HeapAlloc, 3, 0},
    {"kernel32.dll", "HeapFree", k32_HeapFree, 3, 0},
    {"kernel32.dll", "HeapReAlloc", k32_HeapReAlloc, 4, 0},
    {"kernel32.dll", "HeapSize", k32_HeapSize, 3, 0},
    {"kernel32.dll", "VirtualAlloc", k32_VirtualAlloc, 4, 0},
    {"kernel32.dll", "VirtualFree", k32_VirtualFree, 3, 0},
    {"kernel32.dll", "VirtualProtect", k32_VirtualProtect, 4, 0},
    {"kernel32.dll", "IsBadReadPtr", k32_IsBadReadPtr, 2, 0},
    {"kernel32.dll", "IsBadWritePtr", k32_IsBadWritePtr, 2, 0},
    {"kernel32.dll", "IsBadCodePtr", k32_IsBadCodePtr, 1, 0},
    {"kernel32.dll", "GetTickCount", k32_GetTickCount, 0, 0},
    {"kernel32.dll", "QueryPerformanceCounter", k32_QueryPerformanceCounter, 1, 0},
    {"kernel32.dll", "GetSystemTimeAsFileTime", k32_GetSystemTimeAsFileTime, 1, 0},
    {"kernel32.dll", "GetLocalTime", k32_GetLocalTime, 1, 0},
    {"kernel32.dll", "GetSystemInfo", k32_GetSystemInfo, 1, 0},
    {"kernel32.dll", "GetACP", k32_GetACP, 0, 0},
    {"kernel32.dll", "GetOEMCP", k32_GetOEMCP, 0, 0},
    {"kernel32.dll", "GetThreadLocale", k32_GetThreadLocale, 0, 0},
    {"kernel32.dll", "GetCPInfo", k32_GetCPInfo, 2, 0},
    {"kernel32.dll", "WideCharToMultiByte", k32_WideCharToMultiByte, 8, 0},
    {"kernel32.dll", "MultiByteToWideChar", k32_MultiByteToWideChar, 6, 0},
    {"kernel32.dll", "GetStringTypeW", k32_GetStringTypeW, 4, 0},
    {"kernel32.dll", "GetStringTypeA", k32_GetStringTypeA, 5, 0},
    {"kernel32.dll", "LCMapStringW", k32_LCMapStringW, 6, 0},
    {"kernel32.dll", "LCMapStringA", k32_LCMapStringA, 6, 0},
    {"kernel32.dll", "lstrlen", k32_lstrlenA, 1, 0},
    {"kernel32.dll", "lstrcmp", k32_lstrcmpA, 2, 0},
    {"kernel32.dll", "lstrcat", k32_lstrcatA, 2, 0},
    {"kernel32.dll", "LockResource", k32_LockResource, 1, 0},
};

RT_EXPORT_IMPORTS(rt_imports_kernel, defs);
