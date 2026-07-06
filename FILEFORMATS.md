# GunBound Custom File Formats — Reverse-Engineered Reference

Findings from decompiling the asset-loading code path (`LoadGameDataFiles`,
`OpenXFSArchive`, and the LZHUF decode routines). Complements
[ARCHITECTURE.md](ARCHITECTURE.md) and [PROTOCOL.md](PROTOCOL.md).

## Summary table

| Extension | Container | Compression | Confirmed? |
|---|---|---|---|
| `.xfs` (`graphics.xfs`, `sound.xfs`, `Avatar.xfs`) | Custom named-entry archive, magic `XFS2` | LZHUF (LZ77 + adaptive Huffman) for the table of contents; entries likely compressed too | Container format and TOC compression confirmed; per-entry compression not individually verified |
| `.dat` (`characterdata.dat`, `itemdata.dat`, `stage.dat`, `specialdata.dat`) | Flat file, no container | **LZHUF-compressed**, same decoder as XFS TOC | Confirmed for `characterdata.dat`/`itemdata.dat`/`stage.dat` |
| `.img` (sprite/texture files, e.g. `tank1.img`, `bullet1n.img`) | Individual asset, likely stored inside the `.xfs` archives | RLE (run-length encoding), 16bpp pixel data | Confirmed via `BlitRLESprite`/`BlitSprite16bpp` |
| `.sv` (replay files) | Custom event-stream format | Not compressed (not confirmed either way) | Event-code structure confirmed; file header not decoded |
| `ChooseEvent.txt` | Plain text, lives *inside* `graphics.xfs` | None (plain text) | Confirmed, parser fully read |

## The `.xfs` archive format — confirmed structure

Discovered via `OpenXFSArchive` (`0x4f0a50`, was `FUN_004f0a50`):

1. **Magic**: first 4 bytes of the decoded header equal `0x4658`/`0x3253`
   (two little-endian shorts) — read together as ASCII this is **`"XFS2"`**.
   Confirms a custom, versioned container format (version 2).
2. **Footer-based table of contents** (ZIP-like, not header-based): the
   loader seeks to **4 bytes before EOF** and reads a `DWORD` — this is an
   **offset back into the file** where the TOC begins. It seeks there, reads
   another `DWORD` (TOC compressed size), then reads that many bytes into a
   256 KB stack buffer.
3. **The TOC blob is LZHUF-compressed** (see below) and decoded via
   `DecodeLZHUFBlock` (`0x4eaba0`) with the decoded output re-validated
   against the `XFS2` magic — i.e. decompression success is checked by
   re-reading the magic from the decompressed output, not a separate
   checksum field.
4. After the initial TOC chunk, the loader **loops reading additional 4-byte
   length-prefixed chunks**, each triggering a further `operator_new(0x20000)`
   (128 KB) allocation — consistent with the TOC being split across multiple
   compressed blocks/directories rather than one monolithic index.
5. Named-entry lookup: `FindXFSEntry(handle, "ChooseEvent.txt")` (`0x4f1110`,
   was `FUN_004f1110`) resolves a filename to an internal entry handle;
   `ReadXFSEntry`/`ReadXFSEntryByte` (`0x4f0380`/`0x4f06c0`) then stream the
   entry's (decompressed) content out either as a bulk read or byte-by-byte
   — the byte-by-byte variant is used for text parsing (see `ChooseEvent.txt`
   below), the bulk variant for binary assets like sprites.

**Not yet confirmed**: whether individual archive *entries* (as opposed to
the TOC) are also LZHUF-compressed, or stored raw/RLE — the `.img` sprite
format is confirmed RLE-compressed at the pixel level (see below), which may
be applied on top of, instead of, or independent from any LZHUF layer at the
archive-entry level. Not disambiguated from static analysis alone.

## The LZHUF compression scheme

