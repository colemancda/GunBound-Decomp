/* ws2_32 on BSD sockets.
 *
 * Guest SOCKET values index a table of host descriptors. One host thread polls
 * the sockets that have WSAAsyncSelect or WSAEventSelect notifications and turns
 * readiness into window messages or signalled events, following Winsock's
 * rules: each notification is reported once and re-armed by the call that
 * consumes it (recv for FD_READ, a send that would block for FD_WRITE, ...).
 */
#define _GNU_SOURCE
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "rt.h"

#if defined(__APPLE__)
/* Darwin: no POLLRDHUP (a closed peer is then seen at the next recv, which
 * re-arms FD_READ), no SOCK_CLOEXEC, no accept4, pipe2 only recently. Nothing is ever exec'd. */
#define POLLRDHUP 0
#define SOCK_CLOEXEC 0
#define accept4(fd, sa, len, flags) accept(fd, sa, len)
#define pipe2 rt_pipe2 /* only in recent SDKs, and not on older systems */
static int rt_pipe2(int fd[2], int flags) {
    if (pipe(fd) != 0) return -1;
    for (int i = 0; i < 2; i++) {
        if (flags & O_NONBLOCK) fcntl(fd[i], F_SETFL, fcntl(fd[i], F_GETFL) | O_NONBLOCK);
        if (flags & O_CLOEXEC) fcntl(fd[i], F_SETFD, FD_CLOEXEC);
    }
    return 0;
}
#endif
#include "user.h"

#define FD_READ 0x01u
#define FD_WRITE 0x02u
#define FD_OOB 0x04u
#define FD_ACCEPT 0x08u
#define FD_CONNECT 0x10u
#define FD_CLOSE 0x20u

#define SOCKET_ERROR 0xFFFFFFFFu
#define INVALID_SOCKET 0xFFFFFFFFu
#define WSAEINTR 10004u
#define WSAEBADF 10009u
#define WSAEACCES 10013u
#define WSAEFAULT 10014u
#define WSAEINVAL 10022u
#define WSAEMFILE 10024u
#define WSAEWOULDBLOCK 10035u
#define WSAEINPROGRESS 10036u
#define WSAEALREADY 10037u
#define WSAENOTSOCK 10038u
#define WSAEMSGSIZE 10040u
#define WSAENOPROTOOPT 10042u
#define WSAEAFNOSUPPORT 10047u
#define WSAEADDRINUSE 10048u
#define WSAEADDRNOTAVAIL 10049u
#define WSAENETDOWN 10050u
#define WSAENETUNREACH 10051u
#define WSAECONNABORTED 10053u
#define WSAECONNRESET 10054u
#define WSAENOBUFS 10055u
#define WSAEISCONN 10056u
#define WSAENOTCONN 10057u
#define WSAESHUTDOWN 10058u
#define WSAETIMEDOUT 10060u
#define WSAECONNREFUSED 10061u
#define WSAEHOSTUNREACH 10065u
#define WSAHOST_NOT_FOUND 11001u

#define MAX_SOCKETS 256
#define SOCK_BASE 0x200u

typedef struct Sock {
    int fd;            /* -1: free slot */
    int is_dgram, connecting, connected, nonblocking, bound;
    uint16_t bound_port;      /* network byte order; 0 when not bound by the guest */
    uint32_t hwnd, msg;       /* WSAAsyncSelect target */
    RtWaitable *event;        /* WSAEventSelect target */
    uint32_t interest;        /* FD_* mask requested */
    uint32_t armed;           /* FD_* notifications that may be reported */
    uint32_t pending;         /* WSAEventSelect: reported, not yet enumerated */
    uint32_t errors[6];       /* per event bit, for WSAEnumNetworkEvents */
    int closed_reported;
} Sock;

static Sock socks[MAX_SOCKETS];
static pthread_mutex_t sock_mu = PTHREAD_MUTEX_INITIALIZER;
static pthread_once_t sock_once = PTHREAD_ONCE_INIT;
static int wake_pipe[2] = {-1, -1};
static int poller_started;

static void sock_init(void) {
    for (int i = 0; i < MAX_SOCKETS; i++) socks[i].fd = -1;
    if (pipe2(wake_pipe, O_NONBLOCK | O_CLOEXEC) != 0) perror("recomp: pipe");
}

