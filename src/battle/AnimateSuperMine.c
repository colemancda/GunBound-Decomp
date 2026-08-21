/* AnimateSuperMine - 0x004921e0 in the original binary.
 *
 * NAMED 2026-08-19 (was a FUN_ name).  slot 2, the per-frame animate tick of the SuperMine class's
 * vtable.  The class was already fixed by a slot UNIQUE to that vtable (see
 * the InitSuperMine / DestroySuperMine notes); this slot's role comes from the
 * CProjectile slot map in src/cxx/Projectile.h, and the name was only
 * assigned because this function too appears in exactly one vtable - a slot
 * shared between vtables would say nothing about which class it belongs to.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 27 argless PeekPacketChecksumState() calls.  (The worklist's
 * 33 counts six sites past this function's `ret` at 0x492f44 - the
 * 0x492ffb+ tail belongs to the next function; MISMATCH flavour (d).)
 * this=EBX at entry, spilled to frame[0x20] = local_ae0 and reloaded;
 * cells param_1+0x10/0x99/0x3d5/0xe48 (byte 0x40/0x264/0xf54/0x3920) and
 * the global 0x794bf0.  ELEVEN chained returns: the decompile discarded
 * the cell pointer returned by EncodeChecksumDeltaSub/DeltaAdd (0x49224b,
 * 0x49240e, 0x492494, 0x49253a, 0x492714), InitGuardedChecksumSlot
 * (0x49291f) and EncodeChecksumPairDiff (0x4929d5, 0x492a58, 0x492b6e,
 * 0x492c1d, 0x492e15) - each `mov edi,eax` -> `mov eax,edi; call Peek` -
 * now captured in iDelta; two more were already kept in local_aec[0]
 * (0x492323 -> frame[0x14]) and local_ad8[0] (0x492d81 frame[0x28]).
 */
#include "ghidra_types.h"


void __fastcall AnimateSuperMine(int *param_1)

