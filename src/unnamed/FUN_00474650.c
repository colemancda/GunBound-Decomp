/* FUN_00474650 - 0x00474650 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00474650(int *param_1)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  undefined4 uVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  byte bVar15;
  byte *pbVar16;
  undefined4 *unaff_FS_OFFSET;
  bool bVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  undefined4 *puStack_b04;
  int iStack_af4;
  undefined4 uStack_aec;
  int *piStack_ae8;
  int *local_ae4;
  undefined4 *apuStack_ae0 [2];
  int iStack_ad8;
  undefined4 uStack_ad4;
  undefined4 uStack_ad0;
  undefined4 uStack_acc;
  undefined4 uStack_ac8;
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
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053f853;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_ae4 = param_1;
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
    EncodeChecksumDeltaShr(param_1 + 0x10,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x5;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_ab0 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(apuStack_ae0);
      param_1 = piStack_ae8;
    }
    EncodeChecksumDeltaShr(param_1 + 0x99,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x6;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0xffffffff;
    piVar9 = param_1;
    if (iStack_ab0 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(apuStack_ae0);
      piVar9 = piStack_ae8;
    }
    cVar4 = CheckGuardedBoolAnd(piVar9[0x3d2] != 0);
    if (cVar4 == '\0') {
      EmitChecksumSum(piVar9 + 0x2bd);
      EmitChecksumSum(piVar9 + 0x346);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar13 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((int)((uVar13 ^ (int)uVar13 >> 0x1f) - ((int)uVar13 >> 0x1f)) < 200) {
        cVar4 = PacketChecksumLessThan(piVar9 + 0x122,0);
        if (cVar4 == '\0') {
          uVar8 = 200;
        }
        else {
          uVar8 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar8);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar13 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((int)((uVar13 ^ (int)uVar13 >> 0x1f) - ((int)uVar13 >> 0x1f)) < 1000) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(1000);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      uVar8 = EncodeChecksumDeltaDiv(piVar9[0x3d2] + 0x25c,auStack_458,4);
      puStack_8 = (undefined1 *)0x7;
      uVar8 = EncodeChecksumPairDiff(piVar9[0x3d2] + 0x38,auStack_67c,uVar8);
      puStack_8 = (undefined1 *)0x8;
      bVar2 = false;
      bVar17 = false;
      cVar4 = CompareChecksumPair(piVar9 + 0x3d5,uVar8);
      if (cVar4 == '\0') {
        uVar8 = EncodeChecksumDeltaDiv(piVar9[0x3d2] + 0x25c,auStack_8a0,4);
        puStack_8 = (undefined1 *)0x9;
        uVar8 = EncodeChecksumPairSum(piVar9[0x3d2] + 0x38,auStack_ac4,uVar8);
        puStack_8 = (undefined1 *)0xa;
        bVar2 = true;
        bVar17 = true;
        cVar4 = CompareChecksumPair(uVar8,piVar9 + 0x3d5);
        bVar3 = false;
        if (cVar4 != '\0') goto LAB_004755fb;
      }
      else {
LAB_004755fb:
        bVar3 = true;
      }
      puStack_8 = (undefined1 *)0x9;
      if (bVar17) {
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
        iVar5 = piVar9[0x3d4];
        piVar9[0x3d4] = iVar5 + 1;
        if (iVar5 + 1 < 3) {
          uVar8 = EncodeChecksumNegate(piVar9 + 0x122,auStack_234);
          puStack_8 = (undefined1 *)0xb;
          EncodeChecksumState(uVar8);
          puStack_8 = (undefined1 *)0xffffffff;
          ScrubChecksumGuard();
        }
        else {
          SetGuardedBool(0);
        }
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar5 < 0) {
LAB_004757b6:
      *(undefined1 *)(piVar9 + 5) = 1;
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
      iVar5 = *(int *)(&g_nCameraBoundX + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (((iVar5 <= iVar6) ||
          (cVar4 = PacketChecksumGreaterEqual(param_1 + 0x45e,*(undefined4 *)(&g_nCameraBoundY + g_clientContext)),
          cVar4 != '\0')) || (cVar4 = PacketChecksumLessThan(param_1 + 0x45e,0xfffffc18), cVar4 != '\0'))
      goto LAB_004757b6;
    }
    cVar4 = CheckBothGuardedBools();
    if (cVar4 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar10 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = g_clientContext;
      piVar9 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar4 = PeekPacketChecksumBool();
      if ((cVar4 == '\0') && ((&DAT_006a7758)[iVar5] != '\0')) {
        if (((&DAT_006a7736)[iVar5] == '\x01') &&
           ((uVar13 = iVar6 - *(int *)(&g_nCameraY + iVar5) >> 0x1f,
            200 < (int)((iVar6 - *(int *)(&g_nCameraY + iVar5) ^ uVar13) - uVar13) ||
            (uVar13 = iVar10 - *(int *)(&g_nCameraX + iVar5) >> 0x1f,
            300 < (int)((iVar10 - *(int *)(&g_nCameraX + iVar5) ^ uVar13) - uVar13))))) {
          (&DAT_006a7736)[iVar5] = 0;
        }
        iVar11 = 400;
        if (399 < iVar10) {
          iVar11 = iVar10;
        }
        iVar12 = *(int *)(&g_nCameraBoundX + iVar5) + -400;
        if ((iVar11 <= iVar12) && (iVar12 = iVar10, iVar10 < 400)) {
          iVar12 = 400;
        }
        iVar10 = -0x14;
        if (-0x15 < iVar6) {
          iVar10 = iVar6;
        }
        iVar11 = *(int *)(&g_nCameraBoundY + iVar5) + -0x104;
        if ((iVar10 <= iVar11) && (iVar11 = -0x14, -0x15 < iVar6)) {
          iVar11 = iVar6;
        }
        iVar6 = *piVar9 - iVar12;
        *(int *)(&g_nCameraScrollY + iVar5) = iVar11;
        if (((*(int *)(&DAT_006a770c + iVar5) - iVar11) * (*(int *)(&DAT_006a770c + iVar5) - iVar11)
             + iVar6 * iVar6 < 40000) &&
           (((&DAT_006a7734)[iVar5] == '\x01' || ((&DAT_006a7f6c)[iVar5] == '\0')))) {
          *(int *)(&g_nCameraX + iVar5) = iVar12;
          *piVar9 = iVar12;
          *(int *)(&g_nCameraY + iVar5) = iVar11;
          *(int *)(&DAT_006a770c + iVar5) = iVar11;
        }
        if ((((&DAT_006a7734)[iVar5] == '\0') && ((&DAT_006a7f6c)[iVar5] == '\x01')) &&
           ((&DAT_006a7736)[iVar5] == '\0')) {
          iVar6 = *(int *)(&DAT_006a7730 + iVar5);
          iVar10 = iVar6;
          if (iVar12 <= iVar6) {
            iVar10 = iVar12;
          }
          iVar14 = *(int *)(&DAT_006a772c + iVar5);
          if ((iVar14 <= iVar10) && (iVar14 = iVar6, iVar12 <= iVar6)) {
            iVar14 = iVar12;
          }
          *(int *)(&g_nCameraScrollX + iVar5) = iVar14;
        }
        if ((&DAT_006a7734)[iVar5] == '\x01') {
          *(int *)(&g_nCameraScrollX + iVar5) = iVar12;
          *(int *)(&g_nCameraScrollY + iVar5) = iVar11;
        }
      }
    }
    goto LAB_00475974;
  }
  FUN_004262d0(param_1[2],param_1 + 0x45e);
  cVar4 = PeekPacketChecksumBool();
  if (cVar4 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((-1 < iVar5) && (iVar5 < *(int *)(&g_nCameraBoundX + g_clientContext))) {
      pcVar7 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar5);
      puStack_b04 = (undefined4 *)0x0;
      if (0 < *(int *)(&g_nCameraBoundY + g_clientContext)) {
        do {
          if (*pcVar7 != '\0') goto LAB_0047479a;
          pcVar7 = pcVar7 + *(int *)(&g_nCameraBoundX + g_clientContext);
          puStack_b04 = (undefined4 *)((int)puStack_b04 + 1);
        } while ((int)puStack_b04 < *(int *)(&g_nCameraBoundY + g_clientContext));
      }
    }
    puStack_b04 = (undefined4 *)0x2710;
LAB_0047479a:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,uVar8,puStack_b04);
    iStack_af4 = 1;
    if (0 < param_1[0xfe5]) {
      iStack_af4 = param_1[0xfe5];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_ae4 = (int *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_aec = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0043af40(uStack_aec,puStack_b04,0,local_ae4,iVar5 / iStack_af4,uVar8,(char)param_1[0xf]);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar21 = 0;
    uVar20 = 2;
    uVar19 = 0xff;
    uVar18 = 0;
    PeekPacketChecksumBool(0,uVar8,0xff,2,0);
    FUN_00431d90((char)param_1[0xf],7,0,uVar18,uVar8,uVar19,uVar20,uVar21);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar9 = (int *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = g_clientContext;
  iStack_ad8 = param_1[2];
  uStack_aec = uVar8;
  local_ae4 = piVar9;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar6 == 4) {
    puStack_b04 = operator_new(0x3fbc);
    puStack_8 = (undefined1 *)0x0;
    apuStack_ae0[0] = puStack_b04;
    if (puStack_b04 == (undefined4 *)0x0) {
      puStack_b04 = (undefined4 *)0x0;
    }
    else {
      InitProjectile(puStack_b04,0x186a9);
      *puStack_b04 = &PTR_FUN_0055658c;
      puStack_b04[0xfe7] = 0xffffffff;
    }
    puStack_8 = (undefined1 *)0xffffffff;
    iVar6 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar13 = *(uint *)(iVar6 + 4);
    while (uVar13 < 0x186ab) {
      if (uVar13 == 0x186aa) {
        piVar9 = *(int **)(iVar6 + 0x10);
        bVar17 = true;
        if (piVar9[2] == 0) goto LAB_00474a15;
        break;
      }
      iVar6 = *(int *)(iVar6 + 0x1c);
      uVar13 = *(uint *)(iVar6 + 4);
    }
  }
  goto LAB_00474d7e;
  while( true ) {
    piVar9 = (int *)piVar9[4];
    bVar17 = piVar9[2] == 0;
    if (!bVar17) break;
LAB_00474a15:
    if (bVar17) {
      apuStack_ae0[0] = (undefined4 *)piVar9[0xf];
      iVar6 = piVar9[0xe];
      iVar10 = CalculateAngleFromDelta();
      iVar11 = FloatToInt64();
      iVar12 = FloatToInt64();
      iVar12 = (int)apuStack_ae0[0] - iVar12;
      (**(code **)(*piVar9 + 4))(&DAT_00553b90);
      piVar9[0x11] = iVar10;
      apuStack_ae0[0] = (undefined4 *)(&DAT_006a7f74 + iVar5);
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
        FUN_004262d0(iStack_ad8 + 0x10,auStack_ac4);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar8 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = param_1[0xfe5];
        uVar21 = 0;
        uVar20 = 0xff;
        uVar19 = 100;
        uVar18 = 0;
        PeekPacketChecksumBool(uVar8,0,100,0xff,iVar5,0);
        FUN_00432320((char)param_1[0xf],1,1,uVar8,uVar18,uVar19,uVar20,iVar5,uVar21);
        puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),3);
        ScrubChecksumGuard();
LAB_00474cdd:
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        cVar4 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&uStack_aec,&local_ae4,2,1,1);
        if (cVar4 != '\0') {
          uStack_8a4 = 0;
          iStack_ab0 = 0;
          EncodeOutgoingPacketField(0);
          puStack_8 = (undefined1 *)0x1;
          uStack_680 = 0;
          uStack_88c = 0;
          EncodeOutgoingPacketField(0);
          SUBFIELD(puStack_8,0,undefined1) = 2;
          QueueOutgoingPacketField(uStack_aec);
          QueueOutgoingPacketField(local_ae4);
          FUN_004262d0(iStack_ad8 + 0x10,auStack_8a0);
          iVar5 = param_1[0xfe5];
          uVar21 = 0;
          uVar20 = 0xff;
          uVar19 = 100;
          uVar18 = 0;
          PeekChecksumStateUnderLock(auStack_8a0);
          uVar8 = PeekChecksumStateUnderLock(auStack_ac4);
          PeekPacketChecksumBool(uVar8,uVar18,uVar19,uVar20,iVar5,uVar21);
          FUN_00432320((char)param_1[0xf],1,1,uVar8,uVar18,uVar19,uVar20,iVar5,uVar21);
          puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
          ScrubChecksumGuard();
          goto LAB_00474cdd;
        }
      }
      puStack_b04[0xfea] = iVar6 - iVar11;
      puStack_b04[0xfeb] = iVar12;
      puStack_b04[0xfec] = uStack_aec;
      puStack_b04[0xfed] = local_ae4;
      puStack_b04[0xfee] = iVar10;
      uVar8 = FUN_004ac4d0();
      puStack_b04[0xfe9] = uVar8;
      iVar5 = FUN_004ac400();
      puStack_b04[0xfe8] = iVar5 * param_1[0xfe5];
      cVar4 = PeekPacketChecksumBool();
      if (cVar4 == '\0') {
        RegisterActiveObject();
      }
      else {
        (**(code **)*puStack_b04)(1);
      }
      break;
    }
  }
LAB_00474d7e:
  *(undefined1 *)(piStack_ae8 + 5) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar18 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_ae0[0] = (undefined4 *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar19 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar20 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar21 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_ae4 = (int *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uStack_aec = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iStack_ad8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  ApplyCraterExcavation(uStack_aec,local_ae4,uVar21,uVar20,uVar19,apuStack_ae0[0],uVar18,uVar8);
  RebuildTerrainColumnCache(&DAT_006a7708 + g_clientContext);
  uStack_ad4 = 0;
  uStack_ad0 = 0;
  uStack_acc = 5;
  uStack_ac8 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar9 = piStack_ae8;
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_ae0[0] = (undefined4 *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00450eb0(apuStack_ae0[0],uVar8,piVar9,1,1,&uStack_ad4);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar18 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00436ac0(uVar18,uVar8);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_ae0[0] = (undefined4 *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004372f0(piVar9[2] + 1,apuStack_ae0[0],uVar8,piVar9[0xe25],piVar9 + 0xe26);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar18 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar19 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00437150(uVar19,uVar18,0x3c,uVar8);
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
    AcquireSoundChannel(0);
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
  cVar4 = CheckGuardedBoolAnd(iVar5 < iVar6);
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
    if (iVar5 < 1) goto LAB_00475202;
LAB_0047524e:
    cVar4 = PeekPacketChecksumBool();
    if (cVar4 == '\0') {
      SetGuardedBool(1);
    }
  }
  else {
LAB_00475202:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar5) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar5 < 0) goto LAB_0047524e;
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar6 <= iVar5) ||
     (cVar4 = CompareChecksumPair(piStack_ae8 + 0xed2,piStack_ae8 + 0xf5b), cVar4 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar5 <= iVar6) ||
       ((cVar4 = CompareChecksumExceeds(piStack_ae8 + 0xed2,piStack_ae8 + 0xf5b), cVar4 == '\0' ||
        (piStack_ae8[0xed1] < 6)))) goto LAB_00475974;
  }
  iVar5 = g_clientContext;
  pbVar16 = (byte *)(g_clientContext + 0x62143);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *pbVar16 = (byte)iVar6;
  iVar6 = _rand();
  bVar1 = *pbVar16;
  *(byte *)(iVar5 + 0x62144) = (byte)iVar6;
  bVar15 = '\x01' << (bVar1 & 7);
  bVar15 = ~bVar15 & (byte)iVar6 | bVar15;
  *(byte *)(iVar5 + 0x62144) = bVar15;
  *(byte *)(iVar5 + 0x62145) = bVar1 + bVar15 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
LAB_00475974:
  *unaff_FS_OFFSET = uStack_10;
  return;
}

