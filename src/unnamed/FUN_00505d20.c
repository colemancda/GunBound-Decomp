/* FUN_00505d20 - 0x00505d20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00505d20(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_2 == 0) {
    if (param_3 == 0) {
      *(undefined1 *)(param_1 + 0x1d) = 1;
    }
    else {
      if (param_3 == 1) {
        FUN_00508b90();
        FUN_0050eb10(0,1,param_4);
        return;
      }
      if ((param_3 == 2) && (*(int *)(param_1 + 0x90) != -1)) {
        iVar1 = FUN_00401c10();
        if (iVar1 != 0) {
          FUN_00508ea0(&DAT_00e53c40);
          FUN_0050eb10(0,2,param_4);
          return;
        }
      }
    }
  }
  else if ((param_2 == 0x2000) && (param_3 == 0)) {
    DAT_00e54da8 = param_4;
    FUN_0050eb10(0x2000,0,param_4);
    return;
  }
  FUN_0050eb10(param_2,param_3,param_4);
  return;
}

