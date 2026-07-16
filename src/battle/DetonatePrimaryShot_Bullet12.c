/* DetonatePrimaryShot_Bullet12 - 0x004af7a0 in the original binary.
 *
 * RENAMED (2026-07-16, from FUN_004af7a0): the DetonateProjectile
 * (CProjectile virtual slot 6) override for mobile TYPE 11's primary-shot
 * projectile. Type/role CONFIRMED via vtable geometry (its pointer
 * appears once, at slot 6 of projectile vtable 0x556660, whose ctor
 * FUN_004af530 is reached only through SpawnPrimaryShot's case 0xb - the
 * bullet-12 case) - same MIRV/cluster shape as the near-twin
 * DetonatePrimaryShot_Bullet4. The "_Bullet12" suffix is the confirmed
 * bullet/mobile-type; the specific mobile NAME is not confirmable. Raw/
 * near-verbatim Ghidra body - see src/README.md.
 *
 * FIXED (2026-07-16): 23 of this function's 24 EncodeOutgoingPacketField
 * call sites dropped `self` (unaff_EDI) - same angr disassembly
 * reconstruction as the near-twin src/unnamed/DetonatePrimaryShot_Bullet4.c (backward
 * register/stack-slot tracing from each call site, cross-checked
 * against calls to sibling anchor functions whose real addresses are
 * known). This function has its own distinct stack-cached self values
 * (`local_cfc`/`local_cf4`, matching this file's own `param_1 + 0x102e`/
 * `param_1 + 0x10b7` idioms) rather than reusing the twin's offsets -
 * do not assume the two files' self expressions transfer directly.
 * Four sites (the zero-arg `EncodeOutgoingPacketField(0)` calls
 * guarding the two raw scratch-buffer unions) use the established
 * `(char *)&X - 0x14` idiom. Also merged the adjacent argless
 * `PeekPacketChecksumState()` call(s) into each site's value argument
 * (2 calls -> summed, matching the disasm's `add eax,X`) where the
 * source hadn't already captured a value.
 *
 * One site (line ~736, call at disasm 0x4b07fd) is NOT fixed - see its
 * own comment. Same shape as the twin's unresolved site: self traces
 * to a stack slot last written by a `cmp`, not a stable pointer
 * expression, and the surrounding if-block is unreachable in the
 * current bring-up build regardless (gated by CheckGuardedBoolAnd on a
 * value sourced from the stubbed PeekPacketChecksumState).
 */
#include "ghidra_types.h"


