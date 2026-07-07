/* FUN_004f1220 - 0x004f1220 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_004f1220(int param_1,char *param_2,char param_3)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  undefined4 *puVar8;
  
  uVar2 = FUN_004f11a0(param_2);
  if (uVar2 == 0xffffffff) {
    uVar5 = *(uint *)(param_1 + 8);
    uVar2 = 0;
    if (uVar5 != 0) {
      do {
        iVar3 = FUN_004f0990();
        if (0 < iVar3) break;
        uVar2 = uVar2 + 1;
      } while (uVar2 < *(uint *)(param_1 + 8));
    }
    if ((uVar5 & 0x3ff) == 0) {
      puVar4 = operator_new(0x20000);
      *(undefined4 **)(param_1 + 0x40 + (uVar5 >> 10) * 4) = puVar4;
      for (iVar3 = 0x8000; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
      }
    }
    uVar5 = *(uint *)(param_1 + 8);
    *(uint *)(param_1 + 8) = uVar5 + 1;
    uVar7 = uVar5;
    for (; uVar2 < uVar5; uVar5 = uVar5 - 1) {
      uVar7 = uVar7 - 1;
      iVar3 = *(int *)(param_1 + 0x40 + (uVar7 >> 10) * 4);
      if (iVar3 == 0) {
        puVar4 = (undefined4 *)0x0;
      }
      else {
        puVar4 = (undefined4 *)((uVar7 & 0x3ff) * 0x80 + iVar3);
      }
      iVar3 = *(int *)(param_1 + 0x40 + (uVar5 >> 10) * 4);
      if (iVar3 == 0) {
        puVar8 = (undefined4 *)0x0;
      }
      else {
        puVar8 = (undefined4 *)((uVar5 & 0x3ff) * 0x80 + iVar3);
      }
      for (iVar3 = 0x20; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar8 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar8 = puVar8 + 1;
      }
    }
    iVar3 = *(int *)(param_1 + 0x40 + (uVar2 >> 10) * 4);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = (uVar2 & 0x3ff) * 0x80 + iVar3;
    }
    iVar6 = iVar3 - (int)param_2;
    do {
      cVar1 = *param_2;
      param_2[iVar6] = cVar1;
      param_2 = param_2 + 1;
    } while (cVar1 != '\0');
  }
  else {
    iVar3 = *(int *)(param_1 + 0x40 + (uVar2 >> 10) * 4);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = (uVar2 & 0x3ff) * 0x80 + iVar3;
    }
  }
  *(undefined4 *)(iVar3 + 0x74) = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)(iVar3 + 0x7c) = 0;
  *(undefined4 *)(iVar3 + 0x78) = 0;
  *(uint *)(iVar3 + 0x70) = (uint)(param_3 != '\0');
  return uVar2;
}

