/* Guest threads, the handle table, waitable objects and critical sections.
 *
 * Each guest thread is a host pthread with its own CPU, TEB and guest stack.
 * Waitable objects (events, mutexes, threads) share one host mutex and one
 * condition variable: the program has a handful of threads and waits are rare,
 * so a broadcast per state change is cheap and makes WaitForMultipleObjects
 * trivially correct.
 */
#define _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

#include "rt.h"

#define WAIT_OBJECT_0 0u
#define WAIT_TIMEOUT 0x102u
#define WAIT_FAILED 0xFFFFFFFFu
#define INFINITE 0xFFFFFFFFu
#define ERROR_INVALID_HANDLE 6u
#define ERROR_ALREADY_EXISTS 183u
#define ERROR_FILE_NOT_FOUND 2u
#define ERROR_NOT_OWNER 288u
#define STILL_ACTIVE 259u

uint64_t rt_mono_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;
}

/* ------------------------------------------------------------ handle table */
typedef struct HandleEntry {
    int type;
    void *obj;
    void (*close)(void *obj);
} HandleEntry;

#define HANDLE_BASE 0x100u
static HandleEntry *handles;
static uint32_t nhandles, handles_cap;
static pthread_mutex_t handle_mu = PTHREAD_MUTEX_INITIALIZER;

uint32_t rt_handle_alloc(int type, void *obj, void (*close)(void *obj)) {
    pthread_mutex_lock(&handle_mu);
    uint32_t i;
    for (i = 0; i < nhandles; i++)
        if (handles[i].type == RT_H_FREE) break;
    if (i == nhandles) {
        if (nhandles == handles_cap) {
            handles_cap = handles_cap ? handles_cap * 2 : 64;
            handles = realloc(handles, handles_cap * sizeof *handles);
        }
        nhandles++;
    }
    handles[i].type = type;
    handles[i].obj = obj;
    handles[i].close = close;
    pthread_mutex_unlock(&handle_mu);
    return HANDLE_BASE + 4 * i;
}

void *rt_handle_get(uint32_t h, int type) {
    void *obj = NULL;
    uint32_t i = (h - HANDLE_BASE) / 4;
    pthread_mutex_lock(&handle_mu);
    if (h >= HANDLE_BASE && !(h & 3) && i < nhandles && handles[i].type == type) obj = handles[i].obj;
    pthread_mutex_unlock(&handle_mu);
    return obj;
}

int rt_handle_close(uint32_t h) {
    uint32_t i = (h - HANDLE_BASE) / 4;
    pthread_mutex_lock(&handle_mu);
    if (h < HANDLE_BASE || (h & 3) || i >= nhandles || handles[i].type == RT_H_FREE) {
        pthread_mutex_unlock(&handle_mu);
        return 0;
    }
    HandleEntry e = handles[i];
    handles[i].type = RT_H_FREE;
    handles[i].obj = NULL;
    pthread_mutex_unlock(&handle_mu);
    if (e.close) e.close(e.obj);
    return 1;
}

/* -------------------------------------------------------- waitable objects */
struct RtWaitable {
    int kind;
    int refs;
    int signaled;     /* event: set; thread/process: exited; mutex: unused (see owner) */
    int manual_reset; /* events */
    uint32_t owner;   /* mutex: owning thread id, 0 when free */
    uint32_t recursion;
    uint32_t exit_code;
    char *name;
    struct RtWaitable *next_named;
};

static pthread_mutex_t sync_mu = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t sync_cv;
static pthread_once_t sync_once = PTHREAD_ONCE_INIT;
static RtWaitable *named_objects;

static void sync_init(void) {
    pthread_condattr_t at;
    pthread_condattr_init(&at);
    pthread_condattr_setclock(&at, CLOCK_MONOTONIC);
    pthread_cond_init(&sync_cv, &at);
}

RtWaitable *rt_waitable_new(int kind, int manual_reset, int signaled) {
    pthread_once(&sync_once, sync_init);
    RtWaitable *w = calloc(1, sizeof *w);
    w->kind = kind;
    w->refs = 1;
    w->manual_reset = manual_reset;
    w->signaled = signaled;
    w->exit_code = STILL_ACTIVE;
    return w;
}