{
  uint uVar1;
  char cVar2;
  undefined4 uVar3;
  int iDelta;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  undefined4 *unaff_FS_OFFSET;
  bool bVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int local_aec [2];
  uint local_ae4;
  int *local_ae0;
  int local_adc;
  int local_ad8 [2];
  int local_ad0;
  undefined1 local_acc [548];
  undefined1 local_8a8 [548];
  undefined1 auStack_684 [20];
  int iStack_670;
  undefined1 local_460 [548];
  undefined1 auStack_23c [20];
  int iStack_228;
  undefined4 uStack_14;
  undefined1 *puStack_10;
  undefined4 local_c;
  
  local_c = 0xffffffff;
  puStack_10 = &LAB_0053c205;
  uStack_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_14;
  local_ae0 = param_1;
  FUN_004986a0(param_1);
  AdvanceSpriteAnimation((int)param_1);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState((void *)(&DAT_00794bf0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iDelta = EncodeChecksumDeltaSub(param_1 + 0x99,local_acc,uVar3);
  local_c = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar10 = PeekPacketChecksumState((void *)(iDelta));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_aec[0] = PeekPacketChecksumState((void *)(param_1 + 0x10));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FindGroundHeightAtColumn args recovered via angr taint scan @0x4922a0:
   * EDI/x = local_aec[0] (the PeekPacketChecksumState() return captured just
   * above); EAX/y = return of the PREVIOUS PeekPacketChecksumState() call
   * (iVar10, discarded by Ghidra since it mis-modeled this call's real
   * ECX/EDX/EDI/EAX convention). */
  local_ae4 = FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),local_aec[0],iVar10);
  iVar4 = (*(int *)(local_acc + 0x14));
  local_c = 0xffffffff;
  if ((*(int *)(local_acc + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_acc + 0x14),&DAT_0079376c);
    local_aec[0] = iVar4;
    TreeLowerBound(local_ad8,&DAT_00793770);
    param_1 = local_ae0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(param_1 + 0x99));
  bVar9 = iVar4 < (int)local_ae4;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (bVar9) {
    local_aec[0] = EncodeChecksumDeltaSub(param_1 + 0x99,local_acc,local_ae4);
    local_c = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(&DAT_00794bf0));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState((void *)(local_aec[0]));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = (*(int *)(local_acc + 0x14));
    local_c = 0xffffffff;
    if ((*(int *)(local_acc + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_acc + 0x14),&DAT_0079376c);
      local_aec[0] = iVar4;
      TreeLowerBound(local_ad8,&DAT_00793770);
      param_1 = local_ae0;
    }
    if (-iVar5 <= iVar6) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      goto LAB_00492677;
    }
    if ((char)param_1[0xfed] == '\0') {
      *(undefined1 *)(param_1 + 0xfed) = 1;
      param_1[0xfec] = 0;
      param_1[0xfee] = 0;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_aec[0] = PeekPacketChecksumState((void *)(&DAT_00794bf0));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iDelta = EncodeChecksumDeltaSub(param_1 + 0x99,local_acc,local_aec[0]);
    local_c = 2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(iDelta));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = (*(int *)(local_acc + 0x14));
    bVar9 = local_ae4 == iVar5;
    local_c = 0xffffffff;
    if ((*(int *)(local_acc + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_acc + 0x14),&DAT_0079376c);
      local_aec[0] = iVar4;
      TreeLowerBound(local_ad8,&DAT_00793770);
      param_1 = local_ae0;
    }
    if (bVar9) {
      iDelta = EncodeChecksumDeltaSub(param_1 + 0x99,local_acc,0x1e);
      local_c = 3;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar11 = PeekPacketChecksumState((void *)(iDelta));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_aec[0] = PeekPacketChecksumState((void *)(param_1 + 0x10));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      /* FindGroundHeightAtColumn args recovered via angr taint scan @0x4924e9:
       * EDI/x = local_aec[0] (the PeekPacketChecksumState() return captured
       * just above); EAX/y = return of the PREVIOUS PeekPacketChecksumState()
       * call (iVar11, discarded by Ghidra). */
      local_ad0 = FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),local_aec[0],iVar11);
      iVar4 = (*(int *)(local_acc + 0x14));
      local_c = 0xffffffff;
      if ((*(int *)(local_acc + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_acc + 0x14),&DAT_0079376c);
        local_aec[0] = iVar4;
        TreeLowerBound(local_ad8,&DAT_00793770);
        param_1 = local_ae0;
      }
      iDelta = EncodeChecksumDeltaSub(param_1 + 0x99,local_acc,0x1e);
      local_c = 4;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(iDelta));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = (*(int *)(local_acc + 0x14));
      bVar9 = local_ad0 == iVar5;
      local_c = 0xffffffff;
      if ((*(int *)(local_acc + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_acc + 0x14),&DAT_0079376c);
        local_aec[0] = iVar4;
        TreeLowerBound(local_ad8,&DAT_00793770);
        param_1 = local_ae0;
      }
      if (bVar9) {
        uVar3 = EncodeChecksumDeltaAdd(param_1 + 0x99,local_acc,1);
        local_c = 5;
        local_aec[0] = PeekChecksumStateUnderLock(uVar3);
        iVar12 = PeekChecksumStateUnderLock(param_1 + 0x10);
        /* FindGroundHeightAtColumn args recovered via angr taint scan @0x4925f5:
         * EDI/x = return of the PeekChecksumStateUnderLock(param_1 + 0x10)
         * call just above (iVar12, discarded by Ghidra); EAX/y = local_aec[0]
         * (the PeekChecksumStateUnderLock(uVar3) return captured on the line
         * before that). */
        iVar4 = FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),iVar12,local_aec[0]);
        local_c = 0xffffffff;
        local_ae4 = iVar4;
        ScrubChecksumGuard();
        uVar3 = EncodeChecksumDeltaAdd(param_1 + 0x99,local_acc,1);
        local_c = 6;
        iVar5 = PeekChecksumStateUnderLock(uVar3);
        local_c = 0xffffffff;
        ScrubChecksumGuard();
        if (iVar4 == iVar5) {
          local_ae4 = PeekChecksumStateUnderLock(param_1 + 0x99);
        }
      }
    }
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x49267d (`lea edi,[ebx+0x264]` at 0x492677, ebx = this file's own
     * param_1 per `mov ebx,ecx` in the prologue) the cell is
     * param_1+0x99 (scaled int* units, byte offset 0x264) - the same
     * cell EncodeChecksumDeltaSub(param_1 + 0x99, ...) throughout this
     * function already addresses. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
