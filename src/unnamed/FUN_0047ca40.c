/* FUN_0047ca40 - 0x0047ca40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 36 argless PeekPacketChecksumState() calls (worklist 36:36).
 * this=ESI throughout; this+0x264 = param_1+0x99 (turn/shot cell), +0x40 =
 * param_1+0x10, +0x139c = param_1+0x4e7 (the five straight-line
 * SpawnKnightFlameShot copies at 0x47d0fb/0x47d201/0x47d30c/0x47d417/
 * 0x47d522 all peek it via EDI loaded once at 0x47d0f3); the record from
 * GetPlayerRecordBySlot (frame[0x18] = iVar5 / iStack_ad4) +0x90c; the
 * globals 0x796aa0/0x794e48 (do-while arms 0x47d666/0x47d645) and
 * 0x7949c8 (0x47d77c).  Five chained returns: the discarded
 * EncodeChecksumDeltaAdd/Sub results (0x47cb64 frame[0x10], 0x47cc2e,
 * 0x47cee7, 0x47d5af, 0x47d7cc: `mov edi,eax` then `mov eax,edi; call
 * Peek`) are now captured in pvDelta and passed to the following Peek.
 * Ghidra emitted the three DeltaSub blocks out of address order; they were
 * matched by their puStack_8 markers (=2 -> 0x47d5b6, =3 -> 0x47d7d3,
 * =4 -> 0x47ceee), not by C order.  Not touched: the C stores the
 * 0x796aa0 peek at line 90 into iStack_ad4 (the record pointer) - a
 * pre-existing Ghidra data-flow artifact, out of the sweep's scope.
 */
#include "ghidra_types.h"


void __fastcall FUN_0047ca40(int *param_1)

