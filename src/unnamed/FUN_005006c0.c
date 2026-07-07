/* FUN_005006c0 - 0x005006c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_005006c0(int param_1,undefined4 *param_2)

{
  int iVar1;
  
  FUN_00500f90();
  *param_2 = *(undefined4 *)(param_1 + 0x10);
  iVar1 = *(int *)(param_1 + 8) + -1;
  *(undefined4 **)(param_1 + 0x10) = param_2;
  *(int *)(param_1 + 8) = iVar1;
  if (iVar1 == 0) {
    FUN_004ff6d0();
  }
  return;
}

