# Reconstructed C source — status

## Scope: behavioral parity, not byte-matching

The original plan for this repo was **matching decompilation**: write C
that recompiles under period-correct MSVC 7.10 (Visual Studio .NET 2003)
to byte-identical machine code, verified function-by-function against
`orig/GunBound.gme`. That toolchain isn't available in this environment —
it's proprietary, not legally redistributable, and no install media was
on hand. Bringing it up (e.g. via `tools/msvc-env/`'s Wine/Docker
scaffold) needs a supplied Visual Studio .NET 2003 tree; see that
directory's Dockerfile for what's expected.

Given that blocker, this directory instead targets **behavioral parity**:
C that does the same thing as the original function, compiled with a
modern toolchain (currently just system `clang`/`cc`, no Windows
dependency yet), verified by running it against real game data and
diffing the output — not by comparing compiled bytes against the
original binary. `PROGRESS.csv` marks functions done this way as
`PARITY-<file>` rather than the matching-decomp convention's `DONE`, to
keep the two kinds of "verified" distinguishable.

## What's here

- **`lzhuf.c`** / **`include/lzhuf.h`** — the LZHUF decompressor used
  throughout `.xfs`/`.dat` decoding (`DecodeLZHUFBlock`, `0x4eaba0`).
  Ported from the already-validated Python reference
  (`tools/lzhuf/lzhuf.py`), which was itself derived from decompiling the
  real function and fixing a transcription bug found along the way (see
  `tools/lzhuf/BUG_FOUND_wrong_decode_tables.md`). Verified byte-for-byte
  against the Python decoder on three real archive entries pulled
  straight from `orig/graphics.xfs` (`ChooseEvent.txt`, `bullet1n.img`,
  `avataimsi.img`) — see `test_lzhuf.c`.
- **`test_lzhuf.c`** — standalone CLI test driver, not part of the
  eventual game build; exists purely to validate `lzhuf_decode()` against
  real data without needing the rest of the game to compile.

## Building and testing

```
make                    # builds build/test_lzhuf
```

To verify against real archive data, first extract a compressed blob and
its known-good decoded reference with the Python tooling, then diff:

```python
# from tools/lzhuf/
from extract_toc import read_toc
from lzhuf import decode_lzhuf
import struct

entries, *_ = read_toc('../../orig/graphics.xfs')
name, mode_flag, file_offset, decompressed_size, compressed_size = \
    next(e for e in entries if e[0] == 'bullet1n.img')
with open('../../orig/graphics.xfs', 'rb') as f:
    f.seek(file_offset)
    real_compressed_size, checksum = struct.unpack('<II', f.read(8))
    cdata = f.read(real_compressed_size)
open('/tmp/in.bin', 'wb').write(cdata)
open('/tmp/ref.bin', 'wb').write(decode_lzhuf(cdata, decompressed_size))
```

```
build/test_lzhuf /tmp/in.bin /tmp/out.bin 3472   # decompressed_size from above
diff /tmp/ref.bin /tmp/out.bin && echo MATCH
```

## Picking the next function to port

Good next candidates are self-contained algorithms already fully
understood and documented, with no Windows/DirectX/Winsock dependency —
same reasoning that made LZHUF a good first target:

- The `.xfs`/`.dat` checksum routine (`tools/lzhuf/verify_checksum.py`
  has the reference; simple additive checksum, no external deps).
- `BlitSprite16bpp`'s sparse-row pixel decoder (documented in full in
  `FILEFORMATS.md`'s `.img` section, already has a Python reference in
  `tools/lzhuf/decode_img.py`).

Anything touching `IDirectDraw7`/`IDirect3DDevice7`/Winsock will need a
real Windows target (cross-compiled via mingw-w64, or run under Wine) or
a compatibility shim before it can be built and tested the same way —
not attempted yet.