static uint32_t wsa_error(int e) {
    switch (e) {
    case 0: return 0;
    case EINTR: return WSAEINTR;
    case EBADF: return WSAENOTSOCK;
    case EACCES: return WSAEACCES;
    case EFAULT: return WSAEFAULT;
    case EINVAL: return WSAEINVAL;
    case EMFILE: return WSAEMFILE;
    case EAGAIN: return WSAEWOULDBLOCK;
    case EINPROGRESS: return WSAEWOULDBLOCK; /* what a non-blocking connect reports on Windows */
    case EALREADY: return WSAEALREADY;
    case ENOTSOCK: return WSAENOTSOCK;
    case EMSGSIZE: return WSAEMSGSIZE;
    case ENOPROTOOPT: return WSAENOPROTOOPT;
    case EAFNOSUPPORT: return WSAEAFNOSUPPORT;
    case EADDRINUSE: return WSAEADDRINUSE;
    case EADDRNOTAVAIL: return WSAEADDRNOTAVAIL;
    case ENETDOWN: return WSAENETDOWN;
    case ENETUNREACH: return WSAENETUNREACH;
    case ECONNABORTED: return WSAECONNABORTED;
    case ECONNRESET: case EPIPE: return WSAECONNRESET;
    case ENOBUFS: case ENOMEM: return WSAENOBUFS;
    case EISCONN: return WSAEISCONN;
    case ENOTCONN: return WSAENOTCONN;
    case ESHUTDOWN: return WSAESHUTDOWN;
    case ETIMEDOUT: return WSAETIMEDOUT;
    case ECONNREFUSED: return WSAECONNREFUSED;
    case EHOSTUNREACH: return WSAEHOSTUNREACH;
    default: return WSAEINVAL;
    }
}

static uint32_t fail(CPU *c, uint32_t err) {
    rt_set_last_error(c, err);
    return SOCKET_ERROR;
}

/* Under sock_mu. */
static Sock *sock_get(uint32_t s) {
    uint32_t i = s - SOCK_BASE;
    if (s < SOCK_BASE || i >= MAX_SOCKETS || socks[i].fd < 0) return NULL;
    return &socks[i];
}

static void wake_poller(void) {
    char b = 0;
    if (wake_pipe[1] >= 0 && write(wake_pipe[1], &b, 1) < 0) { /* pipe full: the poller is waking anyway */ }
}

static int event_index(uint32_t bit) { return __builtin_ctz(bit); }

/* Under sock_mu: report one event for socket index i. */
static void report(int i, uint32_t bit, uint32_t err) {
    Sock *s = &socks[i];
    s->armed &= ~bit;
    if (!(s->interest & bit)) return;
    if (s->event) {
        s->pending |= bit;
        s->errors[event_index(bit)] = err;
        rt_waitable_signal(s->event);
    } else if (s->hwnd) {
        rt_post_message(s->hwnd, s->msg, SOCK_BASE + (uint32_t)i, bit | (err << 16));
    }
}

static void *poller_main(void *arg) {
    (void)arg;
    struct pollfd pfd[MAX_SOCKETS + 1];
    int idx[MAX_SOCKETS + 1];
    for (;;) {
        int n = 0;
        pfd[n].fd = wake_pipe[0];
        pfd[n].events = POLLIN;
        idx[n++] = -1;
        pthread_mutex_lock(&sock_mu);
        for (int i = 0; i < MAX_SOCKETS; i++) {
            Sock *s = &socks[i];
            if (s->fd < 0 || !s->interest || (!s->hwnd && !s->event)) continue;
            short ev = 0;
            /* While FD_READ is waiting for the guest to call recv, unread data must not
             * keep waking the poller: watch only for the peer closing. */
            if (s->armed & (FD_READ | FD_ACCEPT)) ev |= POLLIN;
            else if (!s->closed_reported && (s->interest & FD_CLOSE) && s->connected) ev |= POLLRDHUP;
            if (s->connecting || (s->armed & FD_WRITE)) ev |= POLLOUT;
            if (!ev) continue;
            pfd[n].fd = s->fd;
            pfd[n].events = ev;
            pfd[n].revents = 0;
            idx[n++] = i;
        }
        pthread_mutex_unlock(&sock_mu);
        if (poll(pfd, (nfds_t)n, 250) <= 0) continue;
        if (pfd[0].revents & POLLIN) {
            char buf[64];
            while (read(wake_pipe[0], buf, sizeof buf) > 0) {}
        }
        pthread_mutex_lock(&sock_mu);
        for (int k = 1; k < n; k++) {
            Sock *s = &socks[idx[k]];
            if (!pfd[k].revents || s->fd != pfd[k].fd) continue;
            if (s->connecting && (pfd[k].revents & (POLLOUT | POLLERR | POLLHUP))) {
                int soerr = 0;
                socklen_t len = sizeof soerr;
                getsockopt(s->fd, SOL_SOCKET, SO_ERROR, &soerr, &len);
                s->connecting = 0;
                s->connected = soerr == 0;
                s->armed |= FD_CONNECT;
                report(idx[k], FD_CONNECT, wsa_error(soerr));
                if (soerr == 0) report(idx[k], FD_WRITE, 0);
                continue;
            }
            if (pfd[k].revents & POLLIN) {
                char probe;
                ssize_t r = (s->is_dgram || !s->connected) ? 1 : recv(s->fd, &probe, 1, MSG_PEEK | MSG_DONTWAIT);
                if (r > 0) {
                    if (s->armed & FD_READ) report(idx[k], FD_READ, 0);
                    else if (s->armed & FD_ACCEPT) report(idx[k], FD_ACCEPT, 0);
                } else if (r == 0 || (errno != EAGAIN && errno != EINTR)) {
                    if (!s->closed_reported) {
                        s->closed_reported = 1;
                        s->armed = (s->armed & ~FD_READ) | FD_CLOSE;
                        report(idx[k], FD_CLOSE, r == 0 ? 0 : wsa_error(errno));
                    }
                }
            } else if ((pfd[k].revents & (POLLERR | POLLHUP | POLLRDHUP)) && !s->closed_reported && s->connected) {
                s->closed_reported = 1;
                s->armed = (s->armed & ~FD_READ) | FD_CLOSE;
                report(idx[k], FD_CLOSE, (pfd[k].revents & POLLERR) ? WSAECONNRESET : 0);
            }
            if ((pfd[k].revents & POLLOUT) && (s->armed & FD_WRITE)) report(idx[k], FD_WRITE, 0);
        }
        pthread_mutex_unlock(&sock_mu);
    }
    return NULL;
}

