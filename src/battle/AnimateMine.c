/* AnimateMine - 0x00498b60 in the original binary.
 *
 * NAMED 2026-08-19 (was a FUN_ name).  slot 2, the per-frame animate tick of the Mine class's
 * vtable.  The class was already fixed by a slot UNIQUE to that vtable (see
 * the InitMine / DestroyMine notes); this slot's role comes from the
 * CProjectile slot map in src/cxx/Projectile.h, and the name was only
 * assigned because this function too appears in exactly one vtable - a slot
 * shared between vtables would say nothing about which class it belongs to.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 24 argless PeekPacketChecksumState() calls (worklist 24).
 * Twin of AnimateSuperMine (this=EBX, spilled to frame[0x20]): cells
 * param_1+0x10/0x99/0x3d5/0xe48 and the global 0x794bf0.  TEN chained
 * returns - the cell pointer returned by EncodeChecksumDeltaSub/DeltaAdd
 * (0x498bd1, 0x498d1d -> frame[0x18], 0x498daa, 0x498e50, 0x498eec ->
 * frame[0x18]), InitGuardedChecksumSlot (0x499224) and
 * EncodeChecksumPairDiff (0x4992d5, 0x499358, 0x499468, 0x49951c), each
 * `mov edi,eax` -> `mov eax,edi; call Peek` or parked in frame[0x18] -
 * captured in iDelta.  Vtable: slot 2 (Animate) of the sub-projectile
 * class 0x5563f0 (dtor 0x497870, ctor InitMine) that SpawnMine
 * builds for DetonateShot1_Bullet7 - i.e. bullet 7's shot-1 cluster
 * child; 0x556380 (AnimateSuperMine's class) derives from it (SpawnSuperMine
 * calls the same ctor then swaps in 0x556380).
 */
#include "ghidra_types.h"


void __fastcall AnimateMine(int *param_1)

{
  uint uVar1;
  char cVar2;
  undefined4 uVar3;
  int iDelta;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *unaff_FS_OFFSET;
  bool bVar8;
  uint local_8c4;
  int local_8b8 [2];
  int local_8b0 [2];
  undefined1 local_8a8 [548];
  undefined1 local_684 [548];
  undefined1 local_460 [548];
  undefined1 auStack_23c [20];
  int iStack_228;
  undefined4 uStack_14;
  undefined1 *puStack_10;
  undefined4 local_c;
  
  local_c = 0xffffffff;
  puStack_10 = &LAB_0053c0d4;
  uStack_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_14;
  FUN_004986a0(param_1);
  AdvanceSpriteAnimation((int)param_1);
  FUN_00498070(param_1);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState((void *)(&DAT_00794bf0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iDelta = EncodeChecksumDeltaSub(param_1 + 0x99,local_8a8,uVar3);
  local_c = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(iDelta));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x10));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped terrain/x/y args - angr-confirmed at
   * 0x498c26. y=EAX came from the first PeekPacketChecksumState()
   * return just above (dropped by Ghidra, captured here as iVar5);
   * x=EDI came from the second Peek's return just above that
   * (captured as iVar6). Same pattern already fixed in
   * src/battle/ComputeMobileGroundY.c. */
  local_8c4 = FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),iVar6,iVar5);
  local_c = 0xffffffff;
  if ((*(int *)(local_8a8 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_8a8 + 0x14),&DAT_0079376c);
    TreeLowerBound(local_8b0);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(param_1 + 0x99));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 < (int)local_8c4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)(param_1 + 0x99));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((int)(local_8c4 + -0xf) <= iVar4) goto LAB_00498f85;
    if ((char)param_1[0xfed] == '\0') {
      *(undefined1 *)(param_1 + 0xfed) = 1;
      param_1[0xfec] = 0;
      param_1[0xfee] = 0;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)(&DAT_00794bf0));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iDelta = EncodeChecksumDeltaSub(param_1 + 0x99,local_8a8,uVar3);
    local_c = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)(iDelta));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_c = 0xffffffff;
    if ((*(int *)(local_8a8 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_8a8 + 0x14),&DAT_0079376c);
      TreeLowerBound(local_8b0);
    }
    if (local_8c4 == iVar4) {
      iDelta = EncodeChecksumDeltaSub(param_1 + 0x99,local_8a8,0x1e);
      local_c = 2;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(iDelta));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x10));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      /* FIXED (2026-07-15): dropped terrain/x/y args - angr-confirmed
       * at 0x498dff, same pattern as the FindGroundHeightAtColumn call
       * above (y=EAX from the first Peek just above, captured as
       * iVar5; x=EDI from the second Peek, captured as iVar6). */
      local_8b8[0] = FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),iVar6,iVar5);
      local_c = 0xffffffff;
      if ((*(int *)(local_8a8 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_8a8 + 0x14),&DAT_0079376c);
        TreeLowerBound(local_8b0);
      }
      iDelta = EncodeChecksumDeltaSub(param_1 + 0x99,local_8a8,0x1e);
      local_c = 3;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState((void *)(iDelta));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      bVar8 = local_8b8[0] == iVar4;
      local_c = 0xffffffff;
      if ((*(int *)(local_8a8 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_8a8 + 0x14),&DAT_0079376c);
        TreeLowerBound(local_8b0);
      }
      if (bVar8) {
        uVar3 = EncodeChecksumDeltaAdd(param_1 + 0x99,local_8a8,1);
        local_c = 4;
        iVar5 = PeekChecksumStateUnderLock(uVar3);
        iVar6 = PeekChecksumStateUnderLock(param_1 + 0x10);
        /* FIXED (2026-07-15): dropped terrain/x/y args - angr-confirmed
         * at 0x498f0b (y=EAX from PeekChecksumStateUnderLock(uVar3)
         * just above, captured as iVar5; x=EDI from
         * PeekChecksumStateUnderLock(param_1 + 0x10), captured as
         * iVar6; both previously discarded). */
        local_8c4 = FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),iVar6,iVar5);
        local_c = 0xffffffff;
        ScrubChecksumGuard();
        uVar3 = EncodeChecksumDeltaAdd(param_1 + 0x99,local_8a8,1);
        local_c = 5;
        iVar4 = PeekChecksumStateUnderLock(uVar3);
        local_c = 0xffffffff;
        ScrubChecksumGuard();
        if (local_8c4 == iVar4) {
          local_8c4 = PeekChecksumStateUnderLock(param_1 + 0x99);
        }
      }
    }
