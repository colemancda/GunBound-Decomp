/* FUN_00506e10 - 0x00506e10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00506e10(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = DAT_007934e8;
  if (param_2 == 0) {
    if (param_3 == 0) {
      *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x1078;
      *(undefined4 *)(iVar1 + 0x44d0) = 6;
      SendOutgoingPacket(iVar1);
    }
    else if (param_3 != 1) goto LAB_00506e51;
    *(undefined1 *)(param_1 + 0x1d) = 1;
  }
LAB_00506e51:
  Widget_OnCommandDefault(param_2,param_3,param_4);
  return;
}

