#!/bin/bash
cd /work
RELAX="-Wno-int-conversion -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -Wno-implicit-function-declaration -Wno-builtin-declaration-mismatch -Wno-incompatible-pointer-types -Wno-discarded-qualifiers"
> /work/build/conflicting_files.txt
SRCS=$(find src -name '*.c' ! -path 'src/lzhuf/*' ! -path 'src/unnamed/msvc_crt_atl/*' ! -name 'test_lzhuf.c' | sort)
n=0
for f in $SRCS; do
  n=$((n+1))
  err=$(winegcc -std=gnu11 -Iinclude $RELAX -c "$f" -o /tmp/scan.o 2>&1 | grep -m1 'conflicting types')
  [ -n "$err" ] && echo "$f :: $(echo "$err" | sed -E 's/.*conflicting types for/conflicting types for/')" >> /work/build/conflicting_files.txt
  [ $((n % 400)) -eq 0 ] && echo "...scanned $n" >&2
done
echo "SCAN-DONE: $(wc -l < /work/build/conflicting_files.txt) files with conflicting types"
cat /work/build/conflicting_files.txt
