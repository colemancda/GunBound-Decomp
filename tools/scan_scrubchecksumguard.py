#!/usr/bin/env python3
"""CFG backward-scan for ScrubChecksumGuard (0x40a2a0) call sites: recover
the dropped ECX (param_1/self cell) value at each call site via capstone
disassembly, first of the immediate predecessor block, then (for
unresolved sites) the whole containing function - same two-pass technique
used for the other CValueGuard-family fixes this session
(FUN_004ac4d0/FUN_004ac400).

Usage: tools/.venv-angr/bin/python3 tools/scan_scrubchecksumguard.py
Output: tools/scrubchecksumguard_sites.json
"""
import json
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GME = os.path.join(REPO, "orig", "GunBound.gme")
TARGET = 0x40a2a0

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

    ecx_val, ecx_src = last_write_before(insns, call_addr, "ecx")

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
        "self_ecx": ecx_val,
        "self_src": ecx_src,
    })

print("Second pass: whole-function scan for unresolved ecx...")
updated = 0
for r in results:
    if r.get("self_ecx") is not None:
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
    val, src = last_write_before(insns, call_addr, "ecx")
    if val:
        r["self_ecx"] = val
        r["self_src"] = src
        updated += 1
print(f"Second pass resolved {updated} more values")

outpath = os.path.join(REPO, "tools", "scrubchecksumguard_sites.json")
with open(outpath, "w") as f:
    json.dump(results, f, indent=2)
print(f"Wrote {len(results)} sites to {outpath}")

from collections import Counter
funcs = Counter(r.get("func_addr") for r in results)
print(f"\ntotal sites: {len(results)}, unique functions: {len(funcs)}")
simple_reg = sum(1 for r in results if r.get("self_ecx") in ("edi", "esi", "ebx", "ebp", "eax", "edx"))
clobbered = sum(1 for r in results if r.get("self_ecx") and "clobbered" in str(r.get("self_ecx")))
stack = sum(1 for r in results if r.get("self_ecx") and "esp" in str(r.get("self_ecx")))
none_ct = sum(1 for r in results if r.get("self_ecx") is None)
print(f"simple register: {simple_reg}, clobbered(needs 1 more step): {clobbered}, stack-slot: {stack}, unresolved: {none_ct}")
