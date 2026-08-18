#!/usr/bin/env python3
"""guard_callsite_verify.py - per-site guard-cell verification anchored on the
NON-GUARD call sequence, independent of every previous sweep.

WHY.  All mechanical guard appliers so far zipped C sites in text order
against resolver rows in address order.  Ghidra's decompiler reorders text
freely - labeled goto blocks AND unlabeled if/else bodies - so in shuffled
functions that zip silently assigns cell A's offset to cell B's call (found
2026-08-17: DetonateProjectile.c line 217 carries +0x3918, but the C block
it sits in is the disasm block at 0x4583d9 whose cell is +0xf3f).  Every
alignment built from applied cells inherits the same bias, because a
misapplied cell "anchors" the wrong text position.  The only positional
evidence that is independent of the sweeps is what Ghidra could not move
relative to the site: the neighbouring DIRECT calls inside the same
statement run.

METHOD.  For each guard call site in the C text, take the nearest preceding
and following DIRECT non-guard calls (names that map to a 0x4xxxxx address
via PROGRESS.csv; imports and CriticalSection wrappers are register-indirect
in the binary and are skipped).  For each resolver row of the same family,
take the nearest `call 0x4xxxxx` before and after the row's address, walking
at most WINDOW bytes and never across another row of the same family.  A
site matches a row when their (prev, next) call anchors agree - one side
suffices if the other is absent on BOTH sides.  A site with exactly one
matching row is VERIFIED; an applied offset disagreeing with its verified
row is WRONG.

The anchor pair is treated as evidence, not proof, when the same (prev,next)
pair brackets several rows of the family - those sites stay UNDECIDED rather
than guessed.

Usage:
  guard_callsite_verify.py [--family PeekBool] [--fix] <file.c> [...]

  --fix   rewrite bare sites whose verified row carries an offset, and
          repair applied sites that disagree with their verified row.
          Without it, report only.
"""
import csv
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
PY = os.path.join(HERE, '.venv-angr/bin/python3')

WINDOW = 0x120

# C spelling -> resolver family name
CALLS = {
    'PeekPacketChecksumState': 'Peek',
    'PeekPacketChecksumBool': 'PeekBool',
    'EncodeOutgoingPacketField': 'Encode',
}

byaddr = {}
name2addr = {}
for r in csv.reader(open(os.path.join(ROOT, 'PROGRESS.csv'))):
    try:
        a = int(r[0], 16)
    except ValueError:
        continue
    if len(r) > 2 and r[1].strip().isdigit():
        byaddr[a] = int(r[1])
        # duplicate names (CRT junk) are unusable as anchors
        name2addr[r[2]] = None if r[2] in name2addr else a
name2addr = {k: v for k, v in name2addr.items() if v is not None}


def rng(path):
    head = open(path, errors='ignore').read(400)
    m = re.search(r'- 0x00([0-9a-f]{6}) in the original binary', head)
    a = int(m.group(1), 16) if m else None
    if a is None:
        m = re.match(r'FUN_00([0-9a-f]{6})', os.path.basename(path))
        a = int(m.group(1), 16) if m else None
    return (a, a + byaddr[a]) if a in byaddr else None


def parse_rows(lo, hi, family):
    out = subprocess.run([PY, os.path.join(HERE, 'guard_cell_resolve.py'),
                          hex(lo), hex(hi)], capture_output=True, text=True).stdout
    rows = []
    for l in out.split('\n'):
        m = re.match(r'(?:!!)?\s+\d+ (0x[0-9a-f]+) (\w+)\s+cell = (.*)', l)
        if m and m.group(2) == family:
            rows.append({'addr': int(m.group(1), 16), 'cell': m.group(3).strip()})
    return rows


