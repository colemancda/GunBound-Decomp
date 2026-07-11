/* FUN_0045ed80 - 0x0045ed80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0045ed80(int *param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  char *pcVar9;
  undefined1 auStack_924 [8];
  char acStack_91c [128];
  undefined1 auStack_89c [548];
  undefined1 auStack_678 [548];
  undefined1 auStack_454 [548];
  undefined1 auStack_230 [20];
  int iStack_21c;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053a1cc) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  iVar6 = param_1[0x2c29];
  if (iVar6 != -1) {
    if ((DAT_00793549 != '\0') &&
       ((**(code **)(**(int **)(DAT_00793554 + iVar6 * 4) + 0xc))(), iVar6 == 0)) {
      DAT_00793568 = 0;
    }
    param_1[0x2c29] = -1;
  }
  switch(param_1[9]) {
  case 0:
    uVar2 = _rand();
    uVar2 = uVar2 & 0x80000007;
    bVar8 = uVar2 == 0;
    if ((int)uVar2 < 0) {
      bVar8 = (uVar2 - 1 | 0xfffffff8) == 0xffffffff;
    }
    if ((!bVar8) || (cVar1 = PeekPacketChecksumBool(), cVar1 != '\0')) {
      (**(code **)(*param_1 + 4))(s_normal_00552230);
      goto LAB_0045f2bb;
    }
    pcVar9 = s_emotion1_00555cb4;
    goto LAB_0045f2b4;
  default:
    if (param_1[0x2b90] != -1) {
      _sprintf(acStack_91c,s_emotion_d_00555ca8,param_1[0x2b90] % 10);
      (**(code **)(*param_1 + 4))(acStack_91c);
      param_1[0x2b90] = param_1[0x2b91];
      param_1[0x2b91] = param_1[0x2b92];
      param_1[0x2b92] = param_1[0x2b93];
      param_1[0x2b93] = param_1[0x2b94];
      param_1[0x2b94] = param_1[0x2b95];
      param_1[0x2b95] = param_1[0x2b96];
      param_1[0x2b96] = param_1[0x2b97];
      param_1[0x2b97] = param_1[0x2b98];
      param_1[0x2b98] = param_1[0x2b99];
      param_1[0x2b99] = -1;
      goto LAB_0045f2bb;
    }
    EncodeChecksumDeltaDiv(param_1 + 0x19d1,auStack_230,3);
    uStack_4 = 3;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    iVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_4 = 0xffffffff;
    if (iStack_21c != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(auStack_924);
    }
    if (iVar6 < iVar7) {
      (**(code **)(*param_1 + 4))(s_wnormal_00553618);
      goto LAB_0045f2bb;
    }
    pcVar9 = s_normal_00552230;
LAB_0045f2b4:
    (**(code **)(*param_1 + 4))(pcVar9);
    goto LAB_0045f2bb;
  case 5:
    cVar1 = FUN_004067c0();
    if (cVar1 != '\0') {
      cVar1 = PeekPacketChecksumBool();
      puVar3 = &DAT_00553b70;
      if (cVar1 != '\x01') {
        puVar3 = &DAT_00553b68;
      }
LAB_0045ef56:
      (**(code **)(*param_1 + 4))(puVar3);
      FUN_00406500(0);
      FUN_00406500(0);
      goto LAB_0045f2bb;
    }
    uVar4 = EncodeChecksumDeltaDiv(param_1 + 0x19d1,auStack_454,3);
    uStack_4 = 0;
    cVar1 = FUN_0040b490(param_1 + 0x1a5a,uVar4);
    uStack_4 = 0xffffffff;
    ScrubChecksumGuard();
    if (cVar1 == '\0') {
      (**(code **)(*param_1 + 4))(s_normal_00552230);
    }
    else {
      (**(code **)(*param_1 + 4))(s_wnormal_00553618);
    }
    cVar1 = FUN_0040b330(param_1 + 0x2cc,*(undefined4 *)(&DAT_006a7724 + g_clientContext));
    if (cVar1 == '\0') goto LAB_0045f2bb;
    iVar6 = *(int *)(g_gameStateVTableArray[0xb] + 0x10a0);
    iVar5 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
    iVar7 = g_clientContext;
    if (iVar6 != iVar5) {
      if (*(char *)(g_clientContext + 0x4590c + iVar6) != *(char *)(g_clientContext + 0x3b6c0)) {
        *(undefined4 *)(*(int *)(g_clientContext + 0x621e0) + 0xb0b0) = 1;
      }
LAB_0045f039:
      if (*(char *)(iVar7 + 0x4590c + iVar6) == *(char *)(iVar7 + 0x3b6c0)) {
        *(undefined4 *)(*(int *)(iVar7 + 0x621e0) + 0xb0b0) = 2;
      }
      goto LAB_0045f2bb;
    }
    break;
  case 6:
    cVar1 = FUN_004067c0();
    if (cVar1 != '\0') {
      cVar1 = PeekPacketChecksumBool();
      puVar3 = &DAT_00553b68;
      if (cVar1 != '\x01') {
        puVar3 = &DAT_00553b70;
      }
      goto LAB_0045ef56;
    }
    uVar4 = EncodeChecksumDeltaDiv(param_1 + 0x19d1,auStack_89c,3);
    uStack_4 = 1;
    cVar1 = FUN_0040b490(param_1 + 0x1a5a,uVar4);
    uStack_4 = 0xffffffff;
    ScrubChecksumGuard();
    if (cVar1 == '\0') {
      (**(code **)(*param_1 + 4))(s_normal_00552230);
    }
    else {
      (**(code **)(*param_1 + 4))(s_wnormal_00553618);
    }
    cVar1 = FUN_0040b330(param_1 + 0x2cc,*(undefined4 *)(&DAT_006a7724 + g_clientContext));
    if (cVar1 == '\0') goto LAB_0045f2bb;
    iVar6 = *(int *)(g_gameStateVTableArray[0xb] + 0x10a0);
    iVar5 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
    iVar7 = g_clientContext;
    if (iVar6 != iVar5) {
      if (*(char *)(g_clientContext + 0x4590c + iVar6) != *(char *)(g_clientContext + 0x3b6c0)) {
        *(undefined4 *)(*(int *)(g_clientContext + 0x621e0) + 0xb0b0) = 1;
      }
      goto LAB_0045f039;
    }
    break;
  case 8:
    uVar4 = EncodeChecksumDeltaDiv(param_1 + 0x19d1,auStack_678,3);
    uStack_4 = 2;
    cVar1 = FUN_0040b490(param_1 + 0x1a5a,uVar4);
    uStack_4 = 0xffffffff;
    ScrubChecksumGuard();
    if (cVar1 == '\0') {
      (**(code **)(*param_1 + 4))(s_normal_00552230);
    }
    else {
      (**(code **)(*param_1 + 4))(s_wnormal_00553618);
    }
    cVar1 = FUN_0040b330(param_1 + 0x2cc,*(undefined4 *)(&DAT_006a7724 + g_clientContext));
    if (cVar1 == '\0') goto LAB_0045f2bb;
    iVar6 = *(int *)(g_gameStateVTableArray[0xb] + 0x10a0);
    iVar5 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
    iVar7 = g_clientContext;
    if (iVar6 != iVar5) {
      if (*(char *)(g_clientContext + 0x4590c + iVar6) != *(char *)(g_clientContext + 0x3b6c0)) {
        *(undefined4 *)(*(int *)(g_clientContext + 0x621e0) + 0xb0b0) = 1;
      }
      if (*(char *)(iVar7 + 0x4590c + iVar6) == *(char *)(iVar7 + 0x3b6c0)) {
        *(undefined4 *)(*(int *)(iVar7 + 0x621e0) + 0xb0b0) = 2;
      }
      goto LAB_0045f2bb;
    }
  }
  *(undefined4 *)(*(int *)(g_clientContext + 0x621e0) + 0xb0b0) = 3;
LAB_0045f2bb:
  return;
}

