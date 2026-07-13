#!/usr/bin/env python3
"""CFG backward-scan for EncodeOutgoingPacketField (0x40a380) call sites:
recover the dropped EDI (self) value at each call site via capstone
disassembly, first of the immediate predecessor block, then (for
unresolved sites) the whole containing function - same two-pass technique
used for FindSpriteFrame's 181 sites (see scan_findspriteframe.py/2.py).

Usage: tools/.venv-angr/bin/python3 tools/scan_encodeoutgoingpacketfield.py
Output: tools/encodeoutgoingpacketfield_sites.json
"""
import json
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GME = os.path.join(REPO, "orig", "GunBound.gme")
TARGET = 0x40a380

import angr
import logging
logging.getLogger("angr").setLevel(logging.ERROR)

print(f"Loading {GME} ...")
proj = angr.Project(GME, auto_load_libs=False, load_options={"main_opts": {"base_addr": 0x400000}})

print("Building CFG (CFGFast) ...")
cfg = proj.analyses.CFGFast(normalize=True)
print(f"CFG done, {len(cfg.kb.functions)} functions found")

node = cfg.model.get_any_node(TARGET)
if node is None:
    print("ERROR: target function node not found")
    sys.exit(1)

preds = cfg.model.get_predecessors(node, jumpkind='Ijk_Call')
print(f"{len(preds)} call predecessors found")


def last_write_before(insns, call_addr, reg):
    val = None
    src = None
    for insn in insns:
        if insn.address >= call_addr:
            break
        m, ops = insn.mnemonic, insn.op_str
        if ops.startswith(reg + ","):
            rhs = ops.split(',', 1)[1].strip()
            if m == 'mov':
                val, src = rhs, f"0x{insn.address:x}: mov {reg},{rhs}"
            elif m == 'lea':
                val, src = f"&({rhs})", f"0x{insn.address:x}: lea {reg},{rhs}"
            elif m == 'xor' and rhs == reg:
                val, src = "0", f"0x{insn.address:x}: xor {reg},{reg}"
            elif m in ('add', 'sub', 'inc', 'dec', 'shr', 'shl', 'sar', 'movzx', 'and', 'or'):
                val, src = f"<clobbered:{m} {reg},{rhs}>", f"0x{insn.address:x}: {m} {reg},{rhs}"
        elif m == 'call':
            pass
    return val, src


results = []
for p in preds:
    try:
        block = proj.factory.block(p.addr, size=p.size)
    except Exception as e:
        results.append({"caller_block": hex(p.addr), "error": str(e)})
        continue
    insns = list(block.capstone.insns)
    call_addr = None
    for insn in insns:
        if insn.mnemonic == 'call':
            call_addr = insn.address

    edi_val, edi_src = last_write_before(insns, call_addr, "edi")

    func_name = None
    func_addr = None
    try:
        f = proj.kb.functions.floor_func(p.addr)
        if f:
            func_name = f.name
            func_addr = hex(f.addr)
    except Exception:
        pass

    results.append({
        "caller_block": hex(p.addr),
        "call_addr": hex(call_addr) if call_addr else None,
        "func_name": func_name,
        "func_addr": func_addr,
        "edi": edi_val,
        "edi_src": edi_src,
    })

# second pass: whole-function backward scan for unresolved EDI
print("Second pass: whole-function scan for unresolved EDI...")
updated = 0
for r in results:
    if r.get("edi") is not None:
        continue
    fa = r.get("func_addr")
    if not fa:
        continue
    func = cfg.kb.functions.get(int(fa, 16))
    if func is None:
        continue
    try:
        insns = []
        for block_addr in sorted(func.block_addrs):
            b = proj.factory.block(block_addr)
            insns.extend(b.capstone.insns)
        insns.sort(key=lambda i: i.address)
    except Exception:
        continue
    call_addr = int(r["call_addr"], 16)
    val, src = last_write_before(insns, call_addr, "edi")
    if val:
        r["edi"] = val
        r["edi_src"] = src
        updated += 1
print(f"Second pass resolved {updated} more sites")

outpath = os.path.join(REPO, "tools", "encodeoutgoingpacketfield_sites.json")
with open(outpath, "w") as f:
    json.dump(results, f, indent=2)
print(f"Wrote {len(results)} sites to {outpath}")

from collections import Counter
edi_counter = Counter(r.get("edi") for r in results)
print(f"\ntotal sites: {len(results)}")
print("EDI value distribution (top 20):")
for val, cnt in edi_counter.most_common(20):
    print(f"  {cnt:4d}  {val}")
none_edi = sum(1 for r in results if r.get("edi") is None)
clobbered = sum(1 for r in results if r.get("edi") and "clobbered" in str(r.get("edi")))
print(f"\nunresolved: {none_edi}, clobbered(needs 1-more-step): {clobbered}")