def disasm_calls(lo, hi):
    """[(addr, target)] of every direct call in the range."""
    out = subprocess.run([PY, os.path.join(HERE, 'disasm_capstone.py'),
                          os.path.join(ROOT, 'orig/GunBound.gme'), hex(lo), hex(hi)],
                         capture_output=True, text=True).stdout
    calls = []
    for l in out.split('\n'):
        m = re.match(r'^([0-9a-f]{8}):\tcall\t(0x[0-9a-f]+)$', l)
        if m:
            calls.append((int(m.group(1), 16), int(m.group(2), 16)))
    return calls


def is_guard(addr):
    """The guard implementation range plus its outliers.  Guard calls are
    unusable as anchors: the C text renames them freely and sometimes hides
    one entirely (dropped-register helpers like 0x40b300/0x40b330 leave no
    statement at all), so only NON-guard calls anchor on either side."""
    return 0x406000 <= addr < 0x40c000 or addr in (
        0x4217b0, 0x420600, 0x426230, 0x4262d0, 0x4dc0f0)


def row_anchors(rows, calls, fam_addrs, eligible):
    """nearest direct anchor-ELIGIBLE call before/after each row address."""
    for row in rows:
        a = row['addr']
        prev = next_ = None
        for ca, ct in calls:
            if ca >= a:
                break
            if a - ca > WINDOW:
                continue
            if ct in fam_addrs and ca != a:
                prev = None          # another same-family row is closer
                continue
            if ct in eligible:
                prev = ct
        for ca, ct in calls:
            if ca <= a:
                continue
            if ca - a > WINDOW:
                break
            if ct in fam_addrs:
                break                # next same-family row cuts the window
            if ct in eligible:
                next_ = ct
                break
        row['prev'], row['next'] = prev, next_


CALLNAME = re.compile(r'\b([A-Za-z_]\w*)\s*\(')
NOT_CALLS = {'if', 'while', 'for', 'switch', 'return', 'sizeof', 'defined'}


def call_tokens(src):
    toks = []
    for i, l in enumerate(src):
        if l.lstrip().startswith('*') or l.lstrip().startswith('/*'):
            continue
        for m in CALLNAME.finditer(l):
            n = m.group(1)
            if n in NOT_CALLS:
                continue
            toks.append((i, m.start(), n))
    return toks


def eligible_anchors(calls, toks):
    """Anchor targets must be RARE ON BOTH SIDES (<=2 occurrences in the
    disasm AND <=2 named occurrences in the C text).  One-sided rarity
    manufactures conflicts: `operator_new` was rare in the disasm walk but
    common in the text walk of DetonateProjectile, so the two sides picked
    different anchors for the SAME position and a correct site got flagged.
    A target absent from the C text entirely (a call Ghidra folded away) is
    likewise ineligible - the text side could never produce it."""
    from collections import Counter
    tcount = Counter(ct for _, ct in calls)
    ccount = Counter()
    for _, _, n in toks:
        a = name2addr.get(n)
        if a is not None:
            ccount[a] += 1
    return {a for a in tcount
            if not is_guard(a) and tcount[a] <= 2 and 1 <= ccount[a] <= 2}


def site_anchors(src, sites, toks, eligible):
    """nearest anchor-eligible named calls around each site in the text."""
    SPAN = 15                      # text lines, rough twin of WINDOW bytes
    for s in sites:
        pos = (s['line'], s['col'])
        prev = next_ = None
        for t in toks:
            if (t[0], t[1]) >= pos:
                break
            n = t[2]
            if n in CALLS and CALLS[n] == s['family']:
                prev = None
                continue
            a = name2addr.get(n)
            if a in eligible and s['line'] - t[0] <= SPAN:
                prev = a
        after = [t for t in toks if (t[0], t[1]) > pos]
        for t in after:
            if t[0] - s['line'] > SPAN:
                break
            n = t[2]
            if n in CALLS and CALLS[n] == s['family']:
                break
            a = name2addr.get(n)
            if a in eligible:
                next_ = a
                break
        s['prev'], s['next'] = prev, next_


