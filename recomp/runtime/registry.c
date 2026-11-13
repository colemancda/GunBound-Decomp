/* advapi32 registry, backed by a text file in the format of a .reg export:
 *
 *   [HKEY_CURRENT_USER\Software\Softnyx\GunBound]
 *   "Location"="C:\\GunBound"
 *   "Version"=dword:00000118
 *   "Blob"=hex:01,02,03
 *
 * The file is read at the first registry call and rewritten whenever the guest
 * changes a value. When it does not exist it is created with the two values the
 * game cannot start without (its install location and its client version) and
 * the settings its launcher provisions. --broker overrides the server address.
 */
#define _GNU_SOURCE
#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "rt.h"

#define REG_SZ 1u
#define REG_BINARY 3u
#define REG_DWORD 4u
#define ERROR_FILE_NOT_FOUND 2u
#define ERROR_INVALID_HANDLE 6u
#define ERROR_MORE_DATA 234u
#define ERROR_NO_MORE_ITEMS 259u

#define HKEY_ROOT_FIRST 0x80000000u
#define HKEY_OPEN_BASE 0x00E00000u

typedef struct RegValue {
    char *name;
    uint32_t type, len;
    uint8_t *data;
    struct RegValue *next;
} RegValue;

typedef struct RegKey {
    char *path; /* e.g. HKEY_CURRENT_USER\Software\Softnyx\GunBound */
    RegValue *values;
    struct RegKey *next;
} RegKey;

static RegKey *keys;
static char *open_keys[256];
static pthread_mutex_t reg_mu = PTHREAD_MUTEX_INITIALIZER;
static int loaded;

static const char *const root_names[] = {
    "HKEY_CLASSES_ROOT", "HKEY_CURRENT_USER", "HKEY_LOCAL_MACHINE", "HKEY_USERS",
};

static RegKey *key_find(const char *path) {
    for (RegKey *k = keys; k; k = k->next)
        if (!strcasecmp(k->path, path)) return k;
    return NULL;
}

static RegKey *key_create(const char *path) {
    RegKey *k = key_find(path);
    if (k) return k;
    k = calloc(1, sizeof *k);
    k->path = strdup(path);
    /* keep file order: append */
    RegKey **pp = &keys;
    while (*pp) pp = &(*pp)->next;
    *pp = k;
    return k;
}

static RegValue *value_find(RegKey *k, const char *name) {
    for (RegValue *v = k->values; v; v = v->next)
        if (!strcasecmp(v->name, name)) return v;
    return NULL;
}

static void value_set(RegKey *k, const char *name, uint32_t type, const void *data, uint32_t len) {
    RegValue *v = value_find(k, name);
    if (!v) {
        v = calloc(1, sizeof *v);
        v->name = strdup(name);
        RegValue **pp = &k->values;
        while (*pp) pp = &(*pp)->next;
        *pp = v;
    }
    free(v->data);
    v->type = type;
    v->len = len;
    v->data = malloc(len ? len : 1);
    memcpy(v->data, data, len);
}

static void set_sz(RegKey *k, const char *name, const char *s) { value_set(k, name, REG_SZ, s, (uint32_t)strlen(s) + 1); }
static void set_dword(RegKey *k, const char *name, uint32_t v) { value_set(k, name, REG_DWORD, &v, 4); }

static void reg_save(void) {
    FILE *f = fopen(g_opt.regfile, "w");
    if (!f) {
        rt_log("recomp: cannot write the registry file %s\n", g_opt.regfile);
        return;
    }
    fprintf(f, "; Registry of the recompiled GunBound client. Edit while the game is not running.\n");
    for (RegKey *k = keys; k; k = k->next) {
        fprintf(f, "\n[%s]\n", k->path);
        for (RegValue *v = k->values; v; v = v->next) {
            fputc('"', f);
            for (const char *p = v->name; *p; p++) {
                if (*p == '"' || *p == '\\') fputc('\\', f);
                fputc(*p, f);
            }
            fputs("\"=", f);
            if (v->type == REG_SZ) {
                fputc('"', f);
                for (uint32_t i = 0; i < v->len && v->data[i]; i++) {
                    if (v->data[i] == '"' || v->data[i] == '\\') fputc('\\', f);
                    fputc(v->data[i], f);
                }
                fputs("\"\n", f);
            } else if (v->type == REG_DWORD && v->len == 4) {
                uint32_t d;
                memcpy(&d, v->data, 4);
                fprintf(f, "dword:%08x\n", d);
            } else {
                if (v->type == REG_BINARY) fputs("hex:", f);
                else fprintf(f, "hex(%x):", v->type);
                for (uint32_t i = 0; i < v->len; i++) fprintf(f, i ? ",%02x" : "%02x", v->data[i]);
                fputc('\n', f);
            }
        }
    }
    fclose(f);
}

