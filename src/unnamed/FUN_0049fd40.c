/* FUN_0049fd40 - 0x0049fd40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0049fd40(int *param_1)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  char *pcVar12;
  byte bVar13;
  uint unaff_EBX;
  code *pcVar14;
  int *piVar15;
  byte *pbVar16;
  undefined4 *unaff_FS_OFFSET;
  bool bVar17;
  undefined *puVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  int *local_af8;
  int *local_af4;
  int *piStack_af0;
  undefined *puStack_aec;
  int *piStack_ae4;
  int *piStack_ae0;
  int iStack_adc;
  int *piStack_ad8;
  int *piStack_ad4;
  int iStack_ad0;
  int *local_acc;
  int *piStack_ac8;
  undefined1 auStack_ac4 [12];
  int iStack_ab8;
  uint uStack_ab4;
  undefined4 uStack_ab0;
  undefined1 auStack_8a8 [4];
  undefined1 uStack_8a4;
  undefined1 auStack_8a0 [20];
  undefined4 uStack_88c;
  undefined1 auStack_684 [4];
  undefined1 uStack_680;
  undefined1 auStack_460 [548];
  undefined1 auStack_23c [556];
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053ecf5;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_af4 = (int *)0x0;
  local_acc = param_1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  iVar4 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar4 + iVar3);
  pcVar14 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_af8 = (int *)PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar3 + (int)local_af8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar1 = FUN_00406690((char)param_1[0xfe8]);
  if ((cVar1 != '\0') || (param_1[0xfe7] == 0x2c)) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    piStack_ae4 = (int *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((0x2b < param_1[0xfe7]) ||
       ((cVar1 = PeekPacketChecksumBool(), cVar1 != '\0' || ((char)param_1[0xfe8] != '\0')))) {
      piStack_ae0 = param_1 + 0x45e;
      piStack_af0 = param_1 + 0x3d5;
      FUN_004262d0(param_1[2],piStack_ae0);
      cVar1 = PeekPacketChecksumBool();
      if (cVar1 != '\0') {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_af4 = (int *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if ((-1 < (int)local_af4) && ((int)local_af4 < *(int *)(&DAT_006a7720 + g_clientContext))) {
          pcVar12 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + (int)local_af4);
          local_af8 = (int *)0x0;
          if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
            do {
              if (*pcVar12 != '\0') goto LAB_004a0a52;
              pcVar12 = pcVar12 + *(int *)(&DAT_006a7720 + g_clientContext);
              local_af8 = (int *)((int)local_af8 + 1);
            } while ((int)local_af8 < *(int *)(&DAT_006a7724 + g_clientContext));
          }
        }
        local_af8 = (int *)0x2710;
LAB_004a0a52:
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436070(&DAT_006a7f70 + g_clientContext,uVar5,local_af8);
        local_af4 = (int *)0x1;
        if (0 < param_1[0xfe5]) {
          local_af4 = (int *)param_1[0xfe5];
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        piStack_ae4 = (int *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        piStack_ad8 = (int *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iStack_adc = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_0043af40(iStack_adc,local_af8,0,piStack_ad8,(int)piStack_ae4 / (int)local_af4,uVar5,
                     (char)param_1[0xf]);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        piStack_ae4 = (int *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar21 = 0;
        uVar20 = 2;
        uVar19 = 0xff;
        uVar6 = 0;
        PeekPacketChecksumBool(0,uVar5,0xff,2,0);
        FUN_00431d90((char)param_1[0xf],7,0,uVar6,uVar5,uVar19,uVar20,uVar21);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_af4 = (int *)PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_acc = (int *)param_1[2];
      puStack_aec = &DAT_006a7f70 + g_clientContext;
      piStack_ad8 = local_af4;
      iStack_adc = iVar3;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar3 == 4) {
        local_af8 = operator_new(0x3fbc);
        puStack_8 = (undefined1 *)0xc;
        piStack_ad4 = local_af8;
        if (local_af8 == (int *)0x0) {
          local_af8 = (int *)0x0;
        }
        else {
          InitProjectile(local_af8,0x186a9);
          *local_af8 = (int)&PTR_FUN_0055658c;
          local_af8[0xfe7] = -1;
        }
        puStack_8 = (undefined1 *)0xffffffff;
        iVar3 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
        uVar7 = *(uint *)(iVar3 + 4);
        while (uVar7 < 0x186ab) {
          if (uVar7 == 0x186aa) {
            piVar15 = *(int **)(iVar3 + 0x10);
            bVar17 = true;
            piStack_ac8 = piVar15;
            if (piVar15[2] == 0) goto LAB_004a0ccf;
            break;
          }
          iVar3 = *(int *)(iVar3 + 0x1c);
          uVar7 = *(uint *)(iVar3 + 4);
        }
      }
      goto LAB_004a101f;
    }
    piVar15 = param_1 + 0x3d5;
    cVar1 = PacketChecksumNotEquals(piVar15,0);
    if ((cVar1 != '\0') &&
       (cVar1 = PacketChecksumNotEquals(piVar15,*(int *)(&DAT_006a7720 + g_clientContext) + -1),
       cVar1 != '\0')) {
      cVar1 = PacketChecksumNotEquals(param_1 + 0x45e,0xfffffeed);
      if ((cVar1 != '\0') &&
         (cVar1 = PacketChecksumNotEquals
                            (param_1 + 0x45e,*(int *)(&DAT_006a7724 + g_clientContext) + -1),
         cVar1 != '\0')) {
        uVar5 = EncodeChecksumDeltaAdd(piVar15,auStack_ac4,8);
        puStack_8 = (undefined1 *)0x0;
        PeekChecksumStateUnderLock(param_1 + 0x45e);
        PeekChecksumStateUnderLock(uVar5);
        iVar3 = FUN_004e43d0();
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
        uVar5 = EncodeChecksumDeltaAdd(piVar15,auStack_ac4,8);
        puStack_8 = (undefined1 *)0x1;
        iVar4 = PeekChecksumStateUnderLock(uVar5);
        if ((iVar3 == iVar4) || (bVar17 = true, iVar3 == -10000)) {
          bVar17 = false;
        }
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
        if (bVar17) {
          QueueOutgoingPacketField(iVar3 + 1);
        }
        uVar5 = EncodeChecksumDeltaSub(piVar15,auStack_ac4,8);
        puStack_8 = (undefined1 *)0x2;
        PeekChecksumStateUnderLock(param_1 + 0x45e);
        PeekChecksumStateUnderLock(uVar5);
        iVar3 = FUN_004e4410();
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
        uVar5 = EncodeChecksumDeltaSub(piVar15,auStack_ac4,8);
        puStack_8 = (undefined1 *)0x3;
        local_af8 = (int *)0x2;
        iVar4 = PeekChecksumStateUnderLock(uVar5);
        if ((iVar3 == iVar4) || (bVar17 = true, iVar3 == 10000)) {
          bVar17 = false;
        }
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
        if (bVar17) {
          QueueOutgoingPacketField(iVar3 + -1);
        }
        uVar5 = FUN_0040b090(piVar15,auStack_ac4,8);
        puStack_8 = (undefined1 *)0x4;
        EncodeChecksumState(uVar5);
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
        PeekChecksumStateUnderLock(param_1 + 0x45e);
        PeekChecksumStateUnderLock(piVar15);
        iVar3 = FindGroundHeightAtColumn();
        if (iVar3 != 10000) {
          uVar5 = EncodeChecksumDeltaSub(param_1 + 0x45e,auStack_ac4,8);
          puStack_8 = (undefined1 *)0x5;
          PeekChecksumStateUnderLock(uVar5);
          PeekChecksumStateUnderLock(piVar15);
          iVar3 = FindGroundHeightAtColumn();
          puStack_8 = (undefined1 *)0xffffffff;
          ScrubChecksumGuard();
          uVar5 = EncodeChecksumDeltaSub(param_1 + 0x45e,auStack_ac4,8);
          puStack_8 = (undefined1 *)0x6;
          iVar4 = PeekChecksumStateUnderLock(uVar5);
          if ((iVar3 == iVar4) || (bVar17 = true, iVar3 == 10000)) {
            bVar17 = false;
          }
          puStack_8 = (undefined1 *)0xffffffff;
          ScrubChecksumGuard();
          if (bVar17) {
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
          local_af8 = (int *)0x8;
          iVar4 = PeekChecksumStateUnderLock(uVar5);
          if ((iVar3 == iVar4) || (bVar17 = true, iVar3 == -10000)) {
            bVar17 = false;
          }
          puStack_8 = (undefined1 *)0xffffffff;
          ScrubChecksumGuard();
          if (bVar17) {
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
    bVar2 = FUN_004a1740(param_1);
    unaff_EBX = (uint)bVar2 << 0x18;
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
    if (bVar2 == 0) {
      PeekChecksumStateUnderLock(param_1 + 0x70b);
    }
    else {
      AddToPacketChecksum(0x5a);
      PeekChecksumStateUnderLock(param_1 + 0x70b);
      PeekChecksumStateUnderLock(param_1 + 0xfe9);
      PeekChecksumStateUnderLock(param_1 + 0xfe9);
    }
    /* float->pointer isn't a legal C cast; go through (int) (raw-port
     * register-reuse artifact, value semantics unverified). */
    local_af4 = (int *)(int)(float)(int)piStack_ae4;
    uVar5 = FloatToInt64();
    uVar6 = FloatToInt64();
    QueueOutgoingPacketField(uVar5);
    QueueOutgoingPacketField(uVar6);
    SetGuardedBool(0);
    pcVar14 = (code *)LeaveCriticalSection;
  }
  EncodeChecksumDeltaShr(param_1 + 0x10,auStack_ac4,8);
  piStack_af0 = param_1 + 0x3d5;
  puStack_8 = (undefined1 *)0x11;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar5);
  (*pcVar14)(&DAT_005a9068);
  uStack_c = 0xffffffff;
  if (uStack_ab4 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&piStack_af0);
    param_1 = piStack_ad4;
    pcVar14 = (code *)LeaveCriticalSection;
    unaff_EBX = uStack_ab4;
  }
  EncodeChecksumDeltaShr(param_1 + 0x99,&piStack_ac8,8);
  piStack_ae4 = param_1 + 0x45e;
  uStack_c = 0x12;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar5);
  (*pcVar14)(&DAT_005a9068);
  uStack_10 = 0xffffffff;
  if (iStack_ab8 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&local_af4);
    param_1 = piStack_ad8;
    pcVar14 = (code *)LeaveCriticalSection;
  }
  cVar1 = CheckGuardedBoolAnd(param_1[0x3d2] != 0);
  if (cVar1 == '\0') {
    EmitChecksumSum(param_1 + 0x2bd);
    EmitChecksumSum(param_1 + 0x346);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    (*pcVar14)(&DAT_005a9068);
    if ((int)((uVar7 ^ (int)uVar7 >> 0x1f) - ((int)uVar7 >> 0x1f)) < 200) {
      cVar1 = PacketChecksumLessThan(param_1 + 0x122,0);
      if (cVar1 == '\0') {
        uVar5 = 200;
      }
      else {
        uVar5 = 0xffffff38;
      }
      QueueOutgoingPacketField(uVar5);
    }
    uVar5 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_684,4);
    uStack_10 = 0x13;
    uVar5 = EncodeChecksumPairDiff(param_1[0x3d2] + 0x38,auStack_460,uVar5);
    uStack_10 = 0x14;
    unaff_EBX = 0x30;
    cVar1 = CompareChecksumPair(local_af8,uVar5);
    if (cVar1 == '\0') {
      uVar5 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_8a8,4);
      uStack_10 = 0x15;
      uVar5 = EncodeChecksumPairSum(param_1[0x3d2] + 0x38,&local_acc,uVar5);
      uStack_10 = 0x16;
      unaff_EBX = 0xf0;
      cVar1 = CompareChecksumPair(uVar5,local_af8);
      bVar17 = false;
      if (cVar1 != '\0') goto LAB_004a0643;
    }
    else {
LAB_004a0643:
      bVar17 = true;
    }
    uStack_10 = 0x15;
    if ((char)unaff_EBX < '\0') {
      unaff_EBX = unaff_EBX & 0xffffff7f;
      ScrubChecksumGuard();
    }
    uStack_10 = 0x14;
    if ((unaff_EBX & 0x40) != 0) {
      unaff_EBX = unaff_EBX & 0xffffffbf;
      ScrubChecksumGuard();
    }
    uStack_10 = 0x13;
    if ((unaff_EBX & 0x20) != 0) {
      unaff_EBX = unaff_EBX & 0xffffffdf;
      ScrubChecksumGuard();
    }
    uStack_10 = 0xffffffff;
    if ((unaff_EBX & 0x10) != 0) {
      ScrubChecksumGuard();
    }
    if (bVar17) {
      iVar3 = param_1[0x3d4];
      param_1[0x3d4] = iVar3 + 1;
      if (iVar3 + 1 < 3) {
        uVar5 = EncodeChecksumNegate(param_1 + 0x122,auStack_23c);
        uStack_10 = 0x17;
        EncodeChecksumState(uVar5);
        uStack_10 = 0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        SetGuardedBool(0);
      }
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar14)(&DAT_005a9068);
  if ((char)(unaff_EBX >> 0x18) == '\0') {
    iVar3 = *(int *)(&DAT_006a7720 + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    (*pcVar14)(&DAT_005a9068);
    if (((iVar3 < iVar4) ||
        (cVar1 = PacketChecksumGreaterThan(piStack_ae0,*(undefined4 *)(&DAT_006a7724 + g_clientContext)),
        cVar1 != '\0')) || (cVar1 = PacketChecksumLessThan(piStack_ae0,0xfffffc18), cVar1 != '\0'))
    goto LAB_004a07f1;
  }
  else {
LAB_004a07f1:
    *(undefined1 *)(param_1 + 5) = 1;
    cVar1 = PeekPacketChecksumBool();
    if ((cVar1 != '\0') && (cVar1 = FUN_0043a530(), cVar1 == '\0')) {
      uVar5 = PeekChecksumStateUnderLock(&DAT_007949c8);
      QueueOutgoingPacketField(uVar5);
    }
  }
  cVar1 = CheckBothGuardedBools();
  if (cVar1 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    (*pcVar14)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = PeekPacketChecksumState();
    (*pcVar14)(&DAT_005a9068);
    iVar3 = g_clientContext;
    piVar15 = (int *)(&DAT_006a7708 + g_clientContext);
    cVar1 = PeekPacketChecksumBool();
    if ((cVar1 == '\0') && ((&DAT_006a7758)[iVar3] != '\0')) {
      if (((&DAT_006a7736)[iVar3] == '\x01') &&
         ((uVar7 = iVar4 - *(int *)(&DAT_006a7714 + iVar3) >> 0x1f,
          200 < (int)((iVar4 - *(int *)(&DAT_006a7714 + iVar3) ^ uVar7) - uVar7) ||
          (uVar7 = iVar8 - *(int *)(&DAT_006a7710 + iVar3) >> 0x1f,
          300 < (int)((iVar8 - *(int *)(&DAT_006a7710 + iVar3) ^ uVar7) - uVar7))))) {
        (&DAT_006a7736)[iVar3] = 0;
      }
      iVar10 = 400;
      if (399 < iVar8) {
        iVar10 = iVar8;
      }
      iVar9 = *(int *)(&DAT_006a7720 + iVar3) + -400;
      if ((iVar10 <= iVar9) && (iVar9 = iVar8, iVar8 < 400)) {
        iVar9 = 400;
      }
      iVar8 = -0x14;
      if (-0x15 < iVar4) {
        iVar8 = iVar4;
      }
      iVar10 = *(int *)(&DAT_006a7724 + iVar3) + -0x104;
      if ((iVar8 <= iVar10) && (iVar10 = -0x14, -0x15 < iVar4)) {
        iVar10 = iVar4;
      }
      iVar4 = *piVar15 - iVar9;
      *(int *)(&DAT_006a771c + iVar3) = iVar10;
      if (((*(int *)(&DAT_006a770c + iVar3) - iVar10) * (*(int *)(&DAT_006a770c + iVar3) - iVar10) +
           iVar4 * iVar4 < 40000) &&
         (((&DAT_006a7734)[iVar3] == '\x01' || ((&DAT_006a7f6c)[iVar3] == '\0')))) {
        *(int *)(&DAT_006a7710 + iVar3) = iVar9;
        *piVar15 = iVar9;
        *(int *)(&DAT_006a7714 + iVar3) = iVar10;
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
        *(int *)(&DAT_006a7718 + iVar3) = iVar11;
      }
      if ((&DAT_006a7734)[iVar3] == '\x01') {
        *(int *)(&DAT_006a7718 + iVar3) = iVar9;
        *(int *)(&DAT_006a771c + iVar3) = iVar10;
      }
    }
  }
LAB_004a166b:
  *unaff_FS_OFFSET = uStack_10;
  return;
  while( true ) {
    piVar15 = (int *)piVar15[4];
    bVar17 = piVar15[2] == 0;
    piStack_ac8 = piVar15;
    if (!bVar17) break;
LAB_004a0ccf:
    if (bVar17) {
      piStack_ad4 = (int *)piVar15[0xf];
      piStack_ae4 = (int *)piVar15[0xe];
      piStack_ac8 = piVar15;
      local_af4 = (int *)CalculateAngleFromDelta();
      iVar3 = FloatToInt64();
      piStack_ae4 = (int *)((int)piStack_ae4 - iVar3);
      iVar3 = FloatToInt64();
      iVar3 = (int)piStack_ad4 - iVar3;
      (**(code **)(*piVar15 + 4))(&DAT_00553b90);
      piVar15[0x11] = (int)local_af4;
      piStack_ad4 = (int *)(puStack_aec + 4);
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
        FUN_004262d0(local_acc + 4,auStack_ac4);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        puStack_aec = (undefined *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar4 = param_1[0xfe5];
        uVar20 = 0;
        uVar19 = 0xff;
        uVar6 = 100;
        uVar5 = 0;
        puVar18 = puStack_aec;
        PeekPacketChecksumBool(puStack_aec,0,100,0xff,iVar4,0);
        FUN_00432320((char)param_1[0xf],1,1,puVar18,uVar5,uVar6,uVar19,iVar4,uVar20);
        puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),0xf);
        ScrubChecksumGuard();
LAB_004a0f88:
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        cVar1 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&iStack_adc,&piStack_ad8,2,1,1);
        if (cVar1 != '\0') {
          uStack_8a4 = 0;
          uStack_ab0 = 0;
          EncodeOutgoingPacketField(0);
          puStack_8 = (undefined1 *)0xd;
          uStack_680 = 0;
          uStack_88c = 0;
          EncodeOutgoingPacketField(0);
          SUBFIELD(puStack_8,0,undefined1) = 0xe;
          QueueOutgoingPacketField(iStack_adc);
          QueueOutgoingPacketField(piStack_ad8);
          FUN_004262d0(local_acc + 4,auStack_8a0);
          iVar4 = param_1[0xfe5];
          uVar21 = 0;
          uVar20 = 0xff;
          uVar19 = 100;
          uVar6 = 0;
          PeekChecksumStateUnderLock(auStack_8a0);
          uVar5 = PeekChecksumStateUnderLock(auStack_ac4);
          PeekPacketChecksumBool(uVar5,uVar6,uVar19,uVar20,iVar4,uVar21);
          FUN_00432320((char)param_1[0xf],1,1,uVar5,uVar6,uVar19,uVar20,iVar4,uVar21);
          puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),0xd);
          ScrubChecksumGuard();
          goto LAB_004a0f88;
        }
      }
      local_af8[0xfea] = (int)piStack_ae4;
      local_af8[0xfeb] = iVar3;
      local_af8[0xfec] = iStack_adc;
      local_af8[0xfed] = (int)piStack_ad8;
      local_af8[0xfee] = (int)local_af4;
      iVar3 = FUN_004ac4d0();
      local_af8[0xfe9] = iVar3;
      iVar3 = FUN_004ac400();
      local_af8[0xfe8] = iVar3 * param_1[0xfe5];
      cVar1 = PeekPacketChecksumBool();
      if (cVar1 == '\0') {
        RegisterActiveObject();
      }
      else {
        (**(code **)*local_af8)(1);
      }
      break;
    }
  }
