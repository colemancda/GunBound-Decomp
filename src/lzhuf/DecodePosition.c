/* DecodePosition - 0x4ea6e0 in the original binary.
 *
 * Reads an 8-bit code via GetByte(), looks up its high bits through
 * the static d_code/d_len tables (DAT_0056dd30/DAT_0056de30 in the
 * original binary - see lzhuf_tables.c), then reads d_len[i]-2 more
 * raw bits one at a time via GetBit() for the low bits of the
 * back-reference distance.
 */
#include "lzhuf_internal.h"

int lzhuf_decode_position(lzhuf_state *s) {
    int i = lzhuf_get_byte(s);
    int c = lzhuf_d_code[i] << 6;
    int j = lzhuf_d_len[i] - 2;
    while (j > 0) {
        i = (i << 1) + lzhuf_get_bit(s);
        j--;
    }
    return c | (i & 0x3f);
}
