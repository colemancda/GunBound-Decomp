/* FUN_004765d0 - 0x004765d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004765d0(int *param_1)

{
  int *piVar1;
  int *piVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  code *pcVar17;
  undefined4 uVar18;
  char *pcVar19;
  uint uStack_ad8;
  int *apiStack_acc [2];
  undefined1 auStack_ac4 [20];
  int iStack_ab0;
  undefined1 auStack_8a0 [548];
  undefined1 auStack_67c [548];
  undefined1 auStack_458 [548];
  undefined1 auStack_234 [548];
  undefined1 *puStack_8;
  undefined4 uStack_4;

  uStack_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped (handler body
   * LAB_0053c398 wasn't included in this function's own decompile;
   * same rationale as entry/InitGame.c - see src/README.md). puStack_8
   * is a real, separate local reused elsewhere in this function
   * despite the SEH-typical name - kept as-is. */
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x476620
   * (`mov edi,ebx`, ebx = `lea ebx,[esi+0x40]` at 0x4765fe, esi = this
   * file's own param_1) the cell is param_1+0x10 (scaled int* units,
   * byte offset 0x40) - the same cell EncodeChecksumDeltaShr(param_1 +
   * 0x10, ...) below (line ~138) already addresses, confirming the
   * mapping. See tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  iVar8 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_1 + 0x10, iVar8 + iVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x47665a
   * (`mov edi,ebp`, ebp = `lea ebp,[esi+0x264]` at 0x476635) the cell is
   * param_1+0x99 (scaled), the same cell EncodeChecksumDeltaShr(param_1
   * + 0x99, ...) below (line ~149) already addresses. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  iVar8 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_1 + 0x99, iVar8 + iVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar6 = PeekPacketChecksumBool();
  if (cVar6 != '\0') {
    *(undefined1 *)(param_1 + 5) = 1;
    cVar6 = PeekPacketChecksumBool();
    if (cVar6 == '\0') {
      AcquireSoundChannel(0);
    }
    piVar9 = (int *)GetPlayerRecordBySlot(g_clientContext);
    if ((piVar9 != (int *)0x0) && ((short)param_1[0xfe7] == -0xf6)) {
      pcVar19 = s_teleport2_005543cc;
      apiStack_acc[0] = piVar9 + 0x2cc;
      uVar18 = 0x14b6;
      piVar1 = piVar9 + 0x243;
      uVar10 = PeekChecksumStateUnderLock(apiStack_acc[0]);
      uVar11 = PeekChecksumStateUnderLock(piVar1);
      FUN_004372f0(0,uVar11,uVar10,uVar18,pcVar19);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar10 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      piVar2 = param_1 + 0x45e;
      uVar10 = EncodeChecksumDeltaSub(piVar2,auStack_67c,uVar10);
      puStack_8 = (undefined1 *)0x0;
      PeekChecksumStateUnderLock(uVar10);
      PeekChecksumStateUnderLock(param_1 + 0x3d5);
      iVar7 = FindGroundHeightAtColumn();
      iVar8 = PeekChecksumStateUnderLock(piVar2);
      puStack_8 = (undefined1 *)0xffffffff;
      ScrubChecksumGuard();
      if (iVar7 == iVar8) {
        /* EncodeChecksumState is void-returning (see its own
         * definition) - this call site's return-value use is a
         * Ghidra per-call-site decompilation inconsistency, same
         * class as entry/WinMain.c's FUN_004058c0 fix. uVar10 is left
         * uninitialized here as a result. */
        EncodeChecksumState(param_1 + 0x3d5);
        EncodeChecksumState(uVar10);
        EncodeChecksumState(piVar2);
      }
      else {
        cVar6 = PacketChecksumLessThan(param_1 + 0x122,0);
        uStack_ad8 = 2;
        if (cVar6 == '\0') {
          uVar10 = EncodeChecksumDeltaSub(param_1 + 0x3d5,auStack_8a0,1);
        }
        else {
          uStack_ad8 = 1;
          uVar10 = EncodeChecksumDeltaAdd(param_1 + 0x3d5,auStack_ac4,1);
        }
        puStack_8 = (undefined1 *)uStack_ad8;
        EncodeChecksumState(uVar10);
        puStack_8 = (undefined1 *)0x1;
        if ((uStack_ad8 & 2) != 0) {
          uStack_ad8 = uStack_ad8 & 0xfffffffd;
          ScrubChecksumGuard();
        }
        puStack_8 = (undefined1 *)0xffffffff;
        if ((uStack_ad8 & 1) != 0) {
          ScrubChecksumGuard();
        }
        EncodeChecksumState(piVar1);
        EncodeChecksumState(piVar2);
        (**(code **)(*piVar9 + 4))(&DAT_00553bcc);
      }
      pcVar19 = s_teleport1_005535f8;
      uVar18 = 0x14b5;
      uVar10 = PeekChecksumStateUnderLock(apiStack_acc[0]);
      uVar11 = PeekChecksumStateUnderLock(piVar1);
      FUN_004372f0(1,uVar11,uVar10,uVar18,pcVar19);
    }
    cVar6 = PeekPacketChecksumBool();
    if ((cVar6 != '\0') && (cVar6 = InitChecksumSeed(), cVar6 == '\0')) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar10 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      QueueOutgoingPacketField(uVar10);
    }
    goto LAB_00476f35;
  }
  EncodeChecksumDeltaShr(param_1 + 0x10,auStack_ac4,8);
  puStack_8 = (undefined1 *)0x3;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x476961
   * (`lea edi,[esi+0xf54]` at 0x47694d, esi = param_1) the cell is
   * param_1+0x3d5 (scaled), the same cell reused throughout this
   * function (PeekChecksumStateUnderLock/EncodeChecksumState/
   * EncodeChecksumDeltaSub(param_1 + 0x3d5, ...) above). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar10 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_1 + 0x3d5, uVar10);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_ab0 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(apiStack_acc);
  }
  EncodeChecksumDeltaShr(param_1 + 0x99,auStack_ac4,8);
  pcVar17 = (code *)EnterCriticalSection;
  puStack_8 = (undefined1 *)0x4;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4769de
   * (`mov edi,ebx`, ebx = `lea ebx,[esi+0x1178]` at 0x4769cc) the cell
   * is param_1+0x45e (scaled), the same cell used elsewhere in this
   * function (piVar2 = param_1 + 0x45e above; PacketChecksumGreaterEqual/
   * PacketChecksumLessThan(param_1 + 0x45e, ...) below). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar10 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_1 + 0x45e, uVar10);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_ab0 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(apiStack_acc);
  }
  cVar6 = CheckGuardedBoolAnd(param_1[0x3d2] != 0);
  if (cVar6 == '\0') {
    EmitChecksumSum(param_1 + 0x2bd);
    EmitChecksumSum(param_1 + 0x346);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar12 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((int)((uVar12 ^ (int)uVar12 >> 0x1f) - ((int)uVar12 >> 0x1f)) < 200) {
      cVar6 = PacketChecksumLessThan(param_1 + 0x122,0);
      if (cVar6 == '\0') {
        uVar10 = 200;
      }
      else {
        uVar10 = 0xffffff38;
      }
      QueueOutgoingPacketField(uVar10);
    }
    uVar10 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_458,4);
    puStack_8 = (undefined1 *)0x5;
    uVar10 = EncodeChecksumPairDiff(param_1[0x3d2] + 0x38,auStack_67c,uVar10);
    puStack_8 = (undefined1 *)0x6;
    bVar4 = false;
    bVar3 = false;
    cVar6 = CompareChecksumPair(param_1 + 0x3d5,uVar10);
    if (cVar6 == '\0') {
      uVar10 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_8a0,4);
      puStack_8 = (undefined1 *)0x7;
      uVar10 = EncodeChecksumPairSum(param_1[0x3d2] + 0x38,auStack_ac4,uVar10);
      puStack_8 = (undefined1 *)0x8;
      bVar4 = true;
      bVar3 = true;
      cVar6 = CompareChecksumPair(uVar10,param_1 + 0x3d5);
      bVar5 = false;
      if (cVar6 != '\0') goto LAB_00476b65;
    }
    else {
LAB_00476b65:
      bVar5 = true;
    }
    puStack_8 = (undefined1 *)0x7;
    if (bVar3) {
      ScrubChecksumGuard();
    }
    puStack_8 = (undefined1 *)0x6;
    if (bVar4) {
      ScrubChecksumGuard();
    }
    puStack_8 = (undefined1 *)0x5;
    ScrubChecksumGuard();
    puStack_8 = (undefined1 *)0xffffffff;
    ScrubChecksumGuard();
    if (bVar5) {
      iVar7 = param_1[0x3d4];
      param_1[0x3d4] = iVar7 + 1;
      if (iVar7 + 1 < 3) {
        uVar10 = EncodeChecksumNegate(param_1 + 0x122,auStack_234);
        puStack_8 = (undefined1 *)0x9;
        EncodeChecksumState(uVar10);
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        SetGuardedBool(0);
      }
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar7 < 0) {
LAB_00476d03:
    *(undefined1 *)(param_1 + 5) = 1;
    cVar6 = PeekPacketChecksumBool();
    if ((cVar6 != '\0') && (cVar6 = InitChecksumSeed(), cVar6 == '\0')) {
      iVar7 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
      if ((iVar7 == 5) || (uVar10 = 2, iVar7 == 6)) {
        uVar10 = 0x19;
      }
      QueueOutgoingPacketField(uVar10);
    }
  }
  else {
    iVar7 = *(int *)(&g_nCameraBoundX + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (((iVar7 <= iVar8) ||
        (cVar6 = PacketChecksumGreaterEqual(param_1 + 0x45e,*(undefined4 *)(&g_nCameraBoundY + g_clientContext)),
        cVar6 != '\0')) || (cVar6 = PacketChecksumLessThan(param_1 + 0x45e,0xfffffc18), cVar6 != '\0'))
    goto LAB_00476d03;
  }
  cVar6 = CheckBothGuardedBools();
  if (cVar6 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar13 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = g_clientContext;
    piVar9 = (int *)(&DAT_006a7708 + g_clientContext);
    cVar6 = PeekPacketChecksumBool();
    if ((cVar6 == '\0') && ((&DAT_006a7758)[iVar7] != '\0')) {
      if (((&DAT_006a7736)[iVar7] == '\x01') &&
         ((uVar12 = iVar8 - *(int *)(&g_nCameraY + iVar7) >> 0x1f,
          200 < (int)((iVar8 - *(int *)(&g_nCameraY + iVar7) ^ uVar12) - uVar12) ||
          (uVar12 = iVar13 - *(int *)(&g_nCameraX + iVar7) >> 0x1f,
          300 < (int)((iVar13 - *(int *)(&g_nCameraX + iVar7) ^ uVar12) - uVar12))))) {
        (&DAT_006a7736)[iVar7] = 0;
      }
      iVar15 = 400;
      if (399 < iVar13) {
        iVar15 = iVar13;
      }
      iVar14 = *(int *)(&g_nCameraBoundX + iVar7) + -400;
      if ((iVar15 <= iVar14) && (iVar14 = iVar13, iVar13 < 400)) {
        iVar14 = 400;
      }
      iVar13 = -0x14;
      if (-0x15 < iVar8) {
        iVar13 = iVar8;
      }
      iVar15 = *(int *)(&g_nCameraBoundY + iVar7) + -0x104;
      if ((iVar13 <= iVar15) && (iVar15 = iVar8, iVar8 < -0x14)) {
        iVar15 = -0x14;
      }
      iVar8 = *piVar9 - iVar14;
      *(int *)(&g_nCameraScrollY + iVar7) = iVar15;
      if (((*(int *)(&DAT_006a770c + iVar7) - iVar15) * (*(int *)(&DAT_006a770c + iVar7) - iVar15) +
           iVar8 * iVar8 < 40000) &&
         (((&DAT_006a7734)[iVar7] == '\x01' || ((&DAT_006a7f6c)[iVar7] == '\0')))) {
        *(int *)(&g_nCameraX + iVar7) = iVar14;
        *piVar9 = iVar14;
        *(int *)(&g_nCameraY + iVar7) = iVar15;
        *(int *)(&DAT_006a770c + iVar7) = iVar15;
      }
      if ((((&DAT_006a7734)[iVar7] == '\0') && ((&DAT_006a7f6c)[iVar7] == '\x01')) &&
         ((&DAT_006a7736)[iVar7] == '\0')) {
        iVar8 = *(int *)(&DAT_006a7730 + iVar7);
        iVar13 = iVar8;
        if (iVar14 <= iVar8) {
          iVar13 = iVar14;
        }
        iVar16 = *(int *)(&DAT_006a772c + iVar7);
        if ((iVar16 <= iVar13) && (iVar16 = iVar8, iVar14 <= iVar8)) {
          iVar16 = iVar14;
        }
        *(int *)(&g_nCameraScrollX + iVar7) = iVar16;
      }
      pcVar17 = (code *)EnterCriticalSection;
      if ((&DAT_006a7734)[iVar7] == '\x01') {
        *(int *)(&g_nCameraScrollX + iVar7) = iVar14;
        *(int *)(&g_nCameraScrollY + iVar7) = iVar15;
      }
    }
  }
  (*pcVar17)(&DAT_005a9068);
  uVar10 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar17)(&DAT_005a9068);
  uVar11 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00436980(uVar11,uVar10,(short)param_1[0xfe9]);
LAB_00476f35:
  return;
}

