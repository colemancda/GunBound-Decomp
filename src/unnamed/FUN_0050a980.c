/* FUN_0050a980 - 0x0050a980 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_0050a980(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  puVar1 = g_gameStateVTableArray[7];
  if (param_2 == 0) {
    if (param_3 == 0) {
      uVar2 = *param_1;
      uVar3 = 0x14;
    }
    else if (param_3 == 2) {
      uVar2 = *param_1;
      uVar3 = 0x16;
    }
    else {
      if (param_3 != 3) goto LAB_0050a9f8;
      uVar2 = *param_1;
      uVar3 = 0x1a;
    }
    FUN_004f2da0(0,uVar2,uVar3);
  }
  else if ((param_2 == 0x2000) && (param_3 == 0)) {
    *(undefined4 *)(g_gameStateVTableArray[7] + 0x454) = param_4;
    FUN_0044b0b0(puVar1);
    RefreshConnectionStatusLabel(param_1);
    Widget_OnCommandDefault(0x2000,0,param_4);
    return;
  }
LAB_0050a9f8:
  Widget_OnCommandDefault(param_2,param_3,param_4);
  return;
}

