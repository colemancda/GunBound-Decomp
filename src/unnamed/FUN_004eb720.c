/* FUN_004eb720 - 0x004eb720 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004eb720(int param_1,int param_2,undefined2 param_3)

{
  int in_EAX;
  int iVar1;
  
  if (((DAT_0079352c != 0) && (param_2 <= DAT_0056df30)) && (DAT_00793530 <= param_2)) {
    if (param_1 < DAT_00793534) {
      in_EAX = in_EAX + (param_1 - DAT_00793534);
      param_1 = DAT_00793534;
    }
    if (DAT_0056df34 < param_1 + in_EAX) {
      in_EAX = (DAT_0056df34 - param_1) + 1;
    }
    if ((0 < in_EAX) && (iVar1 = DAT_0079352c + (DAT_005b3620 * param_1 + param_2) * 2, 0 < in_EAX))
    {
      do {
        FUN_004f2740(iVar1,param_3,1);
        in_EAX = in_EAX + -1;
        iVar1 = iVar1 + DAT_005b3620 * 2;
      } while (in_EAX != 0);
    }
  }
  return;
}

