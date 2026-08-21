/* AdvanceTurnQueue - 0x004cf310 in the original binary.
 *
 * RENAMED (2026-08-13, from FUN_004cf310). Consumes the head of the
 * battle turn queue and advances to the next player.
 *
 * The queue is a byte array at param_1+0x10a8 with its length at
 * param_1+0x10b0.  The function returns immediately when that length is
 * zero; otherwise it retires the head slot and then shifts the array
 * down by one, stores 0xff into the vacated tail entry, and decrements
 * the length - a plain pop-front.
 *
 * Retiring the head means writing 0xffffffff into that player's cell in
 * the per-player delay array, g_clientContext + 0xebef4 + slot*0x224 -
 * the same array SortTurnOrderByDelay orders the turn list by, which is
 * what ties these two together.  It also compares the head slot against
 * the current-slot index at g_clientContext+0x3b49c (again shared with
 * SortTurnOrderByDelay) and, when they match, either tears down the
 * aiming widgets or marks the local player done depending on the battle
 * mode at g_clientContext+0x45354.
 *
 * Call sites match that role: State11_InBattle_OnTick calls it when the
 * per-turn countdown at [0x42d] reaches zero, and
 * State11_InBattle_ProcessBattleAction calls it from three of the
 * turn-end cases after setting the next battle phase in [0x42e].
 *
 * FIXED (2026-07-16): the 2 EncodeOutgoingPacketField calls dropped self -
 * confirmed via angr (tools/encodeoutgoingpacketfield_sites.json, func_addr
 * 0x004cf310) plus manual disassembly of each site (orig/GunBound.gme,
 * 0x4cf6ce and 0x4cf781). Both are the same signed-mod array-cell index
 * pattern already visible in this file's own EncodeChecksumPairSum call a
 * few lines above (`(*(byte *)(param_1 + 0x10a8) & 0x80000007) * 0x224 +
 * 0xebef4 + g_clientContext`): the first call's self recomputes that same
 * index but into a parallel table at +0xee134 instead of +0xebef4 (a
 * distinct field Ghidra's decompile never assigned to a local); the second
 * call's self is the exact same +0xebef4 cell that EncodeChecksumPairSum
 * already uses.
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 11 argless PeekPacketChecksumState() calls (peek status
 * "clean", 11 C : 11 orig).  Cells from tools/guard_cell_resolve.py over
 * 0x4cf310-0x4cf8fb.
 *
 * Four hang off piVar2, the GetPlayerRecordBySlot return at 0x4cf354
 * (+0xb30 and +0x90c, read twice each); the resolver stops at
 * `<clobbered by call>` there.  Five are g_clientContext globals, two of
 * which the C itself corroborates: the +0x45354 reads sit immediately
 * beside the existing PacketChecksumNotEquals(g_clientContext + 0x45354,
 * 3) and PacketChecksumEquals(g_clientContext + 0x45354, 3) calls.  The
 * 0x4cf59d/0x4cf5d4 pair reads frame[0x14], loaded with that same
 * +0x45354 address one push deep at 0x4cf593/0x4cf5ca.
 *
 * One cell is a chained return: EncodeChecksumPairSum (0x4cf682)
 * returns its dest cell in EAX, the decompile discarded it, and the
 * Peek at 0x4cf6c4 re-reads it - captured in a new uVar10.  Its Encode
 * partner at 0x4cf6ce targets a DIFFERENT cell (the +0xee134 table the
 * 2026-07-16 note above describes), so the read and the write are not
 * the same address at that site. */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x004cf69f) */
