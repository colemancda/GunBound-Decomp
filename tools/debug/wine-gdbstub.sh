#!/usr/bin/env bash
# ADVANCED: launch GunBound.gme directly under a winedbg gdb stub, suspended at
# entry. Use this only when you need to debug early init/login code from the very
# first instruction. For everything else prefer wine-attach.sh.
#
# GunBound.gme reads its command line (GetCommandLineA in the 0x5277df CRT entry ->
# WinMain) and DECRYPTS it (CryptDecrypt) to recover the account credentials that
# Launcher.exe encrypted. Launching without that argument means the game has no
# valid credentials and will bail during login. Pass the encrypted hex string as
# CRED_ARG if you have captured one (e.g. from the launcher's CreateProcess call,
# or attach once with wine-attach.sh and read it out of the live process).
#
# Usage: wine-gdbstub.sh [PORT] [CRED_ARG] [EXE]
#   PORT      TCP port for the gdb stub (default 12345)
#   CRED_ARG  encrypted credential string to pass as the client command line
#   EXE       Windows exe to launch (default the GunBound client)
set -euo pipefail

PORT="${1:-12345}"
CRED_ARG="${2:-}"
EXE="${3:-/home/coleman/Games/TestClient/GunBound.gme}"

RUN=/home/coleman/.local/share/lutris/runners/wine/lutris-7.2-2-x86_64
export WINEPREFIX=/home/coleman/Games/wine32-prefix
export WINEARCH=win32
export WINEDEBUG="${WINEDEBUG:--all}"
export WINELOADER="$RUN/bin/wine"
export PATH="$RUN/bin:$PATH"

cd "$(dirname "$EXE")"

if [ -z "$CRED_ARG" ]; then
  echo "[!] No CRED_ARG given — the game will reach WinMain but fail login-time"     >&2
  echo "    credential decryption. Fine for init/DirectDraw/XFS breakpoints; use"    >&2
  echo "    wine-attach.sh for anything that needs a real session."                  >&2
fi

echo "[*] Wine:   $("$RUN/bin/wine" --version)"
echo "[*] Exe:    $EXE"
echo "[*] gdb stub on localhost:$PORT (target loaded SUSPENDED at ntdll, pre-entry)"
echo "[*] In Ghidra pick 'gdb (wine remote stub)', port $PORT; entry is 0x5277df"
exec "$RUN/bin/winedbg" --gdb --no-start --port "$PORT" "$EXE" $CRED_ARG
