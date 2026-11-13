#!/usr/bin/env bash
# Whole-program check: run the recompiled game headless on a virtual clock, dump
# a few frames and compare the host build's with the aarch64 build's (under
# qemu-aarch64). With the virtual clock a frame depends only on the code that
# ran, so the two builds must agree pixel for pixel.
#
#   recomp/test/frames.sh [frame numbers...]        (default: 1 20 60 150)
#
# Environment:
#   RECOMP_EXE   the original executable (default: orig/GunBound.gme)
#   GAMEDIR      the game's files (default: the directory of RECOMP_EXE)
#   TOKEN        the 96-character session token (default: made by tools/make_token.py)
#
# Needs recomp/build/host/gunbound; compares with recomp/build/aarch64/gunbound
# when that exists. Nothing is written outside recomp/build.
set -euo pipefail

here="$(cd "$(dirname "$0")" && pwd)"
recomp="$(cd "$here/.." && pwd)"
root="$(cd "$recomp/.." && pwd)"
exe="${RECOMP_EXE:-$root/orig/GunBound.gme}"
gamedir="${GAMEDIR:-$(dirname "$exe")}"
token="${TOKEN:-$(python3 "$recomp/tools/make_token.py" recomp)}"
out="$recomp/build/frames"
frames=("$@")
[ ${#frames[@]} -gt 0 ] || frames=(1 20 60 150)
mkdir -p "$out"

run() { # target frame
    local target="$1" n="$2" cmd=("$recomp/build/$1/gunbound")
    if [ "$target" = aarch64 ]; then
        local cc="${AARCH64_CC:-/home/coleman/Developer/batocera.linux/output/h616/host/bin/aarch64-buildroot-linux-gnu-gcc}"
        cmd=(qemu-aarch64 -L "$("$cc" -print-sysroot)" "${cmd[@]}")
    fi
    rm -rf "$out/save-$target"
    mkdir -p "$out/save-$target"
    "${cmd[@]}" --exe "$exe" --gamedir "$gamedir" --savedir "$out/save-$target" --headless --virtual-clock \
        --cmdline "$token" --dump-frame "$n" --dump-path "$out/$target-$n.png" --frames "$n" \
        > "$out/$target-$n.log" 2>&1 || { echo "FAIL  $target: exit status $? at frame $n (see $out/$target-$n.log)"; return 1; }
    [ -f "$out/$target-$n.png" ] || { echo "FAIL  $target: frame $n was not presented (see $out/$target-$n.log)"; return 1; }
}

[ -x "$recomp/build/host/gunbound" ] || { echo "build the host target first: recomp/build.sh host" >&2; exit 2; }
status=0
for n in "${frames[@]}"; do
    rm -f "$out/host-$n.png" "$out/aarch64-$n.png"
    run host "$n" || { status=1; continue; }
    sum="$(sha256sum < "$out/host-$n.png" | cut -c1-16)"
    if [ -x "$recomp/build/aarch64/gunbound" ]; then
        run aarch64 "$n" || { status=1; continue; }
        if cmp -s "$out/host-$n.png" "$out/aarch64-$n.png"; then
            echo "PASS  frame $n: host and aarch64 agree ($sum)"
        else
            echo "FAIL  frame $n: host and aarch64 differ ($out/host-$n.png, $out/aarch64-$n.png)"
            status=1
        fi
    else
        echo "ok    frame $n: host only ($sum)"
    fi
done
exit $status
