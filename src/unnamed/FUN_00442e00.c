/* FUN_00442e00 - 0x00442e00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 3 argless Peeks: the current-slot index at +0x3b49c, the
 * +0x3b6c4 cell, and one entry of the 0x448-stride table at +0x477ec
 * (the same table FUN_004cfd20 indexes), here indexed by the live-in
 * EDI the decompile already models as unaff_EDI.
 *
 * RENDER-CHAIN ARG FIX (2026-09-02): recovered container/KEY/FRAME/x/y
 * at the 4 argless FindSpriteFrame() blocks and their sibling blits from
 * per-site disasm (EBP = iVar7 y-base throughout; the stale 2-arg
 * BlitSprite16bpp forms were the block's real x/y).  0x442e81: key
 * 0x2710, frame = bVar1 + 1 (movzx of [gctx+0x3b6c0], inc), x 0x267,
 * y iVar7 - 2.  0x442f73: key 0x2710, frame = iVar5 + 7 (the +0x477ec
 * peek + 7, already the C's sign-guard/clip value), x 0x272, y iVar7.
 * 0x442fc9: key 0x64 (`mov edx,0x64` - not a 0x27xx registry page),
 * frame = uVar3 (movzx word [gctx+edi*2+0x50116], re-typed ushort),
 * x 0x290, y iVar7.  0x44307d: key 0x2710, frame = (cVar2 != 0) + 4
 * (setne dl / add edx,4), x 0x24d, y iVar7 + 6 (`add ebp,6`).
 */
#include "ghidra_types.h"


void FUN_00442e00(uint regEax)

{
  byte bVar1;
  char cVar2;
  undefined2 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int unaff_EDI;
  
  uVar4 = regEax & 0x80000003;
  if ((int)uVar4 < 0) {
    uVar4 = (uVar4 - 1 | 0xfffffffc) + 1;
  }
  iVar7 = ((3 < (int)regEax) - 1 & 0xffffff5a) + 0x1d2 + uVar4 * 0x1d;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b49c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (((unaff_EDI == iVar5) && (bVar1 = *(byte *)(g_clientContext + 0x3b6c0), g_screenSurface != 0)) &&
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
  if (((unaff_EDI == iVar5) && (g_screenSurface != 0)) && (iVar5 = FindSpriteFrame((int)&g_spriteRegistry,0x2710,3), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(3,0x2f3,iVar7 + 3,0x2710);
    }
    else {
      BlitSpriteClipped(3,0x2f3,iVar7 + 3,0x2710);
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0x477ec + unaff_EDI * 0x448));
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
  uVar3 = *(ushort *)(g_clientContext + 0x50116 + unaff_EDI * 2);
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
   * g_clientContext + unaff_EDI*9 + 0x5012e - the same ECX/EBX/ESI trio
   * the BlitRLESprite five instructions later reuses unchanged. */
  DrawFontString(0x2a1,iVar7 + 1,0x1f,(char *)(g_clientContext + 0x5012e + unaff_EDI * 9));
  /* BlitRLESprite's 4th arg (rleData) was dropped as `regEax` in the raw
   * port - objdump at this call site (0x44301c) shows ECX=0x2a1 (this)
   * and EAX = g_clientContext + unaff_EDI*9 + 0x5012e, the same per-slot
   * short-name field pointer just used (also dropped) as DrawFontString's
   * own EAX arg immediately above; corroborated by the identical
   * `iVar*9+0x5012e+g_clientContext` pattern in
   * State11_InBattle_ProcessBattleAction.c and FUN_004d0260.c. */
  BlitRLESprite(0x2a1,iVar7 + 1,0xffff,(byte *)(g_clientContext + 0x5012e + unaff_EDI * 9));
  iVar5 = g_clientContext;
  /* BlitRLESprite's 4th arg (rleData) was dropped as `regEax` - objdump
   * at this call site (0x443048) shows ECX=0x2a1 (this) and EAX =
   * g_clientContext + unaff_EDI*0xd + 0x50196, a per-slot longer-name
   * field; corroborated by the identical `*0xd+0x50196+g_clientContext`
   * pattern in State11_InBattle_RenderHud.c / State11_InBattle_
   * ProcessBattleAction.c / State09_ReadyRoom_ProcessPacket.c. */
  BlitRLESprite(0x2a1,iVar7 + 0xe,0xffff,(byte *)(g_clientContext + 0x50196 + unaff_EDI * 0xd));
  cVar2 = *(char *)(iVar5 + 0x449ba + unaff_EDI);
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

