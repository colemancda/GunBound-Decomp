/* user32, gdi32 and imm32: window classes, windows, message queues, timers and input.
 *
 * Windows are bookkeeping only; nothing is drawn through them. The game's screen
 * reaches the host through DirectDraw (ddraw.c) and video.c. Each guest thread
 * has its own message queue. Input arrives from video.c on the thread that
 * opened the host window and is posted to the main window or the focus window.
 * A built-in EDIT class keeps the text the game types into its shared input
 * control; STATIC exists because the network engine creates hidden STATIC
 * windows to receive notifications.
 */
#define _GNU_SOURCE
#include <ctype.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

#include "rt.h"
#include "user.h"
#include "video.h"

#define WM_CREATE 0x0001
#define WM_DESTROY 0x0002
#define WM_MOVE 0x0003
#define WM_SIZE 0x0005
#define WM_ACTIVATE 0x0006
#define WM_SETFOCUS 0x0007
#define WM_KILLFOCUS 0x0008
#define WM_SETTEXT 0x000C
#define WM_GETTEXT 0x000D
#define WM_GETTEXTLENGTH 0x000E
#define WM_PAINT 0x000F
#define WM_CLOSE 0x0010
#define WM_QUIT 0x0012
#define WM_ERASEBKGND 0x0014
#define WM_SHOWWINDOW 0x0018
#define WM_ACTIVATEAPP 0x001C
#define WM_NCCREATE 0x0081
#define WM_NCDESTROY 0x0082
#define WM_KEYDOWN 0x0100
#define WM_KEYUP 0x0101
#define WM_CHAR 0x0102
#define WM_SYSKEYDOWN 0x0104
#define WM_SYSKEYUP 0x0105
#define WM_SYSCOMMAND 0x0112
#define WM_TIMER 0x0113
#define WM_MOUSEMOVE 0x0200
#define WM_LBUTTONDOWN 0x0201
#define WM_LBUTTONUP 0x0202
#define WM_LBUTTONDBLCLK 0x0203
#define WM_RBUTTONDOWN 0x0204
#define WM_RBUTTONUP 0x0205
#define WM_RBUTTONDBLCLK 0x0206
#define WM_MBUTTONDOWN 0x0207
#define WM_MBUTTONUP 0x0208
#define EM_GETSEL 0x00B0
#define EM_SETSEL 0x00B1
#define EM_LIMITTEXT 0x00C5
#define SC_CLOSE 0xF060
#define CS_DBLCLKS 0x0008
#define WS_CHILD 0x40000000u
#define WS_VISIBLE 0x10000000u
#define GWL_WNDPROC (-4)
#define GWL_HINSTANCE (-6)
#define GWL_HWNDPARENT (-8)
#define GWL_ID (-12)
#define GWL_STYLE (-16)
#define GWL_EXSTYLE (-20)
#define GWL_USERDATA (-21)
#define PM_REMOVE 1

#define SCREEN_W 800
#define SCREEN_H 600
#define HWND_BASE 0x00010100u
#define HDC_FAKE 0x0000DC00u

typedef struct WndClass {
    char *name;
    uint32_t wndproc, style, cls_extra, wnd_extra, hinstance, hcursor;
    struct WndClass *next;
} WndClass;

typedef struct Window {
    uint32_t hwnd;
    WndClass *cls;
    RtThread *owner;
    uint32_t wndproc, style, exstyle, parent, id, hinstance, userdata;
    int x, y, w, h;
    int visible, destroying;
    char *text;
    uint32_t text_limit, sel_start, sel_end; /* EDIT */
    uint8_t extra[64];
} Window;

typedef struct SendCtx {
    int done;
    uint32_t result;
} SendCtx;

typedef struct QMsg {
    uint32_t hwnd, msg, wparam, lparam, time;
    int32_t x, y;
    SendCtx *send; /* non-NULL: a cross-thread SendMessage waiting for the result */
} QMsg;

typedef struct MsgQueue {
    QMsg *buf;
    size_t count, cap;
    int quit;
    uint32_t quit_code;
} MsgQueue;

typedef struct Timer {
    uint32_t hwnd, id, proc, period_ms;
    uint64_t due_ns;
    RtThread *owner;
    int used;
} Timer;

/* One lock for all of user32's tables and queues; never held across a call into the guest. */
static pthread_mutex_t user_mu = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t user_cv;
static pthread_once_t user_once = PTHREAD_ONCE_INIT;
static WndClass *classes;
static Window **windows;
static uint32_t nwindows;
static Timer timers[64];
static uint32_t next_timer_id = 0x7F00;
static uint32_t main_hwnd, focus_hwnd, active_hwnd;
static int cursor_count;
static uint32_t current_cursor = 0x00010003u;
static uint32_t def_proc_addr, edit_proc_addr, static_proc_addr;

static uint32_t now_ms(void) { return (uint32_t)(rt_mono_ns() / 1000000ull); }

static uint32_t user_DefWindowProcA(CPU *c, const uint32_t *a);
static uint32_t edit_wndproc(CPU *c, const uint32_t *a);

static void add_class(const char *name, uint32_t proc, uint32_t style, uint32_t extra, uint32_t hinst) {
    WndClass *k = calloc(1, sizeof *k);
    k->name = strdup(name);
    k->wndproc = proc;
    k->style = style;
    k->wnd_extra = extra;
    k->hinstance = hinst;
    k->next = classes;
    classes = k;
}

static void user_init(void) {
    pthread_condattr_t at;
    pthread_condattr_init(&at);
    pthread_condattr_setclock(&at, CLOCK_MONOTONIC);
    pthread_cond_init(&user_cv, &at);
    def_proc_addr = rt_host_fn("user32.dll", "DefWindowProcA", user_DefWindowProcA, 4);
    edit_proc_addr = rt_host_fn("user32.dll", "<EDIT window procedure>", edit_wndproc, 4);
    static_proc_addr = def_proc_addr;
    add_class("EDIT", edit_proc_addr, 0, 0, 0);
    add_class("STATIC", static_proc_addr, 0, 0, 0);
}

static WndClass *find_class(const char *name) {
    for (WndClass *k = classes; k; k = k->next)
        if (!strcasecmp(k->name, name)) return k;
    return NULL;
}

/* Under user_mu. */
static Window *win_get(uint32_t hwnd) {
    uint32_t i = (hwnd - HWND_BASE) / 4;
    if (hwnd < HWND_BASE || (hwnd & 3) || i >= nwindows) return NULL;
    return windows[i];
}

