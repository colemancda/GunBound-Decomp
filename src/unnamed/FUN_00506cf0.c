/* FUN_00506cf0 - 0x00506cf0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00506cf0(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (param_2 == 0) {
    if (param_3 == 0) {
      FUN_004f2da0(0,*param_1,0x1e);
    }
    else if (param_3 == 1) goto LAB_00506d7f;
  }
  else {
    if (param_2 == 0x1000) {
LAB_00506d7f:
      FUN_00506bf0(param_1);
      Widget_OnCommandDefault(param_2,param_3,param_4);
      return;
    }
    if (param_2 == 0x1001) {
      uVar1 = *param_1;
      uVar2 = DAT_00795070 + 1 & 0x800001ff;
      if ((int)uVar2 < 0) {
        uVar2 = (uVar2 - 1 | 0xfffffe00) + 1;
      }
      if (uVar2 != DAT_00795074) {
        *(undefined4 *)(&DAT_00795078 + DAT_00795070 * 4) = 0;
        *(undefined4 *)(&DAT_00795878 + DAT_00795070 * 4) = uVar1;
        *(undefined4 *)(&DAT_00796078 + DAT_00795070 * 4) = 0x1e;
        DAT_00795070 = uVar2;
        Widget_OnCommandDefault(0x1001,param_3,param_4);
        return;
      }
    }
  }
  Widget_OnCommandDefault(param_2,param_3,param_4);
  return;
}

