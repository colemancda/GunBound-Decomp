/* FUN_00500440 - 0x00500440 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00500440(int *param_1,uint param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_005377d0;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if (param_2 == 0) {
    param_2 = FUN_00500e30();
  }
  if (param_2 != param_1[2]) {
    if (*param_1 == 0) {
      FUN_00500c00(param_1,param_2,0);
      *unaff_FS_OFFSET = local_10;
      return;
    }
    local_8 = 0;
    puVar2 = operator_new(param_2 * 4);
    local_8 = 0xffffffff;
    uVar6 = param_2;
    puVar5 = puVar2;
    if (puVar2 == (undefined4 *)0x0) {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x8007000e);
    }
    for (; uVar6 != 0; uVar6 = uVar6 - 1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    uVar6 = 0;
    if (param_1[2] != 0) {
      do {
        iVar3 = *(int *)(*param_1 + uVar6 * 4);
        while (iVar3 != 0) {
          uVar4 = *(uint *)(iVar3 + 0x18) % param_2;
          iVar1 = *(int *)(iVar3 + 0x14);
          *(undefined4 *)(iVar3 + 0x14) = puVar2[uVar4];
          puVar2[uVar4] = iVar3;
          iVar3 = iVar1;
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < (uint)param_1[2]);
    }
    _free((void *)*param_1);
    *param_1 = (int)puVar2;
    param_1[2] = param_2;
    iVar3 = FUN_0053753c();
    param_1[6] = iVar3;
    uVar6 = FUN_0053753c();
    param_1[7] = uVar6;
    if (uVar6 < 0x11) {
      param_1[7] = 0;
    }
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

