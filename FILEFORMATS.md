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

## The `.xfs` table-of-contents entry record — fully confirmed layout

This is the piece needed to actually **enumerate** an archive's contents
(list every filename it holds), not just look up one name at a time. Traced
by decompiling `OpenXFSArchive`'s TOC-loading loop, `FindXFSEntry` (`0x4f1110`),
its string comparator `FUN_004f0990`, and the two entry-data readers
`ReadXFSEntry`/`ReadXFSEntryByte` (`0x4f0380`/`0x4f06c0`).

### TOC layout in memory (after LZHUF decoding)

The decoded TOC isn't one flat array — it's **chunked**:

- Decoded TOC header (first LZHUF block, key `0x40`) contains, after the
  4-byte `"XFS2"` magic, a **total entry count** (a `uint32_t`, confirmed
  read right after the magic check in `OpenXFSArchive`).
- Entries are grouped into **chunks of 1024 entries** (`entryIndex >> 10`
  selects the chunk, `entryIndex & 0x3ff` selects the entry within it).
  Each chunk is its own separate LZHUF-compressed block, decoded with key
  `0x20000` (128 KB — exactly `1024 entries × 128 bytes/entry`), read via
  the same 4-byte-length-prefixed-block loop as the initial TOC header.
  A pointer to each chunk's decoded 128 KB buffer is stored in an array
  (one `uint32_t` pointer per chunk).
- **Each entry record is exactly 128 (`0x80`) bytes.**
- **Entries are sorted case-insensitively by filename**, enabling
  `FindXFSEntry` to do a genuine **binary search** rather than a linear
  scan — confirmed by reading `FindXFSEntry`'s bisection loop directly
  (midpoint calculation, comparator call, narrowing `[low, high)`) and its
  comparator `FUN_004f0990`, which is a textbook `stricmp`: it upper-cases
  both sides (`'a'-'z'` range mapped by adding `0x20`... actually the reverse:
  it detects `'A'-'Z'` — `0x40 < c < 0x5b` — and folds it to lowercase by
  adding `0x20`) and compares byte-by-byte until a NUL or mismatch. **This
  means enumerating a full archive's filenames means walking every chunk's
  128-byte-stride array, not calling `FindXFSEntry` in a loop** (that
  function is a point lookup, not an iterator) — a real extractor should
  read the chunks directly.

### The 128-byte entry record

| Offset | Size | Field | Confirmed via |
|---|---|---|---|
| `0x00` | up to ~0x70 (variable) | **Filename**, NUL-terminated ASCII, case-insensitive | `FUN_004f0990`'s comparator operates directly on the record's base address |
| `0x70` | 4 | **Storage-mode flag**: `1` = entry stored **raw/uncompressed** in the archive file; anything else (`0`) = entry is **LZHUF-compressed** (the `XFSEntryBlock` format documented above) | `ReadXFSEntryByte`: `if (*(int*)(record+0x70) == 1)` branches into a direct `SetFilePointer`+`ReadFile` path instead of the ring-buffer/`DecodeXFSEntryBlock` path |
| `0x74` | 4 | **Base file offset** of the entry's data — interpreted as a raw byte offset into the archive file if the mode flag is `1`, or as the offset of the `XFSEntryBlock` header (`compressedSize`+`checksum`+`compressedData`) if the mode flag is `0` | `ReadXFSEntry` copies this into the reader-state's file-offset field, later used by both `DecodeXFSEntryBlock`'s `SetFilePointer` and the raw-mode `SetFilePointer` in `ReadXFSEntryByte` |
| `0x78` | 4 | **Decompressed (uncompressed) size** of the entry, in bytes — this is the size a consumer should expect after decompression, used as the EOF check in `ReadXFSEntryByte` (`storedSize <= readCursor` → return 0, i.e. end of entry) | `ReadXFSEntryByte`: `uVar6 = *(uint*)(record+0x78)` compared against the running read-cursor field |
| `0x7c` | 4 | Unaccounted-for / not observed in any of the three functions traced — likely padding, a reserved field, or a value only read by code not covered in this pass (e.g. a per-entry timestamp or CRC used elsewhere) | Not confirmed |

So: **name string, then three trailing `uint32_t` fields (mode flag, file
offset, decompressed size) in the last 12 bytes of the 128-byte record**,
with 4 bytes still unidentified. The exact name-field maximum length
(`0x70` = 112 bytes budget before the trailing fields, assuming no gap)
wasn't independently stress-tested against a real long filename in this
pass, but 112 bytes comfortably covers every filename observed in
[STRINGS.md](STRINGS.md).

