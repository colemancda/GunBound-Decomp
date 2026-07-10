#!/usr/bin/env python3
"""Decode the avatar part tables inside Avatar.xfs.

Avatar.xfs (an XFS2 archive) holds 8 LZHUF-compressed part tables named
{gender}{category}.dat, gender in {f,m}, category in {b,g,h,f}:

    b = Body (clothing)     g = Glasses / eyes
    h = Head (hair/hat)     f = Flag  (only mf.dat is populated; ff.dat empty)

Each .dat is:  uint32 recordCount, then recordCount fixed 132 (0x84)-byte
records:  { uint32 id (== record index); char name[0x40]; char desc[0x40] }.

A part is referenced elsewhere by a 16-bit-ish equip code (see the avatar
compositor at 0x004141b0): bit 15 = gender (1=male 'm', 0=female 'f'),
bits 0..14 = the part id (this record index); 0xffffffff means "no part".
The drawn sprite is "{gender}{category}{id:05d}.img" in graphics.xfs
(plus a large "...l.img" variant); the flag sprite prefix is always "mf".

Usage:  python3 decode_avatar.py <Avatar.xfs> [--csv]
"""
import sys
import struct

sys.path.insert(0, __import__('os').path.dirname(__file__))
from extract_toc import read_toc
from decode_img import decode_entry_partial

RECORD_SIZE = 0x84  # 132 bytes: u32 id + name[0x40] + desc[0x40]

CATEGORY = {'b': 'Body', 'g': 'Glasses', 'h': 'Head', 'f': 'Flag'}
GENDER = {'m': 'Male', 'f': 'Female'}


def parse_part(blob):
    """Return (count, [(id, name, desc), ...]) for one decoded .dat blob."""
    if len(blob) < 4:
        return 0, []
    count = struct.unpack_from('<I', blob, 0)[0]
    recs = []
    for i in range(count):
        base = 4 + i * RECORD_SIZE
        pid = struct.unpack_from('<I', blob, base)[0]
        name = blob[base + 0x04:base + 0x44].split(b'\0')[0].decode('latin1')
        desc = blob[base + 0x44:base + 0x84].split(b'\0')[0].decode('latin1')
        recs.append((pid, name, desc))
    return count, recs


def load_all(xfs_path):
    """Decode every part table in the archive. Returns {entry_name: (count, recs)}."""
    entries, _, _, _ = read_toc(xfs_path)
    out = {}
    for name, mode, off, dsize, csize in entries:
        blob = decode_entry_partial(xfs_path, mode, off, dsize, csize, dsize)
        count, recs = parse_part(blob)
        # sanity: the record math must be exact for a real part table
        assert 4 + count * RECORD_SIZE == len(blob), \
            f'{name}: {count} recs * {RECORD_SIZE} + 4 != {len(blob)}'
        out[name] = (count, recs)
    return out


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    xfs_path = sys.argv[1]
    as_csv = '--csv' in sys.argv[2:]
    tables = load_all(xfs_path)
    if as_csv:
        print('file,gender,category,id,name,description')
        for fname, (count, recs) in tables.items():
            g = GENDER.get(fname[0], '?')
            c = CATEGORY.get(fname[1], '?')
            for pid, name, desc in recs:
                print(f'{fname},{g},{c},{pid},"{name}","{desc}"')
        return
    for fname, (count, recs) in tables.items():
        g = GENDER.get(fname[0], '?')
        c = CATEGORY.get(fname[1], '?')
        print(f'\n== {fname}  ({g} {c})  {count} records ==')
        for pid, name, desc in recs[:8]:
            print(f'  [{pid:3d}] {name:<24} {desc}')
        if count > 8:
            print(f'  ... (+{count - 8} more)')


if __name__ == '__main__':
    main()
