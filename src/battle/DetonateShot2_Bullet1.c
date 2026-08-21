/* DetonateShot2_Bullet1 - 0x004688b0 in the original binary.
 *
 * RENAMED (2026-08-16, from FUN_004688b0): CProjectile virtual slot 6
 * (DetonateProjectile, base impl 0x4572b0) override for mobile type 0's
 * shot 2 (weapon index 1, texture bullet1s); vtable 0x555dac, ctor
 * InitShot2_Bullet1 reached only through SpawnPrimaryShot's case 0. Type/role
 * CONFIRMED via vtable geometry (tools/projectile_class_map.py); the
 * mobile NAME is not confirmable (no mobile-type->name map in the repo).
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-11): CValueGuard sweep - recovered the
 * guard-cell pointers Ghidra dropped from all 85 argless
 * PeekPacketChecksumState and 18 one-arg EncodeOutgoingPacketField
 * calls, per tools/guard_worklist.json (status "clean" both families)
 * + disasm of 0x4688b0-0x46a494. `this` (ECX->EBX) is param_1; the
 * mid-function reloads of the saved-this slot [esp+0x20] are Ghidra's
 * piStack_ae8/piVar15 (value-identical to the entry param_1). Cells:
 * per-object guards at +0x40/+0x264/+0x488/+0x6ac/+0x8d0/+0xaf4/+0xd18/
 * +0xf54/+0x1178/+0x15c0/+0x17e4/+0x1e54/+0x2078/+0x229c/+0x24c0/
 * +0x26e4/+0x2908/+0x2b2c/+0x2d50/+0x2f74 (expressed as int-scaled
 * offsets), globals DAT_00e55ab8/DAT_007949c8/DAT_00e9ba40/
 * g_clientContext+0xebcbc/+0x621e8, and the stack guards auStack_ac4
 * ([esp+0x44]) / auStack_8a0 ([esp+0x268]). The six delta blocks and
 * the two EncodeChecksumDeltaShr blocks peek the helper's chained-
 * return cell, which the decompile discarded - captured in uVar19/
 * uVar17 (and uVar8 for EncodeChecksumPairDiff at 0x469fcd). Three
 * if/else bodies are laid out swapped vs the binary (the bool-gate
 * branches at 0x468d3b and 0x469edb), so all sites were mapped by
 * landmarks, not line order; spot-verified the full 8-arg crater
 * chain at 0x469125-0x469157, the 0x43af40 arg chain at 0x468ac9,
 * the 0x4372f0 [2]+1-vs-[2] discriminator (0x46927e vs 0x469731),
 * and delta blocks 1/2/6.
 */
#include "ghidra_types.h"


void __fastcall DetonateShot2_Bullet1(int *param_1)

