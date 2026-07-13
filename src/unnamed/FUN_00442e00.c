/* FUN_00442e00 - 0x00442e00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00442e00(void)

{
  byte bVar1;
  char cVar2;
  undefined2 uVar3;
  uint in_EAX;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int unaff_EDI;
  
  uVar4 = in_EAX & 0x80000003;
  if ((int)uVar4 < 0) {
    uVar4 = (uVar4 - 1 | 0xfffffffc) + 1;
  }
  iVar7 = ((3 < (int)in_EAX) - 1 & 0xffffff5a) + 0x1d2 + uVar4 * 0x1d;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (((unaff_EDI == iVar5) && (bVar1 = *(byte *)(g_clientContext + 0x3b6c0), DAT_0079352c != 0)) &&
     (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(0x267,iVar7 + -2);
    }
    else {
      BlitSpriteClipped(bVar1 + 1);
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (((unaff_EDI == iVar5) && (DAT_0079352c != 0)) && (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(0x2f3,iVar7 + 3);
    }
    else {
      BlitSpriteClipped(3);
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (((DAT_0079352c != 0) && (-1 < iVar5 + 7)) && (iVar6 = FindSpriteFrame(), iVar6 != 0)) {
    if (*(char *)(iVar6 + 0x18) == '\x01') {
      BlitSprite16bpp(0x272,iVar7);
    }
    else {
      BlitSpriteClipped(iVar5 + 7);
    }
  }
  uVar3 = *(undefined2 *)(g_clientContext + 0x50116 + unaff_EDI * 2);
  if ((DAT_0079352c != 0) && (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(0x290,iVar7);
    }
    else {
      BlitSpriteClipped(uVar3);
    }
  }
  DrawFontString(iVar7 + 1,0x1f);
  /* BlitRLESprite's 4th arg (rleData) was dropped as `in_EAX` in the raw
   * port - objdump at this call site (0x44301c) shows ECX=0x2a1 (this)
   * and EAX = g_clientContext + unaff_EDI*9 + 0x5012e, the same per-slot
   * short-name field pointer just used (also dropped) as DrawFontString's
   * own EAX arg immediately above; corroborated by the identical
   * `iVar*9+0x5012e+g_clientContext` pattern in
   * State11_InBattle_ProcessBattleAction.c and FUN_004d0260.c. */
  BlitRLESprite(0x2a1,iVar7 + 1,0xffff,(byte *)(g_clientContext + 0x5012e + unaff_EDI * 9));
  iVar5 = g_clientContext;
  /* BlitRLESprite's 4th arg (rleData) was dropped as `in_EAX` - objdump
   * at this call site (0x443048) shows ECX=0x2a1 (this) and EAX =
   * g_clientContext + unaff_EDI*0xd + 0x50196, a per-slot longer-name
   * field; corroborated by the identical `*0xd+0x50196+g_clientContext`
   * pattern in State11_InBattle_RenderHud.c / State11_InBattle_
   * ProcessBattleAction.c / State09_ReadyRoom_ProcessPacket.c. */
  BlitRLESprite(0x2a1,iVar7 + 0xe,0xffff,(byte *)(g_clientContext + 0x50196 + unaff_EDI * 0xd));
  cVar2 = *(char *)(iVar5 + 0x449ba + unaff_EDI);
  if ((DAT_0079352c != 0) && (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(0x24d,iVar7 + 6);
      return;
    }
    BlitSpriteClipped((cVar2 != '\0') + '\x04');
  }
  return;
}

