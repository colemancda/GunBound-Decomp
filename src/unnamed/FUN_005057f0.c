/* FUN_005057f0 - 0x005057f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_005057f0(int param_1,uint param_2,int param_3,undefined4 param_4)

{
  if (param_2 < 0x1002) {
    if (param_2 == 0x1001) {
LAB_0050584f:
      *(undefined1 *)(param_1 + 0x1d) = 1;
      Widget_OnCommandDefault(param_2,param_3,param_4);
      return;
    }
    if (param_2 == 0) {
      if (param_3 == 0) goto LAB_0050584f;
      if (param_3 == 3) {
        FUN_00505ad0(param_1);
        Widget_OnCommandDefault(0,3,param_4);
        return;
      }
    }
    else if (param_2 == 0x1000) {
      FUN_00505ad0(param_1);
      Widget_OnCommandDefault(0x1000,param_3,param_4);
      return;
    }
  }
  else if ((param_2 == 0x2000) && (param_3 == 0)) {
    *(undefined4 *)(param_1 + 0x1048) = param_4;
  }
  Widget_OnCommandDefault(param_2,param_3,param_4);
  return;
}

