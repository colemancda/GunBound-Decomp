#!/usr/bin/env python3
"""Audit recovered render-call arguments against the original binary.

The FindSpriteFrame / BlitSprite16bpp / BlitSpriteClipped sweeps recover
arguments from SOURCE-level evidence: the three calls in a render block share
a frame and an outer key, so a recovered one states the others' arguments.
That reasoning is only as good as "the calls I read really are in the same
block", and a window that spills into a neighbouring block produces confident,
compiling, completely wrong values.

This is the independent check. tools/findspriteframe_regs.json holds the
(EDX, ESI) = (outerKey, frame) pairs scanned from the original at every
FindSpriteFrame call site. For each function, the multiset of literal pairs
appearing in the SOURCE must be contained in the multiset scanned from the
BINARY. A pair the source claims more often than the binary uses it is a
block-spill bug.

Containment, not equality: the binary side only counts sites where both
registers were immediates, so it is legitimately smaller.

This caught a real defect the moment it was written - State10_Loading_Render
claiming frame 0x17 twice where the binary has 0x17 once and 0 once, from a
600-character window reaching back into the previous block.

Usage:
  python3 tools/render_args_audit.py
Exit status is 1 if any source-only pair is found.
"""
import collections
import glob
import json
import os
import re
import sys

REGS = "tools/findspriteframe_regs.json"
CALL = re.compile(r"FindSpriteFrame\(\(int\)&DAT_00ea0e18,(0x[0-9a-f]+|\d+),(0x[0-9a-f]+|\d+)\)")


def lit(ev, reg):
    if not ev or "<not set>" in ev:
        return None
    ins = ev.split(": ", 1)[1]
    m = re.match(r"mov %s, (0x[0-9a-f]+|\d+)$" % reg, ins)
    if m:
        return int(m.group(1), 0)
    if re.match(r"xor (\w+), \1$", ins):
        return 0
    return None


def main():
    binary = collections.defaultdict(collections.Counter)
    for r in json.load(open(REGS)):
        binary[r["func"]][(lit(r.get("edx"), "edx"), lit(r.get("esi"), "esi"))] += 1

    by_name = {}
    for p in glob.glob("src/**/*.c", recursive=True):
        by_name.setdefault(os.path.basename(p)[:-2], p)

    bad = 0
    for func, expected in sorted(binary.items()):
        path = by_name.get(func)
        if not path or not os.path.exists(path):
            continue
        src = re.sub(r"/\*.*?\*/", "", open(path, errors="replace").read(), flags=re.S)
        found = collections.Counter()
        for m in CALL.finditer(src):
            found[(int(m.group(1), 0), int(m.group(2), 0))] += 1
        extra = found - expected
        if extra:
            bad += sum(extra.values())
            print("  %-50s claims not in the binary: %s" % (path, dict(extra)))

    print("source-only (outerKey, frame) pairs: %d" % bad)
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
