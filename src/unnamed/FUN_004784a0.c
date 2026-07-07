/* FUN_004784a0 - 0x004784a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004784a0(undefined4 param_1,uint param_2,int param_3,int param_4)

{
  int iVar1;
  uint in_EAX;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  int iVar10;
  undefined4 *puVar11;
  
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar8 = *(uint *)(iVar2 + 4);
  if (uVar8 <= param_2) {
    while (uVar8 != param_2) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar8 = *(uint *)(iVar2 + 4);
      if (param_2 < uVar8) {
        return;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar8 = *(uint *)(iVar2 + 8);
    if (uVar8 <= in_EAX) {
      while (uVar8 != in_EAX) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar8 = *(uint *)(iVar2 + 8);
        if (in_EAX < uVar8) {
          return;
        }
      }
      iVar10 = *(int *)(iVar2 + 0x20);
      iVar5 = *(int *)(iVar2 + 0x28) + 0x20;
      iVar1 = iVar10 + iVar5;
      uVar8 = *(int *)(iVar2 + 0x2c) + 0x30;
      if ((((0 < iVar1) && (iVar5 < 0x40)) && (*(int *)(iVar2 + 0x24) + uVar8 != 0)) &&
         ((int)uVar8 < 0x40)) {
        uVar4 = -uVar8;
        puVar3 = (undefined4 *)
                 (*(int *)(iVar2 + 0x34) + iVar10 * (((int)uVar4 < 0) - 1 & uVar4) * 2);
        iVar7 = *(int *)(iVar2 + 0x24) - (uVar4 & ((int)uVar4 < 0) - 1);
        uVar8 = ((int)uVar8 < 0) - 1 & uVar8;
        if (0x3f < (int)(iVar7 + uVar8)) {
          iVar7 = 0x3f - uVar8;
        }
        if (iVar5 < 0) {
          puVar3 = (undefined4 *)((int)puVar3 + iVar5 * -2);
          iVar5 = 0;
          iVar10 = iVar1;
        }
        if (0x3f < iVar10 + iVar5) {
          iVar10 = 0x3f - iVar5;
        }
        if (0 < iVar7) {
          puVar6 = (undefined4 *)(uVar8 * param_4 + param_3 + iVar5 * 2);
          param_3 = iVar7;
          do {
            uVar4 = (iVar10 * 2 < 0) - 1 & iVar10 * 2;
            puVar9 = puVar3;
            puVar11 = puVar6;
            for (uVar8 = uVar4 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
              *puVar11 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar11 = puVar11 + 1;
            }
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
              *(undefined1 *)puVar11 = *(undefined1 *)puVar9;
              puVar9 = (undefined4 *)((int)puVar9 + 1);
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

