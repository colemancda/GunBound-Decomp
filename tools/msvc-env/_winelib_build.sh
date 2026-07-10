#!/bin/bash
cd /work
mkdir -p build
# gcc 14 promotes int<->pointer conversions to errors; MSVC allowed them.
# For functional validation we demote them back to warnings.
RELAX="-Wno-int-conversion -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -Wno-implicit-function-declaration -Wno-builtin-declaration-mismatch -Wno-incompatible-pointer-types -Wno-discarded-qualifiers"
SRCS=$(find src -name '*.c' ! -path 'src/lzhuf/*' ! -path 'src/unnamed/msvc_crt_atl/*' ! -name 'test_lzhuf.c' | sort)
# crt_shims.cpp defines operator_new/_free/_rand/_sprintf/... - compile it
# (C++) to an object and add it to the link so those symbols resolve.
wineg++ -m32 -std=gnu++03 -Iinclude $RELAX -c src/cxx/crt_shims.cpp -o build/crt_shims.o 2>>build/winelib_err.txt
echo "compiling+linking $(echo "$SRCS" | wc -l) files via winegcc..."
winegcc -m32 -std=gnu11 -Iinclude $RELAX -o build/gunbound.exe $SRCS build/crt_shims.o -lws2_32 -lwinmm -ldsound -lddraw -ldinput8 2>build/winelib_err.txt
echo "WINEGCC-EXIT=$?"
echo "=== error count ==="; grep -c 'error:' build/winelib_err.txt
echo "=== undefined reference count ==="; grep -c 'undefined reference' build/winelib_err.txt
echo "=== first 15 distinct error lines ==="; grep 'error:' build/winelib_err.txt | head -15
echo "=== exe? ==="; ls -la build/gunbound.exe* 2>/dev/null
