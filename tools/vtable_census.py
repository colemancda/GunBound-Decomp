#!/usr/bin/env python3
"""vtable_census.py - enumerate EVERY vtable in GunBound.gme without RTTI.

WHY NOT RTTI.  The game is compiled /GR- (verified 2026-07-12 with Ghidra's
RecoverClassesFromRTTIScript, and 2026-08-18 by byte-scan: the only .?AV
type descriptors are the statically-linked CRT/ATL runtime's own 8 classes).
RTTIWindowsClassRecoverer therefore recovers nothing game-related, ever.

WHAT WORKS INSTEAD.  MSVC installs a vtable with `mov [reg], imm32` /
`mov [reg+disp], imm32` inside the ctor/dtor, so every vtable's address
appears as a 4-byte immediate in .text.  This scans .text for all aligned
and unaligned little-endian dwords pointing into the data sections, keeps
the ones whose target is an array of pointers into .text, and walks each
array's slots:

  - slot walk stops when a dword stops pointing into .text, or when the
    next address is itself an installed vtable (the packed-vtable boundary
    that made 13-slot reads overrun - see Projectile.h / Effects.h).
  - each slot is labeled from PROGRESS.csv; slots inside a known function
    but not at its start are labeled mid-func (thunk-table artifacts);
    slots in code Ghidra NEVER CARVED are flagged UNCARVED - that is how
    the four effect Draw/Tick bodies were found, and this makes the hunt
    exhaustive.

Output: one line per vtable (address, #install sites, slot count) followed
by its slots.  --uncarved prints only vtables containing uncarved slots.

Heuristics, stated: an install immediate that is never dereferenced as a
vtable (e.g. a data pointer stored into a struct) is filtered by requiring
slot 0 to point into .text; string/data false positives fail that.  A
vtable referenced only via base-class ctor inlining still shows up because
the inlined store is in .text all the same.
"""
import csv
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)

d = open(os.path.join(ROOT, 'orig/GunBound.gme'), 'rb').read()
pe = struct.unpack_from('<I', d, 0x3c)[0]
nsec = struct.unpack_from('<H', d, pe + 6)[0]
opt = struct.unpack_from('<H', d, pe + 20)[0]
base = struct.unpack_from('<I', d, pe + 24 + 28)[0]
secs = []
for i in range(nsec):
    name, vs, va, rs, ro = struct.unpack_from('<8sIIII', d, pe + 24 + opt + i * 40)[:5]
    secs.append((name.rstrip(b'\0').decode(), base + va, max(vs, rs), ro))

def sec(name):
    for s in secs:
        if s[0] == name:
            return s
    return None

text = sec('.text')
TEXT_LO, TEXT_HI = text[1], text[1] + text[2]

def va2off(va):
    for _, sva, size, ro in secs:
        if sva <= va < sva + size:
            return ro + (va - sva)
    return None

def u32(va):
    o = va2off(va)
    return struct.unpack_from('<I', d, o)[0] if o is not None else None

# --- every function start/extent Ghidra carved -------------------------------
starts = {}
extents = []
for r in csv.reader(open(os.path.join(ROOT, 'PROGRESS.csv'))):
    try:
        a = int(r[0], 16)
    except (ValueError, IndexError):
        continue
    if len(r) > 2 and r[1].strip().isdigit():
        starts[a] = r[2]
        extents.append((a, a + int(r[1])))
extents.sort()

def classify(va):
    if va in starts:
        return starts[va]
    import bisect
    i = bisect.bisect_right(extents, (va, 1 << 40)) - 1
    if 0 <= i < len(extents) and extents[i][0] <= va < extents[i][1]:
        return 'mid:%s+0x%x' % (starts[extents[i][0]], va - extents[i][0])
    return 'UNCARVED'

# --- all dword immediates in .text that point into a data section ------------
DATA_RANGES = [(s[1], s[1] + s[2]) for s in secs if s[0] in ('.rdata', '.data')]
def in_data(v):
    return any(lo <= v < hi for lo, hi in DATA_RANGES)

to, tlen = text[3], text[2]
raw = d[to:to + tlen]
installs = {}
for i in range(len(raw) - 3):
    v = struct.unpack_from('<I', raw, i)[0]
    if in_data(v):
        installs.setdefault(v, []).append(TEXT_LO + i)

# --- keep candidates whose slot 0 is a code pointer --------------------------
cands = {}
for v in installs:
    s0 = u32(v)
    if s0 is not None and TEXT_LO <= s0 < TEXT_HI:
        cands[v] = installs[v]

boundaries = set(cands)

def walk(vt):
    slots = []
    va = vt
    while True:
        s = u32(va)
        if s is None or not (TEXT_LO <= s < TEXT_HI):
            break
        slots.append(s)
        va += 4
        if va in boundaries:
            break
        if len(slots) >= 64:
            break
    return slots

def main():
    only_uncarved = '--uncarved' in sys.argv
    rows = []
    for vt in sorted(cands):
        slots = walk(vt)
        if len(slots) < 2:
            continue          # single-pointer data, not a vtable
        labels = [classify(s) for s in slots]
        unc = sum(1 for l in labels if l == 'UNCARVED')
        rows.append((vt, len(cands[vt]), slots, labels, unc))
    print('%d candidate vtables (>=2 slots, slot0 in .text)' % len(rows))
    for vt, ninst, slots, labels, unc in rows:
        if only_uncarved and unc == 0:
            continue
        print('\nvtable 0x%x  installs=%d  slots=%d%s' % (
            vt, ninst, len(slots), ('  UNCARVED=%d' % unc) if unc else ''))
        for i, (s, l) in enumerate(zip(slots, labels)):
            print('  %2d: 0x%06x  %s' % (i, s, l))


if __name__ == '__main__':
    main()
