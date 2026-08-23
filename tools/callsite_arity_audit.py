#!/usr/bin/env python3
"""Find every function whose call sites disagree with its own definition.

A missing argument is invisible in this tree.  Ghidra drops stack arguments as
readily as register ones, and functions.h declares most functions K&R-empty
("void f();"), which in C accepts ANY argument list -- so a call passing four
arguments to a six-parameter definition compiles without complaint and the
callee reads two slots of whatever the caller happened to leave on the stack.

Every signature repair on this branch so far was found by tripping over one of
these by accident.  This looks for them on purpose.

Reported disagreements are LEADS, not verdicts.  Some are deliberate: several
widely-called functions are held K&R-empty on purpose so that a partial
migration stays buildable, and those are flagged separately rather than mixed
in with the unknowns.  The real signature always has to come from `ret N` plus
the call-site setup in the original -- this only says where to look.
"""

import collections
import csv
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import callsites

DEFN = re.compile(r'\b([A-Za-z_]\w*)\s*\(([^;{()]*(?:\([^()]*\)[^;{()]*)*)\)\s*\n?\s*\{')
# Deliberately K&R-empty, documented in their own headers: a partial migration
# needs the old call sites to keep compiling while the sweep is in progress.
INTENTIONAL = {'RemoveWidget', 'ScrambleChecksumGuardBytes', 'TreeLowerBound',
               'QueueBroadcastEvent', 'BroadcastQueuedEvent', 'CheckGuardedBoolAnd',
               'PeekBool', 'EncodeBool', 'RescrambleBool', 'DecodeGuardedBool',
               'RescrambleGuardedBool', 'EncodeGuardedBool'}


def load():
    out = []
    for b, _, files in os.walk(os.path.join(ROOT, 'src')):
        for f in sorted(files):
            if f.endswith(('.c', '.cpp')):
                p = os.path.join(b, f)
                t = open(p, errors='replace').read()
                out.append((p, t, callsites.blank_comments(t)))
    return out


def ret_bytes():
    """name -> the operand of the function's first `ret`, from the original.

    This is what turns an "arity mismatch" into a statement.  For a __thiscall
    or __fastcall function Ghidra declares the REGISTER arguments as param_1
    (and param_2), so a definition can hold ten parameters while `ret 0x24`
    says only nine of them are on the stack.  The call sites are then not
    missing a stack argument at all -- they are missing exactly the register
    arguments, which is the dropped-register problem seen from the callee's
    declared signature instead of from an `in_EAX` local.

    dropped_reg_backlog.py cannot see these, because it looks for the local.
    """
    import capstone
    import pefile
    pe = pefile.PE(os.path.join(ROOT, 'orig/GunBound.gme'), fast_load=True)
    sec = [x for x in pe.sections if x.Name.rstrip(b'\x00') == b'.text'][0]
    base = pe.OPTIONAL_HEADER.ImageBase + sec.VirtualAddress
    data = sec.get_data()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    out = {}
    for r in csv.reader(open(os.path.join(ROOT, 'PROGRESS.csv'))):
        try:
            a, size, name = int(r[0], 16), int(r[1], 16 if False else 10), r[2]
        except (ValueError, IndexError):
            continue
        off = a - base
        if off < 0 or off + size > len(data):
            continue
        for i in md.disasm(data[off:off + size], a):
            if i.mnemonic == 'ret':
                out[name] = int(i.op_str, 16) if i.op_str.strip() else 0
                break
    return out


def arity(a):
    v = callsites.split_args(a)
    return 0 if (len(v) == 1 and v[0].strip() in ('void', '')) or not v else len(v)


def main():
    files = load()
    defs = {}
    for p, s, b in files:
        for m in DEFN.finditer(b):
            name = m.group(1)
            if name in callsites.KEYWORDS:
                continue
            defs[name] = (p, arity(m.group(2)))

    short = collections.defaultdict(list)
    for p, s, b in files:
        rel = os.path.relpath(p, ROOT)
        for name in set(re.findall(r'\b([A-Za-z_]\w*)\s*\(', b)):
            if name not in defs or name in callsites.KEYWORDS:
                continue
            dn = defs[name][1]
            for c in callsites.find(s, name, b):
                if c['kind'] != 'call':
                    continue
                n = arity(s[c['open']:c['close']])
                if n != dn:
                    short[name].append((rel, s[:c['start']].count('\n') + 1, n, dn))

    rets = ret_bytes()
    explained = {}
    for k, v in list(short.items()):
        rb = rets.get(k)
        if rb is None:
            continue
        stack_args = rb // 4
        dn = v[0][3]
        regs = dn - stack_args
        got = {x[2] for x in v}
        if regs > 0 and got == {stack_args}:
            explained[k] = (len(v), dn, stack_args, regs)
    for k in explained:
        short.pop(k, None)

    print('EXPLAINED BY REGISTER ARGUMENTS: %d functions, %d call sites'
          % (len(explained), sum(v[0] for v in explained.values())))
    print('  every call site passes exactly ret_N/4 arguments, so what is')
    print('  absent is the register argument(s) Ghidra declared as param_1/2:')
    for k, (n, dn, sa, rg) in sorted(explained.items(), key=lambda kv: -kv[1][0])[:12]:
        print('    %-32s %4d sites  params=%-3d stack=%-3d regs=%d'
              % (k, n, dn, sa, rg))
    print()

    known = {k: v for k, v in short.items() if k in INTENTIONAL}
    unknown = {k: v for k, v in short.items() if k not in INTENTIONAL}
    print('functions defined              : %d' % len(defs))
    print('with disagreeing call sites    : %d  (%d sites)'
          % (len(short), sum(len(v) for v in short.values())))
    print('  deliberately K&R (excluded)  : %d  (%d sites)'
          % (len(known), sum(len(v) for v in known.values())))
    print('  UNEXPLAINED                  : %d  (%d sites)\n'
          % (len(unknown), sum(len(v) for v in unknown.values())))
    rows = sorted(unknown.items(), key=lambda kv: -len(kv[1]))
    print('%-34s %6s %5s %5s  %s' % ('FUNCTION', 'SITES', 'DEF', 'GOT', 'EXAMPLE'))
    for name, v in rows[:40]:
        got = sorted({x[2] for x in v})
        print('%-34s %6d %5d %5s  %s:%d'
              % (name, len(v), v[0][3], ','.join(map(str, got)), v[0][0], v[0][1]))
    import json
    json.dump({k: v for k, v in unknown.items()},
              open(os.path.join(ROOT, 'tools/callsite_arity.json'), 'w'), indent=1)


if __name__ == '__main__':
    main()
