#!/usr/bin/env python3
"""Report which confirmed dropped-register arguments are still unfixed.

tools/sweep_callsite_corroborate.py already did the hard part: it proved,
from the CALLERS' disassembly, which registers are genuine incoming
arguments that Ghidra failed to model, and cached 700 (function, register)
pairs in tools/dropped_regs_confirmed.json. What that file does NOT say is
how many have since been repaired in the C tree - which is the number you
need to plan a sweep. This script answers that.

The test is not "does the file still mention in_EAX". Two things have to be
told apart, and getting it wrong swings the count by hundreds:

  * PROMOTED - the register survives as the NAME OF A PARAMETER, e.g.
    `void AppendPersistentButtonName(int *param_1, char *in_EAX)`. That is
    the established fix in this tree (MSVC cannot express an EAX argument,
    so the register is promoted to a trailing/positional parameter and the
    callers pass it explicitly). Ugly name, correct code - it is FIXED.
  * STILL A LOCAL - the register is declared inside the body, e.g.
    FindSpriteFrame's `int in_EAX; int unaff_ESI;`. Nothing supplies it,
    every call site passes nothing, and the value read at runtime is
    whatever happened to be in the register. That is the real backlog.

So the script locates each function's own definition, splits its parameter
list from its body, and only counts the register as open when the name is
absent from the parameter list. Comments are stripped first, because the
headers in this tree discuss `in_EAX` at length in prose.

Usage:
  python3 tools/dropped_reg_backlog.py [--json out.json] [--top N]
"""
import argparse
import collections
import json
import os
import re

CONFIRMED = "tools/dropped_regs_confirmed.json"

# Ghidra's spelling for a register read before it is written, per register.
NAMES = {
    "eax": ["in_EAX"],
    "ebx": ["unaff_EBX", "in_EBX"],
    "esi": ["unaff_ESI", "in_ESI"],
    "edi": ["unaff_EDI", "in_EDI"],
    "ebp": ["unaff_EBP", "in_EBP"],
    "ecx": ["unaff_ECX", "in_ECX"],
    "edx": ["unaff_EDX", "in_EDX"],
}


def strip_comments(src):
    src = re.sub(r"/\*.*?\*/", "", src, flags=re.S)
    return re.sub(r"//[^\n]*", "", src)


def param_list_of(src, func):
    """The text between the parentheses of func's own definition, or ''."""
    m = re.search(r"\b%s\s*\(([^;{]*?)\)\s*\{" % re.escape(func), src, re.S)
    if not m:  # Ghidra style puts the brace on its own line after a blank one
        m = re.search(r"\b%s\s*\(([^;{]*?)\)\s*$" % re.escape(func), src, re.M | re.S)
    return m.group(1) if m else ""


def classify(entry):
    path = entry["path"]
    if not os.path.exists(path):
        return "missing"
    src = strip_comments(open(path, errors="replace").read())
    names = NAMES[entry["reg"]]
    if not any(re.search(r"\b%s\b" % n, src) for n in names):
        return "gone"
    plist = param_list_of(src, entry["func"])
    if any(re.search(r"\b%s\b" % n, plist) for n in names):
        return "promoted"
    return "open"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--json", help="write the open entries here")
    ap.add_argument("--top", type=int, default=30)
    args = ap.parse_args()

    entries = json.load(open(CONFIRMED))
    buckets = collections.defaultdict(list)
    for e in entries:
        buckets[classify(e)].append(e)

    print("confirmed (function, register) pairs : %d" % len(entries))
    print("  register no longer named at all    : %d" % len(buckets["gone"]))
    print("  promoted to a real parameter       : %d" % len(buckets["promoted"]))
    print("  STILL DECLARED AS A LOCAL (open)   : %d" % len(buckets["open"]))
    print("  file no longer exists              : %d" % len(buckets["missing"]))

    by_func = collections.defaultdict(list)
    for e in buckets["open"]:
        by_func[(e["func"], e["path"], e["callsites"])].append(e["reg"])
    print("\nopen functions: %d\n" % len(by_func))
    print("%7s  %-34s %-10s %s" % ("SITES", "FUNCTION", "REGISTERS", "PATH"))
    ranked = sorted(by_func.items(), key=lambda kv: -kv[0][2])
    for (func, path, sites), regs in ranked[: args.top]:
        print("%7d  %-34s %-10s %s" % (sites, func, "+".join(sorted(regs)), path))

    if args.json:
        json.dump(buckets["open"], open(args.json, "w"), indent=1)
        print("\nwrote %s" % args.json)


if __name__ == "__main__":
    main()
