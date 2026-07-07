/* DecodeLZHUFBlock - 0x4eaba0 in the original binary.
 *
 * The main LZSS unpacking loop, driving the Huffman primitives above:
 * each iteration decodes one symbol via DecodeChar(). Symbols < 256
 * are literal bytes, emitted directly and written into the ring
 * buffer. Symbols >= 256 are back-reference runs: DecodePosition()
 * gives the distance back into the ring buffer, and
 * (symbol - 255 + THRESHOLD) gives the run length. Both paths write
 * through the same ring buffer (text_buf) so later back-references can
 * see earlier-copied bytes, matching the reference Decode() loop.
 *
 * This is the function documented in FILEFORMATS.md as shared by both
 * the .xfs table-of-contents decoder and every individual archive
 * entry/`.dat` file - only the requested output size differs per call.
 *
 * lzhuf_decode() (see include/lzhuf.h) is this function's public
 * wrapper: it owns state-struct allocation/init (InitLZHUFTree) and
 * output-buffer allocation, which in the original binary are the
 * caller's responsibility rather than DecodeLZHUFBlock's own - kept
 * separate here for the same reason.
 */
#include "lzhuf_internal.h"

void lzhuf_decode_block(lzhuf_state *s, uint8_t *out, size_t outsize) {
    size_t count = 0;
    int r = s->r;
    while (count < outsize) {
        int c = lzhuf_decode_char(s);
        if (c < 256) {
            out[count++] = (uint8_t)c;
            s->text_buf[r] = (uint8_t)c;
            r = (r + 1) % LZHUF_N;
        } else {
            int i = (r - lzhuf_decode_position(s) - 1 + LZHUF_N) % LZHUF_N;
            int j = c - 255 + LZHUF_THRESHOLD;
            int n;
            for (n = 0; n < j; n++) {
                uint8_t cc;
                if (count >= outsize) {
                    break;
                }
                cc = s->text_buf[i % LZHUF_N];
                out[count++] = cc;
                s->text_buf[r] = cc;
                r = (r + 1) % LZHUF_N;
                i++;
            }
        }
    }
    s->r = r;
}
