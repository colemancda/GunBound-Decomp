/* FUN_00502920 - 0x00502920 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00502920(undefined4 param_1)

{
  int iVar1;
  int in_EAX;
  
  iVar1 = *(int *)(in_EAX + 4);
  if ((iVar1 != 0) &&
     ((uint)((*(int *)(in_EAX + 8) - iVar1) / 0x1e) <
      (uint)((*(int *)(in_EAX + 0xc) - iVar1) / 0x1e))) {
    iVar1 = *(int *)(in_EAX + 8);
    FUN_00504270(param_1);
    *(int *)(in_EAX + 8) = iVar1 + 0x1e;
    return;
  }
  FUN_00502b00(&param_1,*(undefined4 *)(in_EAX + 8),param_1);
  return;
}