/* Parse a quoted string with backslash escapes starting at *pp (after the opening quote). */
static char *parse_quoted(char **pp) {
    char *p = *pp, *out = malloc(strlen(p) + 1);
    size_t o = 0;
    while (*p && *p != '"') {
        if (*p == '\\' && p[1]) p++;
        out[o++] = *p++;
    }
    out[o] = 0;
    if (*p == '"') p++;
    *pp = p;
    return out;
}

static const char *const game_keys[] = {
    "HKEY_CURRENT_USER\\Software\\Softnyx\\GunBound",
    "HKEY_LOCAL_MACHINE\\Software\\Softnyx\\GunBound",
};

/* --broker HOST[:PORT]: where the game looks for its server list. */
static void apply_broker_option(void) {
    if (!g_opt.broker[0]) return;
    char host[sizeof g_opt.broker];
    unsigned port = 8372;
    snprintf(host, sizeof host, "%s", g_opt.broker);
    char *colon = strrchr(host, ':');
    if (colon) {
        *colon = 0;
        port = (unsigned)atoi(colon + 1);
    }
    for (size_t i = 0; i < RT_COUNTOF(game_keys); i++) {
        RegKey *k = key_find(game_keys[i]);
        if (!k) k = key_create(game_keys[i]);
        set_sz(k, "IP", host);
        set_sz(k, "BuddyIP", host);
        set_dword(k, "Port", port);
    }
}

static void reg_load(void) {
    if (loaded) return;
    loaded = 1;
    FILE *f = fopen(g_opt.regfile, "r");
    if (!f) {
        /* What the game's launcher writes for a fresh installation. */
        static const uint8_t one = 1, two = 2, zero = 0;
        for (size_t i = 0; i < RT_COUNTOF(game_keys); i++) {
            RegKey *k = key_create(game_keys[i]);
            set_sz(k, "Location", "C:\\GunBound\\");
            set_dword(k, "Version", 280);
            set_dword(k, "AutoRefresh", 1);
            value_set(k, "Background", REG_BINARY, &one, 1);
            value_set(k, "Effect3D", REG_BINARY, &two, 1);
            set_dword(k, "EffectVolume", 95);
            set_dword(k, "MusicVolume", 95);
            value_set(k, "MidiMode", REG_BINARY, &one, 1);
            set_dword(k, "MouseSpeed", 50);
            value_set(k, "ShootingMode", REG_BINARY, &zero, 1);
        }
        rt_log("recomp: no registry file at %s; created one with the launcher's default settings\n", g_opt.regfile);
        apply_broker_option();
        reg_save();
        return;
    }
    char line[4096];
    RegKey *cur = NULL;
    while (fgets(line, sizeof line, f)) {
        char *p = line;
        while (isspace((unsigned char)*p)) p++;
        size_t n = strlen(p);
        while (n && isspace((unsigned char)p[n - 1])) p[--n] = 0;
        if (!*p || *p == ';' || *p == '#') continue;
        if (*p == '[') {
            char *e = strrchr(p, ']');
            if (e) *e = 0;
            cur = key_create(p + 1);
            continue;
        }
        if (*p != '"' || !cur) continue;
        p++;
        char *name = parse_quoted(&p);
        while (isspace((unsigned char)*p)) p++;
        if (*p == '=') {
            p++;
            while (isspace((unsigned char)*p)) p++;
            if (*p == '"') {
                p++;
                char *val = parse_quoted(&p);
                set_sz(cur, name, val);
                free(val);
            } else if (!strncasecmp(p, "dword:", 6)) {
                set_dword(cur, name, (uint32_t)strtoul(p + 6, NULL, 16));
            } else if (!strncasecmp(p, "hex", 3)) {
                uint32_t type = REG_BINARY;
                p += 3;
                if (*p == '(') {
                    type = (uint32_t)strtoul(p + 1, &p, 16);
                    if (*p == ')') p++;
                }
                if (*p == ':') p++;
                uint8_t buf[2048];
                uint32_t len = 0;
                while (*p && len < sizeof buf) {
                    char *e;
                    unsigned long b = strtoul(p, &e, 16);
                    if (e == p) break;
                    buf[len++] = (uint8_t)b;
                    p = e;
                    while (*p == ',' || isspace((unsigned char)*p)) p++;
                }
                value_set(cur, name, type, buf, len);
            }
        }
        free(name);
    }
    fclose(f);
    apply_broker_option();
}

