import os

# See tools/README.md's "Diffing a function against the original" section.
#
# This drives asm-differ's "-e" (ELF-symbol) mode, which needs no relinked/
# address-matched image: `myimg` can be any compiled .obj, and asm-differ
# disassembles just the one named symbol out of it, lined up against the
# original binary's real bytes at a given VA range. Point GB_MYIMG at
# whatever .obj you just compiled before running diff.py.
#
# Example:
#   GB_MYIMG=build/GetBit_cmp.obj \
#     tools/.venv-win/Scripts/python.exe tools/asm-differ/diff.py \
#     -e _lzhuf_get_bit 0x4ea120 0x4ea1a4


def apply(config, args):
    config["baseimg"] = "orig/GunBound.gme"
    config["myimg"] = os.environ.get("GB_MYIMG", "build/GetBit_cmp.obj")
    config["source_directories"] = ["src"]
    config["arch"] = "x86"
    config["objdump_executable"] = r"C:\Program Files\LLVM\bin\llvm-objdump.exe"