def find_sites(src, cname, family):
    out = []
    for i, l in enumerate(src):
        if l.lstrip().startswith('*') or cname + '(' not in l:
            continue
        for m in re.finditer(re.escape(cname) + r'(_\d+)?\(', l):
            if m.group(1) is not None:
                continue
            depth, j = 1, m.end()
            while j < len(l) and depth:
                depth += {'(': 1, ')': -1}.get(l[j], 0)
                j += 1
            arg = l[m.end():j - 1]
            if family == 'Encode':
                arg = arg.split(',')[0] if ',' in arg else None
            out.append({'line': i, 'col': m.start(), 'family': family,
                        'arg': arg if arg else None, 'end': j})
    return out


def row_expr(row, off, whole, ctx=None):
    """The full C argument for a row - the base comes from the ROW's shape,
    never from the expression being replaced (a ctx->object repair must
    change the base, not just the number)."""
    if re.match(r'dword ptr \[0x5b3484\] \+', row['cell']):
        return '(byte *)(g_clientContext + 0x%x)' % off
    m = re.match(r'<(e\w\w) (?:crosses block end|live-in)', row['cell'])
    sp = re.match(r'dword ptr \[esp \+ 0x[0-9a-f]+\] \+ 0x[0-9a-f]+$',
                  row['cell'])
    if sp:
        # a spilled object pointer.  The slot trace is unreliable as a base
        # (push-depth artifact, see sweep_peekbool_sibling.py), but the
        # OFFSET is real, and a sibling object-cell spelling in the same
        # file names the base.
        mm = re.search(r'PeekPacketChecksumBool\(\(byte \*\)([A-Za-z_]\w*)'
                       r' \+ 0x[0-9a-f]+\)', whole)
        if mm:
            return '(byte *)%s + 0x%x' % (mm.group(1), off)
    if m:
        mm = re.search(r'PeekPacketChecksumBool\(\(byte \*\)([A-Za-z_]\w*)'
                       r' \+ 0x[0-9a-f]+\)', whole)
        if mm:
            return '(byte *)%s + 0x%x' % (mm.group(1), off)
        # no sibling spelling to borrow: prove reg==this with the dominance
        # analysis, then the base is the function's first parameter.
        if ctx is not None:
            from guard_dominator_base import disasm, in_edges, resolve
            if 'dis' not in ctx:
                ctx['dis'] = disasm(ctx['lo'], ctx['hi'])
                ctx['edges'] = in_edges(ctx['dis'])
            reg = 'ecx' if 'live-in' in row['cell'] else m.group(1)
            base, extra = (('this', 0) if reg == 'ecx' else
                           resolve(ctx['dis'], ctx['edges'], reg, row['addr']))
            if base == 'this' and extra == 0 and ctx.get('param'):
                return '(byte *)%s + 0x%x' % (ctx['param'], off)
    return None


def cell_offset(text):
    if text is None:
        return None
    m = re.search(r'\+ (0x[0-9a-f]+)\)*$', text.strip())
    return int(m.group(1), 16) if m else None


def label_pin(src, sites, rows):
    """Ghidra label definitions are EXACT addresses.  A site within 3 text
    lines below a `LAB_/joined_r/code_r` definition, with no other call of
    its family between label and site, executes within a few instructions of
    that address - so the unique same-family row in [label, label+0x60] IS
    the site's row.  This out-ranks anchor plausibility (it is how the
    Bullet10/15 foursome's wrong +0x6a7f74 cells were pinned to +0xf4c when
    anchor evidence was silent).  Sets s['pin'] where provable."""
    labels = [(i, int(m.group(1), 16)) for i, l in enumerate(src)
              for m in [re.match(r'^\s*(?:LAB|joined_r0x|code_r0x)_?00'
                                 r'([0-9a-f]{6}):\s*$', l)] if m]
    for s in sites:
        s['pin'] = None
        for li, la in labels:
            if not (0 <= s['line'] - li <= 3):
                continue
            between = '\n'.join(src[li + 1:s['line']])
            if 'PeekPacketChecksumBool' in between or \
                    'PeekPacketChecksumState' in between:
                continue
            cands = [r for r in rows if la <= r['addr'] <= la + 0x60]
            if len(cands) == 1:
                s['pin'] = cands[0]
            break


