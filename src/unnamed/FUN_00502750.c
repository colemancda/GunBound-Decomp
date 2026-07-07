/* FUN_00502750 - 0x00502750 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00502750(int param_1)

{
  int iVar1;
  undefined4 in_EAX;
  int local_4;
  
  iVar1 = *(int *)(param_1 + 4);
  local_4 = param_1;
  if ((iVar1 != 0) &&
     ((uint)((*(int *)(param_1 + 8) - iVar1) / 0x12) <
      (uint)((*(int *)(param_1 + 0xc) - iVar1) / 0x12))) {
    iVar1 = *(int *)(param_1 + 8);
    FUN_00504110(param_1);
    *(int *)(param_1 + 8) = iVar1 + 0x12;
    return;
  }
  FUN_005029b0(&local_4,*(undefined4 *)(param_1 + 8),in_EAX);
  return;
}

