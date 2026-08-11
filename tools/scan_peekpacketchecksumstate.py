#!/usr/bin/env python3
"""CFG backward-scan for PeekPacketChecksumState / CValueGuard::Peek
(0x40a2e0) call sites: recover the dropped EAX (the guard-cell `this`)
at each call site via capstone disassembly - first of the immediate
predecessor block, then (for unresolved sites) the whole containing
function. Same two-pass technique as scan_encodeoutgoingpacketfield.py
(EDI, 2102 sites) and scan_findspriteframe.py.

Also scans PeekChecksumStateUnderLock (0x40a4d0), the lock wrapper with
the same dropped cell, tracking EAX there too (verify its register
against the disasm before trusting - see the summary print).

Usage: tools/.venv-angr/bin/python3 tools/scan_peekpacketchecksumstate.py
Output: tools/peekpacketchecksumstate_sites.json
"""
import json
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GME = os.path.join(REPO, "orig", "GunBound.gme")
TARGETS = {
    0x40a2e0: "PeekPacketChecksumState",
    0x40a4d0: "PeekChecksumStateUnderLock",
}
REG = "eax"

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
            elif m in ('add', 'sub', 'inc', 'dec', 'shr', 'shl', 'sar', 'movzx', 'and', 'or'):
                val, src = f"<clobbered:{m} {reg},{rhs}>", f"0x{insn.address:x}: {m} {reg},{rhs}"
        elif m == 'call' and insn.address < call_addr:
            # an intervening call clobbers EAX (its return value) - record it
            # so the site is flagged rather than silently mis-attributed
            tgt = ops.strip()
            val, src = f"<call-ret:{tgt}>", f"0x{insn.address:x}: call {tgt}"
    return val, src


all_results = {}
for TARGET, tname in TARGETS.items():
    node = cfg.model.get_any_node(TARGET)
    if node is None:
        print(f"ERROR: target {tname} (0x{TARGET:x}) node not found")
        continue

    preds = cfg.model.get_predecessors(node, jumpkind='Ijk_Call')
    print(f"{tname}: {len(preds)} call predecessors found")

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

        val, src = last_write_before(insns, call_addr, REG)

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
            "eax": val,
            "eax_src": src,
        })

    # second pass: whole-function backward scan for unresolved EAX
    print(f"{tname}: second pass for unresolved EAX...")
    updated = 0
    for r in results:
        if r.get("eax") is not None:
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
        val, src = last_write_before(insns, call_addr, REG)
        if val:
            r["eax"] = val
            r["eax_src"] = src
            updated += 1
    print(f"{tname}: second pass resolved {updated} more sites")
    all_results[tname] = results

outpath = os.path.join(REPO, "tools", "peekpacketchecksumstate_sites.json")
with open(outpath, "w") as f:
    json.dump(all_results, f, indent=2)

from collections import Counter
for tname, results in all_results.items():
    print(f"\n=== {tname}: {len(results)} sites ===")
    counter = Counter(str(r.get("eax")) for r in results)
    print("EAX value distribution (top 25):")
    for val, cnt in counter.most_common(25):
        print(f"  {cnt:4d}  {val}")
    none_c = sum(1 for r in results if r.get("eax") is None)
    clob = sum(1 for r in results if r.get("eax") and "clobbered" in str(r.get("eax")))
    callret = sum(1 for r in results if r.get("eax") and "call-ret" in str(r.get("eax")))
    print(f"unresolved: {none_c}, clobbered: {clob}, call-ret: {callret}")
print(f"\nWrote {outpath}")
