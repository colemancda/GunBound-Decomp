#!/usr/bin/env python3
"""sweep_peekbool_prove.py - batch closer for the PeekBool tail.

For each bare PeekPacketChecksumBool() site:
  1. identify its ROW: a label pin if one exists, else the unique
     non-conflicting (plausible) row from guard_callsite_verify's anchor
     machinery.  Ambiguity -> skip.
  2. resolve the row's cell to an expression:
       - ctx rows directly
       - `<reg crosses>` rows via guard_dominator_base's dominance proof
       - `dword ptr [esp+X] (+off)` rows via a SLOT TRACE: the last
         `mov [esp+X], reg` before the row, whose reg is defined by a
         directly-preceding lea/ctx-load, accepted only when no store to
         [esp+X-4 / X / X+4] intervenes (the +-4 guards against push-depth
         aliasing) and no jump enters (store, row] from outside.
  3. spell the base:
       - 'this' -> the function's __fastcall/__thiscall first parameter
       - a ctx or lea-derived base -> literal expression
Every fill is printed with its proof line; run guard_callsite_verify
afterwards - it must report wrong=0.
"""
import csv
import os
import re
import subprocess
import sys
import importlib.util

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)


def load(name):
    spec = importlib.util.spec_from_file_location(name.replace('.py', ''),
                                                  os.path.join(HERE, name))
    m = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(m)
    return m


g = load('guard_callsite_verify.py')
d = load('guard_dominator_base.py')


def slot_trace(dis, X, site_addr):
    """value of [esp+X] at site_addr, as (base_expr, off), or (None, why)."""
    addr = lambda l: int(l[:8], 16)
    store = None
    for i, l in enumerate(dis):
        if addr(l) >= site_addr:
            break
        if re.search(r'mov\tdword ptr \[esp \+ ' + re.escape(X) + r'\], (e\w\w)$', l):
            store = (i, l)
    if store is None:
        return None, 'no store to [esp+%s]' % X
    si, sl = store
    W = addr(sl)
    reg = re.search(r'\], (e\w\w)$', sl).group(1)
    # aliasing guard: any store to X-4/X/X+4 in (W, site) kills it
    xs = {'0x%x' % (int(X, 16) + k) for k in (-4, 0, 4)}
    for l in dis:
        a = addr(l)
        if W < a < site_addr and re.search(
                r'mov\tdword ptr \[esp \+ (0x[0-9a-f]+)\],', l):
            off = re.search(r'\[esp \+ (0x[0-9a-f]+)\]', l).group(1)
            if off in xs:
                return None, 'interposed store at 0x%x' % a
    # bypass edges
    for l in dis:
        m = re.search(r'\tj\w+\t(0x4[0-9a-f]+)$', l)
        if m:
            t = int(m.group(1), 16)
            s0 = addr(l)
            if W < t <= site_addr and (s0 <= W or s0 > site_addr):
                return None, 'bypass 0x%x<-0x%x' % (t, s0)
    # what fed reg?  look back a couple of instructions
    for k in range(si - 1, max(si - 4, -1), -1):
        l = dis[k]
        m = re.search(r'\tlea\t' + reg + r', \[(e\w\w) \+ (0x[0-9a-f]+)\]$', l)
        if m:
            base, val = d.resolve(dis, d.in_edges(dis), m.group(1), addr(l))
            if base == 'this':
                return ('this', val + int(m.group(2), 16))
            return None, 'lea base %s unresolved (%s)' % (m.group(1), val)
        m = re.search(r'\tadd\t' + reg + r', (0x[0-9a-f]+)$', l)
        if m:
            # reg = something + imm: check the previous def
            mm = re.search(r'\tmov\t' + reg + r', dword ptr \[0x5b3484\]$',
                           dis[k - 1] if k else '')
            if mm:
                return ('ctx', int(m.group(1), 16))
            return None, 'add-chain base unresolved'
        if re.search(r'\t' + reg + r',', l):
            return None, 'reg fed by: %s' % l.split('\t', 1)[1].strip()
    return None, 'no reg def found'


