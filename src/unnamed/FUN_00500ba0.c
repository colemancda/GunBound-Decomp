/* FUN_00500ba0 - 0x00500ba0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00500ba0(int *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  int *unaff_EBX;
  int iVar4;
  
  puVar1 = (undefined4 *)*param_1;
  if (puVar1 == (undefined4 *)0x0) {
    iVar4 = 0;
  }
  else {
    iVar4 = puVar1[3];
    if (iVar4 == 0) {
      uVar3 = (uint)puVar1[4] % (uint)unaff_EBX[2];
      do {
        uVar3 = uVar3 + 1;
        if ((uint)unaff_EBX[2] <= uVar3) break;
        iVar2 = *(int *)(*unaff_EBX + uVar3 * 4);
        if (iVar2 != 0) {
          iVar4 = iVar2;
        }
      } while (iVar4 == 0);
    }
  }
  *param_1 = iVar4;
  *param_2 = *puVar1;
  *param_3 = puVar1[1];
  param_3[1] = puVar1[2];
  return;
}

