/* GetByte - 0x4ea1b0 in the original binary.
 *
 * Same bit-buffer refill idiom as GetBit (see GetBit.c) - the original
 * binary has no separate FillBuf symbol, so FillBuf was apparently
 * inlined separately into both GetBit and GetByte by the compiler;
 * mirrored here as a local static rather than a shared third function
 * with no corresponding address. Returns a full byte from the
 * compressed stream, built from the top 8 bits of the bit-buffer.
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

int lzhuf_get_byte(lzhuf_state *s) {
    int b;
    fillbuf(s);
    b = (s->getbuf >> 8) & 0xff;
    s->getbuf = (s->getbuf << 8) & 0xffff;
    s->getlen -= 8;
    return b;
}
