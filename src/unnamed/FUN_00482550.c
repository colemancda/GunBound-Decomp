/* FUN_00482550 - 0x00482550 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00482550(int *param_1)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  int iVar16;
  undefined4 *puVar17;
  uint unaff_EBX;
  code *pcVar18;
  byte *pbVar19;
  undefined4 *unaff_FS_OFFSET;
  bool bVar20;
  undefined4 uVar21;
  undefined4 uVar22;
  int iStack_af4;
  int local_ae8;
  undefined4 *puStack_ae0;
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
  puStack_8 = &LAB_005401f3;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  iVar5 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar5 + iVar4);
  pcVar18 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  iVar5 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar5 + iVar4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(3);
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 == '\0') {
    EncodeChecksumDeltaShr(param_1 + 0x10,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x5;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar7);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_ab0 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(apuStack_ad0);
      pcVar18 = (code *)LeaveCriticalSection;
    }
    EncodeChecksumDeltaShr(param_1 + 0x99,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x6;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar7);
    (*pcVar18)(&DAT_005a9068);
    uStack_c = 0xffffffff;
    if (iStack_ab4 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&piStack_ad4);
      pcVar18 = (code *)LeaveCriticalSection;
    }
    cVar2 = CheckGuardedBoolAnd(param_1[0x3d2] != 0);
    if (cVar2 == '\0') {
      EmitChecksumSum(param_1 + 0x2bd);
      EmitChecksumSum(param_1 + 0x346);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar15 = PeekPacketChecksumState();
      (*pcVar18)(&DAT_005a9068);
      if ((int)((uVar15 ^ (int)uVar15 >> 0x1f) - ((int)uVar15 >> 0x1f)) < 200) {
        cVar2 = PacketChecksumLessThan(param_1 + 0x122,0);
        if (cVar2 == '\0') {
          uVar7 = 200;
        }
        else {
          uVar7 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar7);
      }
      uVar7 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_680,4);
      uStack_c = 7;
      uVar7 = EncodeChecksumPairDiff(param_1[0x3d2] + 0x38,auStack_45c,uVar7);
      uStack_c = 8;
      unaff_EBX = 3;
      cVar2 = CompareChecksumPair(param_1 + 0x3d5,uVar7);
      if (cVar2 == '\0') {
        uVar7 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_8a4,4);
        uStack_c = 9;
        uVar7 = EncodeChecksumPairSum(param_1[0x3d2] + 0x38,&iStack_ac8,uVar7);
        uStack_c = 10;
        unaff_EBX = 0xf;
        cVar2 = CompareChecksumPair(uVar7,param_1 + 0x3d5);
        bVar20 = false;
        if (cVar2 != '\0') goto LAB_00483427;
      }
      else {
LAB_00483427:
        bVar20 = true;
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
      if (bVar20) {
        iVar4 = param_1[0x3d4];
        param_1[0x3d4] = iVar4 + 1;
        if (iVar4 + 1 < 3) {
          uVar7 = EncodeChecksumNegate(param_1 + 0x122,auStack_238);
          uStack_c = 0xb;
          EncodeChecksumState(uVar7);
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
    (*pcVar18)(&DAT_005a9068);
    if ((char)(unaff_EBX >> 0x18) == '\0') {
      iVar4 = *(int *)(&g_nCameraBoundX + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      (*pcVar18)(&DAT_005a9068);
      if (((iVar4 <= iVar5) ||
          (cVar2 = PacketChecksumGreaterEqual(param_1 + 0x45e,*(undefined4 *)(&g_nCameraBoundY + g_clientContext)),
          cVar2 != '\0')) || (cVar2 = PacketChecksumLessThan(param_1 + 0x45e,0xfffffc18), cVar2 != '\0'))
      goto LAB_004835e2;
    }
    else {
LAB_004835e2:
      *(undefined1 *)(param_1 + 5) = 1;
      cVar2 = PeekPacketChecksumBool();
      if ((cVar2 != '\0') && (cVar2 = InitChecksumSeed(), cVar2 == '\0')) {
        iVar4 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
        if ((iVar4 == 5) || (uVar7 = 2, iVar4 == 6)) {
          uVar7 = 0x19;
        }
        QueueOutgoingPacketField(uVar7);
      }
    }
    cVar2 = CheckBothGuardedBools();
    if (cVar2 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      (*pcVar18)(&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar16 = PeekPacketChecksumState();
      (*pcVar18)(&DAT_005a9068);
      iVar4 = g_clientContext;
      piVar11 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar2 = PeekPacketChecksumBool();
      if ((cVar2 == '\0') && ((&DAT_006a7758)[iVar4] != '\0')) {
        if (((&DAT_006a7736)[iVar4] == '\x01') &&
           ((uVar15 = iVar5 - *(int *)(&g_nCameraY + iVar4) >> 0x1f,
            200 < (int)((iVar5 - *(int *)(&g_nCameraY + iVar4) ^ uVar15) - uVar15) ||
            (uVar15 = iVar16 - *(int *)(&g_nCameraX + iVar4) >> 0x1f,
            300 < (int)((iVar16 - *(int *)(&g_nCameraX + iVar4) ^ uVar15) - uVar15))))) {
          (&DAT_006a7736)[iVar4] = 0;
        }
        iVar12 = 400;
        if (399 < iVar16) {
          iVar12 = iVar16;
        }
        iVar13 = *(int *)(&g_nCameraBoundX + iVar4) + -400;
        if ((iVar12 <= iVar13) && (iVar13 = iVar16, iVar16 < 400)) {
          iVar13 = 400;
        }
        iVar16 = -0x14;
        if (-0x15 < iVar5) {
          iVar16 = iVar5;
        }
        iVar12 = *(int *)(&g_nCameraBoundY + iVar4) + -0x104;
        if ((iVar16 <= iVar12) && (iVar12 = -0x14, -0x15 < iVar5)) {
          iVar12 = iVar5;
        }
        iVar5 = *piVar11 - iVar13;
        *(int *)(&g_nCameraScrollY + iVar4) = iVar12;
        if (((*(int *)(&DAT_006a770c + iVar4) - iVar12) * (*(int *)(&DAT_006a770c + iVar4) - iVar12)
             + iVar5 * iVar5 < 40000) &&
           (((&DAT_006a7734)[iVar4] == '\x01' || ((&DAT_006a7f6c)[iVar4] == '\0')))) {
          *(int *)(&g_nCameraX + iVar4) = iVar13;
          *piVar11 = iVar13;
          *(int *)(&g_nCameraY + iVar4) = iVar12;
          *(int *)(&DAT_006a770c + iVar4) = iVar12;
        }
        if ((((&DAT_006a7734)[iVar4] == '\0') && ((&DAT_006a7f6c)[iVar4] == '\x01')) &&
           ((&DAT_006a7736)[iVar4] == '\0')) {
          iVar5 = *(int *)(&DAT_006a7730 + iVar4);
          iVar16 = iVar5;
          if (iVar13 <= iVar5) {
            iVar16 = iVar13;
          }
          iVar14 = *(int *)(&DAT_006a772c + iVar4);
          if ((iVar14 <= iVar16) && (iVar14 = iVar5, iVar13 <= iVar5)) {
            iVar14 = iVar13;
          }
          *(int *)(&g_nCameraScrollX + iVar4) = iVar14;
        }
        if ((&DAT_006a7734)[iVar4] == '\x01') {
          *(int *)(&g_nCameraScrollX + iVar4) = iVar13;
          *(int *)(&g_nCameraScrollY + iVar4) = iVar12;
        }
      }
    }
    goto LAB_004837a0;
  }
  *(undefined1 *)(param_1 + 5) = 1;
  SyncOutgoingChecksumField(param_1[2],param_1 + 0x45e);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((-1 < iVar4) && (iVar4 < *(int *)(&g_nCameraBoundX + g_clientContext))) {
    pcVar6 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar4);
    iStack_af4 = 0;
    if (0 < *(int *)(&g_nCameraBoundY + g_clientContext)) {
      do {
        if (*pcVar6 != '\0') goto LAB_0048268a;
        pcVar6 = pcVar6 + *(int *)(&g_nCameraBoundX + g_clientContext);
        iStack_af4 = iStack_af4 + 1;
      } while (iStack_af4 < *(int *)(&g_nCameraBoundY + g_clientContext));
    }
  }
  iStack_af4 = 10000;
LAB_0048268a:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00436070(&DAT_006a7f70 + g_clientContext,uVar7,iStack_af4);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar9 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uStack_ad8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0043af40(uStack_ad8,iStack_af4,0,uVar9,uVar8,uVar7,(char)param_1[0xf]);
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = g_clientContext;
    piVar11 = (int *)(&DAT_006a7708 + g_clientContext);
    cVar2 = PeekPacketChecksumBool();
    if ((cVar2 == '\0') && ((&DAT_006a7758)[iVar4] != '\0')) {
      if (((&DAT_006a7736)[iVar4] == '\x01') &&
         ((uVar15 = iStack_af4 - *(int *)(&g_nCameraY + iVar4) >> 0x1f,
          200 < (int)((iStack_af4 - *(int *)(&g_nCameraY + iVar4) ^ uVar15) - uVar15) ||
          (uVar15 = iVar5 - *(int *)(&g_nCameraX + iVar4) >> 0x1f,
          300 < (int)((iVar5 - *(int *)(&g_nCameraX + iVar4) ^ uVar15) - uVar15))))) {
        (&DAT_006a7736)[iVar4] = 0;
      }
      iVar16 = iVar5;
      if (iVar5 < 400) {
        iVar16 = 400;
      }
      iVar12 = *(int *)(&g_nCameraBoundX + iVar4) + -400;
      if ((*(int *)(&g_nCameraBoundX + iVar4) + -400 < iVar16) ||
         (puStack_ae0 = (undefined4 *)0x190, iVar12 = iVar5, 399 < iVar5)) {
        puStack_ae0 = (undefined4 *)iVar12;
      }
      iVar5 = iStack_af4;
      if (iStack_af4 < -0x14) {
        iVar5 = -0x14;
      }
      iVar16 = *(int *)(&g_nCameraBoundY + iVar4) + -0x104;
      if ((iVar5 <= *(int *)(&g_nCameraBoundY + iVar4) + -0x104) &&
         (iVar16 = iStack_af4, iStack_af4 < -0x14)) {
        iVar16 = -0x14;
      }
      *(int *)(&g_nCameraScrollY + iVar4) = iVar16;
      iVar5 = *piVar11 - (int)puStack_ae0;
      if (((*(int *)(&DAT_006a770c + iVar4) - iVar16) * (*(int *)(&DAT_006a770c + iVar4) - iVar16) +
           iVar5 * iVar5 < 40000) &&
         (((&DAT_006a7734)[iVar4] == '\x01' || ((&DAT_006a7f6c)[iVar4] == '\0')))) {
        *(undefined4 **)(&g_nCameraX + iVar4) = puStack_ae0;
        *piVar11 = (int)puStack_ae0;
        *(int *)(&g_nCameraY + iVar4) = iVar16;
        *(int *)(&DAT_006a770c + iVar4) = iVar16;
      }
      if ((((&DAT_006a7734)[iVar4] == '\0') && ((&DAT_006a7f6c)[iVar4] == '\x01')) &&
         ((&DAT_006a7736)[iVar4] == '\0')) {
        puVar10 = puStack_ae0;
        if (*(int *)(&DAT_006a7730 + iVar4) < (int)puStack_ae0) {
          puVar10 = (undefined4 *)*(int *)(&DAT_006a7730 + iVar4);
        }
        puVar17 = (undefined4 *)*(int *)(&DAT_006a772c + iVar4);
        if ((*(int *)(&DAT_006a772c + iVar4) <= (int)puVar10) &&
           (puVar17 = (undefined4 *)*(int *)(&DAT_006a7730 + iVar4),
           (int)puStack_ae0 <= *(int *)(&DAT_006a7730 + iVar4))) {
          puVar17 = puStack_ae0;
        }
        *(undefined4 **)(&g_nCameraScrollX + iVar4) = puVar17;
      }
      if ((&DAT_006a7734)[iVar4] == '\x01') {
        *(undefined4 **)(&g_nCameraScrollX + iVar4) = puStack_ae0;
        *(int *)(&g_nCameraScrollY + iVar4) = iVar16;
      }
    }
  }
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,uVar7,iStack_af4);
    local_ae8 = 1;
    if (0 < param_1[0xfe5]) {
      local_ae8 = param_1[0xfe5];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_ad8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    piStack_ad4 = (int *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0043af40(piStack_ad4,iStack_af4,0,uStack_ad8,iVar4 / local_ae8,uVar7,(char)param_1[0xf]);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar22 = 0;
    uVar21 = 2;
    uVar9 = 0xff;
    uVar8 = 0;
    PeekPacketChecksumBool(0,uVar7,0xff,2,0);
    FUN_00431d90((char)param_1[0xf],7,0,uVar8,uVar7,uVar9,uVar21,uVar22);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar11 = (int *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = g_clientContext;
  iStack_ac8 = param_1[2];
  uStack_ad8 = uVar7;
  piStack_ad4 = piVar11;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar5 == 4) {
    puStack_ae0 = operator_new(0x3fbc);
    puStack_8 = (undefined1 *)0x0;
    apuStack_ad0[0] = puStack_ae0;
    if (puStack_ae0 == (undefined4 *)0x0) {
      puStack_ae0 = (undefined4 *)0x0;
    }
    else {
      InitProjectile(puStack_ae0,0x186a9);
      *puStack_ae0 = &PTR_FUN_0055658c;
      puStack_ae0[0xfe7] = 0xffffffff;
    }
    puStack_8 = (undefined1 *)0xffffffff;
    iVar5 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar15 = *(uint *)(iVar5 + 4);
    while (uVar15 < 0x186ab) {
      if (uVar15 == 0x186aa) {
        piVar11 = *(int **)(iVar5 + 0x10);
        bVar20 = true;
        if (piVar11[2] == 0) goto LAB_00482b76;
        break;
      }
      iVar5 = *(int *)(iVar5 + 0x1c);
      uVar15 = *(uint *)(iVar5 + 4);
    }
  }
  goto LAB_00482edf;
  while( true ) {
    piVar11 = (int *)piVar11[4];
    bVar20 = piVar11[2] == 0;
    if (!bVar20) break;
LAB_00482b76:
    if (bVar20) {
      apuStack_ad0[0] = (undefined4 *)piVar11[0xf];
      iVar5 = piVar11[0xe];
      iVar16 = CalculateAngleFromDelta();
      iVar12 = FloatToInt64();
      iVar13 = FloatToInt64();
      iVar13 = (int)apuStack_ad0[0] - iVar13;
      (**(code **)(*piVar11 + 4))(&DAT_00553b90);
      piVar11[0x11] = iVar16;
      apuStack_ad0[0] = (undefined4 *)(&DAT_006a7f74 + iVar4);
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
        SyncOutgoingChecksumField(iStack_ac8 + 0x10,auStack_ac4);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar4 = param_1[0xfe5];
        uVar22 = 0;
        uVar21 = 0xff;
        uVar9 = 100;
        uVar8 = 0;
        PeekPacketChecksumBool(uVar7,0,100,0xff,iVar4,0);
        FUN_00432320((char)param_1[0xf],1,1,uVar7,uVar8,uVar9,uVar21,iVar4,uVar22);
        puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),3);
        ScrubChecksumGuard();
LAB_00482e3e:
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        cVar2 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&piStack_ad4,&uStack_ad8,2,1,1);
        if (cVar2 != '\0') {
          auStack_8a4[0] = 0;
          iStack_ab0 = 0;
          EncodeOutgoingPacketField(0);
          puStack_8 = (undefined1 *)0x1;
          auStack_680[0] = 0;
          uStack_88c = 0;
          EncodeOutgoingPacketField(0);
          SUBFIELD(puStack_8,0,undefined1) = 2;
          QueueOutgoingPacketField(piStack_ad4);
          QueueOutgoingPacketField(uStack_ad8);
          SyncOutgoingChecksumField(iStack_ac8 + 0x10,auStack_8a0);
          iVar4 = param_1[0xfe5];
          uVar22 = 0;
          uVar21 = 0xff;
          uVar9 = 100;
          uVar8 = 0;
          PeekChecksumStateUnderLock(auStack_8a0);
          uVar7 = PeekChecksumStateUnderLock(auStack_ac4);
          PeekPacketChecksumBool(uVar7,uVar8,uVar9,uVar21,iVar4,uVar22);
          FUN_00432320((char)param_1[0xf],1,1,uVar7,uVar8,uVar9,uVar21,iVar4,uVar22);
          puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
          ScrubChecksumGuard();
          goto LAB_00482e3e;
        }
      }
      puStack_ae0[0xfea] = iVar5 - iVar12;
      puStack_ae0[0xfeb] = iVar13;
      puStack_ae0[0xfec] = piStack_ad4;
      puStack_ae0[0xfed] = uStack_ad8;
      puStack_ae0[0xfee] = iVar16;
      /* angr-confirmed: self ptr lives in EDI here, reloaded from the
       * spilled projectile object (puStack_ae0) allocated/inited above. */
      uVar7 = FUN_004ac4d0(puStack_ae0);
      puStack_ae0[0xfe9] = uVar7;
      iVar4 = FUN_004ac400(puStack_ae0);
      puStack_ae0[0xfe8] = iVar4 * param_1[0xfe5];
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        RegisterActiveObject(0, 0, (undefined4 *)0);
      }
      else {
        (**(code **)*puStack_ae0)(1);
      }
      break;
    }
  }
