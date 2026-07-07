/* FUN_00505700 - 0x00505700 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00505700(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = param_3;
  if (param_2 != 0) {
    iVar1 = param_2 + -0x1000;
  }
  if (iVar1 == 0) {
    FUN_00505580(param_1);
  }
  else if (iVar1 == 1) {
    *(undefined1 *)(param_1 + 0x1d) = 1;
    FUN_0050eb10(param_2,param_3,param_4);
    return;
  }
  FUN_0050eb10(param_2,param_3,param_4);
  return;
}

