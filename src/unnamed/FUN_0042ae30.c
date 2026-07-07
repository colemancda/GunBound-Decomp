/* FUN_0042ae30 - 0x0042ae30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __thiscall FUN_0042ae30(int *param_1,undefined4 param_2)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00537a95;
  *unaff_FS_OFFSET = &local_c;
  uVar1 = param_1[1];
  if ((uint)param_1[2] <= uVar1) {
    cVar2 = FUN_0042af40();
    if (cVar2 == '\0') {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x8007000e);
    }
  }
  iVar3 = uVar1 * 0x450 + *param_1;
  local_4 = 0;
  if (iVar3 != 0) {
    FUN_0042aeb0(iVar3,param_2);
  }
  param_1[1] = param_1[1] + 1;
  *unaff_FS_OFFSET = local_c;
  return uVar1;
}

