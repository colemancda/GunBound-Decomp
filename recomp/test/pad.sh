#!/usr/bin/env bash
# Game controller and touch input, without a controller, a screen or a server.
#
#   recomp/test/pad.sh [host|aarch64 ...]        (default: every build that exists)
#
# The game is run on the virtual clock to its world-list screen (which shows
# "Access time has expired" when there is no server) while an input script
# moves the left stick, presses buttons, unplugs and plugs the controller and
# touches the screen. Each build is driven two ways:
#
#   direct   headless; the script's controller commands enter just below SDL
#   sdl      a window on SDL's dummy video driver, 1920x1080, and --pad-virtual:
#            the commands drive an SDL virtual joystick and SDL touch events, so
#            SDL's game controller mapping, its events, hot-plugging and the
#            scaling rectangle are all on the path
#
# and judged from --trace-input (the messages the game's window procedures
# received and the keys its DirectInput keyboard read) and from a dumped frame
# (the cursor the game draws must be where the stick moved the pointer).
# The aarch64 build runs under qemu-aarch64.
#
# Environment: RECOMP_EXE, GAMEDIR, TOKEN as for frames.sh. Output: recomp/build/pad.
set -uo pipefail

here="$(cd "$(dirname "$0")" && pwd)"
recomp="$(cd "$here/.." && pwd)"
root="$(cd "$recomp/.." && pwd)"
exe="${RECOMP_EXE:-$root/orig/GunBound.gme}"
gamedir="${GAMEDIR:-$(dirname "$exe")}"
token="${TOKEN:-$(python3 "$recomp/tools/make_token.py" recomp)}"
out="$recomp/build/pad"
targets=("$@")
if [ ${#targets[@]} -eq 0 ]; then
    for t in host aarch64; do [ -x "$recomp/build/$t/gunbound" ] && targets+=("$t"); done
fi
mkdir -p "$out"
status=0

# Stick right for ten frames, A, the right trigger, a press while unplugged, B
# after plugging in again, a finger across the screen, the quit combination.
script="100:stick 100 0;110:stick 0 0;115:ptap a;120:pdown rt;123:pup rt;126:unplug;128:pdown y;129:pup y"
script="$script;131:plug;136:ptap b;142:tdown 125 0;145:tmove 500 500;148:tup;160:pdown back;161:pdown start"

run() { # target name options...
    local target="$1" name="$2" cmd=("$recomp/build/$1/gunbound")
    shift 2
    if [ "$target" = aarch64 ]; then
        local cc="${AARCH64_CC:-/home/coleman/Developer/batocera.linux/output/h616/host/bin/aarch64-buildroot-linux-gnu-gcc}"
        cmd=(qemu-aarch64 -L "$("$cc" -print-sysroot)" "${cmd[@]}")
    fi
    rm -rf "$out/save-$name"
    mkdir -p "$out/save-$name"
    SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy timeout 300 "${cmd[@]}" --exe "$exe" --gamedir "$gamedir" \
        --savedir "$out/save-$name" --virtual-clock --cmdline "$token" --trace-input --frames 400 \
        --dump-frame 113 --dump-path "$out/$name-%d.png" "$@" > "$out/$name.log" 2>&1
}

check() { # description command...
    local what="$1"
    shift
    if "$@"; then echo "PASS  $what"; else echo "FAIL  $what"; status=1; fi
}
# line number of the first match of a pattern after a given line, 0 if none
after() {
    local n
    n="$(tail -n "+$(( $1 + 1 ))" "$3" | grep -n -m1 -E "$2" | cut -d: -f1)"
    echo "$(( ${n:+$1 + n} + 0 ))"
}
in_order() { # log pattern...: each pattern matches after the previous one's match
    local log="$1" at=0
    shift
    for pat in "$@"; do
        at="$(after "$at" "$pat" "$log")"
        [ "$at" != 0 ] || return 1
    done
}

judge() { # name mode
    local name="$1" mode="$2" log="$out/$1.log"
    check "$name: ran until the quit combination ended it" grep -q "controller: back+start, closing the game" "$log"
    # the pointer: the last position the main window was told before A was pressed
    local a_at pos x y x0
    a_at="$(after 0 '^\[pad\] a down' "$log")"
    pos="$(awk -v to="$a_at" 'NR < to && /^\[msg\] 0200 / { split($6, p, ","); x = p[1]; y = p[2]; if (!n++) first = x } END { print first, x, y }' "$log")"
    read -r x0 x y <<< "$pos"
    check "$name: the left stick moved the pointer to the right (x ${x0:-?} -> ${x:-?}, y ${y:-?})" [ "${x:-0}" -ge "$(( ${x0:-999} + 200 ))" ]
    check "$name: the cursor the game draws is there ($(python3 "$here/cursor.py" "$out/$3-113.png" "$out/$name-113.png" "${x:-0}" "${y:-0}" 2>&1))" \
        eval "python3 '$here/cursor.py' '$out/$3-113.png' '$out/$name-113.png' ${x:-0} ${y:-0} > /dev/null 2>&1"
    check "$name: A reached the window procedure as the space bar: key down, character, then key up on release" \
        in_order "$log" '^\[pad\] a down' '^\[msg\] 0100 wparam 20 ' '^\[msg\] 0102 wparam 20 ' \
        '^\[pad\] a up' '^\[msg\] 0101 wparam 20 '
    # the game reads its DirectInput keyboard on a thread of its own
    check "$name: the game's DirectInput keyboard read the space bar going down and coming up" \
        in_order "$log" '^\[pad\] a down' '^\[dinput\] key 39 down' '^\[dinput\] key 39 up'
    check "$name: the right trigger is the left mouse button" \
        in_order "$log" '^\[pad\] rt down' '^\[msg\] 0201 ' '^\[pad\] rt up' '^\[msg\] 0202 '
    check "$name: B is Escape after plugging in again" in_order "$log" '^\[pad\] b down' '^\[msg\] 0100 wparam 1b '
    # the finger: 1920x1080 with a 1440x1080 picture at x 240, so 12.5% of the width is the picture's left edge
    check "$name: a finger presses the left button where it lands and releases where it lifts" \
        in_order "$log" '^\[touch\] down 0 0' '^\[msg\] 0201 wparam 1 at 0,0 ' '^\[touch\] move 400 300' '^\[msg\] 0202 wparam 0 at 400,300 '
    if [ "$mode" = sdl ]; then
        check "$name: a button pressed while the controller is unplugged does nothing" eval "! grep -q '^.msg. 020[45] ' '$log'"
        check "$name: SDL announced the virtual controller, its removal and its return" \
            in_order "$log" 'controller connected: ' 'controller disconnected: ' 'controller connected: '
        check "$name: the picture is 1440x1080 in a 1920x1080 window" grep -q "picture 1440x1080 at 240,0" "$log"
    fi
}

for t in "${targets[@]}"; do
    [ -x "$recomp/build/$t/gunbound" ] || { echo "FAIL  $t: not built (recomp/build.sh $t)"; status=1; continue; }
    run "$t" "$t-base" --headless --frames 114
    [ -f "$out/$t-base-113.png" ] || { echo "FAIL  $t: the run without input did not reach frame 113 (see $out/$t-base.log)"; status=1; continue; }
    # headless there is no window: the finger's thousandths are of the guest screen
    run "$t" "$t-direct" --headless --input "${script//tdown 125 0/tdown 0 0}"
    judge "$t-direct" direct "$t-base"
    run "$t" "$t-sdl" --window-size 1920x1080 --pad-virtual --input "$script"
    if grep -q "SDL dummy window" "$out/$t-sdl.log"; then
        judge "$t-sdl" sdl "$t-base"
    else
        echo "skip  $t-sdl: no SDL window on this build or machine (see $out/$t-sdl.log)"
    fi
done
echo "logs and frames are in $out"
exit $status
