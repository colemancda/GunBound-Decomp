/* FUN_0048e1d0 - 0x0048e1d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0048e1d0(int *param_1)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  byte bVar12;
  uint unaff_EBX;
  code *pcVar13;
  byte *pbVar14;
  int *piVar15;
  undefined4 *unaff_FS_OFFSET;
  bool bVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  undefined4 *puStack_af0;
  int local_ae4;
  undefined4 uStack_adc;
  undefined4 uStack_ad8;
  int *piStack_ad4;
  undefined4 *apuStack_ad0 [2];
  int iStack_ac8;
  undefined1 auStack_ac4 [16];
  int iStack_ab4;
  int iStack_ab0;
  undefined1 auStack_8a4 [4];
  undefined1 auStack_8a0 [20];
  undefined4 uStack_88c;
  undefined1 auStack_680 [548];
  undefined1 auStack_45c [548];
  undefined1 auStack_238 [552];
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053e1c3;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  iVar4 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar4 + iVar3);
  pcVar13 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  iVar4 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar4 + iVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 == '\0') {
    EncodeChecksumDeltaShr(param_1 + 0x10,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x5;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_ab0 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(apuStack_ad0);
      pcVar13 = (code *)LeaveCriticalSection;
    }
    EncodeChecksumDeltaShr(param_1 + 0x99,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x6;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar6);
    (*pcVar13)(&DAT_005a9068);
    uStack_c = 0xffffffff;
    if (iStack_ab4 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&piStack_ad4);
      pcVar13 = (code *)LeaveCriticalSection;
    }
    cVar2 = FUN_00406610(param_1[0x3d2] != 0);
    if (cVar2 == '\0') {
      EmitChecksumSum(param_1 + 0x2bd);
      EmitChecksumSum(param_1 + 0x346);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar10 = PeekPacketChecksumState();
      (*pcVar13)(&DAT_005a9068);
      if ((int)((uVar10 ^ (int)uVar10 >> 0x1f) - ((int)uVar10 >> 0x1f)) < 200) {
        cVar2 = PacketChecksumLessThan(param_1 + 0x122,0);
        if (cVar2 == '\0') {
          uVar6 = 200;
        }
        else {
          uVar6 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar6);
      }
      uVar6 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_680,4);
      uStack_c = 7;
      uVar6 = EncodeChecksumPairDiff(param_1[0x3d2] + 0x38,auStack_45c,uVar6);
      uStack_c = 8;
      unaff_EBX = 3;
      cVar2 = CompareChecksumPair(param_1 + 0x3d5,uVar6);
      if (cVar2 == '\0') {
        uVar6 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_8a4,4);
        uStack_c = 9;
        uVar6 = EncodeChecksumPairSum(param_1[0x3d2] + 0x38,&iStack_ac8,uVar6);
        uStack_c = 10;
        unaff_EBX = 0xf;
        cVar2 = CompareChecksumPair(uVar6,param_1 + 0x3d5);
        bVar16 = false;
        if (cVar2 != '\0') goto LAB_0048ee14;
      }
      else {
LAB_0048ee14:
        bVar16 = true;
      }
      uStack_c = 9;
      if ((unaff_EBX & 8) != 0) {
        unaff_EBX = unaff_EBX & 0xfffffff7;
        ScrubChecksumGuard();
      }
      uStack_c = 8;
      if ((unaff_EBX & 4) != 0) {
        unaff_EBX = unaff_EBX & 0xfffffffb;
        ScrubChecksumGuard();
      }
      uStack_c = 7;
      if ((unaff_EBX & 2) != 0) {
        unaff_EBX = unaff_EBX & 0xfffffffd;
        ScrubChecksumGuard();
      }
      uStack_c = 0xffffffff;
      if ((unaff_EBX & 1) != 0) {
        ScrubChecksumGuard();
      }
      if (bVar16) {
        iVar3 = param_1[0x3d4];
        param_1[0x3d4] = iVar3 + 1;
        if (iVar3 + 1 < 3) {
          uVar6 = FUN_0040a500(param_1 + 0x122,auStack_238);
          uStack_c = 0xb;
          EncodeChecksumState(uVar6);
          uStack_c = 0xffffffff;
          ScrubChecksumGuard();
        }
        else {
          SetGuardedBool(0);
        }
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    piStack_ad4 = param_1 + 0x3d5;
    PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    if ((char)(unaff_EBX >> 0x18) == '\0') {
      iVar3 = *(int *)(&DAT_006a7720 + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState();
      (*pcVar13)(&DAT_005a9068);
      if (((iVar3 <= iVar4) ||
          (cVar2 = PacketChecksumGreaterEqual(param_1 + 0x45e,*(undefined4 *)(&DAT_006a7724 + g_clientContext)),
          cVar2 != '\0')) || (cVar2 = PacketChecksumLessThan(param_1 + 0x45e,0xfffffc18), cVar2 != '\0'))
      goto LAB_0048efcf;
    }
    else {
LAB_0048efcf:
      *(undefined1 *)(param_1 + 5) = 1;
      cVar2 = PeekPacketChecksumBool();
      if ((cVar2 != '\0') && (cVar2 = FUN_0043a530(), cVar2 == '\0')) {
        iVar3 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
        if ((iVar3 == 5) || (uVar6 = 2, iVar3 == 6)) {
          uVar6 = 0x19;
        }
        QueueOutgoingPacketField(uVar6);
        iVar3 = g_clientContext;
        *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar3) = 0;
      }
    }
    cVar2 = FUN_00406710();
    if (cVar2 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState();
      (*pcVar13)(&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = PeekPacketChecksumState();
      (*pcVar13)(&DAT_005a9068);
      iVar3 = g_clientContext;
      piVar15 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar2 = PeekPacketChecksumBool();
      if ((cVar2 == '\0') && ((&DAT_006a7758)[iVar3] != '\0')) {
        if (((&DAT_006a7736)[iVar3] == '\x01') &&
           ((uVar10 = iVar4 - *(int *)(&DAT_006a7714 + iVar3) >> 0x1f,
            200 < (int)((iVar4 - *(int *)(&DAT_006a7714 + iVar3) ^ uVar10) - uVar10) ||
            (uVar10 = iVar7 - *(int *)(&DAT_006a7710 + iVar3) >> 0x1f,
            300 < (int)((iVar7 - *(int *)(&DAT_006a7710 + iVar3) ^ uVar10) - uVar10))))) {
          (&DAT_006a7736)[iVar3] = 0;
        }
        iVar8 = 400;
        if (399 < iVar7) {
          iVar8 = iVar7;
        }
        iVar9 = *(int *)(&DAT_006a7720 + iVar3) + -400;
        if ((iVar8 <= iVar9) && (iVar9 = iVar7, iVar7 < 400)) {
          iVar9 = 400;
        }
        iVar7 = -0x14;
        if (-0x15 < iVar4) {
          iVar7 = iVar4;
        }
        iVar8 = *(int *)(&DAT_006a7724 + iVar3) + -0x104;
        if ((iVar7 <= iVar8) && (iVar8 = -0x14, -0x15 < iVar4)) {
          iVar8 = iVar4;
        }
        iVar4 = *piVar15 - iVar9;
        *(int *)(&DAT_006a771c + iVar3) = iVar8;
        if (((*(int *)(&DAT_006a770c + iVar3) - iVar8) * (*(int *)(&DAT_006a770c + iVar3) - iVar8) +
             iVar4 * iVar4 < 40000) &&
           (((&DAT_006a7734)[iVar3] == '\x01' || ((&DAT_006a7f6c)[iVar3] == '\0')))) {
          *(int *)(&DAT_006a7710 + iVar3) = iVar9;
          *piVar15 = iVar9;
          *(int *)(&DAT_006a7714 + iVar3) = iVar8;
          *(int *)(&DAT_006a770c + iVar3) = iVar8;
        }
        if ((((&DAT_006a7734)[iVar3] == '\0') && ((&DAT_006a7f6c)[iVar3] == '\x01')) &&
           ((&DAT_006a7736)[iVar3] == '\0')) {
          iVar4 = *(int *)(&DAT_006a7730 + iVar3);
          iVar7 = iVar4;
          if (iVar9 <= iVar4) {
            iVar7 = iVar9;
          }
          iVar11 = *(int *)(&DAT_006a772c + iVar3);
          if ((iVar11 <= iVar7) && (iVar11 = iVar4, iVar9 <= iVar4)) {
            iVar11 = iVar9;
          }
          *(int *)(&DAT_006a7718 + iVar3) = iVar11;
        }
        if ((&DAT_006a7734)[iVar3] == '\x01') {
          *(int *)(&DAT_006a7718 + iVar3) = iVar9;
          *(int *)(&DAT_006a771c + iVar3) = iVar8;
        }
      }
    }
    goto LAB_0048f1a6;
  }
  FUN_004262d0(param_1[2],param_1 + 0x45e);
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((-1 < iVar3) && (iVar3 < *(int *)(&DAT_006a7720 + g_clientContext))) {
      pcVar5 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar3);
      puStack_af0 = (undefined4 *)0x0;
      if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
        do {
          if (*pcVar5 != '\0') goto LAB_0048e31a;
          pcVar5 = pcVar5 + *(int *)(&DAT_006a7720 + g_clientContext);
          puStack_af0 = (undefined4 *)((int)puStack_af0 + 1);
        } while ((int)puStack_af0 < *(int *)(&DAT_006a7724 + g_clientContext));
      }
    }
    puStack_af0 = (undefined4 *)0x2710;
LAB_0048e31a:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,uVar6,puStack_af0);
    local_ae4 = 1;
    if (0 < param_1[0xfe5]) {
      local_ae4 = param_1[0xfe5];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_adc = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_ad8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0043af40(uStack_ad8,puStack_af0,0,uStack_adc,iVar3 / local_ae4,uVar6,(char)param_1[0xf]);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar20 = 0;
    uVar19 = 2;
    uVar18 = 0xff;
    uVar17 = 0;
    PeekPacketChecksumBool(0,uVar6,0xff,2,0);
    FUN_00431d90((char)param_1[0xf],7,0,uVar17,uVar6,uVar18,uVar19,uVar20);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar17 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = g_clientContext;
  iStack_ac8 = param_1[2];
  uStack_adc = uVar6;
  uStack_ad8 = uVar17;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 == 4) {
    puStack_af0 = operator_new(0x3fbc);
    puStack_8 = (undefined1 *)0x0;
    apuStack_ad0[0] = puStack_af0;
    if (puStack_af0 == (undefined4 *)0x0) {
      puStack_af0 = (undefined4 *)0x0;
    }
    else {
      FUN_00454dc0(puStack_af0,0x186a9);
      *puStack_af0 = &PTR_FUN_0055658c;
      puStack_af0[0xfe7] = 0xffffffff;
    }
    puStack_8 = (undefined1 *)0xffffffff;
    iVar4 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar10 = *(uint *)(iVar4 + 4);
    while (uVar10 < 0x186ab) {
      if (uVar10 == 0x186aa) {
        piVar15 = *(int **)(iVar4 + 0x10);
        bVar16 = true;
        piStack_ad4 = piVar15;
        if (piVar15[2] == 0) goto LAB_0048e595;
        break;
      }
      iVar4 = *(int *)(iVar4 + 0x1c);
      uVar10 = *(uint *)(iVar4 + 4);
    }
  }
  goto LAB_0048e8fe;
  while( true ) {
    piVar15 = (int *)piVar15[4];
    bVar16 = piVar15[2] == 0;
    piStack_ad4 = piVar15;
    if (!bVar16) break;
LAB_0048e595:
    if (bVar16) {
      apuStack_ad0[0] = (undefined4 *)piVar15[0xf];
      iVar4 = piVar15[0xe];
      piStack_ad4 = piVar15;
      iVar7 = FUN_004f1f10();
      iVar8 = FloatToInt64();
      iVar9 = FloatToInt64();
      iVar9 = (int)apuStack_ad0[0] - iVar9;
      (**(code **)(*piVar15 + 4))(&DAT_00553b90);
      piVar15[0x11] = iVar7;
      apuStack_ad0[0] = (undefined4 *)(&DAT_006a7f74 + iVar3);
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        auStack_680[0] = 0;
        uStack_88c = 0;
        EncodeOutgoingPacketField(0);
        puStack_8 = (undefined1 *)0x3;
        auStack_8a4[0] = 0;
        iStack_ab0 = 0;
        EncodeOutgoingPacketField(0);
        SUBFIELD(puStack_8,0,undefined1) = 4;
        FUN_004262d0(iStack_ac8 + 0x10,auStack_ac4);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar3 = param_1[0xfe5];
        uVar20 = 0;
        uVar19 = 0xff;
        uVar18 = 100;
        uVar17 = 0;
        PeekPacketChecksumBool(uVar6,0,100,0xff,iVar3,0);
        FUN_00432320((char)param_1[0xf],1,1,uVar6,uVar17,uVar18,uVar19,iVar3,uVar20);
        puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),3);
        ScrubChecksumGuard();
LAB_0048e85d:
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        cVar2 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&uStack_ad8,&uStack_adc,2,1,1);
        if (cVar2 != '\0') {
          auStack_8a4[0] = 0;
          iStack_ab0 = 0;
          EncodeOutgoingPacketField(0);
          puStack_8 = (undefined1 *)0x1;
          auStack_680[0] = 0;
          uStack_88c = 0;
          EncodeOutgoingPacketField(0);
          SUBFIELD(puStack_8,0,undefined1) = 2;
          QueueOutgoingPacketField(uStack_ad8);
          QueueOutgoingPacketField(uStack_adc);
          FUN_004262d0(iStack_ac8 + 0x10,auStack_8a0);
          iVar3 = param_1[0xfe5];
          uVar20 = 0;
          uVar19 = 0xff;
          uVar18 = 100;
          uVar17 = 0;
          PeekChecksumStateUnderLock(auStack_8a0);
          uVar6 = PeekChecksumStateUnderLock(auStack_ac4);
          PeekPacketChecksumBool(uVar6,uVar17,uVar18,uVar19,iVar3,uVar20);
          FUN_00432320((char)param_1[0xf],1,1,uVar6,uVar17,uVar18,uVar19,iVar3,uVar20);
          puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
          ScrubChecksumGuard();
          goto LAB_0048e85d;
        }
      }
      puStack_af0[0xfea] = iVar4 - iVar8;
      puStack_af0[0xfeb] = iVar9;
      puStack_af0[0xfec] = uStack_ad8;
      puStack_af0[0xfed] = uStack_adc;
      puStack_af0[0xfee] = iVar7;
      uVar6 = FUN_004ac4d0();
      puStack_af0[0xfe9] = uVar6;
      iVar3 = FUN_004ac400();
      puStack_af0[0xfe8] = iVar3 * param_1[0xfe5];
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        RegisterActiveObject();
      }
      else {
        (**(code **)*puStack_af0)(1);
      }
      break;
    }
  }
LAB_0048e8fe:
  *(undefined1 *)(param_1 + 5) = 1;
  (**(code **)(*param_1 + 0x20))();
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 == '\0') {
    AcquireSoundChannel(0);
  }
  cVar2 = PeekPacketChecksumBool();
  if ((cVar2 != '\0') && (cVar2 = FUN_0043a530(), cVar2 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    QueueOutgoingPacketField(uVar6);
    iVar3 = g_clientContext;
    *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
    *(undefined4 *)(&DAT_005f376c + iVar3) = 0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar2 = FUN_00406610(iVar3 < iVar4);
  if (cVar2 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 < 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar3 < 1) goto LAB_0048ea5a;
LAB_0048eaa6:
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 == '\0') {
      SetGuardedBool(1);
    }
  }
  else {
LAB_0048ea5a:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar3) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar3 < 0) goto LAB_0048eaa6;
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar4 <= iVar3) || (cVar2 = CompareChecksumPair(param_1 + 0xed2,param_1 + 0xf5b), cVar2 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar3 <= iVar4) ||
       ((cVar2 = FUN_0040b410(param_1 + 0xed2,param_1 + 0xf5b), cVar2 == '\0' ||
        (param_1[0xed1] < 6)))) goto LAB_0048f1a6;
  }
  iVar3 = g_clientContext;
  pbVar14 = (byte *)(g_clientContext + 0x62143);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = _rand();
  *pbVar14 = (byte)iVar4;
  iVar4 = _rand();
  bVar1 = *pbVar14;
  *(byte *)(iVar3 + 0x62144) = (byte)iVar4;
  bVar12 = '\x01' << (bVar1 & 7);
  bVar1 = *pbVar14;
  bVar12 = ~bVar12 & (byte)iVar4 | bVar12;
  *(byte *)(iVar3 + 0x62144) = bVar12;
  *(byte *)(iVar3 + 0x62145) = bVar12 + bVar1 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
LAB_0048f1a6:
  *unaff_FS_OFFSET = uStack_10;
  return;
}