static MsgQueue *queue_of(RtThread *th) {
    if (!th->msgq) th->msgq = calloc(1, sizeof(MsgQueue));
    return th->msgq;
}

/* Under user_mu. */
static void queue_push(RtThread *th, const QMsg *m) {
    MsgQueue *q = queue_of(th);
    if (q->count == q->cap) {
        q->cap = q->cap ? q->cap * 2 : 64;
        q->buf = realloc(q->buf, q->cap * sizeof *q->buf);
    }
    q->buf[q->count++] = *m;
    pthread_cond_broadcast(&user_cv);
}

int rt_post_message(uint32_t hwnd, uint32_t msg, uint32_t wparam, uint32_t lparam) {
    pthread_once(&user_once, user_init);
    int ok = 0;
    pthread_mutex_lock(&user_mu);
    Window *w = win_get(hwnd);
    if (w && !w->destroying) {
        QMsg m = {hwnd, msg, wparam, lparam, now_ms(), rt_mouse_x, rt_mouse_y, NULL};
        queue_push(w->owner, &m);
        ok = 1;
    }
    pthread_mutex_unlock(&user_mu);
    return ok;
}

/* Calls a window procedure. Returns 0 if a non-local return passed through (see rt_call_guest). */
static int call_proc(CPU *c, uint32_t proc, uint32_t hwnd, uint32_t msg, uint32_t wp, uint32_t lp, uint32_t *res) {
    uint32_t args[4] = {hwnd, msg, wp, lp};
    if (g_opt.verbose && msg != WM_MOUSEMOVE && msg != WM_TIMER)
        rt_log("[msg %x] hwnd %x msg %04x wparam %x lparam %x -> proc %08x\n", c->thread_id, hwnd, msg, wp, lp, proc);
    if (!proc) {
        if (res) *res = 0;
        return 1;
    }
    return rt_call_guest(c, proc, RT_STDCALL, 4, args, res);
}

/* SendMessage semantics: direct call on the owning thread, queued and awaited otherwise. */
static int send_message(CPU *c, uint32_t hwnd, uint32_t msg, uint32_t wp, uint32_t lp, uint32_t *res) {
    pthread_mutex_lock(&user_mu);
    Window *w = win_get(hwnd);
    if (!w) {
        pthread_mutex_unlock(&user_mu);
        if (res) *res = 0;
        return 1;
    }
    uint32_t proc = w->wndproc;
    RtThread *owner = w->owner;
    if (owner == rt_thread_of(c)) {
        pthread_mutex_unlock(&user_mu);
        return call_proc(c, proc, hwnd, msg, wp, lp, res);
    }
    SendCtx ctx = {0, 0};
    QMsg m = {hwnd, msg, wp, lp, now_ms(), 0, 0, &ctx};
    queue_push(owner, &m);
    while (!ctx.done) pthread_cond_wait(&user_cv, &user_mu);
    pthread_mutex_unlock(&user_mu);
    if (res) *res = ctx.result;
    return 1;
}

/* -------------------------------------------------------------- classes */
H(user_RegisterClassA) {
    pthread_once(&user_once, user_init);
    uint32_t p = a[0];
    const char *name = rt_gstr(ld32(p + 36));
    if (ld32(p + 36) < 0x10000) {
        rt_log("recomp: RegisterClassA with an atom instead of a name is not supported\n");
        return 0;
    }
    pthread_mutex_lock(&user_mu);
    if (find_class(name)) {
        pthread_mutex_unlock(&user_mu);
        rt_set_last_error(c, 1410); /* ERROR_CLASS_ALREADY_EXISTS */
        return 0;
    }
    add_class(name, ld32(p + 4), ld32(p), ld32(p + 12), ld32(p + 16));
    classes->cls_extra = ld32(p + 8);
    classes->hcursor = ld32(p + 24);
    pthread_mutex_unlock(&user_mu);
    if (g_opt.verbose) rt_log("[user] class \"%s\" registered, window procedure %08x\n", name, ld32(p + 4));
    return 0xC000u + (nwindows & 0xFFF) + 1;
}

/* -------------------------------------------------------------- windows */
static void activate_window(CPU *c, uint32_t hwnd);

/* CreateWindowExA(exStyle, class, name, style, x, y, w, h, parent, menu, instance, param) */
H(user_CreateWindowExA) {
    pthread_once(&user_once, user_init);
    if (a[1] < 0x10000) {
        rt_log("recomp: CreateWindowExA with a class atom is not supported\n");
        return 0;
    }
    const char *cname = rt_gstr(a[1]);
    pthread_mutex_lock(&user_mu);
    WndClass *k = find_class(cname);
    if (!k) {
        pthread_mutex_unlock(&user_mu);
        rt_log("recomp: CreateWindowExA: unknown window class \"%s\"\n", cname);
        rt_set_last_error(c, 1407); /* ERROR_CANNOT_FIND_WND_CLASS */
        return 0;
    }
    Window *w = calloc(1, sizeof *w);
    uint32_t i;
    for (i = 0; i < nwindows; i++)
        if (!windows[i]) break;
    if (i == nwindows) {
        windows = realloc(windows, (nwindows + 16) * sizeof *windows);
        memset(windows + nwindows, 0, 16 * sizeof *windows);
        nwindows += 16;
    }
    windows[i] = w;
    w->hwnd = HWND_BASE + 4 * i;
    w->cls = k;
    w->owner = rt_thread_of(c);
    w->wndproc = k->wndproc;
    w->exstyle = a[0];
    w->style = a[3];
    w->x = (int32_t)a[4];
    w->y = (int32_t)a[5];
    w->w = (int32_t)a[6];
    w->h = (int32_t)a[7];
    w->parent = a[8];
    w->id = a[9];
    w->hinstance = a[10];
    w->text = strdup(a[2] ? rt_gstr(a[2]) : "");
    w->text_limit = 30000;
    w->visible = (a[3] & WS_VISIBLE) != 0;
    uint32_t hwnd = w->hwnd, proc = w->wndproc;
    queue_of(w->owner);
    pthread_mutex_unlock(&user_mu);
    if (g_opt.verbose || g_trace_imports)
        rt_log("[user] window %x created: class \"%s\" name \"%s\" style %08x %dx%d parent %x thread %x\n", hwnd, cname,
               a[2] ? rt_gstr(a[2]) : "", a[3], (int32_t)a[6], (int32_t)a[7], a[8], c->thread_id);

    /* CREATESTRUCTA on the guest stack for WM_NCCREATE and WM_CREATE. */
    uint32_t sp = ESP;
    uint32_t cs = (sp - 64) & ~3u;
    st32(cs + 0, a[11]);
    st32(cs + 4, a[10]);
    st32(cs + 8, a[9]);
    st32(cs + 12, a[8]);
    st32(cs + 16, a[7]);
    st32(cs + 20, a[6]);
    st32(cs + 24, a[5]);
    st32(cs + 28, a[4]);
    st32(cs + 32, a[3]);
    st32(cs + 36, a[2]);
    st32(cs + 40, a[1]);
    st32(cs + 44, a[0]);
    ESP = cs - 16;
    uint32_t r = 0;
    if (!call_proc(c, proc, hwnd, WM_NCCREATE, 0, cs, &r)) return 0;
    if (!call_proc(c, proc, hwnd, WM_CREATE, 0, cs, &r)) return 0;
    ESP = sp;
    if (r == 0xFFFFFFFFu) {
        pthread_mutex_lock(&user_mu);
        windows[i] = NULL;
        pthread_mutex_unlock(&user_mu);
        free(w->text);
        free(w);
        return 0;
    }
    return hwnd;
}

