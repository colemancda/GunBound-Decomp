#!/usr/bin/env bash
# Live-trace the avatar subsystem to (1) name the three Avatar-Store slot
# handlers (0x44b170/0x44b330/0x44b460) by which user action fires them, and
# (2) resolve the Head/Flag word order in the avatarEquipped record.
#
# Attaches, installs SAFE auto-continuing breakpoints via gbavatar.py, logs each
# hit, then clean-detaches. See gbavatar.py's header for what each line means.
#
# WHAT TO DO WHILE IT RUNS:
#   Store-handler naming (in the Avatar Store): try each action one at a time and
#   note the wall-clock order — (a) click an item to try it on, (b) remove/clear a
#   slot, (c) switch category tab, (d) click Buy — then match to the HANDLER lines.
#   Head/Flag order: FIRST equip a distinctive flag (note its id from
#   `decode_avatar.py orig/Avatar.xfs`) with a Standard head, THEN enter a game
#   room so a LoadRoomSlotAvatar line dumps your slot's 8-byte record.
#
# Usage: avatar-probe.sh [PORT] [SECONDS] [LOGFILE]
set -euo pipefail

PORT="${1:-12345}"
export GBAVATAR_SECONDS="${2:-45}"
export GBAVATAR_LOG="${3:-/tmp/gb-avatar.log}"

HERE="$(cd "$(dirname "$0")" && pwd)"
GH=/home/coleman/Downloads/ghidra_11.0.1_PUBLIC
export PYTHONPATH="$GH/Ghidra/Debug/Debugger-agent-gdb/pypkg/src:$GH/Ghidra/Debug/Debugger-rmi-trace/pypkg/src"

rm -f "$GBAVATAR_LOG"
"$HERE/wine-attach.sh" "$PORT" >/tmp/gb-avatar-stub.log 2>&1 &
for _ in $(seq 1 15); do ss -ltn 2>/dev/null | grep -q ":$PORT" && break; sleep 1; done
if ! ss -ltn 2>/dev/null | grep -q ":$PORT"; then
  echo "[!] stub failed:"; cat /tmp/gb-avatar-stub.log; exit 1
fi

echo "[*] probing avatar subsystem for ${GBAVATAR_SECONDS}s — drive the Avatar Store / enter a room..."
gdb -q \
  -ex "set pagination off" -ex "set confirm off" -ex "set architecture i386" \
  -ex "target remote localhost:$PORT" \
  -ex "source $HERE/gbavatar.py" \
  -ex "continue"

pkill -f "no-start --port $PORT" 2>/dev/null || true
echo "[*] done -> $GBAVATAR_LOG"
