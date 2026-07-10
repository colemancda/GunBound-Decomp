#!/usr/bin/env bash
# One-shot: attach to the running GunBound client, dump the live GameState + the
# active view (widget/panel) hierarchy via gbstate.py, then detach cleanly.
#
# Safe: read-only, sets NO breakpoints, and detaches immediately — none of the
# freeze risk of the netcap capture path. Attaching still pauses the game for the
# brief moment it takes to read memory.
#
# Usage: dump-view-hierarchy.sh [PORT]
set -euo pipefail

PORT="${1:-12345}"
HERE="$(cd "$(dirname "$0")" && pwd)"
GH=/home/coleman/Downloads/ghidra_11.0.1_PUBLIC
RUN=/home/coleman/.local/share/lutris/runners/wine/lutris-7.2-2-x86_64
export PYTHONPATH="$GH/Ghidra/Debug/Debugger-agent-gdb/pypkg/src:$GH/Ghidra/Debug/Debugger-rmi-trace/pypkg/src"

# 1) stand up the winedbg gdb stub on the running game (backgrounded)
"$HERE/wine-attach.sh" "$PORT" >/tmp/gb-viewdump-stub.log 2>&1 &
for _ in $(seq 1 15); do ss -ltn 2>/dev/null | grep -q ":$PORT" && break; sleep 1; done
if ! ss -ltn 2>/dev/null | grep -q ":$PORT"; then
  echo "[!] stub failed to start:"; cat /tmp/gb-viewdump-stub.log; exit 1
fi

# 2) connect, dump, detach cleanly (gdb detach -> winedbg detaches -> game runs on)
gdb -q -batch \
  -ex "set pagination off" -ex "set confirm off" -ex "set architecture i386" \
  -ex "target remote localhost:$PORT" \
  -ex "source $HERE/gbstate.py" \
  -ex "echo \n===== GameState =====\n" -ex "gbstate" \
  -ex "echo \n===== View hierarchy =====\n" -ex "gbstate panels" \
  -ex "detach" -ex "quit"

# 3) the stub exits when gdb disconnects; make sure nothing lingers
pkill -f "no-start --port $PORT" 2>/dev/null || true
echo "[*] detached; game left running."
