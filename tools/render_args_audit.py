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
    bad += audit_blit_keys()
    return 1 if bad else 0


def split_top(text):
    args, depth, cur = [], 0, ""
    for ch in text:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            args.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip() or args:
        args.append(cur.strip())
    return [a for a in args if a]


def audit_blit_keys():
    """Same containment check for BlitSpriteClipped's recovered outerKey.

    Only the KEY is checked, not the frame. The frame comes from the source in
    the first place, and a source-side "not an integer literal" is not the same
    property as a binary-side "not an immediate push" - comparing those two
    manufactures 25 mismatches that are purely an artefact of the encoding.

    Sites where the binary's EDX was not an immediate cannot be attributed to a
    key at all, so they are carried as SLACK: a function may legitimately show
    that many source keys beyond what the scan pinned down.
    """
    path_of = {}
    for p in glob.glob("src/**/*.c", recursive=True):
        path_of.setdefault(os.path.basename(p)[:-2], p)
    binary = collections.defaultdict(collections.Counter)
    slack = collections.Counter()
    for r in json.load(open("tools/blitspriteclipped_regs.json")):
        m = re.match(r"mov edx, (0x[0-9a-f]+|\d+)$", r["edx"] or "")
        if m:
            binary[r["func"]][int(m.group(1), 0)] += 1
        else:
            slack[r["func"]] += 1
    bad = 0
    for func in sorted(set(binary) | set(slack)):
        path = path_of.get(func)
        if not path or not os.path.exists(path):
            continue
        src = re.sub(r"/\*.*?\*/", "", open(path, errors="replace").read(), flags=re.S)
        found = collections.Counter()
        for m in re.finditer(r"\bBlitSpriteClipped\(", src):
            depth, j = 1, m.end()
            while depth and j < len(src):
                if src[j] == "(":
                    depth += 1
                elif src[j] == ")":
                    depth -= 1
                j += 1
            a = split_top(src[m.end():j - 1])
            if len(a) != 4:
                continue
            try:
                found[int(a[3], 0)] += 1
            except ValueError:
                pass
        surplus = sum((found - binary[func]).values())
        if surplus > slack[func]:
            bad += surplus - slack[func]
            print("  %-50s outerKeys beyond the binary: %s (slack %d)"
                  % (path, dict(found - binary[func]), slack[func]))
    print("unexplained BlitSpriteClipped outerKey claims: %d" % bad)
    return bad


if __name__ == "__main__":
    sys.exit(main())
