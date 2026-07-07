/* GetBit - 0x4ea120 in the original binary.
 *
 * Refills the 16-bit bit-buffer (getbuf/getlen, +0xf6b0/+0xf6b2 in the
 * original state struct) whenever fewer than 9 bits remain - confirmed
 * against the decompiled binary to refill at that fixed threshold
 * rather than "as many bits as the caller needs right now". Returns the
 * next single bit from the compressed stream, MSB-first.
 */
#include "lzhuf_internal.h"

static void fillbuf(lzhuf_state *s) {
    while (s->getlen < 9) {
        uint8_t c = (s->pos < s->data_len) ? s->data[s->pos] : 0;
        s->pos++;
        s->getbuf |= (uint32_t)c << (8 - s->getlen);
        s->getlen += 8;
    }
}

int lzhuf_get_bit(lzhuf_state *s) {
    int b;
    fillbuf(s);
    b = (s->getbuf >> 15) & 1;
    s->getbuf = (s->getbuf << 1) & 0xffff;
    s->getlen -= 1;
    return b;
}
