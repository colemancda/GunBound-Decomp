/* FUN_00502800 - 0x00502800 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00502800(int param_1)

{
  int iVar1;
  undefined4 in_EAX;
  int local_4;
  
  iVar1 = *(int *)(param_1 + 4);
  local_4 = param_1;
  if ((iVar1 != 0) &&
     ((uint)((*(int *)(param_1 + 8) - iVar1) / 0x34) <
      (uint)((*(int *)(param_1 + 0xc) - iVar1) / 0x34))) {
    iVar1 = *(int *)(param_1 + 8);
    FUN_00504160(param_1);
    *(int *)(param_1 + 8) = iVar1 + 0x34;
    return;
  }
  FUN_00502a20(&local_4,*(undefined4 *)(param_1 + 8),in_EAX);
  return;
}