def match(sites, rows):
    """Split rows into PLAUSIBLE (no anchor conflict) and positively MATCHING
    for each site.  An anchor conflict means both sides are known and differ;
    a None on either side is unknown, not a mismatch - the C text hides guard
    helper calls and the disasm walk is window-capped, so absence carries no
    information.

    THE LESSON BAKED IN HERE (Mobile00_MainAction.c line 165, 2026-08-17):
    requiring a positive anchor match to identify a site's row EXCLUDES the
    anchor-less true row and can leave a coincidentally-matching wrong row as
    the "unique" candidate - producing a false WRONG on a correct site.  So
    correctness judgments use the PLAUSIBLE set (an applied offset is wrong
    only when NO plausible row carries it), and rewrites happen only when
    every plausible row agrees on one offset."""
    for s in sites:
        plaus = []
        pos = []
        for r in rows:
            conflict = ((s['prev'] is not None and r['prev'] is not None
                         and s['prev'] != r['prev']) or
                        (s['next'] is not None and r['next'] is not None
                         and s['next'] != r['next']))
            if conflict:
                continue
            plaus.append(r)
            if ((s['prev'] is not None and s['prev'] == r['prev']) or
                    (s['next'] is not None and s['next'] == r['next'])):
                pos.append(r)
        s['plaus'] = plaus
        s['cands'] = pos


