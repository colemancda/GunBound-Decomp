#!/usr/bin/env python3
"""Stage 2a of the dropped-register sweep: build a call-site index.

The first attempt at call-site corroboration used a LINEAR sweep of
.text, which desyncs on data and padding - it found call sites for only 2
of 7 known-true cases and missed nearly every reference to a given struct
offset. This builds the same index from angr's CFGFast instead, which
follows real control flow and so decodes only genuine instruction
boundaries.

For every direct `call <imm>`, this records the instructions preceding it
WITHIN ITS BASIC BLOCK (plus, when the block has a single predecessor,
that predecessor's tail). A register set in that window is what a
register-passed argument actually looks like at a call site.

The result is cached to a pickle so the corroboration pass can be
re-run and re-tuned without paying for CFG construction again.

Usage:
  tools/.venv-angr/bin/python tools/sweep_build_index.py [--out index.pkl]
"""
import argparse
import collections
import pickle

import capstone

BIN = "orig/GunBound.gme"
WINDOW = 16  # max instructions of context to keep before each call

SUB = {
    "eax": {"eax", "ax", "al", "ah"},
    "ebx": {"ebx", "bx", "bl", "bh"},
    "ecx": {"ecx", "cx", "cl", "ch"},
    "edx": {"edx", "dx", "dl", "dh"},
    "esi": {"esi", "si", "sil"},
    "edi": {"edi", "di", "dil"},
    "ebp": {"ebp", "bp", "bpl"},
}
NAME2ROOT = {n: r for r, names in SUB.items() for n in names}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default="sweep_index.pkl")
    args = ap.parse_args()

    import angr
    import logging

    logging.getLogger("angr").setLevel("ERROR")
    logging.getLogger("cle").setLevel("ERROR")

    proj = angr.Project(BIN, auto_load_libs=False)
    print("building CFGFast (this takes a few minutes)...")
    cfg = proj.analyses.CFGFast(normalize=True, force_complete_scan=True)
    nodes = list(cfg.graph.nodes())
    print(f"CFG nodes: {len(nodes)}")

    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True

    # decode every basic block once
    blocks = {}
    for n in nodes:
        if not n.size or n.addr in blocks:
            continue
        try:
            data = proj.loader.memory.load(n.addr, n.size)
        except Exception:  # noqa: BLE001
            continue
        rows = []
        for ins in md.disasm(data, n.addr):
            try:
                _, written = ins.regs_access()
            except capstone.CsError:
                written = ()
            wroots = {NAME2ROOT[ins.reg_name(r)] for r in written
                      if ins.reg_name(r) in NAME2ROOT}
            rows.append((ins.address, ins.mnemonic, ins.op_str, wroots))
        blocks[n.addr] = rows

    preds = {n.addr: [p.addr for p in cfg.graph.predecessors(n)] for n in nodes}

    callsites = collections.defaultdict(list)
    for baddr, rows in blocks.items():
        for i, (addr, mn, ops, _w) in enumerate(rows):
            if mn != "call":
                continue
            try:
                target = int(ops, 16)
            except ValueError:
                continue  # indirect call
            ctx = rows[max(0, i - WINDOW):i]
            if len(ctx) < WINDOW:
                plist = preds.get(baddr, [])
                if len(plist) == 1 and plist[0] in blocks and plist[0] != baddr:
                    need = WINDOW - len(ctx)
                    ctx = blocks[plist[0]][-need:] + ctx
            callsites[target].append({"site": addr, "ctx": ctx})

    print(f"direct-call targets: {len(callsites)}")
    print(f"total call sites:    {sum(len(v) for v in callsites.values())}")
    pickle.dump(dict(callsites), open(args.out, "wb"))
    print(f"wrote {args.out}")


if __name__ == "__main__":
    main()
