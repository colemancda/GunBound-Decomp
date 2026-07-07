/* FUN_0044c370 - 0x0044c370 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_0044c370(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int unaff_EBX;
  int iVar4;
  
  iVar2 = DAT_005b3484;
  iVar1 = *(int *)(DAT_005b3484 + 0x44e24);
  uVar3 = 0;
  if (0 < iVar1) {
    iVar4 = 0;
    do {
      if (*(uint *)(iVar2 + 0x44e24) <= uVar3) {
LAB_0044c3c3:
                    /* WARNING: Subroutine does not return */
        FUN_004010c0(0x80070057);
      }
      if (unaff_EBX < *(int *)(*(int *)(iVar2 + 0x44e20) + 4 + iVar4)) {
        if (*(uint *)(iVar2 + 0x44e24) <= uVar3) goto LAB_0044c3c3;
        *(int *)(iVar4 + 4 + *(int *)(iVar2 + 0x44e20)) =
             *(int *)(iVar4 + 4 + *(int *)(iVar2 + 0x44e20)) + -1;
      }
      uVar3 = uVar3 + 1;
      iVar4 = iVar4 + 0x450;
    } while ((int)uVar3 < iVar1);
  }
  return;
}

