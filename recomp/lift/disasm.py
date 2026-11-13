#!/usr/bin/env python3
"""Linear disassembly helper: dis.py <pe> <hexaddr> [count]  (debugging aid for the lifter)."""
import sys

import capstone
import pefile


def main():
    pe = pefile.PE(sys.argv[1])
    base = pe.OPTIONAL_HEADER.ImageBase
    data = pe.get_memory_mapped_image()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    for spec in sys.argv[2].split(","):
        addr = int(spec, 16)
        count = int(sys.argv[3]) if len(sys.argv) > 3 else 20
        o = addr - base
        n = 0
        for i in md.disasm(data[o:o + count * 15], addr):
            print("%08x  %-20s %s %s" % (i.address, i.bytes.hex(), i.mnemonic, i.op_str))
            n += 1
            if n >= count:
                break
        print()


if __name__ == "__main__":
    main()