LAB_00498f85:
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x498f93 (`lea edi,[ebx+0x264]` at 0x498f8d, ebx = this file's own
     * param_1 per `mov ebx,ecx` in the prologue) the cell is
     * param_1+0x99 (scaled int* units, byte offset 0x264) - the same
     * cell EncodeChecksumDeltaSub(param_1 + 0x99, ...) throughout this
     * function already addresses. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_1 + 0x99, local_8c4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 != '\0') {
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x498fc8 (`lea edi,[ebx+0x3920]` at 0x498fb7) the cell is
     * param_1+0xe48 (scaled). See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)(param_1 + 0xe48));
    EncodeOutgoingPacketField(param_1 + 0xe48, iVar4 + 1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  iVar4 = param_1[0xfe8];
  param_1[0xfe8] = iVar4 + 1;
  if (iVar4 + 1 == 5) {
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x499005 (`lea edi,[ebx+0x3d6c]` at 0x498ff1) the cell is
     * param_1+0xf5b (scaled). See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    EncodeOutgoingPacketField(param_1 + 0xf5b, uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  if ((char)param_1[0xfed] != '\0') {
    iDelta = EncodeChecksumDeltaAdd(param_1 + 0x99,local_8a8,param_1[0xfee]);
    local_c = 6;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)(iDelta));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_c = 0xffffffff;
    if ((*(int *)(local_8a8 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_8a8 + 0x14),&DAT_0079376c);
      TreeLowerBound(local_8b0);
    }
    if (iVar4 < (int)local_8c4) {
      iVar4 = param_1[0xfee];
      param_1[0xfee] = iVar4 + 1;
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x499122 (`lea edi,[ebx+0x264]` at 0x49910e) the cell is
       * param_1+0x99 (scaled) - same cell as the FIXED call near the
       * top of this function. See
       * tools/encodeoutgoingpacketfield_sites.json. */
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x99));
      EncodeOutgoingPacketField(param_1 + 0x99, iVar5 + iVar4 + 1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    else if (param_1[0xfee] < 5) {
      QueueOutgoingPacketField(local_8c4);
      param_1[0xfee] = 0;
      *(undefined1 *)(param_1 + 0xfed) = 0;
    }
    else {
      QueueOutgoingPacketField(local_8c4 - param_1[0xfee]);
      param_1[0xfee] = 1;
    }
  }
  if ((char)param_1[0xff1] != '\0') {
    iVar4 = param_1[0xff2];
    param_1[0xff2] = iVar4 + 1;
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x499162 (`lea edi,[ebx+0x264]` at 0x499150) the cell is
     * param_1+0x99 (scaled) - same cell as the other FIXED calls in
     * this function. See tools/encodeoutgoingpacketfield_sites.json. */
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x99));
    EncodeOutgoingPacketField(param_1 + 0x99, iVar5 - (iVar4 + 1));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(param_1 + 0x10));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (-1 < iVar4) {
    iVar4 = *(int *)(&g_nCameraBoundX + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x10));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar5 < iVar4) {
      iVar4 = *(int *)(&g_nCameraBoundY + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x99));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((iVar5 < iVar4) && (cVar2 = PacketChecksumLessThan(param_1 + 0x99,0xffffff38), cVar2 == '\0'))
      goto LAB_00499217;
    }
  }
  *(undefined1 *)(param_1 + 5) = 1;
