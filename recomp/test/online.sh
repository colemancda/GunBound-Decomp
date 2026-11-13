#!/usr/bin/env bash
# Whole-program check against a running server: two headless instances of the
# host build log in, one creates a room, the other joins it and readies, the
# first starts the game and both fire a shot. The stages are judged from the
# packets each client received (--trace-net); frames are dumped for a look.
#
#   recomp/test/online.sh [broker HOST:PORT]        (default 127.0.0.1:8372)
#
# Environment:
#   RECOMP_EXE   the original executable (default: orig/GunBound.gme)
#   GAMEDIR      the game's files (default: the directory of RECOMP_EXE)
#   TARGET       which build to run (default: host; macos on a Mac)
#   ADDR1 ADDR2  the two instances' local addresses (default 127.0.0.2 and
#                127.0.0.3; a Mac has only 127.0.0.1 on its loopback interface
#                until aliases are added, see below). Never 127.0.0.1: what an
#                instance sends there is meant for itself.
#   PAD=1        play with the game controller instead of the keyboard: the space
#                in the room's title and the shots are the controller's A button
#                (the input script's ptap, pdown and pup commands)
#
# The server must be running (recomp/run.sh --server starts one, as does
# `swift run GunBoundServer` in the server package) and must create accounts on
# first login with the password 1234. The two instances use the addresses
# ADDR1 and ADDR2 (below). Takes about 90 seconds of real time: the
# game runs at its own 20 frames per second. Output goes to recomp/build/online.
set -uo pipefail

here="$(cd "$(dirname "$0")" && pwd)"
recomp="$(cd "$here/.." && pwd)"
root="$(cd "$recomp/.." && pwd)"
exe="${RECOMP_EXE:-$root/orig/GunBound.gme}"
gamedir="${GAMEDIR:-$(dirname "$exe")}"
broker="${1:-127.0.0.1:8372}"
out="$recomp/build/online"
target="${TARGET:-host}"
addr1="${ADDR1:-127.0.0.2}" addr2="${ADDR2:-127.0.0.3}"
if [ "$(uname -s)" = Darwin ]; then
    target="${TARGET:-macos}"
    for a in "$addr1" "$addr2"; do
        ifconfig | grep -q "inet ${a//./\\.} " && continue
        echo "online.sh: $a is not an address of this Mac. Add the two loopback aliases" >&2
        echo "  (sudo ifconfig lo0 alias 127.0.0.2 up; sudo ifconfig lo0 alias 127.0.0.3 up)" >&2
        echo "or set ADDR1 and ADDR2 to two addresses this Mac has. Not 127.0.0.1: an" >&2
        echo "instance's datagrams to 127.0.0.1 are its own and go to its own address." >&2
        exit 2
    done
fi
bin="$recomp/build/$target/gunbound"
frames=1750
[ -x "$bin" ] || { echo "build the $target target first: recomp/build.sh $target" >&2; exit 2; }
rm -rf "$out"
mkdir -p "$out"

# Screen positions: world list row, SERVER, CREATE, the dialog's Create, START/READY,
# View All, the first room card, JOIN.
host_script="260:click 125 72;275:click 462 573;380:click 594 573;420:text Recomp room;440:click 410 370"
host_script="$host_script;900:click 706 573;1150:keydown 20 39;1175:keyup 20 39;1500:keydown 20 39;1530:keyup 20 39"
guest_script="260:click 125 72;275:click 462 573;600:click 86 261;650:click 130 85;680:click 706 573"
guest_script="$guest_script;800:click 706 573;1150:keydown 20 39;1175:keyup 20 39;1500:keydown 20 39;1530:keyup 20 39"

if [ "${PAD:-0}" = 1 ]; then
    host_script="${host_script//text Recomp room/text Recomp;+3:ptap a;+3:text room}"
    host_script="${host_script//keydown 20 39/pdown a}"; host_script="${host_script//keyup 20 39/pup a}"
    guest_script="${guest_script//keydown 20 39/pdown a}"; guest_script="${guest_script//keyup 20 39/pup a}"
