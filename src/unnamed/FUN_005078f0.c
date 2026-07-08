/* FUN_005078f0 - 0x005078f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_005078f0(int param_1)

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
  int iVar10;
  int local_14;
  undefined4 local_c;
  int local_8;
  
  if (*(char *)(param_1 + 0x1e) != '\0') {
    return;
  }
  FUN_005054b0();
  iVar8 = *(int *)(param_1 + 0x2c) + 0x2b;
  local_8 = 0;
  iVar10 = param_1;
LAB_00507930:
  local_c = 0x1f;
  iVar9 = (((int)*(uint *)(g_clientContext + 0x3b97c) < 1) - 1 & *(uint *)(g_clientContext + 0x3b97c)) +
          local_8;
  uVar3 = *(ushort *)(g_clientContext + 0x3f73c + iVar9 * 2);
  if (uVar3 != 0) {
    uVar5 = uVar3 - 1;
    if ((DAT_0079352c != 0) && (-1 < (int)uVar5)) {
      iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar4 = *(uint *)(iVar7 + 4);
      while (uVar4 < 0x35) {
        if (uVar4 == 0x34) {
          iVar7 = *(int *)(iVar7 + 0x10);
          uVar4 = *(uint *)(iVar7 + 8);
          if (uVar4 <= uVar5) goto LAB_005079b8;
          break;
        }
        iVar7 = *(int *)(iVar7 + 0x1c);
        uVar4 = *(uint *)(iVar7 + 4);
      }
    }
  }
  goto LAB_005079ea;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar4 = *(uint *)(iVar7 + 8);
    if (uVar5 < uVar4) break;
LAB_005079b8:
    if (uVar4 == uVar5) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(*(int *)(param_1 + 0x28) + 0x1a,iVar8);
      }
      else {
        BlitSpriteClipped(uVar5);
      }
      break;
    }
  }
LAB_005079ea:
  switch(*(undefined1 *)(g_clientContext + 0x3c4d8 + iVar9)) {
  case 0:
    iVar10 = 0xffff;
    local_14 = 0xffff;
    local_c = 0x1f;
    break;
  case 1:
    iVar10 = 0xc618;
    goto LAB_00507af6;
  case 2:
    iVar10 = 0;
    local_14 = 0xffe0;
    break;
  case 3:
    iVar10 = 0xf800;
    goto LAB_00507af6;
  case 4:
    local_14 = 0xafff;
    iVar10 = 0xf0;
    break;
  case 5:
    iVar10 = 0;
    local_14 = 0xc7f8;
    break;
  case 6:
  case 8:
    iVar10 = 0x8000;
    local_14 = 0xf800;
    break;
  case 7:
    local_14 = 0x78e0;
    iVar10 = 0xfdb4;
    local_c = 0;
    break;
  case 9:
    iVar10 = 0x400;
    local_14 = 0xfff2;
    break;
  case 10:
    local_14 = 0xf800;
    iVar10 = 0xfebf;
    break;
  case 0xb:
    local_14 = 0xfc20;
    iVar10 = 0x4880;
    break;
  case 0xc:
    local_14 = 0x7e0;
    iVar10 = 0x210a;
    break;
  case 0xd:
    local_14 = 0x1f;
    iVar10 = 0xf6bf;
    break;
  case 0xe:
    local_14 = 0xc018;
    iVar10 = 0xfecf;
    break;
  case 0xf:
    local_14 = 0;
    iVar10 = 0xffff;
    break;
  case 0x10:
    iVar10 = 0;
LAB_00507af6:
    local_14 = 0xffff;
  }
  pcVar6 = (char *)(iVar9 * 9 + 0x3b984 + g_clientContext);
  FUN_004eb510(iVar8,local_c);
  BlitRLESprite(iVar8,iVar10);
  do {
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  bVar2 = *(byte *)(g_clientContext + 0x3c4d8 + iVar9);
  if ((bVar2 < 2) || (bVar2 == 7)) {
    pcVar6 = (char *)(g_clientContext + (iVar9 * 5 + 0xef42) * 4);
    BlitRLESprite(iVar8,0);
    BlitRLESprite(iVar8,iVar10);
    do {
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    BlitRLESprite(iVar8,0);
    iVar9 = iVar10;
  }
  else {
    pcVar6 = (char *)(g_clientContext + (iVar9 * 5 + 0xef42) * 4);
    FUN_004eb510(iVar8,iVar10);
    BlitRLESprite(iVar8,local_14);
    do {
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    FUN_004eb510(iVar8,iVar10);
    iVar9 = local_14;
  }
  BlitRLESprite(iVar8,iVar9);
  iVar8 = iVar8 + 0xe;
  local_8 = local_8 + 1;
  if (0xc < local_8) {
    if (*(int *)(g_gameStateVTableArray[3] + 0x124) == -1) {
      return;
    }
    FUN_0042a680(g_gameStateVTableArray[3]);
    return;
  }
  goto LAB_00507930;
}

