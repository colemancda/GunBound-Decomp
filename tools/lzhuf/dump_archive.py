"""
Bulk-extract every entry in a .xfs archive to a review directory.

For .img entries: decodes frame 0 to a PNG using decode_img.py's unified
flat/sparse decoder. Only decodes as many LZHUF output bytes as needed for
the header + frame 0 (not the whole file), so this stays fast even for
huge multi-frame sheets.

For everything else (.txt, .dat, .xes, etc.): writes the raw decoded bytes
to disk as-is.

Usage:
    python3 dump_archive.py /path/to/graphics.xfs /path/to/output_dir [limit]
"""
import os
import sys
import time

from decode_img import (HEADER_PEEK, decode_entry_partial, decode_img_frame0,
                         decode_frame0_rows, rows_to_image)
from extract_toc import read_toc


def safe_filename(name):
    return name.replace('/', '_').replace('\\', '_')


def dump_img_frame0(xfs_path, mode_flag, file_offset, decompressed_size, compressed_size, out_path):
    header = decode_entry_partial(xfs_path, mode_flag, file_offset, decompressed_size,
                                   compressed_size, HEADER_PEEK)
    if len(header) < 48:
        return 'too_short_header'
    frame = decode_img_frame0(header)
    width, height = frame['width'], frame['height']
    if width == 0 or height == 0 or width > 4096 or height > 4096:
        return 'bad_dims'
    needed = 48 + frame['pixel_byte_count']
    decoded = decode_entry_partial(xfs_path, mode_flag, file_offset, decompressed_size,
                                    compressed_size, needed)
    rows = decode_frame0_rows(decoded, width, height, frame['pixel_byte_count'])
    img = rows_to_image(rows, width, height)
    img.save(out_path)
    return 'ok'


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
    status_counts = {}
    exceptions = 0
    for i, (name, mode_flag, file_offset, decompressed_size, compressed_size) in enumerate(entries):
        fname = safe_filename(name)
        try:
            if name.lower().endswith('.img'):
                out_path = os.path.join(out_dir, fname + '.png')
                status = dump_img_frame0(xfs_path, mode_flag, file_offset,
                                          decompressed_size, compressed_size, out_path)
                if status == 'ok':
                    ok_img += 1
                else:
                    status_counts[status] = status_counts.get(status, 0) + 1
            else:
                data = decode_entry_partial(xfs_path, mode_flag, file_offset,
                                             decompressed_size, compressed_size,
                                             decompressed_size)
                out_path = os.path.join(out_dir, fname)
                with open(out_path, 'wb') as f:
                    f.write(data)
                ok_raw += 1
        except Exception as e:
            exceptions += 1
        if (i + 1) % 500 == 0:
            elapsed = time.time() - t0
            failed_total = sum(status_counts.values()) + exceptions
            print(f'{i+1}/{len(entries)} processed ({elapsed:.1f}s elapsed, '
                  f'{ok_img} imgs, {ok_raw} raw, {failed_total} failed)')

    elapsed = time.time() - t0
    failed_total = sum(status_counts.values()) + exceptions
    print(f'DONE: {len(entries)} entries in {elapsed:.1f}s — '
          f'{ok_img} images, {ok_raw} raw files, {failed_total} failed')
    print('Failure breakdown:', dict(status_counts), 'exceptions:', exceptions)


if __name__ == '__main__':
    main()
