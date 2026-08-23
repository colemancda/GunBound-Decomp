#!/usr/bin/env python3
"""For functions whose call sites omit REGISTER arguments, find the uniform ones.

callsite_arity_audit.py identifies where the omission is (declared parameters
minus ret_N/4).  This asks what the missing values ARE, for the subset where
the answer needs no per-site work: a register loaded with the same value at
every call site is determined by that fact alone, with nothing to pair up.

Which register goes with which parameter is NOT assumed from Ghidra's
__fastcall/__thiscall label, because that label is unreliable here -- several
functions in this tree are EAX-first conventions that Ghidra reports as
__fastcall.  Instead every general register is scanned at every call site and
the uniform ones are reported, leaving the mapping to be confirmed against the
callee's entry.

Output is a proposal list; it edits nothing.
"""

import collections
import csv
import json
import os
import re
import struct
import sys

import capstone
import pefile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import callsites
from reg_trace_caller import load, caller_of, disasm_function

REGS = ('eax', 'ebx', 'ecx', 'edx', 'esi', 'edi')


def main():
    base, data, funcs = load()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    addr_of = {n: (a, s) for a, s, n in funcs}

    want = json.load(open(os.path.join(ROOT, 'tools/regparam_targets.json')))

    # one pass for the E8 map
    targets = {addr_of[n][0]: n for n in want if n in addr_of}
    sites = collections.defaultdict(list)
    for off in range(len(data) - 5):
        if data[off] != 0xE8:
            continue
        t = base + off + 5 + struct.unpack('<i', data[off + 1:off + 5])[0]
        if t in targets:
            sites[targets[t]].append(base + off)

    cache = {}
    out = []
    for name in want:
        vas = sites.get(name, [])
        if not vas:
            continue
        cols = collections.defaultdict(list)
        for va in vas:
            c = caller_of(funcs, va)
            if not c:
                continue
            if c[0] not in cache:
                cache[c[0]] = disasm_function(md, data, base, c[0], c[1])
            vals = {}
            for i in cache[c[0]]:
                if i.address >= va:
                    break
                o = re.sub(r'\b(?:byte|word|dword) ptr ', '', i.op_str)
                if i.mnemonic == 'call':
                    vals = {}
                    continue
                d = o.split(',')[0].strip()
                if d in REGS:
                    if i.mnemonic == 'xor' and o == '%s, %s' % (d, d):
                        vals[d] = '0'
                    elif i.mnemonic in ('mov', 'lea'):
                        vals[d] = o.split(',', 1)[1].strip()
                    else:
                        vals[d] = None
            for r in REGS:
                cols[r].append(vals.get(r))
        uni = {}
        for r in REGS:
            v = cols[r]
            got = [x for x in v if x is not None]
            if got and len(got) == len(v) and len(set(got)) == 1:
                uni[r] = got[0]
        if uni:
            out.append({'func': name, 'sites': len(vas), 'uniform': uni})

    out.sort(key=lambda x: -x['sites'])
    json.dump(out, open(os.path.join(ROOT, 'tools/regparam_uniform.json'), 'w'), indent=1)
    print('functions examined            : %d' % len(want))
    print('with at least one UNIFORM reg : %d  (%d call sites)\n'
          % (len(out), sum(o['sites'] for o in out)))
    for o in out[:30]:
        print('%-34s %4d  %s' % (o['func'], o['sites'],
                                 ' '.join('%s=%s' % kv for kv in o['uniform'].items())))


if __name__ == '__main__':
    main()
