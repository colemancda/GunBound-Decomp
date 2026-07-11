#!/usr/bin/env bash
# Compile one src/cxx/*.cpp under real MSVC 7.1 (Docker+Wine) and print the
# asm-differ score for one mangled symbol in it, in a single command - the
# per-method promote-verify loop described in src/cxx/PLAN.md's Tooling
# section. Wraps tools/msvc-env's docker invocation + tools/score.sh.
#
# Usage: tools/promote.sh <cxx-source-relpath> <mangled-symbol> <start-VA-hex> <end-VA-hex>
#   e.g.  tools/promote.sh src/cxx/Widget.cpp '?SetFocus@CWidget@@UAEX_N@Z' 50e860 50e868
#
# Get the mangled symbol name by compiling once and checking the object's
# symbol table, e.g.:
#   llvm-objdump -t build/Widget_cmp.obj | grep SetFocus
#
# NOTE: a bad #include path in the source (or any other error that spawns a
# GUI dialog under Wine) hangs indefinitely with no visible error - if this
# script seems stuck past ~30s, ctrl-C, run `docker ps` to find the stuck
# container, `docker kill` it, fix the source, and retry.
set -euo pipefail

SRC="$1"
SYM="$2"
START="$3"
END="$4"

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

BASENAME="$(basename "$SRC" .cpp)"
OBJ="build/${BASENAME}_cmp.obj"
mkdir -p build

timeout 90 docker run --rm --platform linux/amd64 -v "$PWD":/work -w /work \
    -e INCLUDE="Z:\\work\\include\\msvc;Z:\\work\\include;Z:\\opt\\msvc7\\include;Z:\\opt\\msvc7\\PlatformSDK\\include" \
    -e LIB="Z:\\opt\\msvc7\\lib;Z:\\opt\\msvc7\\PlatformSDK\\lib" \
    gb-msvc wine "Z:\\opt\\msvc7\\bin\\cl.exe" /c /O2 \
    "Z:\\work\\${SRC//\//\\\\}" "/Fo${OBJ//\//\\\\}"

tools/score.sh "$SYM" "$START" "$END" "$OBJ"
