/* FUN_00426a60 - 0x00426a60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00426a60(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  uStack_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00537a58;
  *unaff_FS_OFFSET = &uStack_c;
  FUN_00405510(param_1);
  local_4 = 0;
  iVar1 = (**(code **)(DAT_005b1444 + 0xc))();
  *(int *)(param_1 + 4) = iVar1 + 0x10;
  *(undefined4 *)(param_1 + 0xc) = param_2;
  *unaff_FS_OFFSET = uStack_c;
  return param_1;
}

