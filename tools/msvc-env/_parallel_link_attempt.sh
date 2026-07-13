#!/bin/bash
# Parallelized clean-rebuild variant of tools/msvc-env/_link_attempt.sh
# Same file selection / object naming / link step, but compiles with xargs -P4.
set -u
cd /work
export INCLUDE='Z:\work\include\msvc;Z:\work\include;Z:\opt\msvc7\include;Z:\opt\msvc7\PlatformSDK\include'
export LIB='Z:\opt\msvc7\lib;Z:\opt\msvc7\PlatformSDK\lib'
export WINEDEBUG=-all
CL='Z:\opt\msvc7\bin\cl.exe'
LINK='Z:\opt\msvc7\bin\link.exe'
OUT=build/link_attempt
mkdir -p "$OUT"

mapfile -t FILES < <(find src -name '*.c' ! -path 'src/unnamed/msvc_crt_atl/*' ! -name 'test_lzhuf.c' ! -name 'crt_shims_c.c' | sort)
mapfile -t -O "${#FILES[@]}" FILES < <(find src/cxx -name '*.cpp' ! -name 'crt_shims.cpp' | sort)
for extra in FUN_00520380 FUN_005204f0 FUN_00525ea0 FUN_00525f26 FUN_00525fac \
             FUN_00527cb4 FUN_00527f34 FUN_00527ff4 FloatToInt64 FUN_005375c0; do
  FILES+=("src/unnamed/msvc_crt_atl/$extra.c")
done

total=${#FILES[@]}
echo "Compiling $total objects (parallel x4)..."

compile_one() {
  f="$1"
  obj="build/link_attempt/$(echo "$f" | tr '/' '_' | sed 's/\.cpp$/.obj/;s/\.c$/.obj/')"
  [ -f "$obj" ] && [ "$obj" -nt "$f" ] && return 0
  win='Z:\work\'"${f//\//\\}"
  wobj='Z:\work\'"${obj//\//\\}"
  out=$(wine "Z:\opt\msvc7\bin\cl.exe" /c /nologo /O2 "/Fo$wobj" "$win" 2>&1)
  if echo "$out" | grep -q ' error '; then
    echo "COMPILE-ERR $f"
    echo "$out" | grep -m3 ' error '
  fi
}
export -f compile_one

printf '%s\n' "${FILES[@]}" | xargs -P4 -I{} bash -c 'compile_one "$@"' _ {}

echo "Compile pass done. Linking..."
cd "$OUT"
ls *.obj > objs.rsp
wine "$LINK" /nologo /SUBSYSTEM:WINDOWS /FORCE /OUT:gunbound.exe @objs.rsp \
  kernel32.lib user32.lib gdi32.lib ws2_32.lib ddraw.lib dsound.lib dinput.lib \
  winmm.lib advapi32.lib shell32.lib imm32.lib ole32.lib comctl32.lib \
  dxguid.lib libcmt.lib libcpmt.lib > link.log 2>&1
echo "=== unresolved externals: $(grep -c 'unresolved external' link.log) ==="
echo "=== first 20 unresolved symbol names (deduped) ==="
grep -oE 'unresolved external symbol [^ ]+' link.log | sed 's/unresolved external symbol //' | sort | uniq -c | sort -rn | head -20
echo "=== duplicate definitions ==="
grep -c 'LNK2005' link.log
echo "=== exe produced? ==="
ls -la gunbound.exe 2>/dev/null || echo "(no exe - link failed even with /FORCE)"
