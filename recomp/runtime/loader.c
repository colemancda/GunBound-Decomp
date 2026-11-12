/* PE32 loader: maps the image into guest memory and points the IAT at fake import addresses. */
#include <stdio.h>
#include <stdlib.h>

#include "rt.h"

RtImage g_image;

static uint16_t f16(const uint8_t *p) { return (uint16_t)(p[0] | (p[1] << 8)); }
static uint32_t f32(const uint8_t *p) { return p[0] | (p[1] << 8) | (p[2] << 16) | ((uint32_t)p[3] << 24); }

/* CRC-32 (IEEE, same polynomial as zlib) of the code section, to match the lifter's stamp. */
static uint32_t crc32_ieee(const uint8_t *p, size_t n) {
    static uint32_t table[256];
    if (!table[1]) {
        for (uint32_t i = 0; i < 256; i++) {
            uint32_t c = i;
            for (int k = 0; k < 8; k++) c = (c & 1) ? 0xEDB88320u ^ (c >> 1) : c >> 1;
            table[i] = c;
        }
    }
    uint32_t c = 0xFFFFFFFFu;
    while (n--) c = table[(c ^ *p++) & 0xFF] ^ (c >> 8);
    return ~c;
}

static void die(const char *msg, const char *path) {
    fprintf(stderr, "recomp: %s: %s\n", path, msg);
    exit(2);
}

void rt_load_pe(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        perror(path);
        fprintf(stderr, "recomp: pass the game executable with --exe PATH (or RECOMP_EXE)\n");
        exit(2);
    }
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *file = malloc((size_t)fsize);
    if (!file || fread(file, 1, (size_t)fsize, f) != (size_t)fsize) die("read error", path);
    fclose(f);

    if (fsize < 0x200 || f16(file) != 0x5A4D) die("not an MZ executable", path);
    uint32_t pe = f32(file + 0x3C);
    if (pe + 0x108 > (uint32_t)fsize || f32(file + pe) != 0x4550) die("not a PE executable", path);
    const uint8_t *fh = file + pe + 4;
    const uint8_t *oh = fh + 20;
    if (f16(fh) != 0x14C || f16(oh) != 0x10B) die("not a 32-bit x86 PE32 image", path);
    unsigned nsect = f16(fh + 2);
    unsigned ohsize = f16(fh + 16);

    g_image.entry = f32(oh + 28) + f32(oh + 16);
    g_image.base = f32(oh + 28);
    g_image.size = f32(oh + 56);
    g_image.headers_size = f32(oh + 60);
    g_image.stack_reserve = f32(oh + 72);
    snprintf(g_image.path, sizeof g_image.path, "%s", path);

    if (g_image.base < GUEST_STACK_TOP || (uint64_t)g_image.base + g_image.size > GUEST_HEAP_BASE)
        die("image does not fit the guest layout (base/size)", path);
    if (g_image.entry != rt_entry)
        die("entry point differs from the lifted code: this is not the executable that was lifted", path);

    rt_mem_commit(g_image.base, g_image.size);
    uint32_t hs = g_image.headers_size < (uint32_t)fsize ? g_image.headers_size : (uint32_t)fsize;
    memcpy(G(g_image.base), file, hs);

    const uint8_t *sh = oh + ohsize;
    for (unsigned i = 0; i < nsect; i++, sh += 40) {
        uint32_t vsize = f32(sh + 8), va = f32(sh + 12), rawsize = f32(sh + 16), raw = f32(sh + 20);
        uint32_t n = rawsize < vsize || vsize == 0 ? rawsize : vsize;
        if (raw >= (uint32_t)fsize) continue;
        if (raw + n > (uint32_t)fsize) n = (uint32_t)fsize - raw;
        if ((uint64_t)va + n > g_image.size) die("section outside image", path);
        memcpy(G(g_image.base + va), file + raw, n);
    }

    uint32_t crc = crc32_ieee(G(rt_text_base), rt_text_size);
    if (crc != rt_text_crc)
        die("code section differs from the lifted code: this is not the executable that was lifted", path);

    /* Imports: one fake address per IAT slot. */
    uint32_t imp_rva = f32(oh + 96 + 8);
    if (imp_rva) {
        for (uint32_t d = g_image.base + imp_rva;; d += 20) {
            uint32_t oft = ld32(d), name_rva = ld32(d + 12), ft = ld32(d + 16);
            if (!name_rva && !ft) break;
            const char *dll = (const char *)G(g_image.base + name_rva);
            uint32_t lookup = oft ? oft : ft;
            for (uint32_t i = 0;; i++) {
                uint32_t t = ld32(g_image.base + lookup + 4 * i);
                if (!t) break;
                char ordname[32];
                const char *name;
                if (t & 0x80000000u) {
                    snprintf(ordname, sizeof ordname, "#%u", t & 0xFFFF);
                    name = ordname;
                } else {
                    name = (const char *)G(g_image.base + t + 2);
                }
                uint32_t slot = g_image.base + ft + 4 * i;
                st32(slot, rt_register_import(dll, name, slot));
            }
        }
    }
    free(file);
}
