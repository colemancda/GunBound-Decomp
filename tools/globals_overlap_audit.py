#!/usr/bin/env python3
"""Check that no sized global's extent swallows another declared address.

globals_sized.c gives real storage to globals whose address is used as a
larger object than the one-byte cell globals.c gives everything.  Getting a
size wrong in the generous direction is not caught by anything: the array
compiles, the program runs, and the only symptom is that a DIFFERENT global
which lives inside that range now has its own separate storage -- so writes
through one are invisible to the other.

That is the split-struct bug this tree has hit repeatedly (g_replayContext,
g_wordFilterArrayHeader, the input-event ring), and the reason
g_workerThreadBlock's neighbours were converted to offset-macros rather than
left as independent scalars.

This flags every sized global whose [base, base+size) contains another address
the tree declares, EXCLUDING those already reconciled as SUBFIELD macros.
An entry here is not automatically a bug -- it is the question "should this be
a subfield?" asked at every place it can be asked.
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import globals_resolve as G


def sized_globals():
    """(addr, size, name) for every array-typed definition we can place."""
    m = G.build_map()
    name2addr = {v: int(k, 16) for k, v in m.items()}
    out = []
    for path in ('src/globals.c', 'src/globals_sized.c', 'src/aes_tables.c'):
        src = open(os.path.join(ROOT, path), errors='replace').read()
        for d in re.finditer(
                r'^(?:const\s+)?([A-Za-z_][A-Za-z0-9_ ]*?)\s+([A-Za-z_][A-Za-z0-9_]*)'
                r'\s*\[\s*([^\]]+?)\s*\]\s*(?:=|;)', src, re.M):
            typ, name, size = d.group(1), d.group(2), d.group(3)
            a = name2addr.get(name)
            if a is None:
                continue
            try:
                n = eval(size, {'__builtins__': {}}, {})
            except Exception:
                continue
            el = 4 if ('32' in typ or typ.strip() in ('int', 'unsigned int', 'uint')) else \
                 (2 if '16' in typ else 1)
            out.append((a, n * el, name, os.path.basename(path)))
    return sorted(out)


def main():
    m = G.build_map()
    addrs = sorted(int(k, 16) for k in m)
    subfield = set()
    hdr = open(os.path.join(ROOT, 'include/globals.h'), errors='replace').read()
    # Two reconciliation forms are in use, and counting only one reports
    # already-fixed overlaps as problems:
    #   #define DAT_x SUBFIELD(blob, off, ty)
    #   #define DAT_x (*(uint32_t*)(&blob+off))
    for s in re.finditer(r'#define\s+_?(?:PTR_)?DAT_(00[0-9a-f]+)\s+'
                         r'(?:SUBFIELD|\(\s*\*\s*\([^)]*\)\s*\(\s*&)', hdr):
        subfield.add(int(s.group(1), 16))

    import bisect
    problems = 0
    for a, size, name, where in sized_globals():
        lo = bisect.bisect_right(addrs, a)
        hi = bisect.bisect_left(addrs, a + size)
        inside = [x for x in addrs[lo:hi] if x not in subfield]
        if inside:
            problems += 1
            print('%-28s 0x%06x + 0x%-6x (%s)' % (name, a, size, where))
            for x in inside[:6]:
                print('      contains 0x%06x  %-28s  at +0x%x'
                      % (x, m['%08x' % x], x - a))
            if len(inside) > 6:
                print('      ... and %d more' % (len(inside) - 6))
    print('\nsized globals overlapping another declared address: %d' % problems)


if __name__ == '__main__':
    main()
