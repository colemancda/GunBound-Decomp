#!/usr/bin/env python3
"""guard_label_zip.py - the CORRECT row<->site assignment for goto-shuffled
functions, as an auditor for past sweeps and a fixer for bare sites.

THE BUG THIS EXISTS TO CATCH (found 2026-08-17): every mechanical PeekBool
applier so far zipped C call sites in TEXT order against resolver rows in
ADDRESS order.  For straight-line functions those coincide; in goto-shuffled
functions they do not, and the zip silently assigns cell A's offset to cell
B's call.  Concrete case: DetonateProjectile.c line 217 sits under
`LAB_004583d9:` - the block at 0x4583d9 is `lea eax,[ebx+0xf3f]` /
`mov byte [ebx+0x14],1` / `call 0x4065a0`, and the C matches it statement
for statement - but the naive zip wrote `param_1 + 0x3918`, the cell of the
site at 0x45738c.  Both are real cells of this function, so nothing failed
to compile; the value read would simply be the wrong guard.

THE ASSIGNMENT RULE.  Ghidra emits a label definition wherever it moves a
block textually, and within one text segment (the lines between two label
definitions) addresses are contiguous and increasing.  So the segments
partition the function's address space, and each segment's interval is
[its own label address, the next label address in SORTED order).  Rows
falling in that interval, in address order, map to the segment's sites in
text order - a per-segment zip whose counts must match per segment, not
just per file.

REFUSALS.  switch cases (`caseD_N:`) are label definitions whose address is
NOT derivable from the name, so a file containing one gets no assignment at
all rather than a wrong interval table.  Same for any label form this
parser does not recognise.

Usage:
  guard_label_zip.py --audit <file.c> [...]   compare applied cells, report
  guard_label_zip.py --fix   <file.c> [...]   also fill bare sites + repair
                                              provably misassigned applied
                                              cells (offset forms only)
"""
import csv
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
PY = os.path.join(HERE, '.venv-angr/bin/python3')

FAMILY = 'PeekBool'
CALL = 'PeekPacketChecksumBool'

byaddr = {}
for r in csv.reader(open(os.path.join(ROOT, 'PROGRESS.csv'))):
    if len(r) > 2 and r[1].strip().isdigit():
        byaddr[int(r[0], 16)] = int(r[1])


def rng(path):
    head = open(path, errors='ignore').read(400)
    m = re.search(r'- 0x00([0-9a-f]{6}) in the original binary', head)
    a = int(m.group(1), 16) if m else None
    if a is None:
        m = re.match(r'FUN_00([0-9a-f]{6})', os.path.basename(path))
        a = int(m.group(1), 16) if m else None
    return (a, a + byaddr[a]) if a in byaddr else None


LABEL = re.compile(r'^\s*(?:LAB|joined_r0x|code_r0x)_?00([0-9a-f]{6}):\s*$')
ANY_LABEL = re.compile(r'^\s*\w+:\s*$')
KNOWN_NONLABEL = re.compile(r'^\s*(?:default|case\b|[A-Za-z_]\w*_exit)\s*:?\s*$')


def segments(src, base):
    """[(start_line, addr)], or None if an unparseable label form exists."""
    segs = [(0, base)]
    for i, l in enumerate(src):
        m = LABEL.match(l)
        if m:
            segs.append((i, int(m.group(1), 16)))
            continue
        if ANY_LABEL.match(l) and not KNOWN_NONLABEL.match(l) \
                and not re.match(r'^\s*(?:public|private|protected)\s*:', l):
            return None
    return segs


def row_offset(cell):
    m = re.search(r'\+ (0x[0-9a-f]+)$', cell)
    return int(m.group(1), 16) if m else None


def applied_offset(argtext):
    """The trailing offset of an applied cell expression, or None."""
    m = re.search(r'\+ (0x[0-9a-f]+)\)?$', argtext.strip())
    if not m:
        return None
    off = int(m.group(1), 16)
    # int-pointer arithmetic scales by 4: `param_1 + 0x3d5` is byte 0xf54
    b = re.match(r'\(byte \*\)\s*\(?([A-Za-z_]\w*) \+', argtext.strip())
    if b:
        return off
    p = re.match(r'\s*([A-Za-z_]\w*) \+', argtext.strip())
    if p:
        return None  # unscaled int-pointer form: can't compare bytes safely
    return off


