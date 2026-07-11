/* FUN_00409d10 - 0x00409d10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __thiscall FUN_00409d10(int param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00537aa5;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if (param_2[0xb] == 0) {
    piVar1 = _malloc(param_2[9] * 0x10 + 4);
    if (piVar1 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    *piVar1 = param_2[10];
    param_2[10] = (int)piVar1;
    iVar3 = param_2[9];
    piVar1 = piVar1 + iVar3 * 4 + -3;
    if (-1 < iVar3 + -1) {
      do {
        piVar1[2] = param_2[0xb];
        param_2[0xb] = (int)piVar1;
        piVar1 = piVar1 + -4;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
  }
  iVar3 = param_2[0xb];
  param_2[0xb] = *(int *)(iVar3 + 8);
  local_8 = 1;
  FUN_00405510(iVar3);
  local_8 = 0xffffffff;
  *(undefined4 *)(iVar3 + 0xc) = param_4;
  param_2[1] = param_2[1] + 1;
  *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(*param_2 + param_1 * 4);
  *(int *)(*param_2 + param_1 * 4) = iVar3;
  if (((uint)param_2[6] < (uint)param_2[1]) && (param_2[8] == 0)) {
    uVar2 = FUN_00500e30();
    FUN_00409e20(param_2,uVar2);
  }
  *unaff_FS_OFFSET = local_10;
  return iVar3;
}

