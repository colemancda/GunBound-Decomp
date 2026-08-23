#!/usr/bin/env python3
"""Dump the register and stack setup at every binary call site of a function.

Used to answer one question: when a port's call site passes FEWER arguments
than the definition declares, what were the missing ones?

That situation is more dangerous than it looks.  Appending a recovered
register at a short call site puts it in the wrong parameter slot, and if the
declaration in functions.h is K&R-empty the compiler cannot object -- so the
value silently lands in an unrelated parameter and the result looks recovered.

Where a missing parameter turns out to hold the SAME value at every call site,
it can be filled without pairing binary sites to source sites at all, which is
what makes re-slotting safe for those functions.

Usage: callsite_regs.py <name-or-hex-va>
"""

import struct
import sys
import os

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import capstone
from reg_trace_caller import load, caller_of, disasm_function

REGS = ('eax', 'ebx', 'ecx', 'edx', 'esi', 'edi')


def target_va(arg, funcs):
    try:
        return int(arg, 16)
    except ValueError:
        for a, _, n in funcs:
            if n == arg:
                return a
    raise SystemExit('no such function: %s' % arg)


def main():
    base, data, funcs = load()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    tgt = target_va(sys.argv[1], funcs)

    sites = []
    for off in range(len(data) - 5):
        if data[off] != 0xE8:
            continue
        if base + off + 5 + struct.unpack('<i', data[off + 1:off + 5])[0] == tgt:
            sites.append(base + off)
    print('target 0x%x  call sites: %d\n' % (tgt, len(sites)))
    print('%-10s %-34s %s' % ('VA', 'CALLER', 'SETUP'))
    cols = {r: [] for r in REGS}
    pushes = []
    for va in sites:
        c = caller_of(funcs, va)
        if not c:
            print('0x%-8x %-34s <no caller>' % (va, '?'))
            continue
        ins = disasm_function(md, data, base, c[0], c[1])
        prev = [i for i in ins if i.address < va]
        vals = {}
        ps = []
        for i in prev[-16:]:
            o = i.op_str
            if i.mnemonic == 'push':
                ps.append(o.strip())
                continue
            if i.mnemonic == 'call':
                ps = []
                vals = {}
                continue
            d = o.split(',')[0].strip()
            if d in REGS:
                if i.mnemonic == 'xor' and o == '%s, %s' % (d, d):
                    vals[d] = '0'
                elif i.mnemonic in ('mov', 'lea'):
                    vals[d] = o.split(',', 1)[1].strip()
                else:
                    vals[d] = '%s %s' % (i.mnemonic, o)
        for r in REGS:
            cols[r].append(vals.get(r))
        pushes.append(ps)
        setup = ' '.join('%s=%s' % (r, vals[r]) for r in REGS if r in vals)
        print('0x%-8x %-34s %s | push %s' % (va, c[2], setup, ps or '-'))

    print('\nuniformity across sites (a value present and identical everywhere '
          'can be filled\nwithout pairing binary sites to source sites):')
    for r in REGS:
        vs = cols[r]
        got = [v for v in vs if v is not None]
        if got and len(set(got)) == 1 and len(got) == len(vs):
            print('  %-4s UNIFORM  %s' % (r, got[0]))
        elif got:
            print('  %-4s varies   %d/%d set, %d distinct'
                  % (r, len(got), len(vs), len(set(got))))


if __name__ == '__main__':
    main()
