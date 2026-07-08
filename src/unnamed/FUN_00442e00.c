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
     (iVar5 = FUN_004f30c0(), iVar5 != 0)) {
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
  if (((unaff_EDI == iVar5) && (DAT_0079352c != 0)) && (iVar5 = FUN_004f30c0(), iVar5 != 0)) {
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
  if (((DAT_0079352c != 0) && (-1 < iVar5 + 7)) && (iVar6 = FUN_004f30c0(), iVar6 != 0)) {
    if (*(char *)(iVar6 + 0x18) == '\x01') {
      BlitSprite16bpp(0x272,iVar7);
    }
    else {
      BlitSpriteClipped(iVar5 + 7);
    }
  }
  uVar3 = *(undefined2 *)(g_clientContext + 0x50116 + unaff_EDI * 2);
  if ((DAT_0079352c != 0) && (iVar5 = FUN_004f30c0(), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(0x290,iVar7);
    }
    else {
      BlitSpriteClipped(uVar3);
    }
  }
  FUN_004eb510(iVar7 + 1,0x1f);
  BlitRLESprite(iVar7 + 1,0xffff);
  iVar5 = g_clientContext;
  BlitRLESprite(iVar7 + 0xe,0xffff);
  cVar2 = *(char *)(iVar5 + 0x449ba + unaff_EDI);
  if ((DAT_0079352c != 0) && (iVar5 = FUN_004f30c0(), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(0x24d,iVar7 + 6);
      return;
    }
    BlitSpriteClipped((cVar2 != '\0') + '\x04');
  }
  return;
}

