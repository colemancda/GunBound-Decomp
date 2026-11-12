/* kernel32 file access.
 *
 * The guest's C:\GunBound is the game directory (--gamedir). Names are matched
 * without regard to case, component by component. Everything the guest writes
 * goes to the save directory (--savedir, by default the game directory itself):
 * when the two differ the save directory is an overlay, looked at first and the
 * only place files are created, changed or deleted, so the game files can stay
 * read-only. Paths outside C:\GunBound live under <savedir>/drive_c.
 */
#define _GNU_SOURCE
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>

#include "rt.h"

#define INVALID_HANDLE 0xFFFFFFFFu
#define H_STDIN 0x00000010u
#define H_STDOUT 0x00000014u
#define H_STDERR 0x00000018u

#define ERROR_FILE_NOT_FOUND 2u
#define ERROR_PATH_NOT_FOUND 3u
#define ERROR_ACCESS_DENIED 5u
#define ERROR_INVALID_HANDLE 6u
#define ERROR_FILE_EXISTS 80u
#define ERROR_INVALID_PARAMETER 87u
#define ERROR_ALREADY_EXISTS 183u

typedef struct RtFile {
    int fd;
    char path[768];
} RtFile;

static uint32_t errno_to_win(int e) {
    switch (e) {
    case ENOENT: return ERROR_FILE_NOT_FOUND;
    case ENOTDIR: return ERROR_PATH_NOT_FOUND;
    case EACCES: case EPERM: case EROFS: case EISDIR: return ERROR_ACCESS_DENIED;
    case EEXIST: return ERROR_FILE_EXISTS;
    default: return ERROR_ACCESS_DENIED;
    }
}

/* Append component `name` to the host directory `dir` (dir is modified), matching
 * an existing entry case-insensitively. Returns 1 if the entry exists. */
static int descend(char *dir, size_t cap, const char *name) {
    size_t n = strlen(dir);
    struct stat st;
    snprintf(dir + n, cap - n, "/%s", name);
    if (lstat(dir, &st) == 0 || stat(dir, &st) == 0) return 1;
    dir[n] = 0;
    DIR *d = opendir(dir);
    int found = 0;
    if (d) {
        struct dirent *e;
        while ((e = readdir(d)) != NULL) {
            if (!strcasecmp(e->d_name, name)) {
                snprintf(dir + n, cap - n, "/%s", e->d_name);
                found = 1;
                break;
            }
        }
        closedir(d);
    }
    if (!found) snprintf(dir + n, cap - n, "/%s", name);
    return found;
}

/* Resolve `comps` under host directory `root`. Returns 1 if the whole path exists. */
static int walk(const char *root, char comps[][256], int ncomp, char *out, size_t cap) {
    snprintf(out, cap, "%s", root);
    int exists = 1;
    for (int i = 0; i < ncomp; i++) {
        if (exists) exists = descend(out, cap, comps[i]);
        else {
            size_t n = strlen(out);
            snprintf(out + n, cap - n, "/%s", comps[i]);
        }
    }
    return exists;
}

static int overlay_active(void) { return strcmp(g_opt.gamedir, g_opt.savedir) != 0; }

static void mkdirs_for(const char *path) {
    char tmp[768];
    snprintf(tmp, sizeof tmp, "%s", path);
    for (char *p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = 0;
            mkdir(tmp, 0777);
            *p = '/';
        }
    }
}

/* Translate a guest path. `write`: the caller will create or modify the file.
 * Returns 1 if the resulting host path exists. *in_game is set when the file
 * exists only in the (read-only) game directory; for a write the result is then
 * the overlay path to create and game_path (768 bytes, optional) the original. */
