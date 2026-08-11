#!/usr/bin/env python3
"""Build the per-file worklist for the PeekPacketChecksumState dropped-EAX
sweep (Phase 2 of the CValueGuard migration).

Joins:
  - tools/peekpacketchecksumstate_sites.json (PeekPacketChecksumState
    section: every original `call 0x40a2e0` with its recovered EAX cell)
  - the src/ tree's file headers ("<Name> - 0x00xxxxxx in the original
    binary"), which give each ported file's original function address
  - each file's argless `PeekPacketChecksumState()` call lines

For every ported file the original sites are assigned by address
containment (file's header addr <= call_addr < next ported header addr),
then zipped against the file's argless call lines in order. A file is
"clean" when the counts match exactly; mismatches are flagged for
disasm-assisted mapping (goto-shuffled decompiles reorder blocks, so
order-zip alone is not trusted there anyway - the per-site eax_src
address lets an agent disambiguate).

Usage: python3 tools/gen_peek_worklist.py
Output: tools/peek_worklist.json + a summary to stdout
"""
import json
import os
import re
import subprocess
from collections import defaultdict

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SITES = os.path.join(REPO, "tools", "peekpacketchecksumstate_sites.json")

HDR_RE = re.compile(r'-\s+0x(00[0-9a-fA-F]{6})\s+in the original binary')

# 1. addr -> file index from headers
addr_files = defaultdict(list)
for root, dirs, files in os.walk(os.path.join(REPO, "src")):
    for fn in files:
        if not (fn.endswith(".c") or fn.endswith(".cpp")):
            continue
        path = os.path.join(root, fn)
        try:
            with open(path, errors="replace") as f:
                head = f.read(2048)
        except OSError:
            continue
        m = HDR_RE.search(head)
        if m:
            addr_files[int(m.group(1), 16)].append(os.path.relpath(path, REPO))

dup_addrs = {hex(a): fs for a, fs in addr_files.items() if len(fs) > 1}

# 2. argless call lines per file
def argless_lines(relpath):
    lines = []
    with open(os.path.join(REPO, relpath), errors="replace") as f:
        for i, line in enumerate(f, 1):
            if "PeekPacketChecksumState()" in line:
                lines.append(i)
    return lines

# 3. assign sites to files by containment
with open(SITES) as f:
    sites = json.load(f)["PeekPacketChecksumState"]

sorted_addrs = sorted(addr_files)

def containing_file_addr(call_addr):
    import bisect
    i = bisect.bisect_right(sorted_addrs, call_addr) - 1
    if i < 0:
        return None
    return sorted_addrs[i]

by_file = defaultdict(list)
unassigned = []
for s in sites:
    ca = int(s["call_addr"], 16)
    fa = containing_file_addr(ca)
    if fa is None:
        unassigned.append(s)
        continue
    # heuristic guard: a function is rarely > 0x8000 bytes
    if ca - fa > 0x8000:
        unassigned.append(s)
        continue
    for relpath in addr_files[fa]:
        by_file[relpath].append(s)

worklist = {}
clean = mismatched = 0
for relpath, fsites in sorted(by_file.items()):
    fsites.sort(key=lambda s: int(s["call_addr"], 16))
    lines = argless_lines(relpath)
    status = "clean" if len(lines) == len(fsites) else "MISMATCH"
    if status == "clean":
        clean += 1
    else:
        mismatched += 1
    worklist[relpath] = {
        "status": status,
        "c_argless_lines": lines,
        "orig_sites": [
            {"call_addr": s["call_addr"], "eax": s["eax"], "eax_src": s["eax_src"]}
            for s in fsites
        ],
    }

out = {
    "duplicate_header_addrs": dup_addrs,
    "unassigned_sites": [s["call_addr"] for s in unassigned],
    "files": worklist,
}
outpath = os.path.join(REPO, "tools", "peek_worklist.json")
with open(outpath, "w") as f:
    json.dump(out, f, indent=2)

total_sites = sum(len(v["orig_sites"]) for v in worklist.values())
total_lines = sum(len(v["c_argless_lines"]) for v in worklist.values())
print(f"files in worklist: {len(worklist)} (clean: {clean}, mismatch: {mismatched})")
print(f"orig sites assigned: {total_sites}, C argless lines: {total_lines}")
print(f"unassigned orig sites: {len(unassigned)}")
print(f"duplicate-claim addrs: {len(dup_addrs)}")
print(f"Wrote {outpath}")
print("\nMISMATCH files (top 20 by |delta|):")
mm = [(abs(len(v['c_argless_lines']) - len(v['orig_sites'])), k,
       len(v['c_argless_lines']), len(v['orig_sites']))
      for k, v in worklist.items() if v['status'] == 'MISMATCH']
for d, k, cl, os_ in sorted(mm, reverse=True)[:20]:
    print(f"  C={cl:4d} orig={os_:4d}  {k}")
