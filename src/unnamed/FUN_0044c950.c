/* FUN_0044c950 - 0x0044c950 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0044c950(int *param_1)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  uint unaff_EBX;
  code *pcVar13;
  undefined4 unaff_EBP;
  uint unaff_ESI;
  undefined4 unaff_EDI;
  int *piVar14;
  undefined4 *unaff_FS_OFFSET;
  bool bVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  char cVar20;
  int local_ae8;
  undefined4 *puStack_ae4;
  int *piStack_ae0;
  undefined4 *apuStack_adc [2];
  undefined4 uStack_ad4;
  undefined4 uStack_ad0;
  int *piStack_acc;
  int iStack_ac8;
  undefined1 auStack_ac4 [16];
  uint uStack_ab4;
  int iStack_ab0;
  undefined1 auStack_8a4 [4];
  undefined1 auStack_8a0 [20];
  undefined4 uStack_88c;
  undefined1 auStack_680 [548];
  undefined1 auStack_45c [548];
  undefined1 auStack_238 [536];
  undefined4 uStack_20;
  undefined4 uStack_18;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_00540762;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  iVar5 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar5 + iVar4);
  pcVar13 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  iVar5 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar5 + iVar4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar20 = '\0';
  (**(code **)(*param_1 + 0x14))();
  cVar3 = PeekPacketChecksumBool();
  if (cVar3 == '\0') {
    FUN_0040b180(param_1 + 0x10,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x8;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar7);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_ab0 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(apuStack_adc);
      pcVar13 = (code *)LeaveCriticalSection;
    }
    FUN_0040b180(param_1 + 0x99,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x9;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar7);
    (*pcVar13)(&DAT_005a9068);
    uStack_c = 0xffffffff;
    if (uStack_ab4 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&piStack_ae0);
      pcVar13 = (code *)LeaveCriticalSection;
      unaff_EBX = uStack_ab4;
    }
    cVar3 = FUN_00406610(param_1[0x3d2] != 0);
    if (cVar3 == '\0') {
      FUN_0040afb0(param_1 + 0x2bd);
      FUN_0040afb0(param_1 + 0x346);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      unaff_EBX = PeekPacketChecksumState();
      (*pcVar13)(&DAT_005a9068);
      if ((int)((unaff_EBX ^ (int)unaff_EBX >> 0x1f) - ((int)unaff_EBX >> 0x1f)) < 200) {
        cVar3 = FUN_0040b330(param_1 + 0x122,0);
        if (cVar3 == '\0') {
          uVar7 = 200;
        }
        else {
          uVar7 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar7);
      }
      uVar7 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_680,4);
      uStack_c = 10;
      uVar7 = EncodeChecksumPairDiff(param_1[0x3d2] + 0x38,auStack_45c,uVar7);
      uStack_c = 0xb;
      bVar1 = false;
      bVar15 = false;
      cVar3 = FUN_0040b490(param_1 + 0x3d5,uVar7);
      if (cVar3 == '\0') {
        uVar7 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_8a4,4);
        uStack_c = 0xc;
        uVar7 = EncodeChecksumPairSum(param_1[0x3d2] + 0x38,&iStack_ac8,uVar7);
        uStack_c = 0xd;
        bVar1 = true;
        bVar15 = true;
        cVar3 = FUN_0040b490(uVar7,param_1 + 0x3d5);
        bVar2 = false;
        if (cVar3 != '\0') goto LAB_0044d5d2;
      }
      else {
LAB_0044d5d2:
        bVar2 = true;
      }
      uStack_c = 0xc;
      if (bVar15) {
        ScrubChecksumGuard();
      }
      uStack_c = 0xb;
      if (bVar1) {
        ScrubChecksumGuard();
      }
      uStack_c = 10;
      ScrubChecksumGuard();
      uStack_c = 0xffffffff;
      ScrubChecksumGuard();
      if (bVar2) {
        iVar4 = param_1[0x3d4];
        param_1[0x3d4] = iVar4 + 1;
        if (iVar4 + 1 < 3) {
          uVar7 = FUN_0040a500(param_1 + 0x122,auStack_238);
          uStack_c = 0xe;
          EncodeChecksumState(uVar7);
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
    (*pcVar13)(&DAT_005a9068);
    if (cVar20 == '\0') {
      iVar4 = *(int *)(&DAT_006a7720 + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      cVar3 = iVar4 <= iVar5;
      (*pcVar13)(&DAT_005a9068);
      if (((cVar3 != '\0') ||
          (cVar3 = FUN_0040b300(unaff_EBX,*(undefined4 *)(&DAT_006a7724 + g_clientContext)),
          cVar3 != '\0')) || (cVar3 = FUN_0040b330(unaff_EBX,0xfffffc18), cVar3 != '\0'))
      goto LAB_0044d78e;
    }
    else {
LAB_0044d78e:
      *(undefined1 *)(param_1 + 5) = 1;
      cVar3 = PeekPacketChecksumBool();
      if ((cVar3 != '\0') && (cVar3 = FUN_0043a530(), cVar3 == '\0')) {
        iVar4 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
        if ((iVar4 == 5) || (uVar7 = 2, iVar4 == 6)) {
          uVar7 = 0x19;
        }
        QueueOutgoingPacketField(uVar7);
      }
    }
    cVar3 = FUN_00406710();
    if (cVar3 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      (*pcVar13)(&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = PeekPacketChecksumState();
      (*pcVar13)(&DAT_005a9068);
      iVar4 = g_clientContext;
      piVar14 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar3 = PeekPacketChecksumBool();
      if ((cVar3 == '\0') && ((&DAT_006a7758)[iVar4] != '\0')) {
        if (((&DAT_006a7736)[iVar4] == '\x01') &&
           ((uVar12 = iVar5 - *(int *)(&DAT_006a7714 + iVar4) >> 0x1f,
            200 < (int)((iVar5 - *(int *)(&DAT_006a7714 + iVar4) ^ uVar12) - uVar12) ||
            (uVar12 = iVar8 - *(int *)(&DAT_006a7710 + iVar4) >> 0x1f,
            300 < (int)((iVar8 - *(int *)(&DAT_006a7710 + iVar4) ^ uVar12) - uVar12))))) {
          (&DAT_006a7736)[iVar4] = 0;
        }
        iVar10 = 400;
        if (399 < iVar8) {
          iVar10 = iVar8;
        }
        iVar9 = *(int *)(&DAT_006a7720 + iVar4) + -400;
        if ((iVar10 <= iVar9) && (iVar9 = iVar8, iVar8 < 400)) {
          iVar9 = 400;
        }
        iVar8 = -0x14;
        if (-0x15 < iVar5) {
          iVar8 = iVar5;
        }
        iVar10 = *(int *)(&DAT_006a7724 + iVar4) + -0x104;
        if ((iVar8 <= iVar10) && (iVar10 = -0x14, -0x15 < iVar5)) {
          iVar10 = iVar5;
        }
        iVar5 = *piVar14 - iVar9;
        *(int *)(&DAT_006a771c + iVar4) = iVar10;
        if (((*(int *)(&DAT_006a770c + iVar4) - iVar10) * (*(int *)(&DAT_006a770c + iVar4) - iVar10)
             + iVar5 * iVar5 < 40000) &&
           (((&DAT_006a7734)[iVar4] == '\x01' || ((&DAT_006a7f6c)[iVar4] == '\0')))) {
          *(int *)(&DAT_006a7710 + iVar4) = iVar9;
          *piVar14 = iVar9;
          *(int *)(&DAT_006a7714 + iVar4) = iVar10;
          *(int *)(&DAT_006a770c + iVar4) = iVar10;
        }
        if ((((&DAT_006a7734)[iVar4] == '\0') && ((&DAT_006a7f6c)[iVar4] == '\x01')) &&
           ((&DAT_006a7736)[iVar4] == '\0')) {
          iVar5 = *(int *)(&DAT_006a7730 + iVar4);
          iVar8 = iVar5;
          if (iVar9 <= iVar5) {
            iVar8 = iVar9;
          }
          iVar11 = *(int *)(&DAT_006a772c + iVar4);
          if ((iVar11 <= iVar8) && (iVar11 = iVar5, iVar9 <= iVar5)) {
            iVar11 = iVar9;
          }
          *(int *)(&DAT_006a7718 + iVar4) = iVar11;
        }
        if ((&DAT_006a7734)[iVar4] == '\x01') {
          *(int *)(&DAT_006a7718 + iVar4) = iVar9;
          *(int *)(&DAT_006a771c + iVar4) = iVar10;
        }
      }
    }
    goto LAB_0044d94c;
  }
  *(undefined1 *)(param_1 + 5) = 1;
  FUN_004262d0(param_1[2],param_1 + 0x45e);
  cVar3 = PeekPacketChecksumBool();
  if (cVar3 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((-1 < iVar4) && (iVar4 < *(int *)(&DAT_006a7720 + g_clientContext))) {
      pcVar6 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar4);
      puStack_ae4 = (undefined4 *)0x0;
      if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
        do {
          if (*pcVar6 != '\0') goto LAB_0044ca9a;
          pcVar6 = pcVar6 + *(int *)(&DAT_006a7720 + g_clientContext);
          puStack_ae4 = (undefined4 *)((int)puStack_ae4 + 1);
        } while ((int)puStack_ae4 < *(int *)(&DAT_006a7724 + g_clientContext));
      }
    }
    puStack_ae4 = (undefined4 *)0x2710;
LAB_0044ca9a:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,uVar7,puStack_ae4);
    local_ae8 = 1;
    if (0 < param_1[0xfe5]) {
      local_ae8 = param_1[0xfe5];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
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
    FUN_0043af40(uStack_ad0,puStack_ae4,0,uStack_ad4,(int)piStack_ae0 / local_ae8,uVar7,
                 (char)param_1[0xf]);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    piStack_ae0 = (int *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar19 = 0;
    uVar18 = 2;
    uVar17 = 0xff;
    uVar16 = 0;
    PeekPacketChecksumBool(0,uVar7,0xff,2,0);
    FUN_00431d90((char)param_1[0xf],7,0,uVar16,uVar7,uVar17,uVar18,uVar19);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar16 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = g_clientContext;
  iStack_ac8 = param_1[2];
  uStack_ad4 = uVar7;
  uStack_ad0 = uVar16;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar5 == 4) {
    puStack_ae4 = operator_new(0x3fbc);
    puStack_8 = (undefined1 *)0x0;
    apuStack_adc[0] = puStack_ae4;
    if (puStack_ae4 == (undefined4 *)0x0) {
      puStack_ae4 = (undefined4 *)0x0;
    }
    else {
      FUN_00454dc0(puStack_ae4,0x186a9);
      *puStack_ae4 = &PTR_FUN_0055658c;
      puStack_ae4[0xfe7] = 0xffffffff;
    }
    puStack_8 = (undefined1 *)0xffffffff;
    iVar5 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar12 = *(uint *)(iVar5 + 4);
    while (uVar12 < 0x186ab) {
      if (uVar12 == 0x186aa) {
        piVar14 = *(int **)(iVar5 + 0x10);
        bVar15 = true;
        piStack_acc = piVar14;
        if (piVar14[2] == 0) goto LAB_0044cd15;
        break;
      }
      iVar5 = *(int *)(iVar5 + 0x1c);
      uVar12 = *(uint *)(iVar5 + 4);
    }
  }
  goto LAB_0044d07e;
  while( true ) {
    piVar14 = (int *)piVar14[4];
    bVar15 = piVar14[2] == 0;
    piStack_acc = piVar14;
    if (!bVar15) break;
LAB_0044cd15:
    if (bVar15) {
      apuStack_adc[0] = (undefined4 *)piVar14[0xf];
      piStack_ae0 = (int *)piVar14[0xe];
      piStack_acc = piVar14;
      iVar5 = FUN_004f1f10();
      iVar8 = FloatToInt64();
      piStack_ae0 = (int *)((int)piStack_ae0 - iVar8);
      iVar8 = FloatToInt64();
      iVar8 = (int)apuStack_adc[0] - iVar8;
      (**(code **)(*piVar14 + 4))(&DAT_00553b90);
      piVar14[0x11] = iVar5;
      apuStack_adc[0] = (undefined4 *)(&DAT_006a7f74 + iVar4);
      cVar3 = PeekPacketChecksumBool();
      if (cVar3 == '\0') {
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
        uVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar4 = param_1[0xfe5];
        uVar19 = 0;
        uVar18 = 0xff;
        uVar17 = 100;
        uVar16 = 0;
        PeekPacketChecksumBool(uVar7,0,100,0xff,iVar4,0);
        FUN_00432320((char)param_1[0xf],1,1,uVar7,uVar16,uVar17,uVar18,iVar4,uVar19);
        puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),3);
        ScrubChecksumGuard();
LAB_0044cfdd:
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        cVar3 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&uStack_ad0,&uStack_ad4,2,1,1);
        if (cVar3 != '\0') {
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
          iVar4 = param_1[0xfe5];
          uVar19 = 0;
          uVar18 = 0xff;
          uVar17 = 100;
          uVar16 = 0;
          PeekChecksumStateUnderLock(auStack_8a0);
          uVar7 = PeekChecksumStateUnderLock(auStack_ac4);
          PeekPacketChecksumBool(uVar7,uVar16,uVar17,uVar18,iVar4,uVar19);
          FUN_00432320((char)param_1[0xf],1,1,uVar7,uVar16,uVar17,uVar18,iVar4,uVar19);
          puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
          ScrubChecksumGuard();
          goto LAB_0044cfdd;
        }
      }
      puStack_ae4[0xfea] = piStack_ae0;
      puStack_ae4[0xfeb] = iVar8;
      puStack_ae4[0xfec] = uStack_ad0;
      puStack_ae4[0xfed] = uStack_ad4;
      puStack_ae4[0xfee] = iVar5;
      uVar7 = FUN_004ac4d0();
      puStack_ae4[0xfe9] = uVar7;
      iVar4 = FUN_004ac400();
      puStack_ae4[0xfe8] = iVar4 * param_1[0xfe5];
      cVar3 = PeekPacketChecksumBool();
      if (cVar3 == '\0') {
        RegisterActiveObject();
      }
      else {
        (**(code **)*puStack_ae4)(1);
      }
      break;
    }
  }
LAB_0044d07e:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaSub(param_1 + 0x45e,auStack_ac4,uVar7);
  puStack_8 = (undefined1 *)0x5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_adc[0] = (undefined4 *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = FUN_004e4340();
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_ab0 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(apuStack_adc);
    pcVar13 = (code *)LeaveCriticalSection;
  }
  if (iVar5 < iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    if ((char)((uint)unaff_EBP >> 0x18) == '\0') {
      EncodeChecksumDeltaSub(param_1 + 0x3d5,&iStack_ac8,1);
      uStack_c = 7;
    }
    else {
      EncodeChecksumDeltaAdd(param_1 + 0x3d5,auStack_8a4,1);
      uStack_c = 6;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    uVar16 = PeekPacketChecksumBool(unaff_EDI);
    FUN_004375f0(&DAT_006a7f70 + g_clientContext,iVar4,uVar7,(char)param_1[0xf],uVar16,unaff_EDI);
    uStack_18 = 6;
    if ((unaff_ESI & 2) != 0) {
      unaff_ESI = unaff_ESI & 0xfffffffd;
      ScrubChecksumGuard();
    }
    uStack_18 = 0xffffffff;
    if ((unaff_ESI & 1) != 0) {
      ScrubChecksumGuard();
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    uVar16 = PeekPacketChecksumBool(unaff_EDI);
    FUN_004375f0(&DAT_006a7f70 + g_clientContext,iVar4,uVar7,(char)param_1[0xf],uVar16,unaff_EDI);
  }
  cVar3 = PeekPacketChecksumBool();
  if ((cVar3 != '\0') && (cVar3 = FUN_0043a530(), cVar3 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    QueueOutgoingPacketField(uVar7);
  }
LAB_0044d94c:
  *unaff_FS_OFFSET = uStack_20;
  return;
}