`DecodeLZHUFBlock` (`0x4eaba0`) and its tree-initialization helper
`InitLZHUFTree` (`0x4ea300`) implement what is, with reasonably high
confidence based on the structural signature, a classic **LZHUF** codec
(LZ77 sliding-window matching combined with adaptive/dynamic Huffman coding
of the literal/length alphabet) — a very common "roll your own compression"
choice for Korean-origin games and tools of this era (the algorithm
originates from a widely-shared public-domain reference implementation).
Evidence:

- `InitLZHUFTree` builds a binary tree structure using paired
  father/child-index arrays, initialized with constants matching classic
  LZHUF parameters (a `0x13a` = 314 entry count, matching the typical
  `N_CHAR` alphabet size used in reference LZHUF implementations: 256
  literal byte values plus length-code symbols).
- Both the XFS table-of-contents and the `.dat` data files are decoded
  through this **exact same function**, just called with different
  size/key parameters (`0x40` for the XFS TOC vs. `0x14c0` for
  `characterdata.dat`) — confirming one shared compression scheme reused
  across both container types, not two different schemes.

This has not been fully reverse-engineered into a standalone decoder/encoder
(that would be a substantial follow-up project — implementing the exact
Huffman table update rule and LZ window parameters precisely enough to
decode real files) — this pass confirms *which* algorithm family it is and
exactly where it's invoked, not a byte-exact reimplementation.

## `.dat` files — confirmed structure, corrects an earlier assumption

**Correction**: earlier analysis (before this file-format pass) assumed the
`.dat` files were plain, directly-parseable data based on their extension
and the fact they're loaded via plain `fopen`/`fread`. **They are not
plain** — `fopen`/`fread` only reads the *raw compressed bytes* into memory;
the actual record data only exists after passing through
`DecodeLZHUFBlock`. Confirmed for all three files loaded by
`LoadGameDataFiles` (`0x419d90`, was `FUN_00419d90`):

- `characterdata.dat`, `itemdata.dat`, `stage.dat` are each: opened, read
  fully into a stack buffer via `fseek`/`ftell`/`fread` (the classic
  "seek to end, tell, seek to start, read whole file" idiom), then decoded
  via `DecodeLZHUFBlock(...)`.
- After decoding, a **checksum is validated**: the decoded output is checked
  against `PeekPacketChecksumState()` — the same packet-checksum
  accumulator family documented in [PROTOCOL.md](PROTOCOL.md) — meaning the
  compressed `.dat` blob embeds an expected checksum value that must match
  the state produced by decoding, or the load is rejected (return code `1`
  = checksum mismatch, distinct from `2` = file-not-found).
- `LoadGameDataFiles` also opens `Avatar.xfs` (via `OpenXFSArchive`) as part
  of the same startup sequence — i.e. game-data file loading and avatar
  archive mounting happen together, at the same call site, early in
  `InitGame`.

This means the `orig/characterdata.dat` (1,130 bytes) etc. sample files
already in this repo (see hashes in [README.md](README.md)) are **compressed
blobs**, not directly-readable struct arrays — any future work to parse
their actual field layout needs the LZHUF decoder implemented first.

## `ChooseEvent.txt` — confirmed text config format

Lives *inside* `graphics.xfs` (not a standalone file), parsed by
`LoadChooseEventConfig`/`ParseChooseEventLine` (`0x409a10`/`0x409cb0`).
Fully read, byte-by-byte parser confirmed:

- **Comment lines**: a line whose first character is `;` is treated as a
  comment (still consumed but not parsed as data).
- **Field separator**: **tab character** (`\t`) — each field between tabs
  is parsed as an integer via `atol`.
- **Line terminator**: `\n`. `\r` characters are silently stripped (tolerant
  of Windows-style CRLF line endings).
- **Escape sequence**: a literal two-character `\n` (backslash followed by
  the letter `n`) inside a field is converted to a real newline byte before
  storage — i.e. fields can contain embedded newlines via escaping.
