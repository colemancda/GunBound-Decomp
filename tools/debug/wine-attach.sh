#!/usr/bin/env bash
# PRIMARY debug entry point.
#
# GunBound.gme cannot be started bare: Launcher.exe AES-encrypts the account id
# and passes it as the client's command line, which the game decrypts via
# CryptDecrypt (see src/entry/WinMain.c -> GetCommandLineA, src/.../FUN_00524bb0.c).
# It also seeds HKLM\Software\Softnyx\GunBound. So we let the real launcher start
# the game, then ATTACH a winedbg gdb stub to the running process by its Wine pid.
#
# Usage: wine-attach.sh [PORT] [EXE_NAME]
#   PORT      TCP port for the gdb stub (default 12345)
#   EXE_NAME  process to find in Wine's task list (default GunBound.gme)
set -euo pipefail

PORT="${1:-12345}"
EXE_NAME="${2:-GunBound.gme}"

RUN=/home/coleman/.local/share/lutris/runners/wine/lutris-7.2-2-x86_64
export WINEPREFIX=/home/coleman/Games/wine32-prefix
export WINEARCH=win32
export WINEDEBUG="${WINEDEBUG:--all}"
export WINELOADER="$RUN/bin/wine"
export PATH="$RUN/bin:$PATH"

# Resolve the Wine (Windows) pid from winedbg's process list. The name lives in
# single quotes; the first hex column on that line is the wpid.
WPID=$(echo "info process" | "$RUN/bin/winedbg" 2>/dev/null \
  | grep -F "'$EXE_NAME'" | grep -oE '^[[:space:]]*[0-9a-fA-F]{8}' | tr -d '[:space:]' | head -1)

if [ -z "${WPID:-}" ]; then
  echo "[!] Could not find a running '$EXE_NAME' in the Wine prefix." >&2
  echo "    Start it first via Lutris (or Launcher.exe) so the launcher supplies" >&2
  echo "    the encrypted credentials, then re-run this script." >&2
  echo "    Current Wine tasks:" >&2
  echo "info process" | "$RUN/bin/winedbg" 2>/dev/null | grep "'" >&2 || true
  exit 1
fi

echo "[*] Wine:   $("$RUN/bin/wine" --version)"
echo "[*] Target: $EXE_NAME  (wpid 0x$WPID)"
echo "[*] gdb stub on localhost:$PORT — in Ghidra pick 'gdb (wine remote stub)', port $PORT"
exec "$RUN/bin/winedbg" --gdb --no-start --port "$PORT" "0x$WPID"
