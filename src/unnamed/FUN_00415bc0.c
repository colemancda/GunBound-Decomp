/* FUN_00415bc0 - 0x00415bc0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __fastcall FUN_00415bc0(int *param_1)

{
  int iVar1;
  uint uVar2;
  char cVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00537a95;
  *unaff_FS_OFFSET = &local_c;
  uVar2 = param_1[1];
  if ((uint)param_1[2] <= uVar2) {
    cVar3 = FUN_0050ed30();
    if (cVar3 == '\0') {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x8007000e);
    }
  }
  iVar1 = *param_1 + uVar2 * 4;
  local_4 = 0;
  if (iVar1 != 0) {
    FUN_00405510(iVar1);
  }
  param_1[1] = param_1[1] + 1;
  *unaff_FS_OFFSET = local_c;
  return uVar2;
}