/* Under sock_mu. */
static void start_poller(void) {
    if (poller_started) return;
    poller_started = 1;
    pthread_t pt;
    pthread_attr_t at;
    pthread_attr_init(&at);
    pthread_attr_setdetachstate(&at, PTHREAD_CREATE_DETACHED);
    rt_affinity_host(1);
    pthread_create(&pt, &at, poller_main, NULL);
    rt_affinity_host(0);
    pthread_attr_destroy(&at);
}

/* Under sock_mu: Windows makes a socket non-blocking when notifications are requested. */
static void set_nonblocking(Sock *s, int on) {
    int fl = fcntl(s->fd, F_GETFL, 0);
    fcntl(s->fd, F_SETFL, on ? fl | O_NONBLOCK : fl & ~O_NONBLOCK);
    s->nonblocking = on;
}

/* The address this machine is known by: --local-address, or else the address of
 * the interface the default route uses (no packet is sent to find it). 0 if
 * there is neither. Network byte order. */
static uint32_t local_address(int explicit_only) {
    static uint32_t cached;
    static int have;
    if (g_opt.local_address[0]) {
        struct in_addr in;
        if (inet_aton(g_opt.local_address, &in)) return in.s_addr;
    }
    if (explicit_only) return 0;
    if (!have) {
        have = 1;
        int fd = socket(AF_INET, SOCK_DGRAM | SOCK_CLOEXEC, 0);
        if (fd >= 0) {
            struct sockaddr_in sa = {.sin_family = AF_INET, .sin_port = htons(9)};
            socklen_t len = sizeof sa;
            inet_aton("192.0.2.1", &sa.sin_addr);
            if (connect(fd, (struct sockaddr *)&sa, sizeof sa) == 0 &&
                getsockname(fd, (struct sockaddr *)&sa, &len) == 0)
                cached = sa.sin_addr.s_addr;
            close(fd);
        }
    }
    return cached;
}

/* With --local-address, a socket that the guest has not bound is bound to that
 * address before its first use, so that its traffic leaves from there. */
static void bind_local(uint32_t h, int fd) {
    uint32_t ad = local_address(1);
    if (!ad) return;
    pthread_mutex_lock(&sock_mu);
    Sock *s = sock_get(h);
    int need = s && !s->bound;
    if (s) s->bound = 1;
    pthread_mutex_unlock(&sock_mu);
    if (!need) return;
    struct sockaddr_in sa = {.sin_family = AF_INET};
    sa.sin_addr.s_addr = ad;
    if (bind(fd, (struct sockaddr *)&sa, sizeof sa) != 0)
        rt_log("recomp: cannot bind a socket to %s: %s\n", g_opt.local_address, strerror(errno));
}

/* --trace-net: one line per transfer, with the guest frame number as a clock. */
static void trace_io(const char *what, uint32_t h, const struct sockaddr_in *peer, uint32_t buf, long n) {
    if (!g_opt.trace_net || n < 0) return;
    char hex[3 * 96 + 8], where[40] = "";
    long show = n > 96 ? 96 : n;
    for (long i = 0; i < show; i++) snprintf(hex + 3 * i, 4, " %02x", ld8(buf + (uint32_t)i));
    if (show == 0) hex[0] = 0;
    if (peer) snprintf(where, sizeof where, " %s:%u", inet_ntoa(peer->sin_addr), ntohs(peer->sin_port));
    rt_log("[net] %s %x%s %ld bytes:%s%s\n", what, h, where, n, hex, n > show ? " ..." : "");
}

