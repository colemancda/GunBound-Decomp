#!/usr/bin/env python3
"""Stage 2 of the dropped-register sweep: corroborate at the call sites.

Stage 1 (tools/sweep_dropped_regs.py) finds registers a ported function
reads before writing. That has full recall but poor precision - callee-saved
shuffling and SEH paths make many registers look live-in.

The decisive evidence for a GENUINE register argument is on the caller's
side: if a register really is an incoming parameter, essentially every call
site sets it in the instructions immediately before the `call`. That is how
AllocCipherSchedule's ESI was confirmed (`mov esi, 0x2dbabe65` at 0x501b4c,
one instruction before the call).

This script builds a call-graph from a linear sweep of .text, then scores
each (function, register) candidate by the fraction of its call sites that
set the register in the preceding window. A high score means a real dropped
argument AND tells you what the callers pass.

Usage:
  tools/.venv-angr/bin/python tools/sweep_callsite_corroborate.py \
      --in dropped.json --out corroborated.json [--min-score 0.8]
"""
import argparse
import collections
import json

import capstone

BIN = "orig/GunBound.gme"
WINDOW = 12  # instructions to look back before a call

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


def load_text(proj):
    for sec in proj.loader.main_object.sections:
        if sec.name == ".text":
            return sec.vaddr, proj.loader.memory.load(sec.vaddr, sec.memsize)
    raise SystemExit("no .text section")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--in", dest="inp", required=True)
    ap.add_argument("--out", dest="out", required=True)
    ap.add_argument("--min-score", type=float, default=0.8)
    args = ap.parse_args()

    import angr
    import logging

    logging.getLogger("angr").setLevel("ERROR")
    logging.getLogger("cle").setLevel("ERROR")
    proj = angr.Project(BIN, auto_load_libs=False)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True

    base, data = load_text(proj)
    print(f".text at {base:#x}, {len(data)} bytes - linear sweep...")
    insns = list(md.disasm(data, base))
    print(f"decoded {len(insns)} instructions")

    index = {ins.address: i for i, ins in enumerate(insns)}
    callsites = collections.defaultdict(list)
    for i, ins in enumerate(insns):
        if ins.mnemonic == "call" and ins.operands and \
           ins.operands[0].type == capstone.x86.X86_OP_IMM:
            callsites[ins.operands[0].imm].append(i)
    print(f"found {len(callsites)} distinct direct-call targets")

    candidates = json.load(open(args.inp))
    results = []
    for c in candidates:
        if "confirmed" not in c:
            continue
        addr = int(c["addr"], 16)
        sites = callsites.get(addr, [])
        if not sites:
            continue
        for reg in c["confirmed"]:
            setters, total = [], 0
            for si in sites:
                total += 1
                for j in range(max(0, si - WINDOW), si):
                    ins = insns[j]
                    if ins.mnemonic == "call":
                        setters.append(None)
                        break
                    try:
                        _, written = ins.regs_access()
                    except capstone.CsError:
                        continue
                    if any(NAME2ROOT.get(ins.reg_name(r)) == reg for r in written):
                        setters.append(
                            f"{ins.address:08x}: {ins.mnemonic} {ins.op_str}"
                        )
                        break
                else:
                    setters.append(None)
            hits = [s for s in setters if s]
            score = len(hits) / total if total else 0.0
            if score >= args.min_score:
                results.append({
                    "addr": c["addr"], "func": c["func"], "path": c["path"],
                    "reg": reg, "score": round(score, 3),
                    "callsites": total, "evidence": hits[:6],
                })

    results.sort(key=lambda r: (-r["score"], -r["callsites"], r["path"]))
    print(f"\nCORROBORATED dropped-register args (score >= {args.min_score}): "
          f"{len(results)}\n")
    for r in results:
        print(f"{r['addr']}  {r['func']:<42} {r['reg'].upper():<4} "
              f"score={r['score']:<5} sites={r['callsites']}")
        print(f"          {r['path']}")
        for e in r["evidence"][:3]:
            print(f"            {e}")

    json.dump(results, open(args.out, "w"), indent=2)
    print(f"\nwrote {args.out}")


if __name__ == "__main__":
    main()