LAB_00492677:
    EncodeOutgoingPacketField(param_1 + 0x99, local_ae4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 != '\0') {
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x4926ae (`lea edi,[ebx+0x3920]` at 0x49269d) the cell is
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
     * 0x4926e7 (`lea edi,[ebx+0x3d6c]` at 0x4926d3) the cell is
     * param_1+0xf5b (scaled). See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    EncodeOutgoingPacketField(param_1 + 0xf5b, uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  if ((char)param_1[0xfed] != '\0') {
    iDelta = EncodeChecksumDeltaAdd(param_1 + 0x99,local_acc,param_1[0xfee]);
    local_c = 7;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)(iDelta));
    bVar9 = iVar4 < (int)local_ae4;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = (*(int *)(local_acc + 0x14));
    local_c = 0xffffffff;
    if ((*(int *)(local_acc + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_acc + 0x14),&DAT_0079376c);
      local_aec[0] = iVar4;
      TreeLowerBound(local_ad8,&DAT_00793770);
      param_1 = local_ae0;
    }
    if (bVar9) {
      local_aec[0] = param_1[0xfee] + 1;
      param_1[0xfee] = local_aec[0];
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x4927fc (`lea edi,[ebx+0x264]` at 0x4927e8) the cell is
       * param_1+0x99 (scaled) - same cell as the FIXED call near the top
       * of this function. See
       * tools/encodeoutgoingpacketfield_sites.json. */
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState((void *)(param_1 + 0x99));
      EncodeOutgoingPacketField(param_1 + 0x99, iVar4 + local_aec[0]);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    else if (param_1[0xfee] < 5) {
      QueueOutgoingPacketField(local_ae4);
      param_1[0xfee] = 0;
      *(undefined1 *)(param_1 + 0xfed) = 0;
    }
    else {
      QueueOutgoingPacketField(local_ae4 - param_1[0xfee]);
      param_1[0xfee] = 1;
    }
  }
  if ((char)param_1[0xff1] != '\0') {
    local_aec[0] = param_1[0xff2] + 1;
    param_1[0xff2] = local_aec[0];
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x49283e (`lea edi,[ebx+0x264]` at 0x49282c) the cell is
     * param_1+0x99 (scaled) - same cell as the other FIXED calls in this
     * function. See tools/encodeoutgoingpacketfield_sites.json. */
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)(param_1 + 0x99));
    EncodeOutgoingPacketField(param_1 + 0x99, iVar4 - local_aec[0]);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(param_1 + 0x10));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (-1 < iVar4) {
    local_aec[0] = *(int *)(&g_nCameraBoundX + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)(param_1 + 0x10));
    bVar9 = iVar4 < local_aec[0];
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (bVar9) {
      local_aec[0] = *(int *)(&g_nCameraBoundY + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState((void *)(param_1 + 0x99));
      bVar9 = iVar4 < local_aec[0];
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((bVar9) && (cVar2 = PacketChecksumLessThan(param_1 + 0x99,0xffffff38), cVar2 == '\0'))
      goto LAB_00492912;
    }
  }
  iVar4 = g_clientContext;
  *(undefined1 *)(param_1 + 5) = 1;
  *(undefined4 *)(&DAT_005f3768 + iVar4) = 5;
  *(undefined4 *)(&DAT_005f376c + iVar4) = 0;