/* ------------------------------------------------------------- startup */
H(ws_WSAStartup) {
    UNUSED;
    pthread_once(&sock_once, sock_init);
    uint32_t p = a[1];
    memset(G(p), 0, 400);
    uint16_t want = (uint16_t)a[0];
    uint16_t ver = (want & 0xFF) >= 2 ? 0x0202 : want; /* the version asked for, up to 2.2 */
    st16(p, ver);
    st16(p + 2, 0x0202);
    strcpy((char *)G(p + 4), "WinSock 2.0");
    strcpy((char *)G(p + 4 + 257), "Running");
    st16(p + 4 + 257 + 129, 32767);     /* iMaxSockets */
    st16(p + 4 + 257 + 129 + 2, 65467); /* iMaxUdpDg */
    return 0;
}

H(ws_WSACleanup) { UNUSED; return 0; }
H(ws_WSAGetLastError) { UNUSED; return ld32(c->fs_base + TEB_LAST_ERROR); }
H(ws_htonl) { UNUSED; return __builtin_bswap32(a[0]); }
H(ws_htons) { UNUSED; return __builtin_bswap16((uint16_t)a[0]); }

H(ws_inet_addr) {
    UNUSED;
    struct in_addr in;
    if (!a[0] || !inet_aton(rt_gstr(a[0]), &in)) return 0xFFFFFFFFu;
    return in.s_addr;
}

/* ------------------------------------------------------------- sockets */
H(ws_socket) {
    pthread_once(&sock_once, sock_init);
    if (a[0] != 2) return fail(c, WSAEAFNOSUPPORT);
    int type = a[1] == 1 ? SOCK_STREAM : a[1] == 2 ? SOCK_DGRAM : -1;
    if (type < 0) return fail(c, WSAEINVAL);
    int fd = socket(AF_INET, type | SOCK_CLOEXEC, 0);
    if (fd < 0) return fail(c, wsa_error(errno));
    pthread_mutex_lock(&sock_mu);
    int i;
    for (i = 0; i < MAX_SOCKETS; i++)
        if (socks[i].fd < 0) break;
    if (i == MAX_SOCKETS) {
        pthread_mutex_unlock(&sock_mu);
        close(fd);
        return fail(c, WSAEMFILE);
    }
    memset(&socks[i], 0, sizeof socks[i]);
    socks[i].fd = fd;
    socks[i].is_dgram = type == SOCK_DGRAM;
    pthread_mutex_unlock(&sock_mu);
    if (g_opt.verbose) rt_log("[net] socket %x created (%s)\n", SOCK_BASE + (uint32_t)i, type == SOCK_DGRAM ? "udp" : "tcp");
    return SOCK_BASE + (uint32_t)i;
}

H(ws_closesocket) {
    pthread_mutex_lock(&sock_mu);
    Sock *s = sock_get(a[0]);
    if (!s) {
        pthread_mutex_unlock(&sock_mu);
        return fail(c, WSAENOTSOCK);
    }
    int fd = s->fd;
    if (s->event) rt_waitable_unref(s->event);
    memset(s, 0, sizeof *s);
    s->fd = -1;
    pthread_mutex_unlock(&sock_mu);
    close(fd);
    wake_poller();
    return 0;
}

/* Copies the host fd and flags of a guest socket; returns -1 if it is not one. */
static int sock_fd(uint32_t h, Sock *copy) {
    pthread_mutex_lock(&sock_mu);
    Sock *s = sock_get(h);
    int fd = s ? s->fd : -1;
    if (s && copy) *copy = *s;
    pthread_mutex_unlock(&sock_mu);
    return fd;
}

static void rearm(uint32_t h, uint32_t bits) {
    pthread_mutex_lock(&sock_mu);
    Sock *s = sock_get(h);
    if (s && (s->interest & bits) && (s->armed & bits) != (s->interest & bits)) {
        s->armed |= s->interest & bits;
        pthread_mutex_unlock(&sock_mu);
        wake_poller();
        return;
    }
    pthread_mutex_unlock(&sock_mu);
}

