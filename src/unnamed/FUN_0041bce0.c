/* FUN_0041bce0 - 0x0041bce0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0041bce0(int param_1)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 local_14;
  int local_10;
  undefined4 local_8;
  int local_4;
  
  local_4 = 0;
  local_10 = 0x13a;
  iVar9 = param_1;
LAB_0041bd02:
  local_8 = 0x1f;
  iVar8 = (((int)*(uint *)(param_1 + 0x3b97c) < 1) - 1 & *(uint *)(param_1 + 0x3b97c)) + local_4;
  uVar3 = *(ushort *)(param_1 + 0x3f73c + iVar8 * 2);
  if (((uVar3 != 0) && (uVar5 = uVar3 - 1, DAT_0079352c != 0)) && (-1 < (int)uVar5)) {
    iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar4 = *(uint *)(iVar7 + 4);
    while (uVar4 < 0x35) {
      if (uVar4 == 0x34) {
        iVar7 = *(int *)(iVar7 + 0x10);
        uVar4 = *(uint *)(iVar7 + 8);
        if (uVar4 <= uVar5) goto LAB_0041bd81;
        break;
      }
      iVar7 = *(int *)(iVar7 + 0x1c);
      uVar4 = *(uint *)(iVar7 + 4);
    }
  }
  goto LAB_0041bdb7;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar4 = *(uint *)(iVar7 + 8);
    if (uVar5 < uVar4) break;
LAB_0041bd81:
    if (uVar4 == uVar5) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(0x24,local_10);
      }
      else {
        BlitSpriteClipped(uVar5);
      }
      break;
    }
  }
LAB_0041bdb7:
  switch(*(undefined1 *)(param_1 + 0x3c4d8 + iVar8)) {
  case 0:
    iVar9 = 0xffff;
    local_14 = 0xffff;
    local_8 = 0x1f;
    break;
  case 1:
    iVar9 = 0xc618;
    goto LAB_0041bebd;
  case 2:
    iVar9 = 0;
    local_14 = 0xffe0;
    break;
  case 3:
    iVar9 = 0xf800;
    goto LAB_0041bebd;
  case 4:
    local_14 = 0xafff;
    iVar9 = 0xf0;
    break;
  case 5:
    iVar9 = 0;
    local_14 = 0xc7f8;
    break;
  case 6:
  case 8:
    iVar9 = 0x8000;
    local_14 = 0xf800;
    break;
  case 7:
    local_14 = 0x78e0;
    iVar9 = 0xfdb4;
    local_8 = 0;
    break;
  case 9:
    iVar9 = 0x400;
    local_14 = 0xfff2;
    break;
  case 10:
    local_14 = 0xf800;
    iVar9 = 0xfebf;
    break;
  case 0xb:
    local_14 = 0xfc20;
    iVar9 = 0x4880;
    break;
  case 0xc:
    local_14 = 0x7e0;
    iVar9 = 0x210a;
    break;
  case 0xd:
    local_14 = 0x1f;
    iVar9 = 0xf6bf;
    break;
  case 0xe:
    local_14 = 0xc018;
    iVar9 = 0xfecf;
    break;
  case 0xf:
    local_14 = 0;
    iVar9 = 0xffff;
    break;
  case 0x10:
    iVar9 = 0;
LAB_0041bebd:
    local_14 = 0xffff;
  }
  pcVar6 = (char *)(iVar8 * 9 + 0x3b984 + param_1);
  FUN_004eb510(local_10,local_8);
  BlitRLESprite(local_10,iVar9);
  do {
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  bVar2 = *(byte *)(param_1 + 0x3c4d8 + iVar8);
  if ((bVar2 < 2) || (bVar2 == 7)) {
    pcVar6 = (char *)(param_1 + (iVar8 * 5 + 0xef42) * 4);
    BlitRLESprite(local_10 + 1,0);
    BlitRLESprite(local_10,iVar9);
    do {
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    BlitRLESprite(local_10 + 1,0);
    BlitRLESprite(local_10,iVar9);
  }
  else {
    pcVar6 = (char *)(param_1 + (iVar8 * 5 + 0xef42) * 4);
    FUN_004eb510(local_10,iVar9);
    BlitRLESprite(local_10,local_14);
    do {
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    FUN_004eb510(local_10,iVar9);
    BlitRLESprite(local_10,local_14);
  }
  local_10 = local_10 + 0xf;
  local_4 = local_4 + 1;
  if (0x1fc < local_10) {
    return;
  }
  goto LAB_0041bd02;
}

