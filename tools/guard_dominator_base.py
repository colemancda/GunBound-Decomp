#!/usr/bin/env python3
"""guard_dominator_base.py - resolve a guard site's base register by proving
which write to it reaches the site, instead of guessing.

WHY THIS EXISTS
guard_cell_resolve.py does a linear back-walk and gives up at a block
boundary ("<esi crosses block end at 0x...>").  sweep_peekbool_apply*.py then
falls back to stable_this(), which only accepts a register written EXACTLY
ONCE, from ECX, in the prologue.  That rule is sound but very conservative:
it rejects a register that is written once before the site and again in some
unrelated tail block, even though nothing can reach the site through the
second write.

The Mobile.cpp sweep (a546b86) resolved seven such sites BY HAND with the
analysis below, so it is worth doing properly:

  1. Find W, the last write to the base register at an address < the site.
  2. Prove W DOMINATES the site: every jump whose target lands inside
     (W, site] must originate inside (W, site] as well.  A source before W
     means some path reaches the site without executing W; a source after
     the site is a back-edge, which means a later write could reach it.
  3. If W is the prologue `mov <reg>, ecx`, the base is `this`.
     If W is `lea <reg>, [<reg2> + OFF2]`, recurse on reg2 and fold OFF2 in.
     Anything else (a spill reload, a call result) is left UNRESOLVED.

Step 2 is the whole point.  Without it this is just "the nearest write
wins", which is exactly the kind of plausible-but-unproven rule that put a
peek result where an object pointer belonged (see the sibling applier's
docstring for that near-miss).

WHAT IT DOES NOT DO
It does not verify the zip between resolver rows and C call sites - that is
the caller's job, and for any function carrying `LAB_00xxxxxx:` labels the C
order is NOT address order.  Bracket the sites between labels first.

Usage:  guard_dominator_base.py <file.c|file.cpp> [family-regex]
        guard_dominator_base.py --range 0xSTART 0xEND [family-regex]
"""
import csv
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
PY = os.path.join(HERE, '.venv-angr/bin/python3')

WRITE_OPS = r'(?:mov|lea|add|sub|xor|or|and|imul|movzx|movsx|pop|sar|shl|shr|inc|dec|neg|not)'
REGS = r'e(?:ax|bx|cx|dx|si|di|bp)'


def disasm(lo, hi):
    out = subprocess.run([PY, os.path.join(HERE, 'disasm_capstone.py'),
                          os.path.join(ROOT, 'orig/GunBound.gme'), hex(lo), hex(hi)],
                         capture_output=True, text=True).stdout
    return [l for l in out.split('\n') if re.match(r'^[0-9a-f]{8}:', l)]


def addr_of(line):
    return int(line[:8], 16)


def writes_to(dis, reg):
    """Every instruction that redefines `reg`, as (addr, line)."""
    pat = re.compile(r'^[0-9a-f]{8}:\t' + WRITE_OPS + r'\t' + reg + r'\b(?!\s*\+)')
    out = []
    for l in dis:
        if pat.match(l) and not re.search(r'\t' + WRITE_OPS + r'\t\S+,\s*' + reg + r'$', l):
            out.append((addr_of(l), l))
    # `xchg`/`cmp`/`test` never redefine; the pattern above already excludes them
    return out


def in_edges(dis):
    """target -> [source, ...] for every direct jump in the range."""
    edges = {}
    for l in dis:
        m = re.search(r'\tj\w+\t(0x[0-9a-f]+)$', l)
        if m:
            edges.setdefault(int(m.group(1), 16), []).append(addr_of(l))
    return edges


def dominates(edges, w_addr, site_addr):
    """True if every path to `site_addr` runs through `w_addr`.

    Conservative and purely local: any jump landing in (w_addr, site_addr]
    must come from inside that same span.  A source at or before w_addr
    bypasses the write; a source after site_addr is a back-edge that could
    carry a later definition around.
    """
    for target, sources in edges.items():
        if not (w_addr < target <= site_addr):
            continue
        for s in sources:
            if s <= w_addr or s > site_addr:
                return False
    return True


