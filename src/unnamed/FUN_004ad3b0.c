/* FUN_004ad3b0 - 0x004ad3b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004ad3b0(int *param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint unaff_EBX;
  code *pcVar11;
  int *piVar12;
  undefined4 *unaff_FS_OFFSET;
  bool bVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined4 *puStack_af0;
  int local_aec;
  undefined4 uStack_adc;
  undefined4 uStack_ad8;
  int *piStack_ad4;
  int *piStack_ad0;
  undefined4 *puStack_acc;
  undefined1 auStack_ac8 [4];
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
  puStack_8 = &LAB_0053e523;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar3 + iVar2);
  pcVar11 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar3 + iVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    FUN_004262d0(param_1[2],param_1 + 0x45e);
    cVar1 = PeekPacketChecksumBool();
    if (cVar1 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((-1 < iVar2) && (iVar2 < *(int *)(&DAT_006a7720 + g_clientContext))) {
        pcVar4 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar2);
        puStack_af0 = (undefined4 *)0x0;
        if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
          do {
            if (*pcVar4 != '\0') goto LAB_004ad512;
            pcVar4 = pcVar4 + *(int *)(&DAT_006a7720 + g_clientContext);
            puStack_af0 = (undefined4 *)((int)puStack_af0 + 1);
          } while ((int)puStack_af0 < *(int *)(&DAT_006a7724 + g_clientContext));
        }
      }
      puStack_af0 = (undefined4 *)0x2710;
LAB_004ad512:
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_00436070(&DAT_006a7f70 + g_clientContext,uVar5,puStack_af0);
      local_aec = 1;
      if (0 < param_1[0xfe5]) {
        local_aec = param_1[0xfe5];
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uStack_adc = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uStack_ad8 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_0043af40(uStack_ad8,puStack_af0,0,uStack_adc,iVar2 / local_aec,uVar5,(char)param_1[0xf]);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar17 = 0;
      uVar16 = 2;
      uVar15 = 0xff;
      uVar14 = 0;
      PeekPacketChecksumBool(0,uVar5,0xff,2,0);
      FUN_00431d90((char)param_1[0xf],7,0,uVar14,uVar5,uVar15,uVar16,uVar17);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar14 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    piStack_ad0 = (int *)param_1[2];
    uStack_adc = uVar5;
    uStack_ad8 = uVar14;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar2 == 4) {
      puStack_af0 = operator_new(0x3fbc);
      puStack_8 = (undefined1 *)0x0;
      puStack_acc = puStack_af0;
      if (puStack_af0 == (undefined4 *)0x0) {
        puStack_af0 = (undefined4 *)0x0;
      }
      else {
        FUN_00454dc0(puStack_af0,0x186a9);
        *puStack_af0 = &PTR_FUN_0055658c;
        puStack_af0[0xfe7] = 0xffffffff;
      }
      puStack_8 = (undefined1 *)0xffffffff;
      iVar2 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
      uVar8 = *(uint *)(iVar2 + 4);
      if (uVar8 < 0x186ab) {
        do {
          if (uVar8 == 0x186aa) {
            piVar12 = *(int **)(iVar2 + 0x10);
            bVar13 = true;
            piStack_ad4 = piVar12;
            if (piVar12[2] == 0) goto LAB_004ad793;
            goto LAB_004adaf2;
          }
          iVar2 = *(int *)(iVar2 + 0x1c);
          uVar8 = *(uint *)(iVar2 + 4);
        } while (uVar8 < 0x186ab);
        (**(code **)(*param_1 + 0x20))();
        goto LAB_004ae0cf;
      }
    }
LAB_004adaf2:
    (**(code **)(*param_1 + 0x20))();
    goto LAB_004ae0cf;
  }
  EncodeChecksumDeltaShr(param_1 + 0x10,auStack_ac4,8);
  puStack_8 = (undefined1 *)0x5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_ab0 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(&puStack_acc);
    pcVar11 = (code *)LeaveCriticalSection;
  }
  EncodeChecksumDeltaShr(param_1 + 0x99,auStack_ac4,8);
  puStack_8 = (undefined1 *)0x6;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar5);
  (*pcVar11)(&DAT_005a9068);
  uStack_c = 0xffffffff;
  if (iStack_ab4 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(&piStack_ad0);
    pcVar11 = (code *)LeaveCriticalSection;
  }
  cVar1 = FUN_00406610(param_1[0x3d2] != 0);
  if (cVar1 == '\0') {
    FUN_0040afb0(param_1 + 0x2bd);
    FUN_0040afb0(param_1 + 0x346);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    (*pcVar11)(&DAT_005a9068);
    if ((int)((uVar8 ^ (int)uVar8 >> 0x1f) - ((int)uVar8 >> 0x1f)) < 200) {
      cVar1 = PacketChecksumLessThan(param_1 + 0x122,0);
      if (cVar1 == '\0') {
        uVar5 = 200;
      }
      else {
        uVar5 = 0xffffff38;
      }
      QueueOutgoingPacketField(uVar5);
    }
    uVar5 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_680,4);
    uStack_c = 7;
    uVar5 = EncodeChecksumPairDiff(param_1[0x3d2] + 0x38,auStack_45c,uVar5);
    uStack_c = 8;
    unaff_EBX = 3;
    cVar1 = CompareChecksumPair(param_1 + 0x3d5,uVar5);
    if (cVar1 == '\0') {
      uVar5 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_8a4,4);
      uStack_c = 9;
      uVar5 = EncodeChecksumPairSum(param_1[0x3d2] + 0x38,auStack_ac8,uVar5);
      uStack_c = 10;
      unaff_EBX = 0xf;
      cVar1 = CompareChecksumPair(uVar5,param_1 + 0x3d5);
      bVar13 = false;
      if (cVar1 != '\0') goto LAB_004add3c;
    }
    else {
LAB_004add3c:
      bVar13 = true;
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
    if (bVar13) {
      iVar2 = param_1[0x3d4];
      param_1[0x3d4] = iVar2 + 1;
      if (iVar2 + 1 < 3) {
        uVar5 = FUN_0040a500(param_1 + 0x122,auStack_238);
        uStack_c = 0xb;
        EncodeChecksumState(uVar5);
        uStack_c = 0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        SetGuardedBool(0);
      }
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piStack_ad0 = param_1 + 0x3d5;
  PeekPacketChecksumState();
  (*pcVar11)(&DAT_005a9068);
  if ((char)(unaff_EBX >> 0x18) == '\0') {
    iVar2 = *(int *)(&DAT_006a7720 + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    (*pcVar11)(&DAT_005a9068);
    if (((iVar2 <= iVar3) ||
        (cVar1 = FUN_0040b300(param_1 + 0x45e,*(undefined4 *)(&DAT_006a7724 + g_clientContext)),
        cVar1 != '\0')) || (cVar1 = PacketChecksumLessThan(param_1 + 0x45e,0xfffffc18), cVar1 != '\0'))
    goto LAB_004adef8;
  }
  else {
LAB_004adef8:
    *(undefined1 *)(param_1 + 5) = 1;
    cVar1 = PeekPacketChecksumBool();
    if ((cVar1 != '\0') && (cVar1 = FUN_0043a530(), cVar1 == '\0')) {
      iVar2 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
      if ((iVar2 == 5) || (uVar5 = 2, iVar2 == 6)) {
        uVar5 = 0x19;
      }
      QueueOutgoingPacketField(uVar5);
      iVar2 = g_clientContext;
      *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
      *(undefined4 *)(&DAT_005f376c + iVar2) = 0;
    }
  }
  cVar1 = FUN_00406710();
  if (cVar1 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    (*pcVar11)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    (*pcVar11)(&DAT_005a9068);
    iVar2 = g_clientContext;
    piVar12 = (int *)(&DAT_006a7708 + g_clientContext);
    cVar1 = PeekPacketChecksumBool();
    if ((cVar1 == '\0') && ((&DAT_006a7758)[iVar2] != '\0')) {
      if (((&DAT_006a7736)[iVar2] == '\x01') &&
         ((uVar8 = iVar3 - *(int *)(&DAT_006a7714 + iVar2) >> 0x1f,
          200 < (int)((iVar3 - *(int *)(&DAT_006a7714 + iVar2) ^ uVar8) - uVar8) ||
          (uVar8 = iVar6 - *(int *)(&DAT_006a7710 + iVar2) >> 0x1f,
          300 < (int)((iVar6 - *(int *)(&DAT_006a7710 + iVar2) ^ uVar8) - uVar8))))) {
        (&DAT_006a7736)[iVar2] = 0;
      }
      iVar7 = 400;
      if (399 < iVar6) {
        iVar7 = iVar6;
      }
      iVar9 = *(int *)(&DAT_006a7720 + iVar2) + -400;
      if ((iVar7 <= iVar9) && (iVar9 = iVar6, iVar6 < 400)) {
        iVar9 = 400;
      }
      iVar6 = -0x14;
      if (-0x15 < iVar3) {
        iVar6 = iVar3;
      }
      iVar7 = *(int *)(&DAT_006a7724 + iVar2) + -0x104;
      if ((iVar6 <= iVar7) && (iVar7 = -0x14, -0x15 < iVar3)) {
        iVar7 = iVar3;
      }
      iVar3 = *piVar12 - iVar9;
      *(int *)(&DAT_006a771c + iVar2) = iVar7;
      if (((*(int *)(&DAT_006a770c + iVar2) - iVar7) * (*(int *)(&DAT_006a770c + iVar2) - iVar7) +
           iVar3 * iVar3 < 40000) &&
         (((&DAT_006a7734)[iVar2] == '\x01' || ((&DAT_006a7f6c)[iVar2] == '\0')))) {
        *(int *)(&DAT_006a7710 + iVar2) = iVar9;
        *piVar12 = iVar9;
        *(int *)(&DAT_006a7714 + iVar2) = iVar7;
        *(int *)(&DAT_006a770c + iVar2) = iVar7;
      }
      if ((((&DAT_006a7734)[iVar2] == '\0') && ((&DAT_006a7f6c)[iVar2] == '\x01')) &&
         ((&DAT_006a7736)[iVar2] == '\0')) {
        iVar3 = *(int *)(&DAT_006a7730 + iVar2);
        iVar6 = iVar3;
        if (iVar9 <= iVar3) {
          iVar6 = iVar9;
        }
        iVar10 = *(int *)(&DAT_006a772c + iVar2);
        if ((iVar10 <= iVar6) && (iVar10 = iVar3, iVar9 <= iVar3)) {
          iVar10 = iVar9;
        }
        *(int *)(&DAT_006a7718 + iVar2) = iVar10;
      }
      if ((&DAT_006a7734)[iVar2] == '\x01') {
        *(int *)(&DAT_006a7718 + iVar2) = iVar9;
        *(int *)(&DAT_006a771c + iVar2) = iVar7;
      }
    }
  }
LAB_004ae0cf:
  *unaff_FS_OFFSET = uStack_10;
  return;
  while( true ) {
    piVar12 = (int *)piVar12[4];
    bVar13 = piVar12[2] == 0;
    if (!bVar13) break;
LAB_004ad793:
    if (bVar13) {
      puStack_acc = (undefined4 *)piVar12[0xf];
      iVar2 = piVar12[0xe];
      piStack_ad4 = piVar12;
      iVar3 = FUN_004f1f10();
      iVar6 = FloatToInt64();
      iVar7 = FloatToInt64();
      iVar7 = (int)puStack_acc - iVar7;
      (**(code **)(*piVar12 + 4))(&DAT_00553b90);
      piVar12[0x11] = iVar3;
      cVar1 = PeekPacketChecksumBool();
      if (cVar1 == '\0') {
        auStack_680[0] = 0;
        uStack_88c = 0;
        EncodeOutgoingPacketField(0);
        puStack_8 = (undefined1 *)0x3;
        auStack_8a4[0] = 0;
        iStack_ab0 = 0;
        EncodeOutgoingPacketField(0);
        SUBFIELD(puStack_8,0,undefined1) = 4;
        FUN_004262d0(piStack_ad0 + 4,auStack_ac4);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar9 = param_1[0xfe5];
        uVar17 = 0;
        uVar16 = 0xff;
        uVar15 = 100;
        uVar14 = 0;
        PeekPacketChecksumBool(uVar5,0,100,0xff,iVar9,0);
        FUN_00432320((char)param_1[0xf],1,1,uVar5,uVar14,uVar15,uVar16,iVar9,uVar17);
        puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),3);
        ScrubChecksumGuard();
LAB_004ada51:
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        cVar1 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&uStack_ad8,&uStack_adc,2,1,1);
        if (cVar1 != '\0') {
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
          FUN_004262d0(piStack_ad0 + 4,auStack_8a0);
          iVar9 = param_1[0xfe5];
          uVar17 = 0;
          uVar16 = 0xff;
          uVar15 = 100;
          uVar14 = 0;
          PeekChecksumStateUnderLock(auStack_8a0);
          uVar5 = PeekChecksumStateUnderLock(auStack_ac4);
          PeekPacketChecksumBool(uVar5,uVar14,uVar15,uVar16,iVar9,uVar17);
          FUN_00432320((char)param_1[0xf],1,1,uVar5,uVar14,uVar15,uVar16,iVar9,uVar17);
          puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
          ScrubChecksumGuard();
          goto LAB_004ada51;
        }
      }
      puStack_af0[0xfea] = iVar2 - iVar6;
      puStack_af0[0xfeb] = iVar7;
      puStack_af0[0xfed] = uStack_adc;
      puStack_af0[0xfec] = uStack_ad8;
      puStack_af0[0xfee] = iVar3;
      uVar5 = FUN_004ac4d0();
      puStack_af0[0xfe9] = uVar5;
      iVar2 = FUN_004ac400();
      puStack_af0[0xfe8] = iVar2 * param_1[0xfe5];
      cVar1 = PeekPacketChecksumBool();
      if (cVar1 != '\0') {
        (**(code **)*puStack_af0)(1);
        (**(code **)(*param_1 + 0x20))();
        goto LAB_004ae0cf;
      }
      RegisterActiveObject();
      goto LAB_004adaf2;
    }
  }
  piStack_ad4 = piVar12;
  (**(code **)(*param_1 + 0x20))();
  goto LAB_004ae0cf;
}

