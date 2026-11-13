#!/usr/bin/env bash
# Lifter self-test: hand-written x86 snippets are lifted, run on the runtime and
# compared with the same snippets executed natively on an x86 CPU.
#
#   recomp/test/run.sh [host|aarch64] [--update]
#
# The native reference needs an x86 host that can run 32-bit programs; without one
# (or for the aarch64 target, which runs under qemu-aarch64) the committed
# expected.txt is used. --update rewrites expected.txt from the native reference.
# EXTRA_CFLAGS adds compiler flags for the lifted harness (e.g. -DRT_DYNAMIC_BASE).
set -euo pipefail

target="${1:-host}"
update=0
[ "${2:-}" = "--update" ] && update=1

here="$(cd "$(dirname "$0")" && pwd)"
recomp="$(cd "$here/.." && pwd)"
build="$recomp/build/test"
out="$build/$target"
mkdir -p "$out"

sysroot=""
case "$target" in
host) cc="${CC:-gcc}" ;;
aarch64)
    cc="${AARCH64_CC:-/home/coleman/Developer/batocera.linux/output/h616/host/bin/aarch64-buildroot-linux-gnu-gcc}"
    sysroot="$("$cc" -print-sysroot)"
    ;;
*) echo "usage: $0 [host|aarch64] [--update]" >&2; exit 2 ;;
esac

# ---- 1. assemble the snippets into a flat blob at 0x401000
gcc -m32 -c "$here/snippets.S" -o "$build/snippets.o"
ld -m elf_i386 -Ttext=0x401000 -e t_add32 -o "$build/snippets.elf" "$build/snippets.o"
objcopy -O binary -j .text "$build/snippets.elf" "$build/snippets.bin"
entries="$(nm "$build/snippets.elf" | awk '$2 == "T" && $3 ~ /^[th]_/ { printf "%s%s=%s", sep, $1, $3; sep = "," }')"

# ---- 2. native reference (x86 hosts with 32-bit support only)
have_ref=0
if gcc -m32 -O1 -ffreestanding -fno-builtin -fno-stack-protector -fno-pic -no-pie -nostdlib -static \
        -fno-asynchronous-unwind-tables -mno-sse -mfpmath=387 -Wall \
        "$here/ref_main.c" "$here/snippets.S" -o "$build/ref32" 2>"$build/ref32.log" \
        && "$build/ref32" > "$build/ref.txt" 2>/dev/null; then
    have_ref=1
    if [ "$update" = 1 ]; then
        cp "$build/ref.txt" "$here/expected.txt"
        echo "expected.txt updated from the native reference"
    elif ! cmp -s "$build/ref.txt" "$here/expected.txt"; then
        echo "FAIL: expected.txt is stale: it differs from the native reference (run with --update)" >&2
        exit 1
    fi
else
    echo "note: no native 32-bit reference on this machine; using the committed expected.txt"
fi

# ---- 3. lift and run, with and without the flag-liveness pass
status=0
for mode in liveness noliveness; do
    gen="$build/gen_$mode"
    flags=""
    [ "$mode" = noliveness ] && flags="--no-flag-liveness"
    python3 "$recomp/lift/lift.py" --raw "$build/snippets.bin" --base 0x401000 --entries "$entries" \
        --out "$gen" $flags > "$gen.report.txt"
    if grep -q "^trapped mnemonics    [1-9]" "$gen.report.txt"; then
        echo "FAIL: the lifter trapped instructions in the snippets:" >&2
        sed -n '/^trapped/,/^time/p' "$gen.report.txt" >&2
        exit 1
    fi
    rt_srcs="$(ls "$recomp"/runtime/*.c | grep -v '/main\.c$')"
    # shellcheck disable=SC2086
    "$cc" -std=gnu11 -O1 -fno-strict-aliasing -fwrapv -foptimize-sibling-calls -w ${EXTRA_CFLAGS:-} \
        -I"$recomp/runtime" -I"$gen" -I"$here" \
        -DRT_NO_SDL "$gen"/chunk_*.c "$gen/tables.c" $rt_srcs "$here/lifted_main.c" -lm -pthread \
        -o "$out/lifted_$mode"
    run=("$out/lifted_$mode")
    [ -n "$sysroot" ] && run=(qemu-aarch64 -L "$sysroot" "$out/lifted_$mode")
    if ! "${run[@]}" "$build/snippets.bin" > "$out/$mode.txt"; then
        echo "FAIL: lifted harness ($mode) exited with an error" >&2
        status=1
    fi
    if cmp -s "$out/$mode.txt" "$here/expected.txt"; then
        echo "PASS  $target/$mode: $(wc -l < "$out/$mode.txt") tests, $(awk -F'[ =]' '{ n += $3 } END { print n }' "$out/$mode.txt") vectors match"
    else
        echo "FAIL  $target/$mode: output differs from expected.txt" >&2
        diff "$here/expected.txt" "$out/$mode.txt" | head -20 >&2 || true
        if [ "$have_ref" = 1 ]; then
            "$build/ref32" -v > "$build/ref_verbose.txt"
            "${run[@]}" "$build/snippets.bin" -v > "$out/${mode}_verbose.txt" || true
            echo "first differing vectors (native reference '<' vs lifted '>'):" >&2
            diff "$build/ref_verbose.txt" "$out/${mode}_verbose.txt" | head -24 >&2 || true
        fi
        status=1
    fi
done
exit $status
