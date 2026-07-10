#!/bin/bash
# Full-tree compile + link attempt, run INSIDE the gb-msvc container.
# Compiles every main-tree .c plus the handful of CRT/ATL helpers the
# main code references, then links with the full Win32 import set.
# Reports the unresolved-symbol count - the real link gap.
#
# NOTE: the object list is passed via a linker response file (@objs.rsp);
# 1800 object names blow past Wine's 32K command-line limit and link.exe
# silently produces nothing if they're passed inline.
set -u
cd /work
export INCLUDE='Z:\work\include\msvc;Z:\work\include;Z:\opt\msvc7\include;Z:\opt\msvc7\PlatformSDK\include'
export LIB='Z:\opt\msvc7\lib;Z:\opt\msvc7\PlatformSDK\lib'
export WINEDEBUG=-all
CL='Z:\opt\msvc7\bin\cl.exe'
LINK='Z:\opt\msvc7\bin\link.exe'
OUT=build/link_attempt
mkdir -p "$OUT"

# main tree (lzhuf included - DecodeLZHUFBlock/InitLZHUFTree are referenced)
mapfile -t FILES < <(find src -name '*.c' ! -path 'src/unnamed/msvc_crt_atl/*' ! -name 'test_lzhuf.c' ! -name 'crt_shims_c.c' | sort)
# the CRT/ATL helpers the main code needs that DO compile clean
for extra in FUN_00520380 FUN_005204f0 FUN_00525ea0 FUN_00525f26 FUN_00525fac \
             FUN_00527cb4 FUN_00527f34 FUN_00527ff4 FUN_0053753c FUN_005375c0; do
  FILES+=("src/unnamed/msvc_crt_atl/$extra.c")
done

total=${#FILES[@]}; i=0; cerr=0
echo "Compiling $total objects..."
for f in "${FILES[@]}"; do
  i=$((i+1))
  obj="$OUT/$(echo "$f" | tr '/' '_' | sed 's/\.c$/.obj/')"
  [ -f "$obj" ] && continue
  win='Z:\work\'"${f//\//\\}"
  wobj='Z:\work\'"${obj//\//\\}"
  out=$(wine "$CL" /c /nologo /O2 "/Fo$wobj" "$win" 2>&1)
  echo "$out" | grep -q ' error ' && { echo "COMPILE-ERR $f"; echo "$out" | grep -m3 ' error '; cerr=$((cerr+1)); }
  [ $((i % 300)) -eq 0 ] && echo "  ...$i/$total"
done
echo "Compiled (errors: $cerr). Linking..."
cd "$OUT"
ls *.obj > objs.rsp
wine "$LINK" /nologo /SUBSYSTEM:WINDOWS /FORCE /OUT:gunbound.exe @objs.rsp \
  kernel32.lib user32.lib gdi32.lib ws2_32.lib ddraw.lib dsound.lib dinput.lib \
  winmm.lib advapi32.lib shell32.lib imm32.lib ole32.lib comctl32.lib \
  libcmt.lib > link.log 2>&1
echo "=== unresolved externals: $(grep -c 'unresolved external' link.log) ==="
echo "=== first 20 unresolved symbol names (deduped) ==="
grep -oE 'unresolved external symbol [^ ]+' link.log | sed 's/unresolved external symbol //' | sort | uniq -c | sort -rn | head -20
echo "=== duplicate definitions ==="
grep -c 'LNK2005' link.log
echo "=== exe produced? ==="
ls -la gunbound.exe 2>/dev/null || echo "(no exe - link failed even with /FORCE)"