H(ws_connect) {
    Sock info;
    int fd = sock_fd(a[0], &info);
    if (fd < 0) return fail(c, WSAENOTSOCK);
    if (a[2] < 16) return fail(c, WSAEFAULT);
    struct sockaddr_in sa;
    memcpy(&sa, G(a[1]), sizeof sa);
    sa.sin_family = AF_INET;
    if (g_opt.verbose || g_trace_imports)
        rt_log("[net] socket %x connect to %s:%u\n", a[0], inet_ntoa(sa.sin_addr), ntohs(sa.sin_port));
    bind_local(a[0], fd);
    int r = connect(fd, (struct sockaddr *)&sa, sizeof sa);
    int e = errno;
    pthread_mutex_lock(&sock_mu);
    Sock *s = sock_get(a[0]);
    if (s) {
        if (r == 0) {
            s->connected = 1;
            if (!s->is_dgram) {
                s->armed |= FD_CONNECT;
                report((int)(a[0] - SOCK_BASE), FD_CONNECT, 0);
                s->armed |= FD_WRITE;
            }
        } else if (e == EINPROGRESS) {
            s->connecting = 1;
        }
    }
    pthread_mutex_unlock(&sock_mu);
    wake_poller();
    if (r != 0) return fail(c, wsa_error(e));
    return 0;
}

H(ws_bind) {
    int fd = sock_fd(a[0], NULL);
    if (fd < 0) return fail(c, WSAENOTSOCK);
    if (a[2] < 16) return fail(c, WSAEFAULT);
    struct sockaddr_in sa;
    memcpy(&sa, G(a[1]), sizeof sa);
    sa.sin_family = AF_INET;
    if (sa.sin_addr.s_addr == 0) sa.sin_addr.s_addr = local_address(1);
    int r = bind(fd, (struct sockaddr *)&sa, sizeof sa);
    int e = errno;
    if (g_opt.verbose || g_trace_imports)
        rt_log("[net] socket %x bind to %s:%u%s%s\n", a[0], inet_ntoa(sa.sin_addr), ntohs(sa.sin_port),
               r ? " failed: " : "", r ? strerror(e) : "");
    if (r != 0) return fail(c, wsa_error(e));
    pthread_mutex_lock(&sock_mu);
    Sock *s = sock_get(a[0]);
    if (s) {
        s->bound = 1;
        s->bound_port = sa.sin_port;
    }
    pthread_mutex_unlock(&sock_mu);
    return 0;
}

H(ws_accept) {
    int fd = sock_fd(a[0], NULL);
    if (fd < 0) return fail(c, WSAENOTSOCK);
    struct sockaddr_in sa;
    socklen_t len = sizeof sa;
    int nfd = accept4(fd, (struct sockaddr *)&sa, &len, SOCK_CLOEXEC);
    rearm(a[0], FD_ACCEPT);
    if (nfd < 0) return fail(c, wsa_error(errno));
    pthread_mutex_lock(&sock_mu);
    int i;
    for (i = 0; i < MAX_SOCKETS; i++)
        if (socks[i].fd < 0) break;
    if (i == MAX_SOCKETS) {
        pthread_mutex_unlock(&sock_mu);
        close(nfd);
        return fail(c, WSAEMFILE);
    }
    memset(&socks[i], 0, sizeof socks[i]);
    socks[i].fd = nfd;
    socks[i].connected = 1;
    pthread_mutex_unlock(&sock_mu);
    if (a[1] && a[2] && ld32(a[2]) >= 16) {
        memcpy(G(a[1]), &sa, 16);
        st16(a[1], 2);
        st32(a[2], 16);
    }
    return SOCK_BASE + (uint32_t)i;
}

H(ws_send) {
    int fd = sock_fd(a[0], NULL);
    if (fd < 0) return fail(c, WSAENOTSOCK);
    ssize_t r = send(fd, G(a[1]), a[2], MSG_NOSIGNAL);
    if (r < 0) {
        int e = errno;
        if (e == EAGAIN) rearm(a[0], FD_WRITE);
        return fail(c, wsa_error(e));
    }
    trace_io("send", a[0], NULL, a[1], r);
    return (uint32_t)r;
}

H(ws_recv) {
    int fd = sock_fd(a[0], NULL);
    if (fd < 0) return fail(c, WSAENOTSOCK);
    int flags = (a[3] & 2) ? MSG_PEEK : 0;
    ssize_t r = recv(fd, G(a[1]), a[2], flags);
    int e = errno;
    rearm(a[0], FD_READ);
    if (r < 0) return fail(c, wsa_error(e));
    trace_io("recv", a[0], NULL, a[1], r);
    return (uint32_t)r;
}

