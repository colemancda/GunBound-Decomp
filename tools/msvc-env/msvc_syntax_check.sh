#!/usr/bin/env bash
# Linux-side driver for a per-file MSVC 7.10 syntax/compile check via the
# gb-msvc Docker image (real cl.exe under Wine). This is the Docker equivalent
# of the Makefile's `winelib-syntax-check` target and the Windows-VM
# tools/msvc_syntax_check.ps1 — the piece tools/msvc-env/README.md's "Known
# gaps" flagged as not-yet-wired-up.
#
# Usage:
#   tools/msvc-env/msvc_syntax_check.sh            # syntax-only (/Zs), fast
#   tools/msvc-env/msvc_syntax_check.sh --compile  # real codegen (/Fo), slower
#
# Env:
#   GB_MSVC_IMAGE   image tag to use          (default: gb-msvc)
#   GB_CHECK_LIMIT  cap file count for a smoke test of the pipeline
#
# Output: tools/msvc_syntax_check_results.csv (or _compile_ variant), plus a
# clean/total summary and top error-code histogram on stdout.
#
# All 1781 files share ONE container / one wineserver — a docker-run-per-file
# loop would pay Wine's cold-start cost ~1781 times over.
set -euo pipefail

MODE=syntax
if [ "${1:-}" = "--compile" ]; then
  MODE=compile
elif [ -n "${1:-}" ]; then
  echo "Unknown arg: $1 (use --compile or no arg)" >&2
  exit 2
fi

REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
IMAGE="${GB_MSVC_IMAGE:-gb-msvc}"

if ! docker image inspect "$IMAGE" >/dev/null 2>&1; then
  echo "Docker image '$IMAGE' not found. Build it first:" >&2
  echo "  docker build --platform linux/amd64 -t gb-msvc tools/msvc-env" >&2
  exit 1
fi

exec docker run --rm --platform linux/amd64 \
  -e GB_CHECK_LIMIT="${GB_CHECK_LIMIT:-}" \
  -v "$REPO":/work -w /work \
  "$IMAGE" bash /work/tools/msvc-env/_msvc_check_inner.sh "$MODE"
