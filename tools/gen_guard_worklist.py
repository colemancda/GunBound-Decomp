#!/usr/bin/env python3
"""Build the merged per-file worklist for the CValueGuard call-site sweep:
both guard families in one pass per file.

  - PeekPacketChecksumState (0x40a2e0): argless C sites needing the cell
    (EAX at the original call, from tools/peekpacketchecksumstate_sites.json)
  - EncodeOutgoingPacketField (0x40a380): 1-arg C sites needing the cell
    (EDI at the original call, from tools/encodeoutgoingpacketfield_sites.json)

Assignment is by address containment against the src/ tree's file headers
("<Name> - 0x00xxxxxx in the original binary"). For each family a file is
"clean" when its C site count matches the assigned original sites exactly.
2-arg Encode sites (already fixed by the 2026-07-15 sweep) are listed too
so agents can cross-check the zip alignment against known-correct cells.

Usage: python3 tools/gen_guard_worklist.py
Output: tools/guard_worklist.json
"""
import json
import os
import re
import bisect
from collections import defaultdict

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HDR_RE = re.compile(r'-\s+0x(00[0-9a-fA-F]{6})\s+in the original binary')

# ---- file index ----
addr_files = {}
for root, dirs, files in os.walk(os.path.join(REPO, "src")):
    for fn in files:
        if not fn.endswith((".c", ".cpp")):
            continue
        path = os.path.join(root, fn)
        try:
            with open(path, errors="replace") as f:
                head = f.read(2048)
        except OSError:
            continue
        m = HDR_RE.search(head)
        if m:
            addr_files.setdefault(int(m.group(1), 16), []).append(
                os.path.relpath(path, REPO))
sorted_addrs = sorted(addr_files)


def containing(call_addr):
    i = bisect.bisect_right(sorted_addrs, call_addr) - 1
    if i < 0 or call_addr - sorted_addrs[i] > 0x8000:
        return None
    return sorted_addrs[i]


# ---- C-side site extraction ----
def encode_call_sites(relpath):
    """(line, nargs) for every EncodeOutgoingPacketField call."""
    text = open(os.path.join(REPO, relpath), errors="replace").read()
    out = []
    for m in re.finditer(r'EncodeOutgoingPacketField\s*\(', text):
        i = m.end(); depth = 1; commas = 0
        while i < len(text) and depth:
            c = text[i]
            if c == '(':
                depth += 1
            elif c == ')':
                depth -= 1
            elif c == ',' and depth == 1:
                commas += 1
            i += 1
        line = text[:m.start()].count('\n') + 1
        out.append((line, commas + 1))
    return out


def peek_argless_lines(relpath):
    lines = []
    with open(os.path.join(REPO, relpath), errors="replace") as f:
        for i, line in enumerate(f, 1):
            if "PeekPacketChecksumState()" in line:
                lines.append(i)
    return lines


# ---- original sites ----
with open(os.path.join(REPO, "tools", "peekpacketchecksumstate_sites.json")) as f:
    peek_sites = json.load(f)["PeekPacketChecksumState"]
with open(os.path.join(REPO, "tools", "encodeoutgoingpacketfield_sites.json")) as f:
    enc_sites = json.load(f)

peek_by_file = defaultdict(list)
for s in peek_sites:
    fa = containing(int(s["call_addr"], 16))
    if fa:
        for rp in addr_files[fa]:
            peek_by_file[rp].append(
                {"call_addr": s["call_addr"], "cell": s["eax"], "src": s["eax_src"]})

enc_by_file = defaultdict(list)
for s in enc_sites:
    ca = s.get("call_addr")
    if not ca:
        continue
    fa = containing(int(ca, 16))
    if fa:
        for rp in addr_files[fa]:
            enc_by_file[rp].append(
                {"call_addr": ca, "cell": s.get("edi"), "src": s.get("edi_src")})

# ---- join ----
files = {}
allfiles = set(peek_by_file) | set(enc_by_file)
tot = {"peek_c": 0, "peek_orig": 0, "enc1_c": 0, "enc_orig": 0}
for rp in sorted(allfiles):
    ps = sorted(peek_by_file.get(rp, []), key=lambda s: int(s["call_addr"], 16))
    es = sorted(enc_by_file.get(rp, []), key=lambda s: int(s["call_addr"], 16))
    plines = peek_argless_lines(rp)
    ecalls = encode_call_sites(rp)
    e1 = [l for l, n in ecalls if n == 1]
    e2 = [l for l, n in ecalls if n >= 2]
    entry = {
        "peek": {
            "status": "clean" if len(plines) == len(ps) else "MISMATCH",
            "c_argless_lines": plines,
            "orig_sites": ps,
        },
        "encode": {
            # clean when total C encode calls == total orig sites (the
            # 2-arg ones consumed part of the orig list already)
            "status": "clean" if len(e1) + len(e2) == len(es) else "MISMATCH",
            "c_1arg_lines": e1,
            "c_2arg_lines": e2,
            "orig_sites": es,
        },
    }
    tot["peek_c"] += len(plines); tot["peek_orig"] += len(ps)
    tot["enc1_c"] += len(e1); tot["enc_orig"] += len(es)
    # skip files with nothing to do
    if plines or e1:
        files[rp] = entry

out = {"files": files}
outpath = os.path.join(REPO, "tools", "guard_worklist.json")
with open(outpath, "w") as f:
    json.dump(out, f, indent=2)

nclean = sum(1 for v in files.values()
             if v["peek"]["status"] == "clean" and v["encode"]["status"] == "clean")
print(f"files with work: {len(files)} (fully clean-mapped: {nclean})")
print(f"peek: {tot['peek_c']} argless C lines / {tot['peek_orig']} orig sites")
print(f"encode: {tot['enc1_c']} 1-arg C lines / {tot['enc_orig']} orig sites total")
# workload ranking for agent batching
sized = sorted(files.items(),
               key=lambda kv: -(len(kv[1]["peek"]["c_argless_lines"]) +
                                len(kv[1]["encode"]["c_1arg_lines"])))
print("\ntop 15 files by workload (peek+enc1):")
for rp, v in sized[:15]:
    print(f"  {len(v['peek']['c_argless_lines']):4d}+{len(v['encode']['c_1arg_lines']):3d}  "
          f"[{v['peek']['status'][:5]}/{v['encode']['status'][:5]}]  {rp}")
print(f"Wrote {outpath}")
