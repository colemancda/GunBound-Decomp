#!/usr/bin/env python3
"""Apply PeekPacketChecksumBool cells by OFFSET-SIBLING reuse.

For a site whose base guard_cell_resolve.py could not name, look at the byte
offset it DOES report and see whether the same file already spells that exact
offset with a base, at a site an earlier verified pass fixed.  If there is
exactly one such base, reuse it; if there are none or several, leave the site
alone.

This is deliberately narrow, and in particular it does NOT trust the
resolver's `dword ptr [esp + N] + OFF` back-trace.  Checking one of those by
hand (DetonateShot1_Bullet12, 0x4b2247) showed the trace is misleading: the
slot it names is NOT the slot the object lives in.  Both stores to [esp+0x30]
there land with a push live, so they normalise to +0x2c and hold PEEK
RESULTS, not the object; the site's own instruction is lea eax,[ebx+0xf3f]
and ebx is reloaded from the real +0x30 further up.  The offset sibling is
the evidence here, not the trace.

The independent confirmation is semantic: at these sites the same register is
also used as lea edi,[<reg>+0x3813], the blast-name string, which is
unambiguously a field of the projectile object - so the base is the object,
and 0xf3c/0xf3f/0xf4c are consecutive 3-byte GuardedBool cells on it.

Usage:  sweep_peekbool_sibling.py <file.c> [file.c ...]
"""
import csv
import os
import re
import subprocess
import sys

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


nf = ns = 0
for f in sys.argv[1:]:
    r = rng(f)
    if not r:
        continue
    out = subprocess.run(['tools/.venv-angr/bin/python3', 'tools/guard_cell_resolve.py',
                          hex(r[0]), hex(r[1])], capture_output=True, text=True).stdout
    rows = [m.group(1).strip() for l in out.split('\n')
            for m in [re.match(r'(?:!!)?\s+\d+ 0x[0-9a-f]+ PeekBool\s+cell = (.*)', l)] if m]
    src = open(f, errors='ignore').read().split('\n')
    idx = []
    n = 0
    for i, l in enumerate(src):
        if l.lstrip().startswith('*') or 'PeekPacketChecksumBool(' not in l:
            continue
        for m in re.finditer(r'PeekPacketChecksumBool\(', l):
            if l[m.end():m.end() + 1] == ')':
                idx.append((n, i))
            n += 1
    # the zip is only meaningful when every original call has a C counterpart
    if not idx or n != len(rows):
        continue
    whole = '\n'.join(src)
    ch = 0
    for slot, i in idx:
        m = re.search(r'\+ (0x[0-9a-f]+)$', rows[slot])
        if not m:
            continue
        off = m.group(1)
        bases = set(re.findall(
            r'PeekPacketChecksumBool\(\(byte \*\)([A-Za-z_][A-Za-z_0-9]*) \+ '
            + re.escape(off) + r'\)', whole))
        bases |= set(re.findall(
            r'PeekPacketChecksumBool\(\(byte \*\)\(([A-Za-z_][A-Za-z_0-9]*) \+ '
            + re.escape(off) + r'\)\)', whole))
        if len(bases) != 1:
            continue
        src[i] = src[i].replace('PeekPacketChecksumBool()',
                                'PeekPacketChecksumBool((byte *)%s + %s)' % (bases.pop(), off), 1)
        ch += 1
    if ch:
        open(f, 'w').write('\n'.join(src))
        nf += 1
        ns += ch
print('files=%d sites=%d' % (nf, ns))
