#!/usr/bin/env python3
"""Byte-verification report for the src/cxx/ C++ reconstruction layer (see
src/cxx/PLAN.md's "byte-compare pass"). Reuses tools/gen_diff_report.py's
scoring/rendering machinery against the promoted C++ methods instead of the
raw-C startup path.

Usage:
    python3 tools/gen_cxx_score_report.py [build/link_attempt] [cxx-score-report.html]

Requires the .obj files for the functions below to already exist (run
tools/msvc-env/_link_attempt.sh first, which compiles every src/cxx/*.cpp
alongside the raw C tree) and an objdump whose path contains "llvm-" (see
diff_settings.py) - override with GB_OBJDUMP.

Add an entry here every time a src/cxx method gets a real address + mangled
symbol worth tracking - see tools/promote.sh for the one-off compile+score
loop used to find the symbol name and pin down VA ranges before adding a row.
"""
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_diff_report as gdr  # noqa: E402

REPO = gdr.REPO

# (src/cxx file, original VA hex without 0x, mangled/decorated symbol hint,
#  size in bytes from PROGRESS.csv). The size is passed explicitly (see
# run_diff's size_override) rather than auto-detected: MSVC 7.1 puts each
# C++ member function in its own COMDAT section starting at address 0x0,
# so gen_diff_report's "next symbol at a higher address" heuristic can't
# tell functions in the same object apart by position once there's more
# than one - every one of them "looks like" it starts at the same spot.
FUNCS = [
    # 8, not the 16-byte gap to the next PROGRESS.csv row: the real function
    # is 7 bytes (3 instructions); 0x50e868-0x50e86f is alignment padding
    # (confirmed via a manual asm-differ run - see tools/promote.sh usage
    # in the score-verification history for this method).
    ("src/cxx/Widget.cpp", "50e860", "?SetFocus@CWidget@@UAEX_N@Z", 8),
    ("src/cxx/Widget.cpp", "50e2f0", "?ResetPressState@CWidget@@QAE_NHH@Z", 90),
    ("src/cxx/Widget.cpp", "50e520", "?Draw@CWidget@@UAEXXZ", 49),
    ("src/cxx/Widget.cpp", "50e3a0", "?OnDragMove@CWidget@@UAE_NHH@Z", 120),
    ("src/cxx/Widget.cpp", "50ea50", "?DispatchKey@CWidget@@UAE_NH@Z", 92),
    ("src/cxx/Widget.cpp", "50eab0", "?DispatchMouse@CWidget@@UAE_NH@Z", 85),
    ("src/cxx/Widget.cpp", "50e730", "?MoveBy@CWidget@@QAEXHH@Z", 81),
    ("src/cxx/Widget.cpp", "50e7d0", "?SetEnabled@CWidget@@QAEX_N@Z", 72),
    ("src/cxx/Widget.cpp", "50e9c0", "?HitTest@CWidget@@UAE_NHH@Z", 131),
    ("src/cxx/Widget.cpp", "50e870", "?MouseMoveChildren@CWidget@@QAE_NHH@Z", 99),
    ("src/cxx/Widget.cpp", "50e8e0", "?MouseDownChildren@CWidget@@QAE_NHH@Z", 99),
    ("src/cxx/Widget.cpp", "50e950", "?MouseUpChildren@CWidget@@QAE_NHH@Z", 99),
    ("src/cxx/Widget.cpp", "50e620", "?FindChildIndex@CWidget@@QAEHHH@Z", 68),
    ("src/cxx/Widget.cpp", "50e670", "?AddChild@CWidget@@QAEXPAV1@@Z", 80),
    ("src/cxx/Widget.cpp", "50eb10", "?OnCommand@CWidget@@UAEXHHH@Z", 465),
]

SECTIONS = [
    ("CWidget - base class virtuals + helpers (src/cxx/Widget.cpp)", [
        "src/cxx/Widget.cpp",
    ]),
]


def main():
    build_dir = sys.argv[1] if len(sys.argv) > 1 else os.path.join(REPO, "build", "link_attempt")
    out_path = sys.argv[2] if len(sys.argv) > 2 else os.path.join(REPO, "cxx-score-report.html")

    # Multiple rows share one src file (every CWidget method lives in
    # Widget.cpp) - gen_diff_report's by-file result map only keeps the
    # last result per file, so key results by symbol instead and adapt
    # the section/lookup shape it expects.
    results = []
    for src_rel, va_hex, hint, size in FUNCS:
        r = gdr.run_diff(build_dir, src_rel, va_hex, hint, size_override=size)
        r["file"] = f"{src_rel}::{hint}"
        print(f"{r['file']}: {r.get('status')} {r.get('symbol', '')} {r.get('size', '')}", file=sys.stderr)
        results.append(r)

    sections = [(title, [f"{src}::{hint}" for src, _, hint, _ in FUNCS if src in files])
                for title, files in SECTIONS]

    json_path = os.path.splitext(out_path)[0] + ".json"
    with open(json_path, "w") as f:
        json.dump(results, f, indent=2)

    size = gdr.render_report(
        results, out_path,
        sections=sections,
        report_title="src/cxx byte-verification: CWidget methods",
        report_sub=(
            "Instruction-level comparison of each promoted <code>src/cxx</code> "
            "C++ method against the original <code>GunBound.gme</code> bytes at "
            "its known VA, scored with <code>tools/asm-differ</code> (see "
            "<code>src/cxx/PLAN.md</code>'s \"byte-compare pass\"). A real "
            "MSVC 7.1 recompile of hand-written C++ can't fully byte-match "
            "an unlinked .obj - cross-function call targets are unresolved "
            "relocations here - so treat anything free of a "
            "<span style=\"color:var(--poor)\">red</span> diff line as "
            "effectively verified, not just literal 100% score."
        ),
        obj_dir_label="build/link_attempt/ (src/cxx/*.cpp objects)",
    )
    print(f"wrote {out_path} ({size} bytes) and {json_path}", file=sys.stderr)


if __name__ == "__main__":
    main()
