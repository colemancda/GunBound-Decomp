#!/usr/bin/env bash
# Emit a DWARF object containing every C++ type in src/cxx/, for import into
# Ghidra. The trick: compile the reconstruction headers with host g++ -m32 and
# full class debug info. The GB_STATIC_ASSERTs in the headers force g++'s layout
# to equal MSVC 7.1's (== the binary), so the DWARF offsets are the real offsets
# — no hand-transcription. Ghidra's DWARF analyzer then imports the lot with
# correct sizes, offsets, inheritance and vtables.
#
# Output: build/gb_cxx_types.o  (ELF32 with DWARF). Import it into Ghidra and run
# DWARF analysis, or feed it to import_ghidra_types.sh.
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"
OUT="build/gb_cxx_types.o"
mkdir -p build

# All non-template class/struct names, in header order, de-duplicated.
TYPES=$(grep -hoE '^(class|struct) C?[A-Za-z0-9]+' src/cxx/*.h \
        | awk '{print $2}' | grep -vE '^CAtlArray$' | awk '!seen[$0]++')

TU="$(mktemp --suffix=.cpp)"
trap 'rm -f "$TU"' EXIT
{
  for h in gb_common.h GameState.h Widget.h Protocol.h ClientContext.h ValueGuard.h AtlArray.h; do
    echo "#include \"$h\""
  done
  # One member of each type forces GCC to emit its full layout in DWARF.
  echo 'struct GbForceAll {'
  i=0; for t in $TYPES; do echo "  $t m$i;"; i=$((i+1)); done
  echo '  CAtlArray<CWidget*> arr;'
  echo '};'
  echo 'unsigned gb_force_size = sizeof(GbForceAll);'
} > "$TU"

# -femit-class-debug-always: emit full debug for classes whose vtable key
#   function lives in another TU (otherwise GCC emits declaration-only).
# -fno-eliminate-unused-debug-types: keep types that aren't otherwise referenced.
g++ -m32 -g -gdwarf-4 -fno-eliminate-unused-debug-types -femit-class-debug-always \
    -std=gnu++11 -fpermissive -w -fno-rtti \
    -D'__declspec(x)=' -D__cdecl= -D__stdcall= -D__fastcall= -D__thiscall= -D__forceinline=inline \
    -Iinclude -Isrc/cxx -c "$TU" -o "$OUT"

echo "[*] wrote $OUT"
echo "[*] $(echo "$TYPES" | wc -w) C++ types + CAtlArray<CWidget*>"
command -v pahole >/dev/null && echo "[*] verify a layout:  pahole -C CState02ServerSelect $OUT"