def resolve_row(row, r, dis_box, param, src):
    """(expression, None) or (None, why) for one row's cell."""
    cell = row['cell']
    m = re.match(r'dword ptr \[0x5b3484\] \+ (0x[0-9a-f]+)$', cell)
    if m:
        return '(byte *)(g_clientContext + %s)' % m.group(1), None
    m = re.match(r'<(e\w\w) (?:crosses block end at 0x[0-9a-f]+|'
                 r'live-in at entry)> \+ (0x[0-9a-f]+)$', cell)
    if m:
        if dis_box[0] is None:
            dis_box[0] = d.disasm(r[0], r[1])
        dis = dis_box[0]
        reg = m.group(1) if 'crosses' in cell else \
            {'ecx': 'ecx'}.get(m.group(1), m.group(1))
        if 'live-in' in cell and reg == 'ecx':
            base, val = 'this', 0
        elif 'live-in' in cell and reg == 'eax':
            base, val = 'in_EAX', 0
        else:
            base, val = d.resolve(dis, d.in_edges(dis), reg, row['addr'])
        off = val + int(m.group(2), 16) if isinstance(val, int) else None
        if base == 'this' and param:
            return '(byte *)%s + 0x%x' % (param, off), None
        if base == 'in_EAX' and re.search(r'\bint in_EAX;', '\n'.join(src)):
            return '(byte *)(in_EAX + 0x%x)' % off, None
        return None, 'dominator: %s/%s' % (base, val)
    m = re.match(r'dword ptr \[esp \+ (0x[0-9a-f]+)\]'
                 r'(?: \+ (0x[0-9a-f]+))?$', cell)
    if m:
        if dis_box[0] is None:
            dis_box[0] = d.disasm(r[0], r[1])
        dis = dis_box[0]
        base, val = slot_trace(dis, m.group(1), row['addr'])
        extra = int(m.group(2), 16) if m.group(2) else 0
        if base == 'this' and param:
            return '(byte *)%s + 0x%x' % (param, val + extra), None
        if base == 'ctx':
            return '(byte *)(g_clientContext + 0x%x)' % (val + extra), None
        return None, 'slot: %s' % val
    return None, 'shape: %s' % cell


