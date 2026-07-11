#!/usr/bin/env python3
"""Decode the avatar part tables inside Avatar.xfs.

Avatar.xfs (an XFS2 archive) holds 8 LZHUF-compressed part tables named
{gender}{category}.dat, gender in {f,m}, category in {b,g,h,f}:

    b = Body (clothing)     g = Glasses / eyes
    h = Head (hair/hat)     f = Flag  (only mf.dat is populated; ff.dat empty)

Each .dat is:  uint32 recordCount, then recordCount fixed 132 (0x84)-byte
records:  { uint32 id (== record index); char name[0x40]; char desc[0x40] }.

A part is referenced elsewhere by a 16-bit equip code (see the avatar
compositor at 0x004141b0): bit 15 = gender (1=male 'm', 0=female 'f'),
bits 0..14 = the part id (this record index); 0xffff/0xffffffff means "no part".
The drawn sprite is "{gender}{category}{id:05d}.img" in graphics.xfs
(plus a large "...l.img" variant); the flag sprite prefix is always "mf".

An 'avatarEquipped' value is a UInt64 packing FOUR of those u16 codes,
little-endian (see FILEFORMATS.md "Avatar.xfs"):
    word 0 (bits  0-15) = Body      (b)
    word 1 (bits 16-31) = Head      (h)
    word 2 (bits 32-47) = Glasses   (g)
    word 3 (bits 48-63) = Flag      (f)
Word order confirmed from ComposeAvatarSprites (0x4d1500): it composites
word0->%cb, word1->%ch, word2->%cg; word3 is the flag (drawn separately).

Usage:
  python3 decode_avatar.py <Avatar.xfs>            # dump the 8 part tables
  python3 decode_avatar.py <Avatar.xfs> --csv      # all rows as CSV
  python3 decode_avatar.py <Avatar.xfs> --equip <hex>   # split an avatarEquipped
                                                        # UInt64 into named parts
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


def decode_part_code(code):
    """Split one u16 equip code -> (gender_char, part_id) or (None, None) if empty."""
    code &= 0xffff
    if code == 0xffff:
        return None, None
    return ('m' if (code & 0x8000) else 'f'), (code & 0x7fff)


def part_name(tables, gender, cat, pid):
    """Look up a part's display name from the loaded tables, or '?' / '(none)'."""
    if gender is None:
        return '(none)'
    recs = tables.get(f'{gender}{cat}.dat', (0, []))[1]
    if 0 <= pid < len(recs):
        return recs[pid][1]
    return f'#{pid}'


def split_equipped(value):
    """Split an avatarEquipped UInt64 into its four little-endian u16 words."""
    return [(value >> (16 * i)) & 0xffff for i in range(4)]


def print_equipped(tables, value):
    words = split_equipped(value)
    print(f'avatarEquipped = 0x{value:016x}')
    # word order confirmed from ComposeAvatarSprites (0x4d1500)
    for idx, cat, label in ((0, 'b', 'Body   '), (1, 'h', 'Head   '),
                            (2, 'g', 'Glasses'), (3, 'f', 'Flag   ')):
        g, pid = decode_part_code(words[idx])
        gl = GENDER.get(g, '-')
        # the flag table is only populated under the 'mf' prefix
        lookup_g = 'm' if cat == 'f' else g
        print(f'  word{idx} (bits {idx*16:2d}-{idx*16+15}) {label} 0x{words[idx]:04x}'
              f'  {gl:<6} -> {part_name(tables, lookup_g, cat, pid)}')


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    xfs_path = sys.argv[1]
    argv = sys.argv[2:]
    as_csv = '--csv' in argv
    tables = load_all(xfs_path)
    if '--equip' in argv:
        raw = argv[argv.index('--equip') + 1]
        print_equipped(tables, int(raw, 16) if raw.lower().startswith('0x') else int(raw, 16))
        return
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
