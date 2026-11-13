#!/usr/bin/env python3
"""Turn a --profile file into a table of the functions the time went to.

  profile_report.py PROFILE [BINARY] [--top N] [--nm NM] [--csv PROGRESS.csv]

PROFILE is what the game binary wrote for --profile FILE; BINARY is that same
binary, not stripped (default: recomp/build/host/gunbound). Lifted functions
are called f_<address>; their names are taken from PROGRESS.csv where it has
them. For a binary of another architecture pass a matching nm with --nm.
"""
import argparse
import bisect
import csv
import os
import re
import subprocess


def main():
    here = os.path.dirname(os.path.abspath(__file__))
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("profile")
    ap.add_argument("binary", nargs="?", default=os.path.join(here, "..", "build", "host", "gunbound"))
    ap.add_argument("--top", type=int, default=25)
    ap.add_argument("--nm", default="nm")
    ap.add_argument("--csv", default=os.path.join(here, "..", "..", "PROGRESS.csv"))
    args = ap.parse_args()

    names = {}
    if os.path.exists(args.csv):
        for row in csv.DictReader(open(args.csv, encoding="utf-8", errors="replace")):
            try:
                names[int(row.get("addr", ""), 16)] = row.get("name") or row.get("function") or ""
            except ValueError:
                pass

    syms = []
    out = subprocess.run([args.nm, "-n", "--defined-only", args.binary], stdout=subprocess.PIPE, check=True).stdout
    for line in out.decode().splitlines():
        parts = line.split()
        if len(parts) == 3 and parts[1] in "tTwW":
            syms.append((int(parts[0], 16), parts[2]))
    syms.sort()
    starts = [s[0] for s in syms]

    counts, total = {}, 0
    for line in open(args.profile):
        if line.startswith("#"):
            continue
        addr, n = line.split()
        addr, n = int(addr, 16), int(n)
        total += n
        i = bisect.bisect_right(starts, addr) - 1
        name = "(outside the program: libc, SDL, kernel)" if addr == 0 or i < 0 else syms[i][1]
        counts[name] = counts.get(name, 0) + n

    def label(name):
        m = re.fullmatch(r"f_([0-9a-f]{8})", name)
        if m:
            real = names.get(int(m.group(1), 16))
            return "%s %s" % (name, real) if real else name
        return name

    lifted = sum(n for name, n in counts.items() if re.fullmatch(r"f_[0-9a-f]{8}", name))
    outside = counts.get("(outside the program: libc, SDL, kernel)", 0)
    print("%d samples: %.1f%% lifted game code, %.1f%% runtime, %.1f%% outside the program" % (
        total, 100.0 * lifted / max(total, 1), 100.0 * (total - lifted - outside) / max(total, 1),
        100.0 * outside / max(total, 1)))
    acc = 0
    for name, n in sorted(counts.items(), key=lambda kv: -kv[1])[:args.top]:
        acc += n
        print("%6.2f%% %6.2f%%  %s" % (100.0 * n / total, 100.0 * acc / total, label(name)))


if __name__ == "__main__":
    main()