def main():
    fix = '--fix' in sys.argv
    files = [a for a in sys.argv[1:] if a != '--fix']
    n_fill = n_skip = 0
    for path in files:
        r = g.rng(path)
        if not r:
            continue
        src = open(path, errors='ignore').read().split('\n')
        sites = g.find_sites(src, 'PeekPacketChecksumBool', 'PeekBool')
        if not any(s['arg'] is None for s in sites):
            continue
        rows = g.parse_rows(r[0], r[1], 'PeekBool')
        calls = g.disasm_calls(r[0], r[1])
        toks = g.call_tokens(src)
        el = g.eligible_anchors(calls, toks)
        g.row_anchors(rows, calls, {0x4065a0}, el)
        g.site_anchors(src, sites, toks, el)
        g.match(sites, rows)
        g.label_pin(src, sites, rows)
        dis_box = [None]
        param = None
        for l in src:
            m = re.match(r'^\w[\w ]*?__(?:fastcall|thiscall) \w+\((?:int|uint|byte|char|'
                         r'undefined4)\s*\*?\s*([A-Za-z_]\w*)[,)]', l)
            if m:
                param = m.group(1)
                break
        ch = False
        # cross-site sanity: a row can belong to ONE site.  If two bare sites
        # share the same sole plausible row, the anchor machinery has
        # over-conflicted (seen in State11_InBattle_ProcessBattleAction:
        # 8 sites all "resolved" to row 0x4b59f5) - mark all of them
        # ambiguous rather than filling duplicates.
        sole = {}
        for s in sites:
            if s['arg'] is None and s['pin'] is None and len(s['plaus']) == 1:
                sole.setdefault(s['plaus'][0]['addr'], []).append(s)
        dup = {a for a, ss in sole.items() if len(ss) > 1}
        for s in sites:
            if s['arg'] is not None:
                continue
            if s['pin'] is None and len(s['plaus']) == 1 \
                    and s['plaus'][0]['addr'] in dup:
                n_skip += 1
                continue
            rows_to_try = [s['pin']] if s['pin'] is not None else s['plaus']
            if not rows_to_try:
                n_skip += 1
                continue
            # resolve EVERY candidate row; fill only if they all agree
            exprs = set()
            why = None
            for row in rows_to_try:
                e2, w2 = resolve_row(row, r, dis_box, param, src)
                if e2 is None:
                    why = w2
                    exprs = None
                    break
                exprs.add(e2)
            if exprs is None or len(exprs) != 1:
                if exprs is not None and len(exprs) > 1:
                    why = 'candidates disagree: %s' % sorted(exprs)
                row = rows_to_try[0]
                print('SKIP %s:%d  row 0x%x  %s' % (path, s['line'] + 1,
                                                    row['addr'], why))
                n_skip += 1
                continue
            ex = exprs.pop()
            row = rows_to_try[0]
            if True:
                print('FILL %s:%d  row 0x%x  %s  [%s]' % (
                    path, s['line'] + 1, row['addr'], ex,
                    'pin' if s['pin'] else '%d rows agree' % len(rows_to_try)))
                if fix:
                    l = src[s['line']]
                    src[s['line']] = (l[:s['col']] +
                                      l[s['col']:].replace(
                                          'PeekPacketChecksumBool()',
                                          'PeekPacketChecksumBool(%s)' % ex, 1))
                    ch = True
                n_fill += 1
            continue
            cell = row['cell']
            ex = why = None
            m = re.match(r'dword ptr \[0x5b3484\] \+ (0x[0-9a-f]+)$', cell)
            if m:
                ex = '(byte *)(g_clientContext + %s)' % m.group(1)
            else:
                m = re.match(r'<(e\w\w) (?:crosses block end at 0x[0-9a-f]+|'
                             r'live-in at entry)> \+ (0x[0-9a-f]+)$', cell)
                if m:
                    if dis is None:
                        dis = d.disasm(r[0], r[1])
                    reg = 'ecx' if 'live-in' in cell else m.group(1)
                    base, val = (('this', 0) if reg == 'ecx' else
                                 d.resolve(dis, d.in_edges(dis), reg, row['addr']))
                    if base == 'this' and param:
                        ex = '(byte *)%s + 0x%x' % (param, val + int(m.group(2), 16))
                    else:
                        why = 'dominator: %s' % val
                else:
                    m = re.match(r'dword ptr \[esp \+ (0x[0-9a-f]+)\]'
                                 r'(?: \+ (0x[0-9a-f]+))?$', cell)
                    if m:
                        if dis is None:
                            dis = d.disasm(r[0], r[1])
                        base, val = slot_trace(dis, m.group(1), row['addr'])
                        extra = int(m.group(2), 16) if m.group(2) else 0
                        if base == 'this' and param:
                            ex = '(byte *)%s + 0x%x' % (param, val + extra)
                        elif base == 'ctx':
                            ex = '(byte *)(g_clientContext + 0x%x)' % (val + extra)
                        else:
                            why = 'slot: %s' % val
                    else:
                        why = 'shape: %s' % cell
            if ex is None:
                print('SKIP %s:%d  row 0x%x  %s' % (path, s['line'] + 1,
                                                    row['addr'], why))
                n_skip += 1
                continue
            print('FILL %s:%d  row 0x%x  %s  [%s]' % (
                path, s['line'] + 1, row['addr'], ex,
                'pin' if s['pin'] else 'unique-plausible'))
            if fix:
                l = src[s['line']]
                src[s['line']] = (l[:s['col']] +
                                  l[s['col']:].replace('PeekPacketChecksumBool()',
                                                       'PeekPacketChecksumBool(%s)' % ex, 1))
                ch = True
            n_fill += 1
        if ch:
            open(path, 'w').write('\n'.join(src))
    print('fill=%d skip=%d' % (n_fill, n_skip))


if __name__ == '__main__':
    main()
