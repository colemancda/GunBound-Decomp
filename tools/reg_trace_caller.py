#!/usr/bin/env python3
"""Trace a dropped register back to its origin INSIDE the calling function.

Earlier passes disassembled a fixed window before the call.  That is wrong in
both directions: a 160-byte window reaches back past the caller's own entry
into the previous function's epilogue, where `pop esi` reads exactly like a
definition of esi; and it stops short of definitions made earlier in a long
caller, which then look as though the register arrived from outside.  The
first error invented definitions, the second hid them, and together they made
128 of 190 pairs look like the same unhelpful shape.

PROGRESS.csv carries every function's address and size, so the caller can be
disassembled exactly.  Tracing is then bounded by real function limits.

The walk is a linear backward scan, which assumes the definition reaching the
call is the last one textually before it.  That holds inside a straight-line
run and fails across a branch, so any register whose last definition sits
after a jump target is reported as UNSAFE rather than resolved -- the same
discipline that keeps the block-spill resolver honest.

Terminal forms:
  IMMEDIATE     mov reg, 0x...            -> a literal
  GLOBAL        mov reg, [0x...]          -> a named global
  GLOBAL_ADDR   mov/lea reg, 0x... (data) -> the address of a global
  ENTRY         never defined in the caller -> the caller's own incoming
                register, which for a __thiscall caller is usually `this`
  FRAME         mov reg, [esp/ebp + n]    -> a local or parameter
  FIELD         mov reg, [other + n]      -> a field of another object
  TABLE         lea reg, [idx*k + 0x...]  -> an indexed global table
"""

import collections
import csv
import json
import os
import re
import sys

import capstone
import pefile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

SUB = {'eax': {'eax', 'ax', 'al', 'ah'}, 'ebx': {'ebx', 'bx', 'bl', 'bh'},
       'ecx': {'ecx', 'cx', 'cl', 'ch'}, 'edx': {'edx', 'dx', 'dl', 'dh'},
       'esi': {'esi', 'si'}, 'edi': {'edi', 'di'}, 'ebp': {'ebp', 'bp'}}
FULL = {}
for k, v in SUB.items():
    for a in v:
        FULL[a] = k

DATA_LO, DATA_HI = 0x544000, 0xf3d000


def load():
    pe = pefile.PE(os.path.join(ROOT, 'orig/GunBound.gme'), fast_load=True)
    sec = [s for s in pe.sections if s.Name.rstrip(b'\x00') == b'.text'][0]
    base = pe.OPTIONAL_HEADER.ImageBase + sec.VirtualAddress
    funcs = []
    for r in csv.reader(open(os.path.join(ROOT, 'PROGRESS.csv'))):
        try:
            funcs.append((int(r[0], 16), int(r[1]), r[2]))
        except (ValueError, IndexError):
            pass
    funcs.sort()
    return base, sec.get_data(), funcs


def caller_of(funcs, va):
    import bisect
    i = bisect.bisect_right([f[0] for f in funcs], va) - 1
    if i < 0:
        return None
    a, size, name = funcs[i]
    return (a, size, name) if a <= va < a + size else None


def disasm_function(md, data, base, a, size):
    return list(md.disasm(data[a - base: a - base + size], a))


def branch_targets(ins):
    t = set()
    for i in ins:
        if i.mnemonic.startswith('j'):
            m = re.match(r'^0x([0-9a-f]+)$', i.op_str.strip())
            if m:
                t.add(int(m.group(1), 16))
    return t


