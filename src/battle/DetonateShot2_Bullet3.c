/* DetonateShot2_Bullet3 - 0x00494910 in the original binary.
 *
 * RENAMED (2026-08-16, from FUN_00494910): CProjectile virtual slot 6
 * (DetonateProjectile, base impl 0x4572b0) override for mobile type 2's
 * shot 2 (weapon index 1, texture bullet3s); vtable 0x5563a8, ctor
 * InitShot2_Bullet3 reached only through SpawnPrimaryShot's case 2. Type/role
 * CONFIRMED via vtable geometry (tools/projectile_class_map.py); the
 * mobile NAME is not confirmable (no mobile-type->name map in the repo).
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-11): recovered the guard-cell pointer at all
 * 56 argless PeekPacketChecksumState() calls and all 10 one-argument
 * EncodeOutgoingPacketField(value) calls, per tools/guard_worklist.json
 * and a full read of the original disasm 0x494910-0x495c1a (the decompile
 * is goto-shuffled: the PeekPacketChecksumBool branch at 0x4949c2 jumps
 * to 0x495621 for the C lines-74..262 arm, so sites were matched by
 * landmarks, not line order). Bases: ebx = param_1 on entry, reloaded
 * from [esp+0x30] (piStack_ad8) at 0x49503e/0x49537a/0x495695/0x495718;
 * edi/eax lea forms verified per site. The two Peeks after each
 * EncodeChecksumDeltaShr use that helper's RETURNED cell (chained-return
 * pattern, 0x495631/0x4956ac mov edi,eax), captured in iVar5.
 * Cells confirmed at 0xe55ab8/0x7949c8/0x796aa0 globals,
 * g_clientContext+0xebcbc/+0x5b85c/+0x621e8, and object offsets
 * (x4): +0x10/+0x99/+0x122/+0x1ab/+0x234/+0x3d5/+0x45e/+0x570/+0x5f9/
 * +0x930..+0xbdd (6-cell 0x224-stride array)/+0xe48/+0xed2.
 */
#include "ghidra_types.h"