fi

run() { # name user address script
    local token
    token="$(python3 "$recomp/tools/make_token.py" "$2" 1234)"
    mkdir -p "$out/save-$1"
    timeout 300 "$bin" --exe "$exe" --gamedir "$gamedir" --savedir "$out/save-$1" --headless --cmdline "$token" \
        --broker "$broker" --local-address "$3" --trace-net --input "$4" --frames "$frames" \
        --trace-input --dump-frame 350,560,860,1000,1145,1172,1200,1260,1700 --dump-path "$out/$1-%d.png" > "$out/$1.log" 2>&1
}
run host admin "$addr1" "$host_script" &
p1=$!
run guest tester "$addr2" "$guest_script" &
p2=$!
wait $p1; s1=$?
wait $p2; s2=$?

# A received packet's opcode is the third little-endian word of what recv logged.
got() { grep -Eq "^\[net\] recv [0-9a-f]+ [0-9]+ bytes: [0-9a-f]{2} [0-9a-f]{2} [0-9a-f]{2} [0-9a-f]{2} $2( |\$)" "$out/$1.log"; }
sent() { grep -Eq "^\[net\] send [0-9a-f]+ [0-9]+ bytes: [0-9a-f]{2} [0-9a-f]{2} [0-9a-f]{2} [0-9a-f]{2} $2( |\$)" "$out/$1.log"; }
datagrams() { grep -c "^\[net\] recvfrom [0-9a-f]* $2:" "$out/$1.log"; }
status=0
check() { # description condition...
    local what="$1"; shift
    if "$@"; then echo "PASS  $what"; else echo "FAIL  $what"; status=1; fi
}
both() { got host "$1" && got guest "$1"; }
check "both instances ran to frame $frames (exit status $s1 and $s2)" [ "$s1" = 0 -a "$s2" = 0 ]
check "world list received from the broker (opcode 1102)" both "02 11"
check "logged in (1012)" both "12 10"
check "joined a channel (2001)" both "01 20"
check "room created by the first instance (2121)" got host "21 21"
check "room joined by the second instance (2111)" got guest "11 21"
check "the first instance was told of the second (3010)" got host "10 30"
check "game started (3432)" both "32 34"
check "every datagram reached its peer: none was relayed through the server (4500)" eval '! sent host "00 45" && ! sent guest "00 45"'
n1=$(datagrams host "$addr2"); n2=$(datagrams guest "$addr1")
check "peer-to-peer traffic in both directions ($n1 and $n2 datagrams)" [ "$n1" -ge 10 -a "$n2" -ge 10 ]
# The room's title as the first instance sent it (opcode 2120), with its space.
check "the room was created with the title \"Recomp room\"" grep -Eq "^\[net\] send .* 20 21 .*52 65 63 6f 6d 70 20 72 6f 6f 6d" "$out/host.log"
# The power bar (red, at the bottom of the screen) while the fire key is held: empty
# before the press at frame 1150, filling at 1172 on the instance whose turn it is.
red() { python3 "$here/cursor.py" --red "$out/$1-$2.png" 245 566 645 592 2>/dev/null || echo 0; }
b0=$(( $(red host 1145) + $(red guest 1145) )); b1h=$(red host 1172); b1g=$(red guest 1172)
check "the power bar charged while the fire key was held (red pixels: $b0 before; $b1h and $b1g during)" \
    [ "$b0" -lt 50 -a "$(( b1h > b1g ? b1h : b1g ))" -ge 1000 ]
if [ "${PAD:-0}" = 1 ]; then
    check "the fire key was the controller's A button, read by the game's DirectInput keyboard" \
        eval 'grep -q "^\[pad\] a down" "$out/host.log" && grep -q "^\[dinput\] key 39 down" "$out/host.log" && ! grep -q "keydown 20 39" "$out/host.log"'
fi
echo "frames and logs are in $out"
exit $status