static int resolve2(const char *guest, int write, char *out, size_t cap, int *in_game, char *game_path) {
    char comps[32][256];
    int n = 0;
    const char *p = guest;
    int absolute = 0;
    if (in_game) *in_game = 0;
    if (((p[0] | 0x20) >= 'a' && (p[0] | 0x20) <= 'z') && p[1] == ':') {
        p += 2;
        absolute = *p == '\\' || *p == '/';
    } else if (*p == '\\' || *p == '/') {
        absolute = 1;
    }
    if (!absolute) snprintf(comps[n++], 256, "GunBound"); /* the current directory is the game's */
    while (*p) {
        while (*p == '\\' || *p == '/') p++;
        size_t len = strcspn(p, "\\/");
        if (!len) break;
        if (len == 1 && p[0] == '.') {
        } else if (len == 2 && p[0] == '.' && p[1] == '.') {
            if (n > 0) n--;
        } else if (n < 32) {
            snprintf(comps[n++], 256, "%.*s", (int)(len > 255 ? 255 : len), p);
        }
        p += len;
    }
    if (n > 0 && !strcasecmp(comps[0], "GunBound")) {
        int exists = walk(g_opt.savedir, comps + 1, n - 1, out, cap);
        if (!overlay_active() || exists) return exists;
        char game[768];
        int in_g = walk(g_opt.gamedir, comps + 1, n - 1, game, sizeof game);
        if (write) {
            /* Create it in the overlay, under the directories the game tree has. */
            if (n > 1) {
                char parent[768];
                if (n == 2 || walk(g_opt.gamedir, comps + 1, n - 2, parent, sizeof parent)) mkdirs_for(out);
            }
            if (in_game) *in_game = in_g;
            if (in_g && game_path) snprintf(game_path, 768, "%s", game);
            return 0;
        }
        if (in_g) {
            snprintf(out, cap, "%s", game);
            if (in_game) *in_game = 1;
        }
        return in_g;
    }
    char root[640];
    snprintf(root, sizeof root, "%.600s/drive_c", g_opt.savedir);
    int exists = walk(root, comps, n, out, cap);
    if (write && !exists) mkdirs_for(out);
    return exists;
}

static int resolve(const char *guest, int write, char *out, size_t cap, int *in_game) {
    return resolve2(guest, write, out, cap, in_game, NULL);
}

static int copy_file(const char *from, const char *to) {
    int in = open(from, O_RDONLY | O_CLOEXEC);
    if (in < 0) return 0;
    int out = open(to, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0666);
    if (out < 0) {
        close(in);
        return 0;
    }
    char buf[65536];
    ssize_t r;
    int ok = 1;
    while ((r = read(in, buf, sizeof buf)) > 0)
        if (write(out, buf, (size_t)r) != r) ok = 0;
    close(in);
    close(out);
    return ok && r == 0;
}

static void file_close(void *obj) {
    RtFile *f = obj;
    close(f->fd);
    free(f);
}

/* CreateFileA(name, access, share, security, disposition, flags, template) */
H(k32_CreateFileA) {
    const char *name = rt_gstr(a[0]);
    /* The game opens its archives with OPEN_ALWAYS, some of them for reading only:
     * the disposition alone does not make an open a write. */
    int want_write = (a[1] & 0x50000000u) != 0 || a[4] == 2 || a[4] == 5;
    char host[768], game[768];
    int in_game = 0;
    int exists = resolve(name, 0, host, sizeof host, &in_game);
    if ((!exists && (a[4] == 1 || a[4] == 2 || a[4] == 4)) || (exists && in_game && want_write)) {
        /* It will be created, or it exists only in the game directory and is opened for
         * writing: the file to work on is the one in the save directory. A file about to
         * be truncated needs no copy of its old contents. */
        int was_in_game = exists && in_game;
        resolve2(name, 1, host, sizeof host, &in_game, game);
        if (was_in_game && (a[4] == 3 || a[4] == 4)) {
            exists = copy_file(game, host);
            rt_log("recomp: \"%s\" is opened for writing: copied to the save directory\n", name);
        }
        want_write = 1;
    }
    int flags = O_CLOEXEC;
    if ((a[1] & 0xC0000000u) == 0xC0000000u || (a[1] & 0x10000000u)) flags |= O_RDWR;
    else if (a[1] & 0x40000000u) flags |= O_WRONLY;
    else flags |= O_RDONLY;
    uint32_t err = 0;
    switch (a[4]) {
    case 1: /* CREATE_NEW */
        if (exists) {
            rt_set_last_error(c, ERROR_FILE_EXISTS);
            return INVALID_HANDLE;
        }
        flags |= O_CREAT | O_EXCL;
        break;
    case 2: /* CREATE_ALWAYS */
        flags |= O_CREAT | O_TRUNC;
        if (exists) err = ERROR_ALREADY_EXISTS;
        break;
    case 3: /* OPEN_EXISTING */
        break;
    case 4: /* OPEN_ALWAYS */
        flags |= O_CREAT;
        if (exists) err = ERROR_ALREADY_EXISTS;
        break;
    case 5: /* TRUNCATE_EXISTING */
        if (!exists) {
            rt_set_last_error(c, ERROR_FILE_NOT_FOUND);
            return INVALID_HANDLE;
        }
        flags |= O_CREAT | O_TRUNC;
        break;
    default:
        rt_set_last_error(c, ERROR_INVALID_PARAMETER);
        return INVALID_HANDLE;
    }
    int fd = open(host, flags, 0666);
    struct stat st;
    if (fd >= 0 && fstat(fd, &st) == 0 && S_ISDIR(st.st_mode)) {
        close(fd);
        fd = -1;
        errno = EACCES;
    }
    if (fd < 0) {
        int e = errno;
        if (g_opt.verbose || g_trace_imports) rt_log("[file] open \"%s\" -> %s: %s\n", name, host, strerror(e));
        rt_set_last_error(c, errno_to_win(e));
        return INVALID_HANDLE;
    }
    RtFile *f = calloc(1, sizeof *f);
    f->fd = fd;
    snprintf(f->path, sizeof f->path, "%s", host);
    uint32_t h = rt_handle_alloc(RT_H_FILE, f, file_close);
    if (g_opt.verbose || g_trace_imports)
        rt_log("[file] open \"%s\" -> %s (handle %x%s)\n", name, host, h, want_write ? ", writable" : "");
    rt_set_last_error(c, err);
    return h;
}