void rt_waitable_ref(RtWaitable *w) { __atomic_fetch_add(&w->refs, 1, __ATOMIC_SEQ_CST); }

void rt_waitable_unref(void *p) {
    RtWaitable *w = p;
    pthread_mutex_lock(&sync_mu);
    if (__atomic_sub_fetch(&w->refs, 1, __ATOMIC_SEQ_CST) > 0) {
        pthread_mutex_unlock(&sync_mu);
        return;
    }
    for (RtWaitable **pp = &named_objects; *pp; pp = &(*pp)->next_named) {
        if (*pp == w) {
            *pp = w->next_named;
            break;
        }
    }
    pthread_mutex_unlock(&sync_mu);
    free(w->name);
    free(w);
}

void rt_waitable_signal(RtWaitable *w) {
    pthread_mutex_lock(&sync_mu);
    w->signaled = 1;
    pthread_cond_broadcast(&sync_cv);
    pthread_mutex_unlock(&sync_mu);
}

void rt_waitable_reset(RtWaitable *w) {
    pthread_mutex_lock(&sync_mu);
    w->signaled = 0;
    pthread_mutex_unlock(&sync_mu);
}

void rt_waitable_set_exit_code(RtWaitable *w, uint32_t code) {
    pthread_mutex_lock(&sync_mu);
    w->exit_code = code;
    pthread_mutex_unlock(&sync_mu);
}

/* Under sync_mu. */
static int waitable_ready(const RtWaitable *w, uint32_t tid) {
    if (w->kind == RT_W_MUTEX) return w->owner == 0 || w->owner == tid;
    return w->signaled;
}

/* Under sync_mu: the wait on w is satisfied, apply its side effect. */
static void waitable_acquire(RtWaitable *w, uint32_t tid) {
    if (w->kind == RT_W_MUTEX) {
        w->owner = tid;
        w->recursion++;
    } else if (w->kind == RT_W_EVENT && !w->manual_reset) {
        w->signaled = 0;
    }
}

static uint32_t wait_many(CPU *c, RtWaitable **ws, uint32_t n, int wait_all, uint32_t ms) {
    struct timespec deadline;
    if (ms != INFINITE) {
        clock_gettime(CLOCK_MONOTONIC, &deadline);
        deadline.tv_sec += ms / 1000;
        deadline.tv_nsec += (long)(ms % 1000) * 1000000L;
        if (deadline.tv_nsec >= 1000000000L) {
            deadline.tv_sec++;
            deadline.tv_nsec -= 1000000000L;
        }
    }
    uint32_t tid = c->thread_id, result;
    pthread_mutex_lock(&sync_mu);
    for (;;) {
        if (wait_all) {
            uint32_t ready = 0;
            for (uint32_t i = 0; i < n; i++) ready += (uint32_t)waitable_ready(ws[i], tid);
            if (ready == n) {
                for (uint32_t i = 0; i < n; i++) waitable_acquire(ws[i], tid);
                result = WAIT_OBJECT_0;
                break;
            }
        } else {
            uint32_t i;
            for (i = 0; i < n; i++)
                if (waitable_ready(ws[i], tid)) break;
            if (i < n) {
                waitable_acquire(ws[i], tid);
                result = WAIT_OBJECT_0 + i;
                break;
            }
        }
        if (ms == 0) {
            result = WAIT_TIMEOUT;
            break;
        }
        if (ms == INFINITE) {
            pthread_cond_wait(&sync_cv, &sync_mu);
        } else if (pthread_cond_timedwait(&sync_cv, &sync_mu, &deadline) == ETIMEDOUT) {
            ms = 0; /* one more look at the objects, then report the timeout */
        }
    }
    pthread_mutex_unlock(&sync_mu);
    return result;
}

/* Named events and mutexes. Returns the existing object (with a new reference) or NULL. */
static RtWaitable *named_find(const char *name, int kind) {
    RtWaitable *found = NULL;
    pthread_mutex_lock(&sync_mu);
    for (RtWaitable *w = named_objects; w; w = w->next_named) {
        if (w->kind == kind && !strcmp(w->name, name)) {
            found = w;
            __atomic_fetch_add(&w->refs, 1, __ATOMIC_SEQ_CST);
            break;
        }
    }
    pthread_mutex_unlock(&sync_mu);
    return found;
}

