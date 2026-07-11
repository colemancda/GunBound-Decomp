/* FUN_0046af10 - 0x0046af10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0046af10(int *param_1)

{
  int *piVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint unaff_EBX;
  code *pcVar13;
  int *local_ad0;
  int local_acc;
  undefined1 auStack_ac8 [4];
  undefined1 auStack_ac4 [16];
  uint uStack_ab4;
  int *piStack_ab0;
  undefined1 auStack_8a4 [548];
  undefined1 auStack_680 [548];
  undefined1 auStack_45c [548];
  undefined1 auStack_238 [552];
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;

  uStack_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped (handler body
   * LAB_0053d2f9 wasn't included in this function's own decompile;
   * same rationale as entry/InitGame.c - see src/README.md). uStack_c
   * and puStack_8 are real, separate locals reused elsewhere in this
   * function despite the SEH-typical names - kept as-is. */
  local_ad0 = (int *)0x0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  iVar5 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar5 + iVar4);
  pcVar13 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_acc = PeekPacketChecksumState();
  iVar4 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar4 + local_acc);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar3 = PeekPacketChecksumBool();
  if (cVar3 != '\0') {
    *(undefined1 *)(param_1 + 5) = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436220(&DAT_006a7f70 + g_clientContext,uVar7,uVar6);
    goto LAB_0046b5e9;
  }
  EncodeChecksumDeltaShr(param_1 + 0x10,auStack_ac4,8);
  puStack_8 = (undefined1 *)0x0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar6);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)0xffffffff;
  if (piStack_ab0 != (int *)0x0) {
    ScrambleChecksumGuardBytes();
    local_ad0 = piStack_ab0;
    TreeLowerBound(&local_acc);
    pcVar13 = (code *)LeaveCriticalSection;
  }
  EncodeChecksumDeltaShr(param_1 + 0x99,auStack_ac4,8);
  local_ad0 = param_1 + 0x45e;
  puStack_8 = (undefined1 *)0x1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar6);
  (*pcVar13)(&DAT_005a9068);
  uStack_c = 0xffffffff;
  if (uStack_ab4 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&local_ad0);
    pcVar13 = (code *)LeaveCriticalSection;
    unaff_EBX = uStack_ab4;
  }
  cVar3 = CheckGuardedBoolAnd(param_1[0x3d2] != 0);
  if (cVar3 == '\0') {
    EmitChecksumSum(param_1 + 0x2bd);
    EmitChecksumSum(param_1 + 0x346);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    if ((int)((uVar8 ^ (int)uVar8 >> 0x1f) - ((int)uVar8 >> 0x1f)) < 200) {
      cVar3 = PacketChecksumLessThan(param_1 + 0x122,0);
      if (cVar3 == '\0') {
        uVar6 = 200;
      }
      else {
        uVar6 = 0xffffff38;
      }
      QueueOutgoingPacketField(uVar6);
    }
    uVar6 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_680,4);
    uStack_c = 2;
    uVar6 = EncodeChecksumPairDiff(param_1[0x3d2] + 0x38,auStack_8a4,uVar6);
    uStack_c = 3;
    unaff_EBX = 3;
    cVar3 = CompareChecksumPair(param_1 + 0x3d5,uVar6);
    if (cVar3 == '\0') {
      uVar6 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_45c,4);
      uStack_c = 4;
      uVar6 = EncodeChecksumPairSum(param_1[0x3d2] + 0x38,auStack_ac8,uVar6);
      uStack_c = 5;
      unaff_EBX = 0xf;
      cVar3 = CompareChecksumPair(uVar6,param_1 + 0x3d5);
      bVar2 = false;
      if (cVar3 != '\0') goto LAB_0046b275;
    }
    else {
LAB_0046b275:
      bVar2 = true;
    }
    uStack_c = 4;
    if ((unaff_EBX & 8) != 0) {
      unaff_EBX = unaff_EBX & 0xfffffff7;
      ScrubChecksumGuard();
    }
    uStack_c = 3;
    if ((unaff_EBX & 4) != 0) {
      unaff_EBX = unaff_EBX & 0xfffffffb;
      ScrubChecksumGuard();
    }
    uStack_c = 2;
    if ((unaff_EBX & 2) != 0) {
      unaff_EBX = unaff_EBX & 0xfffffffd;
      ScrubChecksumGuard();
    }
    uStack_c = 0xffffffff;
    if ((unaff_EBX & 1) != 0) {
      ScrubChecksumGuard();
    }
    if (bVar2) {
      iVar4 = param_1[0x3d4];
      param_1[0x3d4] = iVar4 + 1;
      if (iVar4 + 1 < 3) {
        uVar6 = EncodeChecksumNegate(param_1 + 0x122,auStack_238);
        uStack_c = 6;
        EncodeChecksumState(uVar6);
        uStack_c = 0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        SetGuardedBool(0);
      }
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_ad0 = param_1 + 0x3d5;
  PeekPacketChecksumState();
  (*pcVar13)(&DAT_005a9068);
  if ((char)(unaff_EBX >> 0x18) == '\0') {
    iVar4 = *(int *)(&g_nCameraBoundX + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    piVar1 = local_ad0;
    if (((iVar4 <= iVar5) ||
        (cVar3 = PacketChecksumGreaterEqual(local_ad0,*(undefined4 *)(&g_nCameraBoundY + g_clientContext)),
        cVar3 != '\0')) || (cVar3 = PacketChecksumLessThan(piVar1,0xfffffc18), cVar3 != '\0'))
    goto LAB_0046b430;
  }
  else {
LAB_0046b430:
    *(undefined1 *)(param_1 + 5) = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar6);
    (*pcVar13)(&DAT_005a9068);
  }
  cVar3 = CheckBothGuardedBools();
  if (cVar3 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar9 = PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    iVar4 = g_clientContext;
    piVar1 = (int *)(&DAT_006a7708 + g_clientContext);
    cVar3 = PeekPacketChecksumBool();
    if ((cVar3 == '\0') && ((&DAT_006a7758)[iVar4] != '\0')) {
      if (((&DAT_006a7736)[iVar4] == '\x01') &&
         ((uVar8 = iVar5 - *(int *)(&g_nCameraY + iVar4) >> 0x1f,
          200 < (int)((iVar5 - *(int *)(&g_nCameraY + iVar4) ^ uVar8) - uVar8) ||
          (uVar8 = iVar9 - *(int *)(&g_nCameraX + iVar4) >> 0x1f,
          300 < (int)((iVar9 - *(int *)(&g_nCameraX + iVar4) ^ uVar8) - uVar8))))) {
        (&DAT_006a7736)[iVar4] = 0;
      }
      iVar11 = 400;
      if (399 < iVar9) {
        iVar11 = iVar9;
      }
      iVar10 = *(int *)(&g_nCameraBoundX + iVar4) + -400;
      if ((iVar11 <= iVar10) && (iVar10 = iVar9, iVar9 < 400)) {
        iVar10 = 400;
      }
      iVar9 = -0x14;
      if (-0x15 < iVar5) {
        iVar9 = iVar5;
      }
      iVar11 = *(int *)(&g_nCameraBoundY + iVar4) + -0x104;
      if ((iVar9 <= iVar11) && (iVar11 = -0x14, -0x15 < iVar5)) {
        iVar11 = iVar5;
      }
      iVar5 = *piVar1 - iVar10;
      *(int *)(&g_nCameraScrollY + iVar4) = iVar11;
      if (((*(int *)(&DAT_006a770c + iVar4) - iVar11) * (*(int *)(&DAT_006a770c + iVar4) - iVar11) +
           iVar5 * iVar5 < 40000) &&
         (((&DAT_006a7734)[iVar4] == '\x01' || ((&DAT_006a7f6c)[iVar4] == '\0')))) {
        *(int *)(&g_nCameraX + iVar4) = iVar10;
        *piVar1 = iVar10;
        *(int *)(&g_nCameraY + iVar4) = iVar11;
        *(int *)(&DAT_006a770c + iVar4) = iVar11;
      }
      if ((((&DAT_006a7734)[iVar4] == '\0') && ((&DAT_006a7f6c)[iVar4] == '\x01')) &&
         ((&DAT_006a7736)[iVar4] == '\0')) {
        iVar5 = *(int *)(&DAT_006a7730 + iVar4);
        iVar9 = iVar5;
        if (iVar10 <= iVar5) {
          iVar9 = iVar10;
        }
        iVar12 = *(int *)(&DAT_006a772c + iVar4);
        if ((iVar12 <= iVar9) && (iVar12 = iVar5, iVar10 <= iVar5)) {
          iVar12 = iVar10;
        }
        *(int *)(&g_nCameraScrollX + iVar4) = iVar12;
      }
      if ((&DAT_006a7734)[iVar4] == '\x01') {
        *(int *)(&g_nCameraScrollX + iVar4) = iVar10;
        *(int *)(&g_nCameraScrollY + iVar4) = iVar11;
      }
    }
  }
LAB_0046b5e9:
  return;
}

