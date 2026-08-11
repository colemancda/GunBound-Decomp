#!/usr/bin/env python3
"""Recover the stack-pushed cell argument at every PeekChecksumStateUnderLock
(0x40a4d0) call site. Unlike the register-passed guard family,
UnderLock takes its cell as a real stack parameter (`ret 4`), so the
argument is the LAST `push` before each `call 0x40a4d0`.

Reads the call-site inventory from tools/peekpacketchecksumstate_sites.json
(the PeekChecksumStateUnderLock section - its "eax" fields are noise, see
scan_peekpacketchecksumstate.py) and disassembles a window ending at each
call to find the push.

Usage: tools/.venv-angr/bin/python3 tools/scan_underlock_push.py
Output: tools/underlock_push_sites.json
"""
import json
import os
import bisect

import pefile
import capstone

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GME = os.path.join(REPO, "orig", "GunBound.gme")
SITES = os.path.join(REPO, "tools", "peekpacketchecksumstate_sites.json")
WINDOW = 0x40  # bytes before the call to disassemble

pe = pefile.PE(GME)
base = pe.OPTIONAL_HEADER.ImageBase


def read_va(va, size):
    return pe.get_data(va - base, size)


md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = False

with open(SITES) as f:
    data = json.load(f)

sites = data["PeekChecksumStateUnderLock"]
out = []
for s in sites:
    call_addr = s.get("call_addr")
    if not call_addr:
        out.append({**s, "push": None, "push_src": "no-call-addr"})
        continue
    ca = int(call_addr, 16)
    start = ca - WINDOW
    buf = read_va(start, WINDOW + 8)
    # find an instruction-boundary sync: try successive start offsets until
    # disassembly lands exactly on the call
    best = None
    for off in range(0, 16):
        insns = list(md.disasm(buf[off:], start + off))
        addrs = [i.address for i in insns]
        if ca in addrs:
            best = insns
            break
    if best is None:
        out.append({**s, "push": None, "push_src": "desync"})
        continue
    push_val, push_src = None, None
    for insn in best:
        if insn.address >= ca:
            break
        if insn.mnemonic == 'push':
            push_val = insn.op_str
            push_src = f"0x{insn.address:x}: push {insn.op_str}"
    out.append({
        "caller_block": s.get("caller_block"),
        "call_addr": call_addr,
        "func_name": s.get("func_name"),
        "func_addr": s.get("func_addr"),
        "push": push_val,
        "push_src": push_src,
    })

outpath = os.path.join(REPO, "tools", "underlock_push_sites.json")
with open(outpath, "w") as f:
    json.dump(out, f, indent=2)

from collections import Counter
c = Counter(str(r.get("push")) for r in out)
print(f"total: {len(out)}")
print("push distribution (top 25):")
for val, cnt in c.most_common(25):
    print(f"  {cnt:4d}  {val}")
missing = sum(1 for r in out if r.get("push") is None)
print(f"missing: {missing}")
print(f"Wrote {outpath}")