### Important caveat for a from-scratch extractor: shared decode state

`DecodeLZHUFBlock`'s ring buffer, Huffman tree, and bit-buffer are **fields
of the archive handle object itself** (passed as `unaff_ESI`/`in_ECX`
throughout — the same base pointer used for the TOC, the file handle, and
every entry read), not something allocated fresh per entry. This means the
original code reads **one entry fully before starting another** — there's
no reentrant/interleaved multi-entry streaming. A clean-room extractor
doesn't need to replicate this constraint (you can simply decode entries
into independent output buffers one at a time, which is the natural way to
write an extractor anyway), but it's worth knowing if you're trying to
match the original's exact behavior rather than just extract assets.

### Putting it together: the full path from `.xfs` file to an extracted asset

For a tool that opens a `.xfs` file and dumps every entry to disk:

1. Open the file, seek to `EOF - 4`, read a `uint32_t` = TOC offset.
2. Seek to that TOC offset, read a `uint32_t` = TOC header's compressed size,
   read that many bytes, decode with LZHUF (key `0x40`). Verify the decoded
   output starts with `"XFS2"`. Read the `uint32_t` entry count right after
   the magic.
3. For `ceil(entryCount / 1024)` more chunks: read a 4-byte length prefix,
   read that many bytes, decode with LZHUF (key `0x20000`, i.e. expect a
   128 KB decoded output = 1024 × 128-byte records — the last chunk may
   have fewer valid entries, per `entryCount & 0x3ff`).
4. Concatenate/index the chunks to get every entry's 128-byte record: read
   the NUL-terminated name at offset `0x00`, mode flag at `0x70`, file
   offset at `0x74`, decompressed size at `0x78`.
5. For each entry: if mode flag `== 1`, seek to the file offset and read
   `decompressedSize` bytes directly — done, no decompression needed. If
   mode flag `!= 1`, seek to the file offset, read a `uint32_t`
   compressed-size and `uint32_t` checksum (the `XFSEntryBlock` header),
   read `compressedSize` bytes, and LZHUF-decode (key `0x1000`) — this may
   need to be done in a loop for entries larger than the 4 KB ring buffer
   (the original reads/decodes in a streaming fashion; a from-scratch tool
   can simplify this by decoding the whole entry in one pass into an output
   buffer sized to the confirmed `0x78` decompressed-size field, since you
   don't need to replicate the original's fixed internal buffer limits).
6. If the entry's name ends in `.img`, apply the RLE + 16bpp pixel decode
   documented in the `.img` section below to get raw pixel data; otherwise
   (`.txt` files, etc.) the LZHUF-decoded bytes are the final output as-is.

## The LZHUF compression scheme — confirmed as the classic Okumura/Yoshizaki algorithm

`DecodeLZHUFBlock` (`0x4eaba0`), its tree-initialization helper
`InitLZHUFTree` (`0x4ea300`), and its two Huffman-tree-walk primitives
`FUN_004ea670` (character/length decode) and `FUN_004ea6e0` (match-position
decode) were fully decompiled this pass. Together they confirm this is not
merely "an LZHUF-family codec" but a near-verbatim implementation of the
**classic public-domain `LZHUF.C`** (Okumura/Yoshizaki, widely ported since
the late 1980s — the same lineage used by LHA `.lzh` archives) — right down
to matching constant values:

- `InitLZHUFTree` initializes `N_CHAR` = **314** (`0x13a`) leaf symbols and
  a tree table of **627** (`0x273`) total nodes — exactly `T = 2*N_CHAR - 1`,
  the textbook LZHUF binary-tree size formula. This is a strong signature
  match, not just a family resemblance: an independently-designed codec
  would have no reason to land on exactly these constants.
