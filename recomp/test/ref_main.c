/* Native reference: runs the snippets on a real x86 CPU as a freestanding 32-bit
 * Linux program (no libc) and prints the same report as the lifted harness. */
#include "tests.h"

typedef void (*SnippetFn)(u32, u32, u32, u32, u32 *);

#define T(name, kind, p1, p2) void name(u32, u32, u32, u32, u32 *);
TESTS(T)
#undef T

static const SnippetFn fns[N_TESTS] = {
#define T(name, kind, p1, p2) name,
    TESTS(T)
#undef T
};

void *memset(void *d, int v, unsigned n) {
    unsigned char *p = d;
    while (n--) *p++ = (unsigned char)v;
    return d;
}
void *memcpy(void *d, const void *s, unsigned n) {
    unsigned char *p = d;
    const unsigned char *q = s;
    while (n--) *p++ = *q++;
    return d;
}

static char obuf[4096];
static unsigned olen;

static void flush(void) {
    unsigned done = 0;
    while (done < olen) {
        int r;
        __asm__ volatile("int $0x80" : "=a"(r) : "a"(4), "b"(1), "c"(obuf + done), "d"(olen - done) : "memory");
        if (r <= 0) break;
        done += (unsigned)r;
    }
    olen = 0;
}

void put_str(const char *s) {
    while (*s) {
        if (olen == sizeof obuf) flush();
        obuf[olen++] = *s++;
    }
}

void test_call(int index, u32 a, u32 b, u32 c, u32 d, u32 out[8]) { fns[index](a, b, c, d, out); }

int ref_main(int argc) {
    run_tests(argc > 1);
    flush();
    return 0;
}

__asm__(".globl _start\n"
        "_start:\n"
        "    mov (%esp), %eax\n"
        "    and $-16, %esp\n"
        "    sub $12, %esp\n"
        "    push %eax\n"
        "    cld\n"
        "    call ref_main\n"
        "    mov %eax, %ebx\n"
        "    mov $1, %eax\n"
        "    int $0x80\n");
