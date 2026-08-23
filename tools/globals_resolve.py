#!/usr/bin/env python3
"""Map an original-binary address to the name it currently carries in the port.

Why this exists
---------------
Recovering a dropped register argument means writing the recovered value at
every call site.  When that value is a global, the naive move is to emit
`&DAT_00xxxxxx` using the address the disassembler reported.  That is wrong
whenever the global has since been given a real name: the DAT_ spelling no
longer resolves and the file will not compile.

A substring search for the DAT_ name in globals.h does NOT detect this,
because the header documents every rename in a comment -- "g_uiPanelManager
(was DAT_00e53c40)".  The substring is present, so the check passes, and the
applier emits a name that exists only inside a comment.  That false positive
put three files into a non-compiling state; this module is the fix.

Resolution order for an address:
  1. a rename comment  ("<name> (was DAT_<addr>)" or "was DAT_<addr>" trailing
     a declaration)                            -> the CURRENT name
  2. a direct `extern <type> DAT_<addr>;`      -> DAT_<addr>
  3. a `#define DAT_<addr> ...`                -> DAT_<addr>
  4. nothing                                   -> unresolved; caller must skip

Visibility is a separate question this module deliberately does not answer:
not every source file includes globals.h (src/cxx/Projectile.cpp keeps its own
extern block, for instance), so a resolved name can still fail to compile in a
given translation unit.  Only the compiler settles that.  See is_visible_in().
"""

import re
import os

HDR = os.path.join(os.path.dirname(__file__), '..', 'include', 'globals.h')


def _norm(addr):
    """Accept 0x6a7f88 / 006a7f88 / DAT_006a7f88 / PTR_DAT_... -> 8-hex string."""
    if isinstance(addr, int):
        return '%08x' % addr
    s = str(addr).strip().lower()
    s = re.sub(r'^(?:ptr_)?_?dat_', '', s)
    s = re.sub(r'^0x', '', s)
    return '%08x' % int(s, 16)


def build_map(path=HDR):
    """Return {canonical_addr: current_symbol_name}."""
    src = open(path, errors='replace').read()
    out = {}

    # 3. #define DAT_00xxxxxx ...
    for m in re.finditer(r'^#define\s+(_?DAT_00[0-9a-f]+)\b', src, re.M):
        out[_norm(m.group(1))] = m.group(1)

    # 2. extern <type> [*]DAT_00xxxxxx
    for m in re.finditer(r'^extern\s+[A-Za-z_][A-Za-z0-9_ ]*\**\s*(_?DAT_00[0-9a-f]+)\b',
                         src, re.M):
        out[_norm(m.group(1))] = m.group(1)

    # 1b. named bases inferred from offset-macros.  A named global that
    #     carries no address comment is still pinned by any macro written
    #     against it:  #define DAT_00e55ce8 (*(uint32_t*)(&g_replayContext+0x8))
    #     fixes g_replayContext at 0xe55ce8 - 8.  This is the only way such a
    #     base resolves (g_replayContext is exactly that case).
    for m in re.finditer(
            r'^#define\s+_?DAT_(00[0-9a-f]+)\s*\([^\n]*?&\s*([A-Za-z_][A-Za-z0-9_]*)'
            r'\s*\+\s*(0x[0-9a-fA-F]+|\d+)', src, re.M):
        dat_addr, name, off = m.group(1), m.group(2), m.group(3)
        if name.startswith('DAT_'):
            continue
        base = int(dat_addr, 16) - int(off, 0)
        out.setdefault(_norm(base), name)

    # 1c. the SUBFIELD offset-macro form, which is what this tree actually
    #     uses for fields of a sized blob:
    #       #define DAT_00e9c9c8 SUBFIELD(g_workerThreadBlock, 0x4, uint32_t)
    #     fixes the blob's base at 0xe9c9c8 - 4.  Same inference as 1b, but
    #     1b's "&name + off" pattern does not match this spelling.
    for m in re.finditer(
            r'^#define\s+_?DAT_(00[0-9a-f]+)\s+SUBFIELD\s*\(\s*'
            r'([A-Za-z_][A-Za-z0-9_]*)\s*,\s*(0x[0-9a-fA-F]+|\d+)', src, re.M):
        dat_addr, name, off = m.group(1), m.group(2), m.group(3)
        if name.startswith('DAT_'):
            continue
        out.setdefault(_norm(int(dat_addr, 16) - int(off, 0)), name)

    # 1. renames -- these WIN over any DAT_ spelling above.
    #    form A: extern uint32_t g_foo;   /* was DAT_00551cac - ... */
    #    Take the LAST identifier before the ';' -- a greedy type pattern
    #    otherwise swallows all but the final character of the name
    #    (g_cursorDeltaX -> "X", uint32_t g_buttonDefExt -> "t").
    for m in re.finditer(r'^extern\s+([^;\n]*);[^\n]*?was\s+(DAT_00[0-9a-f]+)',
                         src, re.M):
        decl, dat = m.group(1), m.group(2)
        decl = re.sub(r'\[[^\]]*\]', '', decl)          # drop array bounds
        ids = re.findall(r'[A-Za-z_][A-Za-z0-9_]*', decl)
        if ids and not ids[-1].startswith('DAT_'):
            out[_norm(dat)] = ids[-1]
    #    form B: /* g_foo (was DAT_00e53c40) - prose... */  (declaration follows)
    # Ghidra also emits PTR_DAT_ and _DAT_ prefixes, and a rename comment may
    # name either form as the old symbol.  Matching only "DAT_" silently loses
    # those addresses -- which is a quiet failure: the resolver returns None and
    # a caller concludes the global is undeclared.
    for m in re.finditer(
            r'\b([A-Za-z_][A-Za-z0-9_]*)\s*\(was\s+((?:PTR_)?_?DAT_00[0-9a-f]+)\)', src):
        name, dat = m.group(1), m.group(2)
        if not name.startswith('DAT_'):
            out[_norm(dat)] = name

    return out


_CACHE = None


def resolve(addr, path=HDR):
    """Address -> the name to emit in C source, or None if it is not declared."""
    global _CACHE
    if _CACHE is None:
        _CACHE = build_map(path)
    return _CACHE.get(_norm(addr))


def is_visible_in(src_path, name):
    """Cheap, conservative visibility check for one translation unit.

    True if the file includes globals.h, or declares/defines the name itself
    (files such as src/cxx/Projectile.cpp carry private extern blocks).
    A False here is a warning, not a verdict -- headers chain, and only the
    compiler is authoritative.
    """
    try:
        s = open(src_path, errors='replace').read()
    except OSError:
        return False
    if re.search(r'#include\s+"globals\.h"', s):
        return True
    return re.search(r'\b(extern|#define)\b[^\n]*\b%s\b' % re.escape(name), s) is not None


if __name__ == '__main__':
    import sys
    m = build_map()
    if len(sys.argv) > 1:
        for a in sys.argv[1:]:
            print('%-12s -> %s' % (a, resolve(a)))
    else:
        renamed = {k: v for k, v in m.items() if not v.startswith('DAT_')}
        print('addresses declared in globals.h : %d' % len(m))
        print('of which renamed away from DAT_ : %d' % len(renamed))
        for k in sorted(renamed):
            print('  %s -> %s' % (k, renamed[k]))
