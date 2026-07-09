/* State03_GameRoomList_RenderRoomLabel - 0x00429810 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


void __fastcall State03_GameRoomList_RenderRoomLabel(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  char *pcVar7;
  char acStack_80 [128];
  
  if ((DAT_0079352c != 0) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
    if (*(char *)(iVar3 + 0x18) == '\x01') {
      BlitSprite16bpp(0);
    }
    else {
      BlitSpriteClipped(0);
    }
  }
  iVar3 = g_clientContext;
  uVar2 = *(undefined2 *)(g_clientContext + 0x23344);
  if ((DAT_0079352c != 0) && (iVar4 = FindSpriteFrame(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(0xac,9);
    }
    else {
      BlitSpriteClipped(uVar2);
    }
  }
  if (*(char *)(iVar3 + 0x23313) != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    _sprintf(acStack_80,s__s__3d__3d__005536b8,g_clientContext + 0x23313,uVar6,uVar5);
    BlitRLESprite(9,0xfd0f);
  }
  BlitRLESprite(0x17,0xffff);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  pcVar7 = (char *)GetLocalizedString(&DAT_00796eec,20000);
  _sprintf(acStack_80,pcVar7,uVar5);
  pcVar7 = acStack_80;
  do {
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  BlitRLESprite(9,0xffff);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  pcVar7 = (char *)GetLocalizedString(&DAT_00796eec,0x4e21);
  _sprintf(acStack_80,pcVar7,uVar5);
  pcVar7 = acStack_80;
  do {
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  BlitRLESprite(0x16,0xffff);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  pcVar7 = (char *)GetLocalizedString(&DAT_00796eec,0x4e22);
  _sprintf(acStack_80,pcVar7,uVar5);
  BlitRLESprite(0x27,0x1f3b);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  pcVar7 = (char *)GetLocalizedString(&DAT_00796eec,0x4e23);
  _sprintf(acStack_80,pcVar7,uVar5);
  pcVar7 = acStack_80;
  do {
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  BlitRLESprite(0x27,0xe703);
  iVar4 = 0;
  iVar3 = 0x4464c;
  do {
    if ((*(int *)(iVar3 + g_clientContext) != 0) && (iVar4 != *(int *)(param_1 + 0x124))) {
      RenderRoomCard(iVar4);
    }
    iVar3 = iVar3 + 4;
    iVar4 = iVar4 + 1;
  } while (iVar3 < 0x44664);
  return;
}

