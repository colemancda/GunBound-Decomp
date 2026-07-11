/* FUN_00490820 - 0x00490820 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00490820(int *param_1)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  undefined4 uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  byte bVar14;
  code *pcVar15;
  undefined4 unaff_ESI;
  byte *pbVar16;
  undefined4 unaff_EDI;
  int *piVar17;
  undefined4 *unaff_FS_OFFSET;
  bool bVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  char cVar22;
  undefined4 uVar23;
  char cVar24;
  undefined4 *puStack_aec;
  int local_ae4;
  int *piStack_ae0;
  undefined4 *apuStack_adc [2];
  undefined4 uStack_ad4;
  undefined4 uStack_ad0;
  int *piStack_acc;
  int iStack_ac8;
  undefined1 auStack_ac4 [16];
  int iStack_ab4;
  int iStack_ab0;
  undefined1 auStack_8a4 [4];
  undefined1 auStack_8a0 [20];
  undefined4 uStack_88c;
  undefined1 auStack_680 [548];
  undefined1 auStack_45c [548];
  undefined1 auStack_238 [528];
  undefined4 uStack_28;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053f063;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  iVar6 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar6 + iVar5);
  pcVar15 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  iVar6 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar6 + iVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar4 = PeekPacketChecksumBool();
  if (cVar4 == '\0') {
    FUN_0040b180(param_1 + 0x10,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x5;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_ab0 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(apuStack_adc);
      pcVar15 = (code *)LeaveCriticalSection;
    }
    FUN_0040b180(param_1 + 0x99,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x6;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    (*pcVar15)(&DAT_005a9068);
    uStack_c = 0xffffffff;
    if (iStack_ab4 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&piStack_ae0);
      pcVar15 = (code *)LeaveCriticalSection;
    }
    cVar4 = FUN_00406610(param_1[0x3d2] != 0);
    if (cVar4 == '\0') {
      FUN_0040afb0(param_1 + 0x2bd);
      FUN_0040afb0(param_1 + 0x346);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar10 = PeekPacketChecksumState();
      (*pcVar15)(&DAT_005a9068);
      if ((int)((uVar10 ^ (int)uVar10 >> 0x1f) - ((int)uVar10 >> 0x1f)) < 200) {
        cVar4 = FUN_0040b330(param_1 + 0x122,0);
        if (cVar4 == '\0') {
          uVar8 = 200;
        }
        else {
          uVar8 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar8);
      }
      uVar8 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_680,4);
      uStack_c = 7;
      uVar8 = EncodeChecksumPairDiff(param_1[0x3d2] + 0x38,auStack_45c,uVar8);
      uStack_c = 8;
      bVar2 = false;
      bVar18 = false;
      cVar4 = FUN_0040b490(param_1 + 0x3d5,uVar8);
      if (cVar4 == '\0') {
        uVar8 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_8a4,4);
        uStack_c = 9;
        uVar8 = EncodeChecksumPairSum(param_1[0x3d2] + 0x38,&iStack_ac8,uVar8);
        uStack_c = 10;
        bVar2 = true;
        bVar18 = true;
        cVar4 = FUN_0040b490(uVar8,param_1 + 0x3d5);
        bVar3 = false;
        if (cVar4 != '\0') goto LAB_0049168f;
      }
      else {
LAB_0049168f:
        bVar3 = true;
      }
      uStack_c = 9;
      if (bVar18) {
        ScrubChecksumGuard();
      }
      uStack_c = 8;
      if (bVar2) {
        ScrubChecksumGuard();
      }
      uStack_c = 7;
      ScrubChecksumGuard();
      uStack_c = 0xffffffff;
      ScrubChecksumGuard();
      if (bVar3) {
        iVar5 = param_1[0x3d4];
        param_1[0x3d4] = iVar5 + 1;
        if (iVar5 + 1 < 3) {
          uVar8 = FUN_0040a500(param_1 + 0x122,auStack_238);
          uStack_c = 0xb;
          EncodeChecksumState(uVar8);
          uStack_c = 0xffffffff;
          ScrubChecksumGuard();
        }
        else {
          FUN_00406500(0);
        }
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    piStack_ae0 = param_1 + 0x3d5;
    PeekPacketChecksumState();
    cVar4 = '\0';
    (*pcVar15)();
    if (cVar4 == '\0') {
      iVar5 = *(int *)(&DAT_006a7720 + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      cVar4 = iVar5 <= iVar6;
      (*pcVar15)(&DAT_005a9068);
      if (((cVar4 != '\0') ||
          (cVar4 = FUN_0040b300(unaff_ESI,*(undefined4 *)(&DAT_006a7724 + g_clientContext)),
          cVar4 != '\0')) || (cVar4 = FUN_0040b330(unaff_ESI,0xfffffc18), cVar4 != '\0'))
      goto LAB_0049184a;
    }
    else {
LAB_0049184a:
      *(undefined1 *)(param_1 + 5) = 1;
      cVar4 = PeekPacketChecksumBool();
      if ((cVar4 != '\0') && (cVar4 = FUN_0043a530(), cVar4 == '\0')) {
        iVar5 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
        if ((iVar5 == 5) || (uVar8 = 2, iVar5 == 6)) {
          uVar8 = 0x19;
        }
        QueueOutgoingPacketField(uVar8);
        iVar5 = g_clientContext;
        *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar5) = 0;
      }
    }
    cVar4 = FUN_00406710();
    if (cVar4 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      (*pcVar15)(&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar9 = PeekPacketChecksumState();
      (*pcVar15)(&DAT_005a9068);
      iVar5 = g_clientContext;
      piVar17 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar4 = PeekPacketChecksumBool();
      if ((cVar4 == '\0') && ((&DAT_006a7758)[iVar5] != '\0')) {
        if (((&DAT_006a7736)[iVar5] == '\x01') &&
           ((uVar10 = iVar6 - *(int *)(&DAT_006a7714 + iVar5) >> 0x1f,
            200 < (int)((iVar6 - *(int *)(&DAT_006a7714 + iVar5) ^ uVar10) - uVar10) ||
            (uVar10 = iVar9 - *(int *)(&DAT_006a7710 + iVar5) >> 0x1f,
            300 < (int)((iVar9 - *(int *)(&DAT_006a7710 + iVar5) ^ uVar10) - uVar10))))) {
          (&DAT_006a7736)[iVar5] = 0;
        }
        iVar12 = 400;
        if (399 < iVar9) {
          iVar12 = iVar9;
        }
        iVar11 = *(int *)(&DAT_006a7720 + iVar5) + -400;
        if ((iVar12 <= iVar11) && (iVar11 = iVar9, iVar9 < 400)) {
          iVar11 = 400;
        }
        iVar9 = -0x14;
        if (-0x15 < iVar6) {
          iVar9 = iVar6;
        }
        iVar12 = *(int *)(&DAT_006a7724 + iVar5) + -0x104;
        if ((iVar9 <= iVar12) && (iVar12 = -0x14, -0x15 < iVar6)) {
          iVar12 = iVar6;
        }
        iVar6 = *piVar17 - iVar11;
        *(int *)(&DAT_006a771c + iVar5) = iVar12;
        if (((*(int *)(&DAT_006a770c + iVar5) - iVar12) * (*(int *)(&DAT_006a770c + iVar5) - iVar12)
             + iVar6 * iVar6 < 40000) &&
           (((&DAT_006a7734)[iVar5] == '\x01' || ((&DAT_006a7f6c)[iVar5] == '\0')))) {
          *(int *)(&DAT_006a7710 + iVar5) = iVar11;
          *piVar17 = iVar11;
          *(int *)(&DAT_006a7714 + iVar5) = iVar12;
          *(int *)(&DAT_006a770c + iVar5) = iVar12;
        }
        if ((((&DAT_006a7734)[iVar5] == '\0') && ((&DAT_006a7f6c)[iVar5] == '\x01')) &&
           ((&DAT_006a7736)[iVar5] == '\0')) {
          iVar6 = *(int *)(&DAT_006a7730 + iVar5);
          iVar9 = iVar6;
          if (iVar11 <= iVar6) {
            iVar9 = iVar11;
          }
          iVar13 = *(int *)(&DAT_006a772c + iVar5);
          if ((iVar13 <= iVar9) && (iVar13 = iVar6, iVar11 <= iVar6)) {
            iVar13 = iVar11;
          }
          *(int *)(&DAT_006a7718 + iVar5) = iVar13;
        }
        if ((&DAT_006a7734)[iVar5] == '\x01') {
          *(int *)(&DAT_006a7718 + iVar5) = iVar11;
          *(int *)(&DAT_006a771c + iVar5) = iVar12;
        }
      }
    }
    goto LAB_00491a21;
  }
  FUN_004262d0(param_1[2],param_1 + 0x45e);
  cVar4 = PeekPacketChecksumBool();
  if (cVar4 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((-1 < iVar5) && (iVar5 < *(int *)(&DAT_006a7720 + g_clientContext))) {
      pcVar7 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar5);
      puStack_aec = (undefined4 *)0x0;
      if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
        do {
          if (*pcVar7 != '\0') goto LAB_0049096a;
          pcVar7 = pcVar7 + *(int *)(&DAT_006a7720 + g_clientContext);
          puStack_aec = (undefined4 *)((int)puStack_aec + 1);
        } while ((int)puStack_aec < *(int *)(&DAT_006a7724 + g_clientContext));
      }
    }
    puStack_aec = (undefined4 *)0x2710;
LAB_0049096a:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,uVar8,puStack_aec);
    local_ae4 = 1;
    if (0 < param_1[0xfe5]) {
      local_ae4 = param_1[0xfe5];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    piStack_ae0 = (int *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_ad4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_ad0 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0043af40(uStack_ad0,puStack_aec,0,uStack_ad4,(int)piStack_ae0 / local_ae4,uVar8,
                 (char)param_1[0xf]);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    piStack_ae0 = (int *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar23 = 0;
    uVar21 = 2;
    uVar20 = 0xff;
    uVar19 = 0;
    PeekPacketChecksumBool(0,uVar8,0xff,2,0);
    FUN_00431d90((char)param_1[0xf],7,0,uVar19,uVar8,uVar20,uVar21,uVar23);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar19 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = g_clientContext;
  iStack_ac8 = param_1[2];
  uStack_ad4 = uVar8;
  uStack_ad0 = uVar19;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar6 == 4) {
    puStack_aec = operator_new(0x3fbc);
    puStack_8 = (undefined1 *)0x0;
    apuStack_adc[0] = puStack_aec;
    if (puStack_aec == (undefined4 *)0x0) {
      puStack_aec = (undefined4 *)0x0;
    }
    else {
      FUN_00454dc0(puStack_aec,0x186a9);
      *puStack_aec = &PTR_FUN_0055658c;
      puStack_aec[0xfe7] = 0xffffffff;
    }
    puStack_8 = (undefined1 *)0xffffffff;
    iVar6 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar10 = *(uint *)(iVar6 + 4);
    while (uVar10 < 0x186ab) {
      if (uVar10 == 0x186aa) {
        piVar17 = *(int **)(iVar6 + 0x10);
        bVar18 = true;
        piStack_acc = piVar17;
        if (piVar17[2] == 0) goto LAB_00490be5;
        break;
      }
      iVar6 = *(int *)(iVar6 + 0x1c);
      uVar10 = *(uint *)(iVar6 + 4);
    }
  }
  goto LAB_00490f39;
  while( true ) {
    piVar17 = (int *)piVar17[4];
    bVar18 = piVar17[2] == 0;
    piStack_acc = piVar17;
    if (!bVar18) break;
LAB_00490be5:
    if (bVar18) {
      apuStack_adc[0] = (undefined4 *)piVar17[0xf];
      piStack_ae0 = (int *)piVar17[0xe];
      piStack_acc = piVar17;
      iVar6 = FUN_004f1f10();
      iVar9 = FloatToInt64();
      piStack_ae0 = (int *)((int)piStack_ae0 - iVar9);
      iVar9 = FloatToInt64();
      iVar9 = (int)apuStack_adc[0] - iVar9;
      (**(code **)(*piVar17 + 4))(&DAT_00553b90);
      piVar17[0x11] = iVar6;
      apuStack_adc[0] = (undefined4 *)(&DAT_006a7f74 + iVar5);
      cVar4 = PeekPacketChecksumBool();
      if (cVar4 == '\0') {
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
        uVar8 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = param_1[0xfe5];
        uVar23 = 0;
        uVar21 = 0xff;
        uVar20 = 100;
        uVar19 = 0;
        PeekPacketChecksumBool(uVar8,0,100,0xff,iVar5,0);
        FUN_00432320((char)param_1[0xf],1,1,uVar8,uVar19,uVar20,uVar21,iVar5,uVar23);
        puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),3);
        ScrubChecksumGuard();
LAB_00490ea2:
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        cVar4 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&uStack_ad0,&uStack_ad4,2,1,1);
        if (cVar4 != '\0') {
          auStack_8a4[0] = 0;
          iStack_ab0 = 0;
          EncodeOutgoingPacketField(0);
          puStack_8 = (undefined1 *)0x1;
          auStack_680[0] = 0;
          uStack_88c = 0;
          EncodeOutgoingPacketField(0);
          SUBFIELD(puStack_8,0,undefined1) = 2;
          QueueOutgoingPacketField(uStack_ad0);
          QueueOutgoingPacketField(uStack_ad4);
          FUN_004262d0(iStack_ac8 + 0x10,auStack_8a0);
          iVar5 = param_1[0xfe5];
          uVar23 = 0;
          uVar21 = 0xff;
          uVar20 = 100;
          uVar19 = 0;
          PeekChecksumStateUnderLock(auStack_8a0);
          uVar8 = PeekChecksumStateUnderLock(auStack_ac4);
          PeekPacketChecksumBool(uVar8,uVar19,uVar20,uVar21,iVar5,uVar23);
          FUN_00432320((char)param_1[0xf],1,1,uVar8,uVar19,uVar20,uVar21,iVar5,uVar23);
          puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
          ScrubChecksumGuard();
          goto LAB_00490ea2;
        }
      }
      puStack_aec[0xfea] = piStack_ae0;
      puStack_aec[0xfeb] = iVar9;
      puStack_aec[0xfec] = uStack_ad0;
      puStack_aec[0xfed] = uStack_ad4;
      puStack_aec[0xfee] = iVar6;
      uVar8 = FUN_004ac4d0();
      puStack_aec[0xfe9] = uVar8;
      iVar5 = FUN_004ac400();
      puStack_aec[0xfe8] = iVar5 * param_1[0xfe5];
      cVar4 = PeekPacketChecksumBool();
      if (cVar4 == '\0') {
        RegisterActiveObject();
      }
      else {
        (**(code **)*puStack_aec)(1);
      }
      break;
    }
  }
LAB_00490f39:
  *(undefined1 *)(param_1 + 5) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  pcVar15 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_adc[0] = (undefined4 *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004373c0(apuStack_adc[0],uVar8,0x2074,s_ssflame9_00554ce4);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar19 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00436ac0(uVar19,uVar8);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_adc[0] = (undefined4 *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004372f0(param_1[2],apuStack_adc[0],uVar8,param_1[0xe25],param_1 + 0xe26);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar19 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_adc[0] = (undefined4 *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00437150(apuStack_adc[0],uVar19,0x3c,uVar8);
  iVar5 = g_clientContext;
  cVar4 = PeekPacketChecksumBool();
  if (cVar4 != '\x01') {
    iVar6 = *(int *)(&DAT_006a7750 + iVar5);
    if (iVar6 < 0x10) {
      iVar6 = 0xf;
    }
    *(int *)(&DAT_006a7750 + iVar5) = iVar6;
    iVar6 = *(int *)(&DAT_006a7754 + iVar5);
    if (iVar6 < 0xb) {
      iVar6 = 10;
    }
    *(int *)(&DAT_006a7754 + iVar5) = iVar6;
  }
  cVar4 = PeekPacketChecksumBool();
  if (cVar4 == '\0') {
    FUN_004ee9b0(0);
    pcVar15 = (code *)LeaveCriticalSection;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  cVar24 = '\0';
  (*pcVar15)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  cVar22 = '\0';
  (*pcVar15)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar15)(&DAT_005a9068);
  uVar19 = PeekPacketChecksumBool();
  FUN_00437d90(&DAT_006a7f70 + g_clientContext,unaff_ESI,uVar8,(char)param_1[0xf],uVar19);
  cVar4 = PeekPacketChecksumBool();
  if ((cVar4 != '\0') && (cVar4 = FUN_0043a530(), cVar4 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x1e);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = g_clientContext;
    pcVar15 = (code *)LeaveCriticalSection;
    *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
    *(undefined4 *)(&DAT_005f376c + iVar5) = 0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  PeekPacketChecksumState();
  (*pcVar15)(&DAT_005a9068);
  cVar4 = FUN_00406610(unaff_EDI);
  if (cVar4 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    pcVar15 = (code *)LeaveCriticalSection;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar15)(&DAT_005a9068);
  if (cVar24 == '\0') {
LAB_004912e1:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    (*pcVar15)(&DAT_005a9068);
    if (0 < iVar5) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      (*pcVar15)(&DAT_005a9068);
      if (iVar5 < 0) goto LAB_00491321;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    cVar4 = 0 < iVar5;
    (*pcVar15)(&DAT_005a9068);
    if (cVar4 == '\0') goto LAB_004912e1;
LAB_00491321:
    cVar4 = PeekPacketChecksumBool();
    if (cVar4 == '\0') {
      FUN_00406500(1);
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  PeekPacketChecksumState();
  (*pcVar15)(&DAT_005a9068);
  if ((cVar22 == '\0') || (cVar4 = FUN_0040b490(param_1 + 0xed2,param_1 + 0xf5b), cVar4 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    iVar6 = PeekPacketChecksumState();
    cVar4 = iVar6 < iVar5;
    (*pcVar15)(&DAT_005a9068);
    if ((cVar4 == '\0') ||
       ((cVar4 = FUN_0040b410(param_1 + 0xed2,param_1 + 0xf5b), cVar4 == '\0' ||
        (param_1[0xed1] < 6)))) goto LAB_00491a21;
  }
  iVar5 = g_clientContext;
  pbVar16 = (byte *)(g_clientContext + 0x62143);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *pbVar16 = (byte)iVar6;
  iVar6 = _rand();
  bVar1 = *pbVar16;
  *(byte *)(iVar5 + 0x62144) = (byte)iVar6;
  bVar14 = '\x01' << (bVar1 & 7);
  bVar14 = ~bVar14 & (byte)iVar6 | bVar14;
  *(byte *)(iVar5 + 0x62144) = bVar14;
  *(byte *)(iVar5 + 0x62145) = bVar1 + bVar14 + -0x34;
  (*pcVar15)(&DAT_005a9068);
LAB_00491a21:
  *unaff_FS_OFFSET = uStack_28;
  return;
}

