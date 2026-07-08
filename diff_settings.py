import os

# See tools/README.md's "Diffing a function against the original" section.
#
# This drives asm-differ's "-e" (ELF-symbol) mode, which needs no relinked/
# address-matched image: `myimg` can be any compiled .obj, and asm-differ
# disassembles just the one named symbol out of it, lined up against the
# original binary's real bytes at a given VA range. Point GB_MYIMG at
# whatever .obj you just compiled before running diff.py.
#
# Retargeted to run natively from the Mac side (originally configured for
# a Windows VM's Python 3.12 venv + llvm-objdump.exe - that setup was never
# actually exercised once the much faster Docker+Wine real-MSVC-7.1
# pipeline (tools/msvc-env/) replaced driving the VM interactively for
# compiling; this file just never got repointed until now). Uses the Mac's
# own /usr/bin/objdump (Xcode's, part of the standard toolchain - already
# confirmed to disassemble these x86 COFF .objs correctly by hand this
# session) and system python3 (colorama/cxxfilt/watchdog/Levenshtein
# installed via `pip3 install --break-system-packages`).
#
# Example, after compiling a .obj via tools/msvc-env/ (see that directory's
# README.md for the exact docker run invocation):
#   GB_MYIMG=build/GetBit_cmp.obj \
#     python3 tools/asm-differ/diff.py -e _lzhuf_get_bit 0x4ea120 0x4ea1a4


def apply(config, args):
    config["baseimg"] = "orig/GunBound.gme"
    config["myimg"] = os.environ.get("GB_MYIMG", "build/GetBit_cmp.obj")
    config["source_directories"] = ["src"]
    config["arch"] = "x86"
    # Must literally contain "llvm-" (not just resolve to LLVM's objdump
    # under the hood, e.g. via /usr/bin/objdump's symlink) - asm-differ
    # string-matches on the executable path to pick the right
    # --disassemble-symbols= flag spelling for this objdump version.
    config["objdump_executable"] = (
        "/Applications/Xcode.app/Contents/Developer/Toolchains/"
        "XcodeDefault.xctoolchain/usr/bin/llvm-objdump"
    )
