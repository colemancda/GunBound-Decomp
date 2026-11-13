#!/usr/bin/env bash
# Build the statically recompiled client.
#
#   recomp/build.sh [host|aarch64|macos|ios|iossim] [--relift]
#
# host     native build with the system compiler      -> recomp/build/host/gunbound
# aarch64  cross build for Linux/arm64 (glibc)         -> recomp/build/aarch64/gunbound
# macos    native build on a Mac with Xcode's clang    -> recomp/build/macos/gunbound
#          (arm64 by default, MACOS_ARCH=x86_64 for Intel; SDL2 from sdl2-config,
#          e.g. Homebrew's)
# ios      iOS devices, arm64                          -> recomp/build/ios/gunbound
# iossim   the iOS simulator on an Apple Silicon Mac   -> recomp/build/iossim/gunbound
#          Both link SDL2 from recomp/ios/build_sdl.sh when it has been built, and
#          are headless (RT_NO_SDL) otherwise; the .app is made by recomp/ios/build_ios.sh.
#          IOS_MIN sets the deployment target (default 15.0).
#
# Environment:
#   RECOMP_EXE   original executable to lift (default: orig/GunBound.gme)
#   AARCH64_CC   cross compiler (default: the batocera h616 buildroot gcc)
#   JOBS         parallel compile jobs (default: the number of CPUs)
#   OPT          optimisation level for the lifted code (default -O1)
#   EXTRA_CFLAGS extra compiler flags for everything (e.g. -DRT_DYNAMIC_BASE)
#   LIFT_FLAGS   extra lifter flags (e.g. --no-flag-liveness)
#   NO_SDL       1 = build without SDL2 (headless only)
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
jobs="${JOBS:-$( (nproc || sysctl -n hw.ncpu) 2>/dev/null || echo 4)}"
opt="${OPT:--O1}"

case "$target" in
host)
    cc="${CC:-gcc}"
    ;;
aarch64)
    cc="${AARCH64_CC:-/home/coleman/Developer/batocera.linux/output/h616/host/bin/aarch64-buildroot-linux-gnu-gcc}"
    ;;
macos)
    # xcrun's clang, not whichever clang is first on PATH (a swiftly or Homebrew
    # clang has no SDK of its own)
    cc="$(xcrun -f clang)"
    target_flags="-arch ${MACOS_ARCH:-arm64} -isysroot $(xcrun --sdk macosx --show-sdk-path) -mmacosx-version-min=${MACOS_MIN:-13.0}"
    target_libs="-framework Foundation -lobjc" # runtime/darwin.c
    ;;
ios | iossim)
    cc="$(xcrun -f clang)"
    if [ "$target" = ios ]; then sdk=iphoneos triple="arm64-apple-ios${IOS_MIN:-15.0}"
    else sdk=iphonesimulator triple="arm64-apple-ios${IOS_MIN:-15.0}-simulator"; fi
    target_flags="-target $triple -isysroot $(xcrun --sdk $sdk --show-sdk-path)"
    target_libs="-framework Foundation -lobjc"
    sdl_ios="$here/build/deps/sdl-ios/$sdk"
    if [ "${NO_SDL:-0}" != 1 ] && [ ! -f "$sdl_ios/lib/libSDL2.a" ]; then
        echo "note: no SDL2 for $sdk in $sdl_ios (recomp/ios/build_sdl.sh); building headless" >&2
        NO_SDL=1
    fi
    ;;
*)
    echo "usage: $0 [host|aarch64|macos|ios|iossim] [--relift]" >&2
    exit 2
    ;;
esac
command -v "$cc" >/dev/null || { echo "compiler not found: $cc" >&2; exit 2; }

# SDL2: the host's through sdl2-config, the cross build's from the compiler's sysroot.
# NO_SDL=1 builds a headless-only program.
if [ "${NO_SDL:-0}" = 1 ]; then
    sdl_cflags="-DRT_NO_SDL"
    sdl_libs=""
elif [ "$target" = ios ] || [ "$target" = iossim ]; then
    # SDL's UIKit code owns main() and calls SDL_main: the runtime's main is
    # renamed and recomp/ios/ios_main.c (in the app) builds its arguments
    sdl_cflags="-I$sdl_ios/include/SDL2"
    ios_main=1
    sdl_libs="$sdl_ios/lib/libSDL2main.a $sdl_ios/lib/libSDL2.a -framework AVFoundation -framework AudioToolbox -framework CoreAudio -framework CoreBluetooth -framework CoreGraphics -framework CoreHaptics -framework CoreMotion -framework GameController -framework Metal -framework OpenGLES -framework QuartzCore -framework UIKit -liconv"
elif [ "$target" = host ] || [ "$target" = macos ]; then
    sdl_cflags="$(sdl2-config --cflags)"
    sdl_libs="$(sdl2-config --libs)"
else
    sdl_cflags="-I$("$cc" -print-sysroot)/usr/include/SDL2 -D_REENTRANT"
    sdl_libs="-lSDL2"
fi
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
cflags_common="${target_flags:-} -std=gnu11 -pthread -fno-strict-aliasing -fwrapv -fno-stack-protector -I$here/runtime -I$gen ${EXTRA_CFLAGS:-}"
{
    echo "cc = $cc"
    echo "gen_cflags = $opt -foptimize-sibling-calls $cflags_common -w"
    echo "rt_cflags = -O2 -g $cflags_common $sdl_cflags -Wall -Wextra -Wno-unused-parameter"
    echo "rule gen"
    echo "  command = \$cc \$gen_cflags -c \$in -o \$out"
    echo "  description = CC \$out"
    echo "rule rt"
    echo "  command = \$cc \$rt_cflags \$rt_extra -MMD -MF \$out.d -c \$in -o \$out"
    echo "  depfile = \$out.d"
    echo "  description = CC \$out"
    echo "rule link"
    echo "  command = \$cc ${target_flags:-} -o \$out \$in -lm -pthread $sdl_libs ${target_libs:-}"
    echo "  description = LINK \$out"
    objs=""
    for src in "$gen"/chunk_*.c "$gen/tables.c"; do
        o="obj/$(basename "${src%.c}").o"
        # the lifted code is written against cpu.h alone; only tables.c sees rt.h
        deps="$here/runtime/cpu.h $gen/funcs.h"
        [ "$(basename "$src")" = tables.c ] && deps="$deps $here/runtime/rt.h"
        echo "build $o: gen $src | $deps"
        objs="$objs $o"
    done
    for src in "$here"/runtime/*.c; do
        o="obj/rt_$(basename "${src%.c}").o"
        echo "build $o: rt $src"
        [ "${ios_main:-0}" = 1 ] && [ "$(basename "$src")" = main.c ] && echo "  rt_extra = -Dmain=rt_main"
        objs="$objs $o"
    done
    if [ "${ios_main:-0}" = 1 ]; then
        echo "build obj/ios_main.o: rt $here/ios/ios_main.c"
        objs="$objs obj/ios_main.o"
    fi
    echo "build gunbound: link $objs"
    echo "default gunbound"
} > "$out/build.ninja"

echo "== compiling for $target with $cc ($opt, -j$jobs)"
t0=$(date +%s)
ninja -C "$out" -j "$jobs"
echo "== build took $(( $(date +%s) - t0 ))s -> $out/gunbound"