def resolve(dis, edges, reg, site_addr, depth=0):
    """(expression, offset) for `reg` at `site_addr`, or (None, reason)."""
    if depth > 4:
        return None, 'recursion too deep'
    prior = [w for w in writes_to(dis, reg) if w[0] < site_addr]
    if not prior:
        if reg == 'eax':
            # a register argument: EAX is live-in (Ghidra spells it in_EAX)
            return 'in_EAX', 0
        return None, '%s has no write before the site' % reg
    w_addr, w_line = prior[-1]
    if not dominates(edges, w_addr, site_addr):
        return None, 'write at 0x%x does not dominate 0x%x' % (w_addr, site_addr)

    m = re.search(r'\tmov\t' + reg + r', ecx$', w_line)
    if m:
        # the prologue `this` capture: ECX must not have been redefined either
        ecx_prior = [w for w in writes_to(dis, 'ecx') if w[0] < w_addr]
        if ecx_prior:
            return None, 'ecx redefined at 0x%x before the capture' % ecx_prior[-1][0]
        return 'this', 0

    m = re.search(r'\tlea\t' + reg + r', \[(' + REGS + r') \+ (0x[0-9a-f]+)\]$', w_line)
    if m:
        base, off = resolve(dis, edges, m.group(1), w_addr, depth + 1)
        if base is None:
            return None, off
        return base, off + int(m.group(2), 16)

    m = re.search(r'\tmov\t' + reg + r', (' + REGS + r')$', w_line)
    if m:
        return resolve(dis, edges, m.group(1), w_addr, depth + 1)

    return None, 'unhandled write: %s' % w_line.split('\t', 1)[1]


def progress_ranges():
    out = {}
    with open(os.path.join(ROOT, 'PROGRESS.csv')) as fh:
        for r in csv.reader(fh):
            try:
                a = int(r[0], 16)
            except (ValueError, IndexError):
                continue
            if len(r) > 1 and r[1].strip().isdigit():
                out[a] = int(r[1])
    return out


def range_for(path):
    head = open(os.path.join(ROOT, path), errors='ignore').read(400)
    m = re.search(r'- 0x00([0-9a-f]{6}) in the original binary', head)
    a = int(m.group(1), 16) if m else None
    if a is None:
        m = re.match(r'FUN_00([0-9a-f]{6})', os.path.basename(path))
        a = int(m.group(1), 16) if m else None
    sizes = progress_ranges()
    return (a, a + sizes[a]) if a in sizes else None


def main():
    if sys.argv[1] == '--range':
        lo, hi = int(sys.argv[2], 16), int(sys.argv[3], 16)
        fam = sys.argv[4] if len(sys.argv) > 4 else r'\w+'
    else:
        rg = range_for(sys.argv[1])
        if not rg:
            print('no PROGRESS.csv entry for %s' % sys.argv[1])
            return
        lo, hi = rg
        fam = sys.argv[2] if len(sys.argv) > 2 else r'\w+'

    rows = subprocess.run([PY, os.path.join(HERE, 'guard_cell_resolve.py'),
                           hex(lo), hex(hi)], capture_output=True, text=True).stdout
    dis = disasm(lo, hi)
    edges = in_edges(dis)

    for line in rows.split('\n'):
        m = re.match(r'!!\s+(\d+) (0x[0-9a-f]+) (%s)\s+cell = '
                     r'<(%s) crosses block end at 0x[0-9a-f]+>(?: \+ (0x[0-9a-f]+))?$'
                     % (fam, REGS), line)
        if not m:
            continue
        idx, site, family, reg, off = m.groups()
        base, val = resolve(dis, edges, reg, int(site, 16))
        if base is None:
            print('%-4s %-10s %-10s UNRESOLVED  (%s)' % (idx, site, family, val))
        else:
            total = val + (int(off, 16) if off else 0)
            print('%-4s %-10s %-10s %s + 0x%x' % (idx, site, family, base, total))


if __name__ == '__main__':
    main()
