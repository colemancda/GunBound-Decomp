/* FUN_00500c00 - 0x00500c00 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00500c00(undefined4 *param_1,int param_2,int param_3)

{
  void *pvVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00537710;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if ((void *)*param_1 != (void *)0x0) {
    _free((void *)*param_1);
    *param_1 = 0;
  }
  if (param_3 != '\0') {
    local_8 = 0;
    pvVar1 = operator_new(param_2 * 4);
    *param_1 = pvVar1;
    puVar5 = (undefined4 *)*param_1;
    iVar4 = param_2;
    if (puVar5 == (undefined4 *)0x0) {
      *unaff_FS_OFFSET = local_10;
      return 0;
    }
    for (; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
  }
  param_1[2] = param_2;
  uVar2 = FUN_0053753c();
  param_1[6] = uVar2;
  uVar3 = FUN_0053753c();
  param_1[7] = uVar3;
  if (uVar3 < 0x11) {
    param_1[7] = 0;
  }
  *unaff_FS_OFFSET = local_10;
  return 1;
}

