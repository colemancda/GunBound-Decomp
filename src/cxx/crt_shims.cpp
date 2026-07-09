/* CRT/C++ runtime shims - bridge the raw ports' placeholder symbol
 * names to the real MSVC runtime, so the tree can link against
 * libcmt.lib without editing 270 call sites.
 *
 * Ghidra's decompiler renamed C++ operator new / operator delete to
 * the plain C identifiers `operator_new` / `operator_delete` (a valid
 * C name), which the raw ports call as `_operator_new`. The real
 * runtime exports the mangled `??2@YAPAXI@Z` / `??3@YAXPAX@Z`. These
 * one-line forwarders, compiled as C++ and exported with C linkage,
 * connect the two - a linker shim, not reimplementation. */
#include <stdlib.h>

extern "C" void *operator_new(unsigned int size)
{
    return ::operator new(size);
}

extern "C" void operator_delete(void *p)
{
    ::operator delete(p);
}

/* CRT function shims - Ghidra names CRT calls with a leading underscore
 * (_free, _rand, ...), which the C compiler cdecl-decorates to a
 * DOUBLE-underscore symbol (__free) with no declaration in scope. The
 * real CRT in libcmt.lib exports the single-underscore _free. These
 * forwarders provide the __-symbol the raw ports reference and call
 * straight through to the CRT. Variadic ones (_sprintf, _sscanf) use
 * va_list pass-through via the v-forms (except _sscanf; see below). */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

extern "C" {
void  _free(void *p)                         { free(p); }
void *_malloc(unsigned int n)                { return malloc(n); }
void *_calloc(unsigned int a, unsigned int b){ return calloc(a, b); }
void *_realloc(void *p, unsigned int n)      { return realloc(p, n); }
int   _rand(void)                            { return rand(); }
long  _atol(const char *s)                   { return atol(s); }
void *_memmove(void *d, const void *s, unsigned int n) { return memmove(d, s, n); }
void *_memcpy(void *d, const void *s, unsigned int n)  { return memcpy(d, s, n); }
void *_memset(void *d, int c, unsigned int n)          { return memset(d, c, n); }
unsigned int _strlen(const char *s)          { return (unsigned int)strlen(s); }
int   _strcmp(const char *a, const char *b)  { return strcmp(a, b); }
char *_strcpy(char *d, const char *s)        { return strcpy(d, s); }
char *_strcat(char *d, const char *s)        { return strcat(d, s); }
double _pow(double a, double b)              { return pow(a, b); }
struct tm *_localtime(const time_t *t)       { return localtime(t); }
void  _qsort(void *b, unsigned int n, unsigned int w, int (*c)(const void *, const void *)) { qsort(b, n, w, c); }

/* stdio */
unsigned int _fwrite(const void *p, unsigned int s, unsigned int n, FILE *f) { return (unsigned int)fwrite(p, s, n, f); }
unsigned int _fread(void *p, unsigned int s, unsigned int n, FILE *f)        { return (unsigned int)fread(p, s, n, f); }
int   _fclose(FILE *f)                        { return fclose(f); }
FILE *_fopen(const char *p, const char *m)    { return fopen(p, m); }
int   _fseek(FILE *f, long o, int w)          { return fseek(f, o, w); }
long  _ftell(FILE *f)                         { return ftell(f); }

/* variadic: forward through the v-forms */
int _sprintf(char *buf, const char *fmt, ...)
{
    va_list ap; va_start(ap, fmt);
    int r = vsprintf(buf, fmt, ap);
    va_end(ap);
    return r;
}
/* _sscanf: MSVC 7.1 has no vsscanf, so the variadic forward isn't
 * possible here. The 3 raw-port call sites are handled by a linker
 * alias (__sscanf -> _sscanf) instead - see the /ALTERNATENAME note in
 * tools/msvc-env/_link_attempt.sh. */
} /* extern "C" */