{
  int *piVar1;
  byte bVar2;
  undefined1 uVar3;
  char cVar4;
  int iRecord;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  int iVar13;
  int unaff_EBX;
  code *pcVar14;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  uint uVar18;
  undefined4 uVar19;
  undefined *puVar20;
  undefined *puVar21;
  uint uVar22;
  undefined *puVar23;
  undefined *puVar24;
  undefined4 uVar25;
  undefined *puVar26;
  void *pvDelta;
  int iStack_ad4;
  uint local_acc;
  undefined1 auStack_ac8 [4];
  undefined1 auStack_ac4 [20];
  int iStack_ab0;
  undefined1 auStack_89c [20];
  int iStack_888;
  undefined1 auStack_67c [552];
  undefined1 auStack_454 [20];
  int iStack_440;
  undefined1 auStack_234 [548];
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053d1fe;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_acc = 0;
  FUN_0047bfd0();
  AdvanceSpriteAnimation((int)param_1);
  if ((char)param_1[0xd] != '\0') {
    (**(code **)(*param_1 + 4))(s_normal_00552230);
  }
  param_1[0xfec] = (param_1[0xfec] + 1) % 0x16;
  iVar5 = GetPlayerRecordBySlot(g_clientContext);
  iRecord = iVar5;   /* the record stays spilled at frame[0x18] (0x47cab5) and is
                      * re-read by the tail 0xbfbe/0xbfc1 peeks (rows 0x47db7a/8c) */
  if (param_1[9] == 0) {
    uVar3 = PeekPacketChecksumBool((byte *)(iVar5 + 0x8bb7));
    *(undefined1 *)(param_1 + 0xfe8) = uVar3;
  }
  if (iVar5 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar6 != 1) {
      *(undefined1 *)(param_1 + 5) = 1;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState((void *)(iVar5 + 0x90c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    param_1[0xfed] = iVar6;
    pvDelta = EncodeChecksumDeltaAdd(iVar5 + 0xb30,auStack_454,
                 (-(uint)((char)param_1[0xfe8] != '\0') & 0xffffff38) - 200);
    uStack_4 = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iStack_ad4 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState((void *)(pvDelta));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (*(int *)(&g_nCameraBoundY + g_clientContext) + iStack_ad4 < iVar6) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = *(int *)(&g_nCameraBoundY + g_clientContext) + iVar6;
    }
    else {
      pvDelta = EncodeChecksumDeltaAdd(iVar5 + 0xb30,auStack_89c,
                   (-(uint)((char)param_1[0xfe8] != '\0') & 0xffffff38) - 200);
      uStack_4 = CONCAT31(SUBFIELD(uStack_4,1,undefined3),1);
      local_acc = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState((void *)(pvDelta));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    param_1[0xfee] = iVar6;
    uStack_4 = 0;
    if (((local_acc & 1) != 0) && (iStack_888 != 0)) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(auStack_ac8,&DAT_00793770);
    }
    uStack_4 = 0xffffffff;
    if (iStack_440 != 0) {
      ScrambleChecksumGuardBytes(iStack_440,&DAT_0079376c);
      TreeLowerBound(auStack_ac8,&DAT_00793770);
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x99));
  pcVar14 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (param_1[0xfee] != iVar6) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x99));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = param_1[0xfee] - iVar6;
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
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState((void *)(param_1 + 0x99));
    EncodeOutgoingPacketField(iVar7 + iVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    pcVar14 = (code *)LeaveCriticalSection;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState((void *)(param_1 + 0x10));
  puVar26 = &DAT_005a9068;
  (*pcVar14)(&DAT_005a9068);
  if (param_1[0xfed] != unaff_EBX) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x10));
    (*pcVar14)(&DAT_005a9068);
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
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState((void *)(param_1 + 0x10));
    EncodeOutgoingPacketField(iVar7 + iVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    pcVar14 = (code *)LeaveCriticalSection;
  }
  if (param_1[9] == 3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x10));
    (*pcVar14)(&DAT_005a9068);
    if (param_1[0xfed] == iVar6) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x99));
      (*pcVar14)(&DAT_005a9068);
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
    if ((char)param_1[0xff2] != '\0') {
      pvDelta = EncodeChecksumDeltaSub(iStack_ad4 + 0xb30,auStack_67c,400);
      puStack_8 = (undefined1 *)0x2;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar8 = PeekPacketChecksumState((void *)(pvDelta));
      EncodeOutgoingPacketField(uVar8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x99));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      param_1[0xfee] = iVar5;
      puStack_8 = (undefined1 *)0xffffffff;
      ScrubChecksumGuard();
      if (param_1[0xb] == 1) {
        iVar5 = 0;
        do {
          if (*(char *)(iStack_ad4 + 0x651c) == '\0') {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_acc = PeekPacketChecksumState((void *)(&DAT_00794e48));
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          else {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_acc = PeekPacketChecksumState((void *)(&DAT_00796aa0));
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          uVar22 = local_acc;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_acc = PeekPacketChecksumState((void *)(param_1 + 0x4e7));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x99));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar16 = 1;
          uVar15 = 8;
          iVar9 = iVar5 * 2;
          uVar11 = PeekPacketChecksumBool((byte *)param_1 + 0x3918);
          iVar6 = param_1[0xff7];
          iVar7 = param_1[0xff5];
          uVar18 = local_acc;
          uVar12 = PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
          SpawnKnightFlameShot(*(byte *)(param_1 + 2) & 7,iVar5,0,uVar12,iVar7,uVar8,iVar6,uVar18,uVar11,
                       iVar9,uVar22,uVar15,uVar16);
          if (iVar5 == 3) {
            param_1[0xff8] = -param_1[0xff8];
            param_1[0xff6] = -param_1[0xff6];
          }
          else {
            param_1[0xff7] = param_1[0xff7] + param_1[0xff8];
            param_1[0xff5] = param_1[0xff5] + param_1[0xff6];
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < 8);
        cVar4 = InitChecksumSeed();
        if (cVar4 == '\0') {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar8 = PeekPacketChecksumState((void *)(&DAT_007949c8));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
      }
      goto LAB_0047dbc9;
    }
    pvDelta = EncodeChecksumDeltaSub(iStack_ad4 + 0xb30,auStack_234,200);
    puStack_8 = (undefined1 *)0x3;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(pvDelta));
    EncodeOutgoingPacketField(uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x99));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    param_1[0xfee] = iVar5;
    puStack_8 = (undefined1 *)0xffffffff;
    ScrubChecksumGuard();
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(iStack_ad4 + 0x90c));
    EncodeOutgoingPacketField(uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x10));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    param_1[0xfed] = iVar5;
    FUN_0047bfd0();
    if (param_1[0xb] != 2) goto LAB_0047dbc9;
    QueueOutgoingPacketField(0xffffffff);
    iVar7 = PeekChecksumStateUnderLock(param_1 + 0x10);
    iVar5 = param_1[0xfea];
    iVar6 = param_1[0xfeb];
    iVar9 = PeekChecksumStateUnderLock(param_1 + 0x99);
    iVar9 = iVar6 - iVar9;
    local_acc = iVar9 * iVar9 + (iVar5 - iVar7) * (iVar5 - iVar7);
    iVar5 = FloatToInt64();
    param_1[0xff1] = iVar5;
    iVar5 = FloatToInt64();
    iVar5 = iVar5 + param_1[0xfea];
    iVar7 = FloatToInt64();
    iVar6 = iVar6 - iVar7;
    if (*(char *)(iStack_ad4 + 0x651c) == '\0') {
      puVar26 = &DAT_00794e48;
    }
    else {
      puVar26 = &DAT_00796aa0;
    }
    uVar8 = PeekChecksumStateUnderLock(puVar26);
    uVar17 = 0;
    uVar19 = 3;
    uVar16 = 3;
    piVar1 = param_1 + 0x4e7;
    uVar11 = PeekPacketChecksumBool((byte *)param_1 + 0x3918);
    uVar12 = PeekChecksumStateUnderLock(piVar1);
    iVar7 = param_1[0xfe7];
    uVar15 = PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
    SpawnKnightFlameShot(*(byte *)(param_1 + 2) & 7,param_1[0xfe9] + 1,0,uVar15,iVar5,iVar6,iVar7,uVar12,
                 uVar11,uVar16,uVar8,uVar19,uVar17);
    iVar5 = FloatToInt64();
    iVar5 = iVar5 + param_1[0xfea];
    iVar6 = FloatToInt64();
    iVar6 = param_1[0xfeb] - iVar6;
    if (*(char *)(iStack_ad4 + 0x651c) == '\0') {
      puVar26 = &DAT_00794e48;
    }
    else {
      puVar26 = &DAT_00796aa0;
    }
    uVar8 = PeekChecksumStateUnderLock(puVar26);
    uVar17 = 0;
    uVar19 = 3;
    uVar16 = 7;
    uVar11 = PeekPacketChecksumBool((byte *)param_1 + 0x3918);
    uVar12 = PeekChecksumStateUnderLock(piVar1);
    iVar7 = param_1[0xfe7] + 4;
    uVar15 = PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
    SpawnKnightFlameShot(*(byte *)(param_1 + 2) & 7,param_1[0xfe9] + 2,0,uVar15,iVar5,iVar6,iVar7,uVar12,
                 uVar11,uVar16,uVar8,uVar19,uVar17);
    iVar6 = FloatToInt64();
    iVar6 = iVar6 + param_1[0xfea];
    iVar5 = FloatToInt64();
    iVar5 = param_1[0xfeb] - iVar5;
    if (*(char *)(iStack_ad4 + 0x651c) == '\0') {
      puVar26 = &DAT_00794e48;
    }
    else {
      puVar26 = &DAT_00796aa0;
    }
    uVar8 = PeekChecksumStateUnderLock(puVar26);
    uVar25 = 0;
    uVar17 = 3;
    uVar19 = 7;
    uVar12 = PeekPacketChecksumBool((byte *)param_1 + 0x3918);
    uVar11 = PeekChecksumStateUnderLock(piVar1);
    iVar7 = param_1[0xfe7] + -4;
    uVar15 = PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
    bVar2 = *(byte *)(param_1 + 2);
    iVar9 = param_1[0xfe9] + 3;
    uVar16 = 0;
  }
  else {
    if (param_1[9] != 2) goto LAB_0047dbc9;
    pvDelta = EncodeChecksumDeltaSub(iStack_ad4 + 0xb30,auStack_ac4,400);
    puStack_8 = (undefined1 *)0x4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(pvDelta));
    EncodeOutgoingPacketField(uVar8);
    pcVar14 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x99));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0xffffffff;
    param_1[0xfee] = iVar6;
    if (iStack_ab0 != 0) {
      ScrambleChecksumGuardBytes(iStack_ab0,&DAT_0079376c);
      TreeLowerBound(&local_acc,&DAT_00793770);
      pcVar14 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(iStack_ad4 + 0x90c));
    EncodeOutgoingPacketField(uVar8);
    (*pcVar14)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x10));
    (*pcVar14)(&DAT_005a9068);
    param_1[0xfed] = iVar6;
    FUN_0047bfd0();
    if (param_1[0xb] != 2) goto LAB_0047dbc9;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0xffffffff);
    puVar24 = &DAT_005a9068;
    (*pcVar14)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar9 = PeekPacketChecksumState((void *)(param_1 + 0x10));
    puVar23 = &DAT_005a9068;
    (*pcVar14)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState((void *)(param_1 + 0x99));
    puVar21 = &DAT_005a9068;
    (*pcVar14)(&DAT_005a9068);
    iVar7 = param_1[0xfeb];
    iVar6 = FloatToInt64();
    param_1[0xff1] = iVar6;
    iVar10 = FloatToInt64();
    iVar10 = iVar10 + param_1[0xfea];
    iVar6 = FloatToInt64();
    iVar7 = iVar7 - iVar6;
    if (*(char *)(iVar9 + 0x651c) == '\0') {
      puVar20 = &DAT_00794e48;
    }
    else {
      puVar20 = &DAT_00796aa0;
    }
    uVar8 = PeekChecksumStateUnderLock(puVar20);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x4e7));
    (*pcVar14)(&DAT_005a9068);
    uVar19 = 0;
    uVar16 = 5;
    uVar15 = 3;
    uVar11 = PeekPacketChecksumBool((byte *)param_1 + 0x3918);
    iVar13 = param_1[0xfe7];
    uVar12 = PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
    SpawnKnightFlameShot(*(byte *)(param_1 + 2) & 7,param_1[0xfe9] + 1,1,uVar12,uVar8,iVar9,iVar13,iVar7,
                 uVar11,uVar15,puVar26,uVar16,uVar19);
    iVar7 = FloatToInt64();
    iVar7 = iVar7 + param_1[0xfea];
    iVar9 = FloatToInt64();
    iVar9 = param_1[0xfeb] - iVar9;
    if (*(char *)(iVar10 + 0x651c) == '\0') {
      puVar26 = &DAT_00794e48;
    }
    else {
      puVar26 = &DAT_00796aa0;
    }
    uVar11 = PeekChecksumStateUnderLock(puVar26);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x4e7));
    (*pcVar14)(&DAT_005a9068);
    uVar17 = 0;
    uVar19 = 5;
    uVar16 = 7;
    uVar12 = PeekPacketChecksumBool((byte *)param_1 + 0x3918);
    iVar13 = param_1[0xfe7] + 2;
    uVar15 = PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
    SpawnKnightFlameShot(*(byte *)(param_1 + 2) & 7,param_1[0xfe9] + 2,1,uVar15,uVar11,iVar10,iVar13,iVar9,
                 uVar12,uVar16,puVar24,uVar19,uVar17);
    iVar9 = FloatToInt64();
    iVar9 = iVar9 + param_1[0xfea];
    iVar10 = FloatToInt64();
    iVar10 = param_1[0xfeb] - iVar10;
    if (*(char *)(iVar7 + 0x651c) == '\0') {
      puVar26 = &DAT_00794e48;
    }
    else {
      puVar26 = &DAT_00796aa0;
    }
    uVar11 = PeekChecksumStateUnderLock(puVar26);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState((void *)(param_1 + 0x4e7));
    (*pcVar14)(&DAT_005a9068);
    uVar17 = 0;
    uVar19 = 5;
    uVar16 = 7;
    uVar12 = PeekPacketChecksumBool((byte *)param_1 + 0x3918);
    iVar13 = param_1[0xfe7] + -2;
    uVar15 = PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
    SpawnKnightFlameShot(*(byte *)(param_1 + 2) & 7,param_1[0xfe9] + 3,1,uVar15,uVar11,iVar7,iVar13,iVar10,
                 uVar12,uVar16,puVar23,uVar19,uVar17);
    iVar7 = FloatToInt64();
    iVar7 = iVar7 + param_1[0xfea];
    iVar10 = FloatToInt64();
    iVar10 = param_1[0xfeb] - iVar10;
    if (*(char *)(iVar9 + 0x651c) == '\0') {
      puVar26 = &DAT_00794e48;
    }
    else {
      puVar26 = &DAT_00796aa0;
    }
    uVar11 = PeekChecksumStateUnderLock(puVar26);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState((void *)(param_1 + 0x4e7));
    (*pcVar14)(&DAT_005a9068);
    uVar17 = 0;
    uVar19 = 5;
    uVar16 = 0xb;
    uVar12 = PeekPacketChecksumBool((byte *)param_1 + 0x3918);
    iVar13 = param_1[0xfe7] + 4;
    uVar15 = PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
    SpawnKnightFlameShot(*(byte *)(param_1 + 2) & 7,param_1[0xfe9] + 4,1,uVar15,uVar11,iVar9,iVar13,iVar10,
                 uVar12,uVar16,puVar21,uVar19,uVar17);
    FloatToInt64();
    iVar9 = FloatToInt64();
    iVar9 = param_1[0xfeb] - iVar9;
    if (*(char *)(iVar7 + 0x651c) == '\0') {
      puVar26 = &DAT_00794e48;
    }
    else {
      puVar26 = &DAT_00796aa0;
    }
    PeekChecksumStateUnderLock(puVar26);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = PeekPacketChecksumState((void *)(param_1 + 0x4e7));
    (*pcVar14)(&DAT_005a9068);
    uVar25 = 0;
    uVar17 = 5;
    uVar19 = 0xb;
    uVar12 = PeekPacketChecksumBool((byte *)param_1 + 0x3918);
    iVar7 = param_1[0xfe7] + -4;
    uVar15 = PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
    bVar2 = *(byte *)(param_1 + 2);
    uVar16 = 1;
    iVar9 = param_1[0xfe9] + 5;
  }
  SpawnKnightFlameShot(bVar2 & 7,iVar9,uVar16,uVar15,iVar6,iVar5,iVar7,uVar11,uVar12,uVar19,uVar8,uVar17,
               uVar25);
  cVar4 = PeekPacketChecksumBool((byte *)(iRecord + 0xbfbe));
  if ((cVar4 == '\0') && (cVar4 = PeekPacketChecksumBool((byte *)(iRecord + 0xbfc1)), cVar4 == '\0')) {
    cVar4 = InitChecksumSeed();
    if (cVar4 == '\0') {
      uVar8 = PeekChecksumStateUnderLock(&DAT_007949c8);
      QueueOutgoingPacketField(uVar8);
    }
    SetGuardedBool(1,GB_GUARD_UNRECOVERED);
  }
LAB_0047dbc9:
  *unaff_FS_OFFSET = uStack_10;
  return;
}

