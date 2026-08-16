#!/usr/bin/env python3
"""guard_base_hint.py - suggest the C expression for a guard site whose base
register guard_cell_resolve.py could not follow ("<reg crosses block end>").

Why this exists: in the goto-shuffled detonation/spawn functions the object
pointer lives in a callee-saved register set far above the site, so the linear
back-walk gives up.  But the SAME object is almost always already spelled out
elsewhere in the same C file, because the 2026-07 encode sweep and the 2026-08
peek sweep named hundreds of sibling cells on it.  So: take the unresolved
site's byte offset, convert it to the int-pointer offset the C would use
(off/4), and grep the file for every existing expression carrying either form.
A single distinct base across the hits is a very strong candidate; several
different bases means the site needs a real trace.

This SUGGESTS, it does not decide - always eyeball the hit it prints, and
prefer a hit that sits in the same C block as the site.

Usage:  guard_base_hint.py <file.c> [family-regex]
"""
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)


def progress_range(base):
    import csv
    with open(os.path.join(ROOT, 'PROGRESS.csv')) as fh:
        for r in csv.reader(fh):
            if len(r) > 2 and r[2] == base and r[1].strip().isdigit():
                s = int(r[0], 16)
                return s, s + int(r[1])
    return None


def main():
    path = sys.argv[1]
    fam = sys.argv[2] if len(sys.argv) > 2 else r'\w+'
    base = os.path.splitext(os.path.basename(path))[0]
    rng = progress_range(base)
    if not rng:
        print('no PROGRESS.csv entry for %s' % base)
        return
    out = subprocess.run(
        [os.path.join(HERE, '.venv-angr/bin/python3'),
         os.path.join(HERE, 'guard_cell_resolve.py'), hex(rng[0]), hex(rng[1])],
        capture_output=True, text=True).stdout
    src = open(os.path.join(ROOT, path), errors='ignore').read().split('\n')

    for line in out.split('\n'):
        # two shapes carry a base the resolver could not name:
        #   !!  N 0xADDR FAM  cell = <reg crosses block end at 0x..> + 0xOFF
        #       N 0xADDR FAM  cell = dword ptr [esp + 0xN] + 0xOFF
        # the second is a spilled object pointer - just as unnamed, and just
        # as likely to be spelled elsewhere in the file.
        m = re.match(r'!!\s+(\d+) (0x[0-9a-f]+) (%s)\s+cell = <([^>]+)> \+ (0x[0-9a-f]+)'
                     % fam, line)
        if not m:
            m = re.match(r'\s+(\d+) (0x[0-9a-f]+) (%s)\s+cell = '
                         r'(dword ptr \[esp \+ 0x[0-9a-f]+\]) \+ (0x[0-9a-f]+)' % fam, line)
        if not m:
            continue
        idx, addr, family, why, off = m.groups()
        byteoff = int(off, 16)
        forms = {'0x%x' % byteoff}
        if byteoff % 4 == 0:
            forms.add('0x%x' % (byteoff // 4))
        hits = []
        for i, s in enumerate(src, 1):
            if s.lstrip().startswith('*') or s.lstrip().startswith('/*'):
                continue
            for f in forms:
                if re.search(r'\+\s*' + re.escape(f) + r'\b', s):
                    b = re.findall(r'([A-Za-z_][A-Za-z_0-9]*(?:\[[^\]]*\])?)\s*\+\s*'
                                   + re.escape(f) + r'\b', s)
                    hits.append((i, f, b, s.strip()[:96]))
        bases = sorted({b for _, _, bs, _ in hits for b in bs})
        print('%s %-10s +%s   (%s)' % (addr, family, off, why))
        if bases:
            print('     candidate base(s): %s' % ', '.join(bases))
        for i, f, b, s in hits[:3]:
            print('     C%-5d %s' % (i, s))
        if not hits:
            print('     no sibling expression in this file - needs a real trace')
        print()


if __name__ == '__main__':
    main()
