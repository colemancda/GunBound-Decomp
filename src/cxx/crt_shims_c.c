/* Pure-C CRT/allocator shims for the winegcc functional-validation
 * build (the C++ crt_shims.cpp can't be built by wineg++ -m32 here:
 * the 32-bit libstdc++ headers aren't installed). Provides the
 * placeholder symbols Ghidra's raw ports reference and forwards them
 * to the C runtime. Only compiled into the winegcc build (guarded by
 * __WINE__); the MSVC byte-match build uses the real CRT directly and
 * the C++ crt_shims.cpp for operator new/delete.
 *
 * operator_new/operator_delete forward to malloc/free: C++ operator new
 * is malloc-plus-throw-on-failure, and every raw-port call site already
 * null-checks the result, so malloc is behaviorally correct here.
 */
#ifdef __WINE__
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

void *operator_new(unsigned int size)    { return malloc(size); }
void  operator_delete(void *p)           { free(p); }

void  _free(void *p)                          { free(p); }
void *_malloc(unsigned int n)                 { return malloc(n); }
void *_calloc(unsigned int a, unsigned int b) { return calloc(a, b); }
void *_realloc(void *p, unsigned int n)       { return realloc(p, n); }
int   _rand(void)                             { return rand(); }
long  _atol(const char *s)                    { return atol(s); }
void *_memmove(void *d, const void *s, unsigned int n) { return memmove(d, s, n); }
void *_memcpy(void *d, const void *s, unsigned int n)  { return memcpy(d, s, n); }
void *_memset(void *d, int c, unsigned int n)          { return memset(d, c, n); }
unsigned int _strlen(const char *s)           { return (unsigned int)strlen(s); }
int   _strcmp(const char *a, const char *b)   { return strcmp(a, b); }
char *_strcpy(char *d, const char *s)         { return strcpy(d, s); }
char *_strncpy(char *d, const char *s, unsigned int n) { return strncpy(d, s, n); }
char *_strcat(char *d, const char *s)         { return strcat(d, s); }
double _pow(double a, double b)               { return pow(a, b); }
struct tm *_localtime(const time_t *t)        { return localtime(t); }
void  _qsort(void *b, unsigned int n, unsigned int w, int (*c)(const void *, const void *)) { qsort(b, n, w, c); }

unsigned int _fwrite(const void *p, unsigned int s, unsigned int n, FILE *f) { return (unsigned int)fwrite(p, s, n, f); }
unsigned int _fread(void *p, unsigned int s, unsigned int n, FILE *f)        { return (unsigned int)fread(p, s, n, f); }
int   _fclose(FILE *f)                         { return fclose(f); }
FILE *_fopen(const char *p, const char *m)     { return fopen(p, m); }
int   _fseek(FILE *f, long o, int w)           { return fseek(f, o, w); }
long  _ftell(FILE *f)                          { return ftell(f); }

int _sprintf(char *buf, const char *fmt, ...)
{ va_list ap; va_start(ap, fmt); int r = vsprintf(buf, fmt, ap); va_end(ap); return r; }
int _sscanf(const char *buf, const char *fmt, ...)
{ va_list ap; va_start(ap, fmt); int r = vsscanf(buf, fmt, ap); va_end(ap); return r; }

/* x87 float intrinsics (Ghidra names for the FSIN/FCOS/FPTAN/FSQRT/FABS
 * instructions and their libm equivalents) plus a few Ghidra-renamed
 * CRT helpers. All forward to libm/CRT. */
double fsin(double x)  { return sin(x); }
double fcos(double x)  { return cos(x); }
double fptan(double x) { return tan(x); }
double SQRT(double x)  { return sqrt(x); }
double _fabs(double x) { return fabs(x); }
double FID_conflict__cos(double x) { return cos(x); } /* Ghidra-renamed cos */

/* asm() labels force the EXACT symbol the raw ports reference (Ghidra's
 * _stricmp source name -> __stricmp symbol). */
