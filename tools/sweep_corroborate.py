#!/usr/bin/env python3
"""Stage 2b of the dropped-register sweep: score candidates at their call sites.

Stage 1 (sweep_dropped_regs.py) finds registers a function reads before
writing - full recall, poor precision. The decisive evidence for a GENUINE
register argument is on the caller's side: if a register really is an
incoming parameter, essentially every call site sets it just before the
`call`. That is exactly how AllocCipherSchedule's ESI was confirmed
(`mov esi, 0x2dbabe65`, one instruction before the call).

Consumes the CFG-derived index from sweep_build_index.py.

A register is counted as "set" at a call site if some instruction in the
preceding same-block window writes it. `pop <reg>` is NOT counted: that is
an epilogue restore of a callee-saved register, and treating it as an
argument set was a large source of false positives in the first attempt.

Usage:
  tools/.venv-angr/bin/python tools/sweep_corroborate.py \
      --index sweep_index.pkl --in dropped.json --out corroborated.json \
      [--min-score 0.9] [--only ADDR:REG,...]
"""
import argparse
import json
import pickle


def score_one(sites, reg):
    """Return (score, n_sites, evidence[]) for one (function, register)."""
    hits = []
    for s in sites:
        found = None
        for addr, mn, ops, wroots in reversed(s["ctx"]):
            if mn == "call":
                break  # a nearer call clobbers/blocks the argument setup
            if mn == "pop":
                continue  # epilogue restore, not an argument set
            if reg in wroots:
                found = f"{addr:08x}: {mn} {ops}"
                break
        hits.append(found)
    n = len(hits)
    good = [h for h in hits if h]
    return (len(good) / n if n else 0.0), n, good


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--index", required=True)
    ap.add_argument("--in", dest="inp", required=True)
    ap.add_argument("--out", dest="out", required=True)
    ap.add_argument("--min-score", type=float, default=0.9)
    ap.add_argument("--only", default=None,
                    help="comma-separated ADDR:REG pairs, for validation")
    args = ap.parse_args()

    index = pickle.load(open(args.index, "rb"))

    if args.only:
        pairs = []
        for tok in args.only.split(","):
            a, r = tok.split(":")
            pairs.append((int(a, 16), r.lower(), a))
        print(f"{'addr':<10}{'reg':<5}{'score':<8}{'sites':<7}evidence")
        for addr, reg, astr in pairs:
            sites = index.get(addr, [])
            sc, n, ev = score_one(sites, reg)
            print(f"{astr:<10}{reg:<5}{sc:<8.3f}{n:<7}{ev[0] if ev else '-'}")
        return

    candidates = json.load(open(args.inp))
    results = []
    for c in candidates:
        if "confirmed" not in c:
            continue
        sites = index.get(int(c["addr"], 16), [])
        if not sites:
            continue
        for reg in c["confirmed"]:
            sc, n, ev = score_one(sites, reg)
            if sc >= args.min_score:
                results.append({
                    "addr": c["addr"], "func": c["func"], "path": c["path"],
                    "reg": reg, "score": round(sc, 3), "callsites": n,
                    "evidence": ev[:8],
                })

    results.sort(key=lambda r: (-r["score"], -r["callsites"], r["path"]))
    print(f"CORROBORATED (score >= {args.min_score}): {len(results)}\n")
    for r in results:
        print(f"{r['addr']}  {r['func']:<40} {r['reg'].upper():<4} "
              f"score={r['score']:<6} sites={r['callsites']}")
        print(f"          {r['path']}")
        for e in r["evidence"][:3]:
            print(f"            {e}")
    json.dump(results, open(args.out, "w"), indent=2)
    print(f"\nwrote {args.out}")


if __name__ == "__main__":
    main()
