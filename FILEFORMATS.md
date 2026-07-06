# GunBound Custom File Formats — Reverse-Engineered Reference

Findings from decompiling the asset-loading code path (`LoadGameDataFiles`,
`OpenXFSArchive`, and the LZHUF decode routines). Complements
[ARCHITECTURE.md](ARCHITECTURE.md) and [PROTOCOL.md](PROTOCOL.md).

## Summary table

| Extension | Container | Compression | Confirmed? |
|---|---|---|---|
| `.xfs` (`graphics.xfs`, `sound.xfs`, `Avatar.xfs`) | Custom named-entry archive, magic `XFS2` | LZHUF for both the table of contents (key `0x40`) **and each individual entry** (key `0x1000`, own checksum convention) | Confirmed at both the container and per-entry level |
| `.dat` (`characterdata.dat`, `itemdata.dat`, `stage.dat`, `specialdata.dat`) | Flat file, no container | **LZHUF-compressed** (key `0x14c0`), same decoder as XFS | Confirmed for `characterdata.dat`/`itemdata.dat`/`stage.dat` |
| `.img` (sprite/texture files, e.g. `tank1.img`, `bullet1n.img`) | Individual asset stored inside the `.xfs` archives, itself LZHUF-compressed as a container entry | RLE (run-length encoding) on top, 16bpp pixel data, applied after LZHUF decompression | Confirmed via `BlitRLESprite`/`BlitSprite16bpp` for the RLE/pixel layer; confirmed via `DecodeXFSEntryBlock` for the container-level LZHUF layer |
| `.sv` (replay files) | Custom event-stream format | Not compressed (not confirmed either way) | Filename format and per-event record fully confirmed; file open call / possible header not located |
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

**Confirmed**: individual archive *entries* are **also LZHUF-compressed**,
using a distinct key (`0x1000`) from the TOC (`0x40`) and the `.dat` files
(`0x14c0`). Traced via `DecodeXFSEntryBlock` (`0x4f03f0`, was
`FUN_004f03f0`), called during entry setup whenever a "not yet decoded"
condition is met. Confirmed on-disk per-entry block layout:

```
struct XFSEntryBlock {
    uint32_t compressedSize;   // read first, at the entry's stored file offset
    uint32_t checksum;         // read second
    uint8_t  compressedData[compressedSize]; // read third, into an 8 KB buffer
};
```

After reading, `DecodeLZHUFBlock(outputBuffer, readerState, compressedData,
compressedSize, 0x1000)` decompresses it. The decoded output is then
validated via a **summed arithmetic checksum** (not the packet-checksum-
state mechanism used for `.dat` files): the decoder sums four `int` fields
(`piVar2[-2] + piVar2[-1] + piVar2[1] + *piVar2`) across 256 (`0x100`)
iterations over the decoded buffer and compares the result against the
`checksum` field read from the block header. This is a **different
validation style** than the `.dat` files' `PeekPacketChecksumState`-based
check — the two container types share the same compression algorithm but
not the same integrity-check convention.

This means individual `.img` sprite files stored inside `graphics.xfs` are
**LZHUF-compressed at the archive-entry level, and separately RLE-encoded
at the pixel level** (see `BlitRLESprite` in ARCHITECTURE.md) — two
independent compression layers, one for the container, one for the pixel
data itself.

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

## `.sv` replay format — filename and per-event record confirmed

See [ARCHITECTURE.md](ARCHITECTURE.md)'s "replay-recording system" section
for the broader writeup. This section documents the file-format specifics,
now substantially more complete than the previous pass.

### Filename construction (fully confirmed)

Traced to the literal `sprintf` call site in `State09_ReadyRoom_ProcessPacket`
(the Channel 1 `0x3432` opcode handler — "stop replay recording" — which
closes out the *previous* file and immediately builds the *next* one):

```
sprintf(path, "%s%s - %s.sv", baseDir, timestampStr, sanitizedName);
```

- `baseDir` — `&DAT_005b1ed0`, the same asset/data base-directory global used
  throughout asset loading (see `BuildAssetPath` in the XFS section above).
- `timestampStr` — built via `_time32()` → `_localtime()` →
  `strftime(buf, 0x80, "%Y%m%d %H%M", tm)`. Confirms the exact `strftime`
  format string: **`%Y%m%d %H%M`** (e.g. `20260706 1430`).
