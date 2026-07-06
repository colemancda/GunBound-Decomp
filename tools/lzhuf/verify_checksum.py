"""
Verify a decoded .xfs entry against its own embedded integrity checksum.

Confirmed via decompiling GunBound.gme's DecodeXFSEntryBlock (0x4f03f0):
after LZHUF-decoding an entry, the client validates it by summing every
32-bit little-endian word in the first 4096 bytes of the decoded output
(mod 2**32) and comparing against a checksum stored in the entry's own
XFSEntryBlock header (the second uint32, right after compressedSize).

This is a strong correctness check independent of file type — useful any
time there's doubt about whether a decoded entry is bit-for-bit right
(e.g. this caught nothing wrong with the LZHUF port itself when a
multi-frame .img parsing bug was suspected to be a decompression bug).

Usage:
    python3 verify_checksum.py <xfs_path> <entry_name>
"""
import struct
import sys

from extract_toc import read_toc
from lzhuf import decode_lzhuf


def compute_checksum(decoded: bytes) -> int:
    n = min(4096, len(decoded) - (len(decoded) % 4))
    total = 0
    for i in range(0, n, 4):
        total = (total + struct.unpack('<i', decoded[i:i + 4])[0]) & 0xffffffff
    return total


def verify_entry(xfs_path, name, mode_flag, file_offset, decompressed_size, compressed_size):
    with open(xfs_path, 'rb') as f:
        f.seek(file_offset)
        if mode_flag == 1:
            # Raw entries have no XFSEntryBlock header/checksum to check against.
            return None, None
        real_compressed_size, checksum = struct.unpack('<II', f.read(8))
        cdata = f.read(real_compressed_size)
        decoded = decode_lzhuf(cdata, decompressed_size)
    return checksum, compute_checksum(decoded)


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print(f'usage: {sys.argv[0]} <xfs_path> <entry_name>')
        sys.exit(1)
    xfs_path, entry_name = sys.argv[1:3]
    entries, _, _, _ = read_toc(xfs_path)
    match = next((e for e in entries if e[0].lower() == entry_name.lower()), None)
    if match is None:
        raise KeyError(f'entry {entry_name!r} not found')
    stored, computed = verify_entry(xfs_path, *match)
    if stored is None:
        print(f'{entry_name}: stored raw (mode_flag=1), no checksum to verify')
    else:
        status = 'MATCH' if stored == computed else 'MISMATCH'
        print(f'{entry_name}: stored=0x{stored:08x} computed=0x{computed:08x} {status}')
