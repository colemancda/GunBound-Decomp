/* BlitMobilePart - 0x004dca80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall BlitMobilePart(undefined4 param_1,uint param_2,int param_3,int param_4)

{
  int iVar1;
  uint in_EAX;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  uint uVar8;
  undefined4 *puVar9;
  int iVar10;
  undefined4 *puVar11;
  
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar8 = *(uint *)(iVar2 + 4);
  if (uVar8 <= in_EAX) {
    while (uVar8 != in_EAX) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar8 = *(uint *)(iVar2 + 4);
      if (in_EAX < uVar8) {
        return;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar8 = *(uint *)(iVar2 + 8);
    if (uVar8 <= param_2) {
      while (uVar8 != param_2) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar8 = *(uint *)(iVar2 + 8);
        if (param_2 < uVar8) {
          return;
        }
      }
      iVar6 = *(int *)(iVar2 + 0x20);
      iVar3 = *(int *)(iVar2 + 0x28) + 0x40;
      uVar8 = *(int *)(iVar2 + 0x2c) + 0x70;
      if (in_EAX == 0x14b4) {
        uVar8 = *(int *)(iVar2 + 0x2c) + 0x40;
      }
      iVar1 = iVar6 + iVar3;
      if ((((0 < iVar1) && (iVar3 < 0x80)) && (*(int *)(iVar2 + 0x24) + uVar8 != 0)) &&
         ((int)uVar8 < 0x80)) {
        uVar5 = -uVar8;
        puVar4 = (undefined4 *)(*(int *)(iVar2 + 0x34) + iVar6 * (((int)uVar5 < 0) - 1 & uVar5) * 2)
        ;
        iVar10 = *(int *)(iVar2 + 0x24) - (uVar5 & ((int)uVar5 < 0) - 1);
        uVar8 = ((int)uVar8 < 0) - 1 & uVar8;
        if (0x7f < (int)(iVar10 + uVar8)) {
          iVar10 = 0x7f - uVar8;
        }
        if (iVar3 < 0) {
          puVar4 = (undefined4 *)((int)puVar4 + iVar3 * -2);
          iVar3 = 0;
          iVar6 = iVar1;
        }
        if (0x7f < iVar6 + iVar3) {
          iVar6 = 0x7f - iVar3;
        }
        if (0 < iVar10) {
          puVar7 = (undefined4 *)(uVar8 * param_4 + param_3 + iVar3 * 2);
          param_3 = iVar10;
          do {
            uVar5 = (iVar6 * 2 < 0) - 1 & iVar6 * 2;
            puVar9 = puVar4;
            puVar11 = puVar7;
            for (uVar8 = uVar5 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
              *puVar11 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar11 = puVar11 + 1;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined1 *)puVar11 = *(undefined1 *)puVar9;
              puVar9 = (undefined4 *)((int)puVar9 + 1);
              puVar11 = (undefined4 *)((int)puVar11 + 1);
            }
            puVar4 = (undefined4 *)((int)puVar4 + *(int *)(iVar2 + 0x20) * 2);
            puVar7 = (undefined4 *)((int)puVar7 + param_4);
            param_3 = param_3 + -1;
          } while (param_3 != 0);
        }
      }
    }
  }
  return;
}

