/* MSVC-side CRT/allocator/intrinsic shims for the full-tree MSVC link
 * attempt (tools/msvc-env/_link_attempt.sh). Counterpart of the
 * winegcc-only crt_shims_c.c: the raw ports call Ghidra's renamed CRT
 * symbols (_free, _rand, __stricmp, ...) and a handful of decompiler
 * pseudo-ops (CONCAT*, LOCK, fsin, ...). Under MSVC the source names
 * decorate to exactly the symbols the objects reference, so plain C
 * definitions suffice - no asm() labels like the GCC version needs.
 *
 * Everything forwards to the real CRT/Win32 where one exists; EH and
 * ATL helpers are minimal stubs sufficient for a functional link.
 * Compiled only into the MSVC link attempt (guarded by _MSC_VER). */
#ifdef _MSC_VER
#define WIN32_LEAN_AND_MEAN /* keep mmsystem.h out: we define a cdecl
                             * timeGetTime below (a raw port declares it
                             * without the stdcall prototype) */
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <process.h>

/* --- Ghidra-renamed CRT (source `_x` -> symbol `__x`) --- */
void  _free(void *p)                          { free(p); }
void *_malloc(unsigned int n)                 { return malloc(n); }
void *_realloc(void *p, unsigned int n)       { return realloc(p, n); }
int   _rand(void)                             { return rand(); }
long  _atol(const char *s)                    { return atol(s); }
long  _clock(void)                            { return (long)clock(); }
double _fabs(double x)                        { return fabs(x); }
double _pow(double a, double b)               { return pow(a, b); }
void *_memmove(void *d, const void *s, unsigned int n) { return memmove(d, s, n); }
char *_strncpy(char *d, const char *s, unsigned int n) { return strncpy(d, s, n); }
struct tm *_localtime(const time_t *t)        { return localtime(t); }
void  _qsort(void *b, unsigned int n, unsigned int w, int (*c)(const void *, const void *)) { qsort(b, n, w, c); }
unsigned int _strftime(char *b, unsigned int n, const char *f, const struct tm *t) { return (unsigned int)strftime(b, n, f, t); }

unsigned int _fwrite(const void *p, unsigned int s, unsigned int n, FILE *f) { return (unsigned int)fwrite(p, s, n, f); }
unsigned int _fread(void *p, unsigned int s, unsigned int n, FILE *f)        { return (unsigned int)fread(p, s, n, f); }
int   _fclose(FILE *f)                        { return fclose(f); }
int   _fseek(FILE *f, long o, int w)          { return fseek(f, o, w); }
long  _ftell(FILE *f)                         { return ftell(f); }

int _sprintf(char *buf, const char *fmt, ...)
{
    int r; va_list ap;
    va_start(ap, fmt); r = vsprintf(buf, fmt, ap); va_end(ap);
    return r;
}
/* MSVC 7.1 has no vsscanf; forwarding a fixed number of pointer-sized
 * slots covers every raw-port call site (max seen: 4 outputs). */
