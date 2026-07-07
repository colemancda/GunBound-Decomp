/* FUN_00522570 - 0x00522570 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00522570(int param_1,uint param_2)

{
  char *pcVar1;
  char cVar2;
  undefined4 uVar3;
  bool bVar4;
  
  if (DAT_005b15ac != (char *)0x0) {
    uVar3 = FUN_005218c0(&DAT_0056a748,param_1,param_2);
    FUN_00521a90(DAT_005b15ac + 0x24,uVar3);
  }
  pcVar1 = DAT_005b15ac;
  switch(param_1) {
  case 0x60f:
    param_1 = 0x3e9;
    bVar4 = *DAT_005b15ac == '\0';
    goto LAB_0052270b;
  case 0x610:
    param_1 = 0x3ea;
    bVar4 = *DAT_005b15ac == '\0';
    goto LAB_005226b1;
  default:
    if (param_1 == 500) {
      param_1 = 0x3f6;
      param_2 = 500;
    }
    else {
      param_1 = 1000;
    }
    break;
  case 0x614:
    if (DAT_005b15ac[0x21] != '\0') {
      return 1;
    }
    cVar2 = FUN_00521ea0(param_2);
    if (cVar2 != '\0') {
      return 1;
    }
    param_1 = 0x3f6;
    param_2 = 0xdc;
    DAT_005b158c = 2;
    break;
  case 0x615:
    _DAT_005b15a0 = param_2;
    if (param_2 == DAT_005b15a4) {
      return 1;
    }
    if (DAT_005b15ac == (char *)0x0) {
      return 1;
    }
    uVar3 = FUN_005218c0(&DAT_0056a6f4,param_2,DAT_005b15a4);
    FUN_00521a90(DAT_005b15ac + 0x24,uVar3);
    return 1;
  case 0x618:
    if (0x3b < param_2) {
      FUN_00522f20();
      FUN_00523000();
      if (DAT_005b15ac != (char *)0x0) {
        uVar3 = FUN_005218c0(&DAT_0056a730,param_2);
        FUN_00521a90(DAT_005b15ac + 0x24,uVar3);
      }
      param_1 = 0x3e9;
    }
    break;
  case 0x62d:
    param_1 = 0x3f3;
    if (*(int *)(DAT_005b15ac + 4) == 0) {
      pcVar1[8] = -0xd;
      pcVar1[9] = '\x03';
      pcVar1[10] = '\0';
      pcVar1[0xb] = '\0';
      *(uint *)(DAT_005b15ac + 0xc) = param_2;
      return 1;
    }
    break;
  case 0x62e:
    param_1 = 0x3f4;
    if (*(int *)(DAT_005b15ac + 4) == 0) {
      pcVar1[8] = -0xc;
      pcVar1[9] = '\x03';
      pcVar1[10] = '\0';
      pcVar1[0xb] = '\0';
      *(uint *)(DAT_005b15ac + 0xc) = param_2;
      return 1;
    }
    break;
  case 0x62f:
    param_1 = 0x3f5;
    goto LAB_00522706;
  case 0x630:
    param_1 = 0x3f7;
    goto LAB_005226ac;
  case 0x637:
    param_1 = 0x3f6;
    param_2 = 0xd2;
    if (*(int *)(DAT_005b15ac + 4) == 0) {
      pcVar1[8] = -10;
      pcVar1[9] = '\x03';
      pcVar1[10] = '\0';
      pcVar1[0xb] = '\0';
      pcVar1 = DAT_005b15ac;
      pcVar1[0xc] = -0x2e;
      pcVar1[0xd] = '\0';
      pcVar1[0xe] = '\0';
      pcVar1[0xf] = '\0';
      return 1;
    }
    break;
  case 0x638:
    param_1 = 0x3f6;
    param_2 = 0xdc;
    DAT_005b158c = 2;
LAB_00522706:
    bVar4 = *(int *)(DAT_005b15ac + 4) == 0;
LAB_0052270b:
    if (bVar4) {
      *(int *)(DAT_005b15ac + 8) = param_1;
      *(uint *)(DAT_005b15ac + 0xc) = param_2;
      return 1;
    }
    break;
  case 0x639:
    param_1 = 0x3f6;
    param_2 = 0xe6;
    DAT_005b158c = 2;
LAB_005226ac:
    bVar4 = *(int *)(DAT_005b15ac + 4) == 0;
LAB_005226b1:
    if (bVar4) {
      *(int *)(DAT_005b15ac + 8) = param_1;
      *(uint *)(DAT_005b15ac + 0xc) = param_2;
      return 1;
    }
    break;
  case 0x63a:
    if (DAT_005b15ac != (char *)0x0) {
      uVar3 = FUN_005218c0(&DAT_0056a71c,param_2);
      FUN_00521a90(DAT_005b15ac + 0x24,uVar3);
    }
    param_1 = 0x3f8;
  }
  cVar2 = FUN_004152d0(param_1,param_2);
  if (cVar2 != '\0') {
    return 1;
  }
  if (DAT_005b15ac != (char *)0x0) {
    uVar3 = FUN_005218c0(&DAT_0056a6d4,param_1,param_2);
    FUN_00521a90(DAT_005b15ac + 0x24,uVar3);
  }
  DAT_005b15ac[0x22] = '\x01';
  return 0;
}

