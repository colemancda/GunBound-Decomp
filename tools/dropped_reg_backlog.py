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
  * ALIASED - the register name survives as a local, but it is INITIALISED
    FROM A REAL PARAMETER: `int FindSpriteFrame(int container, ...) { int
    in_EAX = container; ... }`. This is what a promotion looks like when the
    author kept the register name so the body did not have to change. Also
    FIXED, and it is worth 34 entries - counting these as open reports 608
    instead of 574, which is how this script read on its first outing.
  * STILL A LOCAL - the register is declared inside the body with nothing
    assigned to it. Nothing supplies it, every call site passes nothing, and
    the value read at runtime is whatever happened to be in the register.
    That is the real backlog.

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


_BYNAME = None


def locate(entry):
    """Find the entry's file, tolerating renames since the scan was cached.

    The cached path goes stale every time a function is renamed or moved --
    and a stale path is scored "missing", which silently REMOVES the pair from
    the open count.  Renaming ten functions quietly shrank this backlog by ten
    without a single register being recovered, which is the wrong direction for
    a measurement to be wrong in.  Fall back to locating the definition by
    name.
    """
    global _BYNAME
    path = entry["path"]
    if os.path.exists(path):
        return path
    if _BYNAME is None:
        _BYNAME = {}
        for base, _, files in os.walk("src"):
            for f in files:
                if f.endswith((".c", ".cpp")):
                    _BYNAME.setdefault(os.path.splitext(f)[0], os.path.join(base, f))
    return _BYNAME.get(entry["func"])


def classify(entry):
    path = locate(entry)
    if not path:
        return "missing"
    src = strip_comments(open(path, errors="replace").read())
    names = NAMES[entry["reg"]]
    plist = param_list_of(src, entry["func"])
    # A recovered register is renamed to regEax/regEsi/... as it is promoted,
    # so the Ghidra local (in_EAX, unaff_ESI, ...) vanishes from the file
    # entirely.  Test the parameter list for the promoted spelling BEFORE the
    # "is the old name still present" test, or every recovery is miscounted as
    # "gone" -- which reads as lost information rather than as work completed.
    promoted_name = "reg" + entry["reg"][0].upper() + entry["reg"][1:].lower()
    if re.search(r"\b%s\b" % promoted_name, plist):
        return "promoted"
    if not any(re.search(r"\b%s\b" % n, src) for n in names):
        return "gone"
    if any(re.search(r"\b%s\b" % n, plist) for n in names):
        return "promoted"
    for n in names:
        # `<type> in_EAX = <something>;` - a declaration WITH an initialiser
        # is the register aliased onto a real parameter, not an unsupplied one.
        if re.search(r"\b\w+\s+\*?%s\s*=\s*[^;=][^;]*;" % n, src):
            return "aliased"
        # The same alias split across two statements:
        #     uint unaff_ESI;
        #     ...
        #     unaff_ESI = (uint)charsetKey;
        # Ghidra emits this form whenever the declaration and the first
        # assignment are separated, and BlitSpriteText is exactly it -- fully
        # recovered since 2026-07-17, yet counted as open (and as the third
        # largest item in the backlog) purely because the initialiser was on
        # its own line.  Require the right-hand side to mention a real
        # parameter, so a self-assignment or a local cannot pass for a fix.
        m = re.search(r"^[ \t]*%s\s*=\s*([^;=][^;]*);" % n, src, re.M)
        # `in_EAX = in_EAX + (param_1 - ...)` mentions a parameter but is a
        # MODIFICATION of a still-unsupplied register, not an alias onto one,
        # so the register's own name must not appear on the right.
        if (m and n not in m.group(1)
                and any(re.search(r"\b%s\b" % re.escape(pn), m.group(1))
                        for pn in re.findall(r"\b\w+\b", plist))):
            return "aliased"
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
    print("  aliased onto a real parameter      : %d" % len(buckets["aliased"]))
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