static int destroy_window(CPU *c, uint32_t hwnd) {
    pthread_mutex_lock(&user_mu);
    Window *w = win_get(hwnd);
    if (!w || w->destroying) {
        pthread_mutex_unlock(&user_mu);
        return 1;
    }
    w->destroying = 1;
    uint32_t proc = w->wndproc;
    uint32_t children[64];
    unsigned nchildren = 0;
    for (uint32_t i = 0; i < nwindows && nchildren < 64; i++)
        if (windows[i] && windows[i]->parent == hwnd && !windows[i]->destroying) children[nchildren++] = windows[i]->hwnd;
    pthread_mutex_unlock(&user_mu);

    uint32_t r;
    if (!call_proc(c, proc, hwnd, WM_DESTROY, 0, 0, &r)) return 0;
    for (unsigned i = 0; i < nchildren; i++)
        if (!destroy_window(c, children[i])) return 0;
    if (!call_proc(c, proc, hwnd, WM_NCDESTROY, 0, 0, &r)) return 0;

    pthread_mutex_lock(&user_mu);
    for (size_t i = 0; i < RT_COUNTOF(timers); i++)
        if (timers[i].used && timers[i].hwnd == hwnd) timers[i].used = 0;
    MsgQueue *q = w->owner->msgq;
    if (q) {
        size_t o = 0;
        for (size_t i = 0; i < q->count; i++) {
            if (q->buf[i].hwnd == hwnd) {
                if (q->buf[i].send) q->buf[i].send->done = 1;
                continue;
            }
            q->buf[o++] = q->buf[i];
        }
        q->count = o;
        pthread_cond_broadcast(&user_cv);
    }
    windows[(hwnd - HWND_BASE) / 4] = NULL;
    if (focus_hwnd == hwnd) focus_hwnd = 0;
    if (active_hwnd == hwnd) active_hwnd = 0;
    if (main_hwnd == hwnd) main_hwnd = 0;
    pthread_mutex_unlock(&user_mu);
    free(w->text);
    free(w);
    return 1;
}

H(user_DestroyWindow) {
    pthread_mutex_lock(&user_mu);
    int ok = win_get(a[0]) != NULL;
    pthread_mutex_unlock(&user_mu);
    if (!ok) {
        rt_set_last_error(c, 1400); /* ERROR_INVALID_WINDOW_HANDLE */
        return 0;
    }
    destroy_window(c, a[0]);
    return 1;
}

static void set_window_text(Window *w, const char *s) {
    free(w->text);
    w->text = strdup(s);
    size_t n = strlen(w->text);
    w->sel_start = w->sel_end = (uint32_t)n;
}

/* DefWindowProcA(hwnd, msg, wparam, lparam) */
static uint32_t user_DefWindowProcA(CPU *c, const uint32_t *a) {
    uint32_t hwnd = a[0], msg = a[1], wp = a[2], lp = a[3], r = 0;
    switch (msg) {
    case WM_NCCREATE:
        return 1;
    case WM_CLOSE:
        destroy_window(c, hwnd);
        return 0;
    case WM_SYSCOMMAND:
        if ((wp & 0xFFF0) == SC_CLOSE) send_message(c, hwnd, WM_CLOSE, 0, 0, &r);
        return 0;
    case WM_ERASEBKGND:
        return 1;
    case WM_GETTEXTLENGTH:
    case WM_GETTEXT:
    case WM_SETTEXT: {
        pthread_mutex_lock(&user_mu);
        Window *w = win_get(hwnd);
        if (w) {
            if (msg == WM_SETTEXT) {
                set_window_text(w, lp ? rt_gstr(lp) : "");
                r = 1;
            } else if (msg == WM_GETTEXTLENGTH) {
                r = (uint32_t)strlen(w->text);
            } else if (wp) {
                size_t n = strlen(w->text);
                if (n >= wp) n = wp - 1;
                memcpy(G(lp), w->text, n);
                st8(lp + (uint32_t)n, 0);
                r = (uint32_t)n;
            }
        }
        pthread_mutex_unlock(&user_mu);
        return r;
    }
    default:
        return 0;
    }
}

