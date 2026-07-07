/* FUN_00504190 - 0x00504190 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00504190(undefined4 param_1,int param_2,int *param_3)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined1 local_8;
  undefined3 uStack_7;
  
  puStack_c = &LAB_00537abd;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  uStack_7 = 0;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    local_8 = 1;
    if (param_3 != (int *)0x0) {
      iVar1 = FUN_0043de10();
      *param_3 = iVar1 + 0x10;
      local_8 = 2;
      iVar1 = FUN_0043de10();
      param_3[1] = iVar1 + 0x10;
    }
    param_3 = param_3 + 2;
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

