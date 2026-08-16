#!/usr/bin/env python3
"""Find every .rdata/.data dword equal to the given code addresses (vtable
slot references) and print address + which known vtable start precedes it.
    tools/.venv-angr/bin/python3 tools/find_vtable_refs.py 0x480310 0x47ca40
"""
import sys, os, struct
import pefile
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
pe = pefile.PE(os.path.join(ROOT, "orig/GunBound.gme"))
base = pe.OPTIONAL_HEADER.ImageBase
targets = {int(a, 16) for a in sys.argv[1:]}
for s in pe.sections:
    name = s.Name.rstrip(b"\0").decode()
    if name not in (".rdata", ".data"):
        continue
    d = s.get_data()
    sva = base + s.VirtualAddress
    for off in range(0, len(d) - 3, 4):
        v = struct.unpack_from("<I", d, off)[0]
        if v in targets:
            print("0x%x found at %s 0x%x" % (v, name, sva + off))