/* The built-in EDIT class: a single-line text buffer edited by WM_CHAR. */
static uint32_t edit_wndproc(CPU *c, const uint32_t *a) {
    uint32_t hwnd = a[0], msg = a[1], wp = a[2], lp = a[3], r = 0;
    pthread_mutex_lock(&user_mu);
    Window *w = win_get(hwnd);
    if (!w) {
        pthread_mutex_unlock(&user_mu);
        return 0;
    }
    size_t len = strlen(w->text);
    switch (msg) {
    case EM_LIMITTEXT:
        w->text_limit = wp ? wp : 30000;
        break;
    case EM_SETSEL:
        w->sel_start = wp > len ? (uint32_t)len : wp;
        w->sel_end = lp > len ? (uint32_t)len : lp;
        break;
    case EM_GETSEL:
        if (wp) st32(wp, w->sel_start);
        if (lp) st32(lp, w->sel_end);
        r = (w->sel_start & 0xFFFF) | (w->sel_end << 16);
        break;
    case WM_CHAR: {
        uint32_t s = w->sel_start < w->sel_end ? w->sel_start : w->sel_end;
        uint32_t e = w->sel_start < w->sel_end ? w->sel_end : w->sel_start;
        if (s > len) s = (uint32_t)len;
        if (e > len) e = (uint32_t)len;
        if (wp == 8) { /* backspace */
            if (s == e && s > 0) s--;
            memmove(w->text + s, w->text + e, len - e + 1);
            w->sel_start = w->sel_end = s;
        } else if (wp >= 0x20 && wp != 0x7F && wp < 0x100) {
            if (len - (e - s) + 1 <= w->text_limit) {
                char *t = malloc(len + 2);
                memcpy(t, w->text, s);
                t[s] = (char)wp;
                memcpy(t + s + 1, w->text + e, len - e + 1);
                free(w->text);
                w->text = t;
                w->sel_start = w->sel_end = s + 1;
            }
        }
        break;
    }
    case WM_KEYDOWN:
        if (wp == 0x2E && w->sel_start < len) { /* VK_DELETE */
            memmove(w->text + w->sel_start, w->text + w->sel_start + 1, len - w->sel_start);
        } else if (wp == 0x25 && w->sel_start > 0) { /* VK_LEFT */
            w->sel_start = w->sel_end = w->sel_start - 1;
        } else if (wp == 0x27 && w->sel_start < len) { /* VK_RIGHT */
            w->sel_start = w->sel_end = w->sel_start + 1;
        } else if (wp == 0x24) { /* VK_HOME */
            w->sel_start = w->sel_end = 0;
        } else if (wp == 0x23) { /* VK_END */
            w->sel_start = w->sel_end = (uint32_t)len;
        }
        break;
    default:
        pthread_mutex_unlock(&user_mu);
        return user_DefWindowProcA(c, a);
    }
    pthread_mutex_unlock(&user_mu);
    return r;
}

H(user_CallWindowProcA) {
    uint32_t r = 0;
    call_proc(c, a[0], a[1], a[2], a[3], a[4], &r);
    return r;
}

H(user_SendMessageA) {
    uint32_t r = 0;
    send_message(c, a[0], a[1], a[2], a[3], &r);
    return r;
}

H(user_GetWindowLongA) {
    UNUSED;
    int32_t idx = (int32_t)a[1];
    uint32_t r = 0;
    pthread_mutex_lock(&user_mu);
    Window *w = win_get(a[0]);
    if (w) {
        switch (idx) {
        case GWL_WNDPROC: r = w->wndproc; break;
        case GWL_HINSTANCE: r = w->hinstance; break;
        case GWL_HWNDPARENT: r = w->parent; break;
        case GWL_ID: r = w->id; break;
        case GWL_STYLE: r = w->style | (w->visible ? WS_VISIBLE : 0); break;
        case GWL_EXSTYLE: r = w->exstyle; break;
        case GWL_USERDATA: r = w->userdata; break;
        default:
            if (idx >= 0 && (size_t)idx + 4 <= sizeof w->extra) memcpy(&r, w->extra + idx, 4);
            break;
        }
    }
    pthread_mutex_unlock(&user_mu);
    return r;
}

H(user_SetWindowLongA) {
    UNUSED;
    int32_t idx = (int32_t)a[1];
    uint32_t r = 0, v = a[2];
    pthread_mutex_lock(&user_mu);
    Window *w = win_get(a[0]);
    if (w) {
        switch (idx) {
        case GWL_WNDPROC: r = w->wndproc; w->wndproc = v; break;
        case GWL_HINSTANCE: r = w->hinstance; w->hinstance = v; break;
        case GWL_HWNDPARENT: r = w->parent; w->parent = v; break;
        case GWL_ID: r = w->id; w->id = v; break;
        case GWL_STYLE: r = w->style; w->style = v; break;
        case GWL_EXSTYLE: r = w->exstyle; w->exstyle = v; break;
        case GWL_USERDATA: r = w->userdata; w->userdata = v; break;
        default:
            if (idx >= 0 && (size_t)idx + 4 <= sizeof w->extra) {
                memcpy(&r, w->extra + idx, 4);
                memcpy(w->extra + idx, &v, 4);
            }
            break;
        }
    }
    pthread_mutex_unlock(&user_mu);
    return r;
}

H(user_GetWindowTextA) {
    uint32_t r = 0;
    send_message(c, a[0], WM_GETTEXT, a[2], a[1], &r);
    return r;
}

H(user_SetWindowTextA) {
    uint32_t r = 0;
    send_message(c, a[0], WM_SETTEXT, 0, a[1], &r);
    if (a[0] == main_hwnd) rt_video_set_title(rt_gstr(a[1]));
    return 1;
}

static int is_top_level_game_window(const Window *w) {
    return w && !(w->style & WS_CHILD) && w->wndproc != def_proc_addr && w->wndproc != edit_proc_addr;
}

/* Make hwnd the active window of the application, with the messages Windows sends. */
static void activate_window(CPU *c, uint32_t hwnd) {
    pthread_mutex_lock(&user_mu);
    Window *w = win_get(hwnd);
    int go = w && active_hwnd != hwnd && is_top_level_game_window(w);
    uint32_t old = active_hwnd;
    if (go) active_hwnd = hwnd;
    pthread_mutex_unlock(&user_mu);
    if (!go) return;
    uint32_t r;
    if (!old && !send_message(c, hwnd, WM_ACTIVATEAPP, 1, 0, &r)) return;
    send_message(c, hwnd, WM_ACTIVATE, 1, old, &r);
}

static uint32_t set_focus(CPU *c, uint32_t hwnd) {
    pthread_mutex_lock(&user_mu);
    uint32_t old = focus_hwnd;
    int valid = hwnd == 0 || win_get(hwnd) != NULL;
    if (valid) focus_hwnd = hwnd;
    pthread_mutex_unlock(&user_mu);
    if (!valid || old == hwnd) return old;
    uint32_t r;
    if (old && !send_message(c, old, WM_KILLFOCUS, hwnd, 0, &r)) return old;
    if (hwnd) send_message(c, hwnd, WM_SETFOCUS, old, 0, &r);
    return old;
}

H(user_SetFocus) { return set_focus(c, a[0]); }

H(user_SetForegroundWindow) {
    activate_window(c, a[0]);
    return 1;
}

