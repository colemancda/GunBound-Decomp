/* DecodeChar - 0x4ea670 in the original binary.
 *
 * Walks the Huffman tree from the root (son[R]) down through the
 * son[]-style child-index array, reading one bit per level via
 * GetBit() to choose left/right, until it reaches a leaf (index < T).
 * Converts the leaf index back to a symbol value and feeds it to
 * Update() to keep the adaptive tree current.
 */
#include "lzhuf_internal.h"

int lzhuf_decode_char(lzhuf_state *s) {
    int c = s->son[LZHUF_R];
    while (c < LZHUF_T) {
        c += lzhuf_get_bit(s);
        c = s->son[c];
    }
    c -= LZHUF_T;
    lzhuf_update(s, c);
    return c;
}
