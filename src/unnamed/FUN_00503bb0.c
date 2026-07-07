/* FUN_00503bb0 - 0x00503bb0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00503bb0(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int unaff_EBX;
  
  if (*(int *)(unaff_EBX + 0x294) != 0) {
    uVar2 = 0;
    if (*(uint *)(unaff_EBX + 0x298) != 0) {
      piVar4 = *(int **)(unaff_EBX + 0x290);
      do {
        if (*piVar4 != 0) {
          iVar3 = (*(int **)(unaff_EBX + 0x290))[uVar2];
          goto joined_r0x00503be3;
        }
        uVar2 = uVar2 + 1;
        piVar4 = piVar4 + 1;
      } while (uVar2 < *(uint *)(unaff_EBX + 0x298));
    }
  }
  iVar3 = 0;
joined_r0x00503be3:
  do {
    if (iVar3 == 0) {
      return;
    }
    iVar5 = 0;
    if ((iVar3 != 0) && (iVar5 = *(int *)(iVar3 + 0xa4), iVar5 == 0)) {
      uVar2 = *(uint *)(iVar3 + 0xa8) % *(uint *)(unaff_EBX + 0x298);
      do {
        uVar2 = uVar2 + 1;
        if (*(uint *)(unaff_EBX + 0x298) <= uVar2) break;
        iVar1 = *(int *)(*(int *)(unaff_EBX + 0x290) + uVar2 * 4);
        if (iVar1 != 0) {
          iVar5 = iVar1;
        }
      } while (iVar5 == 0);
    }
    FUN_00503a50(unaff_EBX,iVar3);
    iVar3 = iVar5;
  } while( true );
}

