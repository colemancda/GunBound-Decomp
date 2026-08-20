#!/usr/bin/env python3
"""retn_signature_audit.py - find ports whose declared parameter list does not
match the original's `ret N`.

WHY.  Ghidra sometimes recovers fewer parameters than a function really takes,
and with no prototype in scope the extra arguments a caller pushes compile
silently - so the defect is invisible until something reads stack garbage.
Three real bugs were found this way on 2026-08-19: SpawnSuperShot (11 declared
vs 12), SpawnItemProjectile (3 vs 7, whole frame shifted a slot) and
SpawnShot_Type13 (0 vs 7).  SpawnPrimaryShot (d63c34d) was the same shape.

THE RULE THAT MATTERS.  Compare ret N against the CALLEE'S DECLARED PARAMETER
LIST.  What the call sites pass proves nothing - in every case found so far the
callers were already correct and only the callee was short.  An earlier pass
cleared SpawnSuperShot precisely by checking ret N against the callers.

THE FILTER THAT MATTERS.  `ret N` counts callee-cleaned stack bytes, so this
check only applies to callee-cleans conventions.  A cdecl function returns
`ret 0` no matter how many arguments it takes, so including them turns ~9 real
candidates into ~800 noise rows.  Hence --all is opt-in.

Register arguments are added in from the port's own convention keyword
(__thiscall = 1, __fastcall = 2) plus one more if the body declares `in_EAX`.
Both are heuristics: Ghidra writes __fastcall whenever it sees ANY register
argument, including EAX-first conventions it cannot express, and it marks ECX
as a parameter even where ECX is written before it is read (a "phantom" - see
BlitSpriteAttached).  So treat a nonzero delta as a lead, not a verdict, and
confirm each one against the disassembly.

Usage:  python3 tools/retn_signature_audit.py [--all]
"""
import glob, re, os, csv, sys
import pefile, capstone

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
pe = pefile.PE(os.path.join(ROOT, 'orig/GunBound.gme'), fast_load=True)
ib = pe.OPTIONAL_HEADER.ImageBase
for s in pe.sections:
    if s.Name.rstrip(b'\0') == b'.text':
        TB = ib + s.VirtualAddress
        TD = s.get_data()
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

prog = {}
for r in csv.reader(open(os.path.join(ROOT, 'PROGRESS.csv'))):
    try:
        if not r[6].startswith('EXCLUDED'):
            prog[r[2]] = (int(r[0], 16), int(r[1]))
    except (IndexError, ValueError):
        continue


def max_retn(va, n):
    """largest `ret N` in the function's extent (multiple exits share N)"""
    best = None
    for i in md.disasm(TD[va - TB:va - TB + n], va):
        if i.mnemonic == 'ret':
            v = int(i.op_str, 16) if i.op_str else 0
            best = v if best is None else max(best, v)
    return best


def main():
    show_all = '--all' in sys.argv
    rows = []
    for p in glob.glob(os.path.join(ROOT, 'src/**/*.c'), recursive=True):
        if 'msvc_crt_atl' in p:
            continue
        nm = os.path.basename(p)[:-2]
        a = prog.get(nm)
        if not a or not (TB <= a[0] < TB + len(TD)) or a[0] + a[1] > TB + len(TD):
            continue
        s = open(p).read()
        m = re.search(r'(?m)^[\w\* ]*\b%s\s*\(([^;{]*?)\)\s*\n\s*\n?\{' % re.escape(nm), s, re.S)
        if not m:
            continue
        decl = len([x for x in m.group(1).split(',') if x.strip() and x.strip() != 'void'])
        head = s[:m.start() + 200]
        conv = 'thiscall' if '__thiscall' in head else ('fastcall' if '__fastcall' in head else 'cdecl')
        reg = {'thiscall': 1, 'fastcall': 2}.get(conv, 0)
        extra = 1 if re.search(r'\bin_EAX\b', s[m.end():]) else 0
        rn = max_retn(*a)
        if rn is None:
            continue
        if rn == 0 and not show_all:
            continue          # cdecl: caller cleans, ret N says nothing
        delta = (rn // 4 + reg + extra) - decl
        if delta:
            rows.append((abs(delta), delta, nm, a[0], rn, rn // 4, decl, conv, extra))
    rows.sort(reverse=True)
    print('%-34s %-9s %-6s %-6s %-5s %-9s %-6s %s' %
          ('function', 'addr', 'retN', 'stack', 'decl', 'conv', 'in_EAX', 'delta'))
    for _, d, nm, ad, rn, st, decl, conv, extra in rows:
        print('%-34s 0x%06x  0x%-4x %-6d %-5d %-9s %-6d %+d' %
              (nm, ad, rn, st, decl, conv, extra, d))
    print('\n%d candidate(s)%s' % (len(rows), '' if show_all else '  (cdecl/ret-0 excluded; --all to include)'))


if __name__ == '__main__':
    main()