H(user_ShowWindow) {
    pthread_mutex_lock(&user_mu);
    Window *w = win_get(a[0]);
    if (!w) {
        pthread_mutex_unlock(&user_mu);
        return 0;
    }
    int was = w->visible, show = a[1] != 0;
    w->visible = show;
    int top = is_top_level_game_window(w);
    char title[128];
    snprintf(title, sizeof title, "%s", w->text);
    if (top && show && !main_hwnd) main_hwnd = a[0];
    int is_main = main_hwnd == a[0];
    pthread_mutex_unlock(&user_mu);
    if (was != show) {
        uint32_t r;
        if (!send_message(c, a[0], WM_SHOWWINDOW, (uint32_t)show, 0, &r)) return 0;
    }
    if (is_main && show) {
        rt_video_open(title, SCREEN_W, SCREEN_H);
        activate_window(c, a[0]);
        if (c->eip == RT_NL_PENDING) return 0;
        pthread_mutex_lock(&user_mu);
        int need_focus = focus_hwnd == 0;
        pthread_mutex_unlock(&user_mu);
        if (need_focus) set_focus(c, a[0]);
    }
    return (uint32_t)was;
}

H(user_UpdateWindow) { UNUSED; return 1; }

H(user_GetClientRect) {
    UNUSED;
    pthread_mutex_lock(&user_mu);
    Window *w = win_get(a[0]);
    int ww = 0, hh = 0, ok = w != NULL;
    if (w) {
        ww = w->w;
        hh = w->h;
        /* DirectDraw sizes the main window to the display mode. */
        if (a[0] == main_hwnd) {
            ww = SCREEN_W;
            hh = SCREEN_H;
        }
    }
    pthread_mutex_unlock(&user_mu);
    st32(a[1], 0);
    st32(a[1] + 4, 0);
    st32(a[1] + 8, (uint32_t)ww);
    st32(a[1] + 12, (uint32_t)hh);
    return (uint32_t)ok;
}

H(user_ClientToScreen) {
    UNUSED;
    pthread_mutex_lock(&user_mu);
    Window *w = win_get(a[0]);
    int ok = w != NULL, x = 0, y = 0;
    if (w && (w->style & WS_CHILD)) {
        x = w->x;
        y = w->y;
    }
    pthread_mutex_unlock(&user_mu);
    st32(a[1], ld32(a[1]) + (uint32_t)x);
    st32(a[1] + 4, ld32(a[1] + 4) + (uint32_t)y);
    return (uint32_t)ok;
}

/* ---------------------------------------------------------------- timers */
H(user_SetTimer) {
    pthread_once(&user_once, user_init);
    uint32_t id = a[1];
    pthread_mutex_lock(&user_mu);
    Window *w = a[0] ? win_get(a[0]) : NULL;
    RtThread *owner = w ? w->owner : rt_thread_of(c);
    Timer *t = NULL;
    for (size_t i = 0; i < RT_COUNTOF(timers) && !t; i++)
        if (timers[i].used && timers[i].hwnd == a[0] && timers[i].id == id && a[0]) t = &timers[i];
    for (size_t i = 0; i < RT_COUNTOF(timers) && !t; i++)
        if (!timers[i].used) t = &timers[i];
    if (!t || (a[0] && !w)) {
        pthread_mutex_unlock(&user_mu);
        return 0;
    }
    if (!a[0]) id = next_timer_id++;
    t->used = 1;
    t->hwnd = a[0];
    t->id = id;
    t->proc = a[3];
    t->period_ms = a[2] < 10 ? 10 : a[2];
    t->due_ns = rt_mono_ns() + (uint64_t)t->period_ms * 1000000ull;
    t->owner = owner;
    queue_of(owner);
    pthread_cond_broadcast(&user_cv);
    pthread_mutex_unlock(&user_mu);
    return id ? id : 1;
}

H(user_KillTimer) {
    UNUSED;
    uint32_t r = 0;
    pthread_mutex_lock(&user_mu);
    for (size_t i = 0; i < RT_COUNTOF(timers); i++) {
        if (timers[i].used && timers[i].hwnd == a[0] && timers[i].id == a[1]) {
            timers[i].used = 0;
            r = 1;
        }
    }
    pthread_mutex_unlock(&user_mu);
    return r;
}

/* ------------------------------------------------------------ the queue */
static void write_msg(uint32_t p, const QMsg *m) {
    st32(p, m->hwnd);
    st32(p + 4, m->msg);
    st32(p + 8, m->wparam);
    st32(p + 12, m->lparam);
    st32(p + 16, m->time);
    st32(p + 20, (uint32_t)m->x);
    st32(p + 24, (uint32_t)m->y);
}

static uint32_t key_lparam(const RtInputEvent *ev) {
    uint32_t lp = 1u | ((uint32_t)(ev->scan & 0x7F) << 16);
    if (ev->scan & 0x80) lp |= 1u << 24;
    if (!ev->down) lp |= 0xC0000000u;
    else if (ev->repeat) lp |= 0x40000000u;
    return lp;
}

static uint32_t mouse_wparam(void) {
    uint32_t wp = 0;
    if (rt_mouse_buttons & 1) wp |= 0x01;
    if (rt_mouse_buttons & 2) wp |= 0x02;
    if (rt_mouse_buttons & 4) wp |= 0x10;
    if (rt_vk_state[0x10] & 0x80) wp |= 0x04;
    if (rt_vk_state[0x11] & 0x80) wp |= 0x08;
    return wp;
}

/* Turn pending host input into posted messages. Video thread only. */
static void pump_input(void) {
    RtInputEvent ev;
    while (rt_video_poll(&ev)) {
        pthread_mutex_lock(&user_mu);
        Window *mw = win_get(main_hwnd);
        if (!mw) {
            pthread_mutex_unlock(&user_mu);
            continue;
        }
        QMsg m = {main_hwnd, 0, 0, 0, now_ms(), ev.x, ev.y, NULL};
        uint32_t pos = ((uint32_t)ev.y << 16) | ((uint32_t)ev.x & 0xFFFF);
        Window *fw = win_get(focus_hwnd);
        switch (ev.type) {
        case RT_EV_MOUSE_MOVE:
            m.msg = WM_MOUSEMOVE;
            m.wparam = mouse_wparam();
            m.lparam = pos;
            break;
        case RT_EV_MOUSE_BUTTON: {
            int dbl = ev.down && ev.repeat > 1 && !(ev.repeat & 1) && (mw->cls->style & CS_DBLCLKS);
            if (ev.code == 1) m.msg = ev.down ? (dbl ? WM_LBUTTONDBLCLK : WM_LBUTTONDOWN) : WM_LBUTTONUP;
            else if (ev.code == 3) m.msg = ev.down ? (dbl ? WM_RBUTTONDBLCLK : WM_RBUTTONDOWN) : WM_RBUTTONUP;
            else m.msg = ev.down ? WM_MBUTTONDOWN : WM_MBUTTONUP;
            m.wparam = mouse_wparam();
            m.lparam = pos;
            break;
        }
        case RT_EV_KEY: {
            int sys = (rt_vk_state[0x12] & 0x80) || ev.code == 0x79; /* Alt held, or F10 */
            m.hwnd = fw ? focus_hwnd : main_hwnd;
            m.msg = ev.down ? (sys ? WM_SYSKEYDOWN : WM_KEYDOWN) : (sys ? WM_SYSKEYUP : WM_KEYUP);
            m.wparam = (uint32_t)ev.code;
            m.lparam = key_lparam(&ev);
            break;
        }
        case RT_EV_CHAR:
            m.hwnd = fw ? focus_hwnd : main_hwnd;
            m.msg = WM_CHAR;
            m.wparam = (uint32_t)ev.code;
            m.lparam = 1;
            break;
        case RT_EV_FOCUS:
            m.msg = WM_ACTIVATEAPP;
            m.wparam = (uint32_t)ev.down;
            break;
        case RT_EV_QUIT:
            m.msg = WM_SYSCOMMAND;
            m.wparam = SC_CLOSE;
            break;
        default:
            break;
        }
        if (m.msg) queue_push(win_get(m.hwnd)->owner, &m);
        pthread_mutex_unlock(&user_mu);
    }
}

