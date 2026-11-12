#!/usr/bin/env python3
"""Print discovery statistics and a mnemonic histogram for a PE image (no code is emitted)."""
import argparse
import collections
import csv
import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from image import Image  # noqa: E402
from analyze import Analysis  # noqa: E402


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pe", required=True)
    ap.add_argument("--csv")
    args = ap.parse_args()
    img = Image.from_pe(args.pe)
    seeds = [img.entry]
    if args.csv:
        seeds += [int(r["addr"], 16) for r in csv.DictReader(open(args.csv))]
    t = time.time()
    an = Analysis(img, seeds)
    an.run()
    print("time %.1fs insns %d starts %d bad %d tables %d unresolved-ijmp %d" % (
        time.time() - t, len(an.insns), len(an.starts), len(an.bad), len(an.tables), len(an.unresolved_ijmp)))
    h = collections.Counter((("%s " % i.rep if i.rep else "") + i.mn) for i in an.insns.values())
    print(" ".join("%s:%d" % kv for kv in h.most_common()))
    print("tables", collections.Counter(v[2] for v in an.tables.values()))
    print("bad", [hex(a) for a in sorted(an.bad)][:40])
    print("unresolved", [(hex(a), an.insns[a].text) for a in an.unresolved_ijmp][:80])
    print("seed kinds", collections.Counter(an.seed_kinds.values()))
    print("segments", collections.Counter(o.seg for i in an.insns.values() for o in i.ops if o.t == "m"))
    print("opsize16", sum(1 for i in an.insns.values() if i.opsize16))
    shapes = collections.Counter()
    for i in an.insns.values():
        shapes[(i.mn, tuple("%s%d" % (o.t, o.size) for o in i.ops))] += 1
    rare = [(k, v) for k, v in shapes.items() if k[0] in ("xchg", "push", "pop", "imul", "bt", "bts", "btr", "shld", "shrd", "cmpxchg", "xadd", "enter")]
    print("shapes", sorted(rare, key=lambda kv: -kv[1]))


if __name__ == "__main__":
    main()
