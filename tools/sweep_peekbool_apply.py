"""Apply the mechanical PeekPacketChecksumBool cell forms.

Range lookup is ADDRESS-based (from the file's own '- 0xNNNNNNNN in the
original binary' header, falling back to the FUN_ basename), not name-based:
15 of these files are the MobileNN_MainAction family, whose PROGRESS.csv rows
were renamed while the files kept their FUN_ names.
"""
import subprocess, csv, re, os, sys

byaddr = {}
for r in csv.reader(open('PROGRESS.csv')):
    if len(r) > 2 and r[1].strip().isdigit():
        byaddr[int(r[0], 16)] = int(r[1])

def rng(path):
    head = open(path, errors='ignore').read(400)
    m = re.search(r'- 0x00([0-9a-f]{6}) in the original binary', head)
    a = None
    if m:
        a = int(m.group(1), 16)
    else:
        m = re.match(r'FUN_00([0-9a-f]{6})', os.path.basename(path))
        if m:
            a = int(m.group(1), 16)
    if a is None or a not in byaddr:
        return None
    return a, a + byaddr[a]

def stable_this(dis, reg):
    """True if `reg` is captured ONCE, from ECX, in the prologue - i.e. it holds
    the __fastcall/__thiscall `this` for the whole function.  Any second write
    means the register is reused and the site needs a real trace."""
    w = [l for l in dis
         if re.match(r'^[0-9a-f]{8}:\t(mov|lea|add|sub|xor|or|and|imul|movzx)\t' + reg + r',', l)]
    return len(w) == 1 and re.search(r'\tmov\t' + reg + r', ecx$', w[0]) is not None


def expr(r, whole, sig, dis=None):
    m = re.match(r'dword ptr \[0x5b3484\] \+ (0x[0-9a-f]+)$', r)
    if m:
        return '(byte *)(g_clientContext + %s)' % m.group(1)
    m = re.match(r'dword ptr \[\w+ \+ (0x621e[04])\] \+ (0x[0-9a-f]+)$', r)
    if m:
        mm = re.search(r'\(([A-Za-z_][A-Za-z_0-9]*) \+ ' + m.group(1) + r'\)', whole)
        base = mm.group(1) if mm else 'g_clientContext'
        return '(byte *)(*(int *)(%s + %s) + %s)' % (base, m.group(1), m.group(2))
    m = re.match(r'<(ecx|esi|eax|edi) live-in at entry> \+ (0x[0-9a-f]+)$', r)
    if m is None and dis is not None:
        # a callee-saved register the linear back-walk lost.  Safe to call it
        # `this` ONLY if the whole function writes it exactly once, from ECX,
        # in the prologue - checked against the disassembly, not assumed.
        mm = re.match(r'<(esi|ebp|ebx|edi) crosses block end at 0x[0-9a-f]+> \+ (0x[0-9a-f]+)$', r)
        if mm and stable_this(dis, mm.group(1)):
            m = mm
    if m and sig:
        pm = re.match(r'(.*?)\s*\*?\s*([A-Za-z_][A-Za-z_0-9]*)$', sig)
        if pm:
            return ('(byte *)%s + %s' % (pm.group(2), m.group(2)) if '*' in sig
                    else '(byte *)(%s + %s)' % (pm.group(2), m.group(2)))
    return None

nf = ns = nl = 0
for f in sys.argv[1:]:
    rg = rng(f)
    if not rg:
        print('  no range:', f); continue
    out = subprocess.run(['tools/.venv-angr/bin/python3', 'tools/guard_cell_resolve.py',
                          hex(rg[0]), hex(rg[1])], capture_output=True, text=True).stdout
    dis = subprocess.run(['tools/.venv-angr/bin/python3', 'tools/disasm_capstone.py',
                          'orig/GunBound.gme', hex(rg[0]), hex(rg[1])],
                         capture_output=True, text=True).stdout.split('\n')
    rows = []
    for l in out.split('\n'):
        m = re.match(r'(?:!!)?\s+\d+ (0x[0-9a-f]+) PeekBool\s+cell = (.*)', l)
        if m:
            rows.append(m.group(2).strip())
    src = open(f, errors='ignore').read().split('\n')
    # Zip against EVERY call site, not just the arg-less ones: earlier sweeps
    # already fixed some, and the resolver still reports a row for those.  A
    # line can hold more than one call (short-circuit chains), so count
    # occurrences, not lines.
    idx = []          # (line index, occurrence-within-line) for arg-less calls
    total = 0
    for i, l in enumerate(src):
        if l.lstrip().startswith('*') or 'PeekPacketChecksumBool(' not in l:
            continue
        for m in re.finditer(r'PeekPacketChecksumBool\(', l):
            argless = l[m.end():m.end() + 1] == ')'
            if argless:
                idx.append((total, i))
            total += 1
    if not idx or total != len(rows):
        print('  count %d(all %d)/%d: %s' % (len(idx), total, len(rows), f)); continue
    whole = '\n'.join(src)
    base = os.path.splitext(os.path.basename(f))[0]
    sig = None
    for l in src:
        m = re.match(r'^[a-z].*?\((.*?)[,)]', l)
        if m and m.group(1).strip() not in ('void', '') and '(' not in m.group(1):
            sig = m.group(1).strip(); break
    ch = 0
    for slot, i in idx:
        ex = expr(rows[slot], whole, sig, dis)
        if ex is None:
            nl += 1; continue
        src[i] = src[i].replace('PeekPacketChecksumBool()',
                                'PeekPacketChecksumBool(%s)' % ex, 1)
        ch += 1
    if ch:
        open(f, 'w').write('\n'.join(src)); nf += 1; ns += ch
print('files=%d sites=%d left=%d' % (nf, ns, nl))
