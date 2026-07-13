#!/usr/bin/env python3
"""Rank WinMain->server-list functions by REAL logic gaps, not raw asm-differ
%, which is structurally deflated by unlinked call-target noise (the
original binary's call targets are never symbolized - see tools/README.md /
session notes). A "real" mismatch is any line where both sides have a full
instruction that differs in mnemonic/operand with no plausible reloc
explanation (gen_diff_report.py's "d-neq" classification); immediate-only
and relocation-annotation lines are noise and excluded.

Usage: python3 tools/rank_real_gaps.py [build/link_attempt]
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_diff_report as gdr


def classify(line):
    if re.search(r"\s\|\s", line):
        return "neq"
    if re.search(r"\si\s", line):
        return "imm"
    if re.search(r"\sr\s", line):
        return "reloc"
    if "IMAGE_REL" in line:
        return "relocref"
    if re.match(r"^\s*$", line):
        return "blank"
    return "match"


def main():
    build_dir = sys.argv[1] if len(sys.argv) > 1 else "build/link_attempt"
    results = []
    for src_rel, va_hex, hint in gdr.FUNCS:
        r = gdr.run_diff(build_dir, src_rel, va_hex, hint)
        if r.get("status") != "OK":
            results.append((src_rel, r.get("status"), None, None, None, None))
            continue
        plain = r.get("plain", "")
        counts = {"neq": 0, "imm": 0, "reloc": 0, "relocref": 0, "match": 0, "blank": 0}
        for line in plain.splitlines():
            counts[classify(line)] += 1
        total_instr = counts["neq"] + counts["imm"] + counts["reloc"] + counts["match"]
        neq_pct = round(100.0 * counts["neq"] / total_instr, 1) if total_instr else None
        results.append((src_rel, "OK", r.get("match_pct"), neq_pct, counts["neq"], total_instr))

    results.sort(key=lambda x: (-1 if x[3] is None else x[3]), reverse=True)
    print(f"{'file':<55} {'status':<8} {'raw%':>6} {'real-mismatch%':>15} {'d-neq lines':>12} {'total lines':>12}")
    for src_rel, status, pct, neq_pct, neq, total in results:
        pct_s = f"{pct}%" if pct is not None else "-"
        neq_pct_s = f"{neq_pct}%" if neq_pct is not None else "-"
        print(f"{src_rel:<55} {status:<8} {pct_s:>6} {neq_pct_s:>15} {neq if neq is not None else '-':>12} {total if total is not None else '-':>12}")


if __name__ == "__main__":
    main()
