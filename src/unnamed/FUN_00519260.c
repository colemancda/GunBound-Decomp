/* FUN_00519260 - 0x00519260 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00519260(undefined4 *param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  
  uVar3 = *(undefined4 *)(&DAT_005448e8 + *(int *)(param_2 + 0xc) * 8);
  uVar1 = *(undefined4 *)(&DAT_005448ec + *(int *)(param_2 + 0xc) * 8);
  if (*(int *)(param_2 + 0x14) == 2) {
    if (*(int *)(param_2 + 0x18) == 0) {
      iVar5 = 6;
      puVar4 = param_1 + 0x24;
      do {
        uVar2 = FUN_00514af0(uVar3);
        puVar4[-0xd] = uVar2;
        uVar2 = FUN_00514af0(uVar3);
        *puVar4 = uVar2;
        uVar2 = FUN_00514af0(uVar3);
        puVar4[0xd] = uVar2;
        puVar4 = puVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      iVar5 = 6;
      param_1 = param_1 + 0x2a;
      do {
        uVar3 = FUN_00514af0(uVar1);
        param_1[-0xd] = uVar3;
        uVar3 = FUN_00514af0(uVar1);
        *param_1 = uVar3;
        uVar3 = FUN_00514af0(uVar1);
        param_1[0xd] = uVar3;
        param_1 = param_1 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      return;
    }
    iVar5 = 8;
    puVar4 = param_1;
    do {
      uVar2 = FUN_00514af0(uVar3);
      *puVar4 = uVar2;
      puVar4 = puVar4 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    iVar5 = 3;
    puVar4 = param_1 + 0x27;
    do {
      uVar2 = FUN_00514af0(uVar3);
      puVar4[-0xd] = uVar2;
      uVar2 = FUN_00514af0(uVar3);
      *puVar4 = uVar2;
      uVar2 = FUN_00514af0(uVar3);
      puVar4[0xd] = uVar2;
      puVar4 = puVar4 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    iVar5 = 6;
    param_1 = param_1 + 0x2a;
    do {
      uVar3 = FUN_00514af0(uVar1);
      param_1[-0xd] = uVar3;
      uVar3 = FUN_00514af0(uVar1);
      *param_1 = uVar3;
      uVar3 = FUN_00514af0(uVar1);
      param_1[0xd] = uVar3;
      param_1 = param_1 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    return;
  }
  if (param_4 != 0) {
    if ((param_3 & 8) == 0) {
      iVar5 = 6;
      puVar4 = param_1;
      do {
        uVar2 = FUN_00514af0(uVar3);
        *puVar4 = uVar2;
        puVar4 = puVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    else {
      iVar5 = 6;
      puVar4 = param_1;
      do {
        *puVar4 = puVar4[-0x7c];
        puVar4 = puVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    if ((param_3 & 4) == 0) {
      puVar4 = param_1 + 6;
      iVar5 = 5;
      do {
        uVar2 = FUN_00514af0(uVar3);
        *puVar4 = uVar2;
        puVar4 = puVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    else {
      puVar4 = param_1 + 6;
      iVar5 = 5;
      do {
        *puVar4 = puVar4[-0x7c];
        puVar4 = puVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    if ((param_3 & 2) == 0) {
      puVar4 = param_1 + 0xb;
      iVar5 = 5;
      do {
        uVar3 = FUN_00514af0(uVar1);
        *puVar4 = uVar3;
        puVar4 = puVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    else {
      puVar4 = param_1 + 0xb;
      iVar5 = 5;
      do {
        *puVar4 = puVar4[-0x7c];
        puVar4 = puVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    if ((param_3 & 1) == 0) {
      param_1 = param_1 + 0x10;
      iVar5 = 5;
      do {
        uVar3 = FUN_00514af0(uVar1);
        *param_1 = uVar3;
        param_1 = param_1 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      return;
    }
    param_1 = param_1 + 0x10;
    iVar5 = 5;
    do {
      *param_1 = param_1[-0x7c];
      param_1 = param_1 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    return;
  }
  iVar5 = 0xb;
  puVar4 = param_1;
  do {
    uVar2 = FUN_00514af0(uVar3);
    *puVar4 = uVar2;
    puVar4 = puVar4 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  iVar5 = 10;
  param_1 = param_1 + 0xb;
  do {
    uVar3 = FUN_00514af0(uVar1);
    *param_1 = uVar3;
    param_1 = param_1 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  return;
}

