#!/usr/bin/env python3
"""Recover a dropped register argument when every caller supplies ONE value.

Ghidra models stack arguments but silently drops register ones.  The callee is
left reading an uninitialised local -- `int in_EAX;` -- and the callers never
pass anything, so the register holds whatever the last unrelated code left in
it.  Some of these are wild writes.

The general fix needs a per-site witness, which is expensive.  But when a scan
of the ORIGINAL .text shows every call site loading the same value into that
register, no pairing is needed: uniformity is the proof.  There is nothing to
match up, and the answer cannot be corrupted by Ghidra's block reordering,
which is what makes this the cheap end of the backlog.

This applier:
  * promotes the register local to a trailing parameter (regEax/regEsi/...)
  * rewrites every use in the body
  * gives functions.h a REAL prototype -- the K&R-empty "int f();" accepts any
    argument list in C, so a missed call site would compile silently; a real
    prototype is what turns the compile into a verification
  * updates stale private prototypes in C++ translation units, which keep their
    own extern "C" blocks that functions.h does not reach
  * appends the recovered value at every call site tree-wide

The threshold is 100%, deliberately.  A "95% uniform" register is not uniform:
it is a genuine varying argument that happens to repeat, and writing the
majority value at the minority site injects a WRONG value where there was
previously an unrecovered one -- strictly worse, and invisible afterwards.
BlitSpriteText is the cautionary case: ESI is 0x1f4 at 35 sites and 0x32 at
RenderWorldListRow, which its own file header had already written down.

It refuses rather than guesses: a pair whose local is already promoted/aliased,
whose value will not resolve to a declared global, or whose definition it
cannot parse is SKIPPED and reported.

Usage:  apply_uniform_reg.py [--apply] [--min-pct N] [--only NAME] [FROM] [TO]
Default is a dry run.
"""

import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import callsites
import globals_resolve

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
UNIFORM = os.path.join(ROOT, 'tools', 'backlog_uniform.json')
FUNCS_H = os.path.join(ROOT, 'include', 'functions.h')

REG_LOCAL = {'eax': ['in_EAX', 'unaff_EAX', 'extraout_EAX'],
             'ebx': ['unaff_EBX', 'in_EBX', 'extraout_EBX'],
             'ecx': ['unaff_ECX', 'in_ECX', 'extraout_ECX'],
             'edx': ['unaff_EDX', 'in_EDX', 'extraout_EDX'],
             'esi': ['unaff_ESI', 'in_ESI', 'extraout_ESI'],
             'edi': ['unaff_EDI', 'in_EDI', 'extraout_EDI'],
             'ebp': ['unaff_EBP', 'in_EBP']}


def param_name(reg):
    return 'reg' + reg[0].upper() + reg[1:].lower()


def all_sources():
    out = []
    for base, _, files in os.walk(os.path.join(ROOT, 'src')):
        for f in files:
            if f.endswith(('.c', '.cpp')):
                out.append(os.path.join(base, f))
    return out


def find_definition(src, name):
    """Locate the definition, tolerating Ghidra's split return-type line.

    Ghidra frequently emits

        void __thiscall
        FUN_004fe420(undefined4 param_1, ...)

    with the return type on its own line.  A pattern anchored on
    "<type> <name>(" misses these entirely -- the same blind spot that left 64
    functions without prototypes in functions.h.
    """
    blanked = callsites.blank_comments(src)
    for c in callsites.find(src, name, blanked):
        if c['kind'] == 'definition':
            return c
    return None


def value_expr(value, cast):
    """Render a scanned value as C, resolving globals to their CURRENT names."""
    m = re.match(r'^ctx\+0x([0-9a-fA-F]+)$', value)
    if m:
        sym = globals_resolve.resolve(m.group(1))
        if not sym:
            return None, 'ctx base 0x%s is not declared in globals.h' % m.group(1)
        return '(%s)(&%s + g_clientContext)' % (cast, sym), None
    m = re.match(r'^0x([0-9a-fA-F]+)$', value)
    if m:
        n = int(m.group(1), 16)
        if n >= 0x400000:
            sym = globals_resolve.resolve(n)
            if not sym:
                return None, 'address 0x%x is not declared in globals.h' % n
            return '(%s)&%s' % (cast, sym), None
        return ('0x%x' % n if n > 9 else str(n)), None
    return None, 'unrecognised value form %r' % value


