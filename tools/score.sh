#!/usr/bin/env bash
# Print just the asm-differ match score for one function - real edit-distance
# scoring via the "-e" (ELF-symbol) mode, no relinked/address-matched image
# needed (see tools/README.md). Lower is better; 0 = perfect match.
#
# Usage: tools/score.sh <symbol> <start-VA-hex> <end-VA-hex> <obj-file>
#   e.g.  tools/score.sh _lzhuf_get_bit 4ea120 4ea1a4 build/GetBit_cmp.obj
set -euo pipefail

SYM="$1"
START="$2"
END="$3"
OBJ="$4"

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PYTHON="python3"

cd "$ROOT"
GB_MYIMG="$OBJ" "$PYTHON" tools/asm-differ/diff.py \
    -e "$SYM" "0x$START" "0x$END" --format json \
    | "$PYTHON" -c "
import json, sys
d = json.load(sys.stdin)
print(f\"score: {d['current_score']} / max: {d['max_score']}\")
"