/* ReadFile(handle, buffer, count, &read, overlapped) */
H(k32_ReadFile) {
    if (a[3]) st32(a[3], 0);
    RtFile *f = rt_handle_get(a[0], RT_H_FILE);
    int fd = f ? f->fd : a[0] == H_STDIN ? 0 : -1;
    if (fd < 0) {
        rt_set_last_error(c, ERROR_INVALID_HANDLE);
        return 0;
    }
    if (!f) return 1; /* standard input: always at end of file */
    uint32_t done = 0;
    while (done < a[2]) {
        ssize_t r = read(fd, G(a[1] + done), a[2] - done);
        if (r < 0) {
            if (errno == EINTR) continue;
            rt_set_last_error(c, errno_to_win(errno));
            return 0;
        }
        if (r == 0) break;
        done += (uint32_t)r;
    }
    if (a[3]) st32(a[3], done);
    return 1;
}

/* WriteFile(handle, buffer, count, &written, overlapped) */
H(k32_WriteFile) {
    if (a[3]) st32(a[3], 0);
    RtFile *f = rt_handle_get(a[0], RT_H_FILE);
    if (!f) {
        if (a[0] == H_STDOUT || a[0] == H_STDERR) {
            /* The guest's console output goes to the host's standard error, marked as such. */
            rt_log("[guest %s] %.*s%s", a[0] == H_STDOUT ? "stdout" : "stderr", (int)a[2], (const char *)G(a[1]),
                   a[2] && ld8(a[1] + a[2] - 1) == '\n' ? "" : "\n");
            if (a[3]) st32(a[3], a[2]);
            return 1;
        }
        rt_set_last_error(c, ERROR_INVALID_HANDLE);
        return 0;
    }
    uint32_t done = 0;
    while (done < a[2]) {
        ssize_t r = write(f->fd, G(a[1] + done), a[2] - done);
        if (r < 0) {
            if (errno == EINTR) continue;
            rt_set_last_error(c, errno_to_win(errno));
            return 0;
        }
        done += (uint32_t)r;
    }
    if (a[3]) st32(a[3], done);
    return 1;
}

/* SetFilePointer(handle, distanceLow, &distanceHigh, method) */
H(k32_SetFilePointer) {
    RtFile *f = rt_handle_get(a[0], RT_H_FILE);
    if (!f) {
        rt_set_last_error(c, ERROR_INVALID_HANDLE);
        return 0xFFFFFFFFu;
    }
    int64_t off = (int32_t)a[1];
    if (a[2]) off = (int64_t)(((uint64_t)ld32(a[2]) << 32) | a[1]);
    int whence = a[3] == 0 ? SEEK_SET : a[3] == 1 ? SEEK_CUR : SEEK_END;
    off_t r = lseek(f->fd, (off_t)off, whence);
    if (r < 0) {
        rt_set_last_error(c, 131); /* ERROR_NEGATIVE_SEEK */
        return 0xFFFFFFFFu;
    }
    if (a[2]) st32(a[2], (uint32_t)((uint64_t)r >> 32));
    rt_set_last_error(c, 0);
    return (uint32_t)r;
}