static void named_add(RtWaitable *w, const char *name) {
    w->name = strdup(name);
    pthread_mutex_lock(&sync_mu);
    w->next_named = named_objects;
    named_objects = w;
    pthread_mutex_unlock(&sync_mu);
}

/* CreateEventA(security, manualReset, initialState, name) */
H(k32_CreateEventA) {
    pthread_once(&sync_once, sync_init);
    RtWaitable *w = NULL;
    uint32_t err = 0;
    if (a[3] && (w = named_find(rt_gstr(a[3]), RT_W_EVENT)) != NULL) {
        err = ERROR_ALREADY_EXISTS;
    } else {
        w = rt_waitable_new(RT_W_EVENT, a[1] != 0, a[2] != 0);
        if (a[3]) named_add(w, rt_gstr(a[3]));
    }
    rt_set_last_error(c, err);
    return rt_handle_alloc(RT_H_WAITABLE, w, rt_waitable_unref);
}

/* OpenEventA(access, inherit, name) */
H(k32_OpenEventA) {
    pthread_once(&sync_once, sync_init);
    RtWaitable *w = a[2] ? named_find(rt_gstr(a[2]), RT_W_EVENT) : NULL;
    if (!w) {
        rt_set_last_error(c, ERROR_FILE_NOT_FOUND);
        return 0;
    }
    return rt_handle_alloc(RT_H_WAITABLE, w, rt_waitable_unref);
}

H(k32_SetEvent) {
    RtWaitable *w = rt_handle_get(a[0], RT_H_WAITABLE);
    if (!w || w->kind != RT_W_EVENT) {
        rt_set_last_error(c, ERROR_INVALID_HANDLE);
        return 0;
    }
    rt_waitable_signal(w);
    return 1;
}

H(k32_ResetEvent) {
    RtWaitable *w = rt_handle_get(a[0], RT_H_WAITABLE);
    if (!w || w->kind != RT_W_EVENT) {
        rt_set_last_error(c, ERROR_INVALID_HANDLE);
        return 0;
    }
    rt_waitable_reset(w);
    return 1;
}

/* CreateMutexA(security, initialOwner, name) */
H(k32_CreateMutexA) {
    pthread_once(&sync_once, sync_init);
    RtWaitable *w = NULL;
    uint32_t err = 0;
    if (a[2] && (w = named_find(rt_gstr(a[2]), RT_W_MUTEX)) != NULL) {
        err = ERROR_ALREADY_EXISTS;
    } else {
        w = rt_waitable_new(RT_W_MUTEX, 0, 0);
        if (a[1]) {
            w->owner = c->thread_id;
            w->recursion = 1;
        }
        if (a[2]) named_add(w, rt_gstr(a[2]));
    }
    rt_set_last_error(c, err);
    return rt_handle_alloc(RT_H_WAITABLE, w, rt_waitable_unref);
}

H(k32_ReleaseMutex) {
    RtWaitable *w = rt_handle_get(a[0], RT_H_WAITABLE);
    if (!w || w->kind != RT_W_MUTEX) {
        rt_set_last_error(c, ERROR_INVALID_HANDLE);
        return 0;
    }
    uint32_t ok = 0;
    pthread_mutex_lock(&sync_mu);
    if (w->owner == c->thread_id && w->recursion) {
        if (--w->recursion == 0) {
            w->owner = 0;
            pthread_cond_broadcast(&sync_cv);
        }
        ok = 1;
    }
    pthread_mutex_unlock(&sync_mu);
    if (!ok) rt_set_last_error(c, ERROR_NOT_OWNER);
    return ok;
}

H(k32_WaitForSingleObject) {
    RtWaitable *w = rt_handle_get(a[0], RT_H_WAITABLE);
    if (!w) {
        rt_set_last_error(c, ERROR_INVALID_HANDLE);
        return WAIT_FAILED;
    }
    return wait_many(c, &w, 1, 0, a[1]);
}