- Given the name "ChooseEvent" and its use inside `graphics.xfs`, this is
  almost certainly the character-select screen's per-character
  animation/event timing table (which frame index triggers which sound/
  effect during the character-selection animation) — not confirmed at the
  field-semantic level (the integer fields' individual meanings weren't
  decoded), only the container/parsing format.

## `.img` sprite format — confirmed via the render pipeline

Not loaded through a dedicated ".img parser" function found directly —
instead confirmed *indirectly* through the rendering code that consumes
decoded sprite data (see [ARCHITECTURE.md](ARCHITECTURE.md)'s rendering
section):

- **`BlitRLESprite`** (`0x4eb450`) decodes a **run-length-encoded** byte
  stream (high bit of each control byte distinguishes a literal run from a
  repeated-byte run) directly into the locked back-buffer.
- **`BlitSprite16bpp`** (`0x4ed6a0`) operates on `unsigned short*` pixel
  data — confirms the decoded pixel format is **16 bits per pixel**
  (RGB565 or RGB555, not disambiguated further).
- Hundreds of `.img` filenames were observed as string literals throughout
  the character/weapon/effect code (`tank1.img`, `bullet1n.img`,
  `flame11.img`, `mf%05d.img` for terrain deformation frames, etc.) — these
  are resolved to loaded texture handles via `FindPreloadedTextureByName`/
  `FindTextureCacheEntryByName` (see ARCHITECTURE.md), which look up
  *already-loaded* data; the actual disk-read + RLE-decode call site for a
  raw `.img` file (as opposed to consuming pre-decoded pixels) has not been
  isolated — it's presumably invoked once during `State10_Loading_PreloadAssets`
  for every filename in its huge preload list, but that specific call
  wasn't traced line-by-line in this pass.

## `.sv` replay format — event structure confirmed, file header not decoded

See [ARCHITECTURE.md](ARCHITECTURE.md)'s "replay-recording system" section
for the full writeup. Summary relevant to file format specifically:

- **Filename pattern**: `%s%s - %s.sv` (three string substitutions — likely
  date, room/player name, and a sequence or map name), with a
  `%Y%m%d %H%M`-style timestamp component also referenced nearby.
- **Body**: a flat stream of typed events (`Replay_AppendEvent(code)` +
  manually-appended payload bytes + `Replay_FlushEvent()`), using a growing
  in-memory buffer (`g_replayEventBuffer`/`g_replayEventCursor`) before being
  written out. Event codes overlap with the live network protocol's `0x8xxx`
  action-code family (see PROTOCOL.md) — the same codes drive both live
  network dispatch and replay playback through `ProcessBattleAction`.
- **Not confirmed**: any file-level header (magic, version, map/player
  metadata section) preceding the event stream — the write-side code
  located so far only shows the event-stream body being built and flushed,
  not an initial header write. A dedicated pass tracing where the replay
  `FILE*` (`DAT_006a9b68`) is `fopen`'d would likely reveal this.

## Known gaps / good next targets

1. Trace where the replay file (`DAT_006a9b68`) is actually `fopen`'d, to
   find the `.sv` file header (if any) preceding the event stream.
2. Confirm whether individual XFS archive entries are LZHUF-compressed,
   RLE-compressed, or stored raw, distinct from the TOC's compression.
3. A byte-exact reimplementation of the LZHUF decoder (`DecodeLZHUFBlock`)
   would be needed to actually decode `orig/characterdata.dat` and friends
   into readable records — this pass identified the algorithm family and
   call sites but did not reverse it byte-for-byte.
4. `ChooseEvent.txt`'s individual integer fields' semantics (what each
   tab-separated value in a line actually means) aren't decoded.
5. Whether `sound.xfs`/`Avatar.xfs` use the identical container format as
   `graphics.xfs` is inferred (same `OpenXFSArchive` function used for all
   three) but not independently spot-checked per file.
