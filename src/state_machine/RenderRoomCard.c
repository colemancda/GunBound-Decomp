/* RenderRoomCard - 0x0042a220 in the original binary.
 *
 * Draws one room card in the lobby's 2x3 grid: background (3-state by selection), flag/mode/status/lock icons, room number, and population gauge. Full offset/sprite tables in docs/screens/03_game_room_list.md. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall RenderRoomCard(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  char local_80 [128];
  
  if (param_2 / 3 == 0) {
    iVar7 = 0x18;
    iVar8 = 1;
  }
  else {
    iVar7 = 0x144;
    iVar8 = 4;
  }
  iVar6 = (param_2 % 3) * 0x3c;
  if (*(int *)(param_1 + 4) == param_2) {
    iVar8 = iVar8 + 2;
  }
  else if (*(int *)(param_1 + 8) == param_2) {
    iVar8 = iVar8 + 1;
  }
  if ((DAT_0079352c != 0) && (iVar4 = FindSpriteFrame(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7,iVar6 + 0x3a);
    }
    else {
      BlitSpriteClipped(iVar8);
    }
  }
  if (((*(char *)(g_clientContext + 0x449b4 + param_2) != '\0') && (DAT_0079352c != 0)) &&
     (iVar8 = FindSpriteFrame(), iVar8 != 0)) {
    if (*(char *)(iVar8 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0xb1,iVar6 + 0x42);
    }
    else {
      BlitSpriteClipped(0xe);
    }
  }
  bVar1 = *(byte *)(g_clientContext + 0x4499c + param_2);
  iVar8 = g_clientContext + 0x4499c;
  if ((DAT_0079352c != 0) && (iVar4 = FindSpriteFrame(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0xc3,iVar6 + 0x46);
    }
    else {
      BlitSpriteClipped(bVar1 + 10);
    }
  }
  bVar1 = *(byte *)(g_clientContext + 0x449a2 + param_2);
  iVar4 = g_clientContext + 0x449a2;
  if ((DAT_0079352c != 0) && (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0xd2,iVar6 + 0x46);
    }
    else {
      BlitSpriteClipped(bVar1 + 10);
    }
  }
  bVar1 = *(byte *)(g_clientContext + 0x44986 + param_2 * 4);
  bVar2 = *(byte *)(g_clientContext + 0x4497c + param_2);
  if ((DAT_0079352c != 0) && (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0x6a,iVar6 + 0x5b);
    }
    else {
      BlitSpriteClipped((bVar1 & 3) * 0xb + (uint)bVar2);
    }
  }
  uVar9 = 9;
  if (*(char *)(g_clientContext + 0x449a8 + param_2) == '\0') {
    if (*(char *)(iVar8 + param_2) == *(char *)(iVar4 + param_2)) {
      uVar9 = 8;
    }
  }
  else {
    uVar9 = 7;
  }
  if ((DAT_0079352c != 0) && (iVar8 = FindSpriteFrame(), iVar8 != 0)) {
    if (*(char *)(iVar8 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0x13,iVar6 + 0x55);
    }
    else {
      BlitSpriteClipped(uVar9);
    }
  }
  if (*(char *)(g_clientContext + 0x449ae + param_2) != '\0') {
    if ((DAT_0079352c != 0) && (iVar8 = FindSpriteFrame(), iVar8 != 0)) {
      if (*(char *)(iVar8 + 0x18) == '\x01') {
        BlitSprite16bpp((-(uint)(param_2 / 3 != 0) & 0xffffff06) + 0xea + iVar7,iVar6 + 0x52);
      }
      else {
        BlitSpriteClipped(0xf);
      }
    }
  }
  _sprintf(local_80,(char *)&PTR_DAT_00551ecc,*(int *)(g_clientContext + 0x44664 + param_2 * 4) + 1);
  BlitSpriteText(0x14,local_80,3,0xb);
  SetClipRect();
  BlitRLESprite(0,iVar6 + 0x44,0xffff,(byte *)0);
  SetClipRect();
  uVar3 = *(uint *)(g_clientContext + 0x44984 + param_2 * 4);
  if ((DAT_0079352c != 0) && (iVar8 = FindSpriteFrame(), iVar8 != 0)) {
    if (*(char *)(iVar8 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0xb1,iVar6 + 0x5b);
      return;
    }
    BlitSpriteClipped((uVar3 >> 0x12 & 3) + 10);
  }
  return;
}

