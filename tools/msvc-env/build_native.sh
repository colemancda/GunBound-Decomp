#!/bin/bash
# Native (no-Docker) full-tree compile + link with real MSVC 7.10 under Wine.
# Mirrors _link_attempt.sh but drives a locally-installed wine directly instead
# of the gb-msvc container, mapping the repo through Wine's default Z: = / drive.
# Compilation is fanned out across cores (JOBS, default = nproc) since Wine's
# per-cl.exe startup dominates; already-fresh .obj files are skipped on rerun.
#
# Requires: wine on PATH, tools/msvc-env/msvc7/ populated (the release asset),
# WINEPREFIX pointing at an initialised prefix (defaults to ~/.wine-msvc7).
set -u

REPO_UNIX="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$REPO_UNIX"

to_win() { printf 'Z:%s' "$(echo "$1" | sed 's#/#\\#g')"; }
WIN_REPO="$(to_win "$REPO_UNIX")"
WIN_MSVC="$WIN_REPO\\tools\\msvc-env\\msvc7"

export WINEPREFIX="${WINEPREFIX:-$HOME/.wine-msvc7}"
export WINEDEBUG=-all
export INCLUDE="$WIN_REPO\\include\\msvc;$WIN_REPO\\include;$WIN_MSVC\\include;$WIN_MSVC\\PlatformSDK\\include"
export LIB="$WIN_MSVC\\lib;$WIN_MSVC\\PlatformSDK\\lib"
CL="$WIN_MSVC\\bin\\cl.exe"
LINK="$WIN_MSVC\\bin\\link.exe"
OUT=build/link_attempt
JOBS="${JOBS:-$(nproc)}"
mkdir -p "$OUT"

mapfile -t FILES < <(find src -name '*.c' ! -path 'src/unnamed/msvc_crt_atl/*' ! -name 'test_lzhuf.c' ! -name 'crt_shims_c.c' | sort)
mapfile -t -O "${#FILES[@]}" FILES < <(find src/cxx -name '*.cpp' ! -name 'crt_shims.cpp' | sort)
for extra in FUN_00520380 FUN_005204f0 FUN_00525ea0 FUN_00525f26 FUN_00525fac \
             FUN_00527cb4 FUN_00527f34 FUN_00527ff4 FloatToInt64 FUN_005375c0; do
  FILES+=("src/unnamed/msvc_crt_atl/$extra.c")
done

# Per-file compile worker (exported for xargs subshells).
export WIN_REPO CL OUT
compile_one() {
  local f="$1"
  local obj="$OUT/$(echo "$f" | tr '/' '_' | sed 's/\.cpp$/.obj/;s/\.c$/.obj/')"
  [ -f "$obj" ] && [ "$obj" -nt "$f" ] && return 0
  local win="$WIN_REPO\\${f//\//\\}"
  local wobj="$WIN_REPO\\${obj//\//\\}"
  local out
  out=$(wine "$CL" /c /nologo /O2 "/Fo$wobj" "$win" 2>&1)
  if echo "$out" | grep -q ' error '; then
    { echo "COMPILE-ERR $f"; echo "$out" | grep -m3 ' error '; } >> "$OUT/compile_errors.log"
  fi
}
export -f compile_one

total=${#FILES[@]}
echo "Compiling $total objects with cl.exe 13.10.3052 (/O2), JOBS=$JOBS..."
: > "$OUT/compile_errors.log"
printf '%s\n' "${FILES[@]}" | xargs -P "$JOBS" -I{} bash -c 'compile_one "$@"' _ {}

cerr=$(grep -c '^COMPILE-ERR' "$OUT/compile_errors.log" || true)
echo "Compiled (errors: $cerr). Linking..."
cd "$OUT"
ls *.obj > objs.rsp
wine "$LINK" /nologo /SUBSYSTEM:WINDOWS /FORCE /OUT:gunbound.exe @objs.rsp \
  kernel32.lib user32.lib gdi32.lib ws2_32.lib ddraw.lib dsound.lib dinput.lib \
  winmm.lib advapi32.lib shell32.lib imm32.lib ole32.lib comctl32.lib \
  dxguid.lib libcmt.lib libcpmt.lib > link.log 2>&1
echo "=== COMPILE-ERR total: $cerr ==="
[ "$cerr" -gt 0 ] && { echo "--- compile errors ---"; cat compile_errors.log; }
echo "=== unresolved externals: $(grep -c 'unresolved external' link.log) ==="
echo "=== exe produced? ==="
ls -la gunbound.exe 2>/dev/null || echo "(no exe - link failed even with /FORCE)"
