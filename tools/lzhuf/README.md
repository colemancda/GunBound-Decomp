# LZHUF decoder — working

Python port of the classic Okumura/Yoshizaki LZHUF algorithm, adapted to
decode GunBound's `.xfs`/`.dat` LZHUF blocks. See
[FILEFORMATS.md](../../FILEFORMATS.md) for the full algorithm confirmation
and validation notes.

## Status: fixed and verified against real game files

The long-standing decode bug (see
[`BUG_FOUND_wrong_decode_tables.md`](BUG_FOUND_wrong_decode_tables.md) for
the full writeup) was the `DecodePosition()` lookup table: what this repo
had as `p_code`/`p_len` was not the real decode-side `d_code`/`d_len` table
from the reference `LZHUF.C` — it was some other (incorrect) monotonic
table, wrong in *content* even though it happened to be the right size
(256 entries), which is why the bug survived cross-checking against an
independent C port that made the exact same transcription mistake. A wrong
position table only breaks back-reference (`DecodePosition`) decoding, not
literal-byte decoding — which is exactly why the tiny 64-byte TOC header
(mostly unique bytes, few back-references) decoded perfectly while real
archive entries (which compress well precisely *because* of repeated
back-references) desynced almost immediately.

**Verified end-to-end against all three real `.xfs` files in `orig/`:**
- `graphics.xfs` — all 9,313 entries decode cleanly, every chunk, no
  degradation. `ChooseEvent.txt` extracted and reads as a simple event-mode
  selector list: `0=off, 1=christmas, 2=event2, 3=event3` (resolves the
  field-semantics gap in [FILEFORMATS.md](../../FILEFORMATS.md)).
- `sound.xfs` — all 96 entries decode cleanly (stored with mode flag `1`,
  i.e. raw/uncompressed — consistent with `.xes` audio files already being
  compressed in their own format).
- `avatar.xfs` — all 8 entries decode cleanly: `fb.dat`/`ff.dat`/`fg.dat`/
  `fh.dat`/`mb.dat`/`mf.dat`/`mg.dat`/`mh.dat` — confirms the
  `f`/`m`-prefixed per-gender file naming guessed at in `STRINGS.md`.

- `lzhuf.py` — the decoder, now fixed (this is the corrected version;
  `lzhuf_buggy_original.py.bak` preserves the original broken tables for
  reference/history).
- `extract_toc.py` — parses a `.xfs` file's footer/TOC/entry records using
  `lzhuf.py`. Works correctly end-to-end now.
- `lzhuf_ref.c` — the independent C port used during debugging. **Still
  has the same wrong tables as the original bug** (not yet fixed) — kept
  as-is for historical reference; don't trust its output. Use `lzhuf.py`.

## Usage

```
python3 extract_toc.py /path/to/graphics.xfs
```

Each entry is `(name, mode_flag, file_offset, decompressed_size, compressed_size)`.
To extract a specific entry's raw decompressed bytes:

```python
import struct
from lzhuf import decode_lzhuf

with open(path, 'rb') as f:
    f.seek(file_offset)
    compressed_size, checksum = struct.unpack('<II', f.read(8))  # only if mode_flag != 1
    data = f.read(compressed_size)
    out = decode_lzhuf(data, decompressed_size)
```

(If `mode_flag == 1`, the entry is stored raw — just `f.seek(file_offset)`
and read `decompressed_size` bytes directly, no LZHUF decode needed.)
