/* FUN_00503710 - 0x00503710 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int * FUN_00503710(int *param_1)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00537a58;
  *unaff_FS_OFFSET = &local_c;
  iVar1 = FUN_0043de10();
  *param_1 = iVar1 + 0x10;
  local_4 = 0;
  iVar1 = FUN_0043de10();
  param_1[1] = iVar1 + 0x10;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

