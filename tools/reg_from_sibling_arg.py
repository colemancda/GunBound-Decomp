#!/usr/bin/env python3
"""Recover a dropped register from an argument the SAME call already passes.

The uniform-value lever is exhausted: what is left is registers whose value
differs per call site, which normally needs a per-site witness.  But there is
one witness that is always available and never needs pairing -- the call's own
stack arguments.

When the setup reads

    lea  esi, [ebp + 0x28]
    push esi                 <- becomes argument N of the call
    ...
    mov  eax, esi            <- the dropped register, same value
    call target

then EAX is not an independent unknown at all: it is argument N, and the port
already writes argument N at that call site.  The recovered expression can be
copied out of the C source rather than reconstructed from the disassembly.
`lea eax, [esi + 0x10]` against a pushed `esi` resolves the same way, as
argument N plus a displacement.

This is the same "same block" identity that unlocked the render trio, applied
to one call instead of two: values that share a definition state each other.

Guards, because a wrong recovery here is worse than none:
  * only the pushes belonging to THIS call count -- the window is cut at the
    previous call instruction, so a neighbour's arguments cannot leak in
  * the source register must not be written between the push and the call
  * the port's call site must have enough arguments for the index implied by
    the push order (arguments are pushed right to left, so the LAST push
    before the call is argument 1)

Output is a proposal per pair, for review -- it does not edit anything.
"""

import collections
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

SUB = {'eax': {'eax', 'ax', 'al'}, 'ebx': {'ebx', 'bx', 'bl'},
       'ecx': {'ecx', 'cx', 'cl'}, 'edx': {'edx', 'dx', 'dl'},
       'esi': {'esi', 'si'}, 'edi': {'edi', 'di'}, 'ebp': {'ebp', 'bp'}}
FULL = {'ax': 'eax', 'al': 'eax', 'bx': 'ebx', 'bl': 'ebx', 'cx': 'ecx',
        'cl': 'ecx', 'dx': 'edx', 'dl': 'edx', 'si': 'esi', 'di': 'edi',
        'bp': 'ebp'}


def norm(r):
    return FULL.get(r, r)


def load_text():
    pe = pefile.PE(os.path.join(ROOT, 'orig/GunBound.gme'), fast_load=True)
    sec = [s for s in pe.sections if s.Name.rstrip(b'\x00') == b'.text'][0]
    return pe.OPTIONAL_HEADER.ImageBase + sec.VirtualAddress, sec.get_data()


def window(md, data, base, va, back=160):
    """Instructions ending at the call, aligned by trying successive starts."""
    for s in range(back, 8, -1):
        ins = list(md.disasm(data[va - s - base: va - base + 5], va - s))
        if ins and any(i.address == va for i in ins):
            return [i for i in ins if i.address <= va]
    return []


def analyse(ins, reg):
    """Return (arg_index, displacement) if `reg` equals a pushed argument."""
    # cut at the previous call so a neighbour's pushes cannot leak in
    cut = 0
    for k, i in enumerate(ins[:-1]):
        if i.mnemonic == 'call':
            cut = k + 1
    body = ins[cut:-1]

    # the defining instruction for the dropped register
    src_reg, disp = None, 0
    for i in body:
        if i.mnemonic in ('push', 'cmp', 'test') or i.mnemonic.startswith('j'):
            continue
        dst = i.op_str.split(',')[0].strip()
        if dst not in SUB[reg]:
            continue
        m = re.match(r'\w+, (\w+)$', i.op_str)
        if i.mnemonic == 'mov' and m and norm(m.group(1)) in SUB:
            src_reg, disp = norm(m.group(1)), 0
            continue
        m = re.match(r'\w+, \[(\w+) \+ (0x[0-9a-f]+)\]$', i.op_str)
        if i.mnemonic == 'lea' and m and norm(m.group(1)) in SUB:
            src_reg, disp = norm(m.group(1)), int(m.group(2), 16)
            continue
        src_reg = None                      # any other definition disqualifies
    if src_reg is None:
        return None

    pushes = [(k, i) for k, i in enumerate(body) if i.mnemonic == 'push']
    if not pushes:
        return None
    for pos, (k, i) in enumerate(pushes):
        if norm(i.op_str.strip()) != src_reg:
            continue
        # the source register must survive from the push to the call
        for j in body[k + 1:]:
            if j.mnemonic in ('push', 'cmp', 'test') or j.mnemonic.startswith('j'):
                continue
            d = j.op_str.split(',')[0].strip()
            if d in SUB.get(src_reg, set()):
                break
        else:
            return (len(pushes) - pos, disp)   # args pushed right-to-left
    return None


def main():
    triage = json.load(open(os.path.join(ROOT, 'tools/backlog_triage.json')))
    base, data = load_text()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    proposals, checked = [], 0
    for e in triage:
        if e['sites'] != 1:
            continue
        checked += 1
        va = int(e['per_site'][0]['va'], 16)
        ins = window(md, data, base, va)
        if not ins:
            continue
        got = analyse(ins, e['reg'])
        if not got:
            continue
        argn, disp = got

        path = os.path.join(ROOT, e['path'])
        if not os.path.exists(path):
            continue
        # find the single source call site
        hits = []
        for b_dir, _, files in os.walk(os.path.join(ROOT, 'src')):
            for f in files:
                if not f.endswith(('.c', '.cpp')):
                    continue
                fp = os.path.join(b_dir, f)
                s = open(fp, errors='replace').read()
                if re.search(r'\b%s\s*\(' % e['func'], s) is None:
                    continue
                for c in callsites.calls(s, e['func']):
                    hits.append((fp, c))
        if len(hits) != 1:
            continue
        fp, c = hits[0]
        args = c['args']
        if argn > len(args):
            continue
        expr = args[argn - 1].strip()
        proposals.append({'func': e['func'], 'reg': e['reg'], 'path': e['path'],
                          'site': os.path.relpath(fp, ROOT), 'arg_index': argn,
                          'disp': disp, 'expr': expr,
                          'ins': e['per_site'][0]['ins']})

    print('1-site pairs examined : %d' % checked)
    print('resolved to a sibling argument : %d' % len(proposals))
    for p in proposals:
        d = ' + 0x%x' % p['disp'] if p['disp'] else ''
        print('  %-26s %-4s  %-22s  arg%d -> %s%s'
              % (p['func'], p['reg'], p['ins'], p['arg_index'], p['expr'], d))
    json.dump(proposals, open(os.path.join(ROOT, 'tools/reg_sibling_arg.json'), 'w'),
              indent=1)


if __name__ == '__main__':
    main()
