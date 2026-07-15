#!/usr/bin/env python3
"""CFG backward-scan for QueueTextureRegionSpans (0x4ebaf0) call sites:
recover the dropped EAX (y-offset), and confirm/recover ECX (param_1) and
EDX (param_2) values at each call site via capstone disassembly, first of
the immediate predecessor block, then (for unresolved sites) the whole
containing function - same two-pass technique used for the other fixes
this session.

Confirmed via direct disassembly of the function's own body at 0x4ebaf0:
ECX=param_1 (2nd/inner tree-search key), EDX=param_2 (1st/outer
tree-search key), EAX=dropped y-offset (in_EAX in the current C source).

Usage: tools/.venv-angr/bin/python3 tools/scan_queuetextureregionspans.py
Output: tools/queuetextureregionspans_sites.json
"""
import json
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GME = os.path.join(REPO, "orig", "GunBound.gme")
TARGET = 0x4ebaf0

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
            elif m in ('add', 'sub', 'inc', 'dec', 'shr', 'shl', 'sar', 'movzx', 'and', 'or', 'imul', 'neg'):
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
    ecx_val, ecx_src = last_write_before(insns, call_addr, "ecx")
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
        "eax_y": eax_val,
        "eax_src": eax_src,
        "ecx_param1": ecx_val,
        "ecx_src": ecx_src,
        "edx_param2": edx_val,
        "edx_src": edx_src,
    })

print("Second pass: whole-function scan for unresolved regs...")
updated = 0
for r in results:
    fa = r.get("func_addr")
    if not fa:
        continue
    if r.get("eax_y") is not None and r.get("ecx_param1") is not None and r.get("edx_param2") is not None:
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
    for reg, key, srckey in (("eax", "eax_y", "eax_src"), ("ecx", "ecx_param1", "ecx_src"), ("edx", "edx_param2", "edx_src")):
        if r.get(key) is None:
            val, src = last_write_before(insns, call_addr, reg)
            if val:
                r[key] = val
                r[srckey] = src
                updated += 1
print(f"Second pass resolved {updated} more values")

outpath = os.path.join(REPO, "tools", "queuetextureregionspans_sites.json")
with open(outpath, "w") as f:
    json.dump(results, f, indent=2)
print(f"Wrote {len(results)} sites to {outpath}")

for r in results:
    print(r.get("func_name"), r.get("func_addr"), r.get("call_addr"),
          "param1(ecx)=", r.get("ecx_param1"), "param2(edx)=", r.get("edx_param2"), "y(eax)=", r.get("eax_y"))