void __fastcall DetonateShot2_Bullet3(int *param_1)

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
  undefined4 *puStack_af4;
  int local_ae8;
  undefined4 uStack_adc;
  int *piStack_ad8;
  int *local_ad4;
  int iImpactX;
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
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005401f3;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_ad4 = param_1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x10));
  iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x122));
  EncodeOutgoingPacketField((void *)(param_1 + 0x10),iVar6 + iVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x99));
  iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x1ab));
  EncodeOutgoingPacketField((void *)(param_1 + 0x99),iVar6 + iVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar4 = PeekPacketChecksumBool((byte *)param_1 + 0xf45);
  if (cVar4 == '\0') {
    iVar5 = EncodeChecksumDeltaShr(param_1 + 0x10,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x5;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)iVar5);
    EncodeOutgoingPacketField((void *)(param_1 + 0x3d5),uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_ab0 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(apuStack_ad0);
      param_1 = piStack_ad8;
    }
    iVar5 = EncodeChecksumDeltaShr(param_1 + 0x99,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x6;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)iVar5);
    EncodeOutgoingPacketField((void *)(param_1 + 0x45e),uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0xffffffff;
    piVar9 = param_1;
    if (iStack_ab0 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(apuStack_ad0);
      piVar9 = piStack_ad8;
    }
    cVar4 = CheckGuardedBoolAnd(piVar9[0x3d2] != 0);
    if (cVar4 == '\0') {
      if ((char)piVar9[0xfe7] == '\0') {
        EmitChecksumSum(piVar9 + 0x122, piVar9 + 0x2bd);
        EmitChecksumSum(piVar9 + 0x1ab, piVar9 + 0x346);
      }
      else {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = PeekPacketChecksumState((void *)&DAT_00796aa0);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        SubFromPacketChecksum(piVar9 + 0x1ab, (int)(0xc400 / (longlong)iVar5));
      }
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar13 = PeekPacketChecksumState((void *)(piVar9 + 0x122));
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
      uVar8 = EncodeChecksumDeltaDiv(piVar9[0x3d2] + 0x25c,auStack_67c,4);
      puStack_8 = (undefined1 *)0x7;
      uVar8 = EncodeChecksumPairDiff(piVar9[0x3d2] + 0x38,auStack_458,uVar8);
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
        if (cVar4 != '\0') goto LAB_0049585a;
      }
      else {
LAB_0049585a:
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
          SetGuardedBool(0,GB_GUARD_UNRECOVERED);
        }
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(piVar9 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar5 < 0) {
LAB_00495a52:
      *(undefined1 *)(piVar9 + 5) = 1;
      cVar4 = PeekPacketChecksumBool((byte *)param_1 + 0xf3f);
      if ((cVar4 != '\0') && (cVar4 = InitChecksumSeed(), cVar4 == '\0')) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField((void *)(g_clientContext + 0x621e8),0x19);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
    }
    else {
      iVar5 = *(int *)(&g_nCameraBoundX + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState((void *)(piVar9 + 0x3d5));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (((iVar5 <= iVar6) ||
          (cVar4 = PacketChecksumGreaterEqual(param_1 + 0x45e,*(undefined4 *)(&g_nCameraBoundY + g_clientContext)),
          cVar4 != '\0')) || (cVar4 = PacketChecksumLessThan(param_1 + 0x45e,0xfffffc18), cVar4 != '\0'))
      goto LAB_00495a52;
    }
    cVar4 = CheckBothGuardedBools();
    if (cVar4 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x45e));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar10 = PeekPacketChecksumState((void *)(piVar9 + 0x3d5));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = g_clientContext;
      piVar9 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar4 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
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
    goto LAB_00495c02;
  }
  SyncOutgoingChecksumField(param_1 + 0x3d5, param_1[2],param_1 + 0x45e);
  cVar4 = PeekPacketChecksumBool((byte *)param_1 + 0x3918);
  if (cVar4 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((-1 < iVar5) && (iVar5 < *(int *)(&g_nCameraBoundX + g_clientContext))) {
      pcVar7 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar5);
      puStack_af4 = (undefined4 *)0x0;
      if (0 < *(int *)(&g_nCameraBoundY + g_clientContext)) {
        do {
          if (*pcVar7 != '\0') goto LAB_00494a5a;
          pcVar7 = pcVar7 + *(int *)(&g_nCameraBoundX + g_clientContext);
          puStack_af4 = (undefined4 *)((int)puStack_af4 + 1);
        } while ((int)puStack_af4 < *(int *)(&g_nCameraBoundY + g_clientContext));
      }
    }
    puStack_af4 = (undefined4 *)0x2710;
