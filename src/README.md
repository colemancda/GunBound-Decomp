# Reconstructed C source — status

## Scope: behavioral parity, not byte-matching

The original plan for this repo was **matching decompilation**: write C
that recompiles under period-correct MSVC 7.10 (Visual Studio .NET 2003)
to byte-identical machine code, verified function-by-function against
`orig/GunBound.gme`. That toolchain isn't available in this environment —
it's proprietary, not legally redistributable, and no install media was
on hand.

Instead, the plan is **Winelib**: build the reconstructed C as a native
macOS binary using Wine's Win32-API-compatible headers/libraries
(`winegcc`), so real DirectDraw/Direct3D7/DirectSound/DirectInput/Winsock
calls can actually run, without needing an actual Windows machine or
MSVC. This still isn't byte-matching (Winelib compiles with a modern
GCC/Clang, not MSVC 7.10), so it's **behavioral parity**: C that does the
same thing as the original function, verified by running it against real
game data/behavior and diffing the output — not by comparing compiled
bytes against the original binary. `PROGRESS.csv` marks functions done
this way as `PARITY-<file>` rather than the matching-decomp convention's
`DONE`, to keep the two kinds of "verified" distinguishable. (The
`tools/msvc-env/` Wine+Docker scaffold for a *true* byte-matching pipeline
is still there and still works if a real VS .NET 2003 tree ever turns up
— see that directory's Dockerfile.)

## Layout: one file per decompiled function

Each original function gets its own file, named after its confirmed name
(or `FUN_<address>` if unnamed), with a header comment giving its
original address and a short description of what it does — mirroring
the convention used by community matching-decomp projects. Shared
per-module state (structs, internal-only declarations) lives in a
`<module>_internal.h` header; a `<module>_api.c` wraps the decompiled
functions in a normal malloc/free-based public API when the original
callers managed state/output buffers inline themselves (as LZHUF's do)
rather than through one clean entry point.

## What's here

- **`lzhuf/`** — the LZHUF decompressor used throughout `.xfs`/`.dat`
  decoding, split into one file per original function:
  - `GetBit.c` / `GetByte.c` — `0x4ea120` / `0x4ea1b0`, the bitstream reader.
  - `InitLZHUFTree.c` — `0x4ea300`, tree/ring-buffer setup.
  - `Reconst.c` — `0x4ea3b0`, periodic full tree rebuild.
  - `Update.c` — `0x4ea580`, adaptive frequency promotion.
  - `DecodeChar.c` — `0x4ea670`, Huffman tree walk for literals/lengths.
  - `DecodePosition.c` — `0x4ea6e0`, back-reference distance decode.
  - `DecodeLZHUFBlock.c` — `0x4eaba0`, the main LZSS unpacking loop.
  - `lzhuf_tables.c` — the static `d_code`/`d_len` decode tables
    (`DAT_0056dd30`/`DAT_0056de30`), not a function but data the above
    depend on.
  - `lzhuf_internal.h` — shared state struct + internal declarations.
  - `lzhuf_api.c` — public malloc/free-based wrapper (see `include/lzhuf.h`).

  All of the above ported from the already-validated Python reference
  (`tools/lzhuf/lzhuf.py`), itself derived from decompiling the real
  functions and fixing a transcription bug found along the way (see
  `tools/lzhuf/BUG_FOUND_wrong_decode_tables.md`). Verified byte-for-byte
  against the Python decoder on three real archive entries pulled
  straight from `orig/graphics.xfs` (`ChooseEvent.txt`, `bullet1n.img`,
  `avataimsi.img`).
- **`test_lzhuf.c`** — standalone CLI test driver, not part of the
  eventual game build; exists purely to validate `lzhuf_decode()` against
  real data without needing the rest of the game to compile.
- **`main.c`** — `WinMain` (`0x40d8e0`) skeleton. Wires up the real
  top-level control flow documented in ARCHITECTURE.md's "Entry point
  and top-level flow" section (window creation, `WSAStartup`, the
  `PeekMessage`-idle-calls-`GameTick` message loop) with stub bodies for
  `WndProc`/`InitGame`/`GameTick`/`Shutdown` — none of those four are
  ported yet, each is a substantial function that belongs in its own
  file (matching the one-file-per-function convention) once tackled.
  **Requires Winelib to build** — real Win32 API surface, not a
  dependency-free algorithm like `lzhuf/`.

## Building and testing

```
make            # native build of src/lzhuf/ only -> build/test_lzhuf
make winelib    # full Winelib build including main.c -> build/gunbound.exe
                # (needs `winegcc` on PATH - see "Wine setup" below)
```

To verify `lzhuf_decode()` against real archive data, first extract a
compressed blob and its known-good decoded reference with the Python
tooling, then diff:

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

## Wine setup

**Real macOS-native Winelib** needs `winegcc`, which isn't available
prebuilt anywhere for macOS (Homebrew's `wine-stable`/`wine@devel` casks
are runtime-only — they ship `wine` but no dev toolchain/headers).
Getting a native `winegcc` means building Wine from source, which hasn't
been attempted (multi-hour build, large dependency chain).

**Working now: `tools/winelib-env/`, a Docker image with a real
`winegcc`** (Debian's `wine64-tools`/`wine64` packages), used as a
stand-in until a native macOS toolchain exists. Caveat: `winegcc` always
targets whatever platform it runs on, so a binary built this way is a
**Linux ELF Winelib binary** — it validates that the code actually
compiles/links against real Win32/DirectX/Winsock declarations (real
progress), but it isn't the eventual native-macOS-binary goal, and it
can only be *run* inside a full Wine environment (not attempted beyond a
basic linkage smoke-test — a headless container has no display, which
`main.c`'s window creation and any eventual DirectDraw code will need
anyway, so there's little to gain from chasing full execution here).

```
docker build --platform linux/amd64 -t gb-winelib tools/winelib-env
docker run --rm --platform linux/amd64 -v "$PWD":/work -w /work gb-winelib \
    make winelib WINEGCC=winegcc-stable
```

produces `build/gunbound.exe` / `build/gunbound.exe.so`. `winegcc` in
this image is only on `PATH` as `winegcc-stable`, hence the explicit
`WINEGCC=` override — pass the same to any other winegcc-family tool
(`wineg++-stable`, `widl-stable`, etc.) if needed later. Also note
`-std=gnu11`, not `c11`: Wine's `winsock.h` expects glibc's BSD typedefs
(`u_short`/`u_int`), which strict C11 mode hides.

## Picking the next function to port

Good next candidates are self-contained algorithms already fully
understood and documented, with no Windows/DirectX/Winsock dependency —
same reasoning that made LZHUF a good first target, buildable/testable
with the native `make` target before Winelib is even needed:

- The `.xfs`/`.dat` checksum routine (`tools/lzhuf/verify_checksum.py`
  has the reference; simple additive checksum, no external deps).
- `BlitSprite16bpp`'s sparse-row pixel decoder (documented in full in
  `FILEFORMATS.md`'s `.img` section, already has a Python reference in
  `tools/lzhuf/decode_img.py`).

Once Winelib is confirmed working, `WndProc`/`InitGame`/`GameTick` (all
stubbed in `main.c`) are the natural next layer — real Win32/DirectX
surface, one file each per the established convention.