{
  int iCraterX;
  byte bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  undefined4 uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  byte bVar14;
  int *piVar15;
  undefined4 *unaff_FS_OFFSET;
  bool bVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  undefined4 *local_aec;
  int *piStack_ae8;
  undefined4 local_ae4;
  undefined4 *apuStack_ae0 [2];
  int iStack_ad8;
  int iStack_ad4;
  int iStack_ad0;
  undefined4 uStack_acc;
  int iStack_ac8;
  undefined1 auStack_ac4 [20];
  int iStack_ab0;
  undefined1 uStack_8a4;
  undefined1 auStack_8a0 [20];
  int iStack_88c;
  undefined1 uStack_680;
  undefined1 auStack_67c [548];
  undefined1 auStack_458 [548];
  undefined1 auStack_234 [548];
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053ffd7;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x10));
  iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x122));
  EncodeOutgoingPacketField((void *)(param_1 + 0x10), iVar6 + iVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x99));
  iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x1ab));
  EncodeOutgoingPacketField((void *)(param_1 + 0x99), iVar6 + iVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar4 = PeekPacketChecksumBool((byte *)param_1 + 0xf45);
  if (cVar4 != '\0') {
    SyncOutgoingChecksumField(param_1 + 0x3d5, (uint)((char)param_1[0xfe7] != '\0') + param_1[2],param_1 + 0x45e);
    cVar4 = PeekPacketChecksumBool((byte *)param_1 + 0x3918);
    if (cVar4 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((-1 < iVar5) && (iVar5 < *(int *)(&g_nCameraBoundX + g_clientContext))) {
        pcVar7 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar5);
        local_aec = (undefined4 *)0x0;
        if (0 < *(int *)(&g_nCameraBoundY + g_clientContext)) {
          do {
            if (*pcVar7 != '\0') goto LAB_00468a0a;
            pcVar7 = pcVar7 + *(int *)(&g_nCameraBoundX + g_clientContext);
            local_aec = (undefined4 *)((int)local_aec + 1);
          } while ((int)local_aec < *(int *)(&g_nCameraBoundY + g_clientContext));
        }
      }
      local_aec = (undefined4 *)0x2710;
LAB_00468a0a:
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_00436070(&DAT_006a7f70 + g_clientContext,uVar8,local_aec);
      iStack_ad8 = 1;
      if (0 < param_1[0xfe5]) {
        iStack_ad8 = param_1[0xfe5];
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar8 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iStack_ad4 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iStack_ad0 = PeekPacketChecksumState((void *)&DAT_007949c8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uStack_acc = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      ApplyBlastDamage(uStack_acc,local_aec,0,iStack_ad0,iStack_ad4 / iStack_ad8,uVar8,
                   (char)param_1[0xf]);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x5f9));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iStack_ad4 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar20 = 0;
      uVar19 = 2;
      uVar18 = 0xff;
      uVar17 = 0;
      PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
      SpawnBlastEffect(local_aec,iStack_ad4,(char)param_1[0xf],7,0,uVar17,uVar8,uVar18,uVar19,uVar20);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iStack_ad8 = PeekPacketChecksumState((void *)(param_1 + 0x45e));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = g_clientContext;
    iStack_ac8 = param_1[2];
    iStack_ad0 = iStack_ad8;
    uStack_acc = uVar8;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState((void *)(g_clientContext + 0xebcbc));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar6 == 4) {
      local_aec = operator_new(0x3fbc);
      puStack_8 = (undefined1 *)0x0;
      apuStack_ae0[0] = local_aec;
      if (local_aec == (undefined4 *)0x0) {
        local_aec = (undefined4 *)0x0;
      }
      else {
        InitProjectile(local_aec,0x186a9);
        *local_aec = &PTR_FUN_0055658c;
        local_aec[0xfe7] = 0xffffffff;
      }
      puStack_8 = (undefined1 *)0xffffffff;
      iVar6 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
      uVar9 = *(uint *)(iVar6 + 4);
      while (uVar9 < 0x186ab) {
        if (uVar9 == 0x186aa) {
          piVar15 = *(int **)(iVar6 + 0x10);
          bVar16 = true;
          if (piVar15[2] == 0) goto LAB_00468c86;
          break;
        }
        iVar6 = *(int *)(iVar6 + 0x1c);
        uVar9 = *(uint *)(iVar6 + 4);
      }
    }
    goto LAB_00468fef;
  }
  goto LAB_00469dc9;
  while( true ) {
    piVar15 = (int *)piVar15[4];
    bVar16 = piVar15[2] == 0;
    if (!bVar16) break;
LAB_00468c86:
    if (bVar16) {
      apuStack_ae0[0] = (undefined4 *)piVar15[0xf];
      iStack_ad4 = piVar15[0xe];
      iStack_ad8 = CalculateAngleFromDelta();
      iVar6 = FloatToInt64();
      iStack_ad4 = iStack_ad4 - iVar6;
      iVar6 = FloatToInt64();
      iVar6 = (int)apuStack_ae0[0] - iVar6;
      (**(code **)(*piVar15 + 4))(&DAT_00553b90);
      piVar15[0x11] = iStack_ad8;
      apuStack_ae0[0] = (undefined4 *)(&DAT_006a7f74 + iVar5);
      cVar4 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
      if (cVar4 == '\0') {
        uStack_680 = 0;
        iStack_88c = 0;
        EncodeOutgoingPacketField((void *)auStack_8a0, 0);
        puStack_8 = (undefined1 *)0x3;
        uStack_8a4 = 0;
        iStack_ab0 = 0;
        EncodeOutgoingPacketField((void *)auStack_ac4, 0);
        SUBFIELD(puStack_8,0,undefined1) = 4;
        SyncOutgoingChecksumField(auStack_8a0, iStack_ac8 + 0x10,auStack_ac4);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState((void *)auStack_ac4);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar8 = PeekPacketChecksumState((void *)auStack_8a0);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = param_1[0xfe5];
        uVar20 = 0;
        uVar19 = 0xff;
        uVar18 = 100;
        uVar17 = 0;
        PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
        FUN_00432320((char)param_1[0xf],1,1,uVar8,uVar17,uVar18,uVar19,iVar5,uVar20);
        puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),3);
        ScrubChecksumGuard();
LAB_00468f4e:
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        cVar4 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&uStack_acc,&iStack_ad0,2,1,1);
        if (cVar4 != '\0') {
          uStack_8a4 = 0;
          iStack_ab0 = 0;
          EncodeOutgoingPacketField((void *)auStack_ac4, 0);
          puStack_8 = (undefined1 *)0x1;
          uStack_680 = 0;
          iStack_88c = 0;
          EncodeOutgoingPacketField((void *)auStack_8a0, 0);
          SUBFIELD(puStack_8,0,undefined1) = 2;
          QueueOutgoingPacketField(uStack_acc);
          QueueOutgoingPacketField(iStack_ad0);
          SyncOutgoingChecksumField(auStack_ac4, iStack_ac8 + 0x10,auStack_8a0);
          iVar5 = param_1[0xfe5];
          uVar20 = 0;
          uVar19 = 0xff;
          uVar18 = 100;
          uVar17 = 0;
          PeekChecksumStateUnderLock(auStack_8a0);
          uVar8 = PeekChecksumStateUnderLock(auStack_ac4);
          PeekPacketChecksumBool((byte *)param_1 + 0xf3c);
          FUN_00432320((char)param_1[0xf],1,1,uVar8,uVar17,uVar18,uVar19,iVar5,uVar20);
          puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
          ScrubChecksumGuard();
          goto LAB_00468f4e;
        }
      }
      local_aec[0xfea] = iStack_ad4;
      local_aec[0xfeb] = iVar6;
      local_aec[0xfec] = uStack_acc;
      local_aec[0xfed] = iStack_ad0;
      local_aec[0xfee] = iStack_ad8;
      /* FIXED (2026-07-15): dropped `self` args - angr-confirmed EDI at
       * 0x468f9a/0x468fab. Disasm traces EDI to a `mov 0x18(%esp),%edi`
       * reload whose only prior writer is the list-node found by the
       * traversal loop above (LAB_00468c86), i.e. the same value already
       * held in `piVar15` here (piVar15 is not reassigned between that
       * loop and this point). */
      uVar8 = FUN_004ac4d0(piVar15);
      local_aec[0xfe9] = uVar8;
      iVar5 = FUN_004ac400(piVar15);
      local_aec[0xfe8] = iVar5 * param_1[0xfe5];
      /* guard-cell: proven - the ctx+0x6a7f70 spill/fold chain; see the
       * fold-dominance proof in commit dc092b4^..'s successor (lea
       * REG,[ctx+0x6a7f70] -> slot, +4 fold -> slot, this peek reads it
       * with no interposed writer and no bypass edge). */
      cVar4 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
      if (cVar4 == '\0') {
        RegisterActiveObject(0, 0, (undefined4 *)0);
      }
      else {
        (**(code **)*local_aec)(1);
      }
      break;
    }
  }
