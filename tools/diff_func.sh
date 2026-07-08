#!/usr/bin/env bash
# Disassemble one function from the original binary and from a freshly
# MSVC-compiled .obj, side by side, using llvm-objdump (Xcode's, on the
# Mac side - see tools/README.md's "Diffing a function against the
# original" section). Quick alternative to the full asm-differ pipeline -
# good enough for eyeballing a single function's instruction stream
# without a fully relinked/address-matched image.
#
# Usage: tools/diff_func.sh <VA-hex> <length-decimal> <obj-file> [symbol-name]
#   symbol-name defaults to the first function symbol in the obj.
set -euo pipefail

VA="$1"
LEN="$2"
OBJ="$3"
SYM="${4:-}"

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
LLVMOBJDUMP="/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/llvm-objdump"
ORIG="$ROOT/orig/GunBound.gme"

echo "=== original @ 0x$VA (len $LEN) ==="
"$LLVMOBJDUMP" -d --x86-asm-syntax=intel \
    --start-address=0x"$VA" --stop-address=0x"$(printf '%x' $((0x$VA + LEN)))" \
    "$ORIG"

echo
echo "=== compiled: $OBJ ${SYM:+(symbol $SYM)} ==="
"$LLVMOBJDUMP" -d --x86-asm-syntax=intel "$OBJ"