/* WaitForMultipleObjects(count, handles, waitAll, milliseconds) */
H(k32_WaitForMultipleObjects) {
    RtWaitable *ws[64];
    uint32_t n = a[0];
    if (n == 0 || n > 64) {
        rt_set_last_error(c, 87);
        return WAIT_FAILED;
    }
    for (uint32_t i = 0; i < n; i++) {
        ws[i] = rt_handle_get(ld32(a[1] + 4 * i), RT_H_WAITABLE);
        if (!ws[i]) {
            rt_set_last_error(c, ERROR_INVALID_HANDLE);
            return WAIT_FAILED;
        }
    }
    return wait_many(c, ws, n, a[2] != 0, a[3]);
}

H(k32_CloseHandle) {
    if (rt_handle_close(a[0])) return 1;
    /* Pseudo handles and handles of object types the runtime does not track. */
    rt_set_last_error(c, ERROR_INVALID_HANDLE);
    return a[0] != 0 && a[0] != 0xFFFFFFFFu && a[0] < HANDLE_BASE;
}

H(k32_Sleep) {
    UNUSED;
    if (a[0] == 0) {
        sched_yield();
    } else {
        struct timespec ts = {.tv_sec = a[0] / 1000, .tv_nsec = (long)(a[0] % 1000) * 1000000L};
        while (nanosleep(&ts, &ts) != 0 && errno == EINTR) {}
    }
    return 0;
}

/* ----------------------------------------------------------------- threads */
static pthread_mutex_t thread_mu = PTHREAD_MUTEX_INITIALIZER;
static uint32_t next_tid = 0x00000A30u;
static RtThread main_thread;

typedef struct ThreadStart {
    RtThread *th;
    RtWaitable *resume; /* created suspended: wait for this before starting */
    uint32_t region;    /* guest allocation holding the stack and the TEB */
    pthread_t pt;
} ThreadStart;

void rt_teb_init(uint32_t teb, uint32_t stack_low, uint32_t stack_top, uint32_t tid) {
    memset(G(teb), 0, TEB_SIZE);
    st32(teb + 0x00, 0xFFFFFFFFu);          /* SEH chain: end marker */
    st32(teb + 0x04, stack_top);            /* StackBase */
    st32(teb + 0x08, stack_low);            /* StackLimit */
    st32(teb + 0x18, teb);                  /* Self */
    st32(teb + 0x20, 0x00000A28);           /* process id */
    st32(teb + 0x24, tid);                  /* thread id */
    st32(teb + 0x2C, teb + TEB_TLS_SLOTS);  /* ThreadLocalStoragePointer */
    st32(teb + 0x30, GUEST_PEB);
}

static void cpu_init(CPU *c, RtThread *th) {
    memset(c, 0, sizeof *c);
    c->fs_base = th->teb;
    c->thread_id = th->tid;
    c->fcw = 0x027F; /* Windows default: 53-bit precision, round to nearest, exceptions masked */
    c->thread = th;
}

RtThread *rt_thread_init_main(void) {
    pthread_once(&sync_once, sync_init);
    RtThread *th = &main_thread;
    th->tid = 0x00000A2Cu;
    th->teb = GUEST_TEB;
    th->stack_low = GUEST_STACK_LOW;
    th->stack_top = GUEST_STACK_TOP;
    th->is_main = 1;
    th->done = rt_waitable_new(RT_W_THREAD, 1, 0);
    rt_teb_init(th->teb, th->stack_low, th->stack_top, th->tid);
    cpu_init(&th->cpu, th);
    rt_set_cpu(&th->cpu);
    return th;
}

static void thread_finish(ThreadStart *ts, uint32_t code) __attribute__((noreturn));
static void thread_finish(ThreadStart *ts, uint32_t code) {
    RtThread *th = ts->th;
    if (g_trace_imports) rt_log("[thread %x] exits with code %u\n", th->tid, code);
    rt_waitable_set_exit_code(th->done, code);
    rt_waitable_signal(th->done);
    rt_waitable_unref(th->done);
    rt_set_cpu(NULL);
    rt_vfree(ts->region, 0, 0x8000);
    if (ts->resume) rt_waitable_unref(ts->resume);
    /* th itself stays allocated: a message queue or a diagnostic may still refer to it. */
    free(ts);
    pthread_exit(NULL);
}

static __thread ThreadStart *t_start;

