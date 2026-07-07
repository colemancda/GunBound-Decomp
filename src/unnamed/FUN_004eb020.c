/* FUN_004eb020 - 0x004eb020 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_004eb020(int param_1,int param_2,int param_3,undefined2 param_4)

{
  ushort uVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  ushort *puVar4;
  int iVar5;
  int iVar6;
  ushort uVar7;
  ushort uVar8;
  int local_48;
  ushort auStack_42 [28];
  ushort local_a;
  
  puVar2 = (undefined1 *)(param_1 + 2);
  iVar5 = 0;
  do {
    iVar6 = iVar5 + 6;
    puVar3 = puVar2 + 0xc;
    auStack_42[iVar5 + 0x11] = CONCAT11(puVar2[-2],puVar2[-1]);
    *(ushort *)(puVar3 + (int)auStack_42 + (0x16 - param_1)) = CONCAT11(*puVar2,puVar2[1]);
    *(ushort *)(puVar3 + (int)auStack_42 + (0x18 - param_1)) = CONCAT11(puVar2[2],puVar2[3]);
    *(ushort *)(puVar2 + (int)auStack_42 + (0x26 - param_1)) = CONCAT11(puVar2[4],puVar2[5]);
    *(ushort *)(puVar3 + (int)auStack_42 + (0x1c - param_1)) = CONCAT11(puVar2[6],puVar2[7]);
    *(ushort *)(puVar3 + (int)auStack_42 + (0x1e - param_1)) = CONCAT11(puVar2[8],puVar2[9]);
    puVar2 = puVar3;
    iVar5 = iVar6;
  } while (iVar6 < 0xc);
  auStack_42[0xe] = local_a >> 1;
  puVar4 = auStack_42 + 0x11;
  auStack_42[1] = auStack_42[0x11] >> 1;
  iVar5 = 1;
  do {
    if (iVar5 == 1) {
      uVar7 = 0;
    }
    else {
      uVar7 = puVar4[-1] >> 1;
    }
    uVar1 = *puVar4;
    uVar7 = uVar1 >> 2 | uVar1 | uVar7;
    auStack_42[iVar5 + 1] = uVar7;
    if (iVar5 == 0xc) {
      uVar8 = 0;
    }
    else {
      uVar8 = puVar4[1] >> 1;
    }
    auStack_42[iVar5 + 1] = ~(uVar1 >> 1) & (uVar8 | uVar7);
    if (iVar5 == 0) {
      uVar7 = 0;
    }
    else {
      uVar7 = *puVar4 >> 1;
    }
    uVar1 = puVar4[1];
    uVar7 = uVar1 >> 2 | uVar1 | uVar7;
    auStack_42[iVar5 + 2] = uVar7;
    if (iVar5 == 0xb) {
      uVar8 = 0;
    }
    else {
      uVar8 = puVar4[2] >> 1;
    }
    auStack_42[iVar5 + 2] = ~(uVar1 >> 1) & (uVar8 | uVar7);
    if (iVar5 == -1) {
      uVar7 = 0;
    }
    else {
      uVar7 = puVar4[1] >> 1;
    }
    uVar1 = puVar4[2];
    uVar7 = uVar1 >> 2 | uVar1 | uVar7;
    auStack_42[iVar5 + 3] = uVar7;
    if (iVar5 == 10) {
      uVar8 = 0;
    }
    else {
      uVar8 = puVar4[3] >> 1;
    }
    auStack_42[iVar5 + 3] = ~(uVar1 >> 1) & (uVar8 | uVar7);
    if (iVar5 == -2) {
      uVar7 = 0;
    }
    else {
      uVar7 = puVar4[2] >> 1;
    }
    uVar1 = puVar4[3];
    uVar7 = uVar1 >> 2 | uVar1 | uVar7;
    auStack_42[iVar5 + 4] = uVar7;
    if (iVar5 == 9) {
      uVar8 = 0;
    }
    else {
      uVar8 = puVar4[4] >> 1;
    }
    iVar5 = iVar5 + 4;
    puVar4 = puVar4 + 4;
    auStack_42[iVar5] = ~(uVar1 >> 1) & (uVar8 | uVar7);
  } while (iVar5 < 0xd);
  puVar4 = auStack_42;
  param_3 = param_3 + -1;
  local_48 = 0xe;
  do {
    puVar4 = puVar4 + 1;
    iVar5 = 0;
    uVar7 = *puVar4;
    do {
      if (((((uVar7 >> (0xfU - (char)iVar5 & 0x1f) & 1) != 0) &&
           (iVar6 = iVar5 + -1 + param_2, iVar6 <= DAT_0056df30)) && (DAT_00793530 <= iVar6)) &&
         ((param_3 <= DAT_0056df34 && (DAT_00793534 <= param_3)))) {
        *(undefined2 *)(DAT_0079352c + (param_3 * DAT_005b3620 + iVar6) * 2) = param_4;
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0xe);
    param_3 = param_3 + 1;
    local_48 = local_48 + -1;
  } while (local_48 != 0);
  return;
}