void __fastcall DetonatePrimaryShot_Bullet12(int *param_1)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffff2c4;
  undefined stack0xfffff2c8;
  undefined stack0xfffff2d4;
  undefined stack0xfffff2d8;
  undefined stack0xfffff2dc;
  undefined stack0xfffff2e0;
  undefined stack0xfffff2e4;
  byte bVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  char *pcVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  int iVar15;
  uint uVar16;
  int iVar17;
  int iVar18;
  byte bVar19;
  code *pcVar20;
  byte *pbVar21;
  undefined4 unaff_EDI;
  int *piVar22;
  undefined4 *unaff_FS_OFFSET;
  bool bVar23;
  char cVar24;
  undefined4 uVar25;
  undefined4 uVar26;
  undefined *puVar27;
  undefined *puVar28;
  undefined *puVar29;
  undefined *puVar30;
  undefined *puVar31;
  undefined *puVar32;
  undefined *puVar33;
  undefined *puVar34;
  undefined1 auStack_d18 [3];
  char local_d15;
  int local_d14;
  undefined4 local_d10;
  int local_d0c;
  undefined *local_d08;
  undefined4 local_d00;
  int *local_cfc;
  float local_cf8;
  int *local_cf4;
  undefined *puStack_cf0;
  int iStack_cec;
  int local_cd0;
  undefined1 uStack_b04;
  undefined1 auStack_b00 [4];
  undefined1 auStack_afc [16];
  undefined4 uStack_aec;
  int local_aac;
  undefined1 uStack_8e0;
  undefined1 auStack_8d8 [548];
  undefined1 auStack_6b4 [532];
  undefined1 auStack_4a0 [20];
  int iStack_48c;
  undefined1 auStack_27c [20];
  int iStack_268;
  undefined4 uStack_58;
  undefined4 uStack_50;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053e2f5;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_d10 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_cfc = param_1 + 0x102e;
  iVar4 = PeekPacketChecksumState();
  pcVar20 = (code *)LeaveCriticalSection;
  local_d15 = iVar4 == -1000000;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (local_d15 == '\0') {
LAB_004af8b0:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(param_1 + 0x10), PeekPacketChecksumState());
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_cf4 = param_1 + 0x10b7;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_cf4 = param_1 + 0x10b7;
    iVar4 = PeekPacketChecksumState();
    local_d15 = iVar4 == -1000000;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (local_d15 == '\0') goto LAB_004af8b0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)local_cfc, PeekPacketChecksumState());
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(param_1 + 0x1140), PeekPacketChecksumState());
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)local_cf4, PeekPacketChecksumState());
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EncodeOutgoingPacketField((void *)(param_1 + 0x99), PeekPacketChecksumState());
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d14 = PeekPacketChecksumState();
  EncodeOutgoingPacketField((void *)local_cfc, local_d14 + PeekPacketChecksumState());
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d14 = PeekPacketChecksumState();
  EncodeOutgoingPacketField((void *)local_cf4, local_d14 + PeekPacketChecksumState());
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d14 = PeekPacketChecksumState();
  EncodeOutgoingPacketField((void *)(param_1 + 0x10), local_d14 + PeekPacketChecksumState());
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d14 = PeekPacketChecksumState();
  EncodeOutgoingPacketField((void *)(param_1 + 0x99), local_d14 + PeekPacketChecksumState());
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004585e0();
  EncodeChecksumDeltaAdd();
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d14 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaMod();
  SUBFIELD(local_4,0,undefined1) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d0c = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
  if (local_cd0 != 0) {
    ScrambleChecksumGuardBytes();
    local_d14 = local_cd0;
    TreeLowerBound();
    pcVar20 = (code *)LeaveCriticalSection;
  }
  local_4 = 0xffffffff;
  if (local_aac != 0) {
    ScrambleChecksumGuardBytes();
    local_d14 = local_aac;
    TreeLowerBound();
    pcVar20 = (code *)LeaveCriticalSection;
  }
  local_cf8 = (float)param_1[0x102a];
  local_d14 = FloatToInt64();
  local_cf8 = (float)FloatToInt64();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d00 = PeekPacketChecksumState();
  (*pcVar20)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d10 = PeekPacketChecksumState();
  EncodeOutgoingPacketField((void *)(param_1 + 0x10), local_d10);
  (*pcVar20)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  puVar34 = &DAT_005a9068;
  (*pcVar20)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d0c = PeekPacketChecksumState();
  EncodeOutgoingPacketField((void *)(param_1 + 0x99), local_d0c);
  puVar33 = &DAT_005a9068;
  (*pcVar20)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d10 = PeekPacketChecksumState();
  puVar32 = &DAT_005a9068;
  (*pcVar20)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  puVar31 = &DAT_005a9068;
  (*pcVar20)(&DAT_005a9068);
  uVar5 = EncodeChecksumPairDiff(param_1 + 0x10,&local_cfc,param_1 + 0x1140);
  uStack_1c = 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  EncodeOutgoingPacketField((void *)(param_1 + 0x122), uVar6);
  puVar30 = &DAT_005a9068;
  (*pcVar20)(&DAT_005a9068);
  uStack_20 = 0xffffffff;
  if (iStack_cec != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&stack0xfffff2dc);
    pcVar20 = (code *)LeaveCriticalSection;
  }
  EncodeChecksumPairDiff(param_1 + 0x99,&local_d00,param_1 + 0x11c9);
  uStack_20 = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  EncodeOutgoingPacketField((void *)(param_1 + 0x1ab), uVar6);
  puVar29 = &DAT_005a9068;
  (*pcVar20)(&DAT_005a9068);
  uStack_24 = 0xffffffff;
  if (puStack_cf0 != (undefined *)0x0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&stack0xfffff2d8);
    pcVar20 = (code *)LeaveCriticalSection;
    puVar34 = puStack_cf0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  EncodeOutgoingPacketField((void *)(param_1 + 0x1140), uVar6);
  (*pcVar20)(&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  EncodeOutgoingPacketField((void *)(param_1 + 0x11c9), uVar6);
  puVar28 = &DAT_005a9068;
  (*pcVar20)(&DAT_005a9068);
  FUN_004585e0();
  (**(code **)(*param_1 + 0x14))();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((void *)(param_1 + 0x122), uVar5);
  puVar27 = &DAT_005a9068;
  (*pcVar20)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((void *)(param_1 + 0x1ab), puVar32);
  puVar32 = &DAT_005a9068;
  (*pcVar20)(&DAT_005a9068);
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 == '\0') {
    EncodeChecksumDeltaShr(param_1 + 0x10,auStack_d18,8);
    uStack_38 = 9;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField((void *)(param_1 + 0x3d5), uVar5);
    (*pcVar20)(&DAT_005a9068);
    uStack_3c = 0xffffffff;
    if (local_d08 != (undefined *)0x0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&stack0xfffff2d8);
      pcVar20 = (code *)LeaveCriticalSection;
      puVar31 = local_d08;
    }
    EncodeChecksumDeltaShr(param_1 + 0x99,&stack0xfffff2e4,8);
    uStack_3c = 10;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField((void *)(param_1 + 0x45e), uVar5);
    cVar2 = '\0';
    (*pcVar20)();
    uStack_40 = 0xffffffff;
    if (local_d0c != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&stack0xfffff2d4);
      pcVar20 = (code *)LeaveCriticalSection;
    }
    cVar24 = CheckGuardedBoolAnd(param_1[0x3d2] != 0);
    if (cVar24 == '\0') {
      EmitChecksumSum(param_1 + 0x2bd);
      EmitChecksumSum(param_1 + 0x346);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar16 = PeekPacketChecksumState();
      (*pcVar20)(&DAT_005a9068);
      if ((int)((uVar16 ^ (int)uVar16 >> 0x1f) - ((int)uVar16 >> 0x1f)) < 200) {
        cVar24 = PacketChecksumLessThan(param_1 + 0x122,0);
        if (cVar24 == '\0') {
          uVar5 = 200;
        }
        else {
          uVar5 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar5);
      }
      uVar5 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_8d8,4);
      uStack_40 = 0xb;
      uVar5 = EncodeChecksumPairDiff(param_1[0x3d2] + 0x38,auStack_6b4,uVar5);
      uStack_40 = 0xc;
      uVar16 = 3;
      cVar24 = CompareChecksumPair(param_1 + 0x3d5,uVar5);
      if (cVar24 == '\0') {
        uVar5 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_afc,4);
        uStack_40 = 0xd;
        uVar5 = EncodeChecksumPairSum(param_1[0x3d2] + 0x38,&stack0xfffff2e0,uVar5);
        uStack_40 = 0xe;
        uVar16 = 0xf;
        cVar24 = CompareChecksumPair(uVar5,param_1 + 0x3d5);
        bVar23 = false;
        if (cVar24 != '\0') goto LAB_004b0c0e;
      }
      else {
LAB_004b0c0e:
        bVar23 = true;
      }
      uStack_40 = 0xd;
      if ((uVar16 & 8) != 0) {
        uVar16 = uVar16 & 0xfffffff7;
        ScrubChecksumGuard();
      }
      uStack_40 = 0xc;
      if ((uVar16 & 4) != 0) {
        uVar16 = uVar16 & 0xfffffffb;
        ScrubChecksumGuard();
      }
      uStack_40 = 0xb;
      if ((uVar16 & 2) != 0) {
        uVar16 = uVar16 & 0xfffffffd;
        ScrubChecksumGuard();
      }
      uStack_40 = 0xffffffff;
      if ((uVar16 & 1) != 0) {
        ScrubChecksumGuard();
      }
      if (bVar23) {
        iVar4 = param_1[0x3d4];
        param_1[0x3d4] = iVar4 + 1;
        if (iVar4 + 1 < 3) {
          uVar5 = EncodeChecksumNegate(param_1 + 0x122,auStack_8d8);
          uStack_40 = 0xf;
          EncodeChecksumState(uVar5);
          uStack_40 = 0xffffffff;
          ScrubChecksumGuard();
        }
        else {
          SetGuardedBool(0);
        }
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar20)(&DAT_005a9068);
    if (cVar2 == '\0') {
      iVar4 = *(int *)(&g_nCameraBoundX + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar15 = PeekPacketChecksumState();
      cVar2 = iVar4 <= iVar15;
      (*pcVar20)(&DAT_005a9068);
      if (cVar2 != '\0') goto LAB_004b0dc8;
      cVar2 = PacketChecksumGreaterEqual(param_1 + 0x45e,*(undefined4 *)(&g_nCameraBoundY + g_clientContext));
      if ((cVar2 != '\0') || (cVar2 = PacketChecksumLessThan(param_1 + 0x45e,0xfffffc18), cVar2 != '\0'))
      goto LAB_004b0dc8;
    }
    else {
LAB_004b0dc8:
      *(undefined1 *)(param_1 + 5) = 1;
      cVar2 = PeekPacketChecksumBool();
      if ((cVar2 != '\0') && (cVar2 = InitChecksumSeed(), cVar2 == '\0')) {
        iVar4 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
        if ((iVar4 == 5) || (uVar5 = 2, iVar4 == 6)) {
          uVar5 = 0x19;
        }
        QueueOutgoingPacketField(uVar5);
      }
    }
    cVar2 = CheckBothGuardedBools();
    if (cVar2 != '\0') {
      EncodeChecksumDeltaShr(puVar31,auStack_27c,8);
      uStack_50 = 0x10;
      EncodeChecksumDeltaShr(puVar29,auStack_4a0,8);
      SUBFIELD(uStack_50,0,undefined1) = 0x11;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar15 = PeekPacketChecksumState();
      (*pcVar20)(&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar9 = PeekPacketChecksumState();
      (*pcVar20)(&DAT_005a9068);
      iVar4 = g_clientContext;
      piVar22 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar2 = PeekPacketChecksumBool();
      if ((cVar2 == '\0') && ((&DAT_006a7758)[iVar4] != '\0')) {
        if (((&DAT_006a7736)[iVar4] == '\x01') &&
           ((uVar16 = iVar15 - *(int *)(&g_nCameraY + iVar4) >> 0x1f,
            200 < (int)((iVar15 - *(int *)(&g_nCameraY + iVar4) ^ uVar16) - uVar16) ||
            (uVar16 = iVar9 - *(int *)(&g_nCameraX + iVar4) >> 0x1f,
            300 < (int)((iVar9 - *(int *)(&g_nCameraX + iVar4) ^ uVar16) - uVar16))))) {
          (&DAT_006a7736)[iVar4] = 0;
        }
        iVar10 = 400;
        if (399 < iVar9) {
          iVar10 = iVar9;
        }
        iVar17 = *(int *)(&g_nCameraBoundX + iVar4) + -400;
        if ((iVar10 <= iVar17) && (iVar17 = iVar9, iVar9 < 400)) {
          iVar17 = 400;
        }
        iVar9 = -0x14;
        if (-0x15 < iVar15) {
          iVar9 = iVar15;
        }
        iVar10 = *(int *)(&g_nCameraBoundY + iVar4) + -0x104;
        if ((iVar9 <= *(int *)(&g_nCameraBoundY + iVar4) + -0x104) && (iVar10 = -0x14, -0x15 < iVar15))
        {
          iVar10 = iVar15;
        }
        iVar15 = *piVar22 - iVar17;
        *(int *)(&g_nCameraScrollY + iVar4) = iVar10;
        if (((*(int *)(&DAT_006a770c + iVar4) - iVar10) * (*(int *)(&DAT_006a770c + iVar4) - iVar10)
             + iVar15 * iVar15 < 40000) &&
           (((&DAT_006a7734)[iVar4] == '\x01' || ((&DAT_006a7f6c)[iVar4] == '\0')))) {
          *(int *)(&g_nCameraX + iVar4) = iVar17;
          *piVar22 = iVar17;
          *(int *)(&g_nCameraY + iVar4) = iVar10;
          *(int *)(&DAT_006a770c + iVar4) = iVar10;
        }
        if ((((&DAT_006a7734)[iVar4] == '\0') && ((&DAT_006a7f6c)[iVar4] == '\x01')) &&
           ((&DAT_006a7736)[iVar4] == '\0')) {
          iVar15 = *(int *)(&DAT_006a7730 + iVar4);
          iVar9 = iVar15;
          if (iVar17 <= iVar15) {
            iVar9 = iVar17;
          }
          iVar18 = *(int *)(&DAT_006a772c + iVar4);
          if ((iVar18 <= iVar9) && (iVar18 = iVar15, iVar17 <= iVar15)) {
            iVar18 = iVar17;
          }
          *(int *)(&g_nCameraScrollX + iVar4) = iVar18;
        }
        if ((&DAT_006a7734)[iVar4] == '\x01') {
          *(int *)(&g_nCameraScrollX + iVar4) = iVar17;
          *(int *)(&g_nCameraScrollY + iVar4) = iVar10;
        }
      }
      uStack_50 = CONCAT31(SUBFIELD(uStack_50,1,undefined3),0x10);
      if (iStack_48c != 0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound(&stack0xfffff2c4);
      }
      uStack_50 = 0xffffffff;
      if (iStack_268 != 0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound(&stack0xfffff2c4);
      }
    }
    goto LAB_004b1030;
  }
  SyncOutgoingChecksumField(param_1[2],param_1 + 0x45e);
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    puVar31 = &DAT_005a9068;
    (*pcVar20)(&DAT_005a9068);
    if ((-1 < iVar4) && (iVar4 < *(int *)(&g_nCameraBoundX + g_clientContext))) {
      pcVar7 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar4);
      iVar4 = 0;
      if (0 < *(int *)(&g_nCameraBoundY + g_clientContext)) {
        do {
          if (*pcVar7 != '\0') break;
          pcVar7 = pcVar7 + *(int *)(&g_nCameraBoundX + g_clientContext);
          iVar4 = iVar4 + 1;
        } while (iVar4 < *(int *)(&g_nCameraBoundY + g_clientContext));
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    (*pcVar20)(&DAT_005a9068);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,puVar28,iVar4);
    puVar28 = (undefined *)0x1;
    if (0 < param_1[0xfe5]) {
      puVar28 = (undefined *)param_1[0xfe5];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar20)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar20)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar20)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar20)(&DAT_005a9068);
    FUN_0043af40(puVar34,puVar32,0,puVar30,iVar4 / (int)puVar27,puVar31,(char)param_1[0xf]);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar20)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar20)(&DAT_005a9068);
    uVar26 = 0;
    uVar25 = 2;
    uVar6 = 0xff;
    uVar5 = 0;
    puVar29 = puVar28;
    PeekPacketChecksumBool(0,puVar28,0xff,2,0);
    FUN_00431d90((char)param_1[0xf],7,0,uVar5,puVar28,uVar6,uVar25,uVar26);
  }
  cVar3 = (char)((uint)puVar27 >> 0x18);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  cVar24 = '\0';
  (*pcVar20)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  cVar2 = '\0';
  (*pcVar20)();
  puVar31 = puVar29;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar20)(&DAT_005a9068);
  if (cVar3 == '\0') {
    puVar8 = operator_new(0x3fbc);
    uStack_44 = 4;
    if (puVar8 == (undefined4 *)0x0) {
      puVar8 = (undefined4 *)0x0;
    }
    else {
      InitProjectile(puVar8,0x186a9);
      *puVar8 = &PTR_FUN_0055658c;
      puVar8[0xfe7] = 0xffffffff;
    }
    uStack_44 = 0xffffffff;
    iVar4 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar16 = *(uint *)(iVar4 + 4);
    while (uVar16 < 0x186ab) {
      if (uVar16 == 0x186aa) {
        piVar22 = *(int **)(iVar4 + 0x10);
        bVar23 = true;
        if (piVar22[2] == 0) goto LAB_004b00de;
        break;
      }
      iVar4 = *(int *)(iVar4 + 0x1c);
      uVar16 = *(uint *)(iVar4 + 4);
    }
  }
  goto LAB_004b0432;
  while( true ) {
    piVar22 = (int *)piVar22[4];
    bVar23 = piVar22[2] == 0;
    if (!bVar23) break;
LAB_004b00de:
    if (bVar23) {
      iVar4 = piVar22[0xf];
      iVar15 = piVar22[0xe];
      iVar9 = CalculateAngleFromDelta();
      iVar10 = FloatToInt64();
      iVar15 = iVar15 - iVar10;
      iVar10 = FloatToInt64();
      (**(code **)(*piVar22 + 4))(&DAT_00553b90);
      piVar22[0x11] = iVar9;
      cVar3 = PeekPacketChecksumBool();
      if (cVar3 == '\0') {
        uStack_8e0 = 0;
        uStack_aec = 0;
        EncodeOutgoingPacketField((char *)&uStack_aec - 0x14, 0);
        uStack_44 = 7;
        uStack_b04 = 0;
        local_d10 = 0;
        EncodeOutgoingPacketField((char *)&local_d10 - 0x14, 0);
        SUBFIELD(uStack_44,0,undefined1) = 8;
        SyncOutgoingChecksumField(puVar31 + 0x10,&stack0xfffff2dc);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        (*pcVar20)(&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar9 = PeekPacketChecksumState();
        (*pcVar20)(&DAT_005a9068);
        iVar17 = param_1[0xfe5];
        uVar26 = 0;
        uVar25 = 0xff;
        uVar6 = 100;
        uVar5 = 0;
        PeekPacketChecksumBool(puVar29,0,100,0xff,iVar17,0);
        FUN_00432320((char)param_1[0xf],1,1,puVar29,uVar5,uVar6,uVar25,iVar17,uVar26);
        uStack_44 = CONCAT31(SUBFIELD(uStack_44,1,undefined3),7);
        ScrubChecksumGuard();
LAB_004b039b:
        uStack_44 = 0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        cVar3 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&stack0xfffff2d8,&stack0xfffff2c8,2,1,1);
        if (cVar3 != '\0') {
          uStack_b04 = 0;
          local_d10 = 0;
          EncodeOutgoingPacketField((char *)&local_d10 - 0x14, 0);
          uStack_44 = 5;
          uStack_8e0 = 0;
          uStack_aec = 0;
          EncodeOutgoingPacketField((char *)&uStack_aec - 0x14, 0);
          SUBFIELD(uStack_44,0,undefined1) = 6;
          QueueOutgoingPacketField(unaff_EDI);
          QueueOutgoingPacketField(puVar33);
          SyncOutgoingChecksumField(puVar31 + 0x10,auStack_b00);
          iVar17 = param_1[0xfe5];
          uVar11 = 0;
          uVar26 = 0xff;
          uVar25 = 100;
          uVar6 = 0;
          PeekChecksumStateUnderLock(auStack_b00);
          uVar5 = PeekChecksumStateUnderLock(&stack0xfffff2dc);
          PeekPacketChecksumBool(uVar5,uVar6,uVar25,uVar26,iVar17,uVar11);
          FUN_00432320((char)param_1[0xf],1,1,uVar5,uVar6,uVar25,uVar26,iVar17,uVar11);
          uStack_44 = CONCAT31(SUBFIELD(uStack_44,1,undefined3),5);
          ScrubChecksumGuard();
          goto LAB_004b039b;
        }
      }
      puVar8[0xfea] = iVar15;
      puVar8[0xfeb] = iVar4 - iVar10;
      puVar8[0xfec] = unaff_EDI;
      puVar8[0xfed] = puVar33;
      puVar8[0xfee] = iVar9;
      /* angr-confirmed: self is EDI at both real call sites, same
       * unaff_EDI already used just above for puVar8[0xfec]. */
      uVar5 = FUN_004ac4d0(unaff_EDI);
      puVar8[0xfe9] = uVar5;
      iVar4 = FUN_004ac400(unaff_EDI);
      puVar8[0xfe8] = iVar4 * param_1[0xfe5];
      cVar3 = PeekPacketChecksumBool();
      if (cVar3 == '\0') {
        RegisterActiveObject(0, 0, (undefined4 *)0);
      }
      else {
        (**(code **)*puVar8)(1);
      }
      break;
    }
  }
