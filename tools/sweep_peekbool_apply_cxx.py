"""PeekPacketChecksumBool applier for the multi-function C++ ports.

Mobile.cpp/Projectile.cpp hold several promoted methods in one file, so the
whole-file zip pbapply.py uses cannot work.  These files DO carry a
`/* 0xADDR <name>` banner before each method, which is an exact address for
the segment - so segment the file on those banners and zip each segment
against its own function's resolver rows.
"""
import subprocess, csv, re, os, sys

byaddr = {}
for r in csv.reader(open('PROGRESS.csv')):
    if len(r) > 2 and r[1].strip().isdigit():
        byaddr[int(r[0], 16)] = int(r[1])

def stable_this(dis, reg):
    w = [l for l in dis
         if re.match(r'^[0-9a-f]{8}:\t(mov|lea|add|sub|xor|or|and|imul|movzx)\t' + reg + r',', l)]
    return len(w) == 1 and re.search(r'\tmov\t' + reg + r', ecx$', w[0]) is not None

def expr(r, whole, this_expr, dis):
    m = re.match(r'dword ptr \[0x5b3484\] \+ (0x[0-9a-f]+)$', r)
    if m:
        return '(unsigned char *)(g_clientContext + %s)' % m.group(1)
    m = re.match(r'dword ptr \[\w+ \+ (0x621e[04])\] \+ (0x[0-9a-f]+)$', r)
    if m:
        mm = re.search(r'\(([A-Za-z_][A-Za-z_0-9]*) \+ ' + m.group(1) + r'\)', whole)
        base = mm.group(1) if mm else 'g_clientContext'
        return '(unsigned char *)(*(int *)(%s + %s) + %s)' % (base, m.group(1), m.group(2))
    m = re.match(r'<(ecx|esi|eax|edi) live-in at entry> \+ (0x[0-9a-f]+)$', r)
    if m is None:
        mm = re.match(r'<(esi|ebp|ebx|edi) crosses block end at 0x[0-9a-f]+> \+ (0x[0-9a-f]+)$', r)
        if mm and stable_this(dis, mm.group(1)):
            m = mm
    if m and this_expr:
        return this_expr % m.group(2)
    return None

path = sys.argv[1]
src = open(path, errors='ignore').read().split('\n')
marks = [(i, int(m.group(1), 16)) for i, l in enumerate(src)
         for m in [re.match(r'/\* 0x(4[0-9a-f]{5}) ', l)] if m]
marks.append((len(src), None))
whole = '\n'.join(src)
total_applied = total_left = 0
for k in range(len(marks) - 1):
    a, addr = marks[k]
    b = marks[k + 1][0]
    if addr not in byaddr:
        continue
    idx = []
    n = 0
    for i in range(a, b):
        l = src[i]
        if l.lstrip().startswith('*') or 'PeekPacketChecksumBool' not in l:
            continue
        # `PeekPacketChecksumBool_2(...)` / `_5(...)` ARE calls to 0x4065a0 -
        # Ghidra fabricated a signature out of the pushes belonging to the
        # NEXT call (verified by address, see the Mobile.cpp sweep commit).
        # They occupy a slot in the row sequence but must not be rewritten.
        for m in re.finditer(r'PeekPacketChecksumBool(_\d+)?\(', l):
            if m.group(1) is None and l[m.end():m.end() + 1] == ')':
                idx.append((n, i))
            n += 1
    if not idx:
        continue
    # some promoted methods keep Ghidra's `param_1 = (int *)this` alias and
    # index off it; use whichever spelling that segment actually uses.
    seg = '\n'.join(src[a:b])
    THIS = ('(unsigned char *)param_1 + %s' if re.search(r'param_1\s*=\s*reinterpret_cast<int \*>\(this\)', seg)
            else '(unsigned char *)this + %s')
    lo, hi = addr, addr + byaddr[addr]
    out = subprocess.run(['tools/.venv-angr/bin/python3', 'tools/guard_cell_resolve.py',
                          hex(lo), hex(hi)], capture_output=True, text=True).stdout
    dis = subprocess.run(['tools/.venv-angr/bin/python3', 'tools/disasm_capstone.py',
                          'orig/GunBound.gme', hex(lo), hex(hi)],
                         capture_output=True, text=True).stdout.split('\n')
    rows = [m.group(1).strip() for l in out.split('\n')
            for m in [re.match(r'(?:!!)?\s+\d+ 0x[0-9a-f]+ PeekBool\s+cell = (.*)', l)] if m]
    if n != len(rows):
        print('  0x%x seg: %d(all %d)/%d rows - skipped' % (addr, len(idx), n, len(rows)))
        continue
    for slot, i in idx:
        ex = expr(rows[slot], whole, THIS, dis)
        if ex is None:
            total_left += 1
            continue
        src[i] = src[i].replace('PeekPacketChecksumBool()',
                                'PeekPacketChecksumBool(%s)' % ex, 1)
        total_applied += 1
open(path, 'w').write('\n'.join(src))
print('%s applied=%d left=%d' % (path, total_applied, total_left))