/* Path of a key handle, or NULL. Under reg_mu. */
static const char *hkey_path(uint32_t h) {
    if (h >= HKEY_ROOT_FIRST && h - HKEY_ROOT_FIRST < RT_COUNTOF(root_names)) return root_names[h - HKEY_ROOT_FIRST];
    uint32_t i = h - HKEY_OPEN_BASE;
    if (h >= HKEY_OPEN_BASE && i < RT_COUNTOF(open_keys)) return open_keys[i];
    return NULL;
}

static uint32_t hkey_open(const char *path) {
    for (uint32_t i = 0; i < RT_COUNTOF(open_keys); i++) {
        if (!open_keys[i]) {
            open_keys[i] = strdup(path);
            return HKEY_OPEN_BASE + i;
        }
    }
    return 0;
}

static int join_path(char *out, size_t cap, uint32_t hkey, uint32_t subkey) {
    const char *base = hkey_path(hkey);
    if (!base) return 0;
    const char *sub = subkey ? rt_gstr(subkey) : "";
    while (*sub == '\\') sub++;
    if (*sub) snprintf(out, cap, "%s\\%s", base, sub);
    else snprintf(out, cap, "%s", base);
    size_t n = strlen(out);
    while (n && out[n - 1] == '\\') out[--n] = 0;
    return 1;
}

/* A key exists if it has an entry of its own or any key below it does. */
static int key_exists(const char *path) {
    size_t n = strlen(path);
    for (RegKey *k = keys; k; k = k->next)
        if (!strncasecmp(k->path, path, n) && (k->path[n] == 0 || k->path[n] == '\\')) return 1;
    for (size_t i = 0; i < RT_COUNTOF(root_names); i++)
        if (!strcasecmp(root_names[i], path)) return 1;
    return 0;
}

/* RegOpenKeyExA(key, subKey, options, access, &result) */
H(adv_RegOpenKeyExA) {
    UNUSED;
    char path[1024];
    uint32_t r = ERROR_FILE_NOT_FOUND;
    pthread_mutex_lock(&reg_mu);
    reg_load();
    if (!join_path(path, sizeof path, a[0], a[1])) {
        r = ERROR_INVALID_HANDLE;
    } else if (key_exists(path)) {
        uint32_t h = hkey_open(path);
        if (h) {
            st32(a[4], h);
            r = 0;
        }
    }
    pthread_mutex_unlock(&reg_mu);
    if (g_opt.verbose || g_trace_imports) rt_log("[reg] open %s -> %s\n", path, r ? "not found" : "ok");
    return r;
}

/* RegCreateKeyExA(key, subKey, reserved, class, options, access, security, &result, &disposition) */
H(adv_RegCreateKeyExA) {
    UNUSED;
    char path[1024];
    uint32_t r = ERROR_INVALID_HANDLE;
    pthread_mutex_lock(&reg_mu);
    reg_load();
    if (join_path(path, sizeof path, a[0], a[1])) {
        int existed = key_exists(path);
        key_create(path);
        uint32_t h = hkey_open(path);
        if (h) {
            st32(a[7], h);
            if (a[8]) st32(a[8], existed ? 2 : 1);
            if (!existed) reg_save();
            r = 0;
        }
    }
    pthread_mutex_unlock(&reg_mu);
    return r;
}

H(adv_RegCloseKey) {
    UNUSED;
    uint32_t i = a[0] - HKEY_OPEN_BASE;
    pthread_mutex_lock(&reg_mu);
    if (a[0] >= HKEY_OPEN_BASE && i < RT_COUNTOF(open_keys) && open_keys[i]) {
        free(open_keys[i]);
        open_keys[i] = NULL;
    }
    pthread_mutex_unlock(&reg_mu);
    return 0;
}

/* RegQueryValueExA(key, name, reserved, &type, data, &size) */
H(adv_RegQueryValueExA) {
    UNUSED;
    uint32_t r = ERROR_FILE_NOT_FOUND;
    const char *name = a[1] ? rt_gstr(a[1]) : "";
    pthread_mutex_lock(&reg_mu);
    reg_load();
    const char *path = hkey_path(a[0]);
    RegKey *k = path ? key_find(path) : NULL;
    RegValue *v = k ? value_find(k, name) : NULL;
    if (!path) {
        r = ERROR_INVALID_HANDLE;
    } else if (v) {
        if (a[3]) st32(a[3], v->type);
        r = 0;
        if (a[5]) {
            uint32_t cap = ld32(a[5]);
            st32(a[5], v->len);
            if (a[4]) {
                if (cap >= v->len) memcpy(G(a[4]), v->data, v->len);
                else r = ERROR_MORE_DATA;
            }
        }
    }
    if (g_opt.verbose || g_trace_imports)
        rt_log("[reg] query %s \"%s\" -> %s\n", path ? path : "?", name, r == 0 ? "ok" : r == ERROR_MORE_DATA ? "buffer too small" : "not found");
    pthread_mutex_unlock(&reg_mu);
    return r;
}

