/* FUN_00401fa0 - 0x00401fa0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00401fa0(void)

{
  undefined4 in_EAX;
  int iVar1;
  undefined1 *unaff_ESI;
  
  iVar1 = FUN_00401bb0(in_EAX);
  if (iVar1 != 0) {
    *(undefined1 *)(iVar1 + 0x30) = *unaff_ESI;
    if (*(short *)(unaff_ESI + 0xe) ==
        (ushort)((ushort)(unaff_ESI[0xb] ^ 0x73) + (ushort)(unaff_ESI[0xd] ^ 0x6b) +
                 (ushort)(unaff_ESI[9] ^ 0x6f) + (ushort)(unaff_ESI[10] ^ 0x6d) +
                 (ushort)(unaff_ESI[0xc] ^ 0x69) + (ushort)(unaff_ESI[8] ^ 99))) {
      *(undefined4 *)(iVar1 + 0x31) = *(undefined4 *)(unaff_ESI + 8);
      *(undefined4 *)(iVar1 + 0x35) = *(undefined4 *)(unaff_ESI + 0xc);
      *(undefined4 *)(iVar1 + 0x39) = *(undefined4 *)(unaff_ESI + 0x10);
      *(undefined4 *)(iVar1 + 0x3d) = *(undefined4 *)(unaff_ESI + 0x14);
    }
  }
  return;
}

