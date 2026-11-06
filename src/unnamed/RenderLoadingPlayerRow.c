/* RenderLoadingPlayerRow - 0x00442e00 in the original binary.
 *
 * Draws one player row of the loading screen: the ready / status icons,
 * the player's name strings and the per-slot icons, at a y derived from
 * the row number.  Evidence is from the sole caller, 0x00442d50
 * (RenderLoadingPlayerRows), which is called by State10_Loading_Render
 * and invokes this at 0x00442d8e and 0x00442de1: EAX = the row number (0..3
 * for the first group of slots, 4..7 for the second, via lea eax,[esi+4])
 * and EDI = the slot index found by its scan of the 8-slot table at
 * g_clientContext + 0x45914 (the occupied-slot bytes it filters on).  The
 * names read here, g_clientContext + 0x5012e + slot * 9 and + 0x50196 +
 * slot * 0xd, are the same two per-slot strings
 * State11_InBattle_ProcessBattleAction passes to AppendChatLogEntry as
 * its name arguments, so the slot is a player slot.  The row geometry
 * is y = 0x12c + 0x1d * (row % 4) for rows 0..3 and 0x1d2 + 0x1d *
 * (row % 4) for rows 4..7.  LIKELY: the name rests
 * on the caller, State10_Loading_Render's own account of per-player rows,
 * and the name strings; the meaning of the individual icons is unproven.
 *
 * Both inputs were registers Ghidra dropped: EAX is already the regEax
 * parameter and EDI (Ghidra's unaff_EDI, read throughout the body) is now
 * the trailing regEdi parameter; the two call sites pass the slot.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void RenderLoadingPlayerRow(uint regEax,int regEdi)

{
  byte bVar1;
  char cVar2;
  undefined2 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  uVar4 = regEax & 0x80000003;
  if ((int)uVar4 < 0) {
    uVar4 = (uVar4 - 1 | 0xfffffffc) + 1;
  }
  iVar7 = ((3 < (int)regEax) - 1 & 0xffffff5a) + 0x1d2 + uVar4 * 0x1d;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b49c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (((regEdi == iVar5) && (bVar1 = *(byte *)(g_clientContext + 0x3b6c0), g_screenSurface != 0)) &&
     (iVar5 = FindSpriteFrame((int)&g_spriteRegistry,0x2710,bVar1 + 1), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(bVar1 + 1,0x267,iVar7 + -2,0x2710);
    }
    else {
      BlitSpriteClipped(bVar1 + 1,0x267,iVar7 + -2,0x2710);
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b6c4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (((regEdi == iVar5) && (g_screenSurface != 0)) && (iVar5 = FindSpriteFrame((int)&g_spriteRegistry,0x2710,3), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(3,0x2f3,iVar7 + 3,0x2710);
    }
    else {
      BlitSpriteClipped(3,0x2f3,iVar7 + 3,0x2710);
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0x477ec + regEdi * 0x448));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (((g_screenSurface != 0) && (-1 < iVar5 + 7)) &&
     (iVar6 = FindSpriteFrame((int)&g_spriteRegistry,0x2710,iVar5 + 7), iVar6 != 0)) {
    if (*(char *)(iVar6 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar5 + 7,0x272,iVar7,0x2710);
    }
    else {
      BlitSpriteClipped(iVar5 + 7,0x272,iVar7,0x2710);
    }
  }
  uVar3 = *(ushort *)(g_clientContext + 0x50116 + regEdi * 2);
  if ((g_screenSurface != 0) &&
     (iVar5 = FindSpriteFrame((int)&g_spriteRegistry,0x64,uVar3), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(uVar3,0x290,iVar7,0x64);
    }
    else {
      BlitSpriteClipped(uVar3,0x290,iVar7,0x64);
    }
  }
  /* RE-SLOT + dropped EAX (objdump @0x442ffa-0x443011): x/ECX = 0x2a1,
   * y = ebx = iVar7 + 1, colour = 0x1f, string = EAX = esi =
   * `lea edx,[ebx+edi*8] / lea esi,[edi+edx+0x5012e]` =
   * g_clientContext + regEdi*9 + 0x5012e - the same ECX/EBX/ESI trio
   * the BlitRLESprite five instructions later reuses unchanged. */
  DrawFontString(0x2a1,iVar7 + 1,0x1f,(char *)(g_clientContext + 0x5012e + regEdi * 9));
  /* BlitRLESprite's 4th arg (rleData) was dropped as `regEax` in the raw
   * port - objdump at this call site (0x44301c) shows ECX=0x2a1 (this)
   * and EAX = g_clientContext + regEdi*9 + 0x5012e, the same per-slot
   * short-name field pointer just used (also dropped) as DrawFontString's
   * own EAX arg immediately above; corroborated by the identical
   * `iVar*9+0x5012e+g_clientContext` pattern in
   * State11_InBattle_ProcessBattleAction.c and FUN_004d0260.c. */
  BlitRLESprite(0x2a1,iVar7 + 1,0xffff,(byte *)(g_clientContext + 0x5012e + regEdi * 9));
  iVar5 = g_clientContext;
  /* BlitRLESprite's 4th arg (rleData) was dropped as `regEax` - objdump
   * at this call site (0x443048) shows ECX=0x2a1 (this) and EAX =
   * g_clientContext + regEdi*0xd + 0x50196, a per-slot longer-name
   * field; corroborated by the identical `*0xd+0x50196+g_clientContext`
   * pattern in State11_InBattle_RenderHud.c / State11_InBattle_
   * ProcessBattleAction.c / State09_ReadyRoom_ProcessPacket.c. */
  BlitRLESprite(0x2a1,iVar7 + 0xe,0xffff,(byte *)(g_clientContext + 0x50196 + regEdi * 0xd));
  cVar2 = *(char *)(iVar5 + 0x449ba + regEdi);
  if ((g_screenSurface != 0) &&
     (iVar5 = FindSpriteFrame((int)&g_spriteRegistry,0x2710,(cVar2 != '\0') + 4), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp((cVar2 != '\0') + 4,0x24d,iVar7 + 6,0x2710);
      return;
    }
    BlitSpriteClipped((cVar2 != '\0') + 4,0x24d,iVar7 + 6,0x2710);
  }
  return;
}

