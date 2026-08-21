#!/usr/bin/env python3
"""Count call sites of a function in src/, bucketed by ARGUMENT COUNT.

Written after miscounting the same sweep three times in one afternoon. Every
ad-hoc `grep -c` for a call site in this tree is wrong in at least one of
three ways, and the wrong number ends up in a commit message:

  1. It counts COMMENTS. The headers here discuss call sites at length, so a
     grep for "Foo()" also counts the prose - including paragraphs written
     minutes earlier in the very file being measured. This inflated the
     dropped-register backlog to 692 (real: 574) and FindSpriteFrame's argless
     count to 162 (real: 150).
  2. It stops at the first ';'. Multi-line calls are truncated or missed, so a
     shape survey built on `grep -o 'Foo([^;]*)'` silently under-reports.
  3. It counts commas naively. `Foo(a, g(b, c))` has two arguments, not three,
     so any bucket-by-comma-count is wrong exactly where the interesting
     call sites are.

This does the boring correct thing: strip comments, match the call by name,
walk the parentheses to find the real closing one, and split arguments at
depth zero only.

Usage:
  python3 tools/count_call_args.py BlitSpriteClipped
  python3 tools/count_call_args.py BlitSpriteClipped --want 4 --list
"""
import argparse
import glob
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from callsites import blank_comments, find as find_calls   # noqa: E402


def strip_comments(src):
    src = re.sub(r"/\*.*?\*/", "", src, flags=re.S)
    return re.sub(r"//[^\n]*", "", src)


def split_args(text):
    """Split a call's argument text at parenthesis depth zero."""
    args, depth, cur = [], 0, ""
    for ch in text:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            args.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip() or args:
        args.append(cur.strip())
    return [a for a in args if a]


def call_sites(src, name):
    """Yield (offset, [args], is_definition) for each occurrence, paren-aware.

    A definition is told from a call by what FOLLOWS the closing parenthesis -
    a body brace rather than a semicolon or an operator. Trying to recognise
    it from what PRECEDES the name (a return type) does not work: a character
    class permissive enough for `unsigned int *` also matches the leading
    whitespace of an ordinary indented call, which silently discarded 226 of
    227 sites the first time this was written.
    """
    for m in re.finditer(r"\b%s\s*\(" % re.escape(name), src):
        i = m.end()
        depth, j = 1, m.end()
        while depth and j < len(src):
            if src[j] == "(":
                depth += 1
            elif src[j] == ")":
                depth -= 1
            j += 1
        yield m.start(), split_args(src[i:j - 1]), src[j:].lstrip().startswith("{")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("name")
    ap.add_argument("--want", type=int, help="argument count considered complete")
    ap.add_argument("--list", action="store_true", help="list the incomplete sites")
    ap.add_argument("--include-definition", action="store_true")
    args = ap.parse_args()

    buckets, incomplete = {}, []
    for path in sorted(glob.glob("src/**/*.c", recursive=True) +
                       glob.glob("src/**/*.cpp", recursive=True)):
        src = open(path, errors="replace").read()
        b = blank_comments(src)
        for c in find_calls(src, args.name, b):
            if c["kind"] != "call" and not args.include_definition:
                continue
            n = len(c["args"])
            buckets[n] = buckets.get(n, 0) + 1
            if args.want is not None and n != args.want:
                incomplete.append((path, b[:c["start"]].count("\n") + 1, n))

    total = sum(buckets.values())
    print("%s: %d call sites" % (args.name, total))
    for n in sorted(buckets):
        print("   %d argument(s): %d" % (n, buckets[n]))
    if args.want is not None:
        print("   complete (%d args): %d ; INCOMPLETE: %d across %d files"
              % (args.want, buckets.get(args.want, 0), len(incomplete),
                 len({p for p, _, _ in incomplete})))
        if args.list:
            for p, ln, n in incomplete:
                print("      %s:%d  (%d args)" % (p, ln, n))


if __name__ == "__main__":
    main()
