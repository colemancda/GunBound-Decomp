#!/usr/bin/env python3
"""Rebuild the uniform-value worklist from the FULL triage scan.

The first uniform list was produced by a scratch script over the head of the
backlog and covered 78 pairs; backlog_triage_all.py now records per-site values
for all ~390 pairs that have direct call sites, so the same lever reaches much
further.

A pair qualifies ONLY when every call site resolved to a value AND all of them
agree.  Both halves matter.  A pair whose values dict holds a single entry can
still have sites the scan could not resolve, and those sites are exactly the
ones likely to differ -- applying the majority value there would replace a
missing value with a wrong one.  That is the BlitSpriteText failure mode
(0x1f4 at 35 sites, 0x32 at one), so the count is required to match the site
total, not merely to dominate it.
"""
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TRIAGE = os.path.join(ROOT, 'tools', 'backlog_triage.json')
OUT = os.path.join(ROOT, 'tools', 'backlog_uniform.json')


def render(v):
    """Triage stores immediates as decimal strings and ctx bases as 'ctx+0x...'."""
    if isinstance(v, str) and v.startswith('ctx+'):
        return v
    n = int(v)
    return '0x%x' % n


def main():
    out = []
    for e in json.load(open(TRIAGE)):
        vals = e.get('values') or {}
        if len(vals) != 1:
            continue
        (val, cnt), = vals.items()
        if cnt != e['sites']:          # unresolved sites are NOT agreement
            continue
        out.append({'func': e['func'], 'reg': e['reg'], 'path': e['path'],
                    'sites': e['sites'], 'value': render(val),
                    'pct': 100, 'distinct': 1, 'vals': {render(val): cnt}})
    out.sort(key=lambda x: -x['sites'])
    json.dump(out, open(OUT, 'w'), indent=1)
    print('uniform pairs: %d  covering %d call sites' % (out and len(out) or 0,
                                                         sum(o['sites'] for o in out)))
    for o in out[:20]:
        print('  %-26s %-4s %3d  %s' % (o['func'], o['reg'], o['sites'], o['value']))


if __name__ == '__main__':
    main()
