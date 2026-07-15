#!/usr/bin/env python3
"""CFG backward-scan for AppendPacketBytes (0x4d2530) call sites: recover
the dropped EAX (self/packet object) and EDX (byte count) values at each
call site via capstone disassembly, first of the immediate predecessor
block, then (for unresolved sites) the whole containing function - same
two-pass technique used for FindGroundHeightAtColumn's 40 sites (see
scan_findgroundheightatcolumn.py).

Usage: tools/.venv-angr/bin/python3 tools/scan_appendpacketbytes.py
Output: tools/appendpacketbytes_sites.json
"""
import json
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GME = os.path.join(REPO, "orig", "GunBound.gme")
TARGET = 0x4d2530

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
            elif m in ('add', 'sub', 'inc', 'dec', 'shr', 'shl', 'sar', 'movzx', 'and', 'or', 'imul'):
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

    eax_val, eax_src = last_write_before(insns, call_addr, "eax")
    edx_val, edx_src = last_write_before(insns, call_addr, "edx")

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
        "eax": eax_val,
        "eax_src": eax_src,
        "edx": edx_val,
        "edx_src": edx_src,
    })

print("Second pass: whole-function scan for unresolved eax/edx...")
updated = 0
for r in results:
    fa = r.get("func_addr")
    if not fa:
        continue
    if r.get("eax") is not None and r.get("edx") is not None:
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
    if r.get("eax") is None:
        val, src = last_write_before(insns, call_addr, "eax")
        if val:
            r["eax"] = val
            r["eax_src"] = src
            updated += 1
    if r.get("edx") is None:
        val, src = last_write_before(insns, call_addr, "edx")
        if val:
            r["edx"] = val
            r["edx_src"] = src
            updated += 1
print(f"Second pass resolved {updated} more values")

outpath = os.path.join(REPO, "tools", "appendpacketbytes_sites.json")
with open(outpath, "w") as f:
    json.dump(results, f, indent=2)
print(f"Wrote {len(results)} sites to {outpath}")

from collections import Counter
eax_counter = Counter(r.get("eax") for r in results)
edx_counter = Counter(r.get("edx") for r in results)
print(f"\ntotal sites: {len(results)}")
print("EAX (self) value distribution (top 20):")
for val, cnt in eax_counter.most_common(20):
    print(f"  {cnt:4d}  {val}")
print("EDX (count) value distribution (top 20):")
for val, cnt in edx_counter.most_common(20):
    print(f"  {cnt:4d}  {val}")
none_eax = sum(1 for r in results if r.get("eax") is None)
none_edx = sum(1 for r in results if r.get("edx") is None)
print(f"\nunresolved eax: {none_eax}, unresolved edx: {none_edx}")
