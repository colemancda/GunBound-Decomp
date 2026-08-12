#!/usr/bin/env python3
"""Side-by-side sweep worksheet for one file: C call sites vs resolved cells.

Prints the file's unfixed guard call sites (argless Peek / 1-arg Encode) with a
line of context, then the disassembly-resolved cell for every guard site in the
function, so the C-line -> original-site mapping can be checked in one view
instead of alternating between four tools.

    tools/.venv-angr/bin/python3 tools/guard_file_report.py src/unnamed/FUN_00491b40.c

The function's start address comes from the header comment ("- 0xNNNNNNNN in the
original binary"); the end is taken past the last site in tools/
guard_worklist.json, with slack for trailing sites of other families.

This only lays the evidence out. The mapping itself is still a judgement call:
counts matching is NOT proof of a correct zip, because Ghidra emits if/else
branches in source order while the compiler may have laid the else out first
(this swapped a pair of Encode cells in DetonateProjectile).  Check landmarks.
"""
import json
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)


def main():
    rel = os.path.relpath(os.path.abspath(sys.argv[1]), ROOT)
    text = open(os.path.join(ROOT, rel), encoding="utf-8", errors="replace").read()
    lines = text.split("\n")

    m = re.search(r"- 0x([0-9a-fA-F]{6,8}) in the original binary", text)
    if not m:
        sys.exit("no '- 0xNNNNNNNN in the original binary' in the header")
    start = int(m.group(1), 16)

    wl = json.load(open(os.path.join(ROOT, "tools/guard_worklist.json")))["files"]
    entry = wl.get(rel, {})
    ends = [int(s["call_addr"], 16)
            for fam in ("peek", "encode")
            for s in entry.get(fam, {}).get("orig_sites", [])]
    # the worklist's site list already respects the function's extent, so key
    # off its last site: disassembling far past the end pulls in the NEXT
    # function's guard sites and silently breaks the C-site-count comparison
    end = (max(ends) if ends else start + 0x400) + 0x40

    print("== %s   0x%x-0x%x" % (rel, start, end))
    for fam, status in (("peek", entry.get("peek", {}).get("status")),
                        ("encode", entry.get("encode", {}).get("status"))):
        n = len(entry.get(fam, {}).get("orig_sites", []))
        print("   worklist %-7s status=%-9s orig_sites=%d" % (fam, status, n))

    print("\n== unfixed C sites (line: text) ==")
    n = 0
    for i, s in enumerate(lines, 1):
        if s.lstrip().startswith("*"):
            continue
        hit = "PeekPacketChecksumState()" in s
        if not hit and "EncodeOutgoingPacketField(" in s:
            # count a comma at paren depth 0 - splitting on the first ")"
            # misreads a cast, e.g. `Encode((int)piVar5 + 0xb728, local_10)`
            arg, depth = s.split("EncodeOutgoingPacketField(", 1)[1], 1
            hit = True
            for ch in arg:
                depth += "([".count(ch) - ")]".count(ch)
                if depth == 0:
                    break
                if ch == "," and depth == 1:
                    hit = False
                    break
        if hit:
            n += 1
            print("%3d  %5d: %s" % (n, i, s.strip()))
    print("   (%d unfixed C sites)" % n)

    print("\n== resolved original sites ==")
    subprocess.run([os.path.join(HERE, ".venv-angr/bin/python3"),
                    os.path.join(HERE, "guard_cell_resolve.py"), hex(start), hex(end)],
                   cwd=ROOT)


if __name__ == "__main__":
    main()
