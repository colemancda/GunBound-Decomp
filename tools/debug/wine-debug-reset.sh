#!/usr/bin/env bash
# Clean up a debugging session: stop any winedbg gdb stub + GunBound process and
# shut the prefix's wineserver down gracefully. Run this if a stub was hard-killed
# and Wine starts throwing SIGFPE (a wedged wineserver poisons every new process).
set +e
RUN=/home/coleman/.local/share/lutris/runners/wine/lutris-7.2-2-x86_64
export WINEPREFIX=/home/coleman/Games/wine32-prefix

pkill -f 'winedbg.exe --gdb --no-start' 2>/dev/null
pkill -f 'TestClient/GunBound.gme'     2>/dev/null
sleep 1
# Graceful first, then force.
"$RUN/bin/wineserver" -k 2>/dev/null
sleep 1
pkill -9 -f "$RUN/bin/wineserver" 2>/dev/null

if ps aux | grep -i wineserver | grep -v grep | grep -qv defunct; then
  echo "[!] a wineserver is still alive:"; ps aux | grep -i wineserver | grep -v grep | grep -v defunct
else
  echo "[*] wine state clean — safe to start a new stub."
fi
