/* DetonateSuperShot_Bullet16 - 0x00467a70 in the original binary.
 *
 * RENAMED (2026-08-16, from FUN_00467a70): CProjectile virtual slot 6
 * (DetonateProjectile, base impl 0x4572b0) override for mobile type 15's
 * super shot (texture bullet16p; vtable 0x555d74, ctor FUN_00467a50
 * reached only through SpawnSuperShot's case 15). Type/role CONFIRMED via
 * vtable geometry (tools/projectile_class_map.py); the mobile NAME is not
 * confirmable (no mobile-type->name map in the repo).
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at 30 of the 31 argless PeekPacketChecksumState() calls and the 5
 * 1-arg EncodeOutgoingPacketField() calls (worklist 31/5).  Third member
 * of the DetonateShot1_Bullet7 / FUN_004aafd0 family: this=ESI, projectile cells
 * param_1+0x10/0x99/0x122/0x1ab/0x234/0x3d5/0x45e/0x5f9/0xe48/0xed2,
 * globals 0xe55ab8/0x7949c8, g_clientContext+0x5b85c (a guarded cell
 * POINTER whose peek result iVar7 is the cell the following Encode
 * writes, 0x467dea via frame[0x14]).  The two discarded
 * EncodeChecksumDeltaShr results (0x467fd0/0x46804d) are captured in
 * pvDelta; the X/Y cell pointers in frame[0x20]/frame[0x1c] (0x46833d /
 * 0x46806a) feed the tail peeks 0x468440/0x468459.  The remaining site
 * (line ~324, 0x467d37) reads the global cell 0x7a7690 - the same fifth
 * guard global FUN_00499ef0 hits.  CLOSED 2026-08-16: that cell is now
 * declared as `uint8_t DAT_007a7690[0x224]` in globals.h/globals.c, so
 * this site takes its real cell too and the file is fully swept.
 */
#include "ghidra_types.h"


void __fastcall DetonateSuperShot_Bullet16(int *param_1)