H(ws_sendto) {
    Sock info;
    int fd = sock_fd(a[0], &info);
    if (fd < 0) return fail(c, WSAENOTSOCK);
    struct sockaddr_in sa;
    ssize_t r;
    bind_local(a[0], fd);
    if (a[4] && a[5] >= 16) {
        memcpy(&sa, G(a[4]), sizeof sa);
        sa.sin_family = AF_INET;
        /* The game delivers its own events to itself by sending them to
         * 127.0.0.1 at the port its socket is bound to. A socket bound to
         * --local-address is not reachable there. */
        if (sa.sin_addr.s_addr == htonl(INADDR_LOOPBACK) && info.bound_port && sa.sin_port == info.bound_port &&
            local_address(1))
            sa.sin_addr.s_addr = local_address(1);
        r = sendto(fd, G(a[1]), a[2], MSG_NOSIGNAL, (struct sockaddr *)&sa, sizeof sa);
    } else {
        r = send(fd, G(a[1]), a[2], MSG_NOSIGNAL);
    }
    if (r < 0) {
        int e = errno;
        if (g_opt.trace_net) rt_log("[net] sendto %x failed: %s\n", a[0], strerror(e));
        if (e == EAGAIN) rearm(a[0], FD_WRITE);
        return fail(c, wsa_error(e));
    }
    trace_io("sendto", a[0], a[4] && a[5] >= 16 ? &sa : NULL, a[1], r);
    return (uint32_t)r;
}

H(ws_recvfrom) {
    int fd = sock_fd(a[0], NULL);
    if (fd < 0) return fail(c, WSAENOTSOCK);
    struct sockaddr_in sa;
    socklen_t len = sizeof sa;
    memset(&sa, 0, sizeof sa);
    ssize_t r = recvfrom(fd, G(a[1]), a[2], (a[3] & 2) ? MSG_PEEK : 0, (struct sockaddr *)&sa, &len);
    int e = errno;
    rearm(a[0], FD_READ);
    if (r < 0) return fail(c, wsa_error(e));
    trace_io("recvfrom", a[0], &sa, a[1], r);
    if (a[4] && a[5] && ld32(a[5]) >= 16) {
        memcpy(G(a[4]), &sa, 16);
        st16(a[4], 2);
        st32(a[5], 16);
    }
    return (uint32_t)r;
}

H(ws_shutdown) {
    int fd = sock_fd(a[0], NULL);
    if (fd < 0) return fail(c, WSAENOTSOCK);
    if (shutdown(fd, a[1] == 0 ? SHUT_RD : a[1] == 1 ? SHUT_WR : SHUT_RDWR) != 0) return fail(c, wsa_error(errno));
    return 0;
}

/* setsockopt(s, level, name, value, length) */
H(ws_setsockopt) {
    int fd = sock_fd(a[0], NULL);
    if (fd < 0) return fail(c, WSAENOTSOCK);
    int level, name;
    int ival = a[3] && a[4] >= 4 ? (int)ld32(a[3]) : a[3] && a[4] >= 1 ? ld8(a[3]) : 0;
    if (a[1] == 0xFFFF) {
        level = SOL_SOCKET;
        switch (a[2]) {
        case 0x0004: name = SO_REUSEADDR; break;
        case 0x0008: name = SO_KEEPALIVE; break;
        case 0x0020: name = SO_BROADCAST; break;
        case 0x1001: name = SO_SNDBUF; break;
        case 0x1002: name = SO_RCVBUF; break;
        case 0x0080: { /* SO_LINGER: {u_short onoff, linger} */
            struct linger lg = {ld16(a[3]), ld16(a[3] + 2)};
            if (setsockopt(fd, SOL_SOCKET, SO_LINGER, &lg, sizeof lg) != 0) return fail(c, wsa_error(errno));
            return 0;
        }
        case 0x1005: case 0x1006: { /* SO_SNDTIMEO / SO_RCVTIMEO: milliseconds */
            struct timeval tv = {ival / 1000, (ival % 1000) * 1000};
            if (setsockopt(fd, SOL_SOCKET, a[2] == 0x1005 ? SO_SNDTIMEO : SO_RCVTIMEO, &tv, sizeof tv) != 0)
                return fail(c, wsa_error(errno));
            return 0;
        }
        default:
            rt_log("recomp: setsockopt(SOL_SOCKET, %#x) is not mapped; ignored\n", a[2]);
            return 0;
        }
    } else if (a[1] == 6 && a[2] == 1) {
        level = IPPROTO_TCP;
        name = TCP_NODELAY;
    } else {
        rt_log("recomp: setsockopt(level %u, option %#x) is not mapped; ignored\n", a[1], a[2]);
        return 0;
    }
    if (setsockopt(fd, level, name, &ival, sizeof ival) != 0) return fail(c, wsa_error(errno));
    return 0;
}

H(ws_ioctlsocket) {
    if (a[1] == 0x8004667Eu) { /* FIONBIO */
        pthread_mutex_lock(&sock_mu);
        Sock *s = sock_get(a[0]);
        if (s) set_nonblocking(s, ld32(a[2]) != 0);
        pthread_mutex_unlock(&sock_mu);
        return s ? 0 : fail(c, WSAENOTSOCK);
    }
    int fd = sock_fd(a[0], NULL);
    if (fd < 0) return fail(c, WSAENOTSOCK);
    if (a[1] == 0x4004667Fu) { /* FIONREAD */
        int n = 0;
        if (ioctl(fd, FIONREAD, &n) != 0) return fail(c, wsa_error(errno));
        st32(a[2], (uint32_t)n);
        return 0;
    }
    return fail(c, WSAEINVAL);
}

