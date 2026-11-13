#!/usr/bin/env bash
# Run the recompiled GunBound client in a window: build it if needed, make the
# session token for an account, point the game at a server and start it.
#
#   recomp/run.sh [options] [-- options for the game binary...]
#
#   --user NAME          account name (default: admin)
#   --password PW        its password (default: 1234)
#   --gamedir DIR        the game's data files: graphics.xfs, sound.xfs, avatar.xfs and the
#                        four .dat files (default: $GUNBOUND_GAMEDIR, then gamedir/ in the
#                        repository, then the directory of the executable)
#   --broker HOST[:PORT] the server that lists the worlds (default: 127.0.0.1:8372)
#   --server             also start a local broker and world server from the GunBound
#                        server package (Swift) and stop them when the game exits.
#                        The package is $GUNBOUND_SERVER (default: ~/Developer/GunBound);
#                        only its .build directory is written to.
#   --instance N         run as the Nth instance on this machine (1, 2, ...): each gets its
#                        own save directory and its own loopback address 127.0.0.(N+1), so
#                        that two clients can meet in one room. Use it on every instance.
#   --fullscreen         start full screen (Alt+Enter switches at any time)
#   --scale N, --scale-mode fit|integer|stretch, --filter sharp|nearest|linear
#                        window size and scaling, see recomp/README.md
#   --headless           no window (for scripted runs; combine with -- --frames N ...)
#   --target host|aarch64  which build to run (default: host; aarch64 runs under qemu)
#   --no-build           do not rebuild first
#
# Environment: RECOMP_EXE (default orig/GunBound.gme), GUNBOUND_GAMEDIR, GUNBOUND_SERVER.
# Saves, the registry file and the server's state and logs are kept under recomp/build/.
set -euo pipefail

here="$(cd "$(dirname "$0")" && pwd)"
root="$(cd "$here/.." && pwd)"
exe="${RECOMP_EXE:-$root/orig/GunBound.gme}"
user=admin
password=1234
gamedir="${GUNBOUND_GAMEDIR:-}"
broker=127.0.0.1:8372
server=0
instance=0
target=host
build=1
pass=()

while [ $# -gt 0 ]; do
    case "$1" in
    --user) user="$2"; shift 2 ;;
    --password) password="$2"; shift 2 ;;
    --gamedir) gamedir="$2"; shift 2 ;;
    --broker) broker="$2"; shift 2 ;;
    --server) server=1; shift ;;
    --instance) instance="$2"; shift 2 ;;
    --target) target="$2"; shift 2 ;;
    --no-build) build=0; shift ;;
    --fullscreen | --headless) pass+=("$1"); shift ;;
    --scale | --scale-mode | --filter) pass+=("$1" "$2"); shift 2 ;;
    -h | --help) sed -n '2,28p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
    --) shift; pass+=("$@"); break ;;
    *) echo "run.sh: unknown option $1 (options for the game binary go after --)" >&2; exit 2 ;;
    esac
done

[ -f "$exe" ] || { echo "run.sh: original executable not found: $exe (set RECOMP_EXE)" >&2; exit 2; }
if [ -z "$gamedir" ]; then
    for d in "$root/gamedir" "$(dirname "$exe")"; do
        [ -f "$d/sound.xfs" ] && [ -f "$d/avatar.xfs" ] && { gamedir="$d"; break; }
    done
fi
[ -n "$gamedir" ] && [ -f "$gamedir/graphics.xfs" ] ||
    { echo "run.sh: the game's data files were not found; pass --gamedir DIR or set GUNBOUND_GAMEDIR" >&2; exit 2; }

if [ "$build" = 1 ]; then
    "$here/build.sh" "$target" >&2
fi
bin="$here/build/$target/gunbound"
[ -x "$bin" ] || { echo "run.sh: $bin does not exist; run recomp/build.sh $target" >&2; exit 2; }
cmd=("$bin")
if [ "$target" = aarch64 ]; then
    cc="${AARCH64_CC:-/home/coleman/Developer/batocera.linux/output/h616/host/bin/aarch64-buildroot-linux-gnu-gcc}"
    cmd=(qemu-aarch64 -L "$("$cc" -print-sysroot)" "$bin")
fi

token="$(python3 "$here/tools/make_token.py" "$user" "$password")"
save="$here/build/save/$user"
if [ "$instance" != 0 ]; then
    save="$save-$instance"
    pass+=(--local-address "127.0.0.$((instance + 1))")
fi
mkdir -p "$save"

# ---- the local server (--server)
pids=()
cleanup() {
    for p in "${pids[@]:-}"; do [ -n "$p" ] && kill "$p" 2>/dev/null || true; done
}
trap cleanup EXIT
listening() { (exec 3<>"/dev/tcp/127.0.0.1/$1") 2>/dev/null; }
if [ "$server" = 1 ]; then
    pkg="${GUNBOUND_SERVER:-$HOME/Developer/GunBound}"
    sdir="$here/build/server"
    mkdir -p "$sdir"
    [ -f "$pkg/Package.swift" ] || { echo "run.sh: no server package at $pkg (set GUNBOUND_SERVER)" >&2; exit 2; }
    sbin="$pkg/.build/debug/GunBoundServer"
    if [ ! -x "$sbin" ]; then
        echo "== building the server in $pkg" >&2
        swift build --package-path "$pkg" --product GunBoundServer >&2
    fi
    cat > "$sdir/servers.json" <<EOF
[ { "name": "GunBound World", "description": "Local world server", "address": "127.0.0.1", "port": 8370,
    "utilization": 0, "capacity": 100, "enabled": true } ]
EOF
    if listening 8370; then
        echo "== a world server is already listening on 127.0.0.1:8370; using it" >&2
    else
        "$sbin" world --address 127.0.0.1 --port 8370 --path "$sdir/world-state.json" > "$sdir/world.log" 2>&1 &
        pids+=($!)
    fi
    if listening 8372; then
        echo "== a broker is already listening on 127.0.0.1:8372; using it" >&2
    else
        "$sbin" broker --path "$sdir/servers.json" --address 127.0.0.1 --port 8372 > "$sdir/broker.log" 2>&1 &
        pids+=($!)
    fi
    for _ in $(seq 50); do
        listening 8370 && listening 8372 && break
        sleep 0.1
    done
    listening 8372 || { echo "run.sh: the server did not start; see $sdir/world.log and $sdir/broker.log" >&2; exit 2; }
    broker=127.0.0.1:8372
    echo "== server running (logs in $sdir); accounts are created on first login with password 1234" >&2
fi

echo "== $user on $broker, data $gamedir, saves $save" >&2
status=0
"${cmd[@]}" --exe "$exe" --gamedir "$gamedir" --savedir "$save" --cmdline "$token" --broker "$broker" \
    "${pass[@]}" || status=$?
exit $status