LAB_00468fef:
  if ((char)param_1[0xfe7] != '\0') {
    *(undefined1 *)(piStack_ae8 + 5) = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x1ab));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar17 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x122));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    apuStack_ae0[0] = (undefined4 *)PeekPacketChecksumState((void *)(piStack_ae8 + 0xbdd));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar18 = PeekPacketChecksumState((void *)(piStack_ae8 + 0xb54));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iStack_ad4 = PeekPacketChecksumState((void *)(piStack_ae8 + 0xacb));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iStack_ad8 = PeekPacketChecksumState((void *)(piStack_ae8 + 0xa42));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iStack_ad0 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x9b9));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_acc = PeekPacketChecksumState((void *)(piStack_ae8 + 0x930));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iStack_ac8 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x45e));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iCraterX = PeekPacketChecksumState((void *)(piStack_ae8 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    ApplyCraterExcavation(uStack_acc,iStack_ad0,iStack_ad8,iStack_ad4,uVar18,apuStack_ae0[0],uVar17,uVar8,
                 (int)(&DAT_006a7708 + g_clientContext),(int)iCraterX,(int)iStack_ac8);
    RebuildTerrainColumnCache(&DAT_006a7708 + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x45e));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    apuStack_ae0[0] = (undefined4 *)PeekPacketChecksumState((void *)(piStack_ae8 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00450eb0(apuStack_ae0[0],uVar8,piStack_ae8,1,0,0);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x45e));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar17 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436ac0(uVar17,uVar8);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x45e));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    apuStack_ae0[0] = (undefined4 *)PeekPacketChecksumState((void *)(piStack_ae8 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    SpawnFlameEffect(piStack_ae8[2] + 1,apuStack_ae0[0],uVar8,piStack_ae8[0xe25],piStack_ae8 + 0xe26);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x570));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar17 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x45e));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar18 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00437150(uVar18,uVar17,0x3c,uVar8);
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
    cVar4 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
    if (cVar4 == '\0') {
      AcquireSoundChannel(0);
    }
    cVar4 = PeekPacketChecksumBool((byte *)param_1 + 0xf3f);
    if ((cVar4 != '\0') && (cVar4 = InitChecksumSeed(), cVar4 == '\0')) {
      uVar8 = PeekChecksumStateUnderLock(&DAT_007949c8);
      QueueOutgoingPacketField(uVar8);
    }
    uVar8 = CompareChecksumPair(g_clientContext + 0x5b85c,piStack_ae8 + 0xe48);
    cVar4 = CheckGuardedBoolAnd(uVar8);
    if (cVar4 != '\0') {
      EncodeChecksumState(piStack_ae8 + 0xe48);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x234));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar5 < 0) && (cVar4 = PacketChecksumGreaterThan(piStack_ae8 + 0x122,0), cVar4 != '\0')) {
LAB_0046942b:
      cVar4 = PeekPacketChecksumBool((byte *)param_1 + 0xf4c);
      if (cVar4 == '\0') {
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
      }
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x234));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((0 < iVar5) && (cVar4 = PacketChecksumLessThan(piStack_ae8 + 0x122,0), cVar4 != '\0'))
      goto LAB_0046942b;
    }
    piVar15 = piStack_ae8 + 0xed2;
    cVar4 = CompareChecksumPair(piStack_ae8 + 0x3d5,piVar15);
    if (((cVar4 != '\0') && (cVar4 = CompareChecksumPair(piVar15,piStack_ae8 + 0xf5b), cVar4 != '\0')) ||
       ((cVar4 = CompareChecksumExceeds(piStack_ae8 + 0x3d5,piVar15), cVar4 != '\0' &&
        ((cVar4 = CompareChecksumExceeds(piVar15,piStack_ae8 + 0xf5b), cVar4 != '\0' &&
         (5 < piStack_ae8[0xed1])))))) {
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
    goto LAB_0046a47c;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x1ab));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar17 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x122));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_ae0[0] = (undefined4 *)PeekPacketChecksumState((void *)(piStack_ae8 + 0xbdd));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar18 = PeekPacketChecksumState((void *)(piStack_ae8 + 0xb54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iStack_ad4 = PeekPacketChecksumState((void *)(piStack_ae8 + 0xacb));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iStack_ad8 = PeekPacketChecksumState((void *)(piStack_ae8 + 0xa42));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iStack_ad0 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x9b9));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uStack_acc = PeekPacketChecksumState((void *)(piStack_ae8 + 0x930));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iStack_ac8 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iCraterX = PeekPacketChecksumState((void *)(piStack_ae8 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  ApplyCraterExcavation(uStack_acc,iStack_ad0,iStack_ad8,iStack_ad4,uVar18,apuStack_ae0[0],uVar17,uVar8,
                 (int)(&DAT_006a7708 + g_clientContext),(int)iCraterX,(int)iStack_ac8);
  RebuildTerrainColumnCache(&DAT_006a7708 + g_clientContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_ae0[0] = (undefined4 *)PeekPacketChecksumState((void *)(piStack_ae8 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00450eb0(apuStack_ae0[0],uVar8,piStack_ae8,1,0,0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar17 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00436ac0(uVar17,uVar8);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar17 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  SpawnFlameEffect(piStack_ae8[2],uVar17,uVar8,piStack_ae8[0xe25],piStack_ae8 + 0xe26);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x570));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar17 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar18 = PeekPacketChecksumState((void *)(piStack_ae8 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00437150(uVar18,uVar17,0x3c,uVar8);
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
  cVar4 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar4 == '\0') {
    AcquireSoundChannel(0);
  }
  uVar8 = EncodeChecksumDeltaMul(piStack_ae8 + 0x930,auStack_8a0,7);
  puStack_8 = (undefined1 *)0x5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar17 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar19 = EncodeChecksumDeltaDiv(uVar8,auStack_ac4,uVar17);
  SUBFIELD(puStack_8,0,undefined1) = 6;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)uVar19);
  EncodeOutgoingPacketField((void *)(piStack_ae8 + 0x930), uVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),5);
  if (iStack_ab0 != 0) {
    ScrambleChecksumGuardBytes(iStack_ab0,&DAT_0079376c);
    TreeLowerBound(apuStack_ae0,&DAT_00793770);
  }
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_88c != 0) {
    ScrambleChecksumGuardBytes(iStack_88c,&DAT_0079376c);
    TreeLowerBound(apuStack_ae0,&DAT_00793770);
  }
  uVar8 = EncodeChecksumDeltaMul(piStack_ae8 + 0x9b9,auStack_8a0,7);
  puStack_8 = (undefined1 *)0x7;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar17 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar19 = EncodeChecksumDeltaDiv(uVar8,auStack_ac4,uVar17);
  SUBFIELD(puStack_8,0,undefined1) = 8;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)uVar19);
  EncodeOutgoingPacketField((void *)(piStack_ae8 + 0x9b9), uVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),7);
  if (iStack_ab0 != 0) {
    ScrambleChecksumGuardBytes(iStack_ab0,&DAT_0079376c);
    TreeLowerBound(apuStack_ae0,&DAT_00793770);
  }
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_88c != 0) {
    ScrambleChecksumGuardBytes(iStack_88c,&DAT_0079376c);
    TreeLowerBound(apuStack_ae0,&DAT_00793770);
  }
  uVar8 = EncodeChecksumDeltaMul(piStack_ae8 + 0xa42,auStack_8a0,7);
  puStack_8 = (undefined1 *)0x9;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar17 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar19 = EncodeChecksumDeltaDiv(uVar8,auStack_ac4,uVar17);
  SUBFIELD(puStack_8,0,undefined1) = 10;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)uVar19);
  EncodeOutgoingPacketField((void *)(piStack_ae8 + 0xa42), uVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),9);
  if (iStack_ab0 != 0) {
    ScrambleChecksumGuardBytes(iStack_ab0,&DAT_0079376c);
    TreeLowerBound(apuStack_ae0,&DAT_00793770);
  }
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_88c != 0) {
    ScrambleChecksumGuardBytes(iStack_88c,&DAT_0079376c);
    TreeLowerBound(apuStack_ae0,&DAT_00793770);
  }
  uVar8 = EncodeChecksumDeltaMul(piStack_ae8 + 0x795,auStack_8a0,7);
  puStack_8 = (undefined1 *)0xb;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar17 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar19 = EncodeChecksumDeltaDiv(uVar8,auStack_ac4,uVar17);
  SUBFIELD(puStack_8,0,undefined1) = 0xc;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)uVar19);
  EncodeOutgoingPacketField((void *)(piStack_ae8 + 0x795), uVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),0xb);
  if (iStack_ab0 != 0) {
    ScrambleChecksumGuardBytes(iStack_ab0,&DAT_0079376c);
    TreeLowerBound(apuStack_ae0,&DAT_00793770);
  }
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_88c != 0) {
    ScrambleChecksumGuardBytes(iStack_88c,&DAT_0079376c);
    TreeLowerBound(apuStack_ae0,&DAT_00793770);
  }
  uVar8 = EncodeChecksumDeltaMul(piStack_ae8 + 0x81e,auStack_8a0,7);
  puStack_8 = (undefined1 *)0xd;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar17 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar19 = EncodeChecksumDeltaDiv(uVar8,auStack_ac4,uVar17);
  SUBFIELD(puStack_8,0,undefined1) = 0xe;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)uVar19);
  EncodeOutgoingPacketField((void *)(piStack_ae8 + 0x81e), uVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),0xd);
  if (iStack_ab0 != 0) {
    ScrambleChecksumGuardBytes(iStack_ab0,&DAT_0079376c);
    TreeLowerBound(apuStack_ae0,&DAT_00793770);
  }
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_88c != 0) {
    ScrambleChecksumGuardBytes(iStack_88c,&DAT_0079376c);
    TreeLowerBound(apuStack_ae0,&DAT_00793770);
  }
  uVar8 = EncodeChecksumDeltaMul(piStack_ae8 + 0x8a7,auStack_8a0,7);
  puStack_8 = (undefined1 *)0xf;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar17 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar19 = EncodeChecksumDeltaDiv(uVar8,auStack_ac4,uVar17);
  SUBFIELD(puStack_8,0,undefined1) = 0x10;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)uVar19);
  EncodeOutgoingPacketField((void *)(piStack_ae8 + 0x8a7), uVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),0xf);
  if (iStack_ab0 != 0) {
    ScrambleChecksumGuardBytes(iStack_ab0,&DAT_0079376c);
    TreeLowerBound(apuStack_ae0,&DAT_00793770);
  }
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_88c != 0) {
    ScrambleChecksumGuardBytes(iStack_88c,&DAT_0079376c);
    TreeLowerBound(apuStack_ae0,&DAT_00793770);
  }
  *(undefined1 *)(piStack_ae8 + 0xfe7) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = _rand();
  *(byte *)((int)piStack_ae8 + 0xf45) = (byte)iVar5;
  iVar5 = _rand();
  bVar1 = *(byte *)((int)piStack_ae8 + 0xf45);
  *(byte *)((int)piStack_ae8 + 0xf46) = (byte)iVar5;
  bVar14 = bVar1 & 7;
  bVar14 = ~('\x01' << bVar14) & (byte)iVar5 | '\0' << bVar14;
  *(byte *)((int)piStack_ae8 + 0xf46) = bVar14;
  *(byte *)((int)piStack_ae8 + 0xf47) = bVar14 + bVar1 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_1 = piStack_ae8;
