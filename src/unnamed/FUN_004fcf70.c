/* FUN_004fcf70 - 0x004fcf70 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004fcf70(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int unaff_EBX;
  int iVar2;
  int iVar3;
  int *unaff_EDI;
  undefined4 auStack_190 [100];
  
  iVar2 = 0;
  if (100 < param_1) {
    param_1 = 100;
  }
  iVar3 = 0;
  if (0 < param_1) {
    do {
      cVar1 = (**(code **)(*unaff_EDI + 0x3c))(*(undefined4 *)(unaff_EBX + iVar3 * 4));
      if (cVar1 == '\0') {
        auStack_190[iVar2] = *(undefined4 *)(unaff_EBX + iVar3 * 4);
        iVar2 = iVar2 + 1;
      }
      else {
        FUN_004fe110(unaff_EDI + 0xb,*(undefined4 *)(unaff_EBX + iVar3 * 4),param_2,param_3,param_4)
        ;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < param_1);
    if (0 < iVar2) {
      FUN_004fd030();
      FUN_00502650(unaff_EDI,iVar2,auStack_190,param_3,param_4);
    }
  }
  return;
}

