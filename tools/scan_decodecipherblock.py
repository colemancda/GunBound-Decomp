#!/usr/bin/env python3
"""CFG backward-scan for DecodeCipherBlock (0x4f5e10) call sites: recover
the dropped EDX (param_2/ciphertext input pointer) value at each call
site via capstone disassembly, first of the immediate predecessor block,
then (for unresolved sites) the whole containing function - same
two-pass technique used for FindGroundHeightAtColumn/AppendPacketBytes.

Confirmed via direct disassembly (see commit history/investigation
notes): real ABI is param_1(ECX,dead)/param_2(EDX,input ciphertext
pointer)/param_3(1st stack arg, output buffer)/param_4(2nd stack arg,
cipher context). Existing 2-arg call sites in the tree pass their 2
visible arguments as (intended-output, intended-context), which under
the K&R declaration land in (dead ECX, EDX) - i.e. completely
mispositioned relative to the real signature, AND missing param_2
(input) entirely. This script only recovers param_2; the existing 2
call-site arguments should be repositioned to param_3/param_4.

Usage: tools/.venv-angr/bin/python3 tools/scan_decodecipherblock.py
Output: tools/decodecipherblock_sites.json
"""
import json
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GME = os.path.join(REPO, "orig", "GunBound.gme")
TARGET = 0x4f5e10

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


def last_two_pushes(insns, call_addr):
    """Return the last two `push` operands before call_addr, in program
    order (first-pushed, second-pushed) - second-pushed = param_3 (1st
    stack param), first-pushed = param_4 (2nd stack param)."""
    pushes = [insn for insn in insns if insn.address < call_addr and insn.mnemonic == 'push']
    last2 = pushes[-2:] if len(pushes) >= 2 else pushes
    return [f"0x{i.address:x}: push {i.op_str}" for i in last2]


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

    edx_val, edx_src = last_write_before(insns, call_addr, "edx")
    pushes = last_two_pushes(insns, call_addr)

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
        "edx_input_hint": edx_val,
        "edx_src": edx_src,
        "last_two_pushes": pushes,
    })

print("Second pass: whole-function scan for unresolved edx...")
updated = 0
for r in results:
    if r.get("edx_input_hint") is not None:
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
    val, src = last_write_before(insns, call_addr, "edx")
    if val:
        r["edx_input_hint"] = val
        r["edx_src"] = src
        updated += 1
print(f"Second pass resolved {updated} more values")

outpath = os.path.join(REPO, "tools", "decodecipherblock_sites.json")
with open(outpath, "w") as f:
    json.dump(results, f, indent=2)
print(f"Wrote {len(results)} sites to {outpath}")

for r in results:
    print(r.get("func_name"), r.get("func_addr"), r.get("call_addr"), "edx=", r.get("edx_input_hint"), "pushes=", r.get("last_two_pushes"))