LAB_00494a5a:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,uVar8,puStack_af4);
    local_ae8 = 1;
    if (0 < param_1[0xfe5]) {
      local_ae8 = param_1[0xfe5];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_ad4 = (int *)PeekPacketChecksumState((void *)&DAT_007949c8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_adc = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    ApplyBlastDamage(uStack_adc,puStack_af4,0,local_ad4,iVar5 / local_ae8,uVar8,(char)param_1[0xf]);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x5f9));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iImpactX = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar21 = 0;
    uVar20 = 2;
    uVar19 = 0xff;
    uVar18 = 0;
    PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
    SpawnBlastEffect(puStack_af4,iImpactX,(char)param_1[0xf],7,0,uVar18,uVar8,uVar19,uVar20,uVar21);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar9 = (int *)PeekPacketChecksumState((void *)(param_1 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = g_clientContext;
  iStack_ac8 = param_1[2];
  uStack_adc = uVar8;
  local_ad4 = piVar9;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState((void *)(g_clientContext + 0xebcbc));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar6 == 4) {
    puStack_af4 = operator_new(0x3fbc);
    puStack_8 = (undefined1 *)0x0;
    apuStack_ad0[0] = puStack_af4;
    if (puStack_af4 == (undefined4 *)0x0) {
      puStack_af4 = (undefined4 *)0x0;
    }
    else {
      InitProjectile(puStack_af4,0x186a9);
      *puStack_af4 = &PTR_FUN_0055658c;
      puStack_af4[0xfe7] = 0xffffffff;
    }
    puStack_8 = (undefined1 *)0xffffffff;
    iVar6 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar13 = *(uint *)(iVar6 + 4);
    while (uVar13 < 0x186ab) {
      if (uVar13 == 0x186aa) {
        piVar9 = *(int **)(iVar6 + 0x10);
        bVar17 = true;
        if (piVar9[2] == 0) goto LAB_00494cd5;
        break;
      }
      iVar6 = *(int *)(iVar6 + 0x1c);
      uVar13 = *(uint *)(iVar6 + 4);
    }
  }
  goto LAB_0049503e;
  while( true ) {
    piVar9 = (int *)piVar9[4];
    bVar17 = piVar9[2] == 0;
    if (!bVar17) break;
LAB_00494cd5:
    if (bVar17) {
      apuStack_ad0[0] = (undefined4 *)piVar9[0xf];
      iVar6 = piVar9[0xe];
      iVar10 = CalculateAngleFromDelta();
      iVar11 = FloatToInt64();
      iVar12 = FloatToInt64();
      iVar12 = (int)apuStack_ad0[0] - iVar12;
      (**(code **)(*piVar9 + 4))(&DAT_00553b90);
      piVar9[0x11] = iVar10;
      apuStack_ad0[0] = (undefined4 *)(&DAT_006a7f74 + iVar5);
      cVar4 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
      if (cVar4 == '\0') {
        uStack_680 = 0;
        uStack_88c = 0;
        EncodeOutgoingPacketField((void *)auStack_8a0,0);
        puStack_8 = (undefined1 *)0x3;
        uStack_8a4 = 0;
        iStack_ab0 = 0;
        EncodeOutgoingPacketField((void *)auStack_ac4,0);
        SUBFIELD(puStack_8,0,undefined1) = 4;
        SyncOutgoingChecksumField(auStack_8a0, iStack_ac8 + 0x10,auStack_ac4);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState((void *)auStack_ac4);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar8 = PeekPacketChecksumState((void *)auStack_8a0);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = param_1[0xfe5];
        uVar21 = 0;
        uVar20 = 0xff;
        uVar19 = 100;
        uVar18 = 0;
        PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
        FUN_00432320((char)param_1[0xf],1,1,uVar8,uVar18,uVar19,uVar20,iVar5,uVar21);
        puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),3);
        ScrubChecksumGuard();
LAB_00494f9d:
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        cVar4 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&uStack_adc,&local_ad4,2,1,1);
        if (cVar4 != '\0') {
          uStack_8a4 = 0;
          iStack_ab0 = 0;
          EncodeOutgoingPacketField((void *)auStack_ac4,0);
          puStack_8 = (undefined1 *)0x1;
          uStack_680 = 0;
          uStack_88c = 0;
          EncodeOutgoingPacketField((void *)auStack_8a0,0);
          SUBFIELD(puStack_8,0,undefined1) = 2;
          QueueOutgoingPacketField(uStack_adc);
          QueueOutgoingPacketField(local_ad4);
          SyncOutgoingChecksumField(auStack_ac4, iStack_ac8 + 0x10,auStack_8a0);
          iVar5 = param_1[0xfe5];
          uVar21 = 0;
          uVar20 = 0xff;
          uVar19 = 100;
          uVar18 = 0;
          PeekChecksumStateUnderLock(auStack_8a0);
          uVar8 = PeekChecksumStateUnderLock(auStack_ac4);
          PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
          FUN_00432320((char)param_1[0xf],1,1,uVar8,uVar18,uVar19,uVar20,iVar5,uVar21);
          puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
          ScrubChecksumGuard();
          goto LAB_00494f9d;
        }
      }
      puStack_af4[0xfea] = iVar6 - iVar11;
      puStack_af4[0xfeb] = iVar12;
      puStack_af4[0xfec] = uStack_adc;
      puStack_af4[0xfed] = local_ad4;
      puStack_af4[0xfee] = iVar10;
      /* FIXED (2026-07-15): dropped self arg - angr-confirmed EDI==piVar9
       * (the traversal pointer set by piVar9=piVar9[4] above and never
       * reassigned before this point) at the real 0x494fe9/0x494ffa calls. */
      uVar8 = FUN_004ac4d0(piVar9);
      puStack_af4[0xfe9] = uVar8;
      iVar5 = FUN_004ac400(piVar9);
      puStack_af4[0xfe8] = iVar5 * param_1[0xfe5];
      /* guard-cell: proven - the ctx+0x6a7f70 spill/fold chain; see the
       * fold-dominance proof in commit dc092b4^..'s successor (lea
       * REG,[ctx+0x6a7f70] -> slot, +4 fold -> slot, this peek reads it
       * with no interposed writer and no bypass edge). */
      cVar4 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
      if (cVar4 == '\0') {
        RegisterActiveObject(0, 0, (undefined4 *)0);
      }
      else {
        (**(code **)*puStack_af4)(1);
      }
      break;
    }
  }
