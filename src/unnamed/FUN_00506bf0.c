/* FUN_00506bf0 - 0x00506bf0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00506bf0(undefined4 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  uVar3 = FUN_0050e620();
  if (uVar3 != 0xffffffff) {
    if ((uint)param_1[4] <= uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x80070057);
    }
    pcVar5 = (char *)(*(int *)(param_1[3] + uVar3 * 4) + 0x38);
    pcVar4 = pcVar5;
    if (pcVar5 != (char *)0x0) {
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
    }
    FUN_004056c0(param_1 + 0x14,pcVar5);
  }
  uVar2 = *param_1;
  if (*(int *)(param_1[0x14] + -0xc) == 0) {
    uVar3 = DAT_00795070 + 1 & 0x800001ff;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffe00) + 1;
    }
    if (uVar3 != DAT_00795074) {
      *(undefined4 *)(&DAT_00795078 + DAT_00795070 * 4) = 0;
      *(undefined4 *)(&DAT_00795878 + DAT_00795070 * 4) = uVar2;
      *(undefined4 *)(&DAT_00796078 + DAT_00795070 * 4) = 0x1e;
      DAT_00795070 = uVar3;
      return CONCAT31((int3)(uVar3 >> 8),1);
    }
  }
  else {
    uVar3 = DAT_00795070 + 1 & 0x800001ff;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffe00) + 1;
    }
    if (uVar3 != DAT_00795074) {
      *(undefined4 *)(&DAT_00795078 + DAT_00795070 * 4) = 0;
      *(undefined4 *)(&DAT_00795878 + DAT_00795070 * 4) = uVar2;
      *(undefined4 *)(&DAT_00796078 + DAT_00795070 * 4) = 0x1f;
      DAT_00795070 = uVar3;
    }
  }
  return CONCAT31((int3)(uVar3 >> 8),1);
}