static void *thread_main(void *arg) {
    ThreadStart *ts = arg;
    RtThread *th = ts->th;
    CPU *c = &th->cpu;
    t_start = ts;
    rt_set_cpu(c);
    rt_install_fault_handler();
    if (ts->resume) {
        RtWaitable *w = ts->resume;
        wait_many(c, &w, 1, 0, INFINITE);
    }
    ESP = th->stack_top - 0x40;
    PUSH32(th->param);
    PUSH32(GUEST_THREAD_RET);
    uint32_t slot = ESP;
    if (g_trace_imports) rt_log("[thread %x] starts at %08x(%08x)\n", th->tid, th->start, th->param);
    rt_call(c, th->start);
    if (c->eip != GUEST_THREAD_RET || c->ret_sp != slot)
        rt_fatal(c, 4, "thread start routine 0x%08x returned to 0x%08x instead of the thread exit address",
                 th->start, c->eip == RT_NL_PENDING ? c->nl_eip : c->eip);
    thread_finish(ts, EAX);
}

/* Thread handle -> resume gate and pthread, for ResumeThread and TerminateThread. */
typedef struct ThreadGate {
    RtWaitable *done, *gate;
    pthread_t pt;
} ThreadGate;
static ThreadGate gates[256];

static void gate_register(RtWaitable *done, RtWaitable *gate, pthread_t pt) {
    pthread_mutex_lock(&thread_mu);
    for (size_t i = 0; i < RT_COUNTOF(gates); i++) {
        if (!gates[i].done || gates[i].done->signaled) {
            if (gates[i].done) {
                rt_waitable_unref(gates[i].done);
                if (gates[i].gate) rt_waitable_unref(gates[i].gate);
            }
            rt_waitable_ref(done);
            gates[i].done = done;
            gates[i].gate = gate;
            gates[i].pt = pt;
            pthread_mutex_unlock(&thread_mu);
            return;
        }
    }
    pthread_mutex_unlock(&thread_mu);
    rt_log("recomp: warning: more than %zu live threads; ResumeThread/TerminateThread will not find this one\n",
           RT_COUNTOF(gates));
}

static ThreadGate *gate_find(RtWaitable *done) {
    for (size_t i = 0; i < RT_COUNTOF(gates); i++)
        if (gates[i].done == done) return &gates[i];
    return NULL;
}

/* CreateThread(security, stackSize, start, param, flags, &threadId) */
H(k32_CreateThread) {
    uint32_t stack = a[1] ? (a[1] + 0xFFFFu) & ~0xFFFFu : 0x100000u;
    if (stack < 0x40000u) stack = 0x40000u;
    uint32_t region = rt_valloc(0, stack + 0x10000u, 0x3000, 4);
    if (!region) {
        rt_set_last_error(c, 8);
        return 0;
    }
    RtThread *th = calloc(1, sizeof *th);
    ThreadStart *ts = calloc(1, sizeof *ts);
    pthread_mutex_lock(&thread_mu);
    th->tid = next_tid;
    next_tid += 4;
    pthread_mutex_unlock(&thread_mu);
    th->stack_low = region;
    th->stack_top = region + stack;
    th->teb = region + stack;
    th->start = a[2];
    th->param = a[3];
    th->done = rt_waitable_new(RT_W_THREAD, 1, 0);
    rt_teb_init(th->teb, th->stack_low, th->stack_top, th->tid);
    cpu_init(&th->cpu, th);
    ts->th = th;
    ts->region = region;
    if (a[4] & 4) ts->resume = rt_waitable_new(RT_W_EVENT, 1, 0); /* CREATE_SUSPENDED */

    rt_waitable_ref(th->done); /* one reference for the handle, one for the running thread */
    if (ts->resume) rt_waitable_ref(ts->resume);
    uint32_t h = rt_handle_alloc(RT_H_WAITABLE, th->done, rt_waitable_unref);
    if (a[5]) st32(a[5], th->tid);

    pthread_attr_t at;
    pthread_attr_init(&at);
    pthread_attr_setstacksize(&at, 16u << 20); /* lifted code recurses on the host stack too */
    pthread_attr_setdetachstate(&at, PTHREAD_CREATE_DETACHED);
    int err = pthread_create(&ts->pt, &at, thread_main, ts);
    pthread_attr_destroy(&at);
    if (err) {
        rt_handle_close(h);
        rt_set_last_error(c, 8);
        return 0;
    }
    gate_register(th->done, ts->resume, ts->pt);
    if (g_trace_imports)
        rt_log("[thread %x] created by %x: start %08x param %08x%s\n", th->tid, c->thread_id, th->start, th->param,
               ts->resume ? " (suspended)" : "");
    return h;
}

