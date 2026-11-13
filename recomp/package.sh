#!/usr/bin/env bash
# Package the aarch64 build as a port for ROCKNIX (Retroid Pocket 5).
#
#   recomp/package.sh [--no-build] [--login USER PASSWORD] [--broker HOST[:PORT]]
#
# Writes recomp/build/dist/gunbound-rocknix/ and gunbound-rocknix.tar.gz next to it:
#
#   GunBound.sh            launcher for the Ports menu  -> /storage/roms/ports/
#   gunbound/gunbound      the program (aarch64, debug information removed, symbols kept)
#   gunbound/gunbound.conf account and server address
#   gunbound/pad.cfg       the controller mapping, ready to edit
#   gunbound/README.txt    how to copy it to the device and run it
#   gunbound/BUILD-INFO.txt what the program needs from the system
#   gunbound/game/         empty: the user's own game files go here
#
# No game data goes into the package. The program itself is derived from the
# game's executable, so the package is for the owner of the game and is not
# committed or published.
#
#   --login USER PASSWORD  also write gunbound/token.txt, the session token for that
#                          account, so that the device needs no key (needs orig/Launcher.cs)
#   --broker HOST[:PORT]   preset the server address in gunbound.conf
#
# Environment: as for build.sh (RECOMP_EXE, AARCH64_CC, ...).
set -euo pipefail

here="$(cd "$(dirname "$0")" && pwd)"
root="$(cd "$here/.." && pwd)"
exe="${RECOMP_EXE:-$root/orig/GunBound.gme}"
cc="${AARCH64_CC:-/home/coleman/Developer/batocera.linux/output/h616/host/bin/aarch64-buildroot-linux-gnu-gcc}"
build=1
user=""
password=""
broker=""
while [ $# -gt 0 ]; do
    case "$1" in
    --no-build) build=0; shift ;;
    --login) user="$2"; password="$3"; shift 3 ;;
    --broker) broker="$2"; shift 2 ;;
    -h | --help) sed -n '2,23p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
    *) echo "package.sh: unknown option $1" >&2; exit 2 ;;
    esac
done

[ "$build" = 1 ] && "$here/build.sh" aarch64 >&2
bin="$here/build/aarch64/gunbound"
[ -x "$bin" ] || { echo "package.sh: $bin does not exist; run recomp/build.sh aarch64" >&2; exit 2; }
tool() { echo "${cc%gcc}$1"; }

dist="$here/build/dist"
pkg="$dist/gunbound-rocknix"
rm -rf "$pkg" "$dist/gunbound-rocknix.tar.gz"
mkdir -p "$pkg/gunbound/game" "$pkg/gunbound/save"

"$(tool strip)" -g -o "$pkg/gunbound/gunbound" "$bin"
chmod 755 "$pkg/gunbound/gunbound"
install -m 755 "$here/port/GunBound.sh" "$pkg/GunBound.sh"
install -m 644 "$here/port/README.txt" "$here/port/gunbound.conf" "$pkg/gunbound/"
[ -z "$broker" ] || sed -i "s|^GB_BROKER=.*|GB_BROKER=$broker|" "$pkg/gunbound/gunbound.conf"
cat > "$pkg/gunbound/game/PUT-YOUR-GAME-FILES-HERE.txt" <<'EOF'
Copy your own GunBound.gme, graphics.xfs, sound.xfs, avatar.xfs and the four
.dat files into this directory (and Launcher.cs, if the token is to be made on
the device). See ../README.txt.
EOF

# The program itself prints the mapping: under qemu when there is one, else from the host build.
sysroot="$("$cc" -print-sysroot)"
qemu=()
command -v qemu-aarch64 > /dev/null && qemu=(qemu-aarch64 -L "$sysroot")
if [ ${#qemu[@]} -gt 0 ]; then
    "${qemu[@]}" "$pkg/gunbound/gunbound" --print-pad-config > "$pkg/gunbound/pad.cfg"
elif [ -x "$here/build/host/gunbound" ]; then
    "$here/build/host/gunbound" --print-pad-config > "$pkg/gunbound/pad.cfg"
else
    echo "package.sh: neither qemu-aarch64 nor the host build is there to write pad.cfg; the defaults are built in" >&2
fi

if [ -n "$user" ]; then
    python3 "$here/tools/make_token.py" "$user" "$password" > "$pkg/gunbound/token.txt"
    sed -i "s|^GB_USER=.*|GB_USER=$user|" "$pkg/gunbound/gunbound.conf"
    # the packaged program must make the same token
    if [ ${#qemu[@]} -gt 0 ]; then
        t="$("${qemu[@]}" "$pkg/gunbound/gunbound" --login "$user" "$password" --login-key "$root/orig/Launcher.cs" --print-token)"
        [ "$t" = "$(cat "$pkg/gunbound/token.txt")" ] || { echo "package.sh: the program's --login disagrees with make_token.py" >&2; exit 1; }
    fi
fi

# ---- what the program needs from the system
readelf="$(tool readelf)"
needed="$("$readelf" -d "$bin" | sed -n 's/.*(NEEDED).*\[\(.*\)\]/\1/p' | tr '\n' ' ')"
interp="$("$readelf" -l "$bin" | sed -n 's/.*program interpreter: \(.*\)\]/\1/p')"
glibc="$("$readelf" -W --dyn-syms "$bin" | grep -o 'GLIBC_[0-9.]*' | sort -uV | tail -n 1)"
sdl_syms="$("$readelf" -W --dyn-syms "$bin" | grep -c ' UND SDL_' || true)"
sdl_built="$(sed -n 's/^#define SDL_\(MAJOR_VERSION\|MINOR_VERSION\|PATCHLEVEL\) *//p' "$sysroot/usr/include/SDL2/SDL_version.h" | tr '\n' '.' | sed 's/\.$//')"
{
    echo "GunBound recompiled client, port package for ROCKNIX"
    echo "built:            $(date -u +%Y-%m-%dT%H:%MZ) from commit $(git -C "$root" rev-parse --short HEAD 2>/dev/null || echo '?')"
    echo "program:          $(file -b "$pkg/gunbound/gunbound" | cut -d, -f1-2)"
    echo "loader:           $interp"
    echo "shared libraries: $needed"
    echo "C library:        needs glibc symbols up to $glibc (built with the compiler $("$cc" -dumpmachine) $("$cc" -dumpversion))"
    echo "SDL2:             $sdl_syms functions used; built against the headers of $sdl_built; the newest it calls are from SDL 2.0.14"
    echo "for the game:     GunBound.gme with SHA-256 $(sha256sum < "$exe" | cut -d' ' -f1)"
} > "$pkg/gunbound/BUILD-INFO.txt"

# ---- nothing of the game may be in the package
if find "$pkg" -iname '*.xfs' -o -iname '*.gme' -o -iname '*.dat' -o -iname 'Launcher.*' | grep -q .; then
    echo "package.sh: game files found in $pkg" >&2
    exit 1
fi
tar -C "$dist" -czf "$dist/gunbound-rocknix.tar.gz" gunbound-rocknix
echo "== $pkg"
cat "$pkg/gunbound/BUILD-INFO.txt"
echo "== $(du -h "$dist/gunbound-rocknix.tar.gz" | cut -f1) $dist/gunbound-rocknix.tar.gz"