/* WARNING: Removing unreachable block (ram,0x004cf617) */
/* WARNING: Removing unreachable block (ram,0x004cf5fe) */
/* WARNING: Removing unreachable block (ram,0x004cf669) */
/* WARNING: Removing unreachable block (ram,0x004cf761) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall AdvanceTurnQueue(int param_1)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  byte bVar8;
  int unaff_EBX;
  code *pcVar9;
  undefined4 uVar10;
  uint *unaff_FS_OFFSET;
  int local_464;
  int local_460;
  undefined *local_45c;
  undefined1 auStack_458 [16];
  int iStack_448;
  undefined1 auStack_234 [16];
  int iStack_224;
  uint uStack_20;
  uint local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_00540806;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (uint)&local_c;
  local_460 = param_1;
  if (*(int *)(param_1 + 0x10b0) != 0) {
    piVar2 = (int *)GetPlayerRecordBySlot(g_clientContext);
    pcVar9 = (code *)LeaveCriticalSection;
    if (piVar2 != (int *)0x0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState((void *)(piVar2 + 0x2cc));
      pcVar9 = (code *)LeaveCriticalSection;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_464 = PeekPacketChecksumState((void *)(piVar2 + 0x243));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_45c = &DAT_006a7708 + g_clientContext;
      cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
      iVar5 = local_464;
      if ((cVar1 == '\0') && (local_45c[0x50] != '\0')) {
        iVar4 = 400;
        if (399 < local_464) {
          iVar4 = local_464;
        }
        local_464 = *(int *)(local_45c + 0x18) + -400;
        if ((iVar4 <= local_464) && (local_464 = 400, 399 < iVar5)) {
          local_464 = iVar5;
        }
        iVar5 = -0x14;
        if (-0x15 < iVar3) {
          iVar5 = iVar3;
        }
        iVar4 = *(int *)(local_45c + 0x1c) + -0x104;
        if ((iVar5 <= *(int *)(local_45c + 0x1c) + -0x104) && (iVar4 = -0x14, -0x15 < iVar3)) {
          iVar4 = iVar3;
        }
        *(int *)(local_45c + 0x10) = local_464;
        *(int *)(local_45c + 0x14) = iVar4;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState((void *)(piVar2 + 0x2cc));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_45c = (undefined *)PeekPacketChecksumState((void *)(piVar2 + 0x243));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      SpawnRiderEffect(*(undefined1 *)(param_1 + 0x10a8),1000);
      (**(code **)(*piVar2 + 4))(&DAT_00555c90);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((iVar5 == 1) || (cVar1 = PacketChecksumNotEquals(g_clientContext + 0x45354,3), cVar1 == '\0')
         ) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = _rand();
        *(char *)((int)piVar2 + 0xbff7) = (char)iVar5;
        iVar5 = _rand();
        *(byte *)(piVar2 + 0x2ffe) = (byte)iVar5;
        bVar8 = '\x01' << (*(byte *)((int)piVar2 + 0xbff7) & 7);
        bVar8 = ~bVar8 & (byte)iVar5 | bVar8;
        *(byte *)(piVar2 + 0x2ffe) = bVar8;
        *(byte *)((int)piVar2 + 0xbff9) = bVar8 + *(char *)((int)piVar2 + 0xbff7) + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        param_1 = local_460;
      }
      else {
        SetGuardedBool(0,GB_GUARD_UNRECOVERED);
        param_1 = local_460;
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
    (*pcVar9)(&DAT_005a9068);
    if ((char)((uint)unaff_EBX >> 0x18) != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
      unaff_EBX = CONCAT13(iVar5 != 3,(int3)unaff_EBX);
      (*pcVar9)(&DAT_005a9068);
      if (iVar5 != 3) {
        FUN_0043c440();
        FUN_0043c4a0();
        FUN_0043c4f0();
      }
    }
    uVar6 = EncodeChecksumDeltaMul(piVar2 + 0x237a,auStack_234,2);
    puStack_8 = (undefined1 *)0x0;
    uVar10 = EncodeChecksumPairSum((*(byte *)(param_1 + 0x10a8) & 0x80000007) * 0x224 + 0xebef4 + g_clientContext,
                 auStack_458,uVar6);
    puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState((void *)uVar10);
    EncodeOutgoingPacketField((*(byte *)(param_1 + 0x10a8) & 0x80000007) * 0x224 + 0xee134 + g_clientContext,
                              uVar6);
    (*pcVar9)(&DAT_005a9068);
    local_c = local_c & 0xffffff00;
    if (iStack_448 != 0) {
      ScrambleChecksumGuardBytes(iStack_448,&DAT_0079376c);
      TreeLowerBound(&local_464);
      pcVar9 = (code *)LeaveCriticalSection;
      unaff_EBX = iStack_448;
    }
    local_c = 0xffffffff;
    if (iStack_224 != 0) {
      ScrambleChecksumGuardBytes(iStack_224,&DAT_0079376c);
      TreeLowerBound(&local_464);
      pcVar9 = (code *)LeaveCriticalSection;
      unaff_EBX = iStack_224;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((*(byte *)(param_1 + 0x10a8) & 0x80000007) * 0x224 + 0xebef4 + g_clientContext,
                              0xffffffff);
    (*pcVar9)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b49c));
    (*pcVar9)(&DAT_005a9068);
    if (*(byte *)(param_1 + 0x10a8) == uVar7) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
      cVar1 = '\x01' - (iVar5 != 1);
      (*pcVar9)(&DAT_005a9068);
      if ((cVar1 == '\0') && (cVar1 = PacketChecksumEquals(g_clientContext + 0x45354,3), cVar1 == '\0')
         ) {
        if (*(char *)(g_clientContext + 0x45126) != '\0') {
          FUN_004e1f70();
          RemoveWidget((int)&DAT_00e9be90,0,3);
          RemoveWidget((int)&DAT_00e9be90,0,0xf);
          pcVar9 = (code *)LeaveCriticalSection;
          *(undefined4 *)(&DAT_006a73c8 + g_clientContext) = 1;
          param_1 = unaff_EBX;
        }
      }
      else {
        iVar5 = g_clientContext;
        *(undefined1 *)(param_1 + 0x93) = 1;
        (&DAT_006a7758)[iVar5] = 0;
      }
    }
    iVar5 = 0;
    if (*(int *)(param_1 + 0x10b0) != 1 && -1 < *(int *)(param_1 + 0x10b0) + -1) {
      do {
        *(undefined1 *)(param_1 + 0x10a8 + iVar5) = *(undefined1 *)(param_1 + 0x10a9 + iVar5);
        iVar5 = iVar5 + 1;
      } while (iVar5 < *(int *)(param_1 + 0x10b0) + -1);
    }
    *(undefined1 *)(iVar5 + 0x10a8 + param_1) = 0xff;
    *(int *)(param_1 + 0x10b0) = *(int *)(param_1 + 0x10b0) + -1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
    (*pcVar9)(&DAT_005a9068);
    *(undefined4 *)(param_1 + 0x10b4) = uVar6;
    *unaff_FS_OFFSET = uStack_20;
    return;
  }
  if (*(char *)(param_1 + 0x11d0) == '\0') {
    switch(*(undefined4 *)(param_1 + 0x10b8)) {
    case 0:
      SetGuardedBool(0,GB_GUARD_UNRECOVERED);
      FUN_004ccd10(param_1);
      *unaff_FS_OFFSET = local_c;
      return;
    case 1:
      cVar1 = PacketChecksumEquals(g_clientContext + 0x45354,3);
      if ((cVar1 != '\0') && (cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f90)), cVar1 == '\x01')) {
        SetGuardedBool(0,GB_GUARD_UNRECOVERED);
        *(undefined1 *)(param_1 + 0x94) = 1;
        uVar6 = PeekChecksumStateUnderLock(&DAT_00794bf0);
        cVar1 = PacketChecksumLessThan(&DAT_006a8e90 + g_clientContext,uVar6);
        if (cVar1 == '\0') {
          cVar1 = PacketChecksumLessThan(&DAT_006a8e90 + g_clientContext,0x28);
          if (cVar1 == '\0') {
            cVar1 = PacketChecksumLessThan(&DAT_006a8e90 + g_clientContext,0x50);
            iVar5 = 3 - (uint)(cVar1 != '\0');
          }
          else {
            iVar5 = 1;
          }
        }
        else {
          iVar5 = 0;
        }
        uVar6 = 1;
        iVar3 = PeekChecksumStateUnderLock(&DAT_006a81b8 + g_clientContext);
        SpawnJewel(&DAT_006a7f70 + g_clientContext,iVar3 % *(int *)(&g_nCameraBoundX + g_clientContext),
                     iVar5,uVar6);
        *unaff_FS_OFFSET = local_c;
        return;
      }
      cVar1 = PacketChecksumEquals(g_clientContext + 0x45354,1);
      if ((cVar1 == '\0') && (cVar1 = PacketChecksumEquals(g_clientContext + 0x45354,3), cVar1 == '\0')
         ) {
        *(undefined1 *)(param_1 + 0x94) = 0;
        FUN_004ce610(param_1);
        *unaff_FS_OFFSET = local_c;
        return;
      }
      *(undefined1 *)(param_1 + 0x94) = 1;
      FUN_004ce3d0(param_1);
      *unaff_FS_OFFSET = local_c;
      return;
    case 2:
      g_stateChangeRequested = 0;
      DAT_0056d108 = 0;
      g_pendingGameState = 9;
      _DAT_007934d8 = 1;
      *unaff_FS_OFFSET = local_c;
      return;
    case 3:
      FUN_004cea70(param_1);
      *unaff_FS_OFFSET = local_c;
      return;
    case 4:
      FUN_004cee30(param_1);
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

