#!/usr/bin/env python3
"""CFG backward-scan for FUN_004ac4d0 (0x4ac4d0) and FUN_004ac400
(0x4ac400) call sites: recover the dropped ECX (param_1/self cell)
value at each call site via capstone disassembly, first of the
immediate predecessor block, then (for unresolved sites) the whole
containing function - same two-pass technique used for the other fixes
this session. Both functions match this codebase's established
"packet-checksum utility family" (CValueGuard) idiom - param_1 is
almost certainly a guarded-value cell pointer, self+0x4c specifically.

Usage: tools/.venv-angr/bin/python3 tools/scan_fun004ac4x0.py
Output: tools/fun004ac4x0_sites.json
"""
import json
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GME = os.path.join(REPO, "orig", "GunBound.gme")
TARGETS = {"FUN_004ac4d0": 0x4ac4d0, "FUN_004ac400": 0x4ac400}

import angr
import logging
logging.getLogger("angr").setLevel(logging.ERROR)

print(f"Loading {GME} ...")
proj = angr.Project(GME, auto_load_libs=False, load_options={"main_opts": {"base_addr": 0x400000}})

print("Building CFG (CFGFast) ...")
cfg = proj.analyses.CFGFast(normalize=True)
print(f"CFG done, {len(cfg.kb.functions)} functions found")


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


all_results = {}
for fn_name, target in TARGETS.items():
    node = cfg.model.get_any_node(target)
    if node is None:
        print(f"ERROR: {fn_name} node not found")
        continue
    preds = cfg.model.get_predecessors(node, jumpkind='Ijk_Call')
    print(f"{fn_name}: {len(preds)} call predecessors found")

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
    print(f"  second pass resolved {updated} more values")
    all_results[fn_name] = results

outpath = os.path.join(REPO, "tools", "fun004ac4x0_sites.json")
with open(outpath, "w") as f:
    json.dump(all_results, f, indent=2)
print(f"Wrote to {outpath}")

for fn_name, results in all_results.items():
    print(f"\n=== {fn_name} ===")
    for r in results:
        print(r.get("func_name"), r.get("func_addr"), r.get("call_addr"), "self=", r.get("self_ecx"))