LAB_00492912:
  iDelta = InitGuardedChecksumSlot(param_1 + 0xc66,local_acc,param_1 + 0xc66);
  local_c = 8;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_ad0 = PeekPacketChecksumState((void *)(iDelta));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_c = 0xffffffff;
  if ((*(int *)(local_acc + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_acc + 0x14),&DAT_0079376c);
    local_aec[0] = (*(int *)(local_acc + 0x14));
    TreeLowerBound(local_ad8,&DAT_00793770);
  }
  local_ae4 = 0;
  do {
    iVar4 = GetPlayerRecordBySlot(g_clientContext);
    if ((iVar4 != 0) && (cVar2 = PeekPacketChecksumBool((byte *)(iVar4 + 0xbff7)), cVar2 != '\x01')) {
      iDelta = EncodeChecksumPairDiff(local_ae0 + 0x10,local_8a8,iVar4 + 0x90c);
      local_c = 9;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_adc = PeekPacketChecksumState((void *)(iDelta));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_c = 0xffffffff;
      local_aec[0] = (*(int *)(local_8a8 + 0x14));
      if ((*(int *)(local_8a8 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_8a8 + 0x14),&DAT_0079376c);
        TreeLowerBound(local_ad8,&DAT_00793770);
      }
      iDelta = EncodeChecksumPairDiff(local_ae0 + 0x99,local_460,iVar4 + 0xb30);
      local_c = 10;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState((void *)(iDelta));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_c = 0xffffffff;
      local_aec[0] = (*(int *)(local_460 + 0x14));
      if ((*(int *)(local_460 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_460 + 0x14),&DAT_0079376c);
        TreeLowerBound(local_ad8,&DAT_00793770);
      }
      if (iVar4 * iVar4 + local_adc * local_adc < local_ad0) {
        (**(code **)(*local_ae0 + 0x20))();
      }
    }
    local_ae4 = local_ae4 + 1;
  } while ((int)local_ae4 < 8);
  local_ae4 = 0;
  do {
    iVar4 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar1 = *(uint *)(iVar4 + 4);
    while (uVar1 < 0x186a7) {
      if (uVar1 == 0x186a6) {
        iVar4 = *(int *)(iVar4 + 0x10);
        uVar1 = *(uint *)(iVar4 + 8);
        if (uVar1 <= local_ae4) goto LAB_00492b46;
        break;
      }
      iVar4 = *(int *)(iVar4 + 0x1c);
      uVar1 = *(uint *)(iVar4 + 4);
    }
LAB_00492cd4:
    local_ae4 = local_ae4 + 1;
  } while ((int)local_ae4 < 8);
  local_ae4 = 0;
LAB_00492cf0:
  piVar7 = local_ae0;
  iVar4 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar1 = *(uint *)(iVar4 + 4);
  while (uVar1 < 0x186a4) {
    if (uVar1 == 0x186a3) {
      piVar8 = *(int **)(iVar4 + 0x10);
      uVar1 = piVar8[2];
      if (uVar1 <= local_ae4) goto LAB_00492d35;
      break;
    }
    iVar4 = *(int *)(iVar4 + 0x1c);
    uVar1 = *(uint *)(iVar4 + 4);
  }
  goto LAB_00492ecb;
