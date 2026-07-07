/* FUN_004a27d0 - 0x004a27d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004a27d0(undefined4 param_1,uint param_2,int param_3,int param_4)

{
  int iVar1;
  uint in_EAX;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  undefined4 *puVar8;
  uint uVar9;
  int iVar10;
  undefined4 *puVar11;
  
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar7 = *(uint *)(iVar2 + 4);
  if (uVar7 <= param_2) {
    while (uVar7 != param_2) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar7 = *(uint *)(iVar2 + 4);
      if (param_2 < uVar7) {
        return;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar7 = *(uint *)(iVar2 + 8);
    if (uVar7 <= in_EAX) {
      while (uVar7 != in_EAX) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar7 = *(uint *)(iVar2 + 8);
        if (in_EAX < uVar7) {
          return;
        }
      }
      iVar4 = *(int *)(iVar2 + 0x20);
      iVar5 = *(int *)(iVar2 + 0x28) + 0x2a;
      iVar1 = iVar4 + iVar5;
      uVar7 = *(int *)(iVar2 + 0x2c) + 0x2a;
      if ((((0 < iVar1) && (iVar5 < 0x54)) && (*(int *)(iVar2 + 0x24) + uVar7 != 0)) &&
         ((int)uVar7 < 0x54)) {
        uVar9 = -uVar7;
        puVar3 = (undefined4 *)(*(int *)(iVar2 + 0x34) + iVar4 * (((int)uVar9 < 0) - 1 & uVar9) * 2)
        ;
        iVar10 = *(int *)(iVar2 + 0x24) - (((int)uVar9 < 0) - 1 & uVar9);
        uVar7 = ((int)uVar7 < 0) - 1 & uVar7;
        if (0x53 < (int)(iVar10 + uVar7)) {
          iVar10 = 0x53 - uVar7;
        }
        if (iVar5 < 0) {
          puVar3 = (undefined4 *)((int)puVar3 + iVar5 * -2);
          iVar5 = 0;
          iVar4 = iVar1;
        }
        if (0x53 < iVar4 + iVar5) {
          iVar4 = 0x53 - iVar5;
        }
        if (0 < iVar10) {
          puVar6 = (undefined4 *)(uVar7 * param_4 + param_3 + iVar5 * 2);
          param_3 = iVar10;
          do {
            uVar9 = (iVar4 * 2 < 0) - 1 & iVar4 * 2;
            puVar8 = puVar3;
            puVar11 = puVar6;
            for (uVar7 = uVar9 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
              *puVar11 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar11 = puVar11 + 1;
            }
            for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
              *(undefined1 *)puVar11 = *(undefined1 *)puVar8;
              puVar8 = (undefined4 *)((int)puVar8 + 1);
              puVar11 = (undefined4 *)((int)puVar11 + 1);
            }
            puVar3 = (undefined4 *)((int)puVar3 + *(int *)(iVar2 + 0x20) * 2);
            puVar6 = (undefined4 *)((int)puVar6 + param_4);
            param_3 = param_3 + -1;
          } while (param_3 != 0);
        }
      }
    }
  }
  return;
}

