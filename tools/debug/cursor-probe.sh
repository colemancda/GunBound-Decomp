#!/usr/bin/env bash
# Log the live cursor draw for a few seconds to resolve the g_cursorFrame mystery.
# Attaches, installs the (safe, auto-continuing) draw breakpoint via gbcursor.py,
# logs $esi / node / g_cursorFrame / g_frameCounter each frame, then clean-detaches.
#
# Move the cursor around the screen while it runs.
#
# Usage: cursor-probe.sh [PORT] [SECONDS] [LOGFILE]
set -euo pipefail

PORT="${1:-12345}"
export GBCURSOR_SECONDS="${2:-10}"
export GBCURSOR_LOG="${3:-/tmp/gb-cursor.log}"

HERE="$(cd "$(dirname "$0")" && pwd)"
GH=/home/coleman/Downloads/ghidra_11.0.1_PUBLIC
export PYTHONPATH="$GH/Ghidra/Debug/Debugger-agent-gdb/pypkg/src:$GH/Ghidra/Debug/Debugger-rmi-trace/pypkg/src"

rm -f "$GBCURSOR_LOG"
"$HERE/wine-attach.sh" "$PORT" >/tmp/gb-cursor-stub.log 2>&1 &
for _ in $(seq 1 15); do ss -ltn 2>/dev/null | grep -q ":$PORT" && break; sleep 1; done
if ! ss -ltn 2>/dev/null | grep -q ":$PORT"; then
  echo "[!] stub failed:"; cat /tmp/gb-cursor-stub.log; exit 1
fi

echo "[*] logging cursor draw for ${GBCURSOR_SECONDS}s — move the cursor around..."
gdb -q \
  -ex "set pagination off" -ex "set confirm off" -ex "set architecture i386" \
  -ex "target remote localhost:$PORT" \
  -ex "source $HERE/gbcursor.py" \
  -ex "continue"

pkill -f "no-start --port $PORT" 2>/dev/null || true
echo "[*] done -> $GBCURSOR_LOG"
