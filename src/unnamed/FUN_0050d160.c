/* FUN_0050d160 - 0x0050d160 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0050d160(int param_1,int param_2,undefined4 param_3)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 *puVar4;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_00537938;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  puVar3 = (undefined4 *)(**(code **)(DAT_005b1444 + 0xc))();
  puVar4 = puVar3 + 4;
  uStack_4 = 0;
  if ((param_1 == 0x2000) && (param_2 == 0)) {
    *(undefined4 *)(g_clientContext + 0x3b97c) = param_3;
  }
  FUN_0050eb10(param_1,param_2,param_3);
  uStack_4 = 0xffffffff;
  piVar1 = puVar3 + 3;
  LOCK();
  iVar2 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar2 == 1 || iVar2 + -1 < 0) {
    (**(code **)(*(int *)*puVar3 + 4))(puVar3,puVar4);
  }
  *unaff_FS_OFFSET = uStack_c;
  return;
}