LAB_00469dc9:
  uVar17 = EncodeChecksumDeltaShr(param_1 + 0x10,auStack_ac4,8);
  puStack_8 = (undefined1 *)0x11;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)uVar17);
  EncodeOutgoingPacketField((void *)(param_1 + 0x3d5), uVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_ab0 != 0) {
    ScrambleChecksumGuardBytes(iStack_ab0,&DAT_0079376c);
    TreeLowerBound(apuStack_ae0,&DAT_00793770);
    param_1 = piStack_ae8;
  }
  uVar17 = EncodeChecksumDeltaShr(param_1 + 0x99,auStack_ac4,8);
  puStack_8 = (undefined1 *)0x12;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)uVar17);
  EncodeOutgoingPacketField((void *)(param_1 + 0x45e), uVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)0xffffffff;
  piVar15 = param_1;
  if (iStack_ab0 != 0) {
    ScrambleChecksumGuardBytes(iStack_ab0,&DAT_0079376c);
    TreeLowerBound(apuStack_ae0,&DAT_00793770);
    piVar15 = piStack_ae8;
  }
  cVar4 = CheckGuardedBoolAnd(piVar15[0x3d2] != 0,(byte *)(piVar15 + 0x3d3));
  if (cVar4 == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(piVar15 + 0x122));
    iVar6 = PeekPacketChecksumState((void *)(piVar15 + 0x2bd));
    EncodeOutgoingPacketField((void *)(piVar15 + 0x122), iVar6 + iVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(piVar15 + 0x1ab));
    iVar6 = PeekPacketChecksumState((void *)(piVar15 + 0x346));
    EncodeOutgoingPacketField((void *)(piVar15 + 0x1ab), iVar6 + iVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar9 = PeekPacketChecksumState((void *)(piVar15 + 0x122));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((int)((uVar9 ^ (int)uVar9 >> 0x1f) - ((int)uVar9 >> 0x1f)) < 200) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(piVar15 + 0x122));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar5 < 0) {
        uVar8 = 0xffffff38;
      }
      else {
        uVar8 = 200;
      }
      QueueOutgoingPacketField(uVar8);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar9 = PeekPacketChecksumState((void *)(piVar15 + 0x122));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((int)((uVar9 ^ (int)uVar9 >> 0x1f) - ((int)uVar9 >> 0x1f)) < 1000) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField((void *)(piVar15 + 0x122), 1000);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    uVar8 = EncodeChecksumDeltaDiv(piVar15[0x3d2] + 0x25c,auStack_67c,4);
    puStack_8 = (undefined1 *)0x13;
    uVar8 = EncodeChecksumPairDiff(piVar15[0x3d2] + 0x38,auStack_458,uVar8);
    puStack_8 = (undefined1 *)0x14;
    bVar3 = false;
    bVar2 = false;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    apuStack_ae0[0] = (undefined4 *)PeekPacketChecksumState((void *)(piVar15 + 0x3d5));
    iVar5 = PeekPacketChecksumState((void *)uVar8);
    bVar16 = (int)apuStack_ae0[0] < iVar5;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (bVar16) {
LAB_0046a089:
      bVar16 = true;
    }
    else {
      uVar8 = EncodeChecksumDeltaDiv(piVar15[0x3d2] + 0x25c,auStack_8a0,4);
      puStack_8 = (undefined1 *)0x15;
      uVar8 = EncodeChecksumPairSum(piVar15[0x3d2] + 0x38,auStack_ac4,uVar8);
      puStack_8 = (undefined1 *)0x16;
      bVar3 = true;
      bVar2 = true;
      cVar4 = CompareChecksumPair(uVar8,piVar15 + 0x3d5);
      bVar16 = false;
      if (cVar4 != '\0') goto LAB_0046a089;
    }
    puStack_8 = (undefined1 *)0x15;
    if (bVar2) {
      ScrubChecksumGuard();
    }
    puStack_8 = (undefined1 *)0x14;
    if (bVar3) {
      ScrubChecksumGuard();
    }
    puStack_8 = (undefined1 *)0x13;
    ScrubChecksumGuard();
    puStack_8 = (undefined1 *)0xffffffff;
    ScrubChecksumGuard();
    if (bVar16) {
      iVar5 = piVar15[0x3d4];
      piVar15[0x3d4] = iVar5 + 1;
      if (iVar5 + 1 < 3) {
        uVar8 = EncodeChecksumNegate(piVar15 + 0x122,auStack_234);
        puStack_8 = (undefined1 *)0x17;
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
  iVar5 = PeekPacketChecksumState((void *)(piVar15 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar5 < 0) {
LAB_0046a2a6:
    *(undefined1 *)(piVar15 + 5) = 1;
    cVar4 = PeekPacketChecksumBool((byte *)param_1 + 0xf3f);
    if ((cVar4 != '\0') && (cVar4 = InitChecksumSeed(), cVar4 == '\0')) {
      iVar5 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
      if ((iVar5 == 5) || (local_ae4 = 2, iVar5 == 6)) {
        local_ae4 = 0x19;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField((void *)(g_clientContext + 0x621e8), local_ae4);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
  }
  else {
    iVar5 = *(int *)(&g_nCameraBoundX + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState((void *)(piVar15 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar5 <= iVar6) goto LAB_0046a2a6;
    iVar5 = *(int *)(&g_nCameraBoundY + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x45e));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar5 <= iVar6) || (cVar4 = PacketChecksumLessThan(param_1 + 0x45e,0xfffffc18), cVar4 != '\0'))
    goto LAB_0046a2a6;
  }
  cVar4 = CheckBothGuardedBools();
  if (cVar4 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x45e));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar10 = PeekPacketChecksumState((void *)(piVar15 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = g_clientContext;
    piVar15 = (int *)(&DAT_006a7708 + g_clientContext);
    cVar4 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
    if ((cVar4 == '\0') && ((&DAT_006a7758)[iVar5] != '\0')) {
      if (((&DAT_006a7736)[iVar5] == '\x01') &&
         ((uVar9 = iVar6 - *(int *)(&g_nCameraY + iVar5) >> 0x1f,
          200 < (int)((iVar6 - *(int *)(&g_nCameraY + iVar5) ^ uVar9) - uVar9) ||
          (uVar9 = iVar10 - *(int *)(&g_nCameraX + iVar5) >> 0x1f,
          300 < (int)((iVar10 - *(int *)(&g_nCameraX + iVar5) ^ uVar9) - uVar9))))) {
        (&DAT_006a7736)[iVar5] = 0;
      }
      iVar12 = 400;
      if (399 < iVar10) {
        iVar12 = iVar10;
      }
      iVar11 = *(int *)(&g_nCameraBoundX + iVar5) + -400;
      if ((iVar12 <= iVar11) && (iVar11 = iVar10, iVar10 < 400)) {
        iVar11 = 400;
      }
      iVar10 = -0x14;
      if (-0x15 < iVar6) {
        iVar10 = iVar6;
      }
      iVar12 = *(int *)(&g_nCameraBoundY + iVar5) + -0x104;
      if ((iVar10 <= iVar12) && (iVar12 = -0x14, -0x15 < iVar6)) {
        iVar12 = iVar6;
      }
      iVar6 = *piVar15 - iVar11;
      *(int *)(&g_nCameraScrollY + iVar5) = iVar12;
      if (((*(int *)(&DAT_006a770c + iVar5) - iVar12) * (*(int *)(&DAT_006a770c + iVar5) - iVar12) +
           iVar6 * iVar6 < 40000) &&
         (((&DAT_006a7734)[iVar5] == '\x01' || ((&DAT_006a7f6c)[iVar5] == '\0')))) {
        *(int *)(&g_nCameraX + iVar5) = iVar11;
        *piVar15 = iVar11;
        *(int *)(&g_nCameraY + iVar5) = iVar12;
        *(int *)(&DAT_006a770c + iVar5) = iVar12;
      }
      if ((((&DAT_006a7734)[iVar5] == '\0') && ((&DAT_006a7f6c)[iVar5] == '\x01')) &&
         ((&DAT_006a7736)[iVar5] == '\0')) {
        iVar6 = *(int *)(&DAT_006a7730 + iVar5);
        iVar10 = iVar6;
        if (iVar11 <= iVar6) {
          iVar10 = iVar11;
        }
        iVar13 = *(int *)(&DAT_006a772c + iVar5);
        if ((iVar13 <= iVar10) && (iVar13 = iVar6, iVar11 <= iVar6)) {
          iVar13 = iVar11;
        }
        *(int *)(&g_nCameraScrollX + iVar5) = iVar13;
      }
      if ((&DAT_006a7734)[iVar5] == '\x01') {
        *(int *)(&g_nCameraScrollX + iVar5) = iVar11;
        *(int *)(&g_nCameraScrollY + iVar5) = iVar12;
      }
    }
  }
LAB_0046a47c:
  *unaff_FS_OFFSET = uStack_10;
  return;
}