def main():
    args = sys.argv[1:]
    family = 'PeekBool'
    fix = False
    if args and args[0] == '--family':
        family = args[1]
        args = args[2:]
    if args and args[0] == '--fix':
        fix = True
        args = args[1:]
    cname = {v: k for k, v in CALLS.items()}[family]
    fam_addr = {'Peek': {0x40a2e0}, 'PeekBool': {0x4065a0}, 'Encode': {0x40a380}}[family]

    n_ver = n_wrong = n_fixed = n_und = 0
    for path in args:
        r = rng(path)
        if not r:
            continue
        src = open(path, errors='ignore').read().split('\n')
        sites = find_sites(src, cname, family)
        if not sites:
            continue
        rows = parse_rows(r[0], r[1], family)
        if len(sites) + sum(1 for l in src for m in
                            [re.search(re.escape(cname) + r'_\d+\(', l)]
                            if m and not l.lstrip().startswith('*')) < len(rows) - 8:
            pass  # inlined twins etc - anchors still work per-site
        calls = disasm_calls(r[0], r[1])
        toks = call_tokens(src)
        eligible = eligible_anchors(calls, toks)
        row_anchors(rows, calls, fam_addr, eligible)
        site_anchors(src, sites, toks, eligible)
        match(sites, rows)
        label_pin(src, sites, rows)
        param = None
        for l in src:
            m = re.match(r'^\w[\w ]*?__fastcall \w+\((?:int|uint|byte|char|'
                         r'undefined4)\s*\*?\s*([A-Za-z_]\w*)[,)]', l)
            if m:
                param = m.group(1)
                break
        fctx = {'lo': r[0], 'hi': r[1], 'param': param}
        changed = False
        for s in sites:
            if s['arg'] is not None and ',' in s['arg']:
                continue           # fabricated multi-arg signature, not ours
            if any('guard-cell: proven' in src[k]
                   for k in range(max(0, s['line'] - 8), s['line'] + 1)):
                # a hand proof the anchor machinery cannot see (dominating
                # spill-slot write, etc.) - documented in the comment above
                # the site.  Trust it.
                n_ver += 1
                continue
            aoff = cell_offset(s['arg'])
            loc = '%s:%d' % (path, s['line'] + 1)
            if s['pin'] is not None:
                # exact-address evidence outranks anchor plausibility
                s['plaus'] = [s['pin']]
            plaus_offs = {cell_offset(r['cell']) for r in s['plaus']}
            if s['arg'] is not None and aoff is not None:
                # int-pointer bases scale by 4 (`param_1 + 0x122` is byte
                # 0x488) and the base's C type is not reliably known here,
                # so accept EITHER scale; flag wrong only when both readings
                # miss every plausible row.
                if aoff in plaus_offs or aoff * 4 in plaus_offs:
                    n_ver += 1
                    continue
                if any(('&DAT_00%06x' % aoff) in src[k]
                       for k in range(max(0, s['line'] - 3), s['line'])):
                    # Ghidra itself stored this address into the spill slot
                    # the call reads (the folded ctx+0x6a7f74 pattern in the
                    # detonation twins: `apuStack_ad0[0] = &DAT_006a7f74 +
                    # iVar` right above the call) - decisive local evidence
                    # even when the row shape is unresolved.
                    n_ver += 1
                    continue
                if None in plaus_offs and family != 'PeekBool':
                    # an UNRESOLVED row (spill slot, <add eax,4>) is
                    # plausible for this site - and for Peek/Encode, Ghidra
                    # itself often kept the argument (it tracks spills the
                    # resolver cannot), so the applied offset cannot be
                    # contradicted.  NOT extended to PeekBool: its cell was
                    # always in dropped EAX, so every applied arg is
                    # sweep-written and an offset matching no resolved row
                    # is a misassignment even when unresolved rows are
                    # nearby (the DetonateProjectile C415/C488 strips were
                    # exactly that, verified by hand).
                    n_und += 1
                    continue
                # no plausible row carries this offset: the site is wrong.
                # It is REPAIRABLE only if every plausible row agrees.
                n_wrong += 1
                fixable = (len(plaus_offs) == 1 and None not in plaus_offs)
                tgt = plaus_offs.copy().pop() if fixable else None
                print('WRONG %-58s applied +0x%-6x %s'
                      % (loc, aoff,
                         '-> +0x%x (all %d plausible rows agree)'
                         % (tgt, len(s['plaus'])) if fixable else
                         'STRIP; plausible: %s'
                         % sorted('0x%x' % o for o in plaus_offs
                                  if o is not None)))
                if fix:
                    l = src[s['line']]
                    if fixable:
                        row = [r for r in s['plaus']
                               if cell_offset(r['cell']) == tgt][0]
                        ex = row_expr(row, tgt, '\n'.join(src), fctx)
                    else:
                        ex = None
                    if fixable and ex is None:
                        changed = changed  # unknown row shape: leave reported
                    else:
                        # a wrong cell is a wild WRITE once the family goes
                        # live (Peek re-encodes) - bare is the safe bring-up
                        # state and stays visible to later passes.
                        seg = (cname + '(%s)' % ex) if ex else cname + '()'
                        src[s['line']] = l[:s['col']] + seg + l[s['end']:]
                        changed = True
                continue
            if s['arg'] is not None:
                continue           # applied but offset-less (ctx forms etc)
            # bare site: fill only when every plausible row agrees on offset
            if len(plaus_offs) != 1 or None in plaus_offs:
                n_und += 1
                continue
            roff = plaus_offs.pop()
            n_ver += 1
            if fix:
                ex = row_expr(s['plaus'][0], roff, '\n'.join(src), fctx)
                if ex is None:
                    continue
                l = src[s['line']]
                src[s['line']] = (l[:s['col']] +
                                  l[s['col']:].replace(cname + '()',
                                                       '%s(%s)' % (cname, ex), 1))
                changed = True
                n_fixed += 1
        if changed:
            open(path, 'w').write('\n'.join(src))
    print('verified=%d wrong=%d fixed-bare=%d undecided=%d'
          % (n_ver, n_wrong, n_fixed, n_und))


if __name__ == '__main__':
    main()
