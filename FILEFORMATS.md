# GunBound Custom File Formats — Reverse-Engineered Reference

Findings from decompiling the asset-loading code path (`LoadGameDataFiles`,
`OpenXFSArchive`, and the LZHUF decode routines). Complements
[ARCHITECTURE.md](ARCHITECTURE.md) and [PROTOCOL.md](PROTOCOL.md). A
working, verified LZHUF decoder and `.xfs` extractor now live in
[tools/lzhuf/](tools/lzhuf/) — see that directory's README for usage.

## Summary table

| Extension | Container | Compression | Confirmed? |
|---|---|---|---|
| `.xfs` (`graphics.xfs`, `sound.xfs`, `Avatar.xfs`) | Custom named-entry archive, magic `XFS2` | LZHUF for both the table of contents (target decoded size `0x40` for the header, `0x20000` per 1024-entry chunk) **and each individual entry** (target decoded size = the entry's own confirmed size field, own checksum convention) | **Fully confirmed and working** — all three real `.xfs` files decode end-to-end via `tools/lzhuf/extract_toc.py` |
| `.dat` (`characterdata.dat`, `itemdata.dat`, `stage.dat`, `specialdata.dat`) | Flat file, no container | **LZHUF-compressed**, same decoder as XFS — **target size differs per file** (confirmed via `LoadGameDataFiles` for three of the four): `characterdata.dat` = `0x14c0` (5,312 bytes), `stage.dat` = `0x3c80` (15,488 bytes), `itemdata.dat` = `0x7850` (30,800 bytes). `specialdata.dat`'s loader wasn't located in `LoadGameDataFiles` or anywhere else this pass — its target size is **unconfirmed** (an earlier pass's `0x14c0` guess for it was never verified against code and shouldn't be trusted) | Confirmed and working for `characterdata.dat`/`stage.dat`/`itemdata.dat` — real content extracted (item names, stage names, Portuguese item descriptions). `specialdata.dat` not yet properly decoded (right target size unknown) |
| `.img` (sprite/texture files, e.g. `tank1.img`, `bullet1n.img`) | Individual asset stored inside the `.xfs` archives, itself LZHUF-compressed as a container entry | RLE (run-length encoding) on top, 16bpp pixel data, applied after LZHUF decompression | Confirmed via `BlitRLESprite`/`BlitSprite16bpp` for the RLE/pixel layer; confirmed via `DecodeXFSEntryBlock` for the container-level LZHUF layer |
| `.sv` (replay files) | Custom event-stream format | Not compressed (not confirmed either way) | Filename format and per-event record fully confirmed; file open call / possible header not located |
| `ChooseEvent.txt` | Plain text, lives *inside* `graphics.xfs` | None (plain text) | **Fully confirmed** — actual content extracted, a 4-line event-name-to-ID registry |

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
using the entry's own decoded-size field (see the confirmed TOC record layout below) rather than a fixed constant like the TOC header (`0x40`) or the `.dat` files
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

- Decoded TOC header (first LZHUF block, target output size `0x40` = 64 bytes) contains, after the
  4-byte `"XFS2"` magic, a **total entry count** (a `uint32_t`, confirmed
  read right after the magic check in `OpenXFSArchive`).
- Entries are grouped into **chunks of 1024 entries** (`entryIndex >> 10`
  selects the chunk, `entryIndex & 0x3ff` selects the entry within it).
  Each chunk is its own separate LZHUF-compressed block, decoded with
  target output size `0x20000` (128 KB — exactly `1024 entries × 128 bytes/entry`), read via
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
| `0x7c` | 4 | **Compressed size on disk** (i.e. the on-disk footprint of the `XFSEntryBlock`'s `compressedData`, only meaningful when the entry is LZHUF-compressed) — distinct from `0x78`'s *decompressed* size | Confirmed via `FUN_004f1220` (the entry-record **insert** function, effectively the archive-writer/pack side — see below): it zero-initializes both `record+0x78` and `record+0x7c` together when creating a fresh record, and a size-accounting function (`FUN_004f18c0`) reads `record+0x78` when the mode flag is `1` (raw) but `record+0x7c` when the mode flag is `0` (compressed) to add to a running byte-loaded counter — i.e. "0x78 = logical/decompressed size" and "0x7c = physical/compressed size," which collapse to the same value only for raw entries |

So: **name string, then four trailing `uint32_t` fields — mode flag, file
offset, decompressed size, compressed size — occupying the last 16 bytes of
the 128-byte record.** All four are now fully identified. The exact
name-field maximum length (`0x70` = 112 bytes budget before the trailing
fields, assuming no gap) wasn't independently stress-tested against a real
long filename in this pass, but 112 bytes comfortably covers every filename
observed in [STRINGS.md](STRINGS.md).

### The archive also has a writer/insert path (not just a reader)

`FUN_004f1220` builds a **brand-new** 128-byte TOC record and inserts it
into the sorted array at the correct sort position (using the same
`FUN_004f0990` comparator `FindXFSEntry` uses for lookup), allocating a
fresh 128 KB chunk when the 1024-entries-per-chunk boundary is crossed and
shifting existing records to make room — i.e. the exact same TOC structure
documented above, but built from scratch rather than just read. This
confirms the field layout further (it explicitly zero-initializes `+0x78`
and `+0x7c` and sets `+0x70`/`+0x74` at creation time) and reveals the
client itself contains **archive-writing logic**, not just a reader — this
is likely used for a runtime avatar/decal cache or similar dynamic content
that gets appended to an in-memory (or on-disk) `.xfs`-shaped structure,
rather than being purely a read-only asset format. This pass didn't trace
who calls `FUN_004f1220` or what triggers writing, so the exact purpose of
the writer path remains open — but it's worth knowing the format isn't
strictly append-only/build-time-only.

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
   read that many bytes, decode with LZHUF (target output size `0x40` = 64 bytes). Verify the decoded
   output starts with `"XFS2"`. Read the `uint32_t` entry count right after
   the magic.
3. For `ceil(entryCount / 1024)` more chunks: read a 4-byte length prefix,
   read that many bytes, decode with LZHUF (target output size `0x20000`, i.e. expect a
   128 KB decoded output = 1024 × 128-byte records — the last chunk may
   have fewer valid entries, per `entryCount & 0x3ff`).
4. Concatenate/index the chunks to get every entry's 128-byte record: read
   the NUL-terminated name at offset `0x00`, mode flag at `0x70`, file
   offset at `0x74`, decompressed size at `0x78`.
5. For each entry: if mode flag `== 1`, seek to the file offset and read
   `decompressedSize` bytes directly — done, no decompression needed. If
   mode flag `!= 1`, seek to the file offset, read a `uint32_t`
   compressed-size and `uint32_t` checksum (the `XFSEntryBlock` header),
   read `compressedSize` bytes, and LZHUF-decode (target output size = the entry's own `0x78` decompressed-size field) — this may
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
  target-output-size parameters (`0x40` for the XFS TOC header vs. `0x14c0` for
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
**Content and semantics now fully confirmed** — the LZHUF decoder bug that
previously blocked reading this file (see the "LZHUF decoder" section
below) has been fixed, and the file was extracted directly from a real
`graphics.xfs`. Its **entire contents** (38 bytes):

```
0	off
1	christmas
2	event2
3	event3
```

This is a small **event-name-to-ID registry**, not a character-select
animation/timing table as earlier passes had guessed — each line is
`<numeric ID>\t<event name>`, e.g. `1` → `"christmas"`. This retroactively
clarifies the earlier `ParseChooseEventLine` trace: it's parsed into a
generic pooled hash-table (`FUN_00426780`/`FUN_00409d10`, a string-hash
lookup + pooled insert — likely a reused generic container, not
`ChooseEvent`-specific) keyed by the **event name string** (the second
field, e.g. `"christmas"`), with the **numeric ID** (first field) as the
stored value — i.e. code elsewhere can look up "what numeric event ID does
the string `christmas` map to." Given the tiny size and content (an
off/christmas/two-generic-"eventN" list), this is almost certainly what
lets the client select a **seasonal reskin or special-event mode** by
name — e.g. a server-sent event name gets resolved to this ID to swap in
holiday-themed assets or `ChooseEvent`-driven map/UI variants. The two
generic entries (`event2`/`event3`) suggest the mechanism supports more
event types than were ever actually named/shipped, or that other events
are added by editing this file rather than the client binary.

## `itemdata.dat` — confirmed record layout and target size

**Correction from the previous pass**: `itemdata.dat`'s real
`DecodeLZHUFBlock` target size, confirmed by decompiling
`LoadGameDataFiles` directly, is **`0x7850` (30,800 bytes)** — not `0x14c0`
(5,312 bytes), which is `characterdata.dat`'s size and had been wrongly
assumed to apply to all three `.dat` files. Redecoding with the correct
size doesn't change the earlier per-record field findings (they were all
within the first 5,312 bytes anyway, so the earlier bytes were already
correct) — it just reveals the *full* file instead of a truncated prefix:

- **Fixed-size records, `0x134` (308) bytes each** (unchanged from the
  earlier finding — confirmed independently via a printable-string scan
  landing on a consistent 308-byte stride).
- **Exactly 100 total slots** (`30800 / 308 = 100` exactly — this divides
  perfectly, strong confirmation the record size and total buffer size are
  both right), of which **13 are populated** in this file's real data
  (the same 13 found in the earlier, truncated pass — `"Dual"`,
  `"Teleport"`, `"Dual+"`, an untranslated-Korean-name item, `"Blood"`,
  `"Energy up 1"`/`"Energy up 2"`, `"Team Teleport"`, `"Change Wind"`,
  `"Power up"`, `"Thunder"`, `"Bunge shot"`, another untranslated item),
  and the remaining 87 slots are zero-filled/unused — consistent with this
  being a smaller private-server build with far fewer items defined than
  the 100-slot capacity allows.
- **Per-record layout — now confirmed directly from `LoadGameDataFiles`'s
  consumer code**, not just inferred from decoded bytes (this section
  supersedes the byte-pattern-only version from the previous pass; the
  earlier guesses turned out close but slightly imprecise in a few spots):

  | Offset | Size | Field | Notes |
  |---|---|---|---|
  | `0x00` | up to 0x20 (32) | Item name, NUL-terminated ASCII/text | e.g. `"Dual"`, `"Teleport"`, `"Energy up 1"` — two entries contain non-ASCII bytes consistent with **Korean text in a single-byte-per-char encoding rendering as mojibake when read as Latin-1** — i.e. this particular (Brazilian Portuguese-localized) build has a couple of items that were never translated from the original Korean strings. Confirmed copied into a persistent per-item structure at a fixed destination offset. |
  | `0x20` | 4 | `uint32` field | Read and fed through the packet checksum accumulator (`EncodeOutgoingPacketField`) — validated but not confirmed copied to a named persistent field in this code path. Often `0` in this file's real data. |
  | `0x24` | 4 | Price/value (`uint32`) | e.g. `600` for "Dual", `100` for "Teleport", `0` for "Blood" — a zero value for some entries suggests not every item is purchasable (some may be quest/event-only). Same checksum treatment as `0x20`. |
  | `0x28` | 4 | Item type/index ID (`uint32`) | e.g. "Energy up 1" and "Energy up 2" share the same value (`7`), consistent with a shared item-family/category ID rather than a unique per-item ID. Same checksum treatment as `0x20`/`0x24` — **correction from the previous pass**: this is not literally duplicated at `0x30` as a single byte; that earlier read was of a different, misidentified field (see `0x30` below). |
  | `0x2c` | 1 | Boolean flag 1 | **Individually obfuscated on copy to persistent storage**: XORed/masked together with two `rand()` calls into a 3-byte encoded form (`encoded_byte, encoded_flag, checksum_byte = encoded_byte + encoded_flag - 0x34`) rather than copied plainly — an explicit anti-memory-editing/anti-cheat measure specifically for this flag (no other item field gets this treatment) |
  | `0x2d` | 1 | Boolean flag 2 | Same individually-obfuscated encoding as `0x2c`, independently |
  | `0x2e` | 1 | Boolean flag 3 | Same individually-obfuscated encoding as `0x2c`/`0x2d`, independently — the fact that exactly *three* boolean-ish flags get this specific protection (out of everything else in the record) suggests these three are considered especially sensitive to tamper with client-side — plausible candidates: "tradable," "usable in battle," "giftable," or similar toggles that a cheater might want to flip locally |
  | `0x2f` | 1 | Unaccounted (padding/gap) | Not read by this code path |
  | `0x30` | 2 | `ushort` field | Read as a genuine 16-bit value and checksummed — **correction from the previous pass**, which had read this as two separate bytes (a duplicate type-ID byte at `0x30` plus a `0xff` "marker" byte at `0x31`); the real code treats it as one `ushort`. Purpose beyond "checksummed" not confirmed. |
  | `0x32` | variable | Localized item description, NUL-terminated | Confirmed copied into persistent storage at its own destination offset, independent of the other fields above. Real examples (Portuguese, this build's localization): `"Usando este item voce pode disparar seu tiro duas vezes..."` (Dual), `"Pode teleportar para o ponto onde o objeto de teleporte caiu..."` (Teleport) |

**Persistent storage confirmed too**: unlike `characterdata.dat` (whose
decoded buffer turned out to be purely a local stack copy, discarded after
checksum validation — see below), `itemdata.dat`'s fields — name,
description, and the three obfuscated flags — are genuinely copied into a
**persistent per-item structure** at `param_1 + 0x58b8d6` (`param_1` being
the same top-level game-object pointer threaded through
`LoadGameDataFiles`), with a **destination stride of `0x9bc` (2,492)
bytes** — much larger than the 308-byte source record, consistent with
the destination struct holding additional derived/runtime fields beyond
what's stored on disk.

Still open: the exact meaning of the `0x20`/`0x28`/`0x30` fields beyond
"checksummed," and which specific gameplay toggles the three obfuscated
boolean flags represent.

## `stage.dat` — confirmed record layout and target size

**Correction from the previous pass**: the earlier attempt used the wrong
target size (`0x14c0`, copied from `characterdata.dat`) and produced a
truncated, confusingly-fragmented decode. Decompiling `LoadGameDataFiles`
directly gives the real values:

- **Target decompressed size: `0x3c80` (15,488 bytes).**
- **Fixed-size records, `0x1e4` (484) bytes each** — confirmed directly
  from the loader's loop (`pcVar10 = pcVar10 + 0x1e4`), not just inferred
  from string positions.
- **Exactly 32 total slots** (initialized loop counter `uStack_181c4 = 0x20`
  = 32, decremented to 0) — `32 × 484 = 15,488`, an exact match confirming
  both numbers.
- **Only slot 0 is populated** in this file's real data — the stage name
  `"Cave(Random)"` appears cleanly at the very start (preceded by 4 bytes,
  `ef db ff 74`, of unclear purpose — possibly a stage ID or checksum
  fragment). Slots 1-31 are **not zero-filled** like `itemdata.dat`'s empty
  slots — they contain non-zero but clearly non-meaningful repeating byte
  patterns (e.g. `0x13` repeated, `0x66` repeated, `0x8c` repeated), which
  reads like uninitialized/leftover builder memory rather than real map
  data. This is consistent with the working theory (see `itemdata.dat`
  above and the Portuguese localization already noted in
  [STRINGS.md](STRINGS.md)) that this is a **smaller private-server build
  with only one stage actually defined**, not the retail game's full map
  roster.
- The per-record field layout beyond the name (the loader reads several
  4-byte fields at offsets `+0x80`/`+0x82`/`+0x84`/`+0x88`.../`+0xa0`, then
  an 8-element sub-array at 4-byte stride starting `+0xc4`, all pushed
  through `EncodeOutgoingPacketField`) wasn't mapped field-by-field this
  pass — worth a dedicated follow-up now that the stride/size are solid.

## `characterdata.dat` — record count/stride confirmed, field semantics partial

Initial attempt at this (decompiling `LoadGameDataFiles`'s post-decode step
directly, the same approach that worked for `stage.dat`) looked like a dead
end at first — that step is a **checksum-validation loop**, not a
field-by-name parser: it walks through a run of raw `uint32`s from the
decoded buffer and feeds each one individually into
`EncodeOutgoingPacketField`/the checksum accumulator, with no meaningful
per-field naming, and Ghidra's stack-frame analysis for this function is
visibly imprecise (several declared local buffers are far too small for
what's actually written through them, so exact buffer boundaries can't be
trusted from the decompiled variable declarations alone).

**However, the loop's own increment amount is trustworthy** (it's a
constant added to a pointer each iteration, not a fuzzy stack-size
inference), and it revealed real structure: `puStack_181d8 = puStack_181d8
+ 0x53` (53 hex = 83 `uint32`s = `0x14C`/332 bytes) advancing once per
iteration, with the outer loop counter initialized to `0x10` (16) and
counting down to zero. **`16 × 332 = 5,312 = 0x14c0`** — an exact match to
the file's confirmed total decoded size, strongly confirming:
**`characterdata.dat` holds exactly 16 fixed-size mobile records of 332
bytes each** — matching GunBound's classic 16-mobile roster count.

Decoded the real file and inspected the first several fields of each
record directly to sanity-check this (not from further code tracing — the
checksum loop doesn't reveal field *names*, just the stride/count):

- **`0x00`-`0x03`, `0x04`-`0x07`** (two `uint32`s): near-constant across
  all 16 records (`28, 24` for 15 of them) — very plausibly a **bounding-
  box/hitbox width and height**. One record (index 13) differs slightly
  (`26, 26`), suggesting that mobile has a non-standard hitbox.
- **`0x08`-`0x0b`**: mostly `0`, with a handful of records showing small
  values (`2`-`4`) — possibly a team/type/category enum.
- **`0x0c`-`0x0f`, `0x10`-`0x13`, `0x14`-`0x17`**: three more `uint32`s
  with plausible small-integer game-balance values (ranging roughly
  10-170) — likely stats such as HP/speed/weight. Notably, **records 2 and
  15 share unusually large values across all three fields** (`170, 130,
  165` and `170, 130, 170` respectively) while every other record clusters
  in the 10-90 range — strongly suggestive of a matched pair of
  heavy/tank-type mobiles (e.g. a land/sea variant of the same unit, or
  two mobiles from the same weight class).

This is real, confirmed structural progress (record count and stride are
solid; several early fields show internally-consistent, plausible
game-data patterns), but the exact field *names* (which offset is truly
"HP" vs "weight" vs something else) aren't confirmed from code — that
would need finding the actual stats-consumer function (e.g. wherever the
character-select screen reads and displays these values) rather than
inferring from cross-record numeric patterns alone.

**Also confirmed via raw disassembly**: the destination buffer
`DecodeLZHUFBlock` writes into for `characterdata.dat` is a genuine
`ESP`-relative stack address (`LEA EAX,[ESP + 0x7c8c]`), not a
mislabeled pointer into the persistent game object — ruling out the
hypothesis that Ghidra's imprecise stack-frame analysis was hiding a
persistent destination. No copy-out step to persistent storage was found
immediately after the checksum loop (contrast with `itemdata.dat`, which
*does* copy into a confirmed persistent struct — see above). This means
`characterdata.dat`'s checksum-validated content is genuinely ephemeral
in this function: the real per-mobile stats consumer (if it re-reads or
re-derives this data) must live in a separate, not-yet-located function.

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

## `sound.xfs` container format — now fully confirmed

Follow-up from the previous pass: `InitDirectSound`/`InitDirectDraw` don't
build their own filenames internally (confirmed by scanning every
`PUSH`/`CALL`/`LEA` in both functions — no `.xfs` string literal anywhere in
either body), so the filename must be threaded in from the caller. Traced
that caller, `InitGame` (`0x40eaa0`), directly:

```c
BuildAssetPath(local_40c, &DAT_005b1ed0, "graphics.xfs", 0);
InitDirectDraw(local_40c);
...
BuildAssetPath(local_40c, &DAT_005b1ed0, "sound.xfs", 0);
InitDirectSound(param_1, 0x10, local_40c);
```

This **confirms `sound.xfs` uses the identical `BuildAssetPath` +
`OpenXFSArchive` path as `graphics.xfs`/`Avatar.xfs`** — `InitGame` builds
the `"sound.xfs"` path exactly the same way it builds `"graphics.xfs"`'s,
and passes it straight into `InitDirectSound` as its third parameter. All
three `.xfs` files (`graphics.xfs`, `sound.xfs`, `Avatar.xfs`) are now
independently confirmed to share the exact same `XFS2` container format —
this closes what was the last open item in the file-format identification
gap list (previously gap #5).

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

## Validation against real game files — corrections and a prototype decoder

Real copies of `graphics.xfs` (206 MB), `sound.xfs` (18.6 MB), and
`avatar.xfs` (122 KB) are now hashed and available locally (see
[README.md](README.md)) — earlier passes had incorrectly assumed these
weren't available. This let several static-analysis findings be checked
against actual bytes for the first time, rather than only against
decompiled code:

- **Terminology correction**: the parameter previously called a "key" in
  every `DecodeLZHUFBlock`/`DecodeXFSEntryBlock` call (`0x40`, `0x1000`,
  `0x20000`, `0x14c0`) is **not a cryptographic key at all** — re-reading
  the decompiled `DecodeLZHUFBlock` more carefully shows this value is
  written into the decode-state struct's first field and used directly as
  the **target decompressed output size**, checked against a running
  byte-decoded counter as the loop's termination condition. All references
  to "key" throughout this document have been corrected to "target output
  size" / "target decoded size."
- **Footer/header format confirmed against real bytes**: read the actual
  footer of `graphics.xfs` — `toc_offset = 206201330`, and the 4 bytes at
  that offset give `toc_compressed_size = 25`, matching the documented
  footer format exactly.
- **A prototype LZHUF decoder was implemented in Python**, checked into
  [tools/lzhuf/](tools/lzhuf/) (adapting the classic Okumura/Yoshizaki
  reference algorithm, using the constants confirmed earlier:
  `N_CHAR=314`, `T=627`, 4096-byte window) and used to
  decode the 25-byte compressed TOC header block from `graphics.xfs`. **It
  decoded correctly on the first real test**: output began with `"XFS2"`
  exactly as predicted, followed by a `uint32_t` at offset 4 (value `999`,
  meaning still unidentified) and a `uint32_t` at offset 8 (value `9313`) —
  this second field is the **total entry count**, confirmed by cross-
  checking against `OpenXFSArchive`'s decompiled chunk-count arithmetic
  (`9313 >> 10 = 9` full 1024-entry chunks + a 97-entry remainder, matching
  `9313 & 0x3ff = 97`). Two real transcription bugs were caught and fixed
  during this process (a match-length off-by-one, and wrong 64-entry
  position-decode tables where the correct reference tables have 256
  entries) — both fixes are reflected in the algorithm description earlier
  in this document.
- **Bug found and fixed — decoder now fully working.** The progressive
  desync described in earlier passes (first record clean, then rapid
  degradation into noise) turned out to be the `DecodePosition()` lookup
  table: what earlier passes transcribed as `p_code`/`p_len` was **not**
  the real decode-side `d_code`/`d_len` table from the reference
  `LZHUF.C` — it was some other, incorrect monotonic table that happened
  to be the right *size* (256 entries) but had entirely wrong *contents*
  (the real table is heavily many-to-one, collapsing many byte values onto
  the same 6-bit position — the whole point of a prefix-decode table —
  whereas the wrong table increased roughly one-to-one, more like an
  encode-side table). This explains the exact symptom: a wrong position
  table only breaks back-reference decoding (`DecodePosition`), not literal
  bytes (`DecodeChar`) — so the tiny 64-byte header (mostly-unique bytes,
  few back-references) decoded perfectly, while real archive entries
  (which compress well *because* of repeated back-references) hit the bug
  almost immediately. It also explains why cross-checking against an
  independent C port didn't catch it: both ports made the same table
  transcription mistake, so they agreed with each other while both being
  wrong.

  **Verified end-to-end against all three real `.xfs` files in `orig/`**:
  `graphics.xfs` (all 9,313 entries, every chunk, no degradation — and
  `ChooseEvent.txt` successfully extracted, see below), `sound.xfs` (all 96
  entries), `avatar.xfs` (all 8 entries — confirming the `f`/`m`-prefixed
  per-gender `.dat` files guessed at in [STRINGS.md](STRINGS.md)). Full
  writeup and the corrected tables: [tools/lzhuf/BUG_FOUND_wrong_decode_tables.md](tools/lzhuf/BUG_FOUND_wrong_decode_tables.md).
  `tools/lzhuf/lzhuf.py` now contains the fix; `tools/lzhuf/extract_toc.py`
  works correctly end-to-end. The original buggy tables are preserved at
  `tools/lzhuf/lzhuf_buggy_original.py.bak` for reference, and
  `tools/lzhuf/lzhuf_ref.c` (the C cross-check) still has the original bug
  and hasn't been fixed (not needed now that the real bug is found and
  fixed in the Python version actually used by `extract_toc.py`).

  **The `.dat` files also decode cleanly now** (same decoder, no
  container/TOC — just the raw file bytes, target size confirmed
  per-file via `LoadGameDataFiles`, see the summary table above):
  `itemdata.dat` (target `0x7850`) starts with the plaintext item name
  `"Dual"` followed by what reads as Portuguese item-description text
  later in the buffer (`"Usando este item voce pode dis..."` — "using this
  item you can dis[able/tribute]..."), `stage.dat` (target `0x3c80`)
  starts with the plaintext stage name `"Cave(Random)"`, and
  `characterdata.dat` (target `0x14c0`) decodes to sequences of small
  `uint32` values consistent with stat fields, though its field-level
  structure (which offset means what) hasn't been mapped yet.
  `specialdata.dat`'s correct target size wasn't confirmed this pass (its
  loader wasn't located) so it hasn't been properly re-decoded. The
  Portuguese text is a good clue about this particular game copy's
  origin/localization (the source folder name — see
  [README.md](README.md) — is a Brazilian Portuguese client build), useful
  context if the exact string content ever seems unexpected compared to an
  English-language GunBound client.

## Known gaps / good next targets

0. **Fully resolved**: the `.xfs` table-of-contents entry record layout is
   now completely mapped (128-byte records, sorted for binary search, name +
   mode-flag + file-offset + decompressed-size + compressed-size fields —
   see the dedicated section above, including the field that was still
   unidentified last pass). This was the missing piece for writing an
   actual extractor (previously only single-entry lookup by name was
   documented, not full-archive enumeration). Also discovered the archive
   format has a writer/insert code path in the client itself, not just a
   reader — see the dedicated note above; its caller/trigger wasn't traced.
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
   compressed (see above), with their own target-size convention and checksum
   convention, separate from both the TOC and the `.dat` files' schemes.
3. **Fully resolved — working decoder exists and is verified.** The entire
   LZHUF codec is confirmed structurally identical to the classic
   public-domain `LZHUF.C` reference (`N_CHAR=314`, `T=627`, 4096-byte
   window), a real bug in the decode-position table was found and fixed
   (see "Validation against real game files" above), and the decoder
   (`tools/lzhuf/lzhuf.py`) now cleanly decodes all three `.xfs` files in
   `orig/` end-to-end plus three of the four `.dat` files (each with its
   own confirmed target size, not a single shared constant as an earlier
   pass assumed — see `LoadGameDataFiles`), extracting real content
   (`ChooseEvent.txt`'s full text, `itemdata.dat`'s item names/Portuguese
   descriptions, `stage.dat`'s stage names). Nothing left to resolve at the
   algorithm level. Remaining work: mapping the last few unconfirmed
   *field-level* semantics within `characterdata.dat` (record count/stride
   now confirmed — 16 records × 332 bytes — and several early fields have
   plausible stat values, but exact field names aren't nailed down) and
   `itemdata.dat`'s decoded byte layout (not about decoding them, which now
   works), and finding `specialdata.dat`'s loader to get its correct
   target size (not located this pass — do not reuse `characterdata.dat`'s
   `0x14c0` for it without verifying against code first, the same mistake
   made earlier for `itemdata.dat`/`stage.dat`).
4. **Fully resolved.** `ChooseEvent.txt`'s actual content was extracted
   (see the dedicated section above): it's a tiny event-name-to-ID registry
   (`0=off, 1=christmas, 2=event2, 3=event3`), not the character-select
   animation/timing table earlier passes had guessed. The hash-table
   storage mechanism traced earlier (`ParseChooseEventLine` →
   `FUN_00426780`/`FUN_00409d10`) makes sense in this light: the event-name
   string is the hash key, the numeric ID is the stored value.
5. **Fully resolved**: `graphics.xfs`, `Avatar.xfs`, and now `sound.xfs`
   (confirmed by tracing `InitGame`'s direct `BuildAssetPath(..., "sound.xfs",
   ...)` → `InitDirectSound(..., path)` call, see the dedicated section
   above) are all independently confirmed to use the identical `XFS2`
   container format via `OpenXFSArchive`. No remaining unknowns in this item.
