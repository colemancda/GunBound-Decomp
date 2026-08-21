#!/usr/bin/env python3
"""Triage the dropped-register backlog by HOW the callers supply the register.

The backlog ranks by call-site count, which is a poor guide to effort: today
ScrambleChecksumGuardBytes (1070 sites) went in one pass while DrawFontString
(30) is blocked, because what matters is not how many callers there are but
whether they all say the same thing.

For each open (function, register) pair this scans every direct call site in
the original and buckets the instruction that last writes the register:

  IMMEDIATE   the same literal everywhere - a global or a constant. Sweeps
              mechanically; this is the ScrambleChecksumGuardBytes/EBX,
              TreeLowerBound/EAX, FindSpriteFrame/EAX shape.
  CTX-REL     `add <reg>, 0x00xxxxxx` after a load of g_clientContext - also
              uniform, spelled `&DAT_00xxxxxx + g_clientContext`.
  OBJ-REL     `lea <reg>, [<obj> + 0xNNN]` - a field address off an object
              pointer. The OFFSET is uniform and recoverable; only the base
              needs naming, and a local witness often supplies it (see
              CheckGuardedBoolAnd, where the cell is the guarded bool + 4).
  STACK       `mov <reg>, [esp + N]` - a caller local; needs frame
              calibration per site.
  REGISTER    `mov <reg>, esi/edi/ebp` - a caller local held live; needs
              per-site register->variable mapping. NO mechanical route.

A pair that is >90% IMMEDIATE or CTX-REL is worth doing now. One that is
mostly REGISTER needs a local witness in the C (an enclosing `if`, a sibling
call in the same block) or it is per-site hand work - see the render-chain
and guard-family headers for both outcomes.

Usage: python3 tools/reg_uniformity_triage.py [--top N]
"""
import argparse
import bisect
import collections
import csv
import json
import os
import re
import struct

import capstone
import pefile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SUB = {'eax': {'eax', 'ax', 'al'}, 'ebx': {'ebx', 'bx', 'bl'},
       'ecx': {'ecx', 'cx', 'cl'}, 'edx': {'edx', 'dx', 'dl'},
       'esi': {'esi', 'si'}, 'edi': {'edi', 'di'}, 'ebp': {'ebp', 'bp'}}


def load_text():
    pe = pefile.PE(os.path.join(ROOT, 'orig/GunBound.gme'), fast_load=True)
    ib = pe.OPTIONAL_HEADER.ImageBase
    sec = [s for s in pe.sections if s.Name.rstrip(b'\x00') == b'.text'][0]
    return ib + sec.VirtualAddress, sec.get_data()


def classify(ins):
    if re.match(r'mov \w+, (0x[0-9a-f]+|\d+)$', ins):
        return 'IMMEDIATE'
    if re.match(r'add \w+, 0x[0-9a-f]{6}$', ins):
        return 'CTX-REL'
    if re.match(r'xor (\w+), \1$', ins):
        return 'IMMEDIATE'
    if 'esp +' in ins or 'ebp -' in ins:
        return 'STACK'
    if re.match(r'lea \w+, \[\w+ [-+] 0x[0-9a-f]+\]$', ins):
        return 'OBJ-REL'          # <object> + fixed offset: a field address
    if re.match(r'(mov|lea) \w+, \w+$', ins):
        return 'REGISTER'
    return 'OTHER'


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--top', type=int, default=15)
    args = ap.parse_args()

    rows = []
    for r in csv.reader(open(os.path.join(ROOT, 'PROGRESS.csv'))):
        try:
            rows.append((int(r[0], 16), int(r[1]), r[2]))
        except ValueError:
            continue
    rows.sort()
    addr_of = {nm: a for a, _, nm in rows}

    base, data = load_text()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    open_pairs = json.load(open(os.path.join(ROOT, 'tools/dropped_regs_confirmed.json')))
    import subprocess
    live = subprocess.run(['python3', os.path.join(ROOT, 'tools/dropped_reg_backlog.py'),
                           '--json', '/tmp/_triage_open.json', '--top', '0'],
                          capture_output=True, text=True, cwd=ROOT)
    open_pairs = json.load(open('/tmp/_triage_open.json'))
    open_pairs.sort(key=lambda e: -e['callsites'])

    print('%7s %-30s %-5s  %s' % ('SITES', 'FUNCTION', 'REG', 'how the callers supply it'))
    for e in open_pairs[:args.top]:
        target = addr_of.get(e['func'])
        if target is None:
            continue
        hits = []
        for off in range(len(data) - 5):
            if data[off] != 0xE8:
                continue
            if base + off + 5 + struct.unpack('<i', data[off + 1:off + 5])[0] == target:
                hits.append(base + off)
        if not hits:
            continue
        buckets = collections.Counter()
        for va in hits:
            ins = None
            for s in range(90, 8, -1):
                d = list(md.disasm(data[va - s - base:va - base + 5], va - s))
                if d and any(i.address == va for i in d):
                    ins = d
                    break
            if not ins:
                buckets['OTHER'] += 1
                continue
            last = None
            for i in ins[:-1]:
                if i.mnemonic in ('test', 'cmp', 'push', 'call', 'ret') or i.mnemonic.startswith('j'):
                    continue
                if i.op_str.split(',')[0].strip() in SUB[e['reg']]:
                    last = '%s %s' % (i.mnemonic, i.op_str)
            buckets[classify(last) if last else 'OTHER'] += 1
        n = sum(buckets.values())
        top = buckets.most_common(1)[0]
        print('%7d %-30s %-5s  %s' % (n, e['func'][:30], e['reg'],
              ' '.join('%s=%d(%d%%)' % (k, v, 100 * v // n) for k, v in buckets.most_common(4))))


if __name__ == '__main__':
    main()