static int msg_matches(const QMsg *m, uint32_t hwnd, uint32_t lo, uint32_t hi) {
    if (hwnd && m->hwnd != hwnd) {
        /* a filter on a window also accepts messages for its children */
        Window *w = win_get(m->hwnd);
        if (!w || w->parent != hwnd) return 0;
    }
    if ((lo || hi) && (m->msg < lo || m->msg > hi)) return 0;
    return 1;
}

/* Returns 1 with *out filled when a message is available. Messages sent from other
 * threads are delivered here, before anything is returned. Returns -1 when a
 * non-local return passed through a window procedure. */
static int peek(CPU *c, QMsg *out, uint32_t hwnd, uint32_t lo, uint32_t hi, int remove) {
    RtThread *th = rt_thread_of(c);
    if (rt_video_on_video_thread()) pump_input();
    pthread_mutex_lock(&user_mu);
    MsgQueue *q = queue_of(th);
    for (;;) {
        size_t i;
        for (i = 0; i < q->count; i++)
            if (q->buf[i].send) break;
        if (i == q->count) break;
        QMsg m = q->buf[i];
        memmove(q->buf + i, q->buf + i + 1, (q->count - i - 1) * sizeof *q->buf);
        q->count--;
        Window *w = win_get(m.hwnd);
        uint32_t proc = w ? w->wndproc : 0;
        pthread_mutex_unlock(&user_mu);
        uint32_t r = 0;
        int ok = call_proc(c, proc, m.hwnd, m.msg, m.wparam, m.lparam, &r);
        pthread_mutex_lock(&user_mu);
        m.send->result = r;
        m.send->done = 1;
        pthread_cond_broadcast(&user_cv);
        if (!ok) {
            pthread_mutex_unlock(&user_mu);
            return -1;
        }
    }
    for (size_t i = 0; i < q->count; i++) {
        if (!msg_matches(&q->buf[i], hwnd, lo, hi)) continue;
        *out = q->buf[i];
        if (remove) {
            memmove(q->buf + i, q->buf + i + 1, (q->count - i - 1) * sizeof *q->buf);
            q->count--;
        }
        pthread_mutex_unlock(&user_mu);
        return 1;
    }
    if (q->quit && q->count == 0 && !hwnd) {
        QMsg m = {0, WM_QUIT, q->quit_code, 0, now_ms(), 0, 0, NULL};
        *out = m;
        if (remove) q->quit = 0;
        pthread_mutex_unlock(&user_mu);
        return 1;
    }
    uint64_t now = rt_mono_ns();
    for (size_t i = 0; i < RT_COUNTOF(timers); i++) {
        Timer *t = &timers[i];
        if (!t->used || t->owner != th || t->due_ns > now) continue;
        QMsg m = {t->hwnd, WM_TIMER, t->id, t->proc, (uint32_t)(now / 1000000ull), 0, 0, NULL};
        if (!msg_matches(&m, hwnd, lo, hi)) continue;
        if (remove) t->due_ns = now + (uint64_t)t->period_ms * 1000000ull;
        *out = m;
        pthread_mutex_unlock(&user_mu);
        return 1;
    }
    pthread_mutex_unlock(&user_mu);
    return 0;
}

/* PeekMessageA(msg, hwnd, min, max, remove) */
H(user_PeekMessageA) {
    pthread_once(&user_once, user_init);
    QMsg m;
    int r = peek(c, &m, a[1], a[2], a[3], (a[4] & PM_REMOVE) != 0);
    if (r < 0) return 0;
    if (r == 0) {
        /* The game spins on PeekMessage between frames; give the processor a rest. */
        static __thread uint64_t last_idle;
        uint64_t now = rt_mono_ns();
        if (now - last_idle < 2000000ull) {
            struct timespec ts = {0, 500000L};
            nanosleep(&ts, NULL);
        }
        last_idle = rt_mono_ns();
        return 0;
    }
    write_msg(a[0], &m);
    return 1;
}

/* GetMessageA(msg, hwnd, min, max) */
H(user_GetMessageA) {
    pthread_once(&user_once, user_init);
    RtThread *th = rt_thread_of(c);
    QMsg m;
    for (;;) {
        int r = peek(c, &m, a[1], a[2], a[3], 1);
        if (r < 0) return 0;
        if (r > 0) break;
        if (rt_video_on_video_thread()) {
            struct timespec ts = {0, 2000000L}; /* host input has no wake-up of its own */
            nanosleep(&ts, NULL);
            continue;
        }
        pthread_mutex_lock(&user_mu);
        MsgQueue *q = queue_of(th);
        if (q->count == 0 && !q->quit) {
            uint64_t due = UINT64_MAX;
            for (size_t i = 0; i < RT_COUNTOF(timers); i++)
                if (timers[i].used && timers[i].owner == th && timers[i].due_ns < due) due = timers[i].due_ns;
            if (due == UINT64_MAX) {
                pthread_cond_wait(&user_cv, &user_mu);
            } else {
                struct timespec ts = {(time_t)(due / 1000000000ull), (long)(due % 1000000000ull)};
                pthread_cond_timedwait(&user_cv, &user_mu, &ts);
            }
        }
        pthread_mutex_unlock(&user_mu);
    }
    write_msg(a[0], &m);
    return m.msg != WM_QUIT;
}

