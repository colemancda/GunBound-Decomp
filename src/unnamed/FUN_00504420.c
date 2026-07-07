/* FUN_00504420 - 0x00504420 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00504420(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int unaff_EBX;
  undefined4 *puVar5;
  
  FUN_00504730();
  puVar1 = *(undefined4 **)(unaff_EBX + 0x10);
  uVar2 = *puVar1;
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[0x5de] = param_1[0x5dc];
    uVar4 = param_1[0x5dc];
    puVar5 = puVar1 + 2;
    for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar5 = *param_1;
      param_1 = param_1 + 1;
      puVar5 = puVar5 + 1;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined1 *)puVar5 = *(undefined1 *)param_1;
      param_1 = (undefined4 *)((int)param_1 + 1);
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
  }
  *(undefined4 *)(unaff_EBX + 0x10) = uVar2;
  *puVar1 = param_3;
  puVar1[1] = param_2;
  *(int *)(unaff_EBX + 8) = *(int *)(unaff_EBX + 8) + 1;
  return;
}

