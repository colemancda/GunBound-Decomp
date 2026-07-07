"""
Decode a GunBound .img sprite entry (from graphics.xfs) to a PNG.

Confirmed header format (frame 0 — see FILEFORMATS.md):
    offset 0x00 (4 bytes): unknown/flags, 0 in all samples tested
    offset 0x04 (4 bytes): frame count (1 for single-frame sprites)
    offset 0x08 (4 bytes): transparencyType — the real per-frame pixel-format
        selector (low byte only matters):
            0 = flat row-major RGB565, always opaque
            1 = sparse per-scanline run list of RGB565 pixels
            2 = flat row-major ARGB4444 (alpha channel included)
        **Correction**: an earlier pass assumed ARGB4444 unconditionally and
        inferred flat-vs-sparse purely from comparing the declared byte count
        against width*height*2. That heuristic happened to work for the
        specific sample files spot-checked at the time (tank1.img,
        bullet1n.img, both genuinely ARGB4444) but was never checked against
        the *actual* per-frame selector — confirmed wrong for ~46% of real
        entries (see below), including two files this project had checked in
        as "verified" ARGB4444 examples (avataimsi.img, presentmode.img —
        both actually RGB565). Archive-wide distribution across graphics.xfs
        (8,926 valid .img entries): 54.4% ARGB4444 (type 2), 40.6% sparse
        RGB565 (type 1), 5.1% flat RGB565 (type 0).
    offset 0x0c (4 bytes): width (pixels)
    offset 0x10 (4 bytes): height (pixels)
    offset 0x14 (4 bytes): signed, likely X hotspot/origin offset
    offset 0x18 (4 bytes): signed, likely Y hotspot/origin offset
    offset 0x1c-0x2b (16 bytes): unidentified
    offset 0x2c (4 bytes): total pixel-run data byte count for this frame
    offset 0x30 onward: pixel data for frame 0, in ONE of two confirmed
        sub-formats (selected by transparencyType, NOT inferred from size):

    (a) Flat array: width*height pixels, row-major, no encoding. RGB565 for
        transparencyType 0, ARGB4444 for transparencyType 2.

    (b) Sparse per-scanline run list (transparencyType 1; the format
        `BlitSprite16bpp` actually implements — re-confirmed via a fresh
        decompile of that function): for each of `height` rows, starting
        right after the previous row:
            [stride:u16] [run_count:u16]
            then run_count spans of:
                [x_offset:u16] [length:u16] [length RGB565 pixels]
        `stride` is the distance (in u16 units, from the row's own start)
        to the next row. Pixels not covered by any run are fully
        transparent. A `stride` of 0 terminates the row list early (seen
        in large sprites where most of the declared canvas is empty).
        Confirmed structurally by manually verifying rows in `presentmode.img`
        (stride matches actual byte consumption) AND confirmed for pixel
        *color* correctness by rendering it end-to-end as RGB565 and getting
        a clean, correctly-colored gift-box icon (matching the filename) —
        the same bytes decoded as ARGB4444 do not produce a sane image.

    Note on a competing hypothesis: an independent Swift reimplementation
    (github.com/colemancda's `Gunbound` package) uses a structurally
    different row algorithm for the sparse case (alternating
    "alpha-run/color-run" pair counts, rather than this stride/run_count/
    x_offset+length shape). Re-decompiling `BlitSprite16bpp` fresh confirms
    the stride/run_count/x_offset+length shape documented here is what the
    real game client executes — the alpha/color-run algorithm doesn't match
    any code path found in `GunBound.gme`. That Swift implementation's
    *correct* contribution was recognizing that pixel format is chosen per
    frame by a real `transparencyType` field rather than inferred from byte
    counts; its specific sparse row-walking algorithm is not confirmed to
    match this client.

Only frame 0 is decoded. Multi-frame sheets (tank1.img, thor.img, etc.)
have more frames following, but the per-frame repeat structure beyond
frame 0 hasn't been mapped (see FILEFORMATS.md's open-questions section).

Usage:
    python3 decode_img.py /path/to/graphics.xfs <entry_name> output.png
"""
import struct
import sys

from lzhuf import decode_lzhuf
from extract_toc import read_toc

HEADER_PEEK = 64  # enough to read width/height at offsets 12/16


def extract_entry(xfs_path: str, entry_name: str):
    entries, _, _, _ = read_toc(xfs_path)
    match = next((e for e in entries if e[0].lower() == entry_name.lower()), None)
    if match is None:
        raise KeyError(f'entry {entry_name!r} not found in {xfs_path}')
    return match


def decode_entry_partial(xfs_path, mode_flag, file_offset, decompressed_size, compressed_size, want_bytes):
    """Decode only the first `want_bytes` of an entry's decompressed content."""
    want_bytes = min(want_bytes, decompressed_size)
    with open(xfs_path, 'rb') as f:
        if mode_flag == 1:
            f.seek(file_offset)
            return f.read(want_bytes)
        f.seek(file_offset)
        real_compressed_size, checksum = struct.unpack('<II', f.read(8))
        cdata = f.read(real_compressed_size)
        return decode_lzhuf(cdata, want_bytes)


