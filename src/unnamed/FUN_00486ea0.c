/* FUN_00486ea0 - 0x00486ea0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00486ea0(int *param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  char *pcVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  byte bVar12;
  byte bVar13;
  undefined3 unaff_EBX;
  code *pcVar14;
  byte *pbVar15;
  undefined4 unaff_ESI;
  code *pcVar16;
  undefined4 unaff_EDI;
  int *piVar17;
  undefined4 *unaff_FS_OFFSET;
  bool bVar18;
  undefined4 uVar19;
  char cVar20;
  undefined4 uVar21;
  undefined4 uVar22;
  uint uVar23;
  undefined4 *local_ae4;
  float fStack_ae0;
  int *piStack_adc;
  int iStack_ad8;
  float fStack_ad4;
  undefined4 uStack_ad0;
  undefined4 *puStack_acc;
  undefined1 auStack_ac8 [4];
  undefined1 auStack_ac4 [8];
  int iStack_abc;
  int iStack_ab4;
  undefined4 uStack_ab0;
  undefined1 auStack_8bc [24];
  undefined1 uStack_8a4;
  undefined1 auStack_8a0 [20];
  undefined4 uStack_88c;
  undefined1 auStack_690 [16];
  undefined1 uStack_680;
  undefined1 auStack_46c [540];
  undefined1 auStack_250 [556];
  undefined4 uStack_24;
  undefined4 uStack_1c;
  undefined4 uStack_14;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053f605;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  pcVar14 = (code *)EnterCriticalSection;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  iVar4 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar4 + iVar3);
  pcVar16 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  iVar4 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar4 + iVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar23 = 8;
  (**(code **)(*param_1 + 0x14))();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar1 = FUN_00406690(CONCAT31((int3)((uint)param_1[0xfe7] >> 8),param_1[0xfe7] == iVar3 * 2));
  if (cVar1 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    piStack_adc = (int *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar3 * 2 <= param_1[0xfe7]) || (cVar1 = PeekPacketChecksumBool(), cVar1 != '\0')) {
      FUN_004262d0(param_1[2],param_1 + 0x45e);
      cVar1 = PeekPacketChecksumBool();
      if (cVar1 != '\0') {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar3 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if ((-1 < iVar3) && (iVar3 < *(int *)(&g_nCameraBoundX + g_clientContext))) {
          pcVar7 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar3);
          local_ae4 = (undefined4 *)0x0;
          if (0 < *(int *)(&g_nCameraBoundY + g_clientContext)) {
            do {
              if (*pcVar7 != '\0') goto LAB_0048780a;
              pcVar7 = pcVar7 + *(int *)(&g_nCameraBoundX + g_clientContext);
              local_ae4 = (undefined4 *)((int)local_ae4 + 1);
            } while ((int)local_ae4 < *(int *)(&g_nCameraBoundY + g_clientContext));
          }
        }
        local_ae4 = (undefined4 *)0x2710;
LAB_0048780a:
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436070(&DAT_006a7f70 + g_clientContext,uVar5,local_ae4);
        fStack_ae0 = 1.4013e-45;
        if (0 < param_1[0xfe5]) {
          fStack_ae0 = (float)param_1[0xfe5];
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        piStack_adc = (int *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        fStack_ad4 = (float)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uStack_ad0 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_0043af40(uStack_ad0,local_ae4,0,fStack_ad4,(int)piStack_adc / (int)fStack_ae0,uVar5,
                     (char)param_1[0xf]);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        piStack_adc = (int *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar22 = 0;
        uVar21 = 2;
        uVar19 = 0xff;
        uVar6 = 0;
        PeekPacketChecksumBool(0,uVar5,0xff,2,0);
        FUN_00431d90((char)param_1[0xf],7,0,uVar6,uVar5,uVar19,uVar21,uVar22);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      fStack_ae0 = (float)PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iStack_ad8 = param_1[2];
      fStack_ad4 = fStack_ae0;
      uStack_ad0 = uVar5;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar3 == 4) {
        local_ae4 = operator_new(0x3fbc);
        puStack_8 = (undefined1 *)0xc;
        puStack_acc = local_ae4;
        if (local_ae4 == (undefined4 *)0x0) {
          local_ae4 = (undefined4 *)0x0;
        }
        else {
          InitProjectile(local_ae4,0x186a9);
          *local_ae4 = &PTR_FUN_0055658c;
          local_ae4[0xfe7] = 0xffffffff;
        }
        puStack_8 = (undefined1 *)0xffffffff;
        iVar4 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
        uVar23 = *(uint *)(iVar4 + 4);
        while (uVar23 < 0x186ab) {
          if (uVar23 == 0x186aa) {
            piVar17 = *(int **)(iVar4 + 0x10);
            bVar18 = true;
            if (piVar17[2] == 0) goto LAB_00487a8c;
            break;
          }
          iVar4 = *(int *)(iVar4 + 0x1c);
          uVar23 = *(uint *)(iVar4 + 4);
        }
      }
      goto LAB_00487dd6;
    }
    piVar17 = param_1 + 0x3d5;
    cVar1 = PacketChecksumNotEquals(piVar17,0);
    if ((cVar1 != '\0') &&
       (cVar1 = PacketChecksumNotEquals(piVar17,*(int *)(&g_nCameraBoundX + g_clientContext) + -1),
       cVar1 != '\0')) {
      cVar1 = PacketChecksumNotEquals(param_1 + 0x45e,0xfffffeed);
      if ((cVar1 != '\0') &&
         (cVar1 = PacketChecksumNotEquals
                            (param_1 + 0x45e,*(int *)(&g_nCameraBoundY + g_clientContext) + -1),
         cVar1 != '\0')) {
        uVar5 = EncodeChecksumDeltaAdd(piVar17,auStack_ac4,8);
        puStack_8 = (undefined1 *)0x0;
        PeekChecksumStateUnderLock(param_1 + 0x45e);
        PeekChecksumStateUnderLock(uVar5);
        iVar3 = FUN_004e43d0();
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
        uVar5 = EncodeChecksumDeltaAdd(piVar17,auStack_ac4,8);
        puStack_8 = (undefined1 *)0x1;
        iVar4 = PeekChecksumStateUnderLock(uVar5);
        if ((iVar3 == iVar4) || (bVar18 = true, iVar3 == -10000)) {
          bVar18 = false;
        }
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
        if (bVar18) {
          QueueOutgoingPacketField(iVar3 + 1);
        }
        uVar5 = EncodeChecksumDeltaSub(piVar17,auStack_ac4,8);
        puStack_8 = (undefined1 *)0x2;
        PeekChecksumStateUnderLock(param_1 + 0x45e);
        PeekChecksumStateUnderLock(uVar5);
        iVar3 = FUN_004e4410();
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
        uVar5 = EncodeChecksumDeltaSub(piVar17,auStack_ac4,8);
        puStack_8 = (undefined1 *)0x3;
        iVar4 = PeekChecksumStateUnderLock(uVar5);
        if ((iVar3 == iVar4) || (bVar18 = true, iVar3 == 10000)) {
          bVar18 = false;
        }
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
        if (bVar18) {
          QueueOutgoingPacketField(iVar3 + -1);
        }
        uVar5 = FUN_0040b090(piVar17,auStack_ac4,8);
        puStack_8 = (undefined1 *)0x4;
        EncodeChecksumState(uVar5);
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
        PeekChecksumStateUnderLock(param_1 + 0x45e);
        PeekChecksumStateUnderLock(piVar17);
        iVar3 = FindGroundHeightAtColumn();
        if (iVar3 != 10000) {
          uVar5 = EncodeChecksumDeltaSub(param_1 + 0x45e,auStack_ac4,8);
          puStack_8 = (undefined1 *)0x5;
          PeekChecksumStateUnderLock(uVar5);
          PeekChecksumStateUnderLock(piVar17);
          iVar3 = FindGroundHeightAtColumn();
          puStack_8 = (undefined1 *)0xffffffff;
          ScrubChecksumGuard();
          uVar5 = EncodeChecksumDeltaSub(param_1 + 0x45e,auStack_ac4,8);
          puStack_8 = (undefined1 *)0x6;
          iVar4 = PeekChecksumStateUnderLock(uVar5);
          if ((iVar3 == iVar4) || (bVar18 = true, iVar3 == 10000)) {
            bVar18 = false;
          }
          puStack_8 = (undefined1 *)0xffffffff;
          ScrubChecksumGuard();
          if (bVar18) {
            QueueOutgoingPacketField(iVar3 + -1);
          }
          uVar5 = EncodeChecksumDeltaAdd(param_1 + 0x45e,auStack_ac4,8);
          puStack_8 = (undefined1 *)0x7;
          PeekChecksumStateUnderLock(uVar5);
          PeekChecksumStateUnderLock(param_1 + 0x3d5);
          iVar3 = FUN_004e4390();
          puStack_8 = (undefined1 *)0xffffffff;
          ScrubChecksumGuard();
          uVar5 = EncodeChecksumDeltaAdd(param_1 + 0x45e,auStack_ac4,8);
          puStack_8 = (undefined1 *)0x8;
          iVar4 = PeekChecksumStateUnderLock(uVar5);
          if ((iVar3 == iVar4) || (bVar18 = true, iVar3 == -10000)) {
            bVar18 = false;
          }
          puStack_8 = (undefined1 *)0xffffffff;
          ScrubChecksumGuard();
          if (bVar18) {
            QueueOutgoingPacketField(iVar3 + 1);
          }
          uVar5 = FUN_0040b090(param_1 + 0x45e,auStack_ac4,8);
          puStack_8 = (undefined1 *)0x9;
          EncodeChecksumState(uVar5);
          puStack_8 = (undefined1 *)0xffffffff;
          ScrubChecksumGuard();
        }
      }
    }
    uVar5 = PeekChecksumStateUnderLock(param_1 + 0x45e);
    uVar6 = PeekChecksumStateUnderLock(param_1 + 0x3d5);
    FUN_00436b50(uVar6,uVar5);
    if (param_1[0xfe7] == -1) {
      param_1[0xfe7] = 0;
    }
    cVar1 = FUN_004a1740(param_1);
    uVar5 = EncodeChecksumNegate(param_1 + 0x122,auStack_ac4);
    puStack_8 = (undefined1 *)0xa;
    EncodeChecksumState(uVar5);
    puStack_8 = (undefined1 *)0xffffffff;
    ScrubChecksumGuard();
    uVar5 = EncodeChecksumNegate(param_1 + 0x1ab,auStack_ac4);
    puStack_8 = (undefined1 *)0xb;
    EncodeChecksumState(uVar5);
    puStack_8 = (undefined1 *)0xffffffff;
    ScrubChecksumGuard();
    FUN_004585e0();
    if (cVar1 == '\0') {
      PeekChecksumStateUnderLock(param_1 + 0x70b);
    }
    else {
      AddToPacketChecksum(0x5a);
      PeekChecksumStateUnderLock(param_1 + 0x70b);
      PeekChecksumStateUnderLock(param_1 + 0xfe9);
      PeekChecksumStateUnderLock(param_1 + 0xfe9);
    }
    fStack_ae0 = (float)(int)piStack_adc;
    uVar5 = FloatToInt64();
    uVar6 = FloatToInt64();
    QueueOutgoingPacketField(uVar5);
    QueueOutgoingPacketField(uVar6);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(char *)((int)param_1 + 0xf45) = (char)iVar3;
    iVar3 = _rand();
    *(byte *)((int)param_1 + 0xf46) = (byte)iVar3;
    bVar12 = *(byte *)((int)param_1 + 0xf45) & 7;
    bVar12 = ~('\x01' << bVar12) & (byte)iVar3 | '\0' << bVar12;
    *(byte *)((int)param_1 + 0xf46) = bVar12;
    *(byte *)((int)param_1 + 0xf47) = *(byte *)((int)param_1 + 0xf45) + bVar12 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    pcVar16 = (code *)LeaveCriticalSection;
  }
  EncodeChecksumDeltaShr(param_1 + 0x10,auStack_ac4,8);
  puStack_8 = (undefined1 *)0x11;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar5);
  cVar1 = '\0';
  (*pcVar16)();
  uStack_c = 0xffffffff;
  if (iStack_ab4 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&uStack_ad0);
    pcVar14 = (code *)EnterCriticalSection;
    pcVar16 = (code *)LeaveCriticalSection;
  }
  EncodeChecksumDeltaShr(param_1 + 0x99,auStack_ac8,8);
  piStack_adc = param_1 + 0x45e;
  uStack_c = 0x12;
  (*pcVar14)(&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar5);
  cVar20 = '\0';
  (*pcVar16)();
  uStack_14 = 0xffffffff;
  if (iStack_abc != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&iStack_ad8);
    pcVar14 = (code *)EnterCriticalSection;
    pcVar16 = (code *)LeaveCriticalSection;
  }
  cVar2 = CheckGuardedBoolAnd(param_1[0x3d2] != 0);
  if (cVar2 == '\0') {
    (*pcVar14)(&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    iVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar4 + iVar3);
    (*pcVar16)(&DAT_005a9068);
    (*pcVar14)(&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    iVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar8 + iVar4);
    (*pcVar16)(&DAT_005a9068);
  }
  else {
    (*pcVar14)(&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    if ((int)((uVar23 ^ (int)uVar23 >> 0x1f) - ((int)uVar23 >> 0x1f)) < 200) {
      (*pcVar14)(&DAT_005a9068);
      PeekPacketChecksumState();
      (*pcVar16)(&DAT_005a9068);
      if (cVar1 == '\0') {
        uVar5 = 200;
      }
      else {
        uVar5 = 0xffffff38;
      }
      QueueOutgoingPacketField(uVar5);
    }
    uVar5 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_690,4);
    uStack_1c = 0x13;
    EncodeChecksumPairDiff(param_1[0x3d2] + 0x38,auStack_46c,uVar5);
    uStack_1c = 0x14;
    (*pcVar14)(&DAT_005a9068);
    PeekPacketChecksumState();
    PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    if (cVar20 == '\0') {
      uVar5 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_8bc,4);
      uStack_24 = 0x15;
      uVar5 = EncodeChecksumPairSum(param_1[0x3d2] + 0x38,&fStack_ae0,uVar5);
      uStack_24 = 0x16;
      uVar23 = 0xf0;
      cVar1 = CompareChecksumPair(uVar5,iVar3);
      cVar20 = '\0';
      if (cVar1 != '\0') goto LAB_00488365;
    }
    else {
LAB_00488365:
      cVar20 = '\x01';
    }
    uStack_24 = 0x15;
    if ((char)uVar23 < '\0') {
      uVar23 = uVar23 & 0xffffff7f;
      ScrubChecksumGuard();
    }
    uStack_24 = 0x14;
    if ((uVar23 & 0x40) != 0) {
      uVar23 = uVar23 & 0xffffffbf;
      ScrubChecksumGuard();
    }
    uStack_24 = 0x13;
    if ((uVar23 & 0x20) != 0) {
      uVar23 = uVar23 & 0xffffffdf;
      ScrubChecksumGuard();
    }
    uStack_24 = 0xffffffff;
    if ((uVar23 & 0x10) != 0) {
      ScrubChecksumGuard();
    }
    if (cVar20 != '\0') {
      iVar4 = param_1[0x3d4];
      param_1[0x3d4] = iVar4 + 1;
      if (iVar4 + 1 < 3) {
        uVar5 = EncodeChecksumNegate(param_1 + 0x122,auStack_250);
        uStack_24 = 0x17;
        EncodeChecksumState(uVar5);
        uStack_24 = 0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        SetGuardedBool(0);
      }
    }
  }
  (*pcVar14)(&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar16)(&DAT_005a9068);
  if ((char)((uint)iVar3 >> 0x18) == '\0') {
    (*pcVar14)(&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    (*pcVar14)(&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    cVar1 = PacketChecksumLessThan(param_1 + 0x3d5,0xfffffc18);
    if (cVar1 != '\0') goto LAB_00488574;
  }
  else {
LAB_00488574:
    *(undefined1 *)(param_1 + 5) = 1;
    cVar1 = PeekPacketChecksumBool();
    if ((cVar1 != '\0') && (cVar1 = FUN_0043a530(), cVar1 == '\0')) {
      (*pcVar14)(&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      (*pcVar16)(&DAT_005a9068);
      (*pcVar14)(&DAT_005a9068);
      EncodeOutgoingPacketField(uVar5);
      (*pcVar16)(&DAT_005a9068);
      iVar3 = g_clientContext;
      *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
      *(undefined4 *)(&DAT_005f376c + iVar3) = 0;
    }
  }
  cVar1 = CheckBothGuardedBools();
  if (cVar1 != '\0') {
    (*pcVar14)(&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    (*pcVar14)(&DAT_005a9068);
    iVar8 = PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    iVar3 = g_clientContext;
    piVar17 = (int *)(&DAT_006a7708 + g_clientContext);
    cVar1 = PeekPacketChecksumBool();
    if ((cVar1 == '\0') && ((&DAT_006a7758)[iVar3] != '\0')) {
      if (((&DAT_006a7736)[iVar3] == '\x01') &&
         ((uVar23 = iVar4 - *(int *)(&g_nCameraY + iVar3) >> 0x1f,
          200 < (int)((iVar4 - *(int *)(&g_nCameraY + iVar3) ^ uVar23) - uVar23) ||
          (uVar23 = iVar8 - *(int *)(&g_nCameraX + iVar3) >> 0x1f,
          300 < (int)((iVar8 - *(int *)(&g_nCameraX + iVar3) ^ uVar23) - uVar23))))) {
        (&DAT_006a7736)[iVar3] = 0;
      }
      iVar10 = 400;
      if (399 < iVar8) {
        iVar10 = iVar8;
      }
      iVar9 = *(int *)(&g_nCameraBoundX + iVar3) + -400;
      if ((iVar10 <= iVar9) && (iVar9 = iVar8, iVar8 < 400)) {
        iVar9 = 400;
      }
      iVar8 = -0x14;
      if (-0x15 < iVar4) {
        iVar8 = iVar4;
      }
      iVar10 = *(int *)(&g_nCameraBoundY + iVar3) + -0x104;
      if ((iVar8 <= iVar10) && (iVar10 = -0x14, -0x15 < iVar4)) {
        iVar10 = iVar4;
      }
      iVar4 = *piVar17 - iVar9;
      *(int *)(&g_nCameraScrollY + iVar3) = iVar10;
      if (((*(int *)(&DAT_006a770c + iVar3) - iVar10) * (*(int *)(&DAT_006a770c + iVar3) - iVar10) +
           iVar4 * iVar4 < 40000) &&
         (((&DAT_006a7734)[iVar3] == '\x01' || ((&DAT_006a7f6c)[iVar3] == '\0')))) {
        *(int *)(&g_nCameraX + iVar3) = iVar9;
        *piVar17 = iVar9;
        *(int *)(&g_nCameraY + iVar3) = iVar10;
        *(int *)(&DAT_006a770c + iVar3) = iVar10;
      }
      if ((((&DAT_006a7734)[iVar3] == '\0') && ((&DAT_006a7f6c)[iVar3] == '\x01')) &&
         ((&DAT_006a7736)[iVar3] == '\0')) {
        iVar4 = *(int *)(&DAT_006a7730 + iVar3);
        iVar8 = iVar4;
        if (iVar9 <= iVar4) {
          iVar8 = iVar9;
        }
        iVar11 = *(int *)(&DAT_006a772c + iVar3);
        if ((iVar11 <= iVar8) && (iVar11 = iVar4, iVar9 <= iVar4)) {
          iVar11 = iVar9;
        }
        *(int *)(&g_nCameraScrollX + iVar3) = iVar11;
      }
      if ((&DAT_006a7734)[iVar3] == '\x01') {
        *(int *)(&g_nCameraScrollX + iVar3) = iVar9;
        *(int *)(&g_nCameraScrollY + iVar3) = iVar10;
      }
    }
  }
LAB_0048875c:
  *unaff_FS_OFFSET = uStack_1c;
  return;
  while( true ) {
    piVar17 = (int *)piVar17[4];
    bVar18 = piVar17[2] == 0;
    if (!bVar18) break;
LAB_00487a8c:
    if (bVar18) {
      puStack_acc = (undefined4 *)piVar17[0xf];
      piStack_adc = (int *)piVar17[0xe];
      fStack_ae0 = (float)CalculateAngleFromDelta();
      iVar4 = FloatToInt64();
      piStack_adc = (int *)((int)piStack_adc - iVar4);
      iVar4 = FloatToInt64();
      iVar4 = (int)puStack_acc - iVar4;
      (**(code **)(*piVar17 + 4))(&DAT_00553b90);
      piVar17[0x11] = (int)fStack_ae0;
      cVar1 = PeekPacketChecksumBool();
      if (cVar1 == '\0') {
        uStack_680 = 0;
        uStack_88c = 0;
        EncodeOutgoingPacketField(0);
        puStack_8 = (undefined1 *)0xf;
        uStack_8a4 = 0;
        uStack_ab0 = 0;
        EncodeOutgoingPacketField(0);
        SUBFIELD(puStack_8,0,undefined1) = 0x10;
        FUN_004262d0(iStack_ad8 + 0x10,auStack_ac4);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar8 = param_1[0xfe5];
        uVar22 = 0;
        uVar21 = 0xff;
        uVar19 = 100;
        uVar6 = 0;
        PeekPacketChecksumBool(uVar5,0,100,0xff,iVar8,0);
        FUN_00432320((char)param_1[0xf],1,1,uVar5,uVar6,uVar19,uVar21,iVar8,uVar22);
        puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),0xf);
        ScrubChecksumGuard();
LAB_00487d3f:
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        cVar1 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&uStack_ad0,&fStack_ad4,2,1,1);
        if (cVar1 != '\0') {
          uStack_8a4 = 0;
          uStack_ab0 = 0;
          EncodeOutgoingPacketField(0);
          puStack_8 = (undefined1 *)0xd;
          uStack_680 = 0;
          uStack_88c = 0;
          EncodeOutgoingPacketField(0);
          SUBFIELD(puStack_8,0,undefined1) = 0xe;
          QueueOutgoingPacketField(uStack_ad0);
          QueueOutgoingPacketField(fStack_ad4);
          FUN_004262d0(iStack_ad8 + 0x10,auStack_8a0);
          iVar8 = param_1[0xfe5];
          uVar22 = 0;
          uVar21 = 0xff;
          uVar19 = 100;
          uVar6 = 0;
          PeekChecksumStateUnderLock(auStack_8a0);
          uVar5 = PeekChecksumStateUnderLock(auStack_ac4);
          PeekPacketChecksumBool(uVar5,uVar6,uVar19,uVar21,iVar8,uVar22);
          FUN_00432320((char)param_1[0xf],1,1,uVar5,uVar6,uVar19,uVar21,iVar8,uVar22);
          puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),0xd);
          ScrubChecksumGuard();
          goto LAB_00487d3f;
        }
      }
      local_ae4[0xfea] = piStack_adc;
      local_ae4[0xfeb] = iVar4;
      local_ae4[0xfed] = fStack_ad4;
      local_ae4[0xfec] = uStack_ad0;
      local_ae4[0xfee] = fStack_ae0;
      uVar5 = FUN_004ac4d0();
      local_ae4[0xfe9] = uVar5;
      iVar4 = FUN_004ac400();
      local_ae4[0xfe8] = iVar4 * param_1[0xfe5];
      cVar1 = PeekPacketChecksumBool();
      if (cVar1 == '\0') {
        RegisterActiveObject();
      }
      else {
        (**(code **)*local_ae4)(1);
      }
      break;
    }
  }
LAB_00487dd6:
  *(undefined1 *)(param_1 + 5) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  pcVar16 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00436ac0(uVar6,uVar5);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_acc = (undefined4 *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004372f0(param_1[2],puStack_acc,uVar5,param_1[0xe25],param_1 + 0xe26);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_acc = (undefined4 *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00437150(puStack_acc,uVar6,0x3c,uVar5);
  iVar4 = g_clientContext;
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\x01') {
    iVar8 = *(int *)(&DAT_006a7750 + iVar4);
    if (iVar8 < 0x10) {
      iVar8 = 0xf;
    }
    *(int *)(&DAT_006a7750 + iVar4) = iVar8;
    iVar8 = *(int *)(&DAT_006a7754 + iVar4);
    if (iVar8 < 0xb) {
      iVar8 = 10;
    }
    *(int *)(&DAT_006a7754 + iVar4) = iVar8;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004373c0(uVar6,uVar5,0x2078,s_ssflame13_005548d8);
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\0') {
    AcquireSoundChannel(0);
    pcVar16 = (code *)LeaveCriticalSection;
  }
  cVar1 = PeekPacketChecksumBool();
  if ((cVar1 != '\0') && (cVar1 = FUN_0043a530(), cVar1 == '\0')) {
    uVar5 = PeekChecksumStateUnderLock(&DAT_007949c8);
    QueueOutgoingPacketField(uVar5);
    iVar4 = g_clientContext;
    *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
    *(undefined4 *)(&DAT_005f376c + iVar4) = 0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  PeekPacketChecksumState();
  (*pcVar16)(&DAT_005a9068);
  cVar1 = CheckGuardedBoolAnd(CONCAT13(iVar3 != 4,unaff_EBX));
  if (cVar1 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    pcVar16 = (code *)LeaveCriticalSection;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar16)(&DAT_005a9068);
  if ((char)((uint)unaff_ESI >> 0x18) == '\0') {
LAB_004880ef:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    if (0 < iVar3) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      (*pcVar16)(&DAT_005a9068);
      if (iVar3 < 0) goto LAB_0048812f;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    if (iVar3 < 1) goto LAB_004880ef;
LAB_0048812f:
    cVar1 = PeekPacketChecksumBool();
    if (cVar1 == '\0') {
      SetGuardedBool(1);
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  PeekPacketChecksumState();
  (*pcVar16)(&DAT_005a9068);
  if (((char)((uint)unaff_EDI >> 0x18) == '\0') ||
     (cVar1 = CompareChecksumPair(param_1 + 0xed2,param_1 + 0xf5b), cVar1 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    iVar4 = PeekPacketChecksumState();
    (*pcVar16)(&DAT_005a9068);
    if ((iVar3 <= iVar4) ||
       ((cVar1 = CompareChecksumExceeds(param_1 + 0xed2,param_1 + 0xf5b), cVar1 == '\0' ||
        (param_1[0xed1] < 6)))) goto LAB_0048875c;
  }
  iVar3 = g_clientContext;
  pbVar15 = (byte *)(g_clientContext + 0x62143);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = _rand();
  *pbVar15 = (byte)iVar4;
  iVar4 = _rand();
  bVar12 = *pbVar15;
  *(byte *)(iVar3 + 0x62144) = (byte)iVar4;
  bVar13 = '\x01' << (bVar12 & 7);
  bVar12 = *pbVar15;
  bVar13 = ~bVar13 & (byte)iVar4 | bVar13;
  *(byte *)(iVar3 + 0x62144) = bVar13;
  *(byte *)(iVar3 + 0x62145) = bVar13 + bVar12 + -0x34;
  (*pcVar16)(&DAT_005a9068);
  goto LAB_0048875c;
}

