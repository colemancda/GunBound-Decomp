#!/usr/bin/env python3
"""Find dropped registers loaded from the CALLER'S OWN stack parameters.

A register defined by `mov reg, [esp + N]` looks like an unresolvable spill.
But if N reaches ABOVE the caller's frame -- past its __chkstk allocation,
SEH triple, callee-saved pushes and the argument pushes pending for this
call -- the slot is not a local at all: it is one of the caller's incoming
stack parameters, which the source already names (param_2, param_3, ...).

Frame offset = N - (seh + frame + 4*saved) - 4*pending_pushes.  +4 is the
first stack parameter, +8 the second.  +0 is the return address and cannot
be an argument, so a +0 result means the pending-push count is wrong (a push
on an untaken branch between the previous call and this one), not that the
slot is.  Those are reported separately rather than silently accepted.

This closed FUN_00458920/FUN_00458a00 (EAX = param_2 at 24 sites); it runs
the same arithmetic over every open pair.
"""
import collections
import json
import os
import re
import struct
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import capstone
import callsites
from reg_trace_caller import load, caller_of, disasm_function

SUB = {'eax': ('eax',), 'ebx': ('ebx',), 'ecx': ('ecx',), 'edx': ('edx',),
       'esi': ('esi',), 'edi': ('edi',)}
CHKSTK = 0x528380


def frame_const(ins):
    seh = 12 if (ins and ins[0].mnemonic == 'push' and ins[0].op_str == '-1') else 0
    chk, last_imm, saved = 0, None, 0
    for i in ins[:24]:
        m = re.match(r'^eax, (0x[0-9a-f]+|\d+)$', i.op_str)
        if i.mnemonic == 'mov' and m:
            last_imm = int(m.group(1), 0)
        if i.mnemonic == 'call' and i.op_str.strip() == '0x%x' % CHKSTK and last_imm:
            chk += last_imm
        m2 = re.match(r'^esp, (0x[0-9a-f]+|\d+)$', i.op_str)
        if i.mnemonic == 'sub' and m2:
            chk += int(m2.group(1), 0)
        if i.mnemonic == 'push' and i.op_str in ('ebx', 'esi', 'edi', 'ebp') and i.address > ins[0].address:
            saved += 1
        if i.mnemonic == 'call' and i.op_str.strip() != '0x%x' % CHKSTK:
            break
    return seh, chk, saved


def caller_params(name):
    for b, _, fs in os.walk(os.path.join(ROOT, 'src')):
        for f in fs:
            if f in (name + '.c', name + '.cpp'):
                s = open(os.path.join(b, f), errors='replace').read()
                bl = callsites.blank_comments(s)
                for c in callsites.find(s, name, bl):
                    if c['kind'] == 'definition':
                        head = s[max(0, c['start'] - 40):c['start']]
                        conv = '__thiscall' if '__thiscall' in head else ('__fastcall' if '__fastcall' in head else 'cdecl')
                        return conv, callsites.split_args(s[c['open']:c['close']])
    return None, None


def main():
    subprocess.run([sys.executable, os.path.join(ROOT, 'tools/dropped_reg_backlog.py'),
                    '--json', '/tmp/_open.json', '--top', '0'], capture_output=True, cwd=ROOT)
    openp = json.load(open('/tmp/_open.json'))
    base, data, funcs = load()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    addr_of = {n: a for a, _, n in funcs}
    targets = {}
    for e in openp:
        a = addr_of.get(e['func'])
        if a:
            targets.setdefault(a, []).append(e)
    sites = collections.defaultdict(list)
    for off in range(len(data) - 5):
        if data[off] != 0xE8:
            continue
        t = base + off + 5 + struct.unpack('<i', data[off + 1:off + 5])[0]
        if t in targets:
            sites[t].append(base + off)
    cache, pcache = {}, {}
    out = collections.defaultdict(list)
    for t, entries in targets.items():
        for va in sites.get(t, []):
            c = caller_of(funcs, va)
            if not c:
                continue
            if c[0] not in cache:
                cache[c[0]] = disasm_function(md, data, base, c[0], c[1])
            ins = cache[c[0]]
            seh, chk, saved = frame_const(ins)
            prev = [i for i in ins if i.address < va]
            k = len(prev) - 1
            while k > 0 and prev[k].mnemonic != 'call':
                k -= 1
            seg = prev[k + 1:]
            for e in entries:
                reg = e['reg']
                defs = [i for i in seg if i.mnemonic == 'mov' and i.op_str.startswith(reg + ', dword ptr [esp + ')]
                if not defs:
                    continue
                mov = defs[-1]
                # the register must not be rewritten after that load
                # ANY instruction whose first operand is the register rewrites
                # it, bar the read-only ones.  An allow-list of mnemonics
                # missed `inc eax` after the load and reported param_2 where
                # the value is param_2 + 1 -- off by one, in a shape that
                # looks recovered.
                if any(i.op_str.split(',')[0].strip() == reg and i.address > mov.address
                       and i.mnemonic not in ('cmp', 'test', 'push')
                       for i in seg):
                    continue
                n = int(re.search(r'0x([0-9a-f]+)', mov.op_str).group(1), 16)
                pb = len([i for i in seg if i.mnemonic == 'push' and i.address < mov.address])
                fo = n - (seh + chk + 4 * saved) - 4 * pb
                if fo < 4:
                    verdict = 'RETADDR(count off)' if fo == 0 else 'local'
                else:
                    idx = fo // 4              # 1 = first stack arg
                    if c[2] not in pcache:
                        pcache[c[2]] = caller_params(c[2])
                    conv, plist = pcache[c[2]]
                    pos = idx + (1 if conv == '__thiscall' else (2 if conv == '__fastcall' else 0))
                    if plist and pos <= len(plist):
                        verdict = 'param_%d [%s]' % (pos, plist[pos - 1].strip())
                    else:
                        verdict = 'stack arg %d but caller declares %s' % (idx, len(plist) if plist else '?')
                out[(e['func'], reg)].append((c[2], '0x%x' % va, fo, verdict))
    for (fn, reg), rows in sorted(out.items(), key=lambda kv: -len(kv[1])):
        vs = collections.Counter(r[3] for r in rows)
        print('%-30s %-4s %2d sites  %s' % (fn, reg, len(rows), dict(vs)))
    json.dump({'%s/%s' % k: v for k, v in out.items()},
              open(os.path.join(ROOT, 'tools/above_frame_params.json'), 'w'), indent=1)


if __name__ == '__main__':
    main()
