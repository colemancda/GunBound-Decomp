#!/usr/bin/env bash
# Runs INSIDE the gb-msvc container (invoked by msvc_syntax_check.sh — not meant
# to be run directly on the host). Per-file MSVC 7.10 check over every raw-ported
# .c file, reusing a single wineserver so all N files share one Wine startup.
#
# Mode (arg 1):
#   syntax  (default) — cl /Zs, parse-only, no codegen. Fast.
#   compile           — cl /O1 /Fo..., real object generation. Slower, catches
#                       codegen-stage errors /Zs misses.
#
# Exclusions mirror the Makefile's winelib-syntax-check and the Windows-VM
# msvc_syntax_check.ps1: src/lzhuf/ (native pure-algorithm build), the
# statically-linked src/unnamed/msvc_crt_atl/ runtime, and test_lzhuf.c.
set -u

MODE="${1:-syntax}"
CL='Z:\opt\msvc7\bin\cl.exe'
# include\msvc (stdint/stdbool shims) MUST come before include\ — see
# tools/README.md. PlatformSDK supplies windows.h/ddraw.h/d3d.h.
export INCLUDE='Z:\work\include\msvc;Z:\work\include;Z:\opt\msvc7\include;Z:\opt\msvc7\PlatformSDK\include'
export LIB='Z:\opt\msvc7\lib;Z:\opt\msvc7\PlatformSDK\lib'
export WINEDEBUG=-all

cd /work

if [ "$MODE" = compile ]; then
  RESULTS=tools/msvc_compile_check_results.csv
  mkdir -p build/objcheck
else
  RESULTS=tools/msvc_syntax_check_results.csv
fi
printf 'File,Ok,FirstError\n' > "$RESULTS"

mapfile -t FILES < <(find src -name '*.c' \
  ! -path 'src/lzhuf/*' ! -path 'src/unnamed/msvc_crt_atl/*' ! -name 'test_lzhuf.c' | sort)

# GB_CHECK_LIMIT caps the file count (for a quick smoke test of the pipeline).
if [ -n "${GB_CHECK_LIMIT:-}" ]; then
  FILES=("${FILES[@]:0:$GB_CHECK_LIMIT}")
fi

total=${#FILES[@]}
ok=0; i=0
echo "Checking $total files (mode=$MODE)..."
for f in "${FILES[@]}"; do
  i=$((i + 1))
  win='Z:\work\'"${f//\//\\}"
  if [ "$MODE" = compile ]; then
    obj='Z:\work\build\objcheck\'"$(basename "${f%.c}").obj"
    out=$(wine "$CL" /c /nologo /O1 "/Fo$obj" "$win" 2>&1)
  else
    out=$(wine "$CL" /c /nologo /Zs "$win" 2>&1)
  fi
  err=$(printf '%s\n' "$out" | grep -m1 ' error ' || true)
  if [ -z "$err" ]; then
    ok=$((ok + 1)); okflag=1
  else
    okflag=0
  fi
  esc=${err//\"/\"\"}          # CSV-escape embedded quotes
  printf '%s,%s,"%s"\n' "$f" "$okflag" "$esc" >> "$RESULTS"
  if [ $((i % 200)) -eq 0 ]; then echo "  ...$i/$total (clean so far: $ok)"; fi
done

echo
echo "DONE: $ok / $total compiled clean — results in $RESULTS"
echo "== top error codes =="
grep -vE ',1,' "$RESULTS" | grep -oE 'error C[0-9]+' | sort | uniq -c | sort -rn | head -15 || true
