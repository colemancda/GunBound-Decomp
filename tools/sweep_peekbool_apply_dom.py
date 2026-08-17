"""PeekPacketChecksumBool applier, dominator edition.

Extends sweep_peekbool_apply.py's mechanics with two upgrades:

1. `<reg crosses block end>` rows are resolved with guard_dominator_base's
   dominance proof instead of the one-write stable_this() rule: the last
   write to the register before the site is accepted only if every jump
   landing between that write and the site also ORIGINATES between them, so
   no path can bypass the write or carry a later definition around a
   back-edge.  This is the analysis that resolved Mobile.cpp's seven
   stragglers by hand (a546b86), now mechanical.

2. The slot zip is validated per-site with LABEL BRACKETING.  Ghidra's
   `LAB_00xxxxxx:` labels are exact addresses, and in goto-shuffled
   functions C text order is NOT address order.  Each applied site must
   satisfy: row address >= the nearest label above it in the text, and row
   addresses within one label-delimited text block must be strictly
   increasing.  A site failing the bracket is skipped (and reported), not
   guessed.

Usage:  sweep_peekbool_apply_dom.py <file.c> [file.c ...]
"""
import csv
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from guard_dominator_base import disasm, in_edges, resolve  # noqa: E402

byaddr = {}
for r in csv.reader(open('PROGRESS.csv')):
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


def cell_expr(row_addr, row, sig, dis, edges, whole):
    m = re.match(r'dword ptr \[0x5b3484\] \+ (0x[0-9a-f]+)$', row)
    if m:
        return '(byte *)(g_clientContext + %s)' % m.group(1)
    m = re.match(r'<(?:ecx|esi|eax|edi) live-in at entry> \+ (0x[0-9a-f]+)$', row)
    off = None
    if m:
        off = int(m.group(1), 16)
    else:
        mm = re.match(r'<(e(?:ax|bx|cx|dx|si|di|bp)) crosses block end at '
                      r'0x[0-9a-f]+>(?: \+ (0x[0-9a-f]+))?$', row)
        if mm:
            base, val = resolve(dis, edges, mm.group(1), row_addr)
            if base == 'this':
                off = val + (int(mm.group(2), 16) if mm.group(2) else 0)
    if off is None or not sig:
        return None
    pm = re.match(r'(.*?)\s*\*?\s*([A-Za-z_][A-Za-z_0-9]*)$', sig)
    if not pm:
        return None
    return ('(byte *)%s + 0x%x' % (pm.group(2), off) if '*' in sig
            else '(byte *)(%s + 0x%x)' % (pm.group(2), off))


nf = ns = nl = nb = 0
for f in sys.argv[1:]:
    rg = rng(f)
    if not rg:
        print('  no range:', f)
        continue
    out = subprocess.run(['tools/.venv-angr/bin/python3', 'tools/guard_cell_resolve.py',
                          hex(rg[0]), hex(rg[1])], capture_output=True, text=True).stdout
    rows = []          # (site address, cell text) in address order
    for l in out.split('\n'):
        m = re.match(r'(?:!!)?\s+\d+ (0x[0-9a-f]+) PeekBool\s+cell = (.*)', l)
        if m:
            rows.append((int(m.group(1), 16), m.group(2).strip()))
    src = open(f, errors='ignore').read().split('\n')
    idx = []
    total = 0
    for i, l in enumerate(src):
        if l.lstrip().startswith('*') or 'PeekPacketChecksumBool(' not in l:
            continue
        for m in re.finditer(r'PeekPacketChecksumBool\(', l):
            if l[m.end():m.end() + 1] == ')':
                idx.append((total, i))
            total += 1
    if not idx or total != len(rows):
        if idx:
            print('  count %d(all %d)/%d: %s' % (len(idx), total, len(rows), f))
        continue

    # label bracketing: every site's zipped row address must be >= the nearest
    # LAB_/joined_r label above it in the text, and rows must be strictly
    # increasing within one label-delimited block.
    labels = [(i, int(m.group(1), 16)) for i, l in enumerate(src)
              for m in [re.search(r'(?:LAB|joined_r0x)_?00([0-9a-f]{6}):', l)] if m]

    def bracket_ok(line_no, row_addr):
        floor = None
        for li, la in labels:
            if li < line_no:
                floor = la
            else:
                break
        return floor is None or row_addr >= floor

    dis = edges = None
    whole = '\n'.join(src)
    sig = None
    for l in src:
        m = re.match(r'^[a-z].*?\((.*?)[,)]', l)
        if m and m.group(1).strip() not in ('void', '') and '(' not in m.group(1):
            sig = m.group(1).strip()
            break
    ch = 0
    prev_addr_by_block = {}
    for slot, i in idx:
        row_addr, row = rows[slot]
        if not bracket_ok(i, row_addr):
            nb += 1
            print('  BRACKET %s C%d row 0x%x' % (f, i + 1, row_addr))
            continue
        blk = max([li for li, _ in labels if li < i], default=-1)
        if blk in prev_addr_by_block and row_addr <= prev_addr_by_block[blk]:
            nb += 1
            print('  ORDER %s C%d row 0x%x' % (f, i + 1, row_addr))
            continue
        prev_addr_by_block[blk] = row_addr
        if dis is None and '<' in row:
            dis = disasm(rg[0], rg[1])
            edges = in_edges(dis)
        ex = cell_expr(row_addr, row, sig, dis or [], edges or {}, whole)
        if ex is None:
            nl += 1
            continue
        src[i] = src[i].replace('PeekPacketChecksumBool()',
                                'PeekPacketChecksumBool(%s)' % ex, 1)
        ch += 1
    if ch:
        open(f, 'w').write('\n'.join(src))
        nf += 1
        ns += ch
print('files=%d sites=%d left=%d bracket-skip=%d' % (nf, ns, nl, nb))
