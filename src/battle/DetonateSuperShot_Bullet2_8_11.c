/* DetonateSuperShot_Bullet2_8_11 - 0x00483ff0 in the original binary.
 *
 * RENAMED (2026-08-16, from FUN_00483ff0): CProjectile virtual slot 6
 * (DetonateProjectile, base impl 0x4572b0) override for mobile type 1's
 * super shot (texture bullet2p; vtable 0x5562c8, ctor FUN_0048d8c0 reached
 * only through SpawnSuperShot's case 1); mobile type 7's super shot
 * (texture bullet8p; vtable 0x5561c8, ctor FUN_004837c0 reached only
 * through SpawnSuperShot's case 7); mobile type 10's super shot (texture
 * bullet11p; vtable 0x555f58, ctor FUN_00475990 reached only through
 * SpawnSuperShot's case 10). Type/role CONFIRMED via vtable geometry
 * (tools/projectile_class_map.py); the mobile NAME is not confirmable (no
 * mobile-type->name map in the repo).
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 36 argless PeekPacketChecksumState() calls (36 C : 36 orig).
 * Cells from tools/guard_cell_resolve.py over the function plus a full
 * landmark match - the decompile is goto-shuffled with the C's FIRST
 * block (the two EncodeChecksumDeltaShr rounds at ~74-89) living at
 * the function's LAST addresses (0x4849d4-0x484a8b in DetonateSuperShot_Bullet2_8_11's
 * layout), and the file's tail (~462-513) being the address-order run
 * 0x48474d-0x484927.
 *
 * DETONATION-TWIN FAMILY, shorter variant: cell for cell the same as
 * DetonateProjectile / FUN_0049d270 with the 8-cell crater block moved
 * out into a callee.  DetonateSuperShot_Bullet2_8_11, FUN_00499ef0 and FUN_0048e1d0 are
 * LINE-FOR-LINE twins of each other (identical C apart from the tail's
 * line offsets and one global), fingerprinted by
 * guard_cell_resolve.py: identical 36-row cell sequences, so the three
 * cross-check each other and the earlier twins.  The object is `this`
 * in ESI throughout (`mov esi,ecx` at entry); the tail's frame[0x20] /
 * frame[0x34] are this+0x1178 / this+0xf54 stored one push deep.  Two
 * cells are chained EncodeChecksumDeltaShr returns (captured, uVar21).
 *
 * TOOL NOTE: this family exposed a resolver hole - the rand-scramble
 * block (`mov esi,[0x5b3484] / add esi,0x62143 ... jmp exit`) sits
 * BEFORE the DeltaShr block in address order but never falls into it,
 * and the linear back-walk crossed the `jmp` and reported ctx+0x62143+N
 * for the DeltaShr-block cells.  guard_cell_resolve.py now stops at an
 * unconditional jmp/ret while walking backwards (`<reg crosses block
 * end>`), and DetonateProjectile's one newly-flagged site (0x458393)
 * was re-verified by hand and stands.
 */
#include "ghidra_types.h"