H(k32_ResumeThread) {
    RtWaitable *w = rt_handle_get(a[0], RT_H_WAITABLE);
    if (!w || w->kind != RT_W_THREAD) {
        rt_set_last_error(c, ERROR_INVALID_HANDLE);
        return 0xFFFFFFFFu;
    }
    pthread_mutex_lock(&thread_mu);
    ThreadGate *g = gate_find(w);
    RtWaitable *gate = g ? g->gate : NULL;
    pthread_mutex_unlock(&thread_mu);
    if (!gate || gate->signaled) return 0; /* was not suspended */
    rt_waitable_signal(gate);
    return 1;
}

H(k32_ExitThread) {
    if (!t_start) {
        /* The main thread: the process lives on until its other threads end or call ExitProcess. */
        RtThread *th = rt_thread_of(c);
        rt_waitable_set_exit_code(th->done, a[0]);
        rt_waitable_signal(th->done);
        pthread_exit(NULL);
    }
    thread_finish(t_start, a[0]);
}

/* TerminateThread(handle, exitCode): the thread is cancelled at its next blocking
 * call; one that never blocks keeps running. Its guest stack is not released. */
H(k32_TerminateThread) {
    RtWaitable *w = rt_handle_get(a[0], RT_H_WAITABLE);
    if (!w || w->kind != RT_W_THREAD) {
        rt_set_last_error(c, ERROR_INVALID_HANDLE);
        return 0;
    }
    pthread_mutex_lock(&thread_mu);
    ThreadGate *g = gate_find(w);
    int live = g && !w->signaled;
    pthread_t pt = g ? g->pt : pthread_self();
    pthread_mutex_unlock(&thread_mu);
    if (live) {
        rt_log("recomp: TerminateThread(%#x, %u) called from thread %x\n", a[0], a[1], c->thread_id);
        pthread_cancel(pt);
        rt_waitable_set_exit_code(w, a[1]);
        rt_waitable_signal(w);
    }
    return 1;
}

H(k32_GetCurrentThreadId) { UNUSED; return c->thread_id; }

/* GetExitCodeProcess / thread-style query on a waitable (process handles are waitables too). */
H(k32_GetExitCodeProcess) {
    RtWaitable *w = rt_handle_get(a[0], RT_H_WAITABLE);
    if (!w) {
        rt_set_last_error(c, ERROR_INVALID_HANDLE);
        return 0;
    }
    pthread_mutex_lock(&sync_mu);
    st32(a[1], w->exit_code);
    pthread_mutex_unlock(&sync_mu);
    return 1;
}

/* -------------------------------------------------------- critical sections
 * A guest CRITICAL_SECTION is 24 bytes: DebugInfo, LockCount, RecursionCount,
 * OwningThread, LockSemaphore, SpinCount. The lock itself is a host recursive
 * mutex found through a tag stored in DebugInfo; the count fields are kept in
 * step for code that inspects them. A section that was never initialised (or
 * was zeroed) gets its mutex on first use. */
#define CS_TAG 0xC5000000u
#define CS_MAX 0x100000u

static pthread_mutex_t **cs_tab;
static uint32_t cs_count, cs_cap;
static uint32_t *cs_free;
static uint32_t cs_nfree;
static pthread_mutex_t cs_mu = PTHREAD_MUTEX_INITIALIZER;

