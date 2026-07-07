/* FUN_004e7560 - 0x004e7560 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004e7560(undefined4 param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  uint unaff_ESI;
  uint uVar4;
  undefined4 *puVar5;
  
  if ((int)unaff_ESI < 8) {
    if (7 < unaff_ESI) {
                    /* WARNING: Subroutine does not return */
      FUN_00426460();
    }
    iVar2 = (unaff_ESI >> 5) * 4;
    uVar4 = ~(1 << ((byte)unaff_ESI & 0x1f));
    *(uint *)(iVar2 + 0x140 + param_2) = *(uint *)(iVar2 + 0x140 + param_2) & uVar4;
    puVar1 = (uint *)(iVar2 + 0x138 + param_2);
    *puVar1 = *puVar1 & uVar4;
    iVar2 = unaff_ESI * 0x200 + param_2;
    puVar5 = (undefined4 *)(iVar2 + 0x42de0);
    for (iVar3 = 0x80; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    puVar5 = (undefined4 *)(iVar2 + 0x40bd8);
    for (iVar3 = 0x80; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    *(undefined1 *)(unaff_ESI + 0x3c0 + param_2) = 0;
    *(undefined1 *)(unaff_ESI + 0x3c8 + param_2) = 0;
    *(undefined1 *)(unaff_ESI + 0x454e4 + param_2) = 0;
  }
  return;
}

