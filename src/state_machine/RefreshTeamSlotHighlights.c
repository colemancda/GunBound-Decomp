/* RefreshTeamSlotHighlights - 0x004db920 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 5 argless PeekPacketChecksumState() calls - four reads of
 * the acting-slot cell g_clientContext+0x3b49c and one of the game-mode
 * cell +0x45354.  Sites zip 1:1 with the original in address order
 * (0x4db947..0x4dba27).
 */
#include "ghidra_types.h"


void RefreshTeamSlotHighlights(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  iVar3 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b49c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (*(char *)(g_clientContext + 0x458fc + iVar2 * 2) == iVar3) {
LAB_004db999:
      iVar2 = 1;
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b49c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      cVar1 = *(char *)(g_clientContext + 0x458fd + iVar2 * 2);
      if (cVar1 == iVar3) goto LAB_004db999;
      iVar2 = (uint)(uint3)(cVar1 >> 7) << 8;
    }
    SetWidgetReadyState(0,0,iVar2,(int)&g_activeObjectRegistry,iVar3 + 0x64);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0xe);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b49c));
  if (iVar3 == 2) {
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (*(char *)(g_clientContext + 0x458fc + iVar2 * 2) != -1) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b49c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      if (*(char *)(g_clientContext + 0x458fd + iVar3 * 2) != -1) {
        bVar4 = false;
        goto LAB_004dba63;
      }
    }
    bVar4 = true;
  }
  else {
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    bVar4 = *(char *)(g_clientContext + 0x458fc + iVar2 * 2) == -1;
  }
LAB_004dba63:
  SetWidgetReadyState(0,0,bVar4,(int)&g_activeObjectRegistry,0x72);
  return;
}

