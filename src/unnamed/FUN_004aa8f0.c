/* FUN_004aa8f0 - 0x004aa8f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 17 argless PeekPacketChecksumState() calls (peek status
 * "clean", 17 C : 17 orig).  Cells from tools/guard_cell_resolve.py over
 * 0x4aa8f0-0x4aac7e.  Straight-line, no gotos, and every cell resolves
 * directly off the incoming ECX with no spills, chained returns or
 * frame slots involved - the simplest shape this sweep has hit.
 *
 * Layout is the detonation-twin tail: the ten-cell crater block
 * (0x6ac/0x488/0x2f74/0x2d50/0x2b2c/0x2908/0x26e4/0x24c0/0x1178/0xf54),
 * then three 0x1178+0xf54 pairs, then a lone &DAT_007949c8.
 */
#include "ghidra_types.h"


void __fastcall FUN_004aa8f0(int param_1)

{
  int iCraterX;
  int iCraterY;
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  code *pcVar12;
  
  *(undefined1 *)(param_1 + 0x14) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x6ac));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar4 = PeekPacketChecksumState((void *)(param_1 + 0x488));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar5 = PeekPacketChecksumState((void *)(param_1 + 0x2f74));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar6 = PeekPacketChecksumState((void *)(param_1 + 0x2d50));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar7 = PeekPacketChecksumState((void *)(param_1 + 0x2b2c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x2908));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar9 = PeekPacketChecksumState((void *)(param_1 + 0x26e4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar10 = PeekPacketChecksumState((void *)(param_1 + 0x24c0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iCraterY = PeekPacketChecksumState((void *)(param_1 + 0x1178));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iCraterX = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  ApplyCraterExcavation(uVar10,uVar9,uVar8,uVar7,uVar6,uVar5,uVar4,uVar3,
                 (int)(&DAT_006a7708 + g_clientContext),(int)iCraterX,(int)iCraterY);
  RebuildTerrainColumnCache(&DAT_006a7708 + g_clientContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
  pcVar12 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar4 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  FUN_00450eb0(uVar4,uVar3,param_1,1,0,0);
  if (*(int *)(param_1 + 0x3f90) != 0xff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar4 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    SpawnCrashEffect(uVar4, uVar3, *(int *)(param_1 + 0x3f90));
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar4 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  SpawnFlameEffect(*(undefined4 *)(param_1 + 8),uVar4,uVar3,*(undefined4 *)(param_1 + 0x3894),
               param_1 + 0x3898);
  iVar1 = g_clientContext;
  cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar2 != '\x01') {
    iVar11 = *(int *)(&DAT_006a7750 + iVar1);
    if (iVar11 < 0x10) {
      iVar11 = 0xf;
    }
    *(int *)(&DAT_006a7750 + iVar1) = iVar11;
    iVar11 = *(int *)(&DAT_006a7754 + iVar1);
    if (iVar11 < 0xb) {
      iVar11 = 10;
    }
    *(int *)(&DAT_006a7754 + iVar1) = iVar11;
  }
  cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar2 == '\0') {
    AcquireSoundChannel(0);
    pcVar12 = (code *)LeaveCriticalSection;
  }
  cVar2 = PeekPacketChecksumBool((byte *)(param_1 + 0xf3f));
  if (cVar2 != '\0') {
    cVar2 = InitChecksumSeed();
    if (cVar2 == '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)&DAT_007949c8);
      (*pcVar12)(&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      /* FIXED (2026-07-16): dropped `self` arg - angr-confirmed at
       * 0x4aac3e: self is g_clientContext+0x621e8 (`mov edi,[0x5b3484];
       * add edi,0x621e8`), a different cell from the immediately
       * preceding peek's own self (a fixed global, 0x7949c8) - value
       * (uVar3) was already correct. */
      EncodeOutgoingPacketField((void *)(g_clientContext + 0x621e8), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar1 = g_clientContext;
      if (*(int *)(&DAT_005f3768 + g_clientContext) != 0) {
        *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar1) = 0;
      }
    }
  }
  return;
}