/* RegSetValueExA(key, name, reserved, type, data, size) */
H(adv_RegSetValueExA) {
    UNUSED;
    uint32_t r = ERROR_INVALID_HANDLE;
    pthread_mutex_lock(&reg_mu);
    reg_load();
    const char *path = hkey_path(a[0]);
    if (path) {
        uint32_t len = a[5];
        if (a[3] == REG_SZ && a[4]) {
            /* store exactly one terminator whatever length the caller counted */
            uint32_t n = 0;
            while (n < len && ld8(a[4] + n)) n++;
            char *tmp = malloc(n + 1);
            memcpy(tmp, G(a[4]), n);
            tmp[n] = 0;
            value_set(key_create(path), a[1] ? rt_gstr(a[1]) : "", REG_SZ, tmp, n + 1);
            free(tmp);
        } else {
            value_set(key_create(path), a[1] ? rt_gstr(a[1]) : "", a[3], G(a[4]), len);
        }
        reg_save();
        r = 0;
    }
    pthread_mutex_unlock(&reg_mu);
    return r;
}

H(adv_RegDeleteValueA) {
    UNUSED;
    uint32_t r = ERROR_FILE_NOT_FOUND;
    pthread_mutex_lock(&reg_mu);
    reg_load();
    const char *path = hkey_path(a[0]);
    RegKey *k = path ? key_find(path) : NULL;
    if (k) {
        for (RegValue **pp = &k->values; *pp; pp = &(*pp)->next) {
            if (!strcasecmp((*pp)->name, a[1] ? rt_gstr(a[1]) : "")) {
                RegValue *v = *pp;
                *pp = v->next;
                free(v->name);
                free(v->data);
                free(v);
                reg_save();
                r = 0;
                break;
            }
        }
    }
    pthread_mutex_unlock(&reg_mu);
    return r;
}

/* RegEnumKeyExA(key, index, name, &nameLen, reserved, class, &classLen, &lastWrite) */
H(adv_RegEnumKeyExA) {
    UNUSED;
    uint32_t r = ERROR_NO_MORE_ITEMS;
    pthread_mutex_lock(&reg_mu);
    reg_load();
    const char *path = hkey_path(a[0]);
    if (!path) {
        r = ERROR_INVALID_HANDLE;
    } else {
        size_t n = strlen(path);
        char seen[64][128];
        unsigned nseen = 0;
        for (RegKey *k = keys; k && r == ERROR_NO_MORE_ITEMS; k = k->next) {
            if (strncasecmp(k->path, path, n) || k->path[n] != '\\') continue;
            char child[128];
            snprintf(child, sizeof child, "%.*s", (int)strcspn(k->path + n + 1, "\\"), k->path + n + 1);
            unsigned i;
            for (i = 0; i < nseen; i++)
                if (!strcasecmp(seen[i], child)) break;
            if (i < nseen) continue;
            if (nseen == a[1]) {
                uint32_t cap = ld32(a[3]);
                if (strlen(child) + 1 > cap) {
                    r = ERROR_MORE_DATA;
                } else {
                    strcpy((char *)G(a[2]), child);
                    st32(a[3], (uint32_t)strlen(child));
                    if (a[6]) st32(a[6], 0);
                    if (a[5] && a[6]) st8(a[5], 0);
                    r = 0;
                }
                break;
            }
            if (nseen < 64) snprintf(seen[nseen++], 128, "%s", child);
        }
    }
    pthread_mutex_unlock(&reg_mu);
    return r;
}

static const ImportDef defs[] = {
    {"advapi32.dll", "RegOpenKeyExA", adv_RegOpenKeyExA, 5, 0},
    {"advapi32.dll", "RegCreateKeyExA", adv_RegCreateKeyExA, 9, 0},
    {"advapi32.dll", "RegCloseKey", adv_RegCloseKey, 1, 0},
    {"advapi32.dll", "RegQueryValueExA", adv_RegQueryValueExA, 6, 0},
    {"advapi32.dll", "RegSetValueExA", adv_RegSetValueExA, 6, 0},
    {"advapi32.dll", "RegDeleteValueA", adv_RegDeleteValueA, 2, 0},
    {"advapi32.dll", "RegEnumKeyExA", adv_RegEnumKeyExA, 8, 0},
};
RT_EXPORT_IMPORTS(rt_imports_registry, defs);
