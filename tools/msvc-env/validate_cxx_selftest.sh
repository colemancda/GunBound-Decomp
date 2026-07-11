#!/usr/bin/env bash
# Validate the C++ type reconstruction (src/cxx/*.h) by compiling
# src/cxx/cxx_selftest.cpp with real MSVC 7.10 cl.exe under Wine in the gb-msvc
# container. cxx_selftest.cpp includes every cxx header and asserts object sizes
# and field offsets (GB_STATIC_ASSERT / GB_OFFSETOF), so a clean /Zs parse means
# the reconstructed layouts match the MSVC 7.10 ABI the game was built with.
#
# This is the C++/.cpp companion to msvc_syntax_check.sh, which only covers the
# raw-ported .c files (cxx_selftest.cpp is C++ and needs its own invocation).
# /Zs = parse + semantic analysis, no codegen; the layout asserts are evaluated
# at that stage. NOTE: 32-bit clang can only check the sizeof asserts - the
# GB_OFFSETOF null-deref trick isn't a constant-expression there, so the offset
# asserts require this real-MSVC path.
#
# Usage:  tools/msvc-env/validate_cxx_selftest.sh    (needs Docker + gb-msvc image)
set -euo pipefail

REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
IMAGE="${GB_MSVC_IMAGE:-gb-msvc}"

if ! docker image inspect "$IMAGE" >/dev/null 2>&1; then
  echo "Docker image '$IMAGE' not found. Build it first:" >&2
  echo "  docker build --platform linux/amd64 -t gb-msvc tools/msvc-env" >&2
  exit 1
fi

# include\msvc (stdint/stdbool shims) before include\ - same ordering as
# _msvc_check_inner.sh. cxx_selftest only needs the cxx headers + those shims.
exec docker run --rm --platform linux/amd64 -v "$REPO":/work -w /work \
  -e INCLUDE='Z:\work\include\msvc;Z:\work\include;Z:\opt\msvc7\include;Z:\opt\msvc7\PlatformSDK\include' \
  -e WINEDEBUG=-all "$IMAGE" \
  wine 'Z:\opt\msvc7\bin\cl.exe' /c /nologo /Zs 'Z:\work\src\cxx\cxx_selftest.cpp'
