"""
Decode a GunBound .img sprite entry (from graphics.xfs) to a PNG.

Confirmed header format (first frame at least — see FILEFORMATS.md):
    offset 0x00 (4 bytes): unknown/flags, 0 in all samples tested
    offset 0x04 (4 bytes): frame count (1 for single-frame sprites)
    offset 0x08 (4 bytes): unknown, varies
    offset 0x0c (4 bytes): width (pixels)
    offset 0x10 (4 bytes): height (pixels)
    offset 0x14 (4 bytes): signed, likely X hotspot/origin offset
    offset 0x18 (4 bytes): signed, likely Y hotspot/origin offset
    offset 0x1c-0x2b (16 bytes): unidentified
    offset 0x2c (4 bytes): pixel data byte count for this frame (width*height*2)
    offset 0x30 onward: raw ARGB4444 pixel data, row-major, width*height*2 bytes
    (4 bits alpha / 4 bits red / 4 bits green / 4 bits blue)

    Confirmed via three independent samples compared against a real
    reference screenshot of the mobile-select screen. Two earlier guesses
    were tried and rejected before this one:
      - RGB565 (5/6/5): recognizable shape, visibly wrong hue (yellow/pink
        instead of orange/red).
      - RGB555 (5/5/5, top bit unused): better, but treads/wheels that
        should be gray rendered as pink/tan, with stray magenta-ish noise.
      - ARGB4444: correct. The giveaway was that every common pixel value
        in a real sample had its top hex digit == 0xf — not a coincidental
        "red channel maxed" pattern, but the alpha nibble reading as fully
        opaque. Decoding the remaining 3 nibbles as R/G/B (4 bits each)
        produces correct-looking colors including proper gray metal
        (treads/wheels) and clean transparency at sprite edges (no more
        solid-black or magenta-fringed backgrounds).

Only the first frame's layout is confirmed. Multi-frame sheets (tank1.img,
thor.img, etc.) have more frames following, but the exact per-frame repeat
structure beyond frame 0 hasn't been mapped yet.

Usage:
    python3 decode_img.py /path/to/graphics.xfs <entry_name> output.png
"""
import struct
import sys

from lzhuf import decode_lzhuf
from extract_toc import read_toc


def decode_img_frame0(decoded: bytes):
    frame_count = struct.unpack('<I', decoded[4:8])[0]
    width = struct.unpack('<I', decoded[12:16])[0]
    height = struct.unpack('<I', decoded[16:20])[0]
    hotspot_x = struct.unpack('<i', decoded[20:24])[0]
    hotspot_y = struct.unpack('<i', decoded[24:28])[0]
    pixel_byte_count = struct.unpack('<I', decoded[44:48])[0]
    pixel_start = 48
    pixel_bytes = decoded[pixel_start:pixel_start + width * height * 2]
    return {
        'frame_count': frame_count,
        'width': width,
        'height': height,
        'hotspot_x': hotspot_x,
        'hotspot_y': hotspot_y,
        'pixel_byte_count': pixel_byte_count,
        'pixel_bytes': pixel_bytes,
    }


def argb4444_to_rgba8888(pixel_bytes: bytes, width: int, height: int):
    from PIL import Image
    img = Image.new('RGBA', (width, height))
    px = img.load()
    for y in range(height):
        for x in range(width):
            idx = (y * width + x) * 2
            val = struct.unpack('<H', pixel_bytes[idx:idx + 2])[0]
            a = (val >> 12) & 0xf
            r = (val >> 8) & 0xf
            g = (val >> 4) & 0xf
            b = val & 0xf
            px[x, y] = (r * 17, g * 17, b * 17, a * 17)
    return img


def extract_entry(xfs_path: str, entry_name: str) -> bytes:
    entries, _, _, _ = read_toc(xfs_path)
    match = next((e for e in entries if e[0].lower() == entry_name.lower()), None)
    if match is None:
        raise KeyError(f'entry {entry_name!r} not found in {xfs_path}')
    name, mode_flag, file_offset, decompressed_size, compressed_size = match
    with open(xfs_path, 'rb') as f:
        if mode_flag == 1:
            f.seek(file_offset)
            return f.read(decompressed_size)
        f.seek(file_offset)
        real_compressed_size, checksum = struct.unpack('<II', f.read(8))
        cdata = f.read(real_compressed_size)
        return decode_lzhuf(cdata, decompressed_size)


if __name__ == '__main__':
    if len(sys.argv) != 4:
        print(f'usage: {sys.argv[0]} <graphics.xfs> <entry_name> <output.png>')
        sys.exit(1)
    xfs_path, entry_name, out_path = sys.argv[1:4]
    decoded = extract_entry(xfs_path, entry_name)
    frame = decode_img_frame0(decoded)
    print(f"{entry_name}: {frame['width']}x{frame['height']}, "
          f"frame_count={frame['frame_count']}, "
          f"hotspot=({frame['hotspot_x']},{frame['hotspot_y']})")
    img = argb4444_to_rgba8888(frame['pixel_bytes'], frame['width'], frame['height'])
    img.save(out_path)
    print(f'saved {out_path}')