LAB_00499217:
  iDelta = InitGuardedChecksumSlot(param_1 + 0xc66,local_8a8,param_1 + 0xc66);
  local_c = 7;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(iDelta));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_c = 0xffffffff;
  if ((*(int *)(local_8a8 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_8a8 + 0x14),&DAT_0079376c);
    local_8b8[0] = (*(int *)(local_8a8 + 0x14));
    TreeLowerBound(local_8b0);
  }
  local_8c4 = 0;
  do {
    iVar5 = GetPlayerRecordBySlot(g_clientContext);
    if ((iVar5 != 0) && (cVar2 = PeekPacketChecksumBool((byte *)(iVar5 + 0xbff7)), cVar2 != '\x01')) {
      iDelta = EncodeChecksumPairDiff(param_1 + 0x10,local_684,iVar5 + 0x90c);
      local_c = 8;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState((void *)(iDelta));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_c = 0xffffffff;
      local_8b8[0] = (*(int *)(local_684 + 0x14));
      if ((*(int *)(local_684 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_684 + 0x14),&DAT_0079376c);
        TreeLowerBound(local_8b0);
      }
      iDelta = EncodeChecksumPairDiff(param_1 + 0x99,local_460,iVar5 + 0xb30);
      local_c = 9;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(iDelta));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_c = 0xffffffff;
      local_8b8[0] = (*(int *)(local_460 + 0x14));
      if ((*(int *)(local_460 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_460 + 0x14),&DAT_0079376c);
        TreeLowerBound(local_8b0);
      }
      if (iVar5 * iVar5 + iVar6 * iVar6 < iVar4) {
        (**(code **)(*param_1 + 0x20))();
      }
    }
    local_8c4 = local_8c4 + 1;
  } while ((int)local_8c4 < 8);
  local_8c4 = 0;
  do {
    iVar5 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar1 = *(uint *)(iVar5 + 4);
    while (uVar1 < 0x186a7) {
      if (uVar1 == 0x186a6) {
        iVar5 = *(int *)(iVar5 + 0x10);
        uVar1 = *(uint *)(iVar5 + 8);
        if (uVar1 <= local_8c4) goto LAB_00499440;
        break;
      }
      iVar5 = *(int *)(iVar5 + 0x1c);
      uVar1 = *(uint *)(iVar5 + 4);
    }
LAB_004995d6:
    local_8c4 = local_8c4 + 1;
    if (7 < (int)local_8c4) {
      if ((char)param_1[0xff1] == '\0') {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x10));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar4 = FUN_00451030(uVar3);
        if (iVar4 != 0) {
          *(undefined1 *)(param_1 + 0xfed) = 0;
          *(undefined1 *)(param_1 + 0xff1) = 1;
          param_1[0xff2] = 0;
        }
      }
      *unaff_FS_OFFSET = uStack_14;
      return;
    }
  } while( true );
LAB_00499440:
  if (uVar1 != local_8c4) goto code_r0x00499442;
  iDelta = EncodeChecksumPairDiff(param_1 + 0x10,local_684,iVar5 + 0x25c);
  local_c = 10;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8b0[0] = PeekPacketChecksumState((void *)(iDelta));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_c = 0xffffffff;
  if ((*(int *)(local_684 + 0x14)) != 0) {
    iVar6 = (*(int *)(local_684 + 0x14)) << 4;
    local_8b8[0] = 0x10;
    do {
      iVar7 = _rand();
      *(char *)(iVar6 + DAT_0079376c) = (char)iVar7;
      iVar6 = iVar6 + 1;
      local_8b8[0] = local_8b8[0] + -1;
    } while (local_8b8[0] != 0);
    TreeLowerBound(local_8b8);
  }
  iDelta = EncodeChecksumPairDiff(param_1 + 0x99,auStack_23c,iVar5 + 0x480);
  local_c = 0xb;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(iDelta));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_c = 0xffffffff;
  if (iStack_228 != 0) {
    iVar6 = iStack_228 << 4;
    local_8b8[0] = 0x10;
    do {
      iVar7 = _rand();
      *(char *)(iVar6 + DAT_0079376c) = (char)iVar7;
      iVar6 = iVar6 + 1;
      local_8b8[0] = local_8b8[0] + -1;
    } while (local_8b8[0] != 0);
    TreeLowerBound(local_8b8);
  }
  if (local_8b0[0] * local_8b0[0] + iVar5 * iVar5 < iVar4) {
    (**(code **)(*param_1 + 0x20))();
  }
  goto LAB_004995d6;
code_r0x00499442:
  iVar5 = *(int *)(iVar5 + 0x10);
  uVar1 = *(uint *)(iVar5 + 8);
  if (local_8c4 < uVar1) goto LAB_004995d6;
  goto LAB_00499440;
}