static uint32_t sock_name(CPU *c, const uint32_t *a, int peer) {
    int fd = sock_fd(a[0], NULL);
    if (fd < 0) return fail(c, WSAENOTSOCK);
    struct sockaddr_in sa;
    socklen_t len = sizeof sa;
    memset(&sa, 0, sizeof sa);
    int r = peer ? getpeername(fd, (struct sockaddr *)&sa, &len) : getsockname(fd, (struct sockaddr *)&sa, &len);
    if (r != 0) return fail(c, wsa_error(errno));
    if (!a[1] || !a[2] || ld32(a[2]) < 16) return fail(c, WSAEFAULT);
    memcpy(G(a[1]), &sa, 16);
    st16(a[1], 2);
    st32(a[2], 16);
    return 0;
}

H(ws_getpeername) { return sock_name(c, a, 1); }
H(ws_getsockname) { return sock_name(c, a, 0); }

/* ------------------------------------------------------- name resolution */
H(ws_gethostname) {
    UNUSED;
    char name[256];
    if (gethostname(name, sizeof name) != 0) snprintf(name, sizeof name, "localhost");
    name[sizeof name - 1] = 0;
    size_t n = strlen(name);
    if (n + 1 > a[1]) return fail(c, WSAEFAULT);
    memcpy(G(a[0]), name, n + 1);
    return 0;
}

/* The hostent lives in guest memory owned by the calling thread, as on Windows. */
H(ws_gethostbyname) {
    static __thread uint32_t buf;
    const char *name = rt_gstr(a[0]);
    char self[256] = "";
    gethostname(self, sizeof self - 1);
    if (!*name) name = self; /* Windows: the empty name is this machine */
    struct addrinfo hints, *res = NULL;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(name, NULL, &hints, &res) != 0 || !res) {
        if (g_opt.verbose) rt_log("[net] gethostbyname(\"%s\") failed\n", name);
        rt_set_last_error(c, WSAHOST_NOT_FOUND);
        return 0;
    }
    uint32_t addrs[8];
    unsigned n = 0;
    for (struct addrinfo *p = res; p && n < 8; p = p->ai_next) {
        uint32_t ad = ((struct sockaddr_in *)p->ai_addr)->sin_addr.s_addr;
        unsigned k;
        for (k = 0; k < n; k++)
            if (addrs[k] == ad) break;
        if (k == n) addrs[n++] = ad;
    }
    freeaddrinfo(res);
    /* The machine's own name: Windows answers with the addresses of its network
     * interfaces, and the game passes the first one on as where its peers can
     * reach it. Many Linux systems resolve the host name to a loopback alias. */
    if (!strcasecmp(name, self)) {
        uint32_t ad = local_address(0);
        if (ad && (g_opt.local_address[0] || (ntohl(addrs[0]) >> 24) == 127)) {
            addrs[0] = ad;
            n = 1;
        }
    }
    if (!buf) buf = rt_heap_alloc(512, 1);
    /* layout: hostent (16) | alias list (4) | address pointers (36) | addresses (32) | name */
    uint32_t aliases = buf + 16, list = buf + 20, data = buf + 56, nm = buf + 88;
    size_t len = strlen(name);
    if (len > 400) len = 400;
    memcpy(G(nm), name, len);
    st8(nm + (uint32_t)len, 0);
    st32(aliases, 0);
    for (unsigned k = 0; k < n; k++) {
        memcpy(G(data + 4 * k), &addrs[k], 4);
        st32(list + 4 * k, data + 4 * k);
    }
    st32(list + 4 * n, 0);
    st32(buf, nm);
    st32(buf + 4, aliases);
    st16(buf + 8, 2);
    st16(buf + 10, 4);
    st32(buf + 12, list);
    if (g_opt.verbose) {
        struct in_addr in = {addrs[0]};
        rt_log("[net] gethostbyname(\"%s\") -> %s (%u addresses)\n", name, inet_ntoa(in), n);
    }
    return buf;
}

