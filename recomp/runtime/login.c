/* --login USER PASSWORD: the session token the game expects as its command line.
 *
 * The game's launcher encrypts three 16-byte blocks with AES-128 (ECB): the
 * user name, the password and zeros, each padded with zeros, and passes the 96
 * hexadecimal digits. The key is not stored here: it is read from the
 * launcher's source (`byte[] key = { 0x.., ... }`) or from a file holding its
 * 32 hexadecimal digits. This is tools/make_token.py for machines without
 * Python. */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rt.h"

static uint8_t sbox[256];

static uint8_t xtime(uint8_t x) { return (uint8_t)((x << 1) ^ ((x >> 7) * 0x1B)); }

static void sbox_init(void) {
    /* multiplicative inverses in GF(2^8) through powers of the generator 3, then the affine map */
    uint8_t p = 1, q = 1;
    do {
        p = (uint8_t)(p ^ xtime(p));
        q ^= (uint8_t)(q << 1);
        q ^= (uint8_t)(q << 2);
        q ^= (uint8_t)(q << 4);
        if (q & 0x80) q ^= 0x09;
        uint8_t x = (uint8_t)(q ^ (q << 1 | q >> 7) ^ (q << 2 | q >> 6) ^ (q << 3 | q >> 5) ^ (q << 4 | q >> 4));
        sbox[p] = x ^ 0x63;
    } while (p != 1);
    sbox[0] = 0x63;
}

static void aes128_encrypt(const uint8_t key[16], const uint8_t in[16], uint8_t out[16]) {
    uint8_t rk[176], s[16], t[16];
    if (!sbox[0]) sbox_init();
    memcpy(rk, key, 16);
    uint8_t rcon = 1;
    for (int i = 16; i < 176; i += 4) {
        uint8_t w[4] = {rk[i - 4], rk[i - 3], rk[i - 2], rk[i - 1]};
        if (i % 16 == 0) {
            uint8_t w0 = w[0];
            w[0] = sbox[w[1]] ^ rcon;
            w[1] = sbox[w[2]];
            w[2] = sbox[w[3]];
            w[3] = sbox[w0];
            rcon = xtime(rcon);
        }
        for (int k = 0; k < 4; k++) rk[i + k] = rk[i - 16 + k] ^ w[k];
    }
    for (int i = 0; i < 16; i++) s[i] = in[i] ^ rk[i];
    for (int round = 1; round <= 10; round++) {
        for (int i = 0; i < 16; i++) t[i] = sbox[s[(i + 4 * (i & 3)) & 15]]; /* SubBytes and ShiftRows */
        if (round < 10) {
            for (int col = 0; col < 16; col += 4) {
                uint8_t a0 = t[col], a1 = t[col + 1], a2 = t[col + 2], a3 = t[col + 3], x = a0 ^ a1 ^ a2 ^ a3;
                s[col] = a0 ^ x ^ xtime(a0 ^ a1);
                s[col + 1] = a1 ^ x ^ xtime(a1 ^ a2);
                s[col + 2] = a2 ^ x ^ xtime(a2 ^ a3);
                s[col + 3] = a3 ^ x ^ xtime(a3 ^ a0);
            }
        } else {
            memcpy(s, t, 16);
        }
        for (int i = 0; i < 16; i++) s[i] ^= rk[16 * round + i];
    }
    memcpy(out, s, 16);
}

/* The key from a launcher source file or from a file of 32 hexadecimal digits. */
static int read_key(const char *path, uint8_t key[16]) {
    FILE *f = fopen(path, "rb");
    if (!f) return 0;
    static char text[1 << 18];
    size_t n = fread(text, 1, sizeof text - 1, f);
    fclose(f);
    text[n] = 0;
    int got = 0;
    const char *p = text;
    /* `byte[] key = { 0x.., ... }` */
    for (const char *q = text; (q = strstr(q, "byte[]")) != NULL; q += 6) {
        const char *r = q + 6 + strspn(q + 6, " \t");
        if (strncmp(r, "key", 3) != 0) continue;
        r += 3 + strspn(r + 3, " \t=");
        if (*r != '{') continue;
        const char *end = strchr(r, '}');
        for (r++; end && r < end && got < 17; r++) {
            if (r[0] == '0' && (r[1] == 'x' || r[1] == 'X')) {
                if (got < 16) key[got] = (uint8_t)strtoul(r + 2, NULL, 16);
                got++;
                r++;
            }
        }
        return got == 16;
    }
    /* otherwise: nothing but 32 hexadecimal digits and white space */
    for (; *p; p++) {
        if (isspace((unsigned char)*p)) continue;
        if (!isxdigit((unsigned char)p[0]) || !isxdigit((unsigned char)p[1]) || got == 16) return 0;
        char b[3] = {p[0], p[1], 0};
        key[got++] = (uint8_t)strtoul(b, NULL, 16);
        p++;
    }
    return got == 16;
}

int rt_login_token(const char *user, const char *password, const char *key_file, char token[97]) {
    uint8_t key[16];
    char tried[1400] = "";
    int ok = 0;
    if (key_file && key_file[0]) {
        ok = read_key(key_file, key);
        snprintf(tried, sizeof tried, "%s", key_file);
    } else {
        /* next to the game's files, then next to the executable */
        static const char *const names[] = {"Launcher.cs", "launcher.key"};
        const char *dirs[3] = {g_opt.gamedir, g_opt.savedir, g_opt.exedir};
        for (int d = 0; d < 3 && !ok; d++) {
            for (int k = 0; k < 2 && !ok; k++) {
                char path[700];
                if (!dirs[d][0]) continue;
                snprintf(path, sizeof path, "%.600s/%s", dirs[d], names[k]);
                ok = read_key(path, key);
                size_t n = strlen(tried);
                if (n < sizeof tried - 720) snprintf(tried + n, sizeof tried - n, "%s%s", n ? ", " : "", path);
            }
        }
    }
    if (!ok) {
        fprintf(stderr,
                "recomp: --login: no key found (tried %s).\n"
                "        The key is in the launcher's source, Launcher.cs, as `byte[] key = { 0x.., ... }`;\n"
                "        put that file (or launcher.key, its 32 hexadecimal digits) in the game directory,\n"
                "        or name it with --login-key FILE, or pass a ready token with --cmdline.\n", tried);
        return 0;
    }
    if (strlen(user) > 16 || strlen(password) > 16 || !user[0]) {
        fprintf(stderr, "recomp: --login: the user name and the password are at most 16 characters\n");
        return 0;
    }
    uint8_t blocks[3][16], out[16];
    memset(blocks, 0, sizeof blocks);
    memcpy(blocks[0], user, strlen(user));
    memcpy(blocks[1], password, strlen(password));
    for (int b = 0; b < 3; b++) {
        aes128_encrypt(key, blocks[b], out);
        for (int i = 0; i < 16; i++) sprintf(token + 32 * b + 2 * i, "%02X", out[i]);
    }
    return 1;
}
