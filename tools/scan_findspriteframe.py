#!/usr/bin/env python3
"""CFG backward-scan for FindSpriteFrame (0x4f30c0) call sites: recover the
literal/traced EAX (container) and ESI (inner key) values at each call site
via capstone disassembly of the predecessor block, same technique used
earlier this session for InvokeWidget's ~117 call sites.

Usage: tools/.venv-angr/bin/python3 tools/scan_findspriteframe.py
Output: tools/findspriteframe_sites.json - one entry per call site with
  {addr, func_addr, func_name, eax, esi, eax_src, esi_src}
"""
import json
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GME = os.path.join(REPO, "orig", "GunBound.gme")
TARGET = 0x4f30c0

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

results = []
for p in preds:
    try:
        block = proj.factory.block(p.addr, size=p.size)
    except Exception as e:
        results.append({"caller_block": hex(p.addr), "error": str(e)})
        continue
    insns = list(block.capstone.insns)
    # find the call instruction itself (last insn, targeting TARGET)
    call_addr = None
    for insn in insns:
        if insn.mnemonic == 'call':
            call_addr = insn.address
    eax_val = None
    esi_val = None
    eax_src = None
    esi_src = None
    # walk backward from the call, tracking last write to eax/esi
    for insn in insns:
        txt = f"{insn.mnemonic} {insn.op_str}"
        m = insn.mnemonic
        ops = insn.op_str
        if m == 'mov' and ops.startswith('eax,'):
            val = ops.split(',', 1)[1].strip()
            eax_val = val
            eax_src = f"0x{insn.address:x}: {txt}"
        elif m == 'lea' and ops.startswith('eax,'):
            eax_val = ops.split(',', 1)[1].strip()
            eax_src = f"0x{insn.address:x}: {txt} (lea)"
        elif m == 'xor' and ops == 'eax, eax':
            eax_val = "0"
            eax_src = f"0x{insn.address:x}: {txt}"
        if m == 'mov' and ops.startswith('esi,'):
            val = ops.split(',', 1)[1].strip()
            esi_val = val
            esi_src = f"0x{insn.address:x}: {txt}"
        elif m == 'lea' and ops.startswith('esi,'):
            esi_val = ops.split(',', 1)[1].strip()
            esi_src = f"0x{insn.address:x}: {txt} (lea)"
        elif m == 'xor' and ops == 'esi, esi':
            esi_val = "0"
            esi_src = f"0x{insn.address:x}: {txt}"

    func = cfg.kb.functions.floor_func(p.addr) if hasattr(cfg.kb.functions, 'floor_func') else None
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
        "esi": esi_val,
        "esi_src": esi_src,
        "insns": [f"0x{i.address:x}: {i.mnemonic} {i.op_str}" for i in insns],
    })

outpath = os.path.join(REPO, "tools", "findspriteframe_sites.json")
with open(outpath, "w") as f:
    json.dump(results, f, indent=2)
print(f"Wrote {len(results)} sites to {outpath}")

# summarize eax value distribution
from collections import Counter
eax_counter = Counter(r.get("eax") for r in results)
print("\nEAX value distribution:")
for val, cnt in eax_counter.most_common(10):
    print(f"  {cnt:4d}  {val}")