static uint32_t cs_create(void) {
    pthread_mutex_t *m = malloc(sizeof *m);
    pthread_mutexattr_t at;
    pthread_mutexattr_init(&at);
    pthread_mutexattr_settype(&at, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(m, &at);
    pthread_mutexattr_destroy(&at);
    pthread_mutex_lock(&cs_mu);
    uint32_t i;
    if (cs_nfree) {
        i = cs_free[--cs_nfree];
    } else {
        if (cs_count == cs_cap) {
            /* The table is only ever replaced, never freed: readers index a snapshot without the lock. */
            uint32_t ncap = cs_cap ? cs_cap * 2 : 256;
            pthread_mutex_t **nt = malloc(ncap * sizeof *nt);
            if (cs_count) memcpy(nt, cs_tab, cs_count * sizeof *nt);
            __atomic_store_n(&cs_tab, nt, __ATOMIC_SEQ_CST);
            cs_cap = ncap;
        }
        if (cs_count >= CS_MAX) {
            fprintf(stderr, "recomp: too many critical sections\n");
            rt_exit(2);
        }
        i = cs_count++;
    }
    cs_tab[i] = m;
    pthread_mutex_unlock(&cs_mu);
    return CS_TAG | i;
}

static pthread_mutex_t *cs_get(uint32_t cs) {
    uint32_t tag = __atomic_load_n((uint32_t *)G(cs), __ATOMIC_SEQ_CST);
    if ((tag & 0xFF000000u) != CS_TAG || (tag & 0x00FFFFFFu) >= cs_count) {
        /* Not initialised: install a mutex, unless another thread gets there first. */
        uint32_t fresh = cs_create();
        uint32_t seen = rt_atomic_cmpxchg32(cs, tag, fresh);
        if (seen != tag) {
            pthread_mutex_lock(&cs_mu);
            cs_free = realloc(cs_free, (cs_nfree + 1) * sizeof *cs_free);
            cs_free[cs_nfree++] = fresh & 0x00FFFFFFu;
            pthread_mutex_unlock(&cs_mu);
            tag = seen;
        } else {
            tag = fresh;
            st32(cs + 4, 0xFFFFFFFFu);
            st32(cs + 8, 0);
            st32(cs + 12, 0);
        }
    }
    return __atomic_load_n(&cs_tab, __ATOMIC_SEQ_CST)[tag & 0x00FFFFFFu];
}

H(k32_InitializeCriticalSection) {
    UNUSED;
    memset(G(a[0]), 0, 24);
    st32(a[0], cs_create());
    st32(a[0] + 4, 0xFFFFFFFFu); /* LockCount */
    return 0;
}

H(k32_DeleteCriticalSection) {
    UNUSED;
    uint32_t tag = ld32(a[0]);
    if ((tag & 0xFF000000u) == CS_TAG && (tag & 0x00FFFFFFu) < cs_count) {
        uint32_t i = tag & 0x00FFFFFFu;
        pthread_mutex_lock(&cs_mu);
        pthread_mutex_t *m = cs_tab[i];
        cs_tab[i] = NULL;
        cs_free = realloc(cs_free, (cs_nfree + 1) * sizeof *cs_free);
        cs_free[cs_nfree++] = i;
        pthread_mutex_unlock(&cs_mu);
        if (m) {
            pthread_mutex_destroy(m);
            free(m);
        }
    }
    memset(G(a[0]), 0, 24);
    return 0;
}

H(k32_EnterCriticalSection) {
    pthread_mutex_t *m = cs_get(a[0]);
    if (!m) rt_fatal(c, 4, "EnterCriticalSection(%#x): the section's lock is gone (deleted while in use?)", a[0]);
    pthread_mutex_lock(m);
    st32(a[0] + 4, ld32(a[0] + 4) + 1);
    st32(a[0] + 8, ld32(a[0] + 8) + 1);
    st32(a[0] + 12, c->thread_id);
    return 0;
}

H(k32_LeaveCriticalSection) {
    pthread_mutex_t *m = cs_get(a[0]);
    if (!m || ld32(a[0] + 12) != c->thread_id || ld32(a[0] + 8) == 0) {
        rt_log("recomp: warning: LeaveCriticalSection(%#x) by thread %x, which does not own it (ignored)\n", a[0],
               c->thread_id);
        return 0;
    }
    uint32_t rec = ld32(a[0] + 8) - 1;
    st32(a[0] + 8, rec);
    st32(a[0] + 4, ld32(a[0] + 4) - 1);
    if (rec == 0) st32(a[0] + 12, 0);
    pthread_mutex_unlock(m);
    return 0;
}

H(k32_InterlockedExchange) { UNUSED; return rt_atomic_xchg32(a[0], a[1]); }

/* --------------------------------------------------------------------- TLS */
static uint8_t tls_used[TLS_SLOT_COUNT];
static pthread_mutex_t tls_mu = PTHREAD_MUTEX_INITIALIZER;

H(k32_TlsAlloc) {
    UNUSED;
    uint32_t slot = 0xFFFFFFFFu;
    pthread_mutex_lock(&tls_mu);
    for (uint32_t i = 0; i < TLS_SLOT_COUNT; i++) {
        if (!tls_used[i]) {
            tls_used[i] = 1;
            slot = i;
            break;
        }
    }
    pthread_mutex_unlock(&tls_mu);
    if (slot == 0xFFFFFFFFu) rt_set_last_error(c, 8);
    else st32(c->fs_base + TEB_TLS_SLOTS + 4 * slot, 0); /* other threads' slots still hold stale values */
    return slot;
}

H(k32_TlsFree) {
    UNUSED;
    if (a[0] >= TLS_SLOT_COUNT) return 0;
    pthread_mutex_lock(&tls_mu);
    tls_used[a[0]] = 0;
    pthread_mutex_unlock(&tls_mu);
    return 1;
}

H(k32_TlsGetValue) {
    if (a[0] >= TLS_SLOT_COUNT) {
        rt_set_last_error(c, 87);
        return 0;
    }
    rt_set_last_error(c, 0);
    return ld32(c->fs_base + TEB_TLS_SLOTS + 4 * a[0]);
}

H(k32_TlsSetValue) {
    if (a[0] >= TLS_SLOT_COUNT) {
        rt_set_last_error(c, 87);
        return 0;
    }
    st32(c->fs_base + TEB_TLS_SLOTS + 4 * a[0], a[1]);
    return 1;
}

static const ImportDef defs[] = {
    {"kernel32.dll", "CreateEventA", k32_CreateEventA, 4, 0},
    {"kernel32.dll", "OpenEventA", k32_OpenEventA, 3, 0},
    {"kernel32.dll", "SetEvent", k32_SetEvent, 1, 0},
    {"kernel32.dll", "ResetEvent", k32_ResetEvent, 1, 0},
    {"kernel32.dll", "CreateMutexA", k32_CreateMutexA, 3, 0},
    {"kernel32.dll", "ReleaseMutex", k32_ReleaseMutex, 1, 0},
    {"kernel32.dll", "WaitForSingleObject", k32_WaitForSingleObject, 2, 0},
    {"kernel32.dll", "WaitForMultipleObjects", k32_WaitForMultipleObjects, 4, 0},
    {"kernel32.dll", "CloseHandle", k32_CloseHandle, 1, 0},
    {"kernel32.dll", "Sleep", k32_Sleep, 1, 0},
    {"kernel32.dll", "CreateThread", k32_CreateThread, 6, 0},
    {"kernel32.dll", "ResumeThread", k32_ResumeThread, 1, 0},
    {"kernel32.dll", "ExitThread", k32_ExitThread, 1, 0},
    {"kernel32.dll", "TerminateThread", k32_TerminateThread, 2, 0},
    {"kernel32.dll", "GetCurrentThreadId", k32_GetCurrentThreadId, 0, 0},
    {"kernel32.dll", "GetExitCodeProcess", k32_GetExitCodeProcess, 2, 0},
    {"kernel32.dll", "InitializeCriticalSection", k32_InitializeCriticalSection, 1, 0},
    {"kernel32.dll", "DeleteCriticalSection", k32_DeleteCriticalSection, 1, 0},
    {"kernel32.dll", "EnterCriticalSection", k32_EnterCriticalSection, 1, 0},
    {"kernel32.dll", "LeaveCriticalSection", k32_LeaveCriticalSection, 1, 0},
    {"kernel32.dll", "InterlockedExchange", k32_InterlockedExchange, 2, 0},
    {"kernel32.dll", "TlsAlloc", k32_TlsAlloc, 0, 0},
    {"kernel32.dll", "TlsFree", k32_TlsFree, 1, 0},
    {"kernel32.dll", "TlsGetValue", k32_TlsGetValue, 1, 0},
    {"kernel32.dll", "TlsSetValue", k32_TlsSetValue, 2, 0},
};
RT_EXPORT_IMPORTS(rt_imports_thread, defs);
