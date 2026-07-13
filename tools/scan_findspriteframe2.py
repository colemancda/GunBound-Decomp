#!/usr/bin/env python3
"""Improved backward scan: for each FindSpriteFrame call site, search
backward through the ENTIRE containing function's disassembly (not just
the immediate basic block) for the last write to ESI/EAX before the call,
using angr's function-level linear disassembly. Falls back gracefully if
no function is recovered.
"""
import json
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GME = os.path.join(REPO, "orig", "GunBound.gme")

import angr
import logging
logging.getLogger("angr").setLevel(logging.ERROR)

print(f"Loading {GME} ...")
proj = angr.Project(GME, auto_load_libs=False, load_options={"main_opts": {"base_addr": 0x400000}})
print("Building CFG (CFGFast) ...")
cfg = proj.analyses.CFGFast(normalize=True)
print(f"CFG done, {len(cfg.kb.functions)} functions found")

data = json.load(open(os.path.join(REPO, "tools", "findspriteframe_sites.json")))

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
        elif m in ('call',) and reg in ('eax',):
            # a call clobbers eax as a return-value sink; anything before this
            # writing eax is stale once a call happens, UNLESS re-written after
            val, src = f"<call-clobbered@0x{insn.address:x}>", None
    return val, src

updated = 0
for r in data:
    if r.get("eax") is not None and r.get("esi") is not None:
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
    except Exception as e:
        continue
    call_addr = int(r["call_addr"], 16)
    if r.get("eax") is None:
        val, src = last_write_before(insns, call_addr, "eax")
        if val:
            r["eax"] = val
            r["eax_src"] = src
            updated += 1
    if r.get("esi") is None:
        val, src = last_write_before(insns, call_addr, "esi")
        if val:
            r["esi"] = val
            r["esi_src"] = src
            updated += 1

print(f"Updated {updated} fields")
outpath = os.path.join(REPO, "tools", "findspriteframe_sites.json")
with open(outpath, "w") as f:
    json.dump(data, f, indent=2)

none_esi = [r for r in data if r.get("esi") is None]
print(f"Still unresolved ESI: {len(none_esi)}")
for r in none_esi:
    print(" ", r.get("func_name"), r.get("call_addr"))