H(k32_GetFileSize) {
    RtFile *f = rt_handle_get(a[0], RT_H_FILE);
    struct stat st;
    if (!f || fstat(f->fd, &st) != 0) {
        rt_set_last_error(c, ERROR_INVALID_HANDLE);
        return 0xFFFFFFFFu;
    }
    if (a[1]) st32(a[1], (uint32_t)((uint64_t)st.st_size >> 32));
    rt_set_last_error(c, 0);
    return (uint32_t)st.st_size;
}

H(k32_SetEndOfFile) {
    RtFile *f = rt_handle_get(a[0], RT_H_FILE);
    if (!f) {
        rt_set_last_error(c, ERROR_INVALID_HANDLE);
        return 0;
    }
    off_t pos = lseek(f->fd, 0, SEEK_CUR);
    return pos >= 0 && ftruncate(f->fd, pos) == 0;
}

H(k32_FlushFileBuffers) { UNUSED; return 1; }

H(k32_GetFileType) {
    UNUSED;
    if (a[0] == H_STDIN || a[0] == H_STDOUT || a[0] == H_STDERR) return 2; /* FILE_TYPE_CHAR */
    if (rt_handle_get(a[0], RT_H_FILE)) return 1;                          /* FILE_TYPE_DISK */
    return 0;
}

H(k32_DeleteFileA) {
    char host[768];
    int in_game = 0;
    if (!resolve(rt_gstr(a[0]), 0, host, sizeof host, &in_game)) {
        rt_set_last_error(c, ERROR_FILE_NOT_FOUND);
        return 0;
    }
    if (in_game) {
        rt_log("recomp: DeleteFileA(\"%s\"): the file is in the read-only game directory; not deleted\n",
               rt_gstr(a[0]));
        rt_set_last_error(c, ERROR_ACCESS_DENIED);
        return 0;
    }
    if (unlink(host) != 0) {
        rt_set_last_error(c, errno_to_win(errno));
        return 0;
    }
    return 1;
}

H(k32_MoveFileA) {
    char from[768], to[768];
    int in_game = 0;
    if (!resolve(rt_gstr(a[0]), 0, from, sizeof from, &in_game)) {
        rt_set_last_error(c, ERROR_FILE_NOT_FOUND);
        return 0;
    }
    if (resolve(rt_gstr(a[1]), 1, to, sizeof to, NULL)) {
        rt_set_last_error(c, ERROR_ALREADY_EXISTS);
        return 0;
    }
    int ok = in_game ? copy_file(from, to) : rename(from, to) == 0;
    if (in_game) rt_log("recomp: MoveFileA(\"%s\"): the source is in the read-only game directory; copied\n", rt_gstr(a[0]));
    if (!ok) rt_set_last_error(c, errno_to_win(errno));
    return (uint32_t)ok;
}

H(k32_CreateDirectoryA) {
    char host[768];
    if (resolve(rt_gstr(a[0]), 1, host, sizeof host, NULL)) {
        rt_set_last_error(c, ERROR_ALREADY_EXISTS);
        return 0;
    }
    if (mkdir(host, 0777) != 0) {
        rt_set_last_error(c, errno == EEXIST ? ERROR_ALREADY_EXISTS : ERROR_PATH_NOT_FOUND);
        return 0;
    }
    return 1;
}

static uint32_t attributes_of(const struct stat *st) {
    if (S_ISDIR(st->st_mode)) return 0x10; /* FILE_ATTRIBUTE_DIRECTORY */
    return 0x20;                           /* FILE_ATTRIBUTE_ARCHIVE */
}

H(k32_GetFileAttributesA) {
    char host[768];
    struct stat st;
    if (!resolve(rt_gstr(a[0]), 0, host, sizeof host, NULL) || stat(host, &st) != 0) {
        rt_set_last_error(c, ERROR_FILE_NOT_FOUND);
        return 0xFFFFFFFFu;
    }
    return attributes_of(&st);
}

