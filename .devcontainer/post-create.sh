#!/usr/bin/env bash
# Runs once after the container is created. Clones asm-differ into the
# (gitignored) tools/asm-differ/ if it isn't already present in the workspace.
set -euo pipefail

if [ ! -e tools/asm-differ/diff.py ]; then
  echo "Cloning asm-differ..."
  git clone --depth 1 https://github.com/simonlindholm/asm-differ tools/asm-differ
else
  echo "asm-differ already present, skipping clone."
fi

echo "Toolchain ready. Try: make   (native parity build)"