- `FUN_004ea670` (`DecodeChar` in the reference source) walks the Huffman
  tree from the root down through a `son[]`-style child-index array
  (`unaff_ESI + 0xece4 + index*4`), refilling a 16-bit bit-buffer
  (`unaff_ESI + 0xf6b0`, with a bits-remaining counter at `+0xf6b2`) one
  byte at a time via `FUN_004ea120` (the reference's `GetBit`/`FillBuf`)
  whenever it runs dry — this is a structurally exact match to the
  reference implementation's `DecodeChar()`.
- `FUN_004ea6e0` (`DecodePosition` in the reference source) reads an 8-bit
  code through a small secondary Huffman table (`DAT_0056dd30`/`DAT_0056de30`,
  matching the reference's static `p_len`/`p_code` tables) for the high
  bits of the back-reference distance, then reads 6 more raw bits for the
  low bits (`uVar2 & 0x3f`) — again an exact structural match to the
  reference's position-decoding scheme.
- The main decode loop in `DecodeLZHUFBlock` is the textbook LZSS
  unpacking loop: a **4096-byte (`0xfff` mask) sliding-window ring buffer**
  (initialized to ASCII spaces, `0x20`, per the reference source's
  convention), where each iteration either emits a literal byte (decoded
  symbol `< 0x100`) or copies a back-reference run (`decoded symbol - 0xfd`
  = run length, `DecodePosition()` = distance back into the ring buffer),
  writing to both the ring buffer and the growing output buffer
  simultaneously — identical in structure to the reference `Decode()` loop.
- Both the XFS table-of-contents and the `.dat` data files are decoded
  through this **exact same function**, just called with different
  size/key parameters (`0x40` for the XFS TOC vs. `0x14c0` for
  `characterdata.dat`, `0x1000` for XFS archive entries) — confirming one
  shared compression scheme reused across all container types.

### The adaptive Huffman update — also confirmed (closes the last piece)

The remaining piece — how the Huffman tree evolves across the stream,
rather than just how it's walked for one symbol — is now confirmed too.
Three more functions decompiled this pass complete the picture:

- **`FUN_004ea120`/`FUN_004ea1b0`** (`GetBit`/`GetByte` in the reference
  source) — the low-level bitstream reader both `DecodeChar` and
  `DecodePosition` call into. Both refill an internal 16-bit bit-buffer
  (state-struct field `+0xf6b0`, with a bits-available counter at
  `+0xf6b2`) one input byte at a time from the compressed-data cursor
  (`+0xf6b8`/`+0xf6c0`/`+0xf6c4`), returning either a single bit or a full
  byte — structurally identical to the reference `GetBit()`/`GetByte()`.
- **`FUN_004ea580`** (`Update` in the reference source) — called at the end
  of every `DecodeChar()` with the just-decoded symbol. Increments that
  symbol's frequency count (`+0xd460` array) and, if it now exceeds a
  neighboring node's frequency, **swaps the node's position in the tree**
  (reordering both the frequency array and the parent/child index arrays
  at `+0xece4`/`+0xde30`/`+0xde34`) to keep the tree weight-ordered — the
  textbook adaptive-Huffman "promote on frequency increase" step. Also
  confirmed the reference's overflow guard: when the root frequency
  (`+0xde28`) reaches **32768** (`0x8000`), it calls `FUN_004ea3b0` to
  fully rebuild the tree before continuing.
- **`FUN_004ea3b0`** (`reconst` in the reference source) — the periodic
  full tree rebuild. Halves every leaf's frequency (`(freq+1)>>1`, the
  reference's overflow-avoidance halving), then reconstructs the entire
  tree bottom-up by repeatedly merging the two lowest-frequency nodes
  (`_memmove`-based insertion into a frequency-sorted array) and
  reassigning every parent/child pointer — again a structural match to the
  reference `reconst()`.

**This closes gap #3 (previously "known gaps" item 3) at the algorithm
level.** Every function involved in decoding an LZHUF stream — bitstream
reader, symbol/position decoders, frequency update, and periodic tree
rebuild — has now been decompiled and confirmed to match the public-domain
`LZHUF.C` reference implementation structurally, not just by family
resemblance. What remains is purely mechanical: transcribing these
confirmed routines (plus the already-documented state-struct offsets:
ring buffer at `+8`, frequency table at `+0xd460`, parent/child arrays at
`+0xece4`/`+0xde30`/`+0xde34`, bit-buffer at `+0xf6b0`) into a standalone,
compilable decoder — no further reverse-engineering unknowns remain, only
implementation work.

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

## `Language.txt` and `Sound.txt` — confirmed to live inside `graphics.xfs`

Resolves a question flagged as open in [STRINGS.md](STRINGS.md) (the `Language.txt`/
`Sound.txt`/`FourWord.txt` filenames hadn't been cross-referenced against
loader code). Traced two more call sites of `OpenXFSArchive`/`FindXFSEntry`:

- `FUN_0043da00`: `BuildAssetPath(buf, &DAT_005b1ed0, "graphics.xfs", 0)` →
  `OpenXFSArchive(buf, 1, 0)` → `FindXFSEntry(handle, "Language.txt")` —
  confirms **`Language.txt` is not a standalone file**, it's an entry inside
  `graphics.xfs`, read the same way `ChooseEvent.txt` is.
- `FUN_004e3500`: identical pattern, opens `graphics.xfs`, then
  `FindXFSEntry(handle, "Sound.txt")` — confirms **`Sound.txt`** likewise
  lives inside `graphics.xfs`, not on disk as its own file.

Both functions open `graphics.xfs` fresh (rather than reusing an
already-open handle), consistent with each config file being loaded through
its own short-lived `OpenXFSArchive`/`FindXFSEntry`/read/close cycle rather
than one archive being kept open for the whole session.

`FourWord.txt` was not traced to a call site in this pass — its consumer
function wasn't identified — so its origin (inside an `.xfs` vs. a
standalone file) remains unconfirmed.

## `Avatar.xfs` — confirmed filename, same container format

Followed up the `LoadGameDataFiles` avatar-archive mount call
(`0x419dce`) with raw disassembly: it calls `BuildAssetPath(buf,
&DAT_005b1ed0, "Avatar.xfs", 0)` (string confirmed at `0x553660` =
`"Avatar.xfs"`) then `OpenXFSArchive(buf, 1, 0)` — the exact same
call shape as every confirmed `graphics.xfs` open. This **confirms**
`Avatar.xfs` uses the identical `XFS2` container format, closing that
part of the previous pass's open question.

## `sound.xfs` container format — inconclusive, revised finding

Widened the search: dumped every `PUSH`/`CALL`/`LEA` instruction across the
*entire* body of both `InitDirectSound` (`0x4ee5b0`–`0x4ee600`) and
`InitDirectDraw` (`0x4efaa0`–`0x4eff50`), not just the few instructions
immediately preceding their `OpenXFSArchive` calls. **Neither function
contains a string-literal push for any `.xfs` filename anywhere in its
body** — every `PUSH` of a `.rdata` address in that range resolves to
something else (the `"dsound.dll"`/`"DirectSoundCreate8"` strings, GUID
constants, D3D enum values, etc.), unlike the `graphics.xfs`/`Avatar.xfs`
call sites which all show a clear `BuildAssetPath(..., "graphics.xfs", ...)`
pattern right before the `OpenXFSArchive` call.

This means both `InitDirectSound`'s and `InitDirectDraw`'s `OpenXFSArchive`
calls almost certainly receive their filename as **an argument passed in
from their caller** (`OpenXFSArchive(param_1, 1, 0)` in `InitDirectDraw`'s
decompiled output confirms `param_1` — the function's own first
parameter — is what's forwarded, not a hardcoded literal), rather than a
literal local to either function. The filename buffer is built somewhere
upstream — presumably in `InitGame`, which calls both — and threaded
through as a parameter. This is a **weaker** finding than the previous
pass's tentative "corroborated" note suggested: it neither confirms nor
rules out `sound.xfs` sharing the container format. Resolving it would
mean tracing `InitGame`'s call sites into `InitDirectSound`/`InitDirectDraw`
to see what buffer it constructs and passes in as that parameter — not
attempted in this pass.

## `.sv` replay file's `fopen()` call site — investigation exhausted (static analysis)

Extended the search from the previous pass. Confirmed the actual CRT
`fopen()` implementation is `FUN_00525fac` (verified by finding a sibling
call site, the screenshot writer at `0x412e50`, which calls
`FUN_00525fac(path, "wb")` immediately before an `fwrite`/`fclose` BMP-write
sequence — this nails down `FUN_00525fac`'s signature as `fopen(path, mode)`
beyond doubt). `FUN_00525fac` has exactly **5 callers system-wide**:
`FUN_00412e00`/`FUN_00412e50` (both part of the screenshot-capture feature,
unrelated to replays) and three call sites inside `LoadGameDataFiles`
(loading `.dat`/`.xfs` game-data files at startup, also unrelated). **None
of these is the replay file.**

Also re-examined the three functions that directly touch
`g_replayFileHandle` (`State09_ReadyRoom_OnEnter`, `State09_ReadyRoom_ProcessPacket`
opcode `0x3432`, `State03_GameRoomList_OnEnter`) instruction-by-instruction:
all three only ever `fclose()` and zero the handle — none of them calls
`fopen`/`CreateFileA` afterward. In `State09_ReadyRoom_ProcessPacket`'s
`0x3432` handler specifically, the replay filename **is built via `sprintf`
into a local stack buffer that is never subsequently read** — confirmed by
dumping every `CALL` instruction in the function (only three, all to
`sprintf`, for three different formatted strings) and the raw disassembly
immediately following the `sprintf`/handle-zero pair (next instructions are
unrelated state resets, no `fopen`/`CreateFileA` in the vicinity).

This means the file is opened by a function this pass could not locate
through xref-based static tracing — the four candidate `CreateFileA` callers
found (`OpenXFSArchive`, plus three registry/hardware-fingerprint functions
at `0x5207d0`/`0x523530`/`0x524bb0` that read like anti-cheat/VM-detection
code, entirely unrelated to replays) rule out the direct-`CreateFileA` path
too. Remaining possibilities, in rough order of likelihood: (a) the path is
stored to a global this pass didn't spot before the function returns, and a
*different*, not-yet-identified function opens it lazily on first write;
(b) the open happens through an indirect/vtable call this pass's plain xref
search doesn't resolve (the same class of gap that made the render vtable
slots hard to enumerate). Resolving this further would need dynamic
analysis: breakpoint on `fopen`/`CreateFileA` while recording a replay in a
live session, or a memory-write watchpoint on `g_replayFileHandle` to catch
the exact instruction that first sets it non-null.

## Known gaps / good next targets

0. **Resolved**: the `.xfs` table-of-contents entry record layout is now
   fully mapped (128-byte records, sorted for binary search, name +
   mode-flag + file-offset + decompressed-size fields — see the dedicated
   section above). This was the missing piece for writing an actual
   extractor (previously only single-entry lookup by name was documented,
   not full-archive enumeration). One 4-byte field in the record (`0x7c`)
   remains unidentified.
1. **Static-analysis-exhausted**: the `.sv` filename format and per-event
   binary record are fully confirmed (see above). The literal `fopen()`-
   equivalent call site was searched exhaustively this pass — every caller
   of the confirmed `fopen()` implementation (`FUN_00525fac`, 5 callers,
   none replay-related), every `CreateFileA` caller (6, all
   XFS-archive-loading or anti-cheat/registry code, none replay-related),
   and every direct read/write reference to `g_replayFileHandle` (all
   `fclose`/zero, never an open) were checked — see the dedicated section
   above. Concluded this needs dynamic analysis (breakpoint/watchpoint) to
   resolve further; not a productive target for more static tracing.
2. **Resolved**: individual XFS archive entries are confirmed LZHUF-
   compressed (see above), with their own distinct key and checksum
   convention, separate from both the TOC and the `.dat` files' schemes.
3. **Resolved at the algorithm level**: the entire LZHUF codec — bitstream
   reader (`GetBit`/`GetByte`), symbol/position Huffman decoders
   (`DecodeChar`/`DecodePosition`), the adaptive frequency-update/tree-
   reorder step (`Update`), and the periodic full-tree rebuild (`reconst`)
   — is now confirmed structurally identical to the classic public-domain
   `LZHUF.C` reference implementation, including exact constants
   (`N_CHAR=314`, `T=627`, 4096-byte window, 32768 frequency-overflow
   threshold). See the dedicated section above for the full function-by-
   function mapping. What remains to actually decode `orig/characterdata.dat`
   and friends is purely mechanical: transcribing the confirmed routines and
   state-struct offsets into a standalone compilable decoder — no more
   reverse-engineering unknowns, only implementation work.
4. `ChooseEvent.txt`'s individual integer fields' semantics (what each
   tab-separated value in a line actually means) aren't decoded.
5. **Mostly resolved, one genuine unknown remains**: `graphics.xfs`
   (confirmed via `Language.txt`/`Sound.txt` lookups) and **`Avatar.xfs`**
   (confirmed via raw-disassembly tracing of `LoadGameDataFiles`'s
   `BuildAssetPath(..., "Avatar.xfs", ...)` call) both independently
   confirmed to use the identical `OpenXFSArchive` container path. `sound.xfs`
   remains **genuinely unconfirmed** — traced further this pass and found
   that `InitDirectSound`'s (and also `InitDirectDraw`'s) `OpenXFSArchive`
   call receives its filename as a parameter forwarded from its caller
   (presumably `InitGame`), not a literal local to the function, so no
   filename string could be recovered by looking at `InitDirectSound` alone.
   Would need to trace `InitGame`'s call sites into these two functions to
   see what buffer it builds and passes in.
