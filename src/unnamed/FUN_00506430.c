/* FUN_00506430 - 0x00506430 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00506430(int param_1,int param_2,int param_3,undefined4 param_4)

{
  if (param_2 == 0) {
    if (param_3 == 0) {
      FUN_00402cf0(&DAT_00e53e88);
    }
    else if (param_3 != 1) goto LAB_00506460;
    *(undefined1 *)(param_1 + 0x1d) = 1;
  }
LAB_00506460:
  FUN_0050eb10(param_2,param_3,param_4);
  return;
}

