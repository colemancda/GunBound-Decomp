#!/usr/bin/env bash
# One command: capture the live client's state as a timestamped screenshot + JSON.
# Attaches read-only via the winedbg gdb stub, writes gameState + view hierarchy
# with gbstate.py, and grabs the game window. Clean detach; safe (no breakpoints).
#
# Usage: capture-state.sh [OUTDIR] [PORT]
#   OUTDIR  where to write gb-view_<timestamp>.{png,json}  (default: current dir)
#   PORT    gdb-stub port (default 12345)
#
# Writes: <OUTDIR>/gb-view_YYYY-MM-DD_HHMMSS.png  and  .json
set -euo pipefail

OUTDIR="${1:-$PWD}"
PORT="${2:-12345}"
TS="$(date +%Y-%m-%d_%H%M%S)"
PNG="$OUTDIR/gb-view_$TS.png"
JSON="$OUTDIR/gb-view_$TS.json"

HERE="$(cd "$(dirname "$0")" && pwd)"
GH=/home/coleman/Downloads/ghidra_11.0.1_PUBLIC
export PYTHONPATH="$GH/Ghidra/Debug/Debugger-agent-gdb/pypkg/src:$GH/Ghidra/Debug/Debugger-rmi-trace/pypkg/src"
export DISPLAY="${DISPLAY:-:0}" XDG_RUNTIME_DIR="${XDG_RUNTIME_DIR:-/run/user/$(id -u)}"

mkdir -p "$OUTDIR"

# 1) screenshot (best-effort — the game window under the Wine virtual desktop)
wid="$(xwininfo -root -tree 2>/dev/null | grep -iE '"GunBound":' | grep -oE '0x[0-9a-f]+' | head -1 || true)"
if [ -n "$wid" ] && command -v import >/dev/null 2>&1; then
  import -window "$wid" "$PNG" 2>/dev/null && echo "[*] screenshot -> $PNG"
else
  echo "[!] no GunBound window found — skipping screenshot"
fi

# 2) stub up
"$HERE/wine-attach.sh" "$PORT" >/tmp/gb-capture-stub.log 2>&1 &
for _ in $(seq 1 15); do ss -ltn 2>/dev/null | grep -q ":$PORT" && break; sleep 1; done
if ! ss -ltn 2>/dev/null | grep -q ":$PORT"; then
  echo "[!] stub failed to start:"; cat /tmp/gb-capture-stub.log; exit 1
fi

# 3) dump JSON, detach cleanly
gdb -q -batch \
  -ex "set pagination off" -ex "set confirm off" -ex "set architecture i386" \
  -ex "target remote localhost:$PORT" \
  -ex "source $HERE/gbstate.py" \
  -ex "gbstate json $JSON" \
  -ex "detach" -ex "quit" >/dev/null 2>&1

pkill -f "no-start --port $PORT" 2>/dev/null || true

if command -v python3 >/dev/null 2>&1 && python3 -m json.tool "$JSON" >/dev/null 2>&1; then
  echo "[*] state    -> $JSON ($(wc -c <"$JSON") bytes, valid)"
else
  echo "[!] JSON not written/invalid — is the game running?"; exit 1
fi
