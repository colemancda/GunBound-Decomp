#!/bin/bash
# Bring-up link: everything _link_attempt.sh built, PLUS auto-generated
# no-op stubs for each still-unresolved symbol, so no call target is a
# zeroed /FORCE placeholder. Produces build/link_attempt/gunbound_bringup.exe.
# Run INSIDE the gb-msvc container, AFTER _link_attempt.sh (needs its
# objects and a fresh link.log; the stubs are generated on the host side
# by gen_bringup_stubs.py or here if python3 exists in the container).
set -u
cd /work
export INCLUDE='Z:\work\include\msvc;Z:\work\include;Z:\opt\msvc7\include;Z:\opt\msvc7\PlatformSDK\include'
export LIB='Z:\opt\msvc7\lib;Z:\opt\msvc7\PlatformSDK\lib'
export WINEDEBUG=-all
CL='Z:\opt\msvc7\bin\cl.exe'
LINK='Z:\opt\msvc7\bin\link.exe'
OUT=build/link_attempt

[ -f "$OUT/link.log" ] || { echo "run _link_attempt.sh first (need $OUT/link.log)"; exit 1; }

command -v python3 >/dev/null || { echo "python3 required (apt-get install python3)"; exit 1; }

cd "$OUT"
do_link() {
  { ls *.obj | grep -v '^bringup_stubs_' | grep -vxF -f /work/tools/msvc-env/bringup_drop.txt; \
    ls bringup_stubs_*.obj 2>/dev/null; } > objs_bringup.rsp
  wine "$LINK" /nologo /SUBSYSTEM:WINDOWS /FORCE /MAP:gunbound_bringup.map /OUT:gunbound_bringup.exe @objs_bringup.rsp \
    kernel32.lib user32.lib gdi32.lib ws2_32.lib ddraw.lib dsound.lib dinput.lib \
    winmm.lib advapi32.lib shell32.lib imm32.lib ole32.lib comctl32.lib \
    dxguid.lib libcmt.lib libcpmt.lib > link_bringup.log 2>&1
}

# pass 1: no stubs - enumerate the full unresolved set (including
# symbols orphaned by the drop list), then generate stubs and relink
rm -f bringup_stubs_*
do_link
python3 /work/tools/msvc-env/gen_bringup_stubs.py link_bringup.log . | tail -1
cd /work
for f in "$OUT"/bringup_stubs_*.c; do
  win='Z:\work\'"${f//\//\\}"
  wobj="${win%.c}.obj"
  out=$(wine "$CL" /c /nologo /O1 "/Fo$wobj" "$win" 2>&1)
  echo "$out" | grep -q ' error ' && { echo "STUB COMPILE-ERR $f"; echo "$out" | grep -m3 ' error '; exit 1; }
done
cd "$OUT"
do_link
echo "=== bring-up unresolved externals: $(grep -c 'unresolved external' link_bringup.log) (want 0) ==="
grep -oE 'unresolved external symbol [^ ]+' link_bringup.log | sort -u | head -10
echo "=== duplicates: $(grep -c 'LNK2005' link_bringup.log) (want 0) ==="
ls -la gunbound_bringup.exe 2>/dev/null || echo "(no exe)"
