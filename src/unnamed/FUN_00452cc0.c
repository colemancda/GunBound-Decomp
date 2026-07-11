/* FUN_00452cc0 - 0x00452cc0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00452cc0(int *param_1)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffff500;
  undefined stack0xfffff504;
  undefined stack0xfffff50c;
  undefined stack0xfffff510;
  undefined stack0xfffff514;
  undefined stack0xfffff518;
  undefined stack0xfffff51c;
  int *piVar1;
  byte bVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  int iVar12;
  int iVar13;
  char *pcVar14;
  code *pcVar15;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  char cVar19;
  undefined *puVar20;
  undefined *puVar21;
  undefined *puVar22;
  uint uStack_ae0;
  char cStack_ad9;
  undefined1 auStack_ad4 [4];
  undefined1 auStack_ad0 [4];
  undefined1 auStack_acc [4];
  undefined4 uStack_ac8;
  int iStack_ac0;
  int iStack_abc;
  int iStack_ab8;
  int iStack_ab4;
  int iStack_ab0;
  uint uStack_aac;
  undefined1 auStack_8d0 [32];
  undefined1 auStack_8b0 [4];
  undefined1 auStack_8ac [4];
  undefined1 auStack_8a8 [12];
  int iStack_89c;
  int iStack_898;
  int iStack_894;
  int iStack_890;
  int iStack_88c;
  uint uStack_888;
  undefined1 auStack_6ac [548];
  undefined1 auStack_488 [548];
  undefined1 auStack_264 [556];
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0054061d;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  if ((param_1[0xfe7] != -1) && (iVar5 = param_1[0xfe7] + 1, param_1[0xfe7] = iVar5, iVar5 == 0x24))
  {
    param_1[0xfe7] = -1;
    (**(code **)(*param_1 + 4))();
  }
  pcVar15 = (code *)LeaveCriticalSection;
  if ((char)param_1[0xd] == '\x01') {
    if (param_1[9] == 1) {
      (**(code **)(*param_1 + 4))();
      FUN_0040ada0();
      puStack_8 = (undefined1 *)0x0;
      EncodeChecksumDeltaDiv();
      puStack_8 = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      EncodeOutgoingPacketField();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      puStack_8 = (undefined1 *)0;
      if (iStack_88c != 0) {
        ScrambleChecksumGuardBytes();
        FUN_0040b540();
        pcVar15 = (code *)LeaveCriticalSection;
      }
      puStack_8 = (undefined1 *)0xffffffff;
      if (iStack_ab0 != 0) {
        ScrambleChecksumGuardBytes();
        FUN_0040b540();
        pcVar15 = (code *)LeaveCriticalSection;
      }
      FUN_0040ada0();
      puStack_8 = (undefined1 *)0x2;
      EncodeChecksumDeltaDiv();
      puStack_8 = (undefined1 *)3;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      EncodeOutgoingPacketField();
      (*pcVar15)();
      uStack_c = 2;
      if (iStack_ab4 != 0) {
        ScrambleChecksumGuardBytes();
        FUN_0040b540();
        pcVar15 = (code *)LeaveCriticalSection;
      }
      uStack_c = 0xffffffff;
      if (iStack_890 != 0) {
        ScrambleChecksumGuardBytes();
        FUN_0040b540();
        pcVar15 = (code *)LeaveCriticalSection;
      }
      uVar6 = FUN_0040ada0(param_1 + 0x8a7);
      uStack_c = 4;
      EncodeChecksumDeltaDiv(uVar6);
      uStack_c = 5;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      EncodeOutgoingPacketField();
      (*pcVar15)();
      uStack_10 = 4;
      if (iStack_ab8 != 0) {
        ScrambleChecksumGuardBytes();
        FUN_0040b540();
        pcVar15 = (code *)LeaveCriticalSection;
      }
      uStack_10 = 0xffffffff;
      if (iStack_894 != 0) {
        ScrambleChecksumGuardBytes();
        FUN_0040b540();
        pcVar15 = (code *)LeaveCriticalSection;
      }
      uVar6 = FUN_0040ada0(param_1 + 0x930,auStack_8a8);
      uStack_10 = 6;
      EncodeChecksumDeltaDiv(uVar6,auStack_acc);
      uStack_10 = 7;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      EncodeOutgoingPacketField();
      (*pcVar15)();
      uStack_14 = 6;
      if (iStack_abc != 0) {
        ScrambleChecksumGuardBytes();
        FUN_0040b540(&stack0xfffff51c);
        pcVar15 = (code *)LeaveCriticalSection;
      }
      uStack_14 = 0xffffffff;
      if (iStack_898 != 0) {
        ScrambleChecksumGuardBytes();
        FUN_0040b540(&stack0xfffff51c);
        pcVar15 = (code *)LeaveCriticalSection;
      }
      uVar6 = FUN_0040ada0(param_1 + 0x9b9,auStack_8ac,param_1 + 0xd7b);
      uStack_14 = 8;
      EncodeChecksumDeltaDiv(uVar6,auStack_ad0,100);
      uStack_14 = 9;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar6 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar6);
      (*pcVar15)(&DAT_005a9068);
      uStack_18 = 8;
      if (iStack_ac0 != 0) {
        ScrambleChecksumGuardBytes();
        FUN_0040b540(&stack0xfffff518);
        pcVar15 = (code *)LeaveCriticalSection;
      }
      uStack_18 = 0xffffffff;
      if (iStack_89c != 0) {
        ScrambleChecksumGuardBytes();
        FUN_0040b540(&stack0xfffff518);
        pcVar15 = (code *)LeaveCriticalSection;
      }
      uVar6 = FUN_0040ada0(param_1 + 0xa42,auStack_8b0,param_1 + 0xd7b);
      uStack_18 = 10;
      EncodeChecksumDeltaDiv(uVar6,auStack_ad4,100);
      uStack_18 = 0xb;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar6 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar6);
      (*pcVar15)(&DAT_005a9068);
      uStack_4 = 10;
      if (uStack_aac != 0) {
        ScrambleChecksumGuardBytes();
        uStack_ae0 = uStack_aac;
        FUN_0040b540();
        pcVar15 = (code *)LeaveCriticalSection;
      }
      uStack_4 = 0xffffffff;
      if (uStack_888 != 0) {
        ScrambleChecksumGuardBytes();
        uStack_ae0 = uStack_888;
        FUN_0040b540();
        pcVar15 = (code *)LeaveCriticalSection;
      }
      goto LAB_00453238;
    }
  }
  else {
LAB_00453238:
    if (param_1[9] == 1) goto LAB_00453f0d;
  }
  cVar3 = PeekPacketChecksumBool();
  if (cVar3 == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField();
    (*pcVar15)();
  }
  else {
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 == '\0') {
      FUN_004585e0();
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = _rand();
      *(byte *)((int)param_1 + 0x3fa3) = (byte)iVar5;
      uVar7 = _rand();
      uStack_ae0 = uVar7 & 0x800000ff;
      if ((int)uStack_ae0 < 0) {
        uStack_ae0 = (uStack_ae0 - 1 | 0xffffff00) + 1;
      }
      bVar2 = *(byte *)((int)param_1 + 0x3fa3);
      *(byte *)(param_1 + 0xfe9) = (byte)uStack_ae0;
      bVar4 = '\x01' << (bVar2 & 7);
      bVar4 = ~bVar4 & (byte)uStack_ae0 | bVar4;
      *(byte *)(param_1 + 0xfe9) = bVar4;
      *(byte *)((int)param_1 + 0x3fa5) = bVar2 + bVar4 + -0x34;
      (*pcVar15)();
      cVar3 = PacketChecksumLessThan();
      param_1[0xfea] = (-(uint)(cVar3 != '\0') & 2) - 1;
    }
    if (param_1[0xfea] == 0) {
      FUN_004585e0();
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  (*pcVar15)();
  iVar5 = (iVar5 + 0xb4) % 0x168;
  if (iVar5 < 0) {
    iVar5 = iVar5 + 0x168;
  }
  uStack_ac8 = *(undefined4 *)(&g_sineTable360 + iVar5 * 4);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  puVar22 = &DAT_005a9068;
  (*pcVar15)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar15)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar15)();
  FloatToInt64();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = PeekPacketChecksumState();
  puVar21 = &DAT_005a9068;
  (*pcVar15)(&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  puVar20 = &DAT_005a9068;
  (*pcVar15)(&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar15)(&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar9 = PeekPacketChecksumState();
  (*pcVar15)(&DAT_005a9068);
  iVar10 = FloatToInt64();
  iVar5 = -(iVar10 / iVar9);
  if (0 < iVar5) {
    puVar22 = (undefined *)-(int)puVar22;
    iVar5 = iVar10 / iVar9;
  }
  cVar3 = FUN_00406860();
  if (cVar3 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar9 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(puVar22 + iVar9);
    (*pcVar15)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar9 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(puVar21 + iVar9);
    (*pcVar15)(&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar9 = PeekPacketChecksumState();
  iVar10 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar10 + iVar9);
  (*pcVar15)(&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar10 = PeekPacketChecksumState();
  iVar9 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar9 + iVar10);
  (*pcVar15)(&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar3 = PeekPacketChecksumBool();
  cStack_ad9 = (char)((uint)iVar8 >> 0x18);
  if (cVar3 == '\0') {
    EncodeChecksumDeltaShr(param_1 + 0x10,&stack0xfffff514,8);
    uStack_30 = 0xc;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar6);
    (*pcVar15)(&DAT_005a9068);
    uStack_34 = 0xffffffff;
    if (iVar8 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&stack0xfffff504);
      pcVar15 = (code *)LeaveCriticalSection;
    }
    EncodeChecksumDeltaShr(param_1 + 0x99,&stack0xfffff510,8);
    uStack_34 = 0xd;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar6);
    (*pcVar15)(&DAT_005a9068);
    uStack_38 = 0xffffffff;
    if (uStack_ae0 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&stack0xfffff500);
      pcVar15 = (code *)LeaveCriticalSection;
    }
    cVar3 = FUN_00406610(param_1[0x3d2] != 0);
    if (cVar3 == '\0') {
      EmitChecksumSum(param_1 + 0x2bd);
      EmitChecksumSum(param_1 + 0x346);
      cVar3 = PacketChecksumGreaterThan(param_1 + 0x1ab,0);
      if (cVar3 != '\0') {
        param_1[0xfea] = 0;
      }
    }
    else {
      uVar7 = PeekChecksumStateUnderLock(param_1 + 0x122);
      if ((int)((uVar7 ^ (int)uVar7 >> 0x1f) - ((int)uVar7 >> 0x1f)) < 200) {
        cVar3 = PacketChecksumLessThan(param_1 + 0x122,0);
        if (cVar3 == '\0') {
          uVar6 = 200;
        }
        else {
          uVar6 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar6);
      }
      uVar6 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_488,4);
      uStack_38 = 0xe;
      uVar6 = EncodeChecksumPairDiff(param_1[0x3d2] + 0x38,auStack_6ac,uVar6);
      uStack_38 = 0xf;
      uVar7 = 3;
      cVar3 = CompareChecksumPair(param_1 + 0x3d5,uVar6);
      if (cVar3 == '\0') {
        uVar6 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_8d0,4);
        uStack_38 = 0x10;
        uVar6 = EncodeChecksumPairSum(param_1[0x3d2] + 0x38,&stack0xfffff50c,uVar6);
        uStack_38 = 0x11;
        uVar7 = 0xf;
        cVar3 = CompareChecksumPair(uVar6,param_1 + 0x3d5);
        cVar19 = '\0';
        if (cVar3 != '\0') goto LAB_00453b3c;
      }
      else {
LAB_00453b3c:
        cVar19 = '\x01';
      }
      uStack_38 = 0x10;
      if ((uVar7 & 8) != 0) {
        uVar7 = uVar7 & 0xfffffff7;
        ScrubChecksumGuard();
      }
      uStack_38 = 0xf;
      if ((uVar7 & 4) != 0) {
        uVar7 = uVar7 & 0xfffffffb;
        ScrubChecksumGuard();
      }
      uStack_38 = 0xe;
      if ((uVar7 & 2) != 0) {
        uVar7 = uVar7 & 0xfffffffd;
        ScrubChecksumGuard();
      }
      uStack_38 = 0xffffffff;
      if ((uVar7 & 1) != 0) {
        ScrubChecksumGuard();
      }
      if (cVar19 != '\0') {
        iVar5 = param_1[0x3d4];
        param_1[0x3d4] = iVar5 + 1;
        if (iVar5 + 1 < 3) {
          uVar6 = FUN_0040a500(param_1 + 0x122,auStack_264);
          uStack_38 = 0x12;
          EncodeChecksumState(uVar6);
          uStack_38 = 0xffffffff;
          ScrubChecksumGuard();
        }
        else {
          SetGuardedBool(0);
        }
      }
    }
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 != '\0') {
      AddToPacketChecksum(param_1[0xfea]);
      if (((param_1[0xfea] == 1) && (cVar3 = PacketChecksumGreaterEqual(param_1 + 0x70b,0x5a), cVar3 != '\0')) ||
         ((param_1[0xfea] == -1 && (cVar3 = PacketChecksumLessEqual(param_1 + 0x70b,0x5a), cVar3 != '\0')))) {
        param_1[0xfea] = 0;
        QueueOutgoingPacketField(0);
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar15)(&DAT_005a9068);
    if ((((cStack_ad9 != '\0') || (cVar3 = PacketChecksumGreaterEqual(), cVar3 != '\0')) ||
        (cVar3 = PacketChecksumGreaterEqual(), cVar3 != '\0')) || (cVar3 = PacketChecksumLessThan(), cVar3 != '\0')) {
      *(undefined1 *)(param_1 + 5) = 1;
      cVar3 = PeekPacketChecksumBool();
      if ((cVar3 != '\0') && (cVar3 = FUN_0043a530(), cVar3 == '\0')) {
        QueueOutgoingPacketField();
        iVar5 = g_clientContext;
        *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar5) = 0;
      }
    }
    cVar3 = FUN_00406710();
    if (cVar3 != '\0') {
      iVar8 = PeekChecksumStateUnderLock();
      iVar9 = PeekChecksumStateUnderLock();
      iVar5 = g_clientContext;
      piVar1 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar3 = PeekPacketChecksumBool();
      if ((cVar3 == '\0') && ((&DAT_006a7758)[iVar5] != '\0')) {
        if (((&DAT_006a7736)[iVar5] == '\x01') &&
           ((uVar7 = iVar8 - *(int *)(&DAT_006a7714 + iVar5) >> 0x1f,
            200 < (int)((iVar8 - *(int *)(&DAT_006a7714 + iVar5) ^ uVar7) - uVar7) ||
            (uVar7 = iVar9 - *(int *)(&DAT_006a7710 + iVar5) >> 0x1f,
            300 < (int)((iVar9 - *(int *)(&DAT_006a7710 + iVar5) ^ uVar7) - uVar7))))) {
          (&DAT_006a7736)[iVar5] = 0;
        }
        iVar10 = 400;
        if (399 < iVar9) {
          iVar10 = iVar9;
        }
        iVar12 = *(int *)(&DAT_006a7720 + iVar5) + -400;
        if ((iVar10 <= iVar12) && (iVar12 = iVar9, iVar9 < 400)) {
          iVar12 = 400;
        }
        iVar9 = -0x14;
        if (-0x15 < iVar8) {
          iVar9 = iVar8;
        }
        iVar10 = *(int *)(&DAT_006a7724 + iVar5) + -0x104;
        if ((iVar9 <= iVar10) && (iVar10 = -0x14, -0x15 < iVar8)) {
          iVar10 = iVar8;
        }
        iVar8 = *piVar1 - iVar12;
        *(int *)(&DAT_006a771c + iVar5) = iVar10;
        if (((*(int *)(&DAT_006a770c + iVar5) - iVar10) * (*(int *)(&DAT_006a770c + iVar5) - iVar10)
             + iVar8 * iVar8 < 40000) &&
           (((&DAT_006a7734)[iVar5] == '\x01' || ((&DAT_006a7f6c)[iVar5] == '\0')))) {
          *(int *)(&DAT_006a7710 + iVar5) = iVar12;
          *piVar1 = iVar12;
          *(int *)(&DAT_006a7714 + iVar5) = iVar10;
          *(int *)(&DAT_006a770c + iVar5) = iVar10;
        }
        if ((((&DAT_006a7734)[iVar5] == '\0') && ((&DAT_006a7f6c)[iVar5] == '\x01')) &&
           ((&DAT_006a7736)[iVar5] == '\0')) {
          iVar8 = *(int *)(&DAT_006a7730 + iVar5);
          iVar9 = iVar8;
          if (iVar12 <= iVar8) {
            iVar9 = iVar12;
          }
          iVar13 = *(int *)(&DAT_006a772c + iVar5);
          if ((iVar13 <= iVar9) && (iVar13 = iVar8, iVar12 <= iVar8)) {
            iVar13 = iVar12;
          }
          *(int *)(&DAT_006a7718 + iVar5) = iVar13;
        }
        if ((&DAT_006a7734)[iVar5] == '\x01') {
          *(int *)(&DAT_006a7718 + iVar5) = iVar12;
          *(int *)(&DAT_006a771c + iVar5) = iVar10;
        }
      }
    }
    goto LAB_00453f0d;
  }
  FUN_004262d0(param_1[2],param_1 + 0x45e);
  cVar3 = PeekPacketChecksumBool();
  if (cVar3 != '\0') {
    iVar8 = PeekChecksumStateUnderLock(param_1 + 0x3d5);
    if ((-1 < iVar8) && (iVar8 < *(int *)(&DAT_006a7720 + g_clientContext))) {
      pcVar14 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar8);
      iVar8 = 0;
      if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
        do {
          if (*pcVar14 != '\0') goto LAB_004535de;
          pcVar14 = pcVar14 + *(int *)(&DAT_006a7720 + g_clientContext);
          iVar8 = iVar8 + 1;
        } while (iVar8 < *(int *)(&DAT_006a7724 + g_clientContext));
      }
    }
    iVar8 = 10000;
LAB_004535de:
    piVar1 = param_1 + 0x3d5;
    iVar9 = iVar8;
    uVar6 = PeekChecksumStateUnderLock(piVar1);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,uVar6,iVar8);
    iVar8 = 1;
    if (0 < param_1[0xfe5]) {
      iVar8 = param_1[0xfe5];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    (*pcVar15)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar15)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puVar20 = (undefined *)PeekPacketChecksumState();
    (*pcVar15)(&DAT_005a9068);
    uVar7 = (uint)*(byte *)(param_1 + 0xf);
    iVar10 = iVar10 / iVar8;
    uVar16 = 0;
    uVar11 = PeekChecksumStateUnderLock(piVar1);
    FUN_0043af40(uVar11,iVar9,uVar16,iVar5,iVar10,uVar6,uVar7);
    uVar18 = 0;
    uVar17 = 2;
    uVar16 = 0xff;
    uVar6 = PeekChecksumStateUnderLock(param_1 + 0x5f9);
    uVar11 = 0;
    PeekChecksumStateUnderLock(piVar1);
    PeekPacketChecksumBool(uVar11,uVar6,uVar16,uVar17,uVar18);
    FUN_00431d90((char)param_1[0xf],7,0,uVar11,uVar6,uVar16,uVar17,uVar18);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  (*pcVar15)(&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar15)(&DAT_005a9068);
  FUN_004398e0(&DAT_006a7f70 + g_clientContext,param_1[2],uVar6,puVar20,param_1,0);
  (**(code **)(*param_1 + 0x20))();
  if (param_1[9] < 2) {
    *(undefined1 *)(param_1 + 5) = 1;
  }
  else {
    pcVar14 = s_ssflame6_00554fc0;
    uVar16 = 0x2071;
    uVar6 = PeekChecksumStateUnderLock(param_1 + 0x45e);
    uVar11 = PeekChecksumStateUnderLock(param_1 + 0x3d5);
    FUN_004373c0(uVar11,uVar6,uVar16,pcVar14);
    param_1[0xfeb] = 0;
  }
  cVar3 = PeekPacketChecksumBool();
  iVar5 = g_clientContext;
  if ((cVar3 != '\0') && (cVar3 = FUN_0043a530(), iVar5 = g_clientContext, cVar3 == '\0')) {
    uVar6 = PeekChecksumStateUnderLock(&DAT_007949c8);
    QueueOutgoingPacketField(uVar6);
    iVar5 = g_clientContext;
    *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
    *(undefined4 *)(&DAT_005f376c + iVar5) = 0;
  }
  uVar6 = CompareChecksumPair(iVar5 + 0x5b85c,param_1 + 0xe48);
  cVar3 = FUN_00406610(uVar6);
  if (cVar3 != '\0') {
    EncodeChecksumState(param_1 + 0xe48);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar15)(&DAT_005a9068);
  if ((cStack_ad9 == '\0') || (cVar3 = PacketChecksumGreaterThan(), cVar3 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    (*pcVar15)();
    if ((0 < iVar5) && (cVar3 = PacketChecksumLessThan(), cVar3 != '\0')) goto LAB_00453887;
  }
  else {
LAB_00453887:
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 == '\0') {
      SetGuardedBool();
    }
  }
  cVar3 = CompareChecksumPair();
  if (((cVar3 != '\0') && (cVar3 = CompareChecksumPair(), cVar3 != '\0')) ||
     ((cVar3 = FUN_0040b410(), cVar3 != '\0' &&
      ((cVar3 = FUN_0040b410(), cVar3 != '\0' && (5 < param_1[0xed1])))))) {
    SetGuardedBool();
  }
LAB_00453f0d:
  *unaff_FS_OFFSET = uStack_c;
  return;
}