def trace(ins, call_va, reg, depth=8):
    """Walk `reg` backwards from the call; return (form, detail, safe)."""
    targets = branch_targets(ins)
    cur = reg
    limit = call_va
    for _ in range(depth):
        defn = None
        for i in ins:
            if i.address >= limit:
                break
            if i.mnemonic in ('push', 'cmp', 'test', 'call') or i.mnemonic.startswith('j'):
                if i.mnemonic == 'call':
                    # a call clobbers eax; that IS a definition
                    if cur == 'eax':
                        defn = i
                continue
            d = i.op_str.split(',')[0].strip()
            if d in SUB.get(cur, set()):
                defn = i
        if defn is None:
            return ('ENTRY', cur, True)
        # a definition that is jumped over is not necessarily the one reaching
        # the call
        safe = not any(defn.address < t <= call_va for t in targets)
        # capstone spells memory operands "dword ptr [esp + 0xb0]"; without
        # stripping the size prefix every memory form falls through to OTHER,
        # which is what made that bucket look like the dominant shape.
        o = re.sub(r'\b(?:byte|word|dword|qword|xmmword) ptr ', '', defn.op_str)
        mn = defn.mnemonic
        if mn == 'call':
            return ('RETVAL', defn.op_str, safe)
        m = re.match(r'\w+, (0x[0-9a-f]+|\d+)$', o)
        if m and mn == 'mov':
            v = int(m.group(1), 0)
            if DATA_LO <= v < DATA_HI:
                return ('GLOBAL_ADDR', '0x%x' % v, safe)
            return ('IMMEDIATE', '0x%x' % v, safe)
        if re.match(r'(\w+), \1$', o) and mn == 'xor':
            return ('IMMEDIATE', '0x0', safe)
        m = re.match(r'\w+, \[(0x[0-9a-f]+)\]$', o)
        if m:
            return ('GLOBAL', m.group(1), safe)
        m = re.match(r'\w+, \[(?:\w+\*\d \+ )?(0x[0-9a-f]+)\]$', o)
        if m and mn == 'lea':
            return ('TABLE', m.group(1), safe)
        m = re.match(r'\w+, \[(esp|ebp) ([-+]) (0x[0-9a-f]+)\]$', o)
        if m:
            return ('FRAME', '%s%s%s' % (m.group(1), m.group(2), m.group(3)), safe)
        m = re.match(r'\w+, \[(\w+) ([-+]) (0x[0-9a-f]+)\]$', o)
        if m and FULL.get(m.group(1)):
            # Resolve the BASE one level further.  A displacement that is
            # itself a data address means the arena-offset idiom -- the port
            # writes it as "&DAT_00xxxxxx + g_clientContext" -- so the whole
            # expression is recoverable once the base is known to be the
            # context.  Stopping at FIELD hides that.
            bform, bdetail, bsafe = trace(ins, defn.address, FULL[m.group(1)],
                                          depth - 1)
            return ('FIELD', '%s %s | base=%s(%s)' % (mn, o, bform, bdetail),
                    safe and bsafe)
        m = re.match(r'\w+, (\w+)$', o)
        if m and FULL.get(m.group(1)) and mn in ('mov', 'lea'):
            cur, limit = FULL[m.group(1)], defn.address
            continue
        m = re.match(r'\w+, \[(\w+) \+ (0x[0-9a-f]+)\]$', o)
        if m and FULL.get(m.group(1)) and mn == 'lea':
            return ('FIELD', '%s %s' % (mn, o), safe)
        return ('OTHER', '%s %s' % (mn, o), safe)
    return ('DEEP', cur, False)


def main():
    triage = json.load(open(os.path.join(ROOT, 'tools/backlog_triage.json')))
    base, data, funcs = load()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    cache = {}

    shapes = collections.Counter()
    unsafe = collections.Counter()
    rows = []
    for e in triage:
        if e['sites'] != 1:
            continue
        va = int(e['per_site'][0]['va'], 16)
        c = caller_of(funcs, va)
        if not c:
            shapes['NO-CALLER'] += 1
            continue
        a, size, cname = c
        if a not in cache:
            cache[a] = disasm_function(md, data, base, a, size)
        form, detail, safe = trace(cache[a], va, e['reg'])
        shapes[form] += 1
        if not safe:
            unsafe[form] += 1
        rows.append({'func': e['func'], 'reg': e['reg'], 'path': e['path'],
                     'caller': cname, 'caller_va': '0x%x' % a, 'va': '0x%x' % va,
                     'form': form, 'detail': detail, 'safe': safe})
    json.dump(rows, open(os.path.join(ROOT, 'tools/reg_trace.json'), 'w'), indent=1)
    print('%-12s %6s %8s' % ('FORM', 'PAIRS', 'UNSAFE'))
    for k, v in shapes.most_common():
        print('%-12s %6d %8d' % (k, v, unsafe[k]))


if __name__ == '__main__':
    main()
