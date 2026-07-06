"""
Decode a GunBound .img sprite entry (from graphics.xfs) to a PNG.

Confirmed header format (frame 0 — see FILEFORMATS.md):
    offset 0x00 (4 bytes): unknown/flags, 0 in all samples tested
    offset 0x04 (4 bytes): frame count (1 for single-frame sprites)
    offset 0x08 (4 bytes): unknown, varies
    offset 0x0c (4 bytes): width (pixels)
    offset 0x10 (4 bytes): height (pixels)
    offset 0x14 (4 bytes): signed, likely X hotspot/origin offset
    offset 0x18 (4 bytes): signed, likely Y hotspot/origin offset
    offset 0x1c-0x2b (16 bytes): unidentified
    offset 0x2c (4 bytes): total pixel-run data byte count for this frame
    offset 0x30 onward: pixel data for frame 0, in ONE of two confirmed
        sub-formats:

    (a) Flat array: width*height ARGB4444 pixels, row-major, no encoding.
        Detected when 0x2c's byte count exactly equals width*height*2.

    (b) Sparse per-scanline run list (the format `BlitSprite16bpp` actually
        implements): for each of `height` rows, starting right after the
        previous row:
            [stride:u16] [run_count:u16]
            then run_count spans of:
                [x_offset:u16] [length:u16] [length ARGB4444 pixels]
        `stride` is the distance (in u16 units, from the row's own start)
        to the next row. Pixels not covered by any run are fully
        transparent. A `stride` of 0 terminates the row list early (seen
        in large sprites where most of the declared canvas is empty).

    Confirmed via multiple real samples, comparing decoded colors against
    a real reference screenshot of the mobile-select screen. Two pixel
    formats were tried and rejected before ARGB4444:
      - RGB565 (5/6/5): recognizable shape, visibly wrong hue.
      - RGB555 (5/5/5, top bit unused): better, but treads/wheels that
        should be gray rendered pink/tan, with magenta-ish noise.
      - ARGB4444: correct. Every common pixel value's top hex digit was
        `0xf` in real samples — the alpha nibble reading fully opaque,
        not a coincidental "red channel maxed" pattern.

Only frame 0 is decoded. Multi-frame sheets (tank1.img, thor.img, etc.)
have more frames following, but the per-frame repeat structure beyond
frame 0 hasn't been mapped.

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


def _nibble_pixel(val):
    a = (val >> 12) & 0xf
    r = (val >> 8) & 0xf
    g = (val >> 4) & 0xf
    b = val & 0xf
    return (r * 17, g * 17, b * 17, a * 17)


def decode_frame0_rows(decoded: bytes, width: int, height: int, pixel_byte_count: int,
                        row_data_start: int = 48):
    """
    Returns a list of `height` rows, each a list of `width` (R,G,B,A) tuples.
    Auto-detects flat vs. sparse storage.
    """
    flat_size = width * height * 2
    if pixel_byte_count == flat_size and row_data_start + flat_size <= len(decoded):
        pixel_bytes = decoded[row_data_start:row_data_start + flat_size]
        rows = []
        for y in range(height):
            row = []
            for x in range(width):
                idx = (y * width + x) * 2
                val = struct.unpack('<H', pixel_bytes[idx:idx + 2])[0]
                row.append(_nibble_pixel(val))
            rows.append(row)
        return rows

    # Sparse per-scanline run list.
    end = min(row_data_start + pixel_byte_count, len(decoded))
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
                    row[xi] = _nibble_pixel(val)
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
    width = struct.unpack('<I', decoded[12:16])[0]
    height = struct.unpack('<I', decoded[16:20])[0]
    hotspot_x = struct.unpack('<i', decoded[20:24])[0]
    hotspot_y = struct.unpack('<i', decoded[24:28])[0]
    pixel_byte_count = struct.unpack('<I', decoded[44:48])[0]
    return {
        'frame_count': frame_count,
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
          f"hotspot=({frame['hotspot_x']},{frame['hotspot_y']}), "
          f"pixel_byte_count={frame['pixel_byte_count']}")
    needed = 48 + frame['pixel_byte_count']
    decoded = decode_entry_partial(xfs_path, mode_flag, file_offset, decompressed_size, compressed_size, needed)
    rows = decode_frame0_rows(decoded, frame['width'], frame['height'], frame['pixel_byte_count'])
    img = rows_to_image(rows, frame['width'], frame['height'])
    img.save(out_path)
    print(f'saved {out_path}')
