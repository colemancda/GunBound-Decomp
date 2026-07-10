#!/bin/bash
# Launch the MSVC-built gunbound.exe in the dedicated test Wine prefix.
#
# The test prefix (~/.wine-gunbound-test by default) is a wow64 Wine prefix
# provisioned with the DirectX 9 runtime (winetricks d3dx9) and forced to an
# 800x600 virtual desktop (winetricks vd=800x600) so the game renders into a
# window instead of taking over the display. Recreate it with:
#   WINEPREFIX=~/.wine-gunbound-test wineboot --init
#   WINEPREFIX=~/.wine-gunbound-test winetricks -q d3dx9 vd=800x600
#
# NOTE: build/link_attempt/gunbound.exe is linked with /FORCE over ~1110
# unresolved externals (known Ghidra fastcall-arity gaps), so it is expected
# to fault early — this is a launch harness for iterating on that, not a
# playable build yet.
set -u
REPO_UNIX="$(cd "$(dirname "$0")/../.." && pwd)"
export WINEPREFIX="${WINEPREFIX:-$HOME/.wine-gunbound-test}"
export WINEDEBUG="${WINEDEBUG:-fixme-all}"
EXE="${1:-$REPO_UNIX/build/link_attempt/gunbound.exe}"
# Run from the repo root so relative asset paths (orig/, *.xfs) resolve.
cd "$REPO_UNIX"
exec wine "$EXE"
