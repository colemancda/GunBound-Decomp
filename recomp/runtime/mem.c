/* Guest address space: one host mapping, a guest heap and a VirtualAlloc arena. */
#define _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#include "rt.h"

#ifdef RT_DYNAMIC_BASE
uint8_t *g_mem;
#endif

#ifndef MAP_FIXED_NOREPLACE
#define MAP_FIXED_NOREPLACE 0x100000
#endif

static uint32_t sys_brk = GUEST_STR_BASE;
static pthread_mutex_t sys_mu = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t heap_mu = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t va_mu = PTHREAD_MUTEX_INITIALIZER;

void rt_mem_init(void) {
#ifdef RT_DYNAMIC_BASE
    void *p = mmap(NULL, GUEST_SIZE, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
    if (p == MAP_FAILED) {
        perror("recomp: mmap guest memory");
        exit(2);
    }
    g_mem = p;
#else
    void *want = (void *)(uintptr_t)RT_GUEST_BASE;
    void *p = mmap(want, GUEST_SIZE, PROT_NONE,
                   MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE | MAP_FIXED_NOREPLACE, -1, 0);
    if (p != want) {
        fprintf(stderr,
                "recomp: cannot map guest memory at host address %p (%s).\n"
                "        Rebuild with -DRT_DYNAMIC_BASE, or pick another -DRT_GUEST_BASE.\n",
                want, p == MAP_FAILED ? strerror(errno) : "address in use");
        exit(2);
    }
#endif
    rt_mem_commit(GUEST_SYS_BASE, GUEST_SYS_SIZE);
    rt_mem_commit(GUEST_STACK_LOW, GUEST_STACK_TOP - GUEST_STACK_LOW);
    rt_mem_commit(GUEST_IMP_BASE, GUEST_IMP_SIZE);
    /* Anything that peeks at an import's first bytes sees a plain `ret`. */
    memset(G(GUEST_IMP_BASE), 0xC3, GUEST_IMP_SIZE);
}

void rt_mem_commit(uint32_t addr, uint32_t size) {
    uint32_t lo = addr & ~0xFFFu;
    uint64_t hi = ((uint64_t)addr + size + 0xFFF) & ~0xFFFull;
    if (hi > GUEST_SIZE) {
        fprintf(stderr, "recomp: commit outside guest memory: %#x+%#x\n", addr, size);
        exit(2);
    }
    if (mprotect(G(lo), (size_t)(hi - lo), PROT_READ | PROT_WRITE) != 0) {
        perror("recomp: mprotect");
        exit(2);
    }
}

uint32_t rt_sys_alloc(uint32_t size) {
    pthread_mutex_lock(&sys_mu);
    uint32_t p = sys_brk;
    size = (size + 15) & ~15u;
    if (p + size > GUEST_SYS_BASE + GUEST_SYS_SIZE) {
        fprintf(stderr, "recomp: system area exhausted\n");
        exit(2);
    }
    sys_brk += size;
    pthread_mutex_unlock(&sys_mu);
    return p;
}

uint32_t rt_sys_strdup(const char *s) {
    uint32_t n = (uint32_t)strlen(s) + 1;
    uint32_t p = rt_sys_alloc(n);
    memcpy(G(p), s, n);
    return p;
}

/* ------------------------------------------------------------------ heap
 * Bump allocation with exact-size-class free lists. Each block has an 8-byte
 * header {capacity, requested size}; a freed block's requested size is
 * HEAP_FREE and its first payload dword links the class's free list.
 * The public functions take heap_mu; the *_locked ones expect it held. */
#define HEAP_HDR 8u
#define HEAP_FREE 0xFFFFFFFFu
#define HEAP_SMALL_MAX 2048u
#define HEAP_NCLASS (HEAP_SMALL_MAX / 16 + 4 * 24)

static uint32_t heap_brk = GUEST_HEAP_BASE;
static uint32_t heap_committed = GUEST_HEAP_BASE;
static uint32_t heap_bins[HEAP_NCLASS];

/* Capacity (payload bytes) and bin for a request. */
static uint32_t heap_class(uint32_t size, uint32_t *cap) {
    if (size < 8) size = 8;
    if (size <= HEAP_SMALL_MAX) {
        uint32_t c = (size + HEAP_HDR + 15) & ~15u; /* whole block is a multiple of 16 */
        *cap = c - HEAP_HDR;
        return c / 16 - 1;
    }
    /* four geometric steps per doubling above HEAP_SMALL_MAX */
    uint32_t total = size + HEAP_HDR;
    unsigned lg = 31 - (unsigned)__builtin_clz(total - 1); /* 2^lg < total <= 2^(lg+1) */
    uint32_t step = 1u << (lg - 2);
    uint32_t c = (total + step - 1) & ~(step - 1);
    uint32_t q = (c - (1u << lg)) / step; /* 1..4 */
    *cap = c - HEAP_HDR;
    uint32_t bin = HEAP_SMALL_MAX / 16 + (lg - 11) * 4 + (q - 1);
    return bin < HEAP_NCLASS ? bin : HEAP_NCLASS - 1;
}

static uint32_t heap_alloc_locked(uint32_t size, int zero) {
    uint32_t cap;
    if (size > 0x10000000u) return 0;
    uint32_t bin = heap_class(size, &cap);
    uint32_t p = 0;
    if (bin != HEAP_NCLASS - 1 && heap_bins[bin]) {
        p = heap_bins[bin];
        heap_bins[bin] = ld32(p);
        if (zero) memset(G(p), 0, size);
    } else {
        uint32_t total = cap + HEAP_HDR;
        if ((uint64_t)heap_brk + total > GUEST_HEAP_END) return 0;
        uint32_t hdr = heap_brk;
        heap_brk += total;
        if (heap_brk > heap_committed) {
            uint32_t grow = (heap_brk - heap_committed + 0xFFFFF) & ~0xFFFFFu;
            if ((uint64_t)heap_committed + grow > GUEST_HEAP_END) grow = GUEST_HEAP_END - heap_committed;
            rt_mem_commit(heap_committed, grow);
            heap_committed += grow;
        }
        p = hdr + HEAP_HDR; /* fresh memory is already zero */
    }
    st32(p - 8, cap);
    st32(p - 4, size);
    return p;
}

static uint32_t heap_size_locked(uint32_t p) {
    if (p < GUEST_HEAP_BASE + HEAP_HDR || p >= heap_brk || (p & 7)) return 0xFFFFFFFFu;
    uint32_t sz = ld32(p - 4);
    if (sz == HEAP_FREE || sz > ld32(p - 8)) return 0xFFFFFFFFu;
    return sz;
}

static void heap_free_locked(uint32_t p) {
    if (!p) return;
    if (heap_size_locked(p) == 0xFFFFFFFFu) {
        fprintf(stderr, "recomp: warning: free of invalid heap block %#x ignored\n", p);
        return;
    }
    uint32_t cap, dummy;
    cap = ld32(p - 8);
    uint32_t bin = heap_class(cap, &dummy);
    st32(p - 4, HEAP_FREE);
    if (bin == HEAP_NCLASS - 1) return; /* oversize blocks are not recycled */
    st32(p, heap_bins[bin]);
    heap_bins[bin] = p;
}

static uint32_t heap_realloc_locked(uint32_t p, uint32_t size, int zero) {
    if (!p) return heap_alloc_locked(size, zero);
    uint32_t old = heap_size_locked(p);
    if (old == 0xFFFFFFFFu) return 0;
    uint32_t cap = ld32(p - 8);
    if (size <= cap) {
        if (zero && size > old) memset(G(p + old), 0, size - old);
        st32(p - 4, size);
        return p;
    }
    uint32_t q = heap_alloc_locked(size, 0);
    if (!q) return 0;
    memcpy(G(q), G(p), old);
    if (zero) memset(G(q + old), 0, size - old);
    heap_free_locked(p);
    return q;
}

uint32_t rt_heap_alloc(uint32_t size, int zero) {
    pthread_mutex_lock(&heap_mu);
    uint32_t p = heap_alloc_locked(size, zero);
    pthread_mutex_unlock(&heap_mu);
    return p;
}

uint32_t rt_heap_size(uint32_t p) {
    pthread_mutex_lock(&heap_mu);
    uint32_t n = heap_size_locked(p);
    pthread_mutex_unlock(&heap_mu);
    return n;
}

void rt_heap_free(uint32_t p) {
    pthread_mutex_lock(&heap_mu);
    heap_free_locked(p);
    pthread_mutex_unlock(&heap_mu);
}

uint32_t rt_heap_realloc(uint32_t p, uint32_t size, int zero) {
    pthread_mutex_lock(&heap_mu);
    uint32_t q = heap_realloc_locked(p, size, zero);
    pthread_mutex_unlock(&heap_mu);
    return q;
}

/* ---------------------------------------------------------- VirtualAlloc
 * Reservations are bump allocated at 64 KiB granularity and committed
 * immediately; MEM_COMMIT inside an existing reservation is a no-op. A released
 * region is reused by a later reservation of the same size (thread stacks). */
#define MEM_COMMIT 0x1000u
#define MEM_RESERVE 0x2000u
#define MEM_DECOMMIT 0x4000u
#define MEM_RELEASE 0x8000u

typedef struct VRegion {
    uint32_t base, size;
    int free;
} VRegion;
static VRegion vregions[4096];
static unsigned nvregions;
static uint32_t va_brk = GUEST_VA_BASE;

static VRegion *vregion_find(uint32_t addr) {
    for (unsigned i = 0; i < nvregions; i++)
        if (!vregions[i].free && addr >= vregions[i].base && addr - vregions[i].base < vregions[i].size)
            return &vregions[i];
    return NULL;
}

uint32_t rt_valloc(uint32_t addr, uint32_t size, uint32_t type, uint32_t protect) {
    (void)protect;
    if (size == 0) return 0;
    uint32_t result = 0;
    pthread_mutex_lock(&va_mu);
    if (addr) {
        VRegion *r = vregion_find(addr);
        /* placement at a caller-chosen address outside a reservation is not supported */
        if (r && (uint64_t)addr + size <= (uint64_t)r->base + r->size)
            result = (type & MEM_RESERVE) ? r->base : (addr & ~0xFFFu);
    } else {
        uint32_t sz = (size + 0xFFFF) & ~0xFFFFu;
        for (unsigned i = 0; i < nvregions && !result && sz >= size; i++) {
            if (vregions[i].free && vregions[i].size == sz) {
                vregions[i].free = 0;
                result = vregions[i].base;
            }
        }
        if (!result && sz >= size && (uint64_t)va_brk + sz <= GUEST_VA_END &&
            nvregions < sizeof vregions / sizeof vregions[0]) {
            result = va_brk;
            va_brk += sz;
            rt_mem_commit(result, sz);
            vregions[nvregions].base = result;
            vregions[nvregions].size = sz;
            vregions[nvregions].free = 0;
            nvregions++;
        }
    }
    pthread_mutex_unlock(&va_mu);
    return result;
}

int rt_vfree(uint32_t addr, uint32_t size, uint32_t type) {
    pthread_mutex_lock(&va_mu);
    VRegion *r = vregion_find(addr);
    if (!r) {
        pthread_mutex_unlock(&va_mu);
        return 0;
    }
    uint32_t lo, len;
    if (type & MEM_RELEASE) {
        lo = r->base;
        len = r->size;
        r->free = 1;
    } else {
        lo = addr & ~0xFFFu;
        len = size ? ((addr + size + 0xFFF) & ~0xFFFu) - lo : r->base + r->size - lo;
    }
    /* Drop the pages so that the range reads as zeros when it is committed or reused. */
    madvise(G(lo), len, MADV_DONTNEED);
    pthread_mutex_unlock(&va_mu);
    return 1;
}

int rt_vquery(uint32_t addr, uint32_t *base, uint32_t *size) {
    int found = 0;
    pthread_mutex_lock(&va_mu);
    VRegion *r = vregion_find(addr);
    if (r) {
        *base = r->base;
        *size = r->size;
        found = 1;
    }
    pthread_mutex_unlock(&va_mu);
    if (found) return 1;
    if (addr >= GUEST_SYS_BASE && addr < GUEST_STACK_TOP) {
        *base = addr >= GUEST_STACK_LOW ? GUEST_STACK_LOW : GUEST_SYS_BASE;
        *size = addr >= GUEST_STACK_LOW ? GUEST_STACK_TOP - GUEST_STACK_LOW : GUEST_SYS_SIZE;
        return 1;
    }
    if (addr >= g_image.base && addr - g_image.base < g_image.size) {
        *base = g_image.base;
        *size = g_image.size;
        return 1;
    }
    if (addr >= GUEST_HEAP_BASE && addr < heap_committed) {
        *base = GUEST_HEAP_BASE;
        *size = heap_committed - GUEST_HEAP_BASE;
        return 1;
    }
    return 0;
}

int rt_guest_readable(uint32_t addr, uint32_t size) {
    uint64_t end = (uint64_t)addr + size;
    uint32_t base, len;
    if (!rt_vquery(addr, &base, &len)) return 0;
    return end <= (uint64_t)base + len;
}