void __fastcall DetonateSuperShot_Bullet2_8_11(int *param_1)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  undefined4 uVar6;
  undefined4 uVar21;
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
  iVar3 = PeekPacketChecksumState((void *)(param_1 + 0x10));
  iVar4 = PeekPacketChecksumState((void *)(param_1 + 0x122));
  EncodeOutgoingPacketField(iVar4 + iVar3);
  pcVar13 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(param_1 + 0x99));
  iVar4 = PeekPacketChecksumState((void *)(param_1 + 0x1ab));
  EncodeOutgoingPacketField(iVar4 + iVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar2 = PeekPacketChecksumBool((byte *)param_1 + 0xf45);
  if (cVar2 == '\0') {
    uVar21 = EncodeChecksumDeltaShr(param_1 + 0x10,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x5;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState((void *)uVar21);
    EncodeOutgoingPacketField(uVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_ab0 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(apuStack_ad0);
      pcVar13 = (code *)LeaveCriticalSection;
    }
    uVar21 = EncodeChecksumDeltaShr(param_1 + 0x99,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x6;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState((void *)uVar21);
    EncodeOutgoingPacketField(uVar6);
    (*pcVar13)(&DAT_005a9068);
    uStack_c = 0xffffffff;
    if (iStack_ab4 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&piStack_ad4);
      pcVar13 = (code *)LeaveCriticalSection;
    }
    cVar2 = CheckGuardedBoolAnd(param_1[0x3d2] != 0);
    if (cVar2 == '\0') {
      EmitChecksumSum(param_1 + 0x122, param_1 + 0x2bd);
      EmitChecksumSum(param_1 + 0x1ab, param_1 + 0x346);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar10 = PeekPacketChecksumState((void *)(param_1 + 0x122));
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
        if (cVar2 != '\0') goto LAB_00484c11;
      }
      else {
LAB_00484c11:
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
          uVar6 = EncodeChecksumNegate(param_1 + 0x122,auStack_238);
          uStack_c = 0xb;
          EncodeChecksumState(uVar6);
          uStack_c = 0xffffffff;
          ScrubChecksumGuard();
        }
        else {
          SetGuardedBool(0,GB_GUARD_UNRECOVERED);
        }
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    piStack_ad4 = param_1 + 0x3d5;
    PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    (*pcVar13)(&DAT_005a9068);
    if ((char)(unaff_EBX >> 0x18) == '\0') {
      iVar3 = *(int *)(&g_nCameraBoundX + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
      (*pcVar13)(&DAT_005a9068);
      if (((iVar3 <= iVar4) ||
          (cVar2 = PacketChecksumGreaterEqual(param_1 + 0x45e,*(undefined4 *)(&g_nCameraBoundY + g_clientContext)),
          cVar2 != '\0')) || (cVar2 = PacketChecksumLessThan(param_1 + 0x45e,0xfffffc18), cVar2 != '\0'))
      goto LAB_00484dcc;
    }
    else {
LAB_00484dcc:
      *(undefined1 *)(param_1 + 5) = 1;
      cVar2 = PeekPacketChecksumBool((byte *)param_1 + 0xf3f);
      if ((cVar2 != '\0') && (cVar2 = InitChecksumSeed(), cVar2 == '\0')) {
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
    cVar2 = CheckBothGuardedBools();
    if (cVar2 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState((void *)(param_1 + 0x45e));
      (*pcVar13)(&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
      (*pcVar13)(&DAT_005a9068);
      iVar3 = g_clientContext;
      piVar15 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar2 = PeekPacketChecksumBool();
      if ((cVar2 == '\0') && ((&DAT_006a7758)[iVar3] != '\0')) {
        if (((&DAT_006a7736)[iVar3] == '\x01') &&
           ((uVar10 = iVar4 - *(int *)(&g_nCameraY + iVar3) >> 0x1f,
            200 < (int)((iVar4 - *(int *)(&g_nCameraY + iVar3) ^ uVar10) - uVar10) ||
            (uVar10 = iVar7 - *(int *)(&g_nCameraX + iVar3) >> 0x1f,
            300 < (int)((iVar7 - *(int *)(&g_nCameraX + iVar3) ^ uVar10) - uVar10))))) {
          (&DAT_006a7736)[iVar3] = 0;
        }
        iVar8 = 400;
        if (399 < iVar7) {
          iVar8 = iVar7;
        }
        iVar9 = *(int *)(&g_nCameraBoundX + iVar3) + -400;
        if ((iVar8 <= iVar9) && (iVar9 = iVar7, iVar7 < 400)) {
          iVar9 = 400;
        }
        iVar7 = -0x14;
        if (-0x15 < iVar4) {
          iVar7 = iVar4;
        }
        iVar8 = *(int *)(&g_nCameraBoundY + iVar3) + -0x104;
        if ((iVar7 <= iVar8) && (iVar8 = -0x14, -0x15 < iVar4)) {
          iVar8 = iVar4;
        }
        iVar4 = *piVar15 - iVar9;
        *(int *)(&g_nCameraScrollY + iVar3) = iVar8;
        if (((*(int *)(&DAT_006a770c + iVar3) - iVar8) * (*(int *)(&DAT_006a770c + iVar3) - iVar8) +
             iVar4 * iVar4 < 40000) &&
           (((&DAT_006a7734)[iVar3] == '\x01' || ((&DAT_006a7f6c)[iVar3] == '\0')))) {
          *(int *)(&g_nCameraX + iVar3) = iVar9;
          *piVar15 = iVar9;
          *(int *)(&g_nCameraY + iVar3) = iVar8;
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
          *(int *)(&g_nCameraScrollX + iVar3) = iVar11;
        }
        if ((&DAT_006a7734)[iVar3] == '\x01') {
          *(int *)(&g_nCameraScrollX + iVar3) = iVar9;
          *(int *)(&g_nCameraScrollY + iVar3) = iVar8;
        }
      }
    }
    goto LAB_00484fa3;
  }
  SyncOutgoingChecksumField(param_1 + 0x3d5, param_1[2],param_1 + 0x45e);
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((-1 < iVar3) && (iVar3 < *(int *)(&g_nCameraBoundX + g_clientContext))) {
      pcVar5 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar3);
      puStack_af0 = (undefined4 *)0x0;
      if (0 < *(int *)(&g_nCameraBoundY + g_clientContext)) {
        do {
          if (*pcVar5 != '\0') goto LAB_0048413a;
          pcVar5 = pcVar5 + *(int *)(&g_nCameraBoundX + g_clientContext);
          puStack_af0 = (undefined4 *)((int)puStack_af0 + 1);
        } while ((int)puStack_af0 < *(int *)(&g_nCameraBoundY + g_clientContext));
      }
    }
    puStack_af0 = (undefined4 *)0x2710;
LAB_0048413a:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,uVar6,puStack_af0);
    local_ae4 = 1;
    if (0 < param_1[0xfe5]) {
      local_ae4 = param_1[0xfe5];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_adc = PeekPacketChecksumState((void *)&DAT_007949c8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_ad8 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0043af40(uStack_ad8,puStack_af0,0,uStack_adc,iVar3 / local_ae4,uVar6,(char)param_1[0xf]);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState((void *)(param_1 + 0x5f9));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar20 = 0;
    uVar19 = 2;
    uVar18 = 0xff;
    uVar17 = 0;
    PeekPacketChecksumBool(0,uVar6,0xff,2,0);
    FUN_00431d90((char)param_1[0xf],7,0,uVar17,uVar6,uVar18,uVar19,uVar20);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState((void *)(param_1 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar17 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = g_clientContext;
  iStack_ac8 = param_1[2];
  uStack_adc = uVar6;
  uStack_ad8 = uVar17;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0xebcbc));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 == 4) {
    puStack_af0 = operator_new(0x3fbc);
    puStack_8 = (undefined1 *)0x0;
    apuStack_ad0[0] = puStack_af0;
    if (puStack_af0 == (undefined4 *)0x0) {
      puStack_af0 = (undefined4 *)0x0;
    }
    else {
      InitProjectile(puStack_af0,0x186a9);
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
        if (piVar15[2] == 0) goto LAB_004843b5;
        break;
      }
      iVar4 = *(int *)(iVar4 + 0x1c);
      uVar10 = *(uint *)(iVar4 + 4);
    }
  }
  goto LAB_0048471e;
  while( true ) {
    piVar15 = (int *)piVar15[4];
    bVar16 = piVar15[2] == 0;
    piStack_ad4 = piVar15;
    if (!bVar16) break;
LAB_004843b5:
    if (bVar16) {
      apuStack_ad0[0] = (undefined4 *)piVar15[0xf];
      iVar4 = piVar15[0xe];
      piStack_ad4 = piVar15;
      iVar7 = CalculateAngleFromDelta();
      iVar8 = FloatToInt64();
      iVar9 = FloatToInt64();
      iVar9 = (int)apuStack_ad0[0] - iVar9;
      (**(code **)(*piVar15 + 4))(&DAT_00553b90);
      piVar15[0x11] = iVar7;
      apuStack_ad0[0] = (undefined4 *)(&DAT_006a7f74 + iVar3);
      cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        auStack_680[0] = 0;
        uStack_88c = 0;
        EncodeOutgoingPacketField(0);
        puStack_8 = (undefined1 *)0x3;
        auStack_8a4[0] = 0;
        iStack_ab0 = 0;
        EncodeOutgoingPacketField(0);
        SUBFIELD(puStack_8,0,undefined1) = 4;
        SyncOutgoingChecksumField(auStack_8a0, iStack_ac8 + 0x10,auStack_ac4);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState((void *)auStack_ac4);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar6 = PeekPacketChecksumState((void *)auStack_8a0);
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
LAB_0048467d:
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
          SyncOutgoingChecksumField(auStack_ac4, iStack_ac8 + 0x10,auStack_8a0);
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
          goto LAB_0048467d;
        }
      }
      puStack_af0[0xfea] = iVar4 - iVar8;
      puStack_af0[0xfeb] = iVar9;
      puStack_af0[0xfec] = uStack_ad8;
      puStack_af0[0xfed] = uStack_adc;
      puStack_af0[0xfee] = iVar7;
      /* angr-confirmed: self ptr lives in EDI here, reloaded from the
       * spilled projectile object (puStack_af0) allocated/inited above. */
      uVar6 = FUN_004ac4d0(puStack_af0);
      puStack_af0[0xfe9] = uVar6;
      iVar3 = FUN_004ac400(puStack_af0);
      puStack_af0[0xfe8] = iVar3 * param_1[0xfe5];
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        RegisterActiveObject(0, 0, (undefined4 *)0);
      }
      else {
        (**(code **)*puStack_af0)(1);
      }
      break;
    }
  }
LAB_0048471e:
  *(undefined1 *)(param_1 + 5) = 1;
  (**(code **)(*param_1 + 0x20))();
  cVar2 = PeekPacketChecksumBool((byte *)param_1 + 0xf3f);
  if ((cVar2 != '\0') && (cVar2 = InitChecksumSeed(), cVar2 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState((void *)&DAT_007949c8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    QueueOutgoingPacketField(uVar6);
    iVar3 = g_clientContext;
    *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
    *(undefined4 *)(&DAT_005f376c + iVar3) = 0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x5b85c));
  iVar4 = PeekPacketChecksumState((void *)(param_1 + 0xe48));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar2 = CheckGuardedBoolAnd(iVar3 < iVar4);
  if (cVar2 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState((void *)(param_1 + 0xe48));
    EncodeOutgoingPacketField(uVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(param_1 + 0x234));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 < 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState((void *)(param_1 + 0x122));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar3 < 1) goto LAB_00484857;
LAB_004848a3:
    cVar2 = PeekPacketChecksumBool((byte *)param_1 + 0xf4c);
    if (cVar2 == '\0') {
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
  }
  else {
LAB_00484857:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState((void *)(param_1 + 0x234));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar3) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState((void *)(param_1 + 0x122));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar3 < 0) goto LAB_004848a3;
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
  iVar4 = PeekPacketChecksumState((void *)(param_1 + 0xed2));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar4 <= iVar3) || (cVar2 = CompareChecksumPair(param_1 + 0xed2,param_1 + 0xf5b), cVar2 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    iVar4 = PeekPacketChecksumState((void *)(param_1 + 0xed2));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar3 <= iVar4) ||
       ((cVar2 = CompareChecksumExceeds(param_1 + 0xed2,param_1 + 0xf5b), cVar2 == '\0' ||
        (param_1[0xed1] < 6)))) goto LAB_00484fa3;
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
LAB_00484fa3:
  *unaff_FS_OFFSET = uStack_10;
  return;
}

