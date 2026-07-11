#!/usr/bin/env bash
# Bind the Ready Room option-toggle LABELS to the 0x3101 settings-dword bit
# groups (A SIDE / SSDEATH / ATTACK / DEATH72 / game-mode). The encode is
# already decoded statically (docs/screens/09_ready_room.md); the missing piece
# is which visible toggle is which group, because the host config toggles are
# image-mapped hit regions, not sprite-labelled widgets.
#
# Attaches, installs SAFE auto-continuing breakpoints via gbroomsettings.py on
# State09_ReadyRoom_OnCommand (buttonId -> group) and QueueOutgoingPacketField
# (the re-sent settings dword, for a bit-level cross-check), logs each hit, then
# clean-detaches. See gbroomsettings.py's header.
#
# WHAT TO DO WHILE IT RUNS (must be the HOST of a room):
#   In the Ready Room, click each room-option toggle ONE AT A TIME and note,
#   for each, the on-screen label (A SIDE / SSDEATH / ATTACK / DEATH72 / the
#   game-mode selector) against the GROUP the CLICK line prints. Four (+mode)
#   clicks resolve the whole label->group map. The following `settings=...`
#   line confirms which bit group actually changed.
#
# Usage: roomsettings-probe.sh [PORT] [SECONDS] [LOGFILE]
set -euo pipefail

PORT="${1:-12345}"
export GBROOM_SECONDS="${2:-60}"
export GBROOM_LOG="${3:-/tmp/gb-roomsettings.log}"

HERE="$(cd "$(dirname "$0")" && pwd)"
GH=/home/coleman/Downloads/ghidra_11.0.1_PUBLIC
export PYTHONPATH="$GH/Ghidra/Debug/Debugger-agent-gdb/pypkg/src:$GH/Ghidra/Debug/Debugger-rmi-trace/pypkg/src"

rm -f "$GBROOM_LOG"
"$HERE/wine-attach.sh" "$PORT" >/tmp/gb-roomsettings-stub.log 2>&1 &
for _ in $(seq 1 15); do ss -ltn 2>/dev/null | grep -q ":$PORT" && break; sleep 1; done
if ! ss -ltn 2>/dev/null | grep -q ":$PORT"; then
  echo "[!] stub failed:"; cat /tmp/gb-roomsettings-stub.log; exit 1
fi

echo "[*] probing room-option toggles for ${GBROOM_SECONDS}s — HOST a room, click each option once..."
gdb -q \
  -ex "set pagination off" -ex "set confirm off" -ex "set architecture i386" \
  -ex "target remote localhost:$PORT" \
  -ex "source $HERE/gbroomsettings.py" \
  -ex "continue"

pkill -f "no-start --port $PORT" 2>/dev/null || true
echo "[*] done -> $GBROOM_LOG"
