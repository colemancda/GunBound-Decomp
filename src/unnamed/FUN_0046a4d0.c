/* FUN_0046a4d0 - 0x0046a4d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 32 argless PeekPacketChecksumState() calls and the 6 1-arg
 * EncodeOutgoingPacketField() calls (worklist 32:32).  this=EBX until
 * 0x46a696 (`add ebx,0xf54` destroys it), then reloaded from frame[0x20]
 * (0x46a504 `mov [esp+0x24],ebx` one push deep) - the C's param_1 /
 * piVar16.  Cells are all this-relative (int-index = byte offset / 4:
 * +0x40=0x10, +0x264=0x99, +0x488=0x122, +0x6ac=0x1ab, +0xf54=0x3d5,
 * +0x1178=0x45e, +0x15c0=0x570, and the crater series 0x2f74..0x24c0)
 * except the two Encodes into g_clientContext+0x6240c fed by the
 * &DAT_00e9ba40 peek (0x46a8e4/0x46ad1a).  frame[0x14]/frame[0x1c] hold
 * the this+0xf54 / this+0x1178 cell POINTERS (0x46a729, 0x46a708,
 * 0x46a9ba, 0x46ac8b), so the tail peeks through them (0x46a781,
 * 0x46a7b9, 0x46a850, 0x46ad72, 0x46ad8b) are those cells.  Two chained
 * returns: the discarded EncodeChecksumDeltaShr results (0x46a927 /
 * 0x46a9a2 `mov edi,eax` -> `mov eax,edi; call Peek`) are now captured
 * in pvDelta.  Ghidra's reassignments of local_adc[0]/param_1 to Peek
 * results are pre-existing data-flow artifacts and were left alone.
 */
#include "ghidra_types.h"


