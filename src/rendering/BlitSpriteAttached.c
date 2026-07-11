/* BlitSpriteAttached - 0x0045b730 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __fastcall
BlitSpriteAttached(undefined4 param_1,uint param_2,uint param_3,uint param_4,int param_5,int param_6)

{
  int iVar1;
  uint in_EAX;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined4 *puVar10;
  int iVar11;
  undefined4 *puVar12;
  
  uVar2 = *(uint *)(DAT_00ea0e1c + 0x1c);
  uVar8 = *(uint *)(uVar2 + 4);
  uVar3 = uVar2;
  while (uVar8 <= param_3) {
    if (uVar8 == param_3) {
      iVar7 = *(int *)(uVar3 + 0x10);
      uVar8 = *(uint *)(iVar7 + 8);
      goto joined_r0x0045b764;
    }
    uVar3 = *(uint *)(uVar3 + 0x1c);
    uVar8 = *(uint *)(uVar3 + 4);
  }
  iVar7 = 0;
LAB_0045b778:
  uVar8 = *(uint *)(uVar2 + 4);
  while (uVar8 <= in_EAX) {
    if (uVar8 == in_EAX) {
      uVar2 = *(uint *)(uVar2 + 0x10);
      uVar8 = *(uint *)(uVar2 + 8);
      if (uVar8 <= param_4) goto LAB_0045b7a9;
      break;
    }
    uVar2 = *(uint *)(uVar2 + 0x1c);
    uVar8 = *(uint *)(uVar2 + 4);
  }
LAB_0045b791:
  return uVar2 & 0xffffff00;
joined_r0x0045b764:
  if (param_2 < uVar8) goto LAB_0045b772;
  if (uVar8 == param_2) goto LAB_0045b778;
  iVar7 = *(int *)(iVar7 + 0x10);
  uVar8 = *(uint *)(iVar7 + 8);
  goto joined_r0x0045b764;
LAB_0045b772:
  iVar7 = 0;
  goto LAB_0045b778;
LAB_0045b7a9:
  while (uVar8 != param_4) {
    uVar2 = *(uint *)(uVar2 + 0x10);
    uVar8 = *(uint *)(uVar2 + 8);
    if (param_4 < uVar8) {
      return uVar2 & 0xffffff00;
    }
  }
  if (param_3 == 0xffffffff) {
    iVar4 = *(int *)(uVar2 + 0x28) + 0x40;
    uVar8 = *(int *)(uVar2 + 0x2c) + 0x40;
  }
  else {
    if (iVar7 == 0) goto LAB_0045b791;
    iVar4 = *(int *)(uVar2 + 0x28) + *(int *)(iVar7 + 0x48) + 0x40 + *(int *)(iVar7 + 0x28);
    uVar8 = *(int *)(uVar2 + 0x2c) + *(int *)(iVar7 + 0x4c) + 0x70 + *(int *)(iVar7 + 0x2c);
  }
  iVar9 = *(int *)(uVar2 + 0x20);
  uVar3 = -uVar8;
  puVar6 = (undefined4 *)(*(int *)(uVar2 + 0x34) + iVar9 * (((int)uVar3 < 0) - 1 & uVar3) * 2);
  iVar11 = *(int *)(uVar2 + 0x24) - (uVar3 & ((int)uVar3 < 0) - 1);
  uVar8 = ((int)uVar8 < 0) - 1 & uVar8;
  iVar1 = iVar4 + iVar9;
  if (((0 < iVar1) && (iVar4 < 0x80)) &&
     ((param_3 == 0xffffffff || ((*(int *)(iVar7 + 0x24) + uVar8 != 0 && ((int)uVar8 < 0x80)))))) {
    if (0x7f < (int)(iVar11 + uVar8)) {
      iVar11 = 0x7f - uVar8;
    }
    if (iVar4 < 0) {
      puVar6 = (undefined4 *)((int)puVar6 + iVar4 * -2);
      iVar4 = 0;
      iVar9 = iVar1;
    }
    if (0x7f < iVar4 + iVar9) {
      iVar9 = 0x7f - iVar4;
    }
    if (0 < iVar11) {
      puVar5 = (undefined4 *)(uVar8 * param_6 + param_5 + iVar4 * 2);
      param_3 = iVar11;
      do {
        uVar3 = (iVar9 * 2 < 0) - 1 & iVar9 * 2;
        puVar10 = puVar6;
        puVar12 = puVar5;
        for (uVar8 = uVar3 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *puVar12 = *puVar10;
          puVar10 = puVar10 + 1;
          puVar12 = puVar12 + 1;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *(undefined1 *)puVar12 = *(undefined1 *)puVar10;
          puVar10 = (undefined4 *)((int)puVar10 + 1);
          puVar12 = (undefined4 *)((int)puVar12 + 1);
        }
        puVar6 = (undefined4 *)((int)puVar6 + *(int *)(uVar2 + 0x20) * 2);
        puVar5 = (undefined4 *)((int)puVar5 + param_6);
        param_3 = param_3 + -1;
      } while (param_3 != 0);
    }
    return CONCAT31((int3)(uVar2 >> 8),1);
  }
  goto LAB_0045b791;
}

