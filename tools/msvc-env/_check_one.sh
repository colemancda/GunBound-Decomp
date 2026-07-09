#!/bin/bash
# Verify a single raw-port .c file against BOTH toolchains:
#   MSVC 7.1 (via the gb-check container, must already be running)
#   winegcc (via the gunbound-devcontainer image, spun up per call)
# Usage: _check_one.sh path/to/file.c
set -u
f="$1"
win="Z:\\work\\${f//\//\\}"
msvc_err=$(docker exec gb-check wine 'Z:\opt\msvc7\bin\cl.exe' /c /nologo /Zs "$win" 2>&1 | grep ' error ')
if [ -n "$msvc_err" ]; then
  echo "MSVC-FAIL $f"
  echo "$msvc_err"
  exit 1
fi
RELAX="-Wno-int-conversion -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -Wno-implicit-function-declaration -Wno-builtin-declaration-mismatch -Wno-incompatible-pointer-types -Wno-discarded-qualifiers"
gcc_err=$(docker run --rm -v "$PWD":/work -w /work gunbound-devcontainer bash -c "winegcc -std=gnu11 -Iinclude $RELAX -c '$f' -o /tmp/t.o 2>&1" | grep -E 'error:|Wreturn-mismatch')
if [ -n "$gcc_err" ]; then
  echo "GCC-FAIL $f"
  echo "$gcc_err"
  exit 1
fi
echo "OK $f"
