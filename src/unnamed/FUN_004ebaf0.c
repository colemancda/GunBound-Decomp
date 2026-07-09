/* FUN_004ebaf0 - 0x004ebaf0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_004ebaf0(uint param_1,uint param_2)

{
  uint uVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  if (uVar1 <= param_2) {
    while (uVar1 != param_2) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar1 = *(uint *)(iVar2 + 4);
      if (param_2 < uVar1) {
        return;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar1 = *(uint *)(iVar2 + 8);
    if (uVar1 <= param_1) {
      while (uVar1 != param_1) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar1 = *(uint *)(iVar2 + 8);
        if (param_1 < uVar1) {
          return;
        }
      }
      uVar4 = *(undefined4 *)(iVar2 + 0x20);
      iVar5 = in_EAX + *(int *)(iVar2 + 0x2c);
      iVar3 = *(int *)(iVar2 + 0x24) - ((DAT_00793534 - iVar5 < 0) - 1 & DAT_00793534 - iVar5);
      if (iVar5 < DAT_00793534) {
        iVar5 = DAT_00793534;
      }
      if (DAT_0056df34 < iVar3 + iVar5) {
        iVar3 = (DAT_0056df34 - iVar5) + 1;
      }
      if (0 < iVar3) {
        do {
          FUN_004eba80(uVar4);
          uVar4 = *(undefined4 *)(iVar2 + 0x20);
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
    }
  }
  return;
}