def apply_one(entry, apply=False):
    name, reg, rel = entry['func'], entry['reg'], entry['path']
    path = os.path.join(ROOT, rel)
    log = []
    if not os.path.exists(path):
        return False, ['%s: file missing' % name], []
    src = open(path, errors='replace').read()

    d = find_definition(src, name)
    if not d:
        return False, ['%s: no definition found in %s' % (name, rel)], []

    # Which Ghidra local carries this register, and is it still open?
    local = None
    for cand in REG_LOCAL[reg]:
        m = re.search(r'^[ \t]*([A-Za-z_][A-Za-z0-9_ ]*?[ \t*]+)%s[ \t]*;[ \t]*\n'
                      % cand, src, re.M)
        if m:
            local, decl_m = cand, m
            break
    if not local:
        return False, ['%s/%s: no local declaration -- already promoted or aliased'
                       % (name, reg)], []

    # Is the local already ALIASED onto a real parameter on a later line?
    #     uint unaff_ESI;
    #     ...
    #     unaff_ESI = (uint)charsetKey;
    # The declaration alone does not mean the register is unsupplied.
    # BlitSpriteText is exactly this: fully recovered since 2026-07-17, but it
    # still declares `uint unaff_ESI;`, so a check that stops at the
    # declaration would re-promote it and give it a DUPLICATE parameter.
    plist = src[d['open']:d['close']]
    pnames = set(re.findall(r'\b\w+\b', plist))
    am = re.search(r'^[ \t]*%s\s*=\s*([^;=][^;]*);' % local, src, re.M)
    if (am and local not in am.group(1)
            and any(re.search(r'\b%s\b' % re.escape(pn), am.group(1))
                    for pn in pnames)):
        return False, ['%s/%s: already aliased onto a parameter (%s)'
                       % (name, reg, am.group(1).strip())], []

    ctype = decl_m.group(1).strip()
    is_ptr = ctype.endswith('*')
    cast = ctype if is_ptr else 'int'
    pname = param_name(reg)

    expr, err = value_expr(entry['value'], cast)
    if err:
        return False, ['%s/%s: %s' % (name, reg, err)], []

    # 1. definition: drop the local, append the parameter, rename uses.
    new = src[:decl_m.start()] + src[decl_m.end():]
    shift = decl_m.end() - decl_m.start()
    d2 = find_definition(new, name)
    args = new[d2['open']:d2['close']]
    decl_param = '%s%s%s' % (ctype, '' if is_ptr else ' ', pname)
    if args.strip() in ('', 'void'):
        new_args = decl_param
    else:
        new_args = args.rstrip() + ',' + decl_param
    new = new[:d2['open']] + new_args + new[d2['close']:]
    new = re.sub(r'\b%s\b' % local, pname, new)
    files = {path: new}

    # 2. call sites tree-wide.
    n_sites = 0
    for f in all_sources():
        s = open(f, errors='replace').read() if f != path else files[path]
        if re.search(r'\b%s\s*\(' % name, s) is None:
            continue
        b = callsites.blank_comments(s)
        cs = [c for c in callsites.find(s, name, b) if c['kind'] == 'call']
        if not cs:
            continue
        for c in sorted(cs, key=lambda x: -x['start']):
            inner = s[c['open']:c['close']]
            add = expr if inner.strip() == '' else inner.rstrip() + ',' + expr
            s = s[:c['open']] + add + s[c['close']:]
            n_sites += 1
        files[f] = s
    log.append('%-26s %s  %2d sites  %s' % (name, reg, n_sites, expr))

    # 3. real prototype in functions.h, plus any private C++ prototypes.
    proto_args = new_args
    hdr = open(FUNCS_H, errors='replace').read()
    hb = callsites.blank_comments(hdr)
    for c in sorted(callsites.find(hdr, name, hb), key=lambda x: -x['start']):
        if c['kind'] == 'declaration':
            hdr = hdr[:c['open']] + proto_args + hdr[c['close']:]
    files[FUNCS_H] = hdr
    for f in all_sources():
        if f == path:
            continue
        s = files.get(f) or open(f, errors='replace').read()
        b = callsites.blank_comments(s)
        ds = [c for c in callsites.find(s, name, b) if c['kind'] == 'declaration']
        if not ds:
            continue
        for c in sorted(ds, key=lambda x: -x['start']):
            s = s[:c['open']] + proto_args + s[c['close']:]
        files[f] = s
        log.append('    private prototype updated in %s' % os.path.relpath(f, ROOT))

    if apply:
        for f, text in files.items():
            open(f, 'w').write(text)
    return True, log, sorted(os.path.relpath(f, ROOT) for f in files)


def main():
    argv = sys.argv[1:]
    apply = '--apply' in argv
    argv = [a for a in argv if a != '--apply']
    min_pct, only = 100, None
    if '--min-pct' in argv:
        i = argv.index('--min-pct'); min_pct = int(argv[i + 1]); del argv[i:i + 2]
    if '--only' in argv:
        i = argv.index('--only'); only = argv[i + 1]; del argv[i:i + 2]
    lo = int(argv[0]) if len(argv) > 0 else 0
    hi = int(argv[1]) if len(argv) > 1 else 10 ** 9

    ents = [e for e in json.load(open(UNIFORM)) if e['pct'] >= min_pct]
    if only:
        ents = [e for e in ents if e['func'] == only]
    ents = ents[lo:hi]

    ok, skipped, touched = 0, [], set()
    for e in ents:
        done, log, files = apply_one(e, apply)
        if done:
            ok += 1
            touched.update(files)
            for line in log:
                print(line)
        else:
            skipped.extend(log)
    print('\n%s: %d pairs, %d files' % ('APPLIED' if apply else 'DRY RUN', ok, len(touched)))
    if skipped:
        print('SKIPPED %d:' % len(skipped))
        for s in skipped:
            print('  ' + s)
    if apply and touched:
        with open('/tmp/uniform_touched.txt', 'w') as fh:
            fh.write('\n'.join(sorted(touched)) + '\n')
        print('touched file list -> /tmp/uniform_touched.txt')


if __name__ == '__main__':
    main()