LAB_0049503e:
  *(undefined1 *)(piStack_ad8 + 5) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x1ab));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar18 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x122));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_ad0[0] = (undefined4 *)PeekPacketChecksumState((void *)(piStack_ad8 + 0xbdd));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar19 = PeekPacketChecksumState((void *)(piStack_ad8 + 0xb54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar20 = PeekPacketChecksumState((void *)(piStack_ad8 + 0xacb));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar21 = PeekPacketChecksumState((void *)(piStack_ad8 + 0xa42));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_ad4 = (int *)PeekPacketChecksumState((void *)(piStack_ad8 + 0x9b9));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uStack_adc = PeekPacketChecksumState((void *)(piStack_ad8 + 0x930));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iStack_ac8 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState((void *)(piStack_ad8 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  ApplyCraterExcavation(uStack_adc,local_ad4,uVar21,uVar20,uVar19,apuStack_ad0[0],uVar18,uVar8);
  RebuildTerrainColumnCache(&DAT_006a7708 + g_clientContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar9 = piStack_ad8;
  uVar8 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_ad0[0] = (undefined4 *)PeekPacketChecksumState((void *)(piStack_ad8 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00450eb0(apuStack_ad0[0],uVar8,piVar9,1,0,0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar18 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00436ac0(uVar18,uVar8);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_ad0[0] = (undefined4 *)PeekPacketChecksumState((void *)(piStack_ad8 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  SpawnFlameEffect(piVar9[2],apuStack_ad0[0],uVar8,piVar9[0xe25],piVar9 + 0xe26);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x570));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar18 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar19 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00437150(uVar19,uVar18,0x3c,uVar8);
  iVar5 = g_clientContext;
  cVar4 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
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
  cVar4 = PeekPacketChecksumBool((byte *)param_1 + 0xf3f);
  if ((cVar4 != '\0') && (cVar4 = InitChecksumSeed(), cVar4 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)&DAT_007949c8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    QueueOutgoingPacketField(uVar8);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0x5b85c));
  iVar6 = PeekPacketChecksumState((void *)(piStack_ad8 + 0xe48));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar4 = CheckGuardedBoolAnd(iVar5 < iVar6);
  if (cVar4 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(piStack_ad8 + 0xe48));
    EncodeOutgoingPacketField((void *)(g_clientContext + 0x5b85c),uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x234));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar5 < 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x122));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar5 < 1) goto LAB_004954a4;
LAB_004954f0:
    cVar4 = PeekPacketChecksumBool((byte *)param_1 + 0xf4c);
    if (cVar4 == '\0') {
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
  }
  else {
LAB_004954a4:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x234));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar5) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x122));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar5 < 0) goto LAB_004954f0;
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x3d5));
  iVar6 = PeekPacketChecksumState((void *)(piStack_ad8 + 0xed2));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar6 <= iVar5) ||
     (cVar4 = CompareChecksumPair(piStack_ad8 + 0xed2,piStack_ad8 + 0xf5b), cVar4 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x3d5));
    iVar6 = PeekPacketChecksumState((void *)(piStack_ad8 + 0xed2));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar5 <= iVar6) ||
       ((cVar4 = CompareChecksumExceeds(piStack_ad8 + 0xed2,piStack_ad8 + 0xf5b), cVar4 == '\0' ||
        (piStack_ad8[0xed1] < 6)))) goto LAB_00495c02;
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
LAB_00495c02:
  *unaff_FS_OFFSET = uStack_10;
  return;
}

