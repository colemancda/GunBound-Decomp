/* Mobile13_ComputeGroundY - 0x0046cbb0 in the original binary.
 *
 * RENAMED (from FUN_0046cbb0): vtable slot 5 (+0x14) of the type-13 mobile
 * vtable 0x555e54 (slot 0 is Mobile13_ScalarDtor at 0x46cb80).  Every other
 * mobile vtable (17 of them in docs/vtable_census.txt) carries
 * ComputeMobileGroundY (0x45c6e0) in slot 5, and SnapMobilesToGround calls
 * that slot per mobile to get the ground Y, so this is the type-13
 * override of the same virtual - src/cxx/Mobile.cpp already says "type 13
 * overrides with 0x46cbb0".  Same five-round skeleton as ComputeMobileGroundY:
 * combine the guard cells at +0xf78 and +0xb30, peek the result, pair it
 * with +0x90c for FindGroundHeightAtColumn.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 9 argless PeekPacketChecksumState() calls (peek status
 * "clean", 9 C : 9 orig), from tools/guard_cell_resolve.py over
 * 0x46cbb0-0x46d00c.
 *
 * The body is five near-identical rounds of "combine two cells, then
 * read the result back and pair it with param_1+0x90c for
 * FindGroundHeightAtColumn".  Six of the nine cells are the chained
 * return of the EncodeChecksumPairDiff / EncodeChecksumDeltaAdd that
 * opens each round - all six discarded by the decompile, now captured
 * in a new uVar5.  A separate uVar1 already holds the DeltaDiv returns
 * and stays live across two rounds, so it could not be reused.
 *
 * The other three cells are param_1 + 0x90c, reached once through the
 * live-in ECX and twice through param_1's frame spill.
 */
#include "ghidra_types.h"


int __fastcall Mobile13_ComputeGroundY(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar5;
  int iVar2;
  int iVar3;
  undefined4 *unaff_FS_OFFSET;
  bool bVar4;
  int local_68c;
  int local_688 [2];
  undefined1 local_680 [8];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00539f08;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uVar1 = EncodeChecksumDeltaDiv(param_1 + 0xf78,local_678,2);
  local_4 = 0;
  uVar5 = EncodeChecksumPairDiff(param_1 + 0xb30,local_454,uVar1);
  SUBFIELD(local_4,0,undefined1) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(param_1 + 0x90c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_68c = FindGroundHeightAtColumn();
  local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&g_valueGuardKeyTable);
    TreeInsert(local_688,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&g_valueGuardKeyTable);
    TreeInsert(local_688,&g_valueGuardMap);
  }
  uVar1 = EncodeChecksumDeltaDiv(param_1 + 0xf78,local_454,2);
  local_4 = 2;
  uVar5 = EncodeChecksumPairDiff(param_1 + 0xb30,local_678,uVar1);
  SUBFIELD(local_4,0,undefined1) = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&g_valueGuardKeyTable);
    TreeInsert(local_688,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&g_valueGuardKeyTable);
    TreeInsert(local_688,&g_valueGuardMap);
  }
  if (local_68c == iVar2) {
    uVar5 = EncodeChecksumPairDiff(param_1 + 0xb30,local_678,param_1 + 0xf78);
    local_4 = 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    PeekPacketChecksumState((void *)uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    PeekPacketChecksumState((void *)(param_1 + 0x90c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    local_688[0] = FindGroundHeightAtColumn();
    local_4 = 0xffffffff;
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&g_valueGuardKeyTable);
      TreeInsert(local_680,&g_valueGuardMap);
    }
    uVar5 = EncodeChecksumPairDiff(param_1 + 0xb30,local_678,param_1 + 0xf78);
    local_4 = 5;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = PeekPacketChecksumState((void *)uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar2 = (*(int *)(local_678 + 0x14));
    bVar4 = local_688[0] == iVar3;
    local_4 = 0xffffffff;
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&g_valueGuardKeyTable);
      local_688[0] = iVar2;
      TreeInsert(local_680,&g_valueGuardMap);
    }
    if (bVar4) {
      uVar5 = EncodeChecksumDeltaAdd(param_1 + 0xb30,local_678,1);
      local_4 = 6;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      PeekPacketChecksumState((void *)uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      local_688[0] = PeekPacketChecksumState((void *)(param_1 + 0x90c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      local_68c = FindGroundHeightAtColumn();
      local_4 = 0xffffffff;
      if ((*(int *)(local_678 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&g_valueGuardKeyTable);
        local_688[0] = (*(int *)(local_678 + 0x14));
        TreeInsert(local_680,&g_valueGuardMap);
      }
      uVar5 = EncodeChecksumDeltaAdd(param_1 + 0xb30,local_230,1);
      local_4 = 7;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar2 = PeekPacketChecksumState((void *)uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      local_4 = 0xffffffff;
      if ((*(int *)(local_230 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_230 + 0x14),&g_valueGuardKeyTable);
        local_688[0] = (*(int *)(local_230 + 0x14));
        TreeInsert(local_680,&g_valueGuardMap);
      }
      if (local_68c == iVar2) {
        local_68c = PeekChecksumStateUnderLock(param_1 + 0xb30);
      }
    }
  }
  iVar2 = *(int *)(param_1 + 0x24);
  *unaff_FS_OFFSET = local_c;
  return local_68c - ((iVar2 == 0xe) - 1 & 0x14);
}