LAB_004a101f:
  *(undefined1 *)(iStack_ad0 + 0x14) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_aec = (undefined *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piStack_ad4 = (int *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piStack_ae4 = (int *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_af4 = (int *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piStack_ad8 = (int *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar19 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iStack_adc = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_acc = (int *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004e4970(uVar19,piStack_ad8,local_af4,piStack_ae4,uVar6,piStack_ad4,puStack_aec,uVar5);
  FUN_004e4d00(&DAT_006a7708 + g_clientContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_aec = (undefined *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = iStack_ad0;
  FUN_00450eb0(puStack_aec,uVar5,iStack_ad0,1,0,0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_aec = (undefined *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00436ac0(puStack_aec,uVar5);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_aec = (undefined *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004372f0(*(undefined4 *)(iVar3 + 8),puStack_aec,uVar5,*(undefined4 *)(iVar3 + 0x3894),
               iVar3 + 0x3898);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_aec = (undefined *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00437150(puStack_aec,uVar6,0x3c,uVar5);
  iVar3 = g_clientContext;
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\x01') {
    iVar4 = *(int *)(&DAT_006a7750 + iVar3);
    if (iVar4 < 0x10) {
      iVar4 = 0xf;
    }
    *(int *)(&DAT_006a7750 + iVar3) = iVar4;
    iVar4 = *(int *)(&DAT_006a7754 + iVar3);
    if (iVar4 < 0xb) {
      iVar4 = 10;
    }
    *(int *)(&DAT_006a7754 + iVar3) = iVar4;
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\0') {
    AcquireSoundChannel(0);
  }
  cVar1 = PeekPacketChecksumBool();
  if ((cVar1 != '\0') && (cVar1 = FUN_0043a530(), cVar1 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_aec = (undefined *)(g_clientContext + 0x621e8);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_aec = (undefined *)PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  puStack_aec = (undefined *)CONCAT31(SUBFIELD(puStack_aec,1,undefined3),(int)puStack_aec < iVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar1 = CheckGuardedBoolAnd(puStack_aec);
  if (cVar1 != '\0') {
    puStack_aec = (undefined *)(g_clientContext + 0x5b85c);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 < 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar3 < 1) goto LAB_004a1483;
LAB_004a14d3:
    cVar1 = PeekPacketChecksumBool();
    iVar3 = g_clientContext;
    if (cVar1 == '\0') {
      pbVar16 = (byte *)(g_clientContext + 0x62146);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = _rand();
      *pbVar16 = (byte)iVar4;
      iVar4 = _rand();
      bVar2 = *pbVar16;
      *(byte *)(iVar3 + 0x62147) = (byte)iVar4;
      bVar13 = '\x01' << (bVar2 & 7);
      bVar2 = *pbVar16;
      bVar13 = ~bVar13 & (byte)iVar4 | bVar13;
      *(byte *)(iVar3 + 0x62147) = bVar13;
      *(byte *)(iVar3 + 0x62148) = bVar13 + bVar2 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
  }
  else {
LAB_004a1483:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar3) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar3 < 0) goto LAB_004a14d3;
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_aec = (undefined *)PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  bVar17 = (int)puStack_aec < iVar3;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (bVar17) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_aec = (undefined *)PeekPacketChecksumState();
    iVar3 = PeekPacketChecksumState();
    bVar17 = iVar3 <= (int)puStack_aec;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (bVar17) goto LAB_004a15b5;
  }
  else {
LAB_004a15b5:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_aec = (undefined *)PeekPacketChecksumState();
    iVar3 = PeekPacketChecksumState();
    bVar17 = (int)puStack_aec <= iVar3;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (((bVar17) || (cVar1 = CompareChecksumExceeds(iStack_ad0 + 0x3b48,iStack_ad0 + 0x3d6c), cVar1 == '\0'))
       || (*(int *)(iStack_ad0 + 0x3b44) < 6)) goto LAB_004a166b;
  }
  iVar3 = g_clientContext;
  pbVar16 = (byte *)(g_clientContext + 0x62143);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = _rand();
  *pbVar16 = (byte)iVar4;
  iVar4 = _rand();
  bVar2 = *pbVar16;
  *(byte *)(iVar3 + 0x62144) = (byte)iVar4;
  bVar13 = '\x01' << (bVar2 & 7);
  bVar13 = ~bVar13 & (byte)iVar4 | bVar13;
  *(byte *)(iVar3 + 0x62144) = bVar13;
  *(byte *)(iVar3 + 0x62145) = bVar13 + bVar2 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  goto LAB_004a166b;
}

