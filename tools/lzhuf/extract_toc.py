import struct, sys
sys.path.insert(0, '.')
from lzhuf import decode_lzhuf

def read_toc(fn):
    with open(fn, 'rb') as f:
        f.seek(0, 2)
        filesize = f.tell()
        f.seek(filesize - 4)
        toc_offset = struct.unpack('<I', f.read(4))[0]
        f.seek(toc_offset)
        toc_size = struct.unpack('<I', f.read(4))[0]
        header_compressed = f.read(toc_size)
        header = decode_lzhuf(header_compressed, 0x40)
        magic = header[0:4]
        assert magic == b'XFS2', f"bad magic {magic}"
        unknown4 = struct.unpack('<I', header[4:8])[0]
        entry_count = struct.unpack('<I', header[8:12])[0]
        print(f"{fn}: magic OK, unknown@4={unknown4}, entry_count={entry_count}")

        num_full_chunks = entry_count >> 10
        remainder = entry_count & 0x3ff
        num_chunks = num_full_chunks + (1 if remainder else 0)

        entries = []
        for c in range(num_chunks):
            clen = struct.unpack('<I', f.read(4))[0]
            cdata = f.read(clen)
            chunk = decode_lzhuf(cdata, 0x20000)
            n_in_chunk = 1024 if (c < num_full_chunks) else remainder
            for e in range(n_in_chunk):
                rec = chunk[e*128:(e+1)*128]
                name_end = rec.find(b'\x00')
                name = rec[:name_end].decode('latin1') if name_end >= 0 else rec.decode('latin1')
                mode_flag, file_offset, decompressed_size, compressed_size = struct.unpack('<IIII', rec[0x70:0x80])
                entries.append((name, mode_flag, file_offset, decompressed_size, compressed_size))
        return entries, filesize, toc_offset, entry_count

if __name__ == '__main__':
    fn = sys.argv[1] if len(sys.argv) > 1 else '/Users/coleman/Developer/GunBound-Decomp/orig/graphics.xfs'
    entries, filesize, toc_offset, entry_count = read_toc(fn)
    print(f"parsed {len(entries)} entries (expected {entry_count})")
    for e in entries[:10]:
        print(e)
    print("...")
    # look for ChooseEvent.txt
    for e in entries:
        if 'chooseevent' in e[0].lower():
            print("FOUND:", e)
