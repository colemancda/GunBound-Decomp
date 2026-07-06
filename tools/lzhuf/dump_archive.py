"""
Bulk-extract every entry in a .xfs archive to a review directory.

For .img entries: decodes frame 0 to a PNG (ARGB4444, see decode_img.py).
Only decodes as many LZHUF output bytes as needed for the header + frame 0
pixel data (not the whole file), so this stays fast even for huge
multi-frame sheets like thor.img.

For everything else (.txt, .dat, .xes, etc.): writes the raw decoded bytes
to disk as-is.

Usage:
    python3 dump_archive.py /path/to/graphics.xfs /path/to/output_dir [limit]
"""
import os
import struct
import sys
import time

from lzhuf import decode_lzhuf
from extract_toc import read_toc

HEADER_AND_FRAME0_CAP = 1 << 20  # 1 MB ceiling; frame 0 of any sprite should be far under this


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


def safe_filename(name):
    return name.replace('/', '_').replace('\\', '_')


def dump_img_frame0(decoded_partial, out_path):
    from PIL import Image
    if len(decoded_partial) < 48:
        return False
    width = struct.unpack('<I', decoded_partial[12:16])[0]
    height = struct.unpack('<I', decoded_partial[16:20])[0]
    if width == 0 or height == 0 or width > 2048 or height > 2048:
        return False
    needed = 48 + width * height * 2
    if len(decoded_partial) < needed:
        return False
    pixel_bytes = decoded_partial[48:needed]
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
    img.save(out_path)
    return True


def main():
    if len(sys.argv) < 3:
        print(f'usage: {sys.argv[0]} <xfs_path> <output_dir> [limit]')
        sys.exit(1)
    xfs_path = sys.argv[1]
    out_dir = sys.argv[2]
    limit = int(sys.argv[3]) if len(sys.argv) > 3 else None

    os.makedirs(out_dir, exist_ok=True)
    entries, filesize, toc_offset, entry_count = read_toc(xfs_path)
    if limit:
        entries = entries[:limit]

    t0 = time.time()
    ok_img = 0
    ok_raw = 0
    failed = 0
    for i, (name, mode_flag, file_offset, decompressed_size, compressed_size) in enumerate(entries):
        fname = safe_filename(name)
        try:
            if name.lower().endswith('.img'):
                partial = decode_entry_partial(xfs_path, mode_flag, file_offset,
                                                decompressed_size, compressed_size,
                                                HEADER_AND_FRAME0_CAP)
                out_path = os.path.join(out_dir, fname + '.png')
                if dump_img_frame0(partial, out_path):
                    ok_img += 1
                else:
                    failed += 1
            else:
                data = decode_entry_partial(xfs_path, mode_flag, file_offset,
                                             decompressed_size, compressed_size,
                                             decompressed_size)
                out_path = os.path.join(out_dir, fname)
                with open(out_path, 'wb') as f:
                    f.write(data)
                ok_raw += 1
        except Exception as e:
            failed += 1
        if (i + 1) % 500 == 0:
            elapsed = time.time() - t0
            print(f'{i+1}/{len(entries)} processed ({elapsed:.1f}s elapsed, '
                  f'{ok_img} imgs, {ok_raw} raw, {failed} failed)')

    elapsed = time.time() - t0
    print(f'DONE: {len(entries)} entries in {elapsed:.1f}s — '
          f'{ok_img} images, {ok_raw} raw files, {failed} failed')


if __name__ == '__main__':
    main()