LAB_004b0432:
  *(undefined1 *)(param_1 + 5) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar25 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar26 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar11 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar12 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar13 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar14 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  ApplyCraterExcavation(uVar14,uVar13,uVar12,uVar11,uVar26,uVar25,uVar6,uVar5);
  RebuildTerrainColumnCache(&DAT_006a7708 + g_clientContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00450eb0(uVar6,uVar5,param_1,1,0,0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004372f0(param_1[2],uVar6,uVar5,param_1[0xe25],param_1 + 0xe26);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar25 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00437150(uVar25,uVar6,0x3c,uVar5);
  iVar4 = g_clientContext;
  cVar3 = PeekPacketChecksumBool();
  if (cVar3 != '\x01') {
    iVar15 = *(int *)(&DAT_006a7750 + iVar4);
    if (iVar15 < 0xb) {
      iVar15 = 10;
    }
    *(int *)(&DAT_006a7750 + iVar4) = iVar15;
    iVar15 = *(int *)(&DAT_006a7754 + iVar4);
    if (iVar15 < 0xb) {
      iVar15 = 10;
    }
    *(int *)(&DAT_006a7754 + iVar4) = iVar15;
  }
  cVar3 = PeekPacketChecksumBool();
  if (cVar3 == '\0') {
    AcquireSoundChannel(0);
  }
  cVar3 = PeekPacketChecksumBool();
  pcVar20 = (code *)LeaveCriticalSection;
  if ((cVar3 != '\0') &&
     (cVar3 = InitChecksumSeed(), pcVar20 = (code *)LeaveCriticalSection, cVar3 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    pcVar20 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    QueueOutgoingPacketField(uVar5);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  PeekPacketChecksumState();
  (*pcVar20)(&DAT_005a9068);
  cVar3 = CheckGuardedBoolAnd(uVar12);
  if (cVar3 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    /* NOT FIXED (2026-07-16): self intentionally left off, same as the
     * twin DetonatePrimaryShot_Bullet4.c's analogous site (0x4b07fd here). angr-traced
     * disasm shows edi reloaded from a stack slot whose last write
     * before this call is a `cmp`, not a `mov`/`lea` - not a stable
     * object-pointer expression. Moot in the current bring-up build
     * regardless: uVar12 (this block's own guard) is itself sourced
     * from a stubbed PeekPacketChecksumState call above, so
     * CheckGuardedBoolAnd(uVar12) always returns 0 and this whole
     * if-block is unreachable until PeekPacketChecksumState/
     * CheckGuardedBoolAnd get real bodies. */
    EncodeOutgoingPacketField(uVar5);
    (*pcVar20)(&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar20)(&DAT_005a9068);
  if (cVar24 == '\0') {
LAB_004b085b:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    cVar24 = 0 < iVar4;
    (*pcVar20)(&DAT_005a9068);
    if (cVar24 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState();
      cVar24 = iVar4 < 0;
      (*pcVar20)(&DAT_005a9068);
      if (cVar24 != '\0') goto LAB_004b08a7;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    cVar24 = 0 < iVar4;
    (*pcVar20)(&DAT_005a9068);
    if (cVar24 == '\0') goto LAB_004b085b;
LAB_004b08a7:
    cVar24 = PeekPacketChecksumBool();
    if (cVar24 == '\0') {
      SetGuardedBool(1);
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  PeekPacketChecksumState();
  (*pcVar20)(&DAT_005a9068);
  if ((cVar2 == '\0') || (cVar2 = CompareChecksumPair(param_1 + 0xed2,param_1 + 0xf5b), cVar2 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    iVar15 = PeekPacketChecksumState();
    cVar2 = iVar15 < iVar4;
    (*pcVar20)(&DAT_005a9068);
    if ((cVar2 == '\0') ||
       ((cVar2 = CompareChecksumExceeds(param_1 + 0xed2,param_1 + 0xf5b), cVar2 == '\0' ||
        (param_1[0xed1] < 6)))) goto LAB_004b1030;
  }
  iVar4 = g_clientContext;
  pbVar21 = (byte *)(g_clientContext + 0x62143);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar15 = _rand();
  *pbVar21 = (byte)iVar15;
  iVar15 = _rand();
  bVar1 = *pbVar21;
  *(byte *)(iVar4 + 0x62144) = (byte)iVar15;
  bVar19 = '\x01' << (bVar1 & 7);
  bVar1 = *pbVar21;
  bVar19 = ~bVar19 & (byte)iVar15 | bVar19;
  *(byte *)(iVar4 + 0x62144) = bVar19;
  *(byte *)(iVar4 + 0x62145) = bVar19 + bVar1 + -0x34;
  (*pcVar20)(&DAT_005a9068);
LAB_004b1030:
  *unaff_FS_OFFSET = uStack_58;
  return;
}

