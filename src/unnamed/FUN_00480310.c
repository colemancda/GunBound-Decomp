/* FUN_00480310 - 0x00480310 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 27 argless PeekPacketChecksumState() calls (worklist 27:27;
 * the 8 Encode cells were already fixed 2026-07-15).  Sibling of
 * FUN_0047ca40: this=ESI, cells this+0x264 (param_1+0x99) / +0x40
 * (param_1+0x10), the GetPlayerRecordBySlot record (frame[0x14], the C's
 * iVar5) +0x90c, g_clientContext+0x45354 and the 0x796aa0 global.  Four
 * chained returns - the discarded EncodeChecksumDeltaAdd/Sub results at
 * 0x480592 (-> frame[0x10], read 0x4805cd), 0x4808db, 0x480c22, 0x480eca
 * (`mov edi,eax` -> `mov eax,edi; call Peek`) - are captured in pvDelta;
 * the fifth (0x48040e -> frame[0x1c], read 0x480455) was already kept in
 * aiStack_ac8[0] and is passed from there.  Ghidra emitted the three
 * trailing DeltaSub blocks out of address order; matched by their
 * uStack_14 markers (=6 -> 0x4808e7, =4 -> 0x480c2e, =5 -> 0x480ed6) and
 * buffer sizes (0x226 / 0x190 / 0xc8), which also confirms that the
 * `param_1[0xff4]` Encode value in the =4 block is real (0x480c93 loads
 * [esi+0x3fd0]; only the =5 and =6 blocks peek record+0x90c there).
 */
#include "ghidra_types.h"


