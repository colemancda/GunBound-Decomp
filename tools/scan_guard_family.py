#!/usr/bin/env python3
"""One-pass CFG scan of the ENTIRE CValueGuard/GuardedBool call family.

For every call site of every family member this records:
  - eax / eax_src: backward-tracked EAX (the family's dominant cell reg)
  - pushes: the last up-to-3 push operands before the call (stack-arg
    members: Queue value, EncodeChecksumState src cell, UnderLock cell)
  - window: the raw disasm of up to 12 instructions preceding the call
    (lets sweep agents resolve register chains without re-running angr)
and each target's prologue (first 14 insns) for ABI confirmation.

Targets: the 25-member family (see cvalueguard-migration memory).
Already-scanned members (Peek 0x40a2e0, inner Encode 0x40a380, UnderLock
0x40a4d0) are NOT rescanned here - their jsons stand.

Usage: tools/.venv-angr/bin/python3 tools/scan_guard_family.py
Output: tools/guard_family_sites.json
"""
import json
import os

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GME = os.path.join(REPO, "orig", "GunBound.gme")

TARGETS = {
    0x40a470: "QueueOutgoingPacketField",
    0x40a4a0: "EncodeChecksumState",
    0x40a440: "EncodeChecksumStateXored",
    0x40a500: "EncodeChecksumNegate",
    0x40a5f0: "EncodeChecksumDeltaAdd",
    0x40a6e0: "EncodeChecksumDeltaSub",
    0x40a7d0: "EncodeChecksumDeltaMul",
    0x40a8c0: "EncodeChecksumDeltaDiv",
    0x40a9c0: "EncodeChecksumDeltaMod",
    0x40b180: "EncodeChecksumDeltaShr",
    0x40aba0: "EncodeChecksumPairSum",
    0x40aca0: "EncodeChecksumPairDiff",
    0x40afb0: "EmitChecksumSum",
    0x40a2a0: "ScrubChecksumGuard",
    0x40b270: "PacketChecksumEquals",
    0x40b2a0: "PacketChecksumNotEquals",
    0x40b2d0: "PacketChecksumGreaterThan",
    0x40b300: "PacketChecksumGreaterEqual",
    0x40b330: "PacketChecksumLessThan",
    0x40b360: "PacketChecksumLessEqual",
    0x4065a0: "PeekPacketChecksumBool",
    0x406500: "SetGuardedBool",
    0x4064a0: "EncodeGuardedBool",
    0x406530: "RescrambleGuardedBool",
    0x406610: "CheckGuardedBoolAnd",
    0x406710: "CheckBothGuardedBools",
}

import angr
import logging
logging.getLogger("angr").setLevel(logging.ERROR)

print(f"Loading {GME} ...")
proj = angr.Project(GME, auto_load_libs=False,
                    load_options={"main_opts": {"base_addr": 0x400000}})
print("Building CFG (CFGFast) ...")
cfg = proj.analyses.CFGFast(normalize=True)
print(f"CFG done, {len(cfg.kb.functions)} functions")


def last_write_before(insns, call_addr, reg):
    val = src = None
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
            else:
                val, src = f"<clobbered:{m} {reg},{rhs}>", f"0x{insn.address:x}: {m} {reg},{rhs}"
        elif m == 'call' and insn.address < call_addr:
            val, src = f"<call-ret:{ops.strip()}>", f"0x{insn.address:x}: call {ops.strip()}"
    return val, src


out = {"prologues": {}, "sites": {}}
for tgt, name in TARGETS.items():
    try:
        b = proj.factory.block(tgt, size=48)
        out["prologues"][name] = [
            f"0x{i.address:x}: {i.mnemonic} {i.op_str}" for i in b.capstone.insns[:14]]
    except Exception as e:
        out["prologues"][name] = [f"error: {e}"]

for tgt, name in TARGETS.items():
    node = cfg.model.get_any_node(tgt)
    if node is None:
        print(f"{name}: NODE NOT FOUND")
        out["sites"][name] = []
        continue
    preds = cfg.model.get_predecessors(node, jumpkind='Ijk_Call')
    rows = []
    for p in preds:
        try:
            block = proj.factory.block(p.addr, size=p.size)
        except Exception:
            continue
        insns = list(block.capstone.insns)
        call_addr = None
        for insn in insns:
            if insn.mnemonic == 'call':
                call_addr = insn.address
        if call_addr is None:
            continue
        eax, eax_src = last_write_before(insns, call_addr, "eax")
        pushes = [f"0x{i.address:x}: push {i.op_str}"
                  for i in insns if i.mnemonic == 'push' and i.address < call_addr][-3:]
        pre = [i for i in insns if i.address < call_addr][-12:]
        window = [f"0x{i.address:x}: {i.mnemonic} {i.op_str}" for i in pre]
        fa = None
        try:
            f = proj.kb.functions.floor_func(p.addr)
            if f:
                fa = hex(f.addr)
        except Exception:
            pass
        rows.append({"call_addr": hex(call_addr), "func_addr": fa,
                     "eax": eax, "eax_src": eax_src,
                     "pushes": pushes, "window": window})
    rows.sort(key=lambda r: int(r["call_addr"], 16))
    out["sites"][name] = rows
    print(f"{name}: {len(rows)} sites")

outpath = os.path.join(REPO, "tools", "guard_family_sites.json")
with open(outpath, "w") as f:
    json.dump(out, f, indent=2)
print(f"Wrote {outpath}")
