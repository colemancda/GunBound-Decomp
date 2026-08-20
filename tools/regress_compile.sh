#!/bin/bash
# Syntax-check a list of source files with MSVC 7.1 in the gb-check container.
#
# Usage: bash tools/regress_compile.sh <file-with-one-path-per-line>
#
# THE POINT OF THE base-name CHECK: the obvious version of this script greps
# the output for 'error C' and calls everything else a pass. When the gb-check
# container is not running, docker prints 'Error response from daemon: ...',
# which does not match 'error C' - so every file is reported clean, instantly.
# That is how a 238-file run of mine 'passed' in a few seconds while the
# container had been dead for two hours, and it hid a file I had corrupted.
# cl /nologo echoes the source file name on every run, so its absence means
# the compiler never ran. Three such failures abort the whole run.
#
# Same family as the traps in the build-and-run notes: a broken toolchain
# that reports success is worse than one that reports failure.
fail=0; n=0; infra=0
while read f; do
  [ -z "$f" ] && continue
  n=$((n+1))
  case "$f" in *.cpp) FL=/TP;; *) FL=;; esac
  out=$(docker exec gb-check wine "Z:\\opt\\msvc7\\bin\\cl.exe" /c /nologo /Zs $FL "Z:\\work\\$(echo $f | tr / \\\\)" 2>&1)
  base=$(basename "$f")
  # cl /nologo echoes the source file name; if it is absent the compiler did not run
  if ! echo "$out" | grep -qF "$base"; then
    infra=$((infra+1)); echo "!!! COMPILER DID NOT RUN for $f :: $(echo "$out" | head -1)"
    [ $infra -ge 3 ] && { echo "ABORTING - toolchain is not working"; exit 2; }
    continue
  fi
  r=$(echo "$out" | grep -E "error C")
  if [ -n "$r" ]; then fail=$((fail+1)); echo "### $f"; echo "$r" | head -3; fi
done < "$1"
echo "REGRESSION DONE: $n attempted, $fail with errors, $infra did not run"