- `sanitizedName` — the room/session name (read from a shared name buffer at
  `DAT_005b3484 + 0x44e64`), copied through a **filename-sanitization loop**
  that strips/rejects the Windows-illegal filename characters
  **`\ / : * ? " < >`  and `|`**, with special-cased handling for bytes
  `>= 0x80` (multi-byte/Korean-text-aware copying, copying 2 bytes at a time
  for high-byte sequences rather than risking splitting a double-byte
  character).

So a real filename looks like: `20260706 1430 - My Room Name.sv` (session
name appended after a literal `" - "` — note this comes from the format
string's fixed text between the second and third `%s`, not from any of the
substituted values themselves).

### Per-event binary record (confirmed)

Found via `WriteReplayEventRecord` (`0x4104f0`, was `FUN_004104f0`), the
lowest-level function that actually calls `fwrite` against the replay file
handle (renamed `g_replayFileHandle`, was `DAT_006a9b68`). Signature:
`WriteReplayEventRecord(size_t payloadLength, uint eventCode, byte *payload)`.
Confirmed write sequence (this function is called after
`Replay_AppendEvent`/`Replay_FlushEvent` have staged the data — it's the
actual disk-write step):

```
struct ReplayEventRecord {
    uint8_t  reserved;        // observed as 0 at this call site
    uint32_t sequenceOrTime;  // read from the In-Battle object at offset +4
                              // (i.e. g_gameStateObjects[0xb] + 4 -- the field
                              // immediately after the object's vtable pointer)
    uint32_t payloadLength;   // = the function's payloadLength argument
    uint16_t eventCode;       // low 16 bits of the eventCode argument
    uint8_t  payload[payloadLength]; // the actual event-specific data
};
```

This exact record shape (reserved byte, then the 4-byte field from the
battle object, then length, then code, then payload) was confirmed
identically at **three separate call sites** across different functions
(`WriteReplayEventRecord` itself, and two other call sites with the same
`fwrite` sequence inlined) — giving high confidence this is the one true
per-event record format used throughout, not something that varies by
caller.

**Not yet confirmed**: the literal `fopen()` call that creates the file.
Every reference to `g_replayFileHandle` found traces to: writing an event
record (guarded on the handle being non-null), explicitly nulling the handle
out (`= 0`), or `fclose`-ing it — the actual open call was not located in
this pass, meaning it's likely in a function not yet traced from this
handle's cross-reference list (possibly reached via a different addressing
form the reference search didn't catch, or gated behind a condition that
wasn't followed). Given the filename-construction code immediately zeroes
the handle right after building the path (rather than opening it inline),
the actual `fopen` may happen lazily on first write, in a function not yet
identified.

**Also not yet confirmed**: any file-level header (magic bytes, version
number, map/player roster metadata section) preceding the first event
record — nothing in the traced code writes anything to the file before the
first `WriteReplayEventRecord` call becomes possible, but this doesn't rule
out a header being written elsewhere (e.g. right after the still-unlocated
`fopen` call, which is exactly the kind of place a header write would
naturally sit).

## Known gaps / good next targets

1. **Partially resolved**: the `.sv` filename format and per-event binary
   record are now fully confirmed (see above). Still open: the literal
   `fopen()`-equivalent call site (to check for a file header preceding the
   first event record) wasn't located. Investigated further this pass: the
   CRT's actual file-opening chain (`__openfile` → `__fsopen` →
   `FUN_00525fac` wrapper) has only 5 callers system-wide, none of them
   replay-related, meaning the replay file must be opened through a
   different mechanism entirely (most likely raw `CreateFileA` +
   `_open_osfhandle`/`_fdopen`, mirroring the pattern already confirmed for
   XFS archives) that wasn't isolated in this pass — this would need either
   more exhaustive tracing of every `CreateFileA` call site in the binary,
   or dynamic analysis (breakpoint on `fclose` of the handle while playing,
   then find what set it).
2. **Resolved**: individual XFS archive entries are confirmed LZHUF-
   compressed (see above), with their own distinct key and checksum
   convention, separate from both the TOC and the `.dat` files' schemes.
3. A byte-exact reimplementation of the LZHUF decoder (`DecodeLZHUFBlock`)
   would be needed to actually decode `orig/characterdata.dat` and friends
   into readable records — this pass identified the algorithm family and
   call sites but did not reverse it byte-for-byte.
4. `ChooseEvent.txt`'s individual integer fields' semantics (what each
   tab-separated value in a line actually means) aren't decoded.
5. Whether `sound.xfs`/`Avatar.xfs` use the identical container format as
   `graphics.xfs` is inferred (same `OpenXFSArchive` function used for all
   three) but not independently spot-checked per file.
