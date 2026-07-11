/* FUN_0046e5a0 - 0x0046e5a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0046e5a0(int *param_1)

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
  int iVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  uint uVar14;
  int *piVar15;
  byte bVar16;
  int *piVar17;
  byte *pbVar18;
  undefined4 *unaff_FS_OFFSET;
  bool bVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  undefined4 uVar22;
  undefined4 uVar23;
  undefined4 *puStack_af0;
  int local_ae8;
  int *piStack_ae0;
  undefined4 uStack_ad8;
  undefined4 uStack_ad4;
  undefined4 *apuStack_ad0 [2];
  int iStack_ac8;
  undefined1 auStack_ac4 [20];
  int iStack_ab0;
  undefined1 uStack_8a4;
  undefined1 auStack_8a0 [20];
  undefined4 uStack_88c;
  undefined1 uStack_680;
  undefined1 auStack_67c [548];
  undefined1 auStack_458 [548];
  undefined1 auStack_234 [548];
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  piVar17 = piStack_ae0;
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053e1c3;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  iVar6 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar6 + iVar5);
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
      FUN_0040b540(apuStack_ad0);
      param_1 = piStack_ae0;
    }
    FUN_0040b180(param_1 + 0x99,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x6;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0xffffffff;
    piVar17 = param_1;
    if (iStack_ab0 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(apuStack_ad0);
      piVar17 = piStack_ae0;
    }
    cVar4 = FUN_00406610(piVar17[0x3d2] != 0);
    if (cVar4 == '\0') {
      FUN_0040afb0(piVar17 + 0x2bd);
      FUN_0040afb0(piVar17 + 0x346);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar14 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((int)((uVar14 ^ (int)uVar14 >> 0x1f) - ((int)uVar14 >> 0x1f)) < 200) {
        cVar4 = FUN_0040b330(piVar17 + 0x122,0);
        if (cVar4 == '\0') {
          uVar8 = 200;
        }
        else {
          uVar8 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar8);
      }
      uVar8 = EncodeChecksumDeltaDiv(piVar17[0x3d2] + 0x25c,auStack_67c,4);
      puStack_8 = (undefined1 *)0x7;
      uVar8 = EncodeChecksumPairDiff(piVar17[0x3d2] + 0x38,auStack_458,uVar8);
      puStack_8 = (undefined1 *)0x8;
      bVar2 = false;
      bVar19 = false;
      cVar4 = FUN_0040b490(piVar17 + 0x3d5,uVar8);
      if (cVar4 == '\0') {
        uVar8 = EncodeChecksumDeltaDiv(piVar17[0x3d2] + 0x25c,auStack_8a0,4);
        puStack_8 = (undefined1 *)0x9;
        uVar8 = EncodeChecksumPairSum(piVar17[0x3d2] + 0x38,auStack_ac4,uVar8);
        puStack_8 = (undefined1 *)0xa;
        bVar2 = true;
        bVar19 = true;
        cVar4 = FUN_0040b490(uVar8,piVar17 + 0x3d5);
        bVar3 = false;
        if (cVar4 != '\0') goto LAB_0046f73e;
      }
      else {
LAB_0046f73e:
        bVar3 = true;
      }
      puStack_8 = (undefined1 *)0x9;
      if (bVar19) {
        ScrubChecksumGuard();
      }
      puStack_8 = (undefined1 *)0x8;
      if (bVar2) {
        ScrubChecksumGuard();
      }
      puStack_8 = (undefined1 *)0x7;
      ScrubChecksumGuard();
      puStack_8 = (undefined1 *)0xffffffff;
      ScrubChecksumGuard();
      if (bVar3) {
        iVar5 = piVar17[0x3d4];
        piVar17[0x3d4] = iVar5 + 1;
        if (iVar5 + 1 < 3) {
          uVar8 = FUN_0040a500(piVar17 + 0x122,auStack_234);
          puStack_8 = (undefined1 *)0xb;
          EncodeChecksumState(uVar8);
          puStack_8 = (undefined1 *)0xffffffff;
          ScrubChecksumGuard();
        }
        else {
          FUN_00406500(0);
        }
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar5 < 0) {
LAB_0046f8f9:
      *(undefined1 *)(piVar17 + 5) = 1;
      cVar4 = PeekPacketChecksumBool();
      if ((cVar4 != '\0') && (cVar4 = FUN_0043a530(), cVar4 == '\0')) {
        iVar5 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
        if ((iVar5 == 5) || (uVar8 = 2, iVar5 == 6)) {
          uVar8 = 0x19;
        }
        QueueOutgoingPacketField(uVar8);
      }
    }
    else {
      iVar5 = *(int *)(&DAT_006a7720 + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (((iVar5 <= iVar6) ||
          (cVar4 = FUN_0040b300(param_1 + 0x45e,*(undefined4 *)(&DAT_006a7724 + g_clientContext)),
          cVar4 != '\0')) || (cVar4 = FUN_0040b330(param_1 + 0x45e,0xfffffc18), cVar4 != '\0'))
      goto LAB_0046f8f9;
    }
    cVar4 = FUN_00406710();
    if (cVar4 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar11 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = g_clientContext;
      piVar17 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar4 = PeekPacketChecksumBool();
      if ((cVar4 == '\0') && ((&DAT_006a7758)[iVar5] != '\0')) {
        if (((&DAT_006a7736)[iVar5] == '\x01') &&
           ((uVar14 = iVar6 - *(int *)(&DAT_006a7714 + iVar5) >> 0x1f,
            200 < (int)((iVar6 - *(int *)(&DAT_006a7714 + iVar5) ^ uVar14) - uVar14) ||
            (uVar14 = iVar11 - *(int *)(&DAT_006a7710 + iVar5) >> 0x1f,
            300 < (int)((iVar11 - *(int *)(&DAT_006a7710 + iVar5) ^ uVar14) - uVar14))))) {
          (&DAT_006a7736)[iVar5] = 0;
        }
        iVar9 = 400;
        if (399 < iVar11) {
          iVar9 = iVar11;
        }
        iVar10 = *(int *)(&DAT_006a7720 + iVar5) + -400;
        if ((iVar9 <= iVar10) && (iVar10 = iVar11, iVar11 < 400)) {
          iVar10 = 400;
        }
        iVar11 = -0x14;
        if (-0x15 < iVar6) {
          iVar11 = iVar6;
        }
        iVar9 = *(int *)(&DAT_006a7724 + iVar5) + -0x104;
        if ((iVar11 <= iVar9) && (iVar9 = -0x14, -0x15 < iVar6)) {
          iVar9 = iVar6;
        }
        iVar6 = *piVar17 - iVar10;
        *(int *)(&DAT_006a771c + iVar5) = iVar9;
        if (((*(int *)(&DAT_006a770c + iVar5) - iVar9) * (*(int *)(&DAT_006a770c + iVar5) - iVar9) +
             iVar6 * iVar6 < 40000) &&
           (((&DAT_006a7734)[iVar5] == '\x01' || ((&DAT_006a7f6c)[iVar5] == '\0')))) {
          *(int *)(&DAT_006a7710 + iVar5) = iVar10;
          *piVar17 = iVar10;
          *(int *)(&DAT_006a7714 + iVar5) = iVar9;
          *(int *)(&DAT_006a770c + iVar5) = iVar9;
        }
        if ((((&DAT_006a7734)[iVar5] == '\0') && ((&DAT_006a7f6c)[iVar5] == '\x01')) &&
           ((&DAT_006a7736)[iVar5] == '\0')) {
          iVar6 = *(int *)(&DAT_006a7730 + iVar5);
          iVar11 = iVar6;
          if (iVar10 <= iVar6) {
            iVar11 = iVar10;
          }
          iVar12 = *(int *)(&DAT_006a772c + iVar5);
          if ((iVar12 <= iVar11) && (iVar12 = iVar6, iVar10 <= iVar6)) {
            iVar12 = iVar10;
          }
          *(int *)(&DAT_006a7718 + iVar5) = iVar12;
        }
        if ((&DAT_006a7734)[iVar5] == '\x01') {
          *(int *)(&DAT_006a7718 + iVar5) = iVar10;
          *(int *)(&DAT_006a771c + iVar5) = iVar9;
        }
      }
    }
    goto LAB_0046fab7;
  }
  FUN_004262d0(param_1[2],param_1 + 0x45e);
  cVar4 = PeekPacketChecksumBool();
  if (cVar4 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((-1 < iVar5) && (iVar5 < *(int *)(&DAT_006a7720 + g_clientContext))) {
      pcVar7 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar5);
      puStack_af0 = (undefined4 *)0x0;
      if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
        do {
          if (*pcVar7 != '\0') goto LAB_0046e6ea;
          pcVar7 = pcVar7 + *(int *)(&DAT_006a7720 + g_clientContext);
          puStack_af0 = (undefined4 *)((int)puStack_af0 + 1);
        } while ((int)puStack_af0 < *(int *)(&DAT_006a7724 + g_clientContext));
      }
    }
    puStack_af0 = (undefined4 *)0x2710;
LAB_0046e6ea:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,uVar8,puStack_af0);
    local_ae8 = 1;
    if (0 < param_1[0xfe5]) {
      local_ae8 = param_1[0xfe5];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_ad4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_ad8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0043af40(uStack_ad8,puStack_af0,0,uStack_ad4,iVar5 / local_ae8,uVar8,(char)param_1[0xf]);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar23 = 0;
    uVar22 = 2;
    uVar21 = 0xff;
    uVar20 = 0;
    PeekPacketChecksumBool(0,uVar8,0xff,2,0);
    FUN_00431d90((char)param_1[0xf],7,0,uVar20,uVar8,uVar21,uVar22,uVar23);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar20 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = g_clientContext;
  iStack_ac8 = param_1[2];
  uStack_ad8 = uVar20;
  uStack_ad4 = uVar8;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar6 == 4) {
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
    iVar6 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar14 = *(uint *)(iVar6 + 4);
    while (uVar14 < 0x186ab) {
      if (uVar14 == 0x186aa) {
        piVar15 = *(int **)(iVar6 + 0x10);
        bVar19 = true;
        if (piVar15[2] == 0) goto LAB_0046e965;
        break;
      }
      iVar6 = *(int *)(iVar6 + 0x1c);
      uVar14 = *(uint *)(iVar6 + 4);
    }
  }
  goto LAB_0046ecce;
  while( true ) {
    piVar15 = (int *)piVar15[4];
    bVar19 = piVar15[2] == 0;
    if (!bVar19) break;
LAB_0046e965:
    if (bVar19) {
      apuStack_ad0[0] = (undefined4 *)piVar15[0xf];
      iVar6 = piVar15[0xe];
      iVar11 = FUN_004f1f10();
      iVar9 = FloatToInt64();
      iVar10 = FloatToInt64();
      iVar10 = (int)apuStack_ad0[0] - iVar10;
      (**(code **)(*piVar15 + 4))(&DAT_00553b90);
      piVar15[0x11] = iVar11;
      apuStack_ad0[0] = (undefined4 *)(&DAT_006a7f74 + iVar5);
      cVar4 = PeekPacketChecksumBool();
      if (cVar4 == '\0') {
        uStack_680 = 0;
        uStack_88c = 0;
        EncodeOutgoingPacketField(0);
        puStack_8 = (undefined1 *)0x3;
        uStack_8a4 = 0;
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
        uVar22 = 0xff;
        uVar21 = 100;
        uVar20 = 0;
        PeekPacketChecksumBool(uVar8,0,100,0xff,iVar5,0);
        FUN_00432320((char)param_1[0xf],1,1,uVar8,uVar20,uVar21,uVar22,iVar5,uVar23);
        puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),3);
        ScrubChecksumGuard();
LAB_0046ec2d:
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        cVar4 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&uStack_ad8,&uStack_ad4,2,1,1);
        if (cVar4 != '\0') {
          uStack_8a4 = 0;
          iStack_ab0 = 0;
          EncodeOutgoingPacketField(0);
          puStack_8 = (undefined1 *)0x1;
          uStack_680 = 0;
          uStack_88c = 0;
          EncodeOutgoingPacketField(0);
          SUBFIELD(puStack_8,0,undefined1) = 2;
          QueueOutgoingPacketField(uStack_ad8);
          QueueOutgoingPacketField(uStack_ad4);
          FUN_004262d0(iStack_ac8 + 0x10,auStack_8a0);
          iVar5 = param_1[0xfe5];
          uVar23 = 0;
          uVar22 = 0xff;
          uVar21 = 100;
          uVar20 = 0;
          PeekChecksumStateUnderLock(auStack_8a0);
          uVar8 = PeekChecksumStateUnderLock(auStack_ac4);
          PeekPacketChecksumBool(uVar8,uVar20,uVar21,uVar22,iVar5,uVar23);
          FUN_00432320((char)param_1[0xf],1,1,uVar8,uVar20,uVar21,uVar22,iVar5,uVar23);
          puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
          ScrubChecksumGuard();
          goto LAB_0046ec2d;
        }
      }
      puStack_af0[0xfea] = iVar6 - iVar9;
      puStack_af0[0xfeb] = iVar10;
      puStack_af0[0xfec] = uStack_ad8;
      puStack_af0[0xfed] = uStack_ad4;
      puStack_af0[0xfee] = iVar11;
      uVar8 = FUN_004ac4d0();
      puStack_af0[0xfe9] = uVar8;
      iVar5 = FUN_004ac400();
      puStack_af0[0xfe8] = iVar5 * param_1[0xfe5];
      cVar4 = PeekPacketChecksumBool();
      if (cVar4 == '\0') {
        RegisterActiveObject();
      }
      else {
        (**(code **)*puStack_af0)(1);
      }
      break;
    }
  }
LAB_0046ecce:
  *(undefined1 *)(piStack_ae0 + 5) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar20 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_ad0[0] = (undefined4 *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar21 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar22 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar23 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uStack_ad4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uStack_ad8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iStack_ac8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004e4970(uStack_ad8,uStack_ad4,uVar23,uVar22,uVar21,apuStack_ad0[0],uVar20,uVar8);
  FUN_004e4d00(&DAT_006a7708 + g_clientContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_ad0[0] = (undefined4 *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00450eb0(apuStack_ad0[0],uVar8,piStack_ae0,1,0,0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar20 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00436ac0(uVar20,uVar8);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_ad0[0] = (undefined4 *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004372f0(piStack_ae0[2],apuStack_ad0[0],uVar8,piStack_ae0[0xe25],piStack_ae0 + 0xe26);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar20 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar21 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00437150(uVar21,uVar20,0x3c,uVar8);
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
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_ad0[0] = (undefined4 *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar20 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar21 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar22 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0043b7a0(uVar22,uVar21,0,uVar20,apuStack_ad0[0],uVar8,(char)piStack_ae0[0xf]);
  cVar4 = PeekPacketChecksumBool();
  if (cVar4 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar11 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = g_clientContext;
    piVar15 = (int *)(&DAT_006a7708 + g_clientContext);
    cVar4 = PeekPacketChecksumBool();
    if ((cVar4 == '\0') && ((&DAT_006a7758)[iVar5] != '\0')) {
      if (((&DAT_006a7736)[iVar5] == '\x01') &&
         ((uVar14 = iVar6 - *(int *)(&DAT_006a7714 + iVar5) >> 0x1f,
          200 < (int)((iVar6 - *(int *)(&DAT_006a7714 + iVar5) ^ uVar14) - uVar14) ||
          (uVar14 = iVar11 - *(int *)(&DAT_006a7710 + iVar5) >> 0x1f,
          300 < (int)((iVar11 - *(int *)(&DAT_006a7710 + iVar5) ^ uVar14) - uVar14))))) {
        (&DAT_006a7736)[iVar5] = 0;
      }
      iVar9 = 400;
      if (399 < iVar11) {
        iVar9 = iVar11;
      }
      piStack_ae0 = (int *)(*(int *)(&DAT_006a7720 + iVar5) + -400);
      if ((iVar9 <= (int)piStack_ae0) && (piStack_ae0 = (int *)0x190, 399 < iVar11)) {
        piStack_ae0 = (int *)iVar11;
      }
      iVar11 = -0x14;
      if (-0x15 < iVar6) {
        iVar11 = iVar6;
      }
      iVar9 = *(int *)(&DAT_006a7724 + iVar5) + -0x104;
      if ((iVar11 <= *(int *)(&DAT_006a7724 + iVar5) + -0x104) && (iVar9 = -0x14, -0x15 < iVar6)) {
        iVar9 = iVar6;
      }
      iVar6 = *piVar15 - (int)piStack_ae0;
      *(int *)(&DAT_006a771c + iVar5) = iVar9;
      if (((*(int *)(&DAT_006a770c + iVar5) - iVar9) * (*(int *)(&DAT_006a770c + iVar5) - iVar9) +
           iVar6 * iVar6 < 40000) &&
         (((&DAT_006a7734)[iVar5] == '\x01' || ((&DAT_006a7f6c)[iVar5] == '\0')))) {
        *(int **)(&DAT_006a7710 + iVar5) = piStack_ae0;
        *piVar15 = (int)piStack_ae0;
        *(int *)(&DAT_006a7714 + iVar5) = iVar9;
        *(int *)(&DAT_006a770c + iVar5) = iVar9;
      }
      if ((((&DAT_006a7734)[iVar5] == '\0') && ((&DAT_006a7f6c)[iVar5] == '\x01')) &&
         ((&DAT_006a7736)[iVar5] == '\0')) {
        piVar15 = (int *)*(int *)(&DAT_006a7730 + iVar5);
        if ((int)piStack_ae0 <= *(int *)(&DAT_006a7730 + iVar5)) {
          piVar15 = piStack_ae0;
        }
        piVar13 = (int *)*(int *)(&DAT_006a772c + iVar5);
        if ((*(int *)(&DAT_006a772c + iVar5) <= (int)piVar15) &&
           (piVar13 = (int *)*(int *)(&DAT_006a7730 + iVar5),
           (int)piStack_ae0 <= *(int *)(&DAT_006a7730 + iVar5))) {
          piVar13 = piStack_ae0;
        }
        *(int **)(&DAT_006a7718 + iVar5) = piVar13;
      }
      if ((&DAT_006a7734)[iVar5] == '\x01') {
        *(int **)(&DAT_006a7718 + iVar5) = piStack_ae0;
        *(int *)(&DAT_006a771c + iVar5) = iVar9;
      }
    }
  }
  cVar4 = PeekPacketChecksumBool();
  if ((cVar4 != '\0') && (cVar4 = FUN_0043a530(), cVar4 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    QueueOutgoingPacketField(uVar8);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar4 = FUN_00406610(iVar5 < iVar6);
  if (cVar4 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar5 < 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar5 < 1) goto LAB_0046f388;
LAB_0046f3d4:
    cVar4 = PeekPacketChecksumBool();
    if (cVar4 == '\0') {
      FUN_00406500(1);
    }
  }
  else {
LAB_0046f388:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar5) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar5 < 0) goto LAB_0046f3d4;
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar6 <= iVar5) || (cVar4 = FUN_0040b490(piVar17 + 0xed2,piVar17 + 0xf5b), cVar4 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar5 <= iVar6) ||
       ((cVar4 = FUN_0040b410(piVar17 + 0xed2,piVar17 + 0xf5b), cVar4 == '\0' ||
        (piVar17[0xed1] < 6)))) goto LAB_0046fab7;
  }
  iVar5 = g_clientContext;
  pbVar18 = (byte *)(g_clientContext + 0x62143);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *pbVar18 = (byte)iVar6;
  iVar6 = _rand();
  bVar1 = *pbVar18;
  *(byte *)(iVar5 + 0x62144) = (byte)iVar6;
  bVar16 = '\x01' << (bVar1 & 7);
  bVar16 = ~bVar16 & (byte)iVar6 | bVar16;
  *(byte *)(iVar5 + 0x62144) = bVar16;
  *(byte *)(iVar5 + 0x62145) = bVar1 + bVar16 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
LAB_0046fab7:
  *unaff_FS_OFFSET = uStack_10;
  return;
}