H(k32_SetFileAttributesA) {
    char host[768];
    if (!resolve(rt_gstr(a[0]), 0, host, sizeof host, NULL)) {
        rt_set_last_error(c, ERROR_FILE_NOT_FOUND);
        return 0;
    }
    return 1;
}

static uint64_t filetime_of(time_t t) { return ((uint64_t)t + 11644473600ull) * 10000000ull; }

static int wild_match(const char *pat, const char *s) {
    for (; *pat; pat++, s++) {
        if (*pat == '*') {
            while (pat[1] == '*') pat++;
            if (!pat[1]) return 1;
            for (; *s; s++)
                if (wild_match(pat + 1, s)) return 1;
            return wild_match(pat + 1, s);
        }
        if (!*s) return 0;
        if (*pat != '?' && tolower((unsigned char)*pat) != tolower((unsigned char)*s)) return 0;
    }
    return *s == 0;
}

static void fill_find_data(uint32_t p, const char *name, const struct stat *st) {
    memset(G(p), 0, 320);
    st32(p, attributes_of(st));
    st64(p + 4, filetime_of(st->st_ctime));
    st64(p + 12, filetime_of(st->st_atime));
    st64(p + 20, filetime_of(st->st_mtime));
    st32(p + 28, (uint32_t)((uint64_t)st->st_size >> 32));
    st32(p + 32, (uint32_t)st->st_size);
    snprintf((char *)G(p + 44), 260, "%s", name);
}

/* First match of `pat` in host directory `dir`. */
static int find_in(const char *dir, const char *pat, uint32_t out) {
    DIR *d = opendir(dir);
    if (!d) return 0;
    struct dirent *e;
    int found = 0;
    while (!found && (e = readdir(d)) != NULL) {
        if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, "..")) continue;
        if (!wild_match(pat, e->d_name)) continue;
        char full[1100];
        struct stat st;
        snprintf(full, sizeof full, "%s/%s", dir, e->d_name);
        if (stat(full, &st) != 0) continue;
        fill_find_data(out, e->d_name, &st);
        found = 1;
    }
    closedir(d);
    return found;
}

/* FindFirstFileA(pattern, &findData). The program imports neither FindNextFileA
 * nor FindClose, so only the first match is ever looked at. */
H(k32_FindFirstFileA) {
    const char *g = rt_gstr(a[0]);
    char dirpart[600], pat[260];
    const char *slash = strrchr(g, '\\');
    const char *fs = strrchr(g, '/');
    if (fs > slash) slash = fs;
    if (slash) {
        snprintf(dirpart, sizeof dirpart, "%.*s", (int)(slash - g + 1), g);
        snprintf(pat, sizeof pat, "%s", slash + 1);
    } else {
        snprintf(dirpart, sizeof dirpart, ".");
        snprintf(pat, sizeof pat, "%s", g);
    }
    char host[768];
    int found = 0;
    int in_game = 0;
    if (resolve(dirpart, 0, host, sizeof host, &in_game)) found = find_in(host, pat, a[1]);
    if (!found && overlay_active() && !in_game) {
        /* the directory exists in the overlay but the file may only be in the game tree */
        char both[768];
        snprintf(both, sizeof both, "%s", g_opt.savedir);
        size_t n = strlen(g_opt.savedir);
        if (!strncmp(host, both, n)) {
            snprintf(both, sizeof both, "%.300s%.400s", g_opt.gamedir, host + n);
            found = find_in(both, pat, a[1]);
        }
    }
    if (g_opt.verbose || g_trace_imports) rt_log("[file] find \"%s\" -> %s\n", g, found ? "found" : "not found");
    if (!found) {
        rt_set_last_error(c, ERROR_FILE_NOT_FOUND);
        return INVALID_HANDLE;
    }
    return rt_handle_alloc(RT_H_FIND, NULL, NULL);
}

H(k32_GetSystemDirectoryA) {
    UNUSED;
    static const char dir[] = "C:\\WINDOWS\\system32";
    if (a[1] < sizeof dir) return sizeof dir;
    memcpy(G(a[0]), dir, sizeof dir);
    return sizeof dir - 1;
}

/* ------------------------------------------------------------ resources
 * FindResource walks the three-level resource directory of the image:
 * type, name, language. Names and types are integers or strings. */