LAB_00492b46:
  if (uVar1 != local_ae4) goto code_r0x00492b48;
  iDelta = EncodeChecksumPairDiff(local_ae0 + 0x10,local_8a8,iVar4 + 0x25c);
  local_c = 0xb;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_ad8[0] = PeekPacketChecksumState((void *)(iDelta));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_c = 0xffffffff;
  local_adc = (*(int *)(local_8a8 + 0x14));
  if ((*(int *)(local_8a8 + 0x14)) != 0) {
    iVar5 = (*(int *)(local_8a8 + 0x14)) << 4;
    local_aec[0] = 0x10;
    do {
      iVar6 = _rand();
      *(char *)(iVar5 + DAT_0079376c) = (char)iVar6;
      iVar5 = iVar5 + 1;
      local_aec[0] = local_aec[0] + -1;
    } while (local_aec[0] != 0);
    TreeLowerBound(local_aec,&DAT_00793770);
  }
  piVar7 = local_ae0;
  iDelta = EncodeChecksumPairDiff(local_ae0 + 0x99,auStack_684,iVar4 + 0x480);
  local_c = 0xc;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(iDelta));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_c = 0xffffffff;
  local_adc = iStack_670;
  if (iStack_670 != 0) {
    iVar5 = iStack_670 << 4;
    local_aec[0] = 0x10;
    do {
      iVar6 = _rand();
      *(char *)(iVar5 + DAT_0079376c) = (char)iVar6;
      iVar5 = iVar5 + 1;
      local_aec[0] = local_aec[0] + -1;
    } while (local_aec[0] != 0);
    TreeLowerBound(local_aec,&DAT_00793770);
    piVar7 = local_ae0;
  }
  if (local_ad8[0] * local_ad8[0] + iVar4 * iVar4 < local_ad0) {
    (**(code **)(*piVar7 + 0x20))();
  }
  goto LAB_00492cd4;
code_r0x00492b48:
  iVar4 = *(int *)(iVar4 + 0x10);
  uVar1 = *(uint *)(iVar4 + 8);
  if (local_ae4 < uVar1) goto LAB_00492cd4;
  goto LAB_00492b46;
  while( true ) {
    piVar8 = (int *)piVar8[4];
    uVar1 = piVar8[2];
    if (local_ae4 < uVar1) break;
LAB_00492d35:
    if (uVar1 == local_ae4) {
      if (piVar8 != local_ae0) {
        local_ad8[0] = EncodeChecksumPairDiff(local_ae0 + 0x10,local_8a8,piVar8 + 0x10);
        local_c = 0xd;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_adc = PeekPacketChecksumState((void *)(local_ad8[0]));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_c = 0xffffffff;
        local_ad8[0] = (*(int *)(local_8a8 + 0x14));
        if ((*(int *)(local_8a8 + 0x14)) != 0) {
          iVar4 = (*(int *)(local_8a8 + 0x14)) << 4;
          local_aec[0] = 0x10;
          do {
            iVar5 = _rand();
            *(char *)(iVar4 + DAT_0079376c) = (char)iVar5;
            iVar4 = iVar4 + 1;
            local_aec[0] = local_aec[0] + -1;
          } while (local_aec[0] != 0);
          TreeLowerBound(local_aec,&DAT_00793770);
          piVar7 = local_ae0;
        }
        iDelta = EncodeChecksumPairDiff(piVar7 + 0x99,auStack_23c,piVar8 + 0x99);
        local_c = 0xe;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar4 = PeekPacketChecksumState((void *)(iDelta));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_c = 0xffffffff;
        local_ad8[0] = iStack_228;
        if (iStack_228 != 0) {
          iVar5 = iStack_228 << 4;
          local_aec[0] = 0x10;
          do {
            iVar6 = _rand();
            *(char *)(iVar5 + DAT_0079376c) = (char)iVar6;
            iVar5 = iVar5 + 1;
            local_aec[0] = local_aec[0] + -1;
          } while (local_aec[0] != 0);
          TreeLowerBound(local_aec,&DAT_00793770);
          piVar7 = local_ae0;
        }
        if (local_adc * local_adc + iVar4 * iVar4 < local_ad0) {
          (**(code **)(*piVar7 + 0x20))();
        }
      }
      break;
    }
  }
LAB_00492ecb:
  piVar7 = local_ae0;
  local_ae4 = local_ae4 + 1;
  if (0x3f < (int)local_ae4) {
    if ((char)local_ae0[0xff1] == '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = PeekPacketChecksumState((void *)(local_ae0 + 0x10));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = FUN_00451030(uVar3);
      if (iVar4 != 0) {
        *(undefined1 *)(piVar7 + 0xfed) = 0;
        *(undefined1 *)(piVar7 + 0xff1) = 1;
        piVar7[0xff2] = 0;
      }
    }
    *unaff_FS_OFFSET = uStack_14;
    return;
  }
  goto LAB_00492cf0;
}

