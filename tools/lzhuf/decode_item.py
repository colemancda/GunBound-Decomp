#!/usr/bin/env python3
"""Decode orig/itemdata.dat and resolve the battle-item ordinals.

itemdata.dat is a flat LZHUF-compressed file (target 0x7850 = 100 records of
308 bytes; only ~13 populated in this build). Record layout (see FILEFORMATS.md):
    0x00  char[0x20]  name (NUL-terminated; a couple are Korean mojibake)
    0x24  uint32      price
    0x28  uint32      item type/family id
    0x30  uint16      packed shelf-icon code (same packing as DAT_0056dc40)
    0x32  ...         localized description

The runtime item bar/shelf is indexed by an *item ordinal* (= item-ownership
bitmask bit, ctx+0x457a1), and DAT_0056dc40[ordinal] is that ordinal's icon code.
Matching each ordinal's icon code back to a record's 0x30 recovers which item each
ordinal is -- entirely from client data. Ordinals 0-10 are the battle items.

Usage:  python3 decode_item.py [orig/itemdata.dat]
"""
import sys, os, struct
sys.path.insert(0, os.path.dirname(__file__))
from lzhuf import decode_lzhuf

REC = 308
OUT = 0x7850

# DAT_0056dc40 @ 0x56dc40 - the 40-entry shelf-icon table, verbatim from the binary
# (low byte = icon-pair index, high byte 0x00/0xff = icon-sheet texture 0x2713/0x2714)
DAT_0056DC40 = [
    0xff01, 0x0003, 0xff07, 0x0007, 0xff02, 0x000f, 0xff0b, 0x0001,
    0x0002, 0xff06, 0xff0a, 0xff04, 0xff05, 0x0006, 0xff08, 0xff09,
    0x0008, 0x0009, 0x0003, 0x000b, 0x000c, 0x000d, 0x000e, 0x0004,
    0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017,
    0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0xff0a, 0x001d, 0x0005,
]


def parse(path):
    raw = open(path, 'rb').read()
    data = decode_lzhuf(raw, OUT)
    items = []  # (record_index, name, price, type, icon_code)
    for i in range(OUT // REC):
        r = data[i * REC:(i + 1) * REC]
        if len(r) < 0x34:
            break
        name = r[0:0x20].split(b'\0')[0].decode('latin1', 'replace')
        if not name.strip('\x00 '):
            continue
        price = struct.unpack_from('<I', r, 0x24)[0]
        typ = struct.unpack_from('<I', r, 0x28)[0]
        icon = struct.unpack_from('<H', r, 0x30)[0]
        items.append((i, name, price, typ, icon))
    return items


def main(argv):
    path = argv[1] if len(argv) > 1 else 'orig/itemdata.dat'
    items = parse(path)
    by_icon = {icon: name for (_, name, _, _, icon) in items}

    print(f'itemdata.dat: {len(items)} populated records')
    print(f"{'rec':>3} {'name':<16} {'price':>6} {'type':>4} {'icon':>6}")
    for i, name, price, typ, icon in items:
        print(f'{i:>3} {name[:16]:<16} {price:>6} {typ:>4} 0x{icon:04x}')

    print('\nitem ordinal -> icon (DAT_0056dc40) -> item name:')
    print(f"{'ord':>3} {'icon':>6}  item")
    for ordn, icon in enumerate(DAT_0056DC40):
        tag = '  (battle item)' if ordn <= 10 else ''
        print(f'{ordn:>3} 0x{icon:04x}  {by_icon.get(icon, "-- (not in this build)")}{tag}')


if __name__ == '__main__':
    main(sys.argv)
