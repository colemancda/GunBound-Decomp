/* FUN_0044c7b0 - 0x0044c7b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined1 __fastcall FUN_0044c7b0(uint param_1,int *param_2)

{
  char cVar1;
  int in_EAX;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  if (in_EAX != -1) {
    param_2[3] = in_EAX;
  }
  if (param_1 == 0) {
    iVar4 = *param_2;
    if (iVar4 != 0) {
      for (iVar3 = param_2[1]; iVar3 != 0; iVar3 = iVar3 + -1) {
        FUN_00426810(iVar4);
        iVar4 = iVar4 + 0x450;
      }
      _free((void *)*param_2);
      *param_2 = 0;
    }
    param_2[1] = 0;
    param_2[2] = 0;
    return 1;
  }
  if ((uint)param_2[2] < param_1) {
    cVar1 = FUN_0042af40();
    if (cVar1 == '\0') {
      return 0;
    }
    uVar2 = param_2[1];
  }
  else {
    uVar2 = param_2[1];
    if (param_1 <= uVar2) {
      if (param_1 < uVar2) {
        FUN_00426700();
        param_2[1] = param_1;
        return 1;
      }
      goto LAB_0044c85f;
    }
  }
  FUN_0044c870(uVar2 * 0x450 + *param_2,param_1 - uVar2);
LAB_0044c85f:
  param_2[1] = param_1;
  return 1;
}