void __fastcall FUN_00480310(int *param_1)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffff520;
  void *pvDelta;
  int *piVar1;
  bool bVar2;
  undefined1 uVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  code *pcVar14;
  int unaff_EBP;
  code *pcVar15;
  int unaff_EDI;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar16;
  undefined *puVar17;
  undefined4 uVar18;
  int aiStack_ac8 [2];
  undefined1 auStack_ac0 [20];
  int iStack_aac;
  undefined1 auStack_89c [20];
  int iStack_888;
  undefined1 auStack_688 [12];
  int iStack_67c;
  undefined1 auStack_464 [548];
  undefined1 auStack_240 [548];
  undefined4 uStack_1c;
  undefined4 uStack_14;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053d19b;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  FUN_0047bfd0();
  AdvanceSpriteAnimation((int)param_1);
  if ((char)param_1[0xd] != '\0') {
    (**(code **)(*param_1 + 4))(s_normal_00552230);
  }
  param_1[0xfec] = (param_1[0xfec] + 1) % 0x16;
  iVar5 = GetPlayerRecordBySlot(g_clientContext);
  if (param_1[9] == 0) {
    uVar3 = PeekPacketChecksumBool();
    *(undefined1 *)(param_1 + 0xfe8) = uVar3;
  }
  pcVar15 = (code *)EnterCriticalSection;
  if (iVar5 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    pcVar14 = (code *)LeaveCriticalSection;
    if (iVar5 != 1) {
      *(undefined1 *)(param_1 + 5) = 1;
    }
  }
  else if ((char)param_1[0xff1] == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar6 = PeekPacketChecksumState((void *)(iVar5 + 0x90c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    param_1[0xfed] = iVar6;
    pvDelta = EncodeChecksumDeltaAdd(iVar5 + 0xb30,auStack_ac0,
                 (-(uint)((char)param_1[0xfe8] != '\0') & 0xfffffea2) - 200);
    uStack_4 = 2;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    aiStack_ac8[0] = PeekPacketChecksumState((void *)(&DAT_00796aa0));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar6 = PeekPacketChecksumState((void *)(pvDelta));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    bVar2 = iVar6 <= *(int *)(&g_nCameraBoundY + g_clientContext) + aiStack_ac8[0];
    if (bVar2) {
      uVar8 = EncodeChecksumDeltaAdd(iVar5 + 0xb30,auStack_89c,
                           (-(uint)((char)param_1[0xfe8] != '\0') & 0xfffffea2) - 200);
      uStack_4 = CONCAT31(SUBFIELD(uStack_4,1,undefined3),3);
      iVar5 = PeekChecksumStateUnderLock(uVar8);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar5 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar5 = *(int *)(&g_nCameraBoundY + g_clientContext) + iVar5;
    }
    param_1[0xfee] = iVar5;
    uStack_4 = 2;
    if (bVar2) {
      ScrubChecksumGuard();
    }
    uStack_4 = 0xffffffff;
    pcVar14 = (code *)LeaveCriticalSection;
    if (iStack_aac != 0) {
      ScrambleChecksumGuardBytes(iStack_aac,&g_valueGuardKeyTable);
      TreeLowerBound(aiStack_ac8,&g_valueGuardMap);
      pcVar14 = (code *)LeaveCriticalSection;
    }
  }
  else {
    aiStack_ac8[0] = EncodeChecksumDeltaSub(iVar5 + 0xb30,auStack_89c,400);
    pcVar15 = (code *)EnterCriticalSection;
    uStack_4 = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar6 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
    pcVar14 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    aiStack_ac8[0] = PeekPacketChecksumState((void *)(aiStack_ac8[0]));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    bVar2 = aiStack_ac8[0] <= *(int *)(&g_nCameraBoundY + g_clientContext) + iVar6;
    if (bVar2) {
      uVar8 = EncodeChecksumDeltaSub(iVar5 + 0xb30,auStack_ac0,400);
      uStack_4 = CONCAT31(SUBFIELD(uStack_4,1,undefined3),1);
      iVar5 = PeekChecksumStateUnderLock(uVar8);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar5 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar5 = *(int *)(&g_nCameraBoundY + g_clientContext) + iVar5;
    }
    param_1[0xfee] = iVar5;
    uStack_4 = 0;
    if (bVar2) {
      ScrubChecksumGuard();
    }
    uStack_4 = 0xffffffff;
    if (iStack_888 != 0) {
      ScrambleChecksumGuardBytes(iStack_888,&g_valueGuardKeyTable);
      TreeLowerBound(aiStack_ac8,&g_valueGuardMap);
    }
  }
  (*pcVar15)(&g_valueGuardLock);
  PeekPacketChecksumState((void *)(param_1 + 0x99));
  (*pcVar14)(&g_valueGuardLock);
  if (param_1[0xfee] != unaff_EBP) {
    (*pcVar15)(&g_valueGuardLock);
    iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x99));
    (*pcVar14)(&g_valueGuardLock);
    iVar5 = param_1[0xfee] - iVar5;
    if ((param_1[0xfef] == 0) && (param_1[9] != 3)) {
      if (0 < iVar5) {
        iVar5 = iVar5 + 7;
      }
      if (iVar5 < 0) {
        iVar5 = iVar5 + -7;
      }
      iVar5 = (int)(iVar5 + (iVar5 >> 0x1f & 7U)) >> 3;
    }
    else {
      if (0 < iVar5) {
        iVar5 = iVar5 + 1;
      }
      if (iVar5 < 0) {
        iVar5 = iVar5 + -1;
      }
      iVar5 = iVar5 / 2;
    }
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x48075a
     * (edi loaded from esi+0x264). esi == param_1 here: 0x264/4 == 0x99,
     * exactly the `param_1 + 0x99` cell this file threads through
     * PeekChecksumStateUnderLock elsewhere below. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    (*pcVar15)(&g_valueGuardLock);
    iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x99));
    EncodeOutgoingPacketField(param_1 + 0x99, iVar6 + iVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    pcVar14 = (code *)LeaveCriticalSection;
  }
  (*pcVar15)(&g_valueGuardLock);
  iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x10));
  (*pcVar14)(&g_valueGuardLock);
  if (param_1[0xfed] != unaff_EDI) {
    (*pcVar15)(&g_valueGuardLock);
    iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x10));
    (*pcVar14)(&g_valueGuardLock);
    iVar6 = param_1[0xfed] - iVar6;
    if ((param_1[0xfef] == 0) && (param_1[9] != 3)) {
      if (0 < iVar6) {
        iVar6 = iVar6 + 7;
      }
      if (iVar6 < 0) {
        iVar6 = iVar6 + -7;
      }
      iVar6 = (int)(iVar6 + (iVar6 >> 0x1f & 7U)) >> 3;
    }
    else {
      if (0 < iVar6) {
        iVar6 = iVar6 + 1;
      }
      if (iVar6 < 0) {
        iVar6 = iVar6 + -1;
      }
      iVar6 = iVar6 / 2;
    }
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x48080b
     * (edi loaded from esi+0x40). esi == param_1 here: 0x40/4 == 0x10,
     * exactly the `param_1 + 0x10` cell this file threads through
     * PeekChecksumStateUnderLock elsewhere below. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    (*pcVar15)(&g_valueGuardLock);
    iVar7 = PeekPacketChecksumState((void *)(param_1 + 0x10));
    EncodeOutgoingPacketField(param_1 + 0x10, iVar7 + iVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    pcVar14 = (code *)LeaveCriticalSection;
  }
  if (param_1[9] == 3) {
    (*pcVar15)(&g_valueGuardLock);
    iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x10));
    (*pcVar14)(&g_valueGuardLock);
    if (param_1[0xfed] == iVar6) {
      (*pcVar15)(&g_valueGuardLock);
      iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x99));
      (*pcVar14)(&g_valueGuardLock);
      if (param_1[0xfee] == iVar6) {
        switch(param_1[0xfef]) {
        case 0:
          (**(code **)(*param_1 + 4))(s_normal_00552230);
          break;
        case 1:
        case 3:
          (**(code **)(*param_1 + 4))(&DAT_00553b68);
          break;
        case 2:
          (**(code **)(*param_1 + 4))(&DAT_00553b70);
        }
        param_1[0xfef] = 0;
      }
    }
  }
  if (param_1[9] == 1) {
    if ((char)param_1[0xff1] != '\0') {
      pvDelta = EncodeChecksumDeltaSub(iVar5 + 0xb30,auStack_464,400);
      uStack_14 = 4;
      /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at
       * 0x480902/0x480989 (edi loaded from esi+0x264/esi+0x40), same
       * `param_1 + 0x99` / `param_1 + 0x10` cells as above. See
       * tools/encodeoutgoingpacketfield_sites.json. */
      (*pcVar15)(&g_valueGuardLock);
      uVar8 = PeekPacketChecksumState((void *)(pvDelta));
      EncodeOutgoingPacketField(param_1 + 0x99, uVar8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      (*pcVar15)(&g_valueGuardLock);
      iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x99));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      param_1[0xfee] = iVar6;
      uStack_1c = 0xffffffff;
      ScrubChecksumGuard();
      iVar6 = param_1[0xff4];
      (*pcVar15)(&g_valueGuardLock);
      EncodeOutgoingPacketField(param_1 + 0x10, iVar6);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      (*pcVar15)(&g_valueGuardLock);
      iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x10));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      param_1[0xfed] = iVar6;
      if (param_1[0xb] == 1) {
        if (*(char *)(iVar5 + 0x651c) == '\0') {
          puVar17 = &DAT_00794e48;
        }
        else {
          puVar17 = &DAT_00796aa0;
        }
        uVar8 = PeekChecksumStateUnderLock(puVar17);
        iVar6 = param_1[0xff3];
        if ((char)param_1[0xff8] == '\0') {
          iVar6 = iVar6 + 4;
        }
        uVar18 = 1;
        uVar16 = 8;
        uVar9 = PeekPacketChecksumBool((byte *)param_1 + 0x3918);
        uVar10 = PeekChecksumStateUnderLock(param_1 + 0x4e7);
        iVar7 = param_1[0xfe7];
        uVar11 = PeekChecksumStateUnderLock(param_1 + 0x99);
        uVar12 = PeekChecksumStateUnderLock(param_1 + 0x10);
        uVar13 = PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
        SpawnShot_Type9(*(byte *)(param_1 + 2) & 7,iVar6,1,uVar13,uVar12,uVar11,iVar7,uVar10,uVar9,
                     uVar8,uVar16,uVar18);
        cVar4 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
        if (cVar4 == '\0') {
          AcquireSoundChannel(0);
        }
        if (param_1[0xff3] < 3) {
          param_1[0xff3] = param_1[0xff3] + 1;
          param_1[0xff4] = param_1[0xff4] + param_1[0xff5];
          param_1[0xff6] = param_1[0xff6] + param_1[0xff7];
          (**(code **)(*param_1 + 4))(&DAT_00553f90);
          param_1[0xfef] = 3;
        }
        else if ((char)param_1[0xff8] == '\0') {
          param_1[0xff6] = param_1[0xff6] + param_1[0xff7];
          param_1[0xff5] = -param_1[0xff5];
          param_1[0xff3] = 1;
          *(undefined1 *)(param_1 + 0xff8) = 1;
          (**(code **)(*param_1 + 4))(&DAT_00553f90);
          param_1[0xfef] = 3;
        }
        else {
          *(undefined1 *)(param_1 + 0xff1) = 0;
          iVar5 = PeekChecksumStateUnderLock(iVar5 + 0x90c);
          param_1[0xfed] = iVar5;
          cVar4 = InitChecksumSeed();
          if (cVar4 == '\0') {
            uVar8 = PeekChecksumStateUnderLock(&DAT_007949c8);
            QueueOutgoingPacketField(uVar8);
            iVar5 = g_clientContext;
            if (*(int *)(&DAT_005f3768 + g_clientContext) != 0) {
              *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
              *(undefined4 *)(&DAT_005f376c + iVar5) = 0;
            }
          }
          (**(code **)(*param_1 + 4))(&DAT_00553f90);
          param_1[0xfef] = 0;
        }
      }
      goto LAB_0048108e;
    }
    pvDelta = EncodeChecksumDeltaSub(iVar5 + 0xb30,auStack_240,200);
    uStack_14 = 5;
    /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at
     * 0x480c49/0x480ca4 (edi loaded from esi+0x264/esi+0x40), same
     * `param_1 + 0x99` / `param_1 + 0x10` cells as above. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    (*pcVar15)(&g_valueGuardLock);
    uVar8 = PeekPacketChecksumState((void *)(pvDelta));
    EncodeOutgoingPacketField(param_1 + 0x99, uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    (*pcVar15)(&g_valueGuardLock);
    iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x99));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    param_1[0xfee] = iVar6;
    uStack_1c = 0xffffffff;
    ScrubChecksumGuard();
    (*pcVar15)(&g_valueGuardLock);
    uVar8 = PeekPacketChecksumState((void *)(iVar5 + 0x90c));
    EncodeOutgoingPacketField(param_1 + 0x10, uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    (*pcVar15)(&g_valueGuardLock);
    iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x10));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    param_1[0xfed] = iVar6;
    FUN_0047bfd0();
    if (param_1[0xb] != 1) goto LAB_0048108e;
    QueueOutgoingPacketField(0xffffffff);
    if (*(char *)(iVar5 + 0x651c) == '\0') {
      puVar17 = &DAT_00794e48;
    }
    else {
      puVar17 = &DAT_00796aa0;
    }
    uVar8 = PeekChecksumStateUnderLock(puVar17);
    uVar18 = 0;
    uVar16 = 1;
    uVar9 = PeekPacketChecksumBool((byte *)param_1 + 0x3918);
    uVar10 = PeekChecksumStateUnderLock(param_1 + 0x4e7);
    iVar5 = param_1[0xfe7];
    uVar11 = PeekChecksumStateUnderLock(param_1 + 0x99);
    uVar12 = PeekChecksumStateUnderLock(param_1 + 0x10);
    uVar13 = PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
    SpawnShot_Type9(*(byte *)(param_1 + 2) & 7,param_1[0xfe9],0,uVar13,uVar12,uVar11,iVar5,uVar10,uVar9
                 ,uVar8,uVar16,uVar18);
    cVar4 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  }
  else {
    if (param_1[9] != 2) goto LAB_0048108e;
    pvDelta = EncodeChecksumDeltaSub(iVar5 + 0xb30,auStack_688,0x226);
    uStack_14 = 6;
    /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at
     * 0x480ef1/0x480f54 (edi loaded from esi+0x264/esi+0x40), same
     * `param_1 + 0x99` / `param_1 + 0x10` cells as above (the second call
     * even has `piVar1 = param_1 + 0x10;` assigned on the very same
     * line, confirming the cell independently). See
     * tools/encodeoutgoingpacketfield_sites.json. */
    (*pcVar15)(&g_valueGuardLock);
    uVar8 = PeekPacketChecksumState((void *)(pvDelta));
    EncodeOutgoingPacketField(param_1 + 0x99, uVar8);
    pcVar14 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    (*pcVar15)(&g_valueGuardLock);
    iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x99));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uStack_1c = 0xffffffff;
    param_1[0xfee] = iVar6;
    if (iStack_67c != 0) {
      ScrambleChecksumGuardBytes(iStack_67c,&g_valueGuardKeyTable);
      TreeLowerBound(&stack0xfffff520,&g_valueGuardMap);
      pcVar14 = (code *)LeaveCriticalSection;
    }
    (*pcVar15)(&g_valueGuardLock);
    uVar8 = PeekPacketChecksumState((void *)(iVar5 + 0x90c));
    piVar1 = param_1 + 0x10;
    EncodeOutgoingPacketField(param_1 + 0x10, uVar8);
    (*pcVar14)(&g_valueGuardLock);
    (*pcVar15)(&g_valueGuardLock);
    iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x10));
    (*pcVar14)(&g_valueGuardLock);
    param_1[0xfed] = iVar6;
    FUN_0047bfd0();
    iVar6 = param_1[0xb];
    if (iVar6 == 1) {
      QueueOutgoingPacketField(0xffffffff);
      if (*(char *)(iVar5 + 0x651c) == '\0') {
        puVar17 = &DAT_00794e48;
      }
      else {
        puVar17 = &DAT_00796aa0;
      }
      uVar8 = PeekChecksumStateUnderLock(puVar17);
      uVar18 = 0;
      uVar16 = 3;
      uVar9 = PeekPacketChecksumBool((byte *)param_1 + 0x3918);
      uVar10 = PeekChecksumStateUnderLock(param_1 + 0x4e7);
      iVar5 = param_1[0xfe7] + -1;
      uVar11 = PeekChecksumStateUnderLock(param_1 + 0x99);
      uVar12 = PeekChecksumStateUnderLock(piVar1);
      uVar13 = PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
      SpawnShot_Type9(*(byte *)(param_1 + 2) & 7,param_1[0xfe9],1,uVar13,uVar12,uVar11,iVar5,uVar10,
                   uVar9,uVar8,uVar16,uVar18);
      cVar4 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
      if (cVar4 == '\0') {
        AcquireSoundChannel(0);
      }
      goto LAB_0048108e;
    }
    if (iVar6 == 3) {
      QueueOutgoingPacketField(0xffffffff);
      if (*(char *)(iVar5 + 0x651c) == '\0') {
        puVar17 = &DAT_00794e48;
      }
      else {
        puVar17 = &DAT_00796aa0;
      }
      uVar8 = PeekChecksumStateUnderLock(puVar17);
      uVar18 = 0;
      uVar16 = 3;
      uVar9 = PeekPacketChecksumBool((byte *)param_1 + 0x3918);
      uVar10 = PeekChecksumStateUnderLock(param_1 + 0x4e7);
      iVar5 = param_1[0xfe7];
      uVar11 = PeekChecksumStateUnderLock(param_1 + 0x99);
      uVar12 = PeekChecksumStateUnderLock(piVar1);
      uVar13 = PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
      SpawnShot_Type9(*(byte *)(param_1 + 2) & 7,param_1[0xfe9] + 1,1,uVar13,uVar12,uVar11,iVar5,uVar10
                   ,uVar9,uVar8,uVar16,uVar18);
      cVar4 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
      if (cVar4 == '\0') {
        AcquireSoundChannel(0);
      }
      goto LAB_0048108e;
    }
    if (iVar6 != 5) goto LAB_0048108e;
    QueueOutgoingPacketField(0xffffffff);
    if (*(char *)(iVar5 + 0x651c) == '\0') {
      puVar17 = &DAT_00794e48;
    }
    else {
      puVar17 = &DAT_00796aa0;
    }
    uVar8 = PeekChecksumStateUnderLock(puVar17);
    uVar18 = 0;
    uVar16 = 3;
    uVar9 = PeekPacketChecksumBool((byte *)param_1 + 0x3918);
    uVar10 = PeekChecksumStateUnderLock(param_1 + 0x4e7);
    iVar5 = param_1[0xfe7] + 1;
    uVar11 = PeekChecksumStateUnderLock(param_1 + 0x99);
    uVar12 = PeekChecksumStateUnderLock(piVar1);
    uVar13 = PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
    SpawnShot_Type9(*(byte *)(param_1 + 2) & 7,param_1[0xfe9] + 2,1,uVar13,uVar12,uVar11,iVar5,uVar10,
                 uVar9,uVar8,uVar16,uVar18);
    cVar4 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  }
  if (cVar4 == '\0') {
    AcquireSoundChannel(0);
  }
  cVar4 = PeekPacketChecksumBool();
  if ((cVar4 == '\0') && (cVar4 = PeekPacketChecksumBool(), cVar4 == '\0')) {
    cVar4 = InitChecksumSeed();
    if (cVar4 == '\0') {
      uVar8 = PeekChecksumStateUnderLock(&DAT_007949c8);
      QueueOutgoingPacketField(uVar8);
    }
    SetGuardedBool(1,GB_GUARD_UNRECOVERED);
  }
LAB_0048108e:
  *unaff_FS_OFFSET = uStack_1c;
  return;
}