/* ---------------------------------------------------------- notifications */
static uint32_t select_events(CPU *c, uint32_t h, uint32_t hwnd, uint32_t msg, RtWaitable *ev, uint32_t mask) {
    pthread_once(&sock_once, sock_init);
    pthread_mutex_lock(&sock_mu);
    Sock *s = sock_get(h);
    if (!s) {
        pthread_mutex_unlock(&sock_mu);
        return fail(c, WSAENOTSOCK);
    }
    if (s->event) rt_waitable_unref(s->event);
    s->event = ev;
    if (ev) rt_waitable_ref(ev);
    s->hwnd = hwnd;
    s->msg = msg;
    s->interest = mask;
    s->armed = mask & (FD_READ | FD_ACCEPT | FD_CLOSE);
    if (s->connected && !s->is_dgram) s->armed |= mask & FD_WRITE;
    if (s->is_dgram) s->armed |= mask & FD_WRITE;
    s->pending = 0;
    if (mask) set_nonblocking(s, 1);
    start_poller();
    pthread_mutex_unlock(&sock_mu);
    wake_poller();
    if (g_opt.verbose)
        rt_log("[net] socket %x notifications %#x -> %s %x\n", h, mask, ev ? "event" : "window", ev ? 0 : hwnd);
    return 0;
}

/* WSAAsyncSelect(s, hwnd, msg, events) */
H(ws_WSAAsyncSelect) { return select_events(c, a[0], a[1], a[2], NULL, a[3]); }

/* WSAEventSelect(s, event, events) */
H(ws_WSAEventSelect) {
    RtWaitable *ev = a[1] ? rt_handle_get(a[1], RT_H_WAITABLE) : NULL;
    if (a[1] && !ev) return fail(c, WSAEINVAL);
    return select_events(c, a[0], 0, 0, ev, a[2]);
}

H(ws_WSACreateEvent) {
    UNUSED;
    return rt_handle_alloc(RT_H_WAITABLE, rt_waitable_new(RT_W_EVENT, 1, 0), rt_waitable_unref);
}

/* WSAEnumNetworkEvents(s, event, &networkEvents{long events; int errors[10]}) */
H(ws_WSAEnumNetworkEvents) {
    RtWaitable *ev = a[1] ? rt_handle_get(a[1], RT_H_WAITABLE) : NULL;
    pthread_mutex_lock(&sock_mu);
    Sock *s = sock_get(a[0]);
    if (!s) {
        pthread_mutex_unlock(&sock_mu);
        return fail(c, WSAENOTSOCK);
    }
    if (ev) rt_waitable_reset(ev);
    st32(a[2], s->pending);
    for (int i = 0; i < 10; i++) st32(a[2] + 4 + 4 * (uint32_t)i, i < 6 ? s->errors[i] : 0);
    s->pending = 0;
    memset(s->errors, 0, sizeof s->errors);
    pthread_mutex_unlock(&sock_mu);
    return 0;
}

static const ImportDef defs[] = {
    {"ws2_32.dll", "WSAStartup", ws_WSAStartup, 2, 0},
    {"ws2_32.dll", "WSACleanup", ws_WSACleanup, 0, 0},
    {"ws2_32.dll", "WSAGetLastError", ws_WSAGetLastError, 0, 0},
    {"ws2_32.dll", "htonl", ws_htonl, 1, 0},
    {"ws2_32.dll", "htons", ws_htons, 1, 0},
    {"ws2_32.dll", "inet_addr", ws_inet_addr, 1, 0},
    {"ws2_32.dll", "socket", ws_socket, 3, 0},
    {"ws2_32.dll", "closesocket", ws_closesocket, 1, 0},
    {"ws2_32.dll", "connect", ws_connect, 3, 0},
    {"ws2_32.dll", "bind", ws_bind, 3, 0},
    {"ws2_32.dll", "accept", ws_accept, 3, 0},
    {"ws2_32.dll", "send", ws_send, 4, 0},
    {"ws2_32.dll", "recv", ws_recv, 4, 0},
    {"ws2_32.dll", "sendto", ws_sendto, 6, 0},
    {"ws2_32.dll", "recvfrom", ws_recvfrom, 6, 0},
    {"ws2_32.dll", "shutdown", ws_shutdown, 2, 0},
    {"ws2_32.dll", "setsockopt", ws_setsockopt, 5, 0},
    {"ws2_32.dll", "ioctlsocket", ws_ioctlsocket, 3, 0},
    {"ws2_32.dll", "getpeername", ws_getpeername, 3, 0},
    {"ws2_32.dll", "getsockname", ws_getsockname, 3, 0},
    {"ws2_32.dll", "gethostname", ws_gethostname, 2, 0},
    {"ws2_32.dll", "gethostbyname", ws_gethostbyname, 1, 0},
    {"ws2_32.dll", "WSAAsyncSelect", ws_WSAAsyncSelect, 4, 0},
    {"ws2_32.dll", "WSAEventSelect", ws_WSAEventSelect, 3, 0},
    {"ws2_32.dll", "WSACreateEvent", ws_WSACreateEvent, 0, 0},
    {"ws2_32.dll", "WSAEnumNetworkEvents", ws_WSAEnumNetworkEvents, 3, 0},
};
RT_EXPORT_IMPORTS(rt_imports_winsock, defs);