def sites_in(src):
    """Every CALL occurrence: (line, occurrence-in-line, argtext or None)."""
    out = []
    for i, l in enumerate(src):
        if l.lstrip().startswith('*') or CALL + '(' not in l:
            continue
        for m in re.finditer(re.escape(CALL) + r'(_\d+)?\(', l):
            if m.group(1) is not None:
                out.append((i, m.start(), 'VARIANT'))
                continue
            depth = 1
            j = m.end()
            while j < len(l) and depth:
                depth += {'(': 1, ')': -1}.get(l[j], 0)
                j += 1
            arg = l[m.end():j - 1]
            out.append((i, m.start(), arg if arg else None))
    return out


def assign(path):
    """Yield (site, row) pairs plus diagnostics for one file."""
    rg = rng(path)
    if not rg:
        return None, 'no range'
    src = open(path, errors='ignore').read().split('\n')
    segs = segments(src, rg[0])
    if segs is None:
        return None, 'unparseable label form (switch case?)'
    out = subprocess.run([PY, os.path.join(HERE, 'guard_cell_resolve.py'),
                          hex(rg[0]), hex(rg[1])], capture_output=True, text=True).stdout
    rows = []
    for l in out.split('\n'):
        m = re.match(r'(?:!!)?\s+\d+ (0x[0-9a-f]+) %s\s+cell = (.*)' % FAMILY, l)
        if m:
            rows.append((int(m.group(1), 16), m.group(2).strip()))
    sites = sites_in(src)
    if len(sites) != len(rows):
        return None, 'file count %d != %d rows' % (len(sites), len(rows))

    # interval for each segment: [own addr, next addr in sorted order)
    addrs = sorted(a for _, a in segs) + [rg[1]]
    nxt = {a: addrs[i + 1] for i, a in enumerate(addrs[:-1])}

    def seg_of_line(i):
        cur = segs[0]
        for s in segs:
            if s[0] <= i:
                cur = s
            else:
                break
        return cur

    pairs = []
    by_seg = {}
    for s in sites:
        by_seg.setdefault(seg_of_line(s[0])[1], []).append(s)
    used = set()
    for seg_addr, seg_sites in sorted(by_seg.items()):
        lo, hi = seg_addr, nxt[seg_addr]
        seg_rows = [r for r in rows if lo <= r[0] < hi]
        if len(seg_rows) != len(seg_sites):
            return None, 'segment 0x%x: %d sites / %d rows' % (
                seg_addr, len(seg_sites), len(seg_rows))
        for st, rw in zip(seg_sites, seg_rows):
            pairs.append((st, rw))
            used.add(rw[0])
    if len(used) != len(rows):
        return None, 'rows outside all segments'
    return pairs, src


def main():
    mode = sys.argv[1]
    bad = fixed = audited = 0
    for path in sys.argv[2:]:
        pairs, src = assign(path)
        if pairs is None:
            print('SKIP %-55s %s' % (path, src))
            continue
        changed = False
        for (line, col, arg), (raddr, cell) in pairs:
            if arg == 'VARIANT':
                continue
            roff = row_offset(cell)
            if arg is None:
                if mode == '--fix' and roff is not None and '<' not in cell \
                        and 'esp' not in cell:
                    m = re.match(r'dword ptr \[0x5b3484\] \+ (0x[0-9a-f]+)$', cell)
                    if m:
                        ex = '(byte *)(g_clientContext + %s)' % m.group(1)
                    else:
                        continue
                    src[line] = src[line][:col] + src[line][col:].replace(
                        CALL + '()', CALL + '(%s)' % ex, 1)
                    changed = True
                    fixed += 1
                continue
            audited += 1
            aoff = applied_offset(arg)
            if aoff is None or roff is None:
                continue
            if aoff != roff:
                bad += 1
                print('WRONG %s:%d  applied +0x%x  but row 0x%x says +0x%x  (%s)'
                      % (path, line + 1, aoff, raddr, roff, cell))
        if changed:
            open(path, 'w').write('\n'.join(src))
    print('audited=%d wrong=%d fixed=%d' % (audited, bad, fixed))


if __name__ == '__main__':
    main()
