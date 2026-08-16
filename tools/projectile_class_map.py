#!/usr/bin/env python3
"""Map projectile-class constructors -> vtable -> slot functions.

For each constructor address (the FUN_ called right after operator_new in
SpawnPrimaryShot / SpawnSuperShot / SpawnItemProjectile), disassemble the
ctor, find the `mov dword ptr [reg], 0x55xxxx` vtable store, then read the
vtable (13 slots, CProjectile layout, see src/cxx/Projectile.h) from the
original image and print slot -> function address.  Used 2026-08-16 to name
the per-weapon projectile virtuals swept by the CValueGuard pass.

    tools/.venv-angr/bin/python3 tools/projectile_class_map.py 0x47de30 [...]
"""
import re, subprocess, sys, os, struct
import pefile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
pe = pefile.PE(os.path.join(ROOT, "orig/GunBound.gme"))
base = pe.OPTIONAL_HEADER.ImageBase

def read(va, n):
    for s in pe.sections:
        sva = base + s.VirtualAddress
        if sva <= va < sva + max(s.Misc_VirtualSize, s.SizeOfRawData):
            d = s.get_data()
            o = va - sva
            return d[o:o + n]
    return b""

def disasm(a, b):
    out = subprocess.run([os.path.join(HERE, ".venv-angr/bin/python3"),
                          os.path.join(HERE, "disasm_capstone.py"),
                          os.path.join(ROOT, "orig/GunBound.gme"), hex(a), hex(b)],
                         capture_output=True, text=True, cwd=ROOT).stdout
    return out.splitlines()

for arg in sys.argv[1:]:
    ctor = int(arg, 16)
    vt = None
    for line in disasm(ctor, ctor + 0x60):
        m = re.search(r"mov\tdword ptr \[(?:e[a-z]x|esi|edi)\], (0x55[0-9a-f]{4})", line)
        if m:
            vt = int(m.group(1), 16)
            break
    if vt is None:
        print("%s: no vtable store found" % arg); continue
    slots = struct.unpack("<13I", read(vt, 52))
    print("ctor %s vtable 0x%x: " % (arg, vt) + " ".join("%d:0x%x" % (i, s) for i, s in enumerate(slots)))