int    stricmp_shim(const char *a, const char *b) asm("__stricmp");
int    stricmp_shim(const char *a, const char *b)  { return strcasecmp(a, b); }
int    strnicmp_shim(const char *a, const char *b, unsigned int n) asm("__strnicmp");
int    strnicmp_shim(const char *a, const char *b, unsigned int n) { return strncasecmp(a, b, n); }
int    mbscmp_shim(const unsigned char *a, const unsigned char *b) asm("__mbscmp");
int    mbscmp_shim(const unsigned char *a, const unsigned char *b) { return strcmp((const char*)a,(const char*)b); }
int    mbsicmp_shim(const unsigned char *a, const unsigned char *b) asm("__mbsicmp");
int    mbsicmp_shim(const unsigned char *a, const unsigned char *b){ return strcasecmp((const char*)a,(const char*)b); }
int    memicmp_shim(const void *a, const void *b, unsigned int n) asm("__memicmp");
int    memicmp_shim(const void *a, const void *b, unsigned int n)  { return strncasecmp((const char*)a,(const char*)b,n); }
char  *itoa_shim(int v, char *buf, int radix) asm("__itoa");
char  *itoa_shim(int v, char *buf, int radix)
{
    /* minimal itoa for radix 10/16 (all the raw ports use) */
    static const char d[] = "0123456789abcdef";
    char tmp[34]; int i = 0, neg = (radix == 10 && v < 0);
    unsigned int uv = neg ? (unsigned int)(-v) : (unsigned int)v;
    do { tmp[i++] = d[uv % (unsigned)radix]; uv /= (unsigned)radix; } while (uv);
    char *p = buf; if (neg) *p++ = '-';
    while (i) *p++ = tmp[--i];
    *p = 0; return buf;
}
long   _clock(void)  { return (long)clock(); }
unsigned int _strftime(char *b, unsigned int n, const char *f, const struct tm *t) { return (unsigned int)strftime(b,n,f,t); }

/* CRT/EH/threading primitives Ghidra references by decorated name.
 * Stubs sufficient for a functional link; behavior is minimal/no-op
 * where the real runtime semantics aren't reconstructed. */
#include <windows.h>

long long aulldiv_shim(unsigned long long a, unsigned long long b) asm("__aulldiv");
long long aulldiv_shim(unsigned long long a, unsigned long long b) { return b ? (long long)(a / b) : 0; }

/* _beginthread wrapper via Win32 CreateThread (msvcrt's _beginthread
 * isn't in the link; CreateThread is the functional equivalent). The
 * thread proc signature differs (void(*)(void*) vs DWORD WINAPI(void*)),
 * bridged through a tiny trampoline. */
typedef struct { void (*fn)(void *); void *arg; } gb_thunk_t;
static DWORD WINAPI gb_thread_trampoline(void *p)
{ gb_thunk_t t = *(gb_thunk_t *)p; free(p); t.fn(t.arg); return 0; }
unsigned int beginthread_shim(void (*f)(void *), unsigned int stack, void *arg) asm("__beginthread");
unsigned int beginthread_shim(void (*f)(void *), unsigned int stack, void *arg)
{
    gb_thunk_t *t = (gb_thunk_t *)malloc(sizeof *t);
    if (!t) return (unsigned int)-1;
    t->fn = f; t->arg = arg;
    HANDLE h = CreateThread(0, stack, gb_thread_trampoline, t, 0, 0);
    return (unsigned int)(unsigned long)h;
}
void endthread_shim(void) asm("__endthread");
void endthread_shim(void) { ExitThread(0); }

void CxxThrowException_shim(void *obj, void *info) asm("__CxxThrowException_8");
void CxxThrowException_shim(void *obj, void *info) { (void)obj; (void)info; /* no C++ EH in this build */ }

/* ATL base-module instance accessor - returns the process module. */
void *ATL_CAtlBaseModule_GetHInstanceAt(void *self, int idx)
{ (void)self; (void)idx; return GetModuleHandleA(0); }

/* eh_vector_*_iterator_ walk an array running a per-element ctor/dtor;
 * (count, size, elem_fn) - iterate and call. */
void eh_vec_ctor_shim(void *base, unsigned int count, unsigned int size, void (*ctor)(void *)) asm("_eh_vector_constructor_iterator_");
void eh_vec_ctor_shim(void *base, unsigned int count, unsigned int size, void (*ctor)(void *))
{ char *p = (char*)base; unsigned int i; for (i=0;i<count;i++){ if(ctor) ctor(p); p+=size; } }
void eh_vec_dtor_shim(void *base, unsigned int count, unsigned int size, void (*dtor)(void *)) asm("_eh_vector_destructor_iterator_");
void eh_vec_dtor_shim(void *base, unsigned int count, unsigned int size, void (*dtor)(void *))
{ char *p = (char*)base + (unsigned long)count*size; unsigned int i; for (i=0;i<count;i++){ p-=size; if(dtor) dtor(p); } }

/* exception ctor/dtor (Ghidra's renamed MSVC C++ exception class members
 * - ::exception/::~exception). No-op: no C++ EH in this build. */
void *exception__ctor(void *self, const char *msg) { (void)msg; return self; }
void  exception__dtor(void *self) { (void)self; }

/* misc CRT internals referenced by the pulled-in CRT-tree helpers. */
int __dosmaperr(int oserr) { (void)oserr; return 0; }  /* maps OS error -> errno; stub */
void *__fsopen(const char *path, const char *mode, int shflag) { (void)shflag; return fopen(path, mode); }
double __fload_withFB(void *p) { return p ? *(float *)p : 0.0; } /* load float w/ fallback */
#endif /* __WINE__ */
