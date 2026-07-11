/* FUN_004aafd0 - 0x004aafd0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004aafd0(int *param_1)

{
  int *piVar1;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  byte bVar16;
  uint uVar17;
  uint unaff_EBX;
  code *pcVar18;
  byte *pbVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  undefined4 uVar22;
  int *local_ad4;
  int local_ad0 [2];
  int iStack_ac8;
  undefined1 auStack_ac4 [16];
  uint uStack_ab4;
  int iStack_ab0;
  undefined1 auStack_8a4 [548];
  undefined1 auStack_680 [548];
  undefined1 auStack_45c [548];
  undefined1 auStack_238 [552];
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053e5d9) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  local_ad4 = (int *)0x0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  iVar8 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar8 + iVar7);
  pcVar18 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_ad0[0] = PeekPacketChecksumState();
  iVar7 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar7 + local_ad0[0]);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar6 = PeekPacketChecksumBool();
  if (cVar6 == '\0') {
    EncodeChecksumDeltaShr(param_1 + 0x10,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar10);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_ab0 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(local_ad0);
      pcVar18 = (code *)LeaveCriticalSection;
    }
    EncodeChecksumDeltaShr(param_1 + 0x99,auStack_ac4,8);
    local_ad4 = param_1 + 0x45e;
    puStack_8 = (undefined1 *)0x1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar10);
    (*pcVar18)(&DAT_005a9068);
    uStack_c = 0xffffffff;
    if (uStack_ab4 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&local_ad4);
      pcVar18 = (code *)LeaveCriticalSection;
      unaff_EBX = uStack_ab4;
    }
    cVar6 = CheckGuardedBoolAnd(param_1[0x3d2] != 0);
    if (cVar6 == '\0') {
      EmitChecksumSum(param_1 + 0x2bd);
      EmitChecksumSum(param_1 + 0x346);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      unaff_EBX = PeekPacketChecksumState();
      (*pcVar18)(&DAT_005a9068);
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
      uVar10 = EncodeChecksumPairDiff(param_1[0x3d2] + 0x38,auStack_8a4,uVar10);
      uStack_c = 3;
      bVar4 = false;
      bVar3 = false;
      cVar6 = CompareChecksumPair(param_1 + 0x3d5,uVar10);
      if (cVar6 == '\0') {
        uVar10 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_45c,4);
        uStack_c = 4;
        uVar10 = EncodeChecksumPairSum(param_1[0x3d2] + 0x38,&iStack_ac8,uVar10);
        uStack_c = 5;
        bVar4 = true;
        bVar3 = true;
        cVar6 = CompareChecksumPair(uVar10,param_1 + 0x3d5);
        bVar5 = false;
        if (cVar6 != '\0') goto LAB_004ab7ad;
      }
      else {
LAB_004ab7ad:
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
          SetGuardedBool(0);
        }
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_ad4 = param_1 + 0x3d5;
    PeekPacketChecksumState();
    (*pcVar18)(&DAT_005a9068);
    if ((char)(unaff_EBX >> 0x18) == '\0') {
      iVar7 = *(int *)(&DAT_006a7720 + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = PeekPacketChecksumState();
      (*pcVar18)(&DAT_005a9068);
      piVar1 = local_ad4;
      if (((iVar7 <= iVar8) ||
          (cVar6 = PacketChecksumGreaterEqual(local_ad4,*(undefined4 *)(&DAT_006a7724 + g_clientContext)),
          cVar6 != '\0')) || (cVar6 = PacketChecksumLessThan(piVar1,0xfffffc18), cVar6 != '\0'))
      goto LAB_004ab968;
    }
    else {
LAB_004ab968:
      *(undefined1 *)(param_1 + 5) = 1;
      cVar6 = PeekPacketChecksumBool();
      if ((cVar6 != '\0') && (cVar6 = FUN_0043a530(), cVar6 == '\0')) {
        iVar7 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
        if ((iVar7 == 5) || (uVar10 = 2, iVar7 == 6)) {
          uVar10 = 0x19;
        }
        QueueOutgoingPacketField(uVar10);
        iVar7 = g_clientContext;
        if (*(int *)(&DAT_005f3768 + g_clientContext) != 0) {
          *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
          *(undefined4 *)(&DAT_005f376c + iVar7) = 0;
        }
      }
    }
    cVar6 = CheckBothGuardedBools();
    if (cVar6 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = PeekPacketChecksumState();
      (*pcVar18)(&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar12 = PeekPacketChecksumState();
      (*pcVar18)(&DAT_005a9068);
      iVar7 = g_clientContext;
      piVar1 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar6 = PeekPacketChecksumBool();
      if ((cVar6 == '\0') && ((&DAT_006a7758)[iVar7] != '\0')) {
        if (((&DAT_006a7736)[iVar7] == '\x01') &&
           ((uVar17 = iVar8 - *(int *)(&DAT_006a7714 + iVar7) >> 0x1f,
            200 < (int)((iVar8 - *(int *)(&DAT_006a7714 + iVar7) ^ uVar17) - uVar17) ||
            (uVar17 = iVar12 - *(int *)(&DAT_006a7710 + iVar7) >> 0x1f,
            300 < (int)((iVar12 - *(int *)(&DAT_006a7710 + iVar7) ^ uVar17) - uVar17))))) {
          (&DAT_006a7736)[iVar7] = 0;
        }
        iVar14 = 400;
        if (399 < iVar12) {
          iVar14 = iVar12;
        }
        iVar13 = *(int *)(&DAT_006a7720 + iVar7) + -400;
        if ((iVar14 <= iVar13) && (iVar13 = iVar12, iVar12 < 400)) {
          iVar13 = 400;
        }
        iVar12 = -0x14;
        if (-0x15 < iVar8) {
          iVar12 = iVar8;
        }
        iVar14 = *(int *)(&DAT_006a7724 + iVar7) + -0x104;
        if ((iVar12 <= iVar14) && (iVar14 = -0x14, -0x15 < iVar8)) {
          iVar14 = iVar8;
        }
        iVar8 = *piVar1 - iVar13;
        *(int *)(&DAT_006a771c + iVar7) = iVar14;
        if (((*(int *)(&DAT_006a770c + iVar7) - iVar14) * (*(int *)(&DAT_006a770c + iVar7) - iVar14)
             + iVar8 * iVar8 < 40000) &&
           (((&DAT_006a7734)[iVar7] == '\x01' || ((&DAT_006a7f6c)[iVar7] == '\0')))) {
          *(int *)(&DAT_006a7710 + iVar7) = iVar13;
          *piVar1 = iVar13;
          *(int *)(&DAT_006a7714 + iVar7) = iVar14;
          *(int *)(&DAT_006a770c + iVar7) = iVar14;
        }
        if ((((&DAT_006a7734)[iVar7] == '\0') && ((&DAT_006a7f6c)[iVar7] == '\x01')) &&
           ((&DAT_006a7736)[iVar7] == '\0')) {
          iVar8 = *(int *)(&DAT_006a7730 + iVar7);
          iVar12 = iVar8;
          if (iVar13 <= iVar8) {
            iVar12 = iVar13;
          }
          iVar15 = *(int *)(&DAT_006a772c + iVar7);
          if ((iVar15 <= iVar12) && (iVar15 = iVar8, iVar13 <= iVar8)) {
            iVar15 = iVar13;
          }
          *(int *)(&DAT_006a7718 + iVar7) = iVar15;
        }
        if ((&DAT_006a7734)[iVar7] == '\x01') {
          *(int *)(&DAT_006a7718 + iVar7) = iVar13;
          *(int *)(&DAT_006a771c + iVar7) = iVar14;
        }
      }
    }
    goto LAB_004abb49;
  }
  cVar6 = PeekPacketChecksumBool();
  if (cVar6 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((-1 < iVar7) && (iVar7 < *(int *)(&DAT_006a7720 + g_clientContext))) {
      pcVar9 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar7);
      iVar7 = 0;
      if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
        do {
          if (*pcVar9 != '\0') goto LAB_004ab0f1;
          pcVar9 = pcVar9 + *(int *)(&DAT_006a7720 + g_clientContext);
          iVar7 = iVar7 + 1;
        } while (iVar7 < *(int *)(&DAT_006a7724 + g_clientContext));
      }
    }
    iVar7 = 10000;
LAB_004ab0f1:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_ad4 = (int *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,local_ad4,iVar7);
    local_ad4 = (int *)0x1;
    if (0 < param_1[0xfe5]) {
      local_ad4 = (int *)param_1[0xfe5];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iStack_ac8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_ad0[0] = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0043af40(uVar11,iVar7,0,local_ad0[0],iStack_ac8 / (int)local_ad4,uVar10,(char)param_1[0xf]);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_ad0[0] = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar22 = 0;
    uVar21 = 2;
    uVar20 = 0xff;
    uVar11 = 0;
    PeekPacketChecksumBool(0,uVar10,0xff,2,0);
    FUN_00431d90((char)param_1[0xf],7,0,uVar11,uVar10,uVar20,uVar21,uVar22);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar10 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar11 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004398e0(&DAT_006a7f70 + g_clientContext,param_1[2] + 1,uVar11,uVar10,param_1,1);
  *(undefined1 *)(param_1 + 5) = 1;
  cVar6 = PeekPacketChecksumBool();
  if (cVar6 == '\0') {
    AcquireSoundChannel(0);
  }
  cVar6 = PeekPacketChecksumBool();
  if ((cVar6 != '\0') && (cVar6 = FUN_0043a530(), cVar6 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    QueueOutgoingPacketField(uVar10);
    iVar7 = g_clientContext;
    if (*(int *)(&DAT_005f3768 + g_clientContext) != 0) {
      *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
      *(undefined4 *)(&DAT_005f376c + iVar7) = 0;
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  iVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar6 = CheckGuardedBoolAnd(iVar7 < iVar8);
  if (cVar6 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar10);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar7 < 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar7 < 1) goto LAB_004ab3f6;
LAB_004ab442:
    cVar6 = PeekPacketChecksumBool();
    if (cVar6 == '\0') {
      SetGuardedBool(1);
    }
  }
  else {
LAB_004ab3f6:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar7) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar7 < 0) goto LAB_004ab442;
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  iVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar8 <= iVar7) || (cVar6 = CompareChecksumPair(param_1 + 0xed2,param_1 + 0xf5b), cVar6 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    iVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar7 <= iVar8) ||
       ((cVar6 = FUN_0040b410(param_1 + 0xed2,param_1 + 0xf5b), cVar6 == '\0' ||
        (param_1[0xed1] < 6)))) goto LAB_004abb49;
  }
  iVar7 = g_clientContext;
  pbVar19 = (byte *)(g_clientContext + 0x62143);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = _rand();
  *pbVar19 = (byte)iVar8;
  iVar8 = _rand();
  bVar2 = *pbVar19;
  *(byte *)(iVar7 + 0x62144) = (byte)iVar8;
  bVar16 = '\x01' << (bVar2 & 7);
  bVar2 = *pbVar19;
  bVar16 = ~bVar16 & (byte)iVar8 | bVar16;
  *(byte *)(iVar7 + 0x62144) = bVar16;
  *(byte *)(iVar7 + 0x62145) = bVar16 + bVar2 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
LAB_004abb49:
  return;
}