H(user_TranslateMessage) {
    uint32_t p = a[0];
    uint32_t msg = ld32(p + 4), vk = ld32(p + 8);
    if (msg != WM_KEYDOWN) return 0;
    /* Printable characters arrive from the host as text input; only the control
     * characters are derived from key presses here. */
    uint32_t ch = 0;
    if (vk == 0x0D) ch = 13;
    else if (vk == 0x08) ch = 8;
    else if (vk == 0x09) ch = 9;
    else if (vk == 0x1B) ch = 27;
    if (!ch) return 0;
    pthread_mutex_lock(&user_mu);
    Window *w = win_get(ld32(p));
    if (w) {
        QMsg m = {ld32(p), WM_CHAR, ch, ld32(p + 12), ld32(p + 16), 0, 0, NULL};
        MsgQueue *q = queue_of(w->owner);
        /* WM_CHAR goes to the head of the queue, as it follows its key press immediately. */
        queue_push(w->owner, &m);
        memmove(q->buf + 1, q->buf, (q->count - 1) * sizeof *q->buf);
        q->buf[0] = m;
    }
    pthread_mutex_unlock(&user_mu);
    (void)c;
    return 1;
}

H(user_DispatchMessageA) {
    uint32_t p = a[0];
    uint32_t hwnd = ld32(p), msg = ld32(p + 4), wp = ld32(p + 8), lp = ld32(p + 12), r = 0;
    if (msg == WM_TIMER && lp) {
        uint32_t args[4] = {hwnd, WM_TIMER, wp, now_ms()};
        rt_call_guest(c, lp, RT_STDCALL, 4, args, &r);
        return r;
    }
    if (!hwnd) return 0;
    pthread_mutex_lock(&user_mu);
    Window *w = win_get(hwnd);
    uint32_t proc = w ? w->wndproc : 0;
    pthread_mutex_unlock(&user_mu);
    if (proc) call_proc(c, proc, hwnd, msg, wp, lp, &r);
    return r;
}

H(user_PostQuitMessage) {
    pthread_once(&user_once, user_init);
    pthread_mutex_lock(&user_mu);
    MsgQueue *q = queue_of(rt_thread_of(c));
    q->quit = 1;
    q->quit_code = a[0];
    pthread_cond_broadcast(&user_cv);
    pthread_mutex_unlock(&user_mu);
    return 0;
}

/* ------------------------------------------------------- cursor and keys */
H(user_LoadCursorA) {
    UNUSED;
    if (a[0] == 0 && a[1] < 0x10000) return 0x00010000u | (a[1] & 0xFF) | 1u; /* a stock cursor */
    return 0x00010001u;
}

H(user_SetCursor) {
    UNUSED;
    return __atomic_exchange_n(&current_cursor, a[0], __ATOMIC_SEQ_CST);
}

H(user_ShowCursor) {
    UNUSED;
    pthread_mutex_lock(&user_mu);
    cursor_count += a[0] ? 1 : -1;
    int n = cursor_count;
    pthread_mutex_unlock(&user_mu);
    rt_video_show_cursor(n >= 0);
    return (uint32_t)n;
}

H(user_SetCursorPos) {
    UNUSED;
    rt_mouse_x = (int32_t)a[0];
    rt_mouse_y = (int32_t)a[1];
    rt_video_warp_mouse((int32_t)a[0], (int32_t)a[1]);
    return 1;
}

H(user_GetKeyState) {
    UNUSED;
    uint8_t s = rt_vk_state[a[0] & 0xFF];
    return (uint32_t)(int32_t)(int16_t)(((s & 0x80) ? 0xFF80 : 0) | (s & 1));
}

/* ------------------------------------------------------------ MessageBox */
H(user_MessageBoxA) {
    fflush(stdout);
    rt_log("\nrecomp: MessageBoxA from thread %x (type %#x)\n  caption: %s\n  text:    %s\n", c->thread_id, a[3],
           a[2] ? rt_gstr(a[2]) : "(default: Error)", a[1] ? rt_gstr(a[1]) : "");
    rt_video_message_box(a[2] ? rt_gstr(a[2]) : "Error", a[1] ? rt_gstr(a[1]) : "");
    switch (a[3] & 0xF) {
    case 4: return 6; /* MB_YESNO: IDYES */
    case 3: return 6; /* MB_YESNOCANCEL */
    default: return 1; /* IDOK */
    }
}

/* -------------------------------------------------------------- wsprintf
 * int wsprintfA(char *out, const char *fmt, ...): cdecl, so the variable
 * arguments are read from the guest stack. */
static uint32_t format_guest(char *out, size_t cap, const char *fmt, uint32_t argp) {
    size_t o = 0;
#define PUT(ch) do { if (o + 1 < cap) out[o] = (char)(ch); o++; } while (0)
    while (*fmt) {
        if (*fmt != '%') {
            PUT(*fmt++);
            continue;
        }
        const char *start = fmt++;
        char spec[32], buf[64];
        size_t sn = 0;
        spec[sn++] = '%';
        while (*fmt && strchr("-+ #0", *fmt) && sn < 8) spec[sn++] = *fmt++;
        while (isdigit((unsigned char)*fmt) && sn < 16) spec[sn++] = *fmt++;
        if (*fmt == '.') {
            spec[sn++] = *fmt++;
            while (isdigit((unsigned char)*fmt) && sn < 24) spec[sn++] = *fmt++;
        }
        int wide = 0;
        while (*fmt == 'l' || *fmt == 'h' || *fmt == 'w' || *fmt == 'I') {
            if (*fmt == 'l' || *fmt == 'w') wide = 1;
            fmt++;
        }
        char conv = *fmt ? *fmt++ : 0;
        const char *s = buf;
        switch (conv) {
        case 'd': case 'i': case 'u': case 'x': case 'X':
            spec[sn++] = conv;
            spec[sn] = 0;
            snprintf(buf, sizeof buf, spec, ld32(argp));
            argp += 4;
            break;
        case 'c': case 'C':
            buf[0] = (char)ld32(argp);
            buf[1] = 0;
            argp += 4;
            break;
        case 's': case 'S': {
            uint32_t p = ld32(argp);
            argp += 4;
            int prec = -1, width = 0, left = 0;
            for (size_t k = 1; k < sn; k++) {
                if (spec[k] == '-') left = 1;
                else if (spec[k] == '.') { prec = atoi(spec + k + 1); break; }
                else if (isdigit((unsigned char)spec[k]) && spec[k] != '0' && !width) { width = atoi(spec + k); }
            }
            char tmp[1024];
            size_t n = 0;
            if (!p) {
                n = (size_t)snprintf(tmp, sizeof tmp, "(null)");
            } else if (wide || conv == 'S') {
                while (n + 1 < sizeof tmp && ld16(p + 2 * (uint32_t)n)) {
                    uint16_t wc = ld16(p + 2 * (uint32_t)n);
                    tmp[n++] = wc < 0x100 ? (char)wc : '?';
                }
            } else {
                while (n + 1 < sizeof tmp && ld8(p + (uint32_t)n)) {
                    tmp[n] = (char)ld8(p + (uint32_t)n);
                    n++;
                }
            }
            if (prec >= 0 && n > (size_t)prec) n = (size_t)prec;
            if (!left) for (size_t k = n; k < (size_t)width; k++) PUT(' ');
            for (size_t k = 0; k < n; k++) PUT(tmp[k]);
            if (left) for (size_t k = n; k < (size_t)width; k++) PUT(' ');
            s = "";
            break;
        }
        case '%':
            buf[0] = '%';
            buf[1] = 0;
            break;
        default: /* unknown conversion: copied through, as wsprintf does */
            for (const char *q = start; q < fmt; q++) PUT(*q);
            s = "";
            break;
        }
        while (*s) PUT(*s++);
    }
#undef PUT
    if (cap) out[o < cap ? o : cap - 1] = 0;
    return (uint32_t)o;
}

