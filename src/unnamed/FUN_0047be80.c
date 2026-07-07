/* FUN_0047be80 - 0x0047be80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0047be80(undefined4 param_1,uint param_2,int param_3,int param_4)

{
  int iVar1;
  uint in_EAX;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  uint uVar10;
  undefined4 *puVar11;
  
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar10 = *(uint *)(iVar2 + 4);
  if (uVar10 <= param_2) {
    while (uVar10 != param_2) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar10 = *(uint *)(iVar2 + 4);
      if (param_2 < uVar10) {
        return;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar10 = *(uint *)(iVar2 + 8);
    if (uVar10 <= in_EAX) {
      while (uVar10 != in_EAX) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar10 = *(uint *)(iVar2 + 8);
        if (in_EAX < uVar10) {
          return;
        }
      }
      iVar4 = *(int *)(iVar2 + 0x20);
      iVar5 = *(int *)(iVar2 + 0x28) + 0x10;
      iVar1 = iVar4 + iVar5;
      uVar10 = *(int *)(iVar2 + 0x2c) + 0x10;
      if ((((0 < iVar1) && (iVar5 < 0x20)) && (*(int *)(iVar2 + 0x24) + uVar10 != 0)) &&
         ((int)uVar10 < 0x80)) {
        uVar7 = -uVar10;
        puVar3 = (undefined4 *)(*(int *)(iVar2 + 0x34) + iVar4 * (((int)uVar7 < 0) - 1 & uVar7) * 2)
        ;
        iVar8 = *(int *)(iVar2 + 0x24) - (((int)uVar7 < 0) - 1 & uVar7);
        uVar10 = ((int)uVar10 < 0) - 1 & uVar10;
        if (0x1f < (int)(iVar8 + uVar10)) {
          iVar8 = 0x1f - uVar10;
        }
        if (iVar5 < 0) {
          puVar3 = (undefined4 *)((int)puVar3 + iVar5 * -2);
          iVar5 = 0;
          iVar4 = iVar1;
        }
        if (0x1f < iVar4 + iVar5) {
          iVar4 = 0x1f - iVar5;
        }
        if (0 < iVar8) {
          puVar6 = (undefined4 *)(uVar10 * param_4 + param_3 + iVar5 * 2);
          param_3 = iVar8;
          do {
            uVar7 = (iVar4 * 2 < 0) - 1 & iVar4 * 2;
            puVar9 = puVar3;
            puVar11 = puVar6;
            for (uVar10 = uVar7 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
              *puVar11 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar11 = puVar11 + 1;
            }
            for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
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

