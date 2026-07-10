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

int    _stricmp(const char *a, const char *b)  { return strcasecmp(a, b); }
int    _strnicmp(const char *a, const char *b, unsigned int n) { return strncasecmp(a, b, n); }
int    _mbscmp(const unsigned char *a, const unsigned char *b) { return strcmp((const char*)a,(const char*)b); }
int    _mbsicmp(const unsigned char *a, const unsigned char *b){ return strcasecmp((const char*)a,(const char*)b); }
int    _memicmp(const void *a, const void *b, unsigned int n)  { return strncasecmp((const char*)a,(const char*)b,n); }
long   _clock(void)  { return (long)clock(); }
unsigned int _strftime(char *b, unsigned int n, const char *f, const struct tm *t) { return (unsigned int)strftime(b,n,f,t); }
#endif /* __WINE__ */