{
  int *piVar1;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  char cVar6;
  void *pvDelta;
  int iVar7;
  int iVar8;
  char *pcVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  byte bVar15;
  uint uVar16;
  uint unaff_EBX;
  code *pcVar17;
  byte *pbVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  undefined4 uVar22;
  int iStack_adc;
  int *local_ad8;
  int iImpactX;
  int local_ad4 [2];
  int iStack_acc;
  undefined4 uStack_ac8;
  undefined1 auStack_ac4 [16];
  uint uStack_ab4;
  int iStack_ab0;
  undefined1 auStack_8a4 [548];
  undefined1 auStack_680 [548];
  undefined1 auStack_45c [548];
  undefined1 auStack_238 [552];
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;

  uStack_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped (handler body
   * LAB_0053d3b9 wasn't included in this function's own decompile;
   * same rationale as entry/InitGame.c - see src/README.md). uStack_c
   * and puStack_8 are real, separate locals reused elsewhere in this
   * function (an exception-cleanup index and a tri-state flag,
   * respectively) despite the SEH-typical names - kept as-is. */
  local_ad8 = (int *)0x0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState((void *)(param_1 + 0x10));
  iVar8 = PeekPacketChecksumState((void *)(param_1 + 0x122));
  EncodeOutgoingPacketField((void *)(param_1 + 0x10), iVar8 + iVar7);
  pcVar17 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_ad4[0] = PeekPacketChecksumState((void *)(param_1 + 0x99));
  iVar7 = PeekPacketChecksumState((void *)(param_1 + 0x1ab));
  EncodeOutgoingPacketField((void *)(param_1 + 0x99), iVar7 + local_ad4[0]);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar6 = PeekPacketChecksumBool((byte *)param_1 + 0xf45);
  if (cVar6 == '\0') {
    pvDelta = EncodeChecksumDeltaShr(param_1 + 0x10,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState((void *)(pvDelta));
    EncodeOutgoingPacketField((void *)(param_1 + 0x3d5), uVar10);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_ab0 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_ad4);
      pcVar17 = (code *)LeaveCriticalSection;
    }
    pvDelta = EncodeChecksumDeltaShr(param_1 + 0x99,auStack_ac4,8);
    local_ad8 = param_1 + 0x45e;
    puStack_8 = (undefined1 *)0x1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState((void *)(pvDelta));
    EncodeOutgoingPacketField((void *)(param_1 + 0x45e), uVar10);
    (*pcVar17)(&DAT_005a9068);
    uStack_c = 0xffffffff;
    if (uStack_ab4 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&local_ad8);
      pcVar17 = (code *)LeaveCriticalSection;
      unaff_EBX = uStack_ab4;
    }
    cVar6 = CheckGuardedBoolAnd(param_1[0x3d2] != 0);
    if (cVar6 == '\0') {
      EmitChecksumSum(param_1 + 0x122, param_1 + 0x2bd);
      EmitChecksumSum(param_1 + 0x1ab, param_1 + 0x346);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      unaff_EBX = PeekPacketChecksumState((void *)(param_1 + 0x122));
      (*pcVar17)(&DAT_005a9068);
      if ((int)((unaff_EBX ^ (int)unaff_EBX >> 0x1f) - ((int)unaff_EBX >> 0x1f)) < 200) {
        cVar6 = PacketChecksumLessThan(param_1 + 0x122,0);
        if (cVar6 == '\0') {
          uVar10 = 200;
        }
        else {
          uVar10 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar10);
      }
      uVar10 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_680,4);
      uStack_c = 2;
      uVar10 = EncodeChecksumPairDiff(param_1[0x3d2] + 0x38,auStack_45c,uVar10);
      uStack_c = 3;
      bVar4 = false;
      bVar3 = false;
      cVar6 = CompareChecksumPair(param_1 + 0x3d5,uVar10);
      if (cVar6 == '\0') {
        uVar10 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_8a4,4);
        uStack_c = 4;
        uVar10 = EncodeChecksumPairSum(param_1[0x3d2] + 0x38,&uStack_ac8,uVar10);
        uStack_c = 5;
        bVar4 = true;
        bVar3 = true;
        cVar6 = CompareChecksumPair(uVar10,param_1 + 0x3d5);
        bVar5 = false;
        if (cVar6 != '\0') goto LAB_00468200;
      }
      else {
LAB_00468200:
        bVar5 = true;
      }
      uStack_c = 4;
      if (bVar3) {
        ScrubChecksumGuard();
      }
      uStack_c = 3;
      if (bVar4) {
        ScrubChecksumGuard();
      }
      uStack_c = 2;
      ScrubChecksumGuard();
      uStack_c = 0xffffffff;
      ScrubChecksumGuard();
      if (bVar5) {
        iVar7 = param_1[0x3d4];
        param_1[0x3d4] = iVar7 + 1;
        if (iVar7 + 1 < 3) {
          uVar10 = EncodeChecksumNegate(param_1 + 0x122,auStack_238);
          uStack_c = 6;
          EncodeChecksumState(uVar10);
          uStack_c = 0xffffffff;
          ScrubChecksumGuard();
        }
        else {
          SetGuardedBool(0,GB_GUARD_UNRECOVERED);
        }
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_ad8 = param_1 + 0x3d5;
    PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    (*pcVar17)(&DAT_005a9068);
    if ((char)(unaff_EBX >> 0x18) == '\0') {
      iVar7 = *(int *)(&g_nCameraBoundX + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
      (*pcVar17)(&DAT_005a9068);
      piVar1 = local_ad8;
      if (((iVar7 <= iVar8) ||
          (cVar6 = PacketChecksumGreaterEqual(local_ad8,*(undefined4 *)(&g_nCameraBoundY + g_clientContext)),
          cVar6 != '\0')) || (cVar6 = PacketChecksumLessThan(piVar1,0xfffffc18), cVar6 != '\0'))
      goto LAB_004683bc;
    }
    else {
LAB_004683bc:
      *(undefined1 *)(param_1 + 5) = 1;
      cVar6 = PeekPacketChecksumBool((byte *)param_1 + 0xf3f);
      if ((cVar6 != '\0') && (cVar6 = InitChecksumSeed(), cVar6 == '\0')) {
        iVar7 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
        if ((iVar7 == 5) || (uVar10 = 2, iVar7 == 6)) {
          uVar10 = 0x19;
        }
        QueueOutgoingPacketField(uVar10);
        iVar7 = g_clientContext;
        *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar7) = 0;
      }
    }
    cVar6 = CheckBothGuardedBools();
    if (cVar6 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = PeekPacketChecksumState((void *)(param_1 + 0x45e));
      (*pcVar17)(&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar11 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
      (*pcVar17)(&DAT_005a9068);
      iVar7 = g_clientContext;
      piVar1 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar6 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
      if ((cVar6 == '\0') && ((&DAT_006a7758)[iVar7] != '\0')) {
        if (((&DAT_006a7736)[iVar7] == '\x01') &&
           ((uVar16 = iVar8 - *(int *)(&g_nCameraY + iVar7) >> 0x1f,
            200 < (int)((iVar8 - *(int *)(&g_nCameraY + iVar7) ^ uVar16) - uVar16) ||
            (uVar16 = iVar11 - *(int *)(&g_nCameraX + iVar7) >> 0x1f,
            300 < (int)((iVar11 - *(int *)(&g_nCameraX + iVar7) ^ uVar16) - uVar16))))) {
          (&DAT_006a7736)[iVar7] = 0;
        }
        iVar13 = 400;
        if (399 < iVar11) {
          iVar13 = iVar11;
        }
        iVar12 = *(int *)(&g_nCameraBoundX + iVar7) + -400;
        if ((iVar13 <= iVar12) && (iVar12 = iVar11, iVar11 < 400)) {
          iVar12 = 400;
        }
        iVar11 = -0x14;
        if (-0x15 < iVar8) {
          iVar11 = iVar8;
        }
        iVar13 = *(int *)(&g_nCameraBoundY + iVar7) + -0x104;
        if ((iVar11 <= iVar13) && (iVar13 = -0x14, -0x15 < iVar8)) {
          iVar13 = iVar8;
        }
        iVar8 = *piVar1 - iVar12;
        *(int *)(&g_nCameraScrollY + iVar7) = iVar13;
        if (((*(int *)(&DAT_006a770c + iVar7) - iVar13) * (*(int *)(&DAT_006a770c + iVar7) - iVar13)
             + iVar8 * iVar8 < 40000) &&
           (((&DAT_006a7734)[iVar7] == '\x01' || ((&DAT_006a7f6c)[iVar7] == '\0')))) {
          *(int *)(&g_nCameraX + iVar7) = iVar12;
          *piVar1 = iVar12;
          *(int *)(&g_nCameraY + iVar7) = iVar13;
          *(int *)(&DAT_006a770c + iVar7) = iVar13;
        }
        if ((((&DAT_006a7734)[iVar7] == '\0') && ((&DAT_006a7f6c)[iVar7] == '\x01')) &&
           ((&DAT_006a7736)[iVar7] == '\0')) {
          iVar8 = *(int *)(&DAT_006a7730 + iVar7);
          iVar11 = iVar8;
          if (iVar12 <= iVar8) {
            iVar11 = iVar12;
          }
          iVar14 = *(int *)(&DAT_006a772c + iVar7);
          if ((iVar14 <= iVar11) && (iVar14 = iVar8, iVar12 <= iVar8)) {
            iVar14 = iVar12;
          }
          *(int *)(&g_nCameraScrollX + iVar7) = iVar14;
        }
        if ((&DAT_006a7734)[iVar7] == '\x01') {
          *(int *)(&g_nCameraScrollX + iVar7) = iVar12;
          *(int *)(&g_nCameraScrollY + iVar7) = iVar13;
        }
      }
    }
    goto LAB_00468593;
  }
  SyncOutgoingChecksumField(param_1 + 0x3d5, param_1[2],param_1 + 0x45e);
  cVar6 = PeekPacketChecksumBool((byte *)param_1 + 0x3918);
  if (cVar6 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((-1 < iVar7) &&
       (local_ad8 = *(int **)(&g_nCameraBoundX + g_clientContext), iVar7 < (int)local_ad8)) {
      pcVar9 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar7);
      iStack_adc = 0;
      if (0 < *(int *)(&g_nCameraBoundY + g_clientContext)) {
        do {
          if (*pcVar9 != '\0') goto LAB_00467bba;
          pcVar9 = pcVar9 + (int)local_ad8;
          iStack_adc = iStack_adc + 1;
        } while (iStack_adc < *(int *)(&g_nCameraBoundY + g_clientContext));
      }
    }
    iStack_adc = 10000;
LAB_00467bba:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_ad8 = (int *)PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,local_ad8,iStack_adc);
    local_ad8 = (int *)0x1;
    if (0 < param_1[0xfe5]) {
      local_ad8 = (int *)param_1[0xfe5];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_ac8 = PeekPacketChecksumState((void *)(&DAT_00e55ab8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iStack_acc = PeekPacketChecksumState((void *)(&DAT_00e55ab8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_ad4[0] = PeekPacketChecksumState((void *)(&DAT_007949c8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0043af40(uVar10,iStack_adc,0,local_ad4[0],iStack_acc / (int)local_ad8,uStack_ac8,
                 (char)param_1[0xf]);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState((void *)(param_1 + 0x5f9));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iImpactX = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar22 = 0;
    uVar21 = 2;
    uVar20 = 0xff;
    uVar19 = 0;
    PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
    FUN_00431d90(iStack_adc,iImpactX,(char)param_1[0xf],7,0,uVar19,uVar10,uVar20,uVar21,uVar22);
  }
  *(undefined1 *)(param_1 + 5) = 1;
  (**(code **)(*param_1 + 0x20))();
  cVar6 = PeekPacketChecksumBool();
  if ((cVar6 != '\0') && (cVar6 = InitChecksumSeed(), cVar6 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState((void *)(&DAT_007a7690));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    QueueOutgoingPacketField(uVar10);
    iVar7 = g_clientContext;
    *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
    *(undefined4 *)(&DAT_005f376c + iVar7) = 0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState((void *)(g_clientContext + 0x5b85c));
  iVar8 = PeekPacketChecksumState((void *)(param_1 + 0xe48));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar6 = CheckGuardedBoolAnd(iVar7 < iVar8);
  if (cVar6 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState((void *)(param_1 + 0xe48));
    EncodeOutgoingPacketField((void *)(iVar7), uVar10);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState((void *)(param_1 + 0x234));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar7 < 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState((void *)(param_1 + 0x122));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar7 < 1) goto LAB_00467e48;
LAB_00467e94:
    cVar6 = PeekPacketChecksumBool((byte *)param_1 + 0xf4c);
    if (cVar6 == '\0') {
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
  }
  else {
LAB_00467e48:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState((void *)(param_1 + 0x234));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar7) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = PeekPacketChecksumState((void *)(param_1 + 0x122));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar7 < 0) goto LAB_00467e94;
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
  iVar8 = PeekPacketChecksumState((void *)(param_1 + 0xed2));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar8 <= iVar7) || (cVar6 = CompareChecksumPair(param_1 + 0xed2,param_1 + 0xf5b), cVar6 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    iVar8 = PeekPacketChecksumState((void *)(param_1 + 0xed2));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar7 <= iVar8) ||
       ((cVar6 = CompareChecksumExceeds(param_1 + 0xed2,param_1 + 0xf5b), cVar6 == '\0' ||
        (param_1[0xed1] < 6)))) goto LAB_00468593;
  }
  iVar7 = g_clientContext;
  pbVar18 = (byte *)(g_clientContext + 0x62143);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = _rand();
  *pbVar18 = (byte)iVar8;
  iVar8 = _rand();
  bVar2 = *pbVar18;
  *(byte *)(iVar7 + 0x62144) = (byte)iVar8;
  bVar15 = '\x01' << (bVar2 & 7);
  bVar2 = *pbVar18;
  bVar15 = ~bVar15 & (byte)iVar8 | bVar15;
  *(byte *)(iVar7 + 0x62144) = bVar15;
  *(byte *)(iVar7 + 0x62145) = bVar15 + bVar2 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
LAB_00468593:
  return;
}