LAB_00482edf:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar15 = (uint)*(byte *)(param_1 + 0xfe4);
  uVar21 = 0;
  uVar9 = 1;
  uVar8 = 0;
  PeekPacketChecksumBool(0,uVar7,uVar15,1,0);
  FUN_00431d90((char)param_1[0xf],7,0,uVar8,uVar7,uVar15,uVar9,uVar21);
  cVar2 = PeekPacketChecksumBool();
  if ((cVar2 != '\0') && (cVar2 = InitChecksumSeed(), cVar2 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    QueueOutgoingPacketField(uVar7);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar2 = CheckGuardedBoolAnd(iVar4 < iVar5);
  if (cVar2 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar7);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 < 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar4 < 1) goto LAB_0048305d;
LAB_004830a9:
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 == '\0') {
      SetGuardedBool(1);
    }
  }
  else {
LAB_0048305d:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar4) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar4 < 0) goto LAB_004830a9;
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar5 <= iVar4) || (cVar2 = CompareChecksumPair(param_1 + 0xed2,param_1 + 0xf5b), cVar2 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar4 <= iVar5) ||
       ((cVar2 = CompareChecksumExceeds(param_1 + 0xed2,param_1 + 0xf5b), cVar2 == '\0' ||
        (param_1[0xed1] < 6)))) goto LAB_004837a0;
  }
  iVar4 = g_clientContext;
  pbVar19 = (byte *)(g_clientContext + 0x62143);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = _rand();
  *pbVar19 = (byte)iVar5;
  iVar5 = _rand();
  bVar1 = *pbVar19;
  *(byte *)(iVar4 + 0x62144) = (byte)iVar5;
  bVar3 = '\x01' << (bVar1 & 7);
  bVar3 = ~bVar3 & (byte)iVar5 | bVar3;
  *(byte *)(iVar4 + 0x62144) = bVar3;
  *(byte *)(iVar4 + 0x62145) = bVar1 + bVar3 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
LAB_004837a0:
  *unaff_FS_OFFSET = uStack_10;
  return;
}

