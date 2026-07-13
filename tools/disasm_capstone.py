#!/usr/bin/env python3
"""Disassemble a VA range from a PE via pefile+capstone.

Workaround for orig/GunBound.gme having a corrupted COFF
PointerToSymbolTable/NumberOfSymbols pair that makes `objdump -d` abort
with "file truncated" on some address ranges - pefile/capstone don't
touch the symbol table at all, so they're unaffected.

Usage: python3 tools/disasm_capstone.py <path-to-pe> <start-va-hex> <end-va-hex>
  e.g. python3 tools/disasm_capstone.py orig/GunBound.gme 0x50d200 0x50d54e

Requires: pip3 install --break-system-packages capstone pefile
"""
import sys
import pefile
import capstone

path = sys.argv[1]
start_va = int(sys.argv[2], 16)
end_va = int(sys.argv[3], 16)

pe = pefile.PE(path, fast_load=True)
image_base = pe.OPTIONAL_HEADER.ImageBase

data = None
for section in pe.sections:
    va = image_base + section.VirtualAddress
    size = max(section.Misc_VirtualSize, section.SizeOfRawData)
    if va <= start_va < va + size:
        offset_in_section = start_va - va
        data = section.get_data()[offset_in_section: offset_in_section + (end_va - start_va)]
        break

if data is None:
    print("Address not found in any section")
    sys.exit(1)

md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = False
for insn in md.disasm(data, start_va):
    print(f"{insn.address:08x}:\t{insn.mnemonic}\t{insn.op_str}")
