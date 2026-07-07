/* Shared state struct and internal declarations for the LZHUF module.
 * Not part of the public API (see include/lzhuf.h for that) - mirrors
 * the original binary's per-call state struct, whose real field offsets
 * are documented in FILEFORMATS.md's LZHUF section (+0xece4 son[],
 * +0xde30/+0xde34 freq[]/prnt[], +0xd460 per-symbol frequency,
 * +0xf6b0/+0xf6b2 bit-buffer/bit-count, +0xf6b8/+0xf6c0/+0xf6c4
 * compressed-data cursor fields).
 */
#ifndef GB_LZHUF_INTERNAL_H
#define GB_LZHUF_INTERNAL_H

#include <stddef.h>
#include <stdint.h>

#define LZHUF_N 4096            /* ring buffer size */
#define LZHUF_F 60               /* max match length */
#define LZHUF_THRESHOLD 2
#define LZHUF_N_CHAR (256 - LZHUF_THRESHOLD + LZHUF_F)   /* 314 */
#define LZHUF_T (LZHUF_N_CHAR * 2 - 1)                   /* 627 */
#define LZHUF_R (LZHUF_T - 1)                            /* root node index, 626 */
#define LZHUF_MAX_FREQ 0x8000

typedef struct {
    const uint8_t *data;
    size_t data_len;
    size_t pos;
    uint32_t getbuf;
    uint32_t getlen;
    uint8_t text_buf[LZHUF_N + LZHUF_F - 1];
    int r;
    uint16_t freq[LZHUF_T + 1];
    int prnt[LZHUF_T + LZHUF_N_CHAR];
    int son[LZHUF_T];
} lzhuf_state;

/* GetBit/GetByte - 0x4ea120/0x4ea1b0 in the original binary. */
int lzhuf_get_bit(lzhuf_state *s);
int lzhuf_get_byte(lzhuf_state *s);

/* InitLZHUFTree - 0x4ea300. */
void lzhuf_init_tree(lzhuf_state *s);

/* Reconst - 0x4ea3b0. */
void lzhuf_reconst(lzhuf_state *s);

/* Update - 0x4ea580. */
void lzhuf_update(lzhuf_state *s, int c);

/* DecodeChar - 0x4ea670. */
int lzhuf_decode_char(lzhuf_state *s);

/* DecodePosition - 0x4ea6e0. Uses the static d_code/d_len tables
 * defined in lzhuf_tables.c (DAT_0056dd30/DAT_0056de30 in the
 * original binary). */
int lzhuf_decode_position(lzhuf_state *s);
extern const uint8_t lzhuf_d_code[256];
extern const uint8_t lzhuf_d_len[256];

/* DecodeLZHUFBlock - 0x4eaba0. */
void lzhuf_decode_block(lzhuf_state *s, uint8_t *out, size_t outsize);

#endif
