#!/usr/bin/env python3
"""Normalise [esp+N] references to frame offsets, so a spill can be matched.

A dropped register whose value arrives from a caller stack slot has been the
main blocker on this backlog: the register trace ends at FRAME(esp+0x30) and
there is no way to say WHAT that slot holds.

The obvious approach -- look for a store to "[esp+0x30]" earlier in the
function -- does not work, and an earlier attempt in this tree (the spill
resolver in guard_dominator_base.py) resolved 0 of 49 cases because of it.
ESP MOVES.  The slot written as [esp+0x3c] before three pushes is the same
slot read as [esp+0x30] after them, and the two never match by name.

So track esp instead of trusting its spelling.  Walking a function in address
order and maintaining a delta from entry esp (push -4, pop +4, sub/add esp,imm)
gives every memory reference a FRAME OFFSET that is stable across the whole
function, and stores and loads of one slot then agree.

Where esp cannot be tracked -- an `add esp, reg`, or a backward branch into a
region with a different delta -- the model says so rather than guessing.  A
wrong slot identification would attach a confident value to the wrong
argument, which is worse than leaving it open.
"""

import re
import sys
import os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))

MEM = re.compile(r'\[(esp|ebp)\s*([-+])\s*(0x[0-9a-f]+|\d+)\]')
MEM0 = re.compile(r'\[(esp|ebp)\]')


_RETN = None


def callee_pops(target):
    """How many bytes the callee at `target` removes on return (its `ret N`).

    A call is not esp-neutral.  MSVC's __stdcall/__thiscall callees pop their
    own arguments, so after `push;push;call` esp is back where it started and
    the caller emits no `add esp`.  A model that ignores this drifts by exactly
    the argument size at every such call -- and then reports two DIFFERENT
    stack slots as one frame offset, which is how a wrong value gets attached
    to a recovered register with no visible error.
    """
    global _RETN
    if _RETN is None:
        import csv
        import capstone
        import pefile
        pe = pefile.PE(os.path.join(ROOT, 'orig/GunBound.gme'), fast_load=True)
        sec = [x for x in pe.sections if x.Name.rstrip(b'\x00') == b'.text'][0]
        b = pe.OPTIONAL_HEADER.ImageBase + sec.VirtualAddress
        data = sec.get_data()
        md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        _RETN = {}
        for r in csv.reader(open(os.path.join(ROOT, 'PROGRESS.csv'))):
            try:
                a, size = int(r[0], 16), int(r[1])
            except (ValueError, IndexError):
                continue
            off = a - b
            if off < 0 or off + size > len(data):
                continue
            for i in md.disasm(data[off:off + size], a):
                if i.mnemonic == 'ret':
                    _RETN[a] = int(i.op_str, 16) if i.op_str.strip() else 0
                    break
    return _RETN.get(target)


def model(ins):
    """[(instruction, esp_delta_before, ok)] plus a global 'trustworthy' flag.

    esp_delta_before is relative to esp at function entry (so the return
    address sits at delta 0, the first stack argument at +4).
    """
    out, delta, ok = [], 0, True
    ebp_frame = None
    targets = set()
    # An indirect jump is a switch dispatch: blocks after it are reached only
    # through a table this walk cannot follow, so a linear delta carried into
    # them means nothing.  Refuse the whole function rather than produce
    # offsets that look computed.
    for i in ins:
        if i.mnemonic == 'jmp' and ('[' in i.op_str):
            ok = False
            break
    for i in ins:
        if i.mnemonic.startswith('j'):
            m = re.match(r'^0x([0-9a-f]+)$', i.op_str.strip())
            if m:
                targets.add(int(m.group(1), 16))
    seen_delta = {}
    for i in ins:
        # a branch target reached with a different delta makes the model unsafe
        if i.address in targets:
            if i.address in seen_delta and seen_delta[i.address] != delta:
                ok = False
            seen_delta[i.address] = delta
        out.append((i, delta, ok))
        o = i.op_str
        if i.mnemonic == 'push':
            delta -= 4
        elif i.mnemonic == 'pop':
            delta += 4
        elif i.mnemonic == 'call':
            m = re.match(r'^0x([0-9a-f]+)$', o.strip())
            pops = callee_pops(int(m.group(1), 16)) if m else None
            if pops is None:
                ok = False           # unknown callee: cannot say what it pops
            else:
                delta += pops
        elif i.mnemonic in ('sub', 'add') and o.startswith('esp,'):
            m = re.match(r'esp,\s*(0x[0-9a-f]+|\d+)$', o)
            if m:
                v = int(m.group(1), 0)
                delta += -v if i.mnemonic == 'sub' else v
            else:
                ok = False           # add esp, <register>: untrackable
        elif i.mnemonic == 'mov' and o == 'ebp, esp':
            ebp_frame = delta
        elif re.match(r'^(esp|ebp),', o) and i.mnemonic in ('mov', 'lea', 'xor'):
            if o.startswith('esp,'):
                ok = False
    return out, ebp_frame


def frame_offset(op_str, delta, ebp_frame):
    """Frame offset of the FIRST [esp/ebp +- N] in op_str, or None."""
    m = MEM.search(op_str)
    if m:
        base, sign, num = m.group(1), m.group(2), int(m.group(3), 0)
        v = num if sign == '+' else -num
        if base == 'esp':
            return delta + v
        if ebp_frame is None:
            return None
        return ebp_frame + v
    if MEM0.search(op_str):
        base = MEM0.search(op_str).group(1)
        return delta if base == 'esp' else ebp_frame
    return None


def slot_source(ins, call_va, want_off, ebp_frame=None):
    """What was last STORED to frame offset `want_off` before call_va."""
    rows, ebp = model(ins)
    if ebp_frame is None:
        ebp_frame = ebp
    best = None
    for i, delta, ok in rows:
        if i.address >= call_va:
            break
        if i.mnemonic not in ('mov', 'lea'):
            continue
        dst = i.op_str.split(',')[0].strip()
        if not (dst.startswith('[') or 'ptr [' in dst):
            continue
        off = frame_offset(dst, delta, ebp_frame)
        if off is not None and off == want_off:
            best = (i, ok)
    return best


if __name__ == '__main__':
    import capstone
    from reg_trace_caller import load, caller_of, disasm_function
    base, data, funcs = load()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    va = int(sys.argv[1], 16)
    slot = int(sys.argv[2], 0)          # the [esp+N] seen AT the call
    c = caller_of(funcs, va)
    ins = disasm_function(md, data, base, c[0], c[1])
    rows, ebp = model(ins)
    d = next((dl for i, dl, _ in rows if i.address == va), None)
    print('caller %s @0x%x   esp delta at call = %d' % (c[2], c[0], d))
    off = d + slot
    print('[esp+0x%x] at the call is frame offset %+d' % (slot, off))
    got = slot_source(ins, va, off, ebp)
    if got:
        i, ok = got
        print('last store: 0x%x  %s %s%s' % (i.address, i.mnemonic, i.op_str,
                                             '' if ok else '   (MODEL UNSAFE)'))
    else:
        print('no store to that slot found before the call')
