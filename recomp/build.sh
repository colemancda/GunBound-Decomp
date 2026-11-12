#!/usr/bin/env bash
# Build the statically recompiled client.
#
#   recomp/build.sh [host|aarch64] [--relift]
#
# host     native build with the system compiler      -> recomp/build/host/gunbound
# aarch64  cross build for Linux/arm64 (glibc)         -> recomp/build/aarch64/gunbound
#
# Environment:
#   RECOMP_EXE   original executable to lift (default: orig/GunBound.gme)
#   AARCH64_CC   cross compiler (default: the batocera h616 buildroot gcc)
#   JOBS         parallel compile jobs (default 4)
#   OPT          optimisation level for the lifted code (default -O1)
#   EXTRA_CFLAGS extra compiler flags for everything (e.g. -DRT_DYNAMIC_BASE)
#   LIFT_FLAGS   extra lifter flags (e.g. --no-flag-liveness)
#   VARIANT      suffix for the output directories, to keep an experimental build
#                (other LIFT_FLAGS / EXTRA_CFLAGS) next to the normal one
set -euo pipefail

target="${1:-host}"
relift=0
[ "${2:-}" = "--relift" ] && relift=1

here="$(cd "$(dirname "$0")" && pwd)"
root="$(cd "$here/.." && pwd)"
exe="${RECOMP_EXE:-$root/orig/GunBound.gme}"
csv="$root/PROGRESS.csv"
build="$here/build"
variant="${VARIANT:-}"
gen="$build/gen$variant"
out="$build/$target$variant"
jobs="${JOBS:-4}"
opt="${OPT:--O1}"

case "$target" in
host)
    cc="${CC:-gcc}"
    ;;
aarch64)
    cc="${AARCH64_CC:-/home/coleman/Developer/batocera.linux/output/h616/host/bin/aarch64-buildroot-linux-gnu-gcc}"
    ;;
*)
    echo "usage: $0 [host|aarch64] [--relift]" >&2
    exit 2
    ;;
esac
command -v "$cc" >/dev/null || { echo "compiler not found: $cc" >&2; exit 2; }
[ -f "$exe" ] || { echo "original executable not found: $exe (set RECOMP_EXE)" >&2; exit 2; }

# ---- 1. lift (shared by all targets; redone when the lifter or the inputs change)
mkdir -p "$gen" "$out/obj"
stamp="$gen/.stamp"
need=$relift
[ -f "$stamp" ] || need=1
if [ "$need" = 0 ]; then
    for f in "$here"/lift/*.py "$exe" "$csv"; do
        [ "$f" -nt "$stamp" ] && need=1
    done
fi
if [ "$need" = 1 ]; then
    echo "== lifting $exe"
    t0=$(date +%s)
    # shellcheck disable=SC2086
    python3 "$here/lift/lift.py" --pe "$exe" --csv "$csv" --out "$gen" ${LIFT_FLAGS:-}
    touch "$stamp"
    echo "== lift took $(( $(date +%s) - t0 ))s"
fi

# ---- 2. compile + link through ninja
cflags_common="-std=gnu11 -pthread -fno-strict-aliasing -fwrapv -fno-stack-protector -I$here/runtime -I$gen ${EXTRA_CFLAGS:-}"
{
    echo "cc = $cc"
    echo "gen_cflags = $opt -foptimize-sibling-calls $cflags_common -w"
    echo "rt_cflags = -O2 -g $cflags_common -Wall -Wextra -Wno-unused-parameter"
    echo "rule gen"
    echo "  command = \$cc \$gen_cflags -c \$in -o \$out"
    echo "  description = CC \$out"
    echo "rule rt"
    echo "  command = \$cc \$rt_cflags -MMD -MF \$out.d -c \$in -o \$out"
    echo "  depfile = \$out.d"
    echo "  description = CC \$out"
    echo "rule link"
    echo "  command = \$cc -o \$out \$in -lm -pthread"
    echo "  description = LINK \$out"
    objs=""
    for src in "$gen"/chunk_*.c "$gen/tables.c"; do
        o="obj/$(basename "${src%.c}").o"
        echo "build $o: gen $src | $here/runtime/cpu.h $here/runtime/rt.h $gen/funcs.h"
        objs="$objs $o"
    done
    for src in "$here"/runtime/*.c; do
        o="obj/rt_$(basename "${src%.c}").o"
        echo "build $o: rt $src"
        objs="$objs $o"
    done
    echo "build gunbound: link $objs"
    echo "default gunbound"
} > "$out/build.ninja"

echo "== compiling for $target with $cc ($opt, -j$jobs)"
t0=$(date +%s)
ninja -C "$out" -j "$jobs"
echo "== build took $(( $(date +%s) - t0 ))s -> $out/gunbound"