def _rgb565_pixel(val):
    r = (val >> 11) & 0x1f
    g = (val >> 5) & 0x3f
    b = val & 0x1f
    return (r * 255 // 31, g * 255 // 63, b * 255 // 31, 255)


def _argb4444_pixel(val):
    a = (val >> 12) & 0xf
    r = (val >> 8) & 0xf
    g = (val >> 4) & 0xf
    b = val & 0xf
    return (r * 17, g * 17, b * 17, a * 17)


# transparencyType values, confirmed via GunBound.gme's ImageDecoder-equivalent
# and cross-checked against InsideGB.exe's independent C# reimplementation.
TRANSPARENCY_NONE = 0   # flat RGB565, always opaque
TRANSPARENCY_SIMPLE = 1  # sparse run-list of RGB565 pixels
TRANSPARENCY_ALPHA = 2   # flat ARGB4444


def decode_frame0_rows(decoded: bytes, width: int, height: int, pixel_byte_count: int,
                        transparency_type: int, row_data_start: int = 48):
    """
    Returns a list of `height` rows, each a list of `width` (R,G,B,A) tuples.
    Uses the real per-frame transparencyType selector, not a size heuristic.
    """
    flat_size = width * height * 2
    end = min(row_data_start + pixel_byte_count, len(decoded))

    if transparency_type in (TRANSPARENCY_NONE, TRANSPARENCY_ALPHA):
        pixel_fn = _rgb565_pixel if transparency_type == TRANSPARENCY_NONE else _argb4444_pixel
        pixel_bytes = decoded[row_data_start:min(row_data_start + flat_size, end)]
        rows = []
        for y in range(height):
            row = []
            for x in range(width):
                idx = (y * width + x) * 2
                if idx + 2 > len(pixel_bytes):
                    row.append((0, 0, 0, 0))
                    continue
                val = struct.unpack('<H', pixel_bytes[idx:idx + 2])[0]
                row.append(pixel_fn(val))
            rows.append(row)
        return rows

    # Sparse per-scanline run list (transparencyType == 1), RGB565 pixels.
    # Structure confirmed directly from BlitSprite16bpp's disassembly:
    # [stride:u16][run_count:u16] then run_count x [x_offset:u16][length:u16][length pixels].
    pos = row_data_start
    rows = []
    for y in range(height):
        row = [(0, 0, 0, 0)] * width
        if pos + 4 > end:
            rows.append(row)
            continue
        stride = struct.unpack('<H', decoded[pos:pos + 2])[0]
        run_count = struct.unpack('<H', decoded[pos + 2:pos + 4])[0]
        run_ptr = pos + 4
        for _ in range(run_count):
            if run_ptr + 4 > end:
                break
            x_off = struct.unpack('<H', decoded[run_ptr:run_ptr + 2])[0]
            length = struct.unpack('<H', decoded[run_ptr + 2:run_ptr + 4])[0]
            run_ptr += 4
            for k in range(length):
                if run_ptr + 2 > end:
                    break
                val = struct.unpack('<H', decoded[run_ptr:run_ptr + 2])[0]
                xi = x_off + k
                if 0 <= xi < width:
                    row[xi] = _rgb565_pixel(val)
                run_ptr += 2
        rows.append(row)
        if stride == 0:
            # Terminator: no more rows have data: fill remainder transparent.
            for _ in range(y + 1, height):
                rows.append([(0, 0, 0, 0)] * width)
            break
        pos = pos + stride * 2
    return rows


def decode_img_frame0(decoded: bytes):
    frame_count = struct.unpack('<I', decoded[4:8])[0]
    transparency_type_raw = struct.unpack('<i', decoded[8:12])[0]
    transparency_type = transparency_type_raw & 0xff
    width = struct.unpack('<I', decoded[12:16])[0]
    height = struct.unpack('<I', decoded[16:20])[0]
    hotspot_x = struct.unpack('<i', decoded[20:24])[0]
    hotspot_y = struct.unpack('<i', decoded[24:28])[0]
    pixel_byte_count = struct.unpack('<I', decoded[44:48])[0]
    return {
        'frame_count': frame_count,
        'transparency_type': transparency_type,
        'width': width,
        'height': height,
        'hotspot_x': hotspot_x,
        'hotspot_y': hotspot_y,
        'pixel_byte_count': pixel_byte_count,
    }


def rows_to_image(rows, width, height):
    from PIL import Image
    img = Image.new('RGBA', (width, height))
    px = img.load()
    for y, row in enumerate(rows):
        for x, rgba in enumerate(row):
            px[x, y] = rgba
    return img


if __name__ == '__main__':
    if len(sys.argv) != 4:
        print(f'usage: {sys.argv[0]} <graphics.xfs> <entry_name> <output.png>')
        sys.exit(1)
    xfs_path, entry_name, out_path = sys.argv[1:4]
    name, mode_flag, file_offset, decompressed_size, compressed_size = extract_entry(xfs_path, entry_name)
    header = decode_entry_partial(xfs_path, mode_flag, file_offset, decompressed_size, compressed_size, HEADER_PEEK)
    frame = decode_img_frame0(header)
    print(f"{entry_name}: {frame['width']}x{frame['height']}, "
          f"frame_count={frame['frame_count']}, "
          f"transparencyType={frame['transparency_type']}, "
          f"hotspot=({frame['hotspot_x']},{frame['hotspot_y']}), "
          f"pixel_byte_count={frame['pixel_byte_count']}")
    needed = 48 + frame['pixel_byte_count']
    decoded = decode_entry_partial(xfs_path, mode_flag, file_offset, decompressed_size, compressed_size, needed)
    rows = decode_frame0_rows(
        decoded, frame['width'], frame['height'], frame['pixel_byte_count'], frame['transparency_type']
    )
    img = rows_to_image(rows, frame['width'], frame['height'])
    img.save(out_path)
    print(f'saved {out_path}')
