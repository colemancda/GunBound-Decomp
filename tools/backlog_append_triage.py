#!/usr/bin/env python3
"""Split the dropped-register backlog into cheap appends and real re-slots.

tools/dropped_reg_backlog.py says WHICH (function, register) pairs are still
open.  It does not say how expensive each one is, and the difference is large:

  CLEAN-APPEND     every source call site already passes exactly as many
                   arguments as the definition declares, so the recovered
                   register can be appended as a trailing parameter and every
                   site gets one more argument.  Mechanical.

  RESLOT/ARTIFACT  the sites pass FEWER arguments than the callee declares.
                   Appending there is a SILENT BUG: the recovered value lands
                   in an unrelated parameter and the result looks fixed.  These
                   need every slot rewritten, and often need Ghidra's
                   push-as-stack-store artifacts (`uStack_a08 = 0xff;` sitting
                   above an argless call) deleted and turned back into
                   arguments first.

  MIXED            different sites pass different counts - usually a genuine
                   re-slot at some sites only, so each site needs reading.

Picking a CLEAN-APPEND target off this list costs a fraction of what a
RESLOT one costs, which is worth knowing before starting rather than after.

The arity comparison is deliberately the same one tools/promoted_arity_audit.py
makes after a change; this just makes it available before.

Usage:  python3 tools/backlog_append_triage.py [--status CLEAN-APPEND]
"""
import argparse
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)


def backlog_rows():
    out = subprocess.run([sys.executable, os.path.join(HERE, 'dropped_reg_backlog.py'),
                          '--top', '10000'],
                         capture_output=True, text=True, cwd=ROOT).stdout
    rows = []
    for line in out.split('\n'):
        m = re.match(r'\s+(\d+)\s+(\S+)\s+(\S+)\s+(\S+)$', line)
        if m and m.group(4).startswith('src/'):
            rows.append((int(m.group(1)), m.group(2), m.group(3), m.group(4)))
    return rows


def declared_params(path, func):
    """Count the parameters on the definition line, or None if not found."""
    try:
        src = open(os.path.join(ROOT, path), errors='replace').read()
    except OSError:
        return None
    m = re.search(r'^[A-Za-z_][\w \*]*?\b' + re.escape(func) + r'\s*\(([^)]*)\)\s*$',
                  src, re.M)
    if not m:
        return None
    body = m.group(1).strip()
    if body in ('', 'void'):
        return 0
    return len([p for p in body.split(',') if p.strip()])


def passed_counts(func):
    out = subprocess.run([sys.executable, os.path.join(HERE, 'count_call_args.py'), func],
                         capture_output=True, text=True, cwd=ROOT).stdout
    return sorted({int(a) for a, _ in re.findall(r'(\d+) argument\(s\): (\d+)', out)})


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--status', help='show only this status')
    args = ap.parse_args()

    print("%5s %-28s %-9s %8s  %-9s %s"
          % ("SITES", "FUNCTION", "REGISTERS", "DECLARED", "PASSED", "STATUS"))
    tally = {}
    for sites, func, regs, path in backlog_rows():
        ndecl = declared_params(path, func)
        if ndecl is None:
            continue
        passed = passed_counts(func)
        if not passed:
            continue
        if passed == [ndecl]:
            status = 'CLEAN-APPEND'
        elif len(passed) > 1:
            status = 'MIXED'
        else:
            status = 'RESLOT/ARTIFACT'
        tally[status] = tally.get(status, 0) + 1
        if args.status and status != args.status:
            continue
        print("%5d %-28s %-9s %8d  %-9s %s"
              % (sites, func, regs, ndecl, ','.join(map(str, passed)), status))
    print()
    for k in sorted(tally):
        print("  %-16s %d" % (k, tally[k]))


if __name__ == '__main__':
    main()