void __fastcall FUN_0046a4d0(int *param_1)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int *piVar16;
  undefined4 *unaff_FS_OFFSET;
  void *pvDelta;
  int *local_adc [2];
  undefined4 uStack_ad4;
  undefined4 uStack_ad0;
  undefined4 uStack_acc;
  undefined4 uStack_ac8;
  undefined1 auStack_ac4 [20];
  int iStack_ab0;
  undefined1 auStack_8a0 [548];
  undefined1 auStack_67c [548];
  undefined1 auStack_458 [548];
  undefined1 auStack_234 [548];
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053fe59;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_adc[0] = param_1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x10));
  iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x122));
  EncodeOutgoingPacketField((void *)(param_1 + 0x10), iVar6 + iVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar7 = (int *)PeekPacketChecksumState((void *)(param_1 + 0x99));
  iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x1ab));
  EncodeOutgoingPacketField((void *)(param_1 + 0x99), iVar5 + (int)piVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar4 = PeekPacketChecksumBool();
  if (cVar4 != '\0') {
    *(undefined1 *)(param_1 + 5) = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x1ab));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar9 = PeekPacketChecksumState((void *)(param_1 + 0x122));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState((void *)(param_1 + 0xbdd));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_acc = PeekPacketChecksumState((void *)(param_1 + 0xb54));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_ad0 = PeekPacketChecksumState((void *)(param_1 + 0xacb));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_ac8 = PeekPacketChecksumState((void *)(param_1 + 0xa42));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_ad4 = PeekPacketChecksumState((void *)(param_1 + 0x9b9));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_adc[0] = (int *)PeekPacketChecksumState((void *)(param_1 + 0x930));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState((void *)(param_1 + 0x45e));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    ApplyCraterExcavation(local_adc[0],uStack_ad4,uStack_ac8,uStack_ad0,uStack_acc,uVar10,uVar9,uVar8);
    RebuildTerrainColumnCache(&DAT_006a7708 + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x45e));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_adc[0] = (int *)PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00450eb0(local_adc[0],uVar8,piVar7,1,0,0);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x45e));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar9 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436ac0(uVar9,uVar8);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x45e));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_adc[0] = (int *)PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_004372f0(piVar7[2],local_adc[0],uVar8,piVar7[0xe25],piVar7 + 0xe26);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x570));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar9 = PeekPacketChecksumState((void *)(param_1 + 0x45e));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_adc[0] = (int *)PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00437150(local_adc[0],uVar9,0x3c,uVar8);
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
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(&DAT_00e9ba40));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(g_clientContext + 0x6240c), uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    goto LAB_0046aec1;
  }
  pvDelta = EncodeChecksumDeltaShr(param_1 + 0x10,auStack_ac4,8);
  puStack_8 = (undefined1 *)0x0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(pvDelta));
  EncodeOutgoingPacketField((void *)(param_1 + 0x3d5), uVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_ab0 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_adc);
    param_1 = piVar7;
  }
  pvDelta = EncodeChecksumDeltaShr(param_1 + 0x99,auStack_ac4,8);
  puStack_8 = (undefined1 *)0x1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(pvDelta));
  EncodeOutgoingPacketField((void *)(param_1 + 0x45e), uVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)0xffffffff;
  piVar16 = param_1;
  if (iStack_ab0 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_adc);
    piVar16 = piVar7;
  }
  cVar4 = CheckGuardedBoolAnd(piVar16[0x3d2] != 0);
  if (cVar4 == '\0') {
    EmitChecksumSum(piVar16 + 0x122, piVar16 + 0x2bd);
    EmitChecksumSum(piVar16 + 0x1ab, piVar16 + 0x346);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = PeekPacketChecksumState((void *)(piVar16 + 0x122));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((int)((uVar11 ^ (int)uVar11 >> 0x1f) - ((int)uVar11 >> 0x1f)) < 200) {
      cVar4 = PacketChecksumLessThan(piVar16 + 0x122,0);
      if (cVar4 == '\0') {
        uVar8 = 200;
      }
      else {
        uVar8 = 0xffffff38;
      }
      QueueOutgoingPacketField(uVar8);
    }
    uVar8 = EncodeChecksumDeltaDiv(piVar16[0x3d2] + 0x25c,auStack_67c,4);
    puStack_8 = (undefined1 *)0x2;
    uVar8 = EncodeChecksumPairDiff(piVar16[0x3d2] + 0x38,auStack_8a0,uVar8);
    puStack_8 = (undefined1 *)0x3;
    bVar2 = false;
    bVar1 = false;
    cVar4 = CompareChecksumPair(piVar16 + 0x3d5,uVar8);
    if (cVar4 == '\0') {
      uVar8 = EncodeChecksumDeltaDiv(piVar16[0x3d2] + 0x25c,auStack_458,4);
      puStack_8 = (undefined1 *)0x4;
      uVar8 = EncodeChecksumPairSum(piVar16[0x3d2] + 0x38,auStack_ac4,uVar8);
      puStack_8 = (undefined1 *)0x5;
      bVar2 = true;
      bVar1 = true;
      cVar4 = CompareChecksumPair(uVar8,piVar16 + 0x3d5);
      bVar3 = false;
      if (cVar4 != '\0') goto LAB_0046ab4e;
    }
    else {
LAB_0046ab4e:
      bVar3 = true;
    }
    puStack_8 = (undefined1 *)0x4;
    if (bVar1) {
      ScrubChecksumGuard();
    }
    puStack_8 = (undefined1 *)0x3;
    if (bVar2) {
      ScrubChecksumGuard();
    }
    puStack_8 = (undefined1 *)0x2;
    ScrubChecksumGuard();
    puStack_8 = (undefined1 *)0xffffffff;
    ScrubChecksumGuard();
    if (bVar3) {
      iVar5 = piVar16[0x3d4];
      piVar16[0x3d4] = iVar5 + 1;
      if (iVar5 + 1 < 3) {
        uVar8 = EncodeChecksumNegate(piVar16 + 0x122,auStack_234);
        puStack_8 = (undefined1 *)0x6;
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
  iVar5 = PeekPacketChecksumState((void *)(piVar16 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar5 < 0) {
LAB_0046ad0a:
    *(undefined1 *)(piVar16 + 5) = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(&DAT_00e9ba40));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(g_clientContext + 0x6240c), uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  else {
    iVar5 = *(int *)(&g_nCameraBoundX + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState((void *)(piVar16 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (((iVar5 <= iVar6) ||
        (cVar4 = PacketChecksumGreaterEqual(param_1 + 0x45e,*(undefined4 *)(&g_nCameraBoundY + g_clientContext)),
        cVar4 != '\0')) || (cVar4 = PacketChecksumLessThan(param_1 + 0x45e,0xfffffc18), cVar4 != '\0'))
    goto LAB_0046ad0a;
  }
  cVar4 = CheckBothGuardedBools();
  if (cVar4 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x45e));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar12 = PeekPacketChecksumState((void *)(piVar16 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = g_clientContext;
    piVar7 = (int *)(&DAT_006a7708 + g_clientContext);
    cVar4 = PeekPacketChecksumBool();
    if ((cVar4 == '\0') && ((&DAT_006a7758)[iVar5] != '\0')) {
      if (((&DAT_006a7736)[iVar5] == '\x01') &&
         ((uVar11 = iVar6 - *(int *)(&g_nCameraY + iVar5) >> 0x1f,
          200 < (int)((iVar6 - *(int *)(&g_nCameraY + iVar5) ^ uVar11) - uVar11) ||
          (uVar11 = iVar12 - *(int *)(&g_nCameraX + iVar5) >> 0x1f,
          300 < (int)((iVar12 - *(int *)(&g_nCameraX + iVar5) ^ uVar11) - uVar11))))) {
        (&DAT_006a7736)[iVar5] = 0;
      }
      iVar14 = 400;
      if (399 < iVar12) {
        iVar14 = iVar12;
      }
      iVar13 = *(int *)(&g_nCameraBoundX + iVar5) + -400;
      if ((iVar14 <= iVar13) && (iVar13 = iVar12, iVar12 < 400)) {
        iVar13 = 400;
      }
      iVar12 = -0x14;
      if (-0x15 < iVar6) {
        iVar12 = iVar6;
      }
      iVar14 = *(int *)(&g_nCameraBoundY + iVar5) + -0x104;
      if ((iVar12 <= iVar14) && (iVar14 = -0x14, -0x15 < iVar6)) {
        iVar14 = iVar6;
      }
      iVar6 = *piVar7 - iVar13;
      *(int *)(&g_nCameraScrollY + iVar5) = iVar14;
      if (((*(int *)(&DAT_006a770c + iVar5) - iVar14) * (*(int *)(&DAT_006a770c + iVar5) - iVar14) +
           iVar6 * iVar6 < 40000) &&
         (((&DAT_006a7734)[iVar5] == '\x01' || ((&DAT_006a7f6c)[iVar5] == '\0')))) {
        *(int *)(&g_nCameraX + iVar5) = iVar13;
        *piVar7 = iVar13;
        *(int *)(&g_nCameraY + iVar5) = iVar14;
        *(int *)(&DAT_006a770c + iVar5) = iVar14;
      }
      if ((((&DAT_006a7734)[iVar5] == '\0') && ((&DAT_006a7f6c)[iVar5] == '\x01')) &&
         ((&DAT_006a7736)[iVar5] == '\0')) {
        iVar6 = *(int *)(&DAT_006a7730 + iVar5);
        iVar12 = iVar6;
        if (iVar13 <= iVar6) {
          iVar12 = iVar13;
        }
        iVar15 = *(int *)(&DAT_006a772c + iVar5);
        if ((iVar15 <= iVar12) && (iVar15 = iVar6, iVar13 <= iVar6)) {
          iVar15 = iVar13;
        }
        *(int *)(&g_nCameraScrollX + iVar5) = iVar15;
      }
      if ((&DAT_006a7734)[iVar5] == '\x01') {
        *(int *)(&g_nCameraScrollX + iVar5) = iVar13;
        *(int *)(&g_nCameraScrollY + iVar5) = iVar14;
      }
    }
  }
LAB_0046aec1:
  *unaff_FS_OFFSET = uStack_10;
  return;
}