H(user_wsprintfA) {
    char out[1025]; /* wsprintf never writes more than 1024 characters */
    uint32_t n = format_guest(out, sizeof out, rt_gstr(a[1]), ESP + 12);
    if (n > 1024) n = 1024;
    memcpy(G(a[0]), out, n + 1);
    return n;
}

/* ------------------------------------------------------------ gdi32, imm32 */
H(user_GetDC) { UNUSED; return HDC_FAKE; }
H(user_ReleaseDC) { UNUSED; return 1; }

H(gdi_GetDeviceCaps) {
    UNUSED;
    switch (a[1]) {
    case 8: return SCREEN_W;  /* HORZRES */
    case 10: return SCREEN_H; /* VERTRES */
    case 12: return 16;       /* BITSPIXEL */
    case 14: return 1;        /* PLANES */
    case 88: case 90: return 96; /* LOGPIXELSX/Y */
    case 116: return 60;      /* VREFRESH */
    case 117: return SCREEN_H; /* DESKTOPVERTRES */
    case 118: return SCREEN_W; /* DESKTOPHORZRES */
    default: return 0;
    }
}

H(imm_ImmDisableIME) { UNUSED; return 1; }
H(imm_ImmGetContext) { UNUSED; return 0; }
H(imm_ImmGetOpenStatus) { UNUSED; return 0; }
H(imm_ImmGetCompositionStringA) { UNUSED; return 0; }
H(imm_ImmSetCompositionWindow) { UNUSED; return 0; }

static const ImportDef defs[] = {
    {"user32.dll", "RegisterClassA", user_RegisterClassA, 1, 0},
    {"user32.dll", "CreateWindowExA", user_CreateWindowExA, 12, 0},
    {"user32.dll", "DestroyWindow", user_DestroyWindow, 1, 0},
    {"user32.dll", "DefWindowProcA", user_DefWindowProcA, 4, 0},
    {"user32.dll", "CallWindowProcA", user_CallWindowProcA, 5, 0},
    {"user32.dll", "SendMessageA", user_SendMessageA, 4, 0},
    {"user32.dll", "GetWindowLongA", user_GetWindowLongA, 2, 0},
    {"user32.dll", "SetWindowLongA", user_SetWindowLongA, 3, 0},
    {"user32.dll", "GetWindowTextA", user_GetWindowTextA, 3, 0},
    {"user32.dll", "SetWindowTextA", user_SetWindowTextA, 2, 0},
    {"user32.dll", "SetFocus", user_SetFocus, 1, 0},
    {"user32.dll", "SetForegroundWindow", user_SetForegroundWindow, 1, 0},
    {"user32.dll", "ShowWindow", user_ShowWindow, 2, 0},
    {"user32.dll", "UpdateWindow", user_UpdateWindow, 1, 0},
    {"user32.dll", "GetClientRect", user_GetClientRect, 2, 0},
    {"user32.dll", "ClientToScreen", user_ClientToScreen, 2, 0},
    {"user32.dll", "SetTimer", user_SetTimer, 4, 0},
    {"user32.dll", "KillTimer", user_KillTimer, 2, 0},
    {"user32.dll", "PeekMessageA", user_PeekMessageA, 5, 0},
    {"user32.dll", "GetMessageA", user_GetMessageA, 4, 0},
    {"user32.dll", "TranslateMessage", user_TranslateMessage, 1, 0},
    {"user32.dll", "DispatchMessageA", user_DispatchMessageA, 1, 0},
    {"user32.dll", "PostQuitMessage", user_PostQuitMessage, 1, 0},
    {"user32.dll", "LoadCursorA", user_LoadCursorA, 2, 0},
    {"user32.dll", "SetCursor", user_SetCursor, 1, 0},
    {"user32.dll", "ShowCursor", user_ShowCursor, 1, 0},
    {"user32.dll", "SetCursorPos", user_SetCursorPos, 2, 0},
    {"user32.dll", "GetKeyState", user_GetKeyState, 1, 0},
    {"user32.dll", "MessageBoxA", user_MessageBoxA, 4, 0},
    {"user32.dll", "wsprintfA", user_wsprintfA, 2, 1},
    {"user32.dll", "GetDC", user_GetDC, 1, 0},
    {"user32.dll", "ReleaseDC", user_ReleaseDC, 2, 0},
    {"gdi32.dll", "GetDeviceCaps", gdi_GetDeviceCaps, 2, 0},
    {"imm32.dll", "ImmDisableIME", imm_ImmDisableIME, 1, 0},
    {"imm32.dll", "ImmGetContext", imm_ImmGetContext, 1, 0},
    {"imm32.dll", "ImmGetOpenStatus", imm_ImmGetOpenStatus, 1, 0},
    {"imm32.dll", "ImmGetCompositionStringA", imm_ImmGetCompositionStringA, 4, 0},
    {"imm32.dll", "ImmSetCompositionWindow", imm_ImmSetCompositionWindow, 2, 0},
};
RT_EXPORT_IMPORTS(rt_imports_user, defs);

uint32_t rt_main_window(void) { return main_hwnd; }
