#!/usr/bin/env python3
"""Does a function actually READ a register before writing it?

A register holding the same value at every call site looks like a uniform
argument, but the scan that found it takes the last write before the CALL --
which may belong to something else entirely.  `mov eax, 0x88888889` is a
reciprocal-division magic constant the compiler emitted for the caller's own
arithmetic; it is uniform across call sites for a reason that has nothing to
do with the callee.

The callee settles it.  A register that is READ before it is written is an
incoming argument.  One that is written first is not an argument at all,
whatever the call sites look like -- that is the same phantom test that showed
RemoveWidget's and SetWidgetReadyState's ECX to be no argument at all.

Usage: reg_is_argument.py <function> [register ...]
"""

import os
import re
import sys

import capstone

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
from reg_trace_caller import load, disasm_function

SUB = {'eax': {'eax', 'ax', 'al', 'ah'}, 'ebx': {'ebx', 'bx', 'bl', 'bh'},
       'ecx': {'ecx', 'cx', 'cl', 'ch'}, 'edx': {'edx', 'dx', 'dl', 'dh'},
       'esi': {'esi', 'si'}, 'edi': {'edi', 'di'}, 'ebp': {'ebp', 'bp'}}


def verdict(ins, reg):
    """'ARGUMENT' if read before written, 'PHANTOM' if written first."""
    alias = SUB[reg]
    # Skip the entry prologue.  Its pushes are not reads:
    #   push ebx/esi/edi/ebp  -- callee-saved registers being saved
    #   push ecx / push eax   -- MSVC's stack-allocation idiom, a four-byte
    #                            `sub esp,4` written as a push
    # Counting either as a read makes every __thiscall function look as though
    # it reads ECX, which is exactly the wrong answer for the phantom case:
    # FUN_004e7d60 opens with `push ecx` and never reads ECX at all.
    k = 0
    for i in ins:
        if i.mnemonic == 'push' and i.op_str.strip() in ('ebx', 'esi', 'edi',
                                                         'ebp', 'ecx', 'eax'):
            k += 1
            continue
        break
    ins = ins[k:]
    for i in ins:
        o = re.sub(r'\b(?:byte|word|dword) ptr ', '', i.op_str)
        parts = [p.strip() for p in o.split(',')]
        if i.mnemonic in ('push', 'cmp', 'test', 'imul', 'idiv', 'mul', 'div',
                          'add', 'sub', 'and', 'or') and any(
                re.search(r'\b%s\b' % a, o) for a in alias):
            return 'ARGUMENT', '%s %s' % (i.mnemonic, o)
        # read as a source operand or inside a memory reference
        if len(parts) > 1 and any(re.search(r'\b%s\b' % a, parts[1]) for a in alias):
            return 'ARGUMENT', '%s %s' % (i.mnemonic, o)
        if parts and parts[0].startswith('[') and any(
                re.search(r'\b%s\b' % a, parts[0]) for a in alias):
            return 'ARGUMENT', '%s %s' % (i.mnemonic, o)
        # written
        if parts and parts[0] in alias and i.mnemonic in ('mov', 'lea', 'xor',
                                                          'pop', 'movzx', 'movsx'):
            return 'PHANTOM', '%s %s' % (i.mnemonic, o)
        if i.mnemonic == 'call' and reg == 'eax':
            return 'PHANTOM', 'call clobbers eax before any read'
    return 'UNUSED', '-'


def main():
    base, data, funcs = load()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    addr = {n: (a, s) for a, s, n in funcs}
    name = sys.argv[1]
    regs = sys.argv[2:] or list(SUB)
    if name not in addr:
        raise SystemExit('unknown function %s' % name)
    a, size = addr[name]
    ins = disasm_function(md, data, base, a, size)
    rets = [i for i in ins if i.mnemonic == 'ret']
    print('%s @0x%x  ret %s' % (name, a, (rets[0].op_str or '0') if rets else '?'))
    for r in regs:
        v, why = verdict(ins, r)
        print('  %-4s %-9s %s' % (r, v, why))


if __name__ == '__main__':
    main()
