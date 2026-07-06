"""
Parse RT_DIALOG resources out of a PE file, dumping each dialog's control
IDs, window classes, and caption text (static analysis only, no execution).
"""
import struct
import sys

import pefile

RT_DIALOG = 5


def read_sz_or_ord(data, off):
    val = struct.unpack_from('<H', data, off)[0]
    if val == 0x0000:
        return off + 2, None
    if val == 0xFFFF:
        ordv = struct.unpack_from('<H', data, off + 2)[0]
        return off + 4, f'#{ordv}'
    # null-terminated UTF-16LE string
    start = off
    while struct.unpack_from('<H', data, off)[0] != 0:
        off += 2
    off += 2
    s = data[start:off - 2].decode('utf-16-le', errors='replace')
    return off, s


def align4(off):
    return (off + 3) & ~3


def parse_dialog(data):
    items = []
    dlgVer, signature = struct.unpack_from('<HH', data, 0)
    if signature == 0xFFFF:
        # DIALOGEX
        off = 8  # dlgVer, signature, helpID(4)... wait recompute
        helpID, exStyle, style = struct.unpack_from('<III', data, 4)
        off = 16
        cDlgItems, x, y, cx, cy = struct.unpack_from('<Hhhhh', data, off)
        off += 10
        off, menu = read_sz_or_ord(data, off)
        off, wclass = read_sz_or_ord(data, off)
        off, title = read_sz_or_ord(data, off)
        if style & 0x40:  # DS_SETFONT
            pointsize, weight = struct.unpack_from('<HH', data, off)
            off += 4
            italic = data[off]
            off += 1
            charset = data[off]
            off += 1
            off, typeface = read_sz_or_ord(data, off)
        off = align4(off)
        for _ in range(cDlgItems):
            helpID, exStyle, style = struct.unpack_from('<III', data, off)
            off += 12
            ix, iy, icx, icy = struct.unpack_from('<hhhh', data, off)
            off += 8
            item_id = struct.unpack_from('<I', data, off)[0]
            off += 4
            off, iclass = read_sz_or_ord(data, off)
            off, ititle = read_sz_or_ord(data, off)
            extraCount = struct.unpack_from('<H', data, off)[0]
            off += 2 + extraCount
            off = align4(off)
            items.append((item_id, iclass, ititle))
        return 'DIALOGEX', title, items
    else:
        # classic DIALOG
        off = 0
        style, exStyle = struct.unpack_from('<II', data, off)
        off += 8
        cdit, x, y, cx, cy = struct.unpack_from('<Hhhhh', data, off)
        off += 10
        off, menu = read_sz_or_ord(data, off)
        off, wclass = read_sz_or_ord(data, off)
        off, title = read_sz_or_ord(data, off)
        if style & 0x40:
            pointsize = struct.unpack_from('<H', data, off)[0]
            off += 2
            off, typeface = read_sz_or_ord(data, off)
        off = align4(off)
        for _ in range(cdit):
            style, exStyle = struct.unpack_from('<II', data, off)
            off += 8
            ix, iy, icx, icy = struct.unpack_from('<hhhh', data, off)
            off += 8
            item_id = struct.unpack_from('<H', data, off)[0]
            off += 2
            off, iclass = read_sz_or_ord(data, off)
            off, ititle = read_sz_or_ord(data, off)
            extraCount = struct.unpack_from('<H', data, off)[0]
            off += 2 + extraCount
            off = align4(off)
            items.append((item_id, iclass, ititle))
        return 'DIALOG', title, items


def main(path):
    pe = pefile.PE(path)
    pe.parse_data_directories()
    if not hasattr(pe, 'DIRECTORY_ENTRY_RESOURCE'):
        print('no resources')
        return
    for entry in pe.DIRECTORY_ENTRY_RESOURCE.entries:
        type_id = entry.id if entry.name is None else str(entry.name)
        if type_id != RT_DIALOG:
            continue
        for name_entry in entry.directory.entries:
            dlg_name = name_entry.id if name_entry.name is None else str(name_entry.name)
            for lang_entry in name_entry.directory.entries:
                rva = lang_entry.data.struct.OffsetToData
                size = lang_entry.data.struct.Size
                data = pe.get_data(rva, size)
                try:
                    kind, title, items = parse_dialog(data)
                except Exception as e:
                    print(f'DIALOG id={dlg_name}: PARSE ERROR {e}')
                    continue
                print(f'\n=== DIALOG id={dlg_name} ({kind}) title={title!r} ===')
                for item_id, iclass, ititle in items:
                    print(f'    id={item_id:<6} class={str(iclass):15} text={ititle!r}')


if __name__ == '__main__':
    main(sys.argv[1])
