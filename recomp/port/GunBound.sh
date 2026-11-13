#!/bin/bash
# GunBound (recompiled client) as a ROCKNIX port.
#
# This file goes into /storage/roms/ports/ next to the directory gunbound/,
# which holds the program, its settings (gunbound/gunbound.conf) and, in
# gunbound/game/, your own copy of the game. See gunbound/README.txt.
#
# It can also be run by hand over ssh; anything given on the command line is
# passed to the program (try: GunBound.sh --frames 200 --dump-frame 150).

# PortMaster's environment, as the other ports use it: the controller mappings
# made in EmulationStation, the helpers that put the window on the screen.
XDG_DATA_HOME=${XDG_DATA_HOME:-$HOME/.local/share}
if [ -d "/opt/system/Tools/PortMaster/" ]; then
    controlfolder="/opt/system/Tools/PortMaster"
elif [ -d "/opt/tools/PortMaster/" ]; then
    controlfolder="/opt/tools/PortMaster"
elif [ -d "$XDG_DATA_HOME/PortMaster/" ]; then
    controlfolder="$XDG_DATA_HOME/PortMaster"
else
    controlfolder="/roms/ports/PortMaster"
fi
if [ -f "$controlfolder/control.txt" ]; then
    # shellcheck disable=SC1090,SC1091
    source "$controlfolder/control.txt"
    # shellcheck disable=SC1090
    [ -f "${controlfolder}/mod_${CFW_NAME}.txt" ] && source "${controlfolder}/mod_${CFW_NAME}.txt"
    get_controls
    # the program uses the system's own libraries, not the compatibility set
    unset LD_LIBRARY_PATH
elif [ -f /etc/profile ]; then
    # shellcheck disable=SC1091
    . /etc/profile
fi

here="$(cd "$(dirname "$0")" && pwd)"
port="$here/gunbound"
[ -d "$port" ] || port="$here" # run from inside the port directory
log="$port/log.txt"
cd "$port" || exit 1
exec > >(tee "$log") 2>&1
echo "== $(date) GunBound port starting in $port"

# ---- settings
GB_USER=player
GB_PASSWORD=1234
GB_BROKER=192.168.1.10:8372
GB_OPTIONS=""
# shellcheck disable=SC1091
[ -f "$port/gunbound.conf" ] && . "$port/gunbound.conf"

fail() {
    echo "GunBound: $*"
    echo "(this message is in $log)"
    sleep 5
    exit 1
}

# ---- the game's files, whatever the case of their names
find_file() { find "$1" -maxdepth 1 -iname "$2" 2>/dev/null | head -n 1; }
game="$port/game"
exe="$(find_file "$game" GunBound.gme)"
[ -n "$exe" ] || fail "no GunBound.gme in $game: copy your game directory's contents there"
for f in graphics.xfs sound.xfs avatar.xfs; do
    [ -n "$(find_file "$game" "$f")" ] || fail "$f is missing from $game"
done
mkdir -p "$port/save"

# ---- the program: it must be executable, which a FAT or exFAT card does not allow
bin="$port/gunbound"
[ -f "$bin" ] || fail "the program $bin is missing"
if ! chmod +x "$bin" 2>/dev/null || [ ! -x "$bin" ]; then
    mkdir -p /tmp/gunbound-port
    cp "$bin" /tmp/gunbound-port/gunbound && chmod +x /tmp/gunbound-port/gunbound || fail "cannot make the program executable"
    bin=/tmp/gunbound-port/gunbound
    echo "== running a copy of the program from $bin (the port directory does not allow execution)"
fi
run=("$bin")
if [ ! -e /lib/ld-linux-aarch64.so.1 ]; then
    for ld in /usr/lib/ld-linux-aarch64.so.1 /lib64/ld-linux-aarch64.so.1; do
        [ -e "$ld" ] && { run=("$ld" "$bin"); break; }
    done
fi

# GB_RUNNER: something to run the program under (an emulator on a PC, a debugger)
# shellcheck disable=SC2206
[ -z "${GB_RUNNER:-}" ] || run=($GB_RUNNER "$bin")

# ---- the account: a ready token, or the name and password with the launcher's key
login=()
if [ -f "$port/token.txt" ]; then
    login=(--cmdline "$(tr -d ' \r\n' < "$port/token.txt")")
else
    key="$(find_file "$port" launcher.key)"
    [ -n "$key" ] || key="$(find_file "$game" Launcher.cs)"
    [ -n "$key" ] || fail "no token.txt or launcher.key in $port and no Launcher.cs in $game (see README.txt, 'The account')"
    login=(--login "$GB_USER" "$GB_PASSWORD" --login-key "$key")
fi

# ---- controller mappings, when PortMaster did not provide them
if [ -z "${SDL_GAMECONTROLLERCONFIG_FILE:-}" ]; then
    for db in /storage/.config/SDL-GameControllerDB/gamecontrollerdb.txt /usr/config/SDL-GameControllerDB/gamecontrollerdb.txt; do
        [ -f "$db" ] && { export SDL_GAMECONTROLLERCONFIG_FILE="$db"; break; }
    done
fi

# ---- the screen: sway's Wayland display, also when started over ssh
export SDL_VIDEODRIVER="${SDL_VIDEODRIVER:-wayland}"
export XDG_RUNTIME_DIR="${XDG_RUNTIME_DIR:-/var/run/0-runtime-dir}"
export WAYLAND_DISPLAY="${WAYLAND_DISPLAY:-wayland-1}"
unset DISPLAY
type pm_platform_helper > /dev/null 2>&1 && pm_platform_helper "$bin"

pad=()
[ -f "$port/pad.cfg" ] && pad=(--pad-config "$port/pad.cfg")

echo "== ${run[*]} as $GB_USER on $GB_BROKER"
# shellcheck disable=SC2086
"${run[@]}" --exe "$exe" --gamedir "$game" --savedir "$port/save" "${login[@]}" --broker "$GB_BROKER" \
    --fullscreen --scale-mode fit "${pad[@]}" $GB_OPTIONS "$@"
status=$?
echo "== exit status $status"
type pm_finish > /dev/null 2>&1 && pm_finish
exit $status