static uint32_t rsrc_lookup(uint32_t dir, uint32_t key) {
    uint32_t base = g_image.base + g_image.rsrc_rva;
    uint32_t nnamed = ld16(dir + 12), nid = ld16(dir + 14);
    for (uint32_t i = 0; i < nnamed + nid; i++) {
        uint32_t e = dir + 16 + 8 * i;
        uint32_t name = ld32(e), off = ld32(e + 4);
        if (key >= 0x10000) {
            if (!(name & 0x80000000u)) continue;
            uint32_t ws = base + (name & 0x7FFFFFFF);
            uint32_t len = ld16(ws);
            const char *want = rt_gstr(key);
            if (strlen(want) != len) continue;
            uint32_t k;
            for (k = 0; k < len; k++)
                if (toupper((unsigned char)want[k]) != toupper(ld16(ws + 2 + 2 * k) & 0xFF)) break;
            if (k == len) return off;
        } else if (!(name & 0x80000000u) && name == key) {
            return off;
        }
    }
    return 0;
}

static uint32_t find_resource(CPU *c, uint32_t name, uint32_t type) {
    if (!g_image.rsrc_rva) {
        rt_set_last_error(c, 1812); /* ERROR_RESOURCE_DATA_NOT_FOUND */
        return 0;
    }
    uint32_t base = g_image.base + g_image.rsrc_rva;
    uint32_t off = rsrc_lookup(base, type);
    if (off & 0x80000000u) off = rsrc_lookup(base + (off & 0x7FFFFFFF), name);
    else off = 0;
    if (off & 0x80000000u) {
        uint32_t dir = base + (off & 0x7FFFFFFF);
        off = ld16(dir + 12) + ld16(dir + 14) ? ld32(dir + 16 + 4) : 0; /* first language */
    }
    if (!off || (off & 0x80000000u)) {
        rt_set_last_error(c, 1814); /* ERROR_RESOURCE_NAME_NOT_FOUND */
        return 0;
    }
    return base + off; /* IMAGE_RESOURCE_DATA_ENTRY */
}

H(k32_FindResourceA) { return find_resource(c, a[1], a[2]); }
H(k32_FindResourceExA) { return find_resource(c, a[2], a[1]); }
H(k32_LoadResource) { UNUSED; return a[1] ? g_image.base + ld32(a[1]) : 0; }
H(k32_SizeofResource) { UNUSED; return a[1] ? ld32(a[1] + 4) : 0; }

static const ImportDef defs[] = {
    {"kernel32.dll", "CreateFileA", k32_CreateFileA, 7, 0},
    {"kernel32.dll", "ReadFile", k32_ReadFile, 5, 0},
    {"kernel32.dll", "WriteFile", k32_WriteFile, 5, 0},
    {"kernel32.dll", "SetFilePointer", k32_SetFilePointer, 4, 0},
    {"kernel32.dll", "GetFileSize", k32_GetFileSize, 2, 0},
    {"kernel32.dll", "SetEndOfFile", k32_SetEndOfFile, 1, 0},
    {"kernel32.dll", "FlushFileBuffers", k32_FlushFileBuffers, 1, 0},
    {"kernel32.dll", "GetFileType", k32_GetFileType, 1, 0},
    {"kernel32.dll", "DeleteFileA", k32_DeleteFileA, 1, 0},
    {"kernel32.dll", "MoveFileA", k32_MoveFileA, 2, 0},
    {"kernel32.dll", "CreateDirectoryA", k32_CreateDirectoryA, 2, 0},
    {"kernel32.dll", "GetFileAttributesA", k32_GetFileAttributesA, 1, 0},
    {"kernel32.dll", "SetFileAttributesA", k32_SetFileAttributesA, 2, 0},
    {"kernel32.dll", "FindFirstFileA", k32_FindFirstFileA, 2, 0},
    {"kernel32.dll", "GetSystemDirectoryA", k32_GetSystemDirectoryA, 2, 0},
    {"kernel32.dll", "FindResourceA", k32_FindResourceA, 3, 0},
    {"kernel32.dll", "FindResourceExA", k32_FindResourceExA, 4, 0},
    {"kernel32.dll", "LoadResource", k32_LoadResource, 2, 0},
    {"kernel32.dll", "SizeofResource", k32_SizeofResource, 2, 0},
};
RT_EXPORT_IMPORTS(rt_imports_file, defs);
