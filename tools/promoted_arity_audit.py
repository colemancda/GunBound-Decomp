#!/usr/bin/env python3
"""Check every promoted function for prototype and call-site arity agreement.

Written after finding that a promoted register had been appended at a call
site that was already SHORT, so the recovered value landed in the wrong
parameter slot -- and nothing caught it, because the function's declaration in
functions.h was still K&R-empty and a K&R prototype accepts any argument list.

Two classifier bugs let that through, both now fixed in callsites.py:
  * "void __fastcall f();" was not recognised as a declaration (the pattern
    allowed only ONE word of return type), so prototype sweeps skipped it
  * "return f(a);" WAS recognised as a declaration (no keyword blacklist), so
    call-site sweeps skipped those sites entirely

This audit is the check that should have existed from the start.  For every
function whose parameter list contains a regEax/regEsi/... parameter it
compares:
    definition arity  vs  functions.h prototype  vs  every call site
and reports each disagreement.  A K&R-empty prototype is itself reported: it
is not a prototype, it is an opt-out from checking.
"""

import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import callsites

REGP = re.compile(r'\breg(Eax|Ebx|Ecx|Edx|Esi|Edi|Ebp)\b')


_CACHE = None


def sources():
    """Every source file, read and comment-blanked ONCE.

    The first version re-read and re-blanked the whole tree for each promoted
    function, which is quadratic and took longer than the compile it was
    meant to protect."""
    global _CACHE
    if _CACHE is None:
        _CACHE = []
        for b, _, files in os.walk(os.path.join(ROOT, 'src')):
            for f in sorted(files):
                if f.endswith(('.c', '.cpp')):
                    fp = os.path.join(b, f)
                    txt = open(fp, errors='replace').read()
                    _CACHE.append((fp, txt, callsites.blank_comments(txt)))
    return _CACHE


def arity(argstr):
    a = callsites.split_args(argstr)
    if len(a) == 1 and a[0].strip() in ('void', ''):
        return 0
    return len(a)


def main():
    defs = {}
    # Find promoted definitions directly.  Walking every "name(" token and
    # calling find() on each is a full-file scan per token -- hundreds of scans
    # for a large file -- and was why this audit took longer than the build.
    # A promoted definition is recognisable on its own: a parameter list
    # holding a regEax/regEsi/... parameter, followed by the opening brace.
    DEFN = re.compile(r'\b([A-Za-z_]\w*)\s*\(([^;{()]*(?:\([^()]*\)[^;{()]*)*)\)'
                      r'\s*\n?\s*\{')
    for p, s, b in sources():
        if not REGP.search(s):
            continue
        for m in DEFN.finditer(b):
            # "if (...) {" and "while (...) {" match the shape of a definition
            # exactly; only the name distinguishes them.
            if m.group(1) in callsites.KEYWORDS:
                continue
            if REGP.search(m.group(2)):
                defs[m.group(1)] = (p, arity(m.group(2)), m.group(2))

    print('promoted functions found: %d\n' % len(defs))

    hdr = open(os.path.join(ROOT, 'include/functions.h'), errors='replace').read()
    hb = callsites.blank_comments(hdr)
    problems = []
    for name, (dp, dn, dargs) in sorted(defs.items()):
        decls = [c for c in callsites.find(hdr, name, hb) if c['kind'] == 'declaration']
        for c in decls:
            pn = arity(hdr[c['open']:c['close']])
            if pn == 0 and hdr[c['open']:c['close']].strip() == '':
                problems.append(('KNR-PROTOTYPE', name, 'functions.h', dn, 0))
            elif pn != dn:
                problems.append(('PROTO-ARITY', name, 'functions.h', dn, pn))
        if not decls:
            problems.append(('NO-PROTOTYPE', name, 'functions.h', dn, -1))
    # File-major, not function-major.  Scanning every source once per promoted
    # function is O(functions x files) and took longer than the compile this is
    # meant to guard; one pass over the tree, checking only the names that
    # actually occur in each file, is the same information far cheaper.
    for p, s, sb in sources():
        rel = os.path.relpath(p, ROOT)
        for name, (dp, dn, dargs) in defs.items():
            if re.search(r'\b%s\s*\(' % name, sb) is None:
                continue
            for c in callsites.find(s, name, sb):
                if c['kind'] == 'call':
                    n = arity(s[c['open']:c['close']])
                    if n != dn:
                        problems.append(('CALL-ARITY', name,
                                         rel + ':' + str(s[:c['start']].count('\n') + 1),
                                         dn, n))
                elif c['kind'] == 'declaration' and p != dp:
                    n = arity(s[c['open']:c['close']])
                    if n != dn:
                        problems.append(('PRIVATE-PROTO', name, rel, dn, n))

    if not problems:
        print('no disagreements')
        return
    print('%-15s %-26s %-44s %5s %5s' % ('KIND', 'FUNCTION', 'WHERE', 'DEF', 'GOT'))
    for k, n, w, d, g in problems:
        print('%-15s %-26s %-44s %5d %5s' % (k, n, w, d, g if g >= 0 else '-'))
    print('\n%d disagreements' % len(problems))


if __name__ == '__main__':
    main()