int _sscanf(const char *buf, const char *fmt, ...)
{
    void *a[8]; int i; va_list ap;
    va_start(ap, fmt);
    for (i = 0; i < 8; i++) a[i] = va_arg(ap, void *);
    va_end(ap);
    return sscanf(buf, fmt, a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
}

/* --- Ghidra double-underscore names (source `__x` -> symbol `___x`);
 *     forward to the real single-underscore CRT function --- */
int    __stricmp(const char *a, const char *b)                      { return _stricmp(a, b); }
int    __strnicmp(const char *a, const char *b, unsigned int n)     { return _strnicmp(a, b, n); }
int    __mbscmp(const unsigned char *a, const unsigned char *b)     { return strcmp((const char *)a, (const char *)b); }
int    __mbsicmp(const unsigned char *a, const unsigned char *b)    { return _stricmp((const char *)a, (const char *)b); }
int    __memicmp(const void *a, const void *b, unsigned int n)      { return _memicmp(a, b, n); }
char  *__itoa(int v, char *buf, int radix)                          { return _itoa(v, buf, radix); }
FILE  *__fsopen(const char *p, const char *m, int sh)               { (void)sh; return fopen(p, m); }
void   __dosmaperr(unsigned long e)                                 { (void)e; }
unsigned long __beginthread(void (*f)(void *), unsigned int stack, void *arg) { return _beginthread(f, stack, arg); }
void   __endthread(void)                                            { _endthread(); }
unsigned __int64 __aulldiv(unsigned __int64 a, unsigned __int64 b)  { return b ? a / b : 0; }
void   __CxxThrowException_8(void *obj, void *info)                 { (void)obj; (void)info; /* no C++ EH here */ }

/* --- EH vector iterators / exception object helpers (stubs) --- */
void  _eh_vector_constructor_iterator_() {}
void  _eh_vector_destructor_iterator_()  {}
void *exception__ctor(void *thisp, void *arg) { (void)arg; return thisp; }
void  exception__dtor(void *thisp)            { (void)thisp; }

/* --- ATL helper --- */
void *ATL_CAtlBaseModule_GetHInstanceAt(int i) { (void)i; return 0; }

/* --- Ghidra decompiler pseudo-ops (function form, for the few TUs
 *     that don't include ghidra_intrinsics.h's macro versions) --- */
unsigned short CONCAT11(unsigned int hi, unsigned int lo) { return (unsigned short)(((hi & 0xff) << 8) | (lo & 0xff)); }
unsigned int   CONCAT13(unsigned int hi, unsigned int lo) { return ((hi & 0xff) << 24) | (lo & 0xffffff); }
unsigned int   CONCAT22(unsigned int hi, unsigned int lo) { return ((hi & 0xffff) << 16) | (lo & 0xffff); }
unsigned int   CONCAT31(unsigned int hi, unsigned int lo) { return ((hi & 0xffffff) << 8) | (lo & 0xff); }
void LOCK(void)   {}
void UNLOCK(void) {}

/* --- x87 float intrinsics (Ghidra names) --- */
double fsin(double x)  { return sin(x); }
double fcos(double x)  { return cos(x); }
double fptan(double x) { return tan(x); }
double SQRT(double x)  { return sqrt(x); }
double FID_conflict__cos(double x) { return cos(x); } /* Ghidra-renamed cos */

/* --- Startup hook: initialize the static CRITICAL_SECTIONs ---
 * WinMain's first act is EnterCriticalSection(&DAT_005a9068); in the
 * original binary a C++ static initializer set these up. Our ports
 * lost that, so register an initializer in the CRT's C-init table
 * (.CRT$XCU) - libcmt runs it before WinMain. Storage lives in
 * src/globals_sized.c. */
extern unsigned char DAT_005a9068[24], DAT_005a9084[24], DAT_00e9af44[24];
static void gb_init_critical_sections(void)
{
    InitializeCriticalSection((LPCRITICAL_SECTION)DAT_005a9068);
    InitializeCriticalSection((LPCRITICAL_SECTION)DAT_005a9084);
    InitializeCriticalSection((LPCRITICAL_SECTION)DAT_00e9af44);
}
/* data_seg, NOT #pragma section(...,read): VC7.1's linker keeps a
 * read-only .CRT$XCU out of the read-write .CRT group libcmt walks in
 * _cinit, so the hook silently never runs (verified empirically). */
#pragma data_seg(".CRT$XCU")
static void (*gb_init_cs_entry)(void) = gb_init_critical_sections;
#pragma data_seg()

/* --- Win32 calls a raw port declares without the stdcall prototype
 *     (so the object references the cdecl symbol) --- */
unsigned long timeGetTime(void) { return GetTickCount(); }
void *ShellExecuteA(void *hwnd, const char *op, const char *file,
                    const char *params, const char *dir, int show)
{
    typedef void *(__stdcall *fn_t)(void *, const char *, const char *,
                                    const char *, const char *, int);
    HMODULE h = LoadLibraryA("shell32.dll");
    fn_t fn = h ? (fn_t)GetProcAddress(h, "ShellExecuteA") : 0;
    return fn ? fn(hwnd, op, file, params, dir, show) : 0;
}
#endif /* _MSC_VER */
