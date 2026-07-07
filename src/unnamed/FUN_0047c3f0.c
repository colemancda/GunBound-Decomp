/* FUN_0047c3f0 - 0x0047c3f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0047c3f0(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined *puVar6;
  int iVar7;
  int *unaff_ESI;
  int unaff_EDI;
  code *pcVar8;
  int *unaff_FS_OFFSET;
  float10 fVar9;
  uint uStack_ad4;
  int aiStack_acc [2];
  undefined1 auStack_ac4 [20];
  int iStack_ab0;
  undefined1 auStack_8ac [16];
  int iStack_89c;
  undefined1 auStack_684 [12];
  int iStack_678;
  undefined1 auStack_458 [20];
  int iStack_444;
  undefined1 auStack_234 [4];
  int iStack_230;
  undefined4 uStack_18;
  undefined4 uStack_14;
  int iStack_10;
  int iStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_00539b25;
  iStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (int)&iStack_c;
  unaff_ESI[0xfef] = 3;
  (**(code **)(*unaff_ESI + 4))();
  iVar2 = GetPlayerRecordBySlot(DAT_005b3484);
  if (iVar2 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    pcVar8 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar3 != 1) {
      *(undefined1 *)(unaff_ESI + 5) = 1;
      goto LAB_0047ca25;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    unaff_ESI[0xfed] = iVar3;
    aiStack_acc[0] =
         FUN_0040a5f0(iVar2 + 0xb30,auStack_458,
                      (-(uint)((char)unaff_ESI[0xfe8] != '\0') & 0xffffff38) - 200);
    puStack_8 = (undefined1 *)0x0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    aiStack_acc[0] = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (*(int *)(&DAT_006a7724 + DAT_005b3484) + iVar3 < aiStack_acc[0]) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = *(int *)(&DAT_006a7724 + DAT_005b3484) + iVar3;
    }
    else {
      FUN_0040a5f0(iVar2 + 0xb30,auStack_ac4,
                   (-(uint)((char)unaff_ESI[0xfe8] != '\0') & 0xffffff38) - 200);
      puStack_8 = (undefined1 *)CONCAT31(puStack_8._1_3_,1);
      uStack_ad4 = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0x0;
    unaff_ESI[0xfee] = iVar3;
    if (((uStack_ad4 & 1) != 0) && (uStack_ad4 = uStack_ad4 & 0xfffffffe, iStack_ab0 != 0)) {
      FUN_0040a240();
      FUN_0040b540(aiStack_acc);
    }
    puStack_8 = (undefined1 *)0xffffffff;
    pcVar8 = (code *)LeaveCriticalSection;
    if (iStack_444 != 0) {
      FUN_0040a240();
      FUN_0040b540(aiStack_acc);
      pcVar8 = (code *)LeaveCriticalSection;
    }
  }
  iVar3 = iVar2 + 0xb30;
  *(undefined1 *)(unaff_ESI + 0xff9) = 0;
  *(undefined1 *)(unaff_ESI + 0xff2) = 1;
  FUN_0040a6e0(iVar3,auStack_234,400);
  puStack_8 = (undefined1 *)0x2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  aiStack_acc[0] = PeekPacketChecksumState();
  (*pcVar8)(&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar8)(&DAT_005a9068);
  if ((int)(*(int *)(&DAT_006a7724 + DAT_005b3484) + uStack_ad4) < unaff_EDI) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    (*pcVar8)(&DAT_005a9068);
    puVar6 = &DAT_00553f90 + *(int *)(&DAT_006a7724 + DAT_005b3484);
  }
  else {
    FUN_0040a6e0(iVar3,auStack_684,400);
    iStack_10 = CONCAT31(iStack_10._1_3_,3);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    (*pcVar8)(&DAT_005a9068);
    puVar6 = &DAT_00553f90;
  }
  FUN_0040a6e0(iVar3,auStack_8ac,puVar6);
  uStack_14 = 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  (*pcVar8)(&DAT_005a9068);
  uStack_18 = CONCAT31(uStack_18._1_3_,3);
  unaff_ESI[0xff3] = iVar3;
  if (iStack_89c != 0) {
    FUN_0040a240();
    FUN_0040b540(&stack0xfffff524);
  }
  uStack_18 = 2;
  if (((uVar5 & 2) != 0) && (iStack_678 != 0)) {
    FUN_0040a240();
    FUN_0040b540(&stack0xfffff524);
  }
  uStack_18 = 0xffffffff;
  if (iStack_230 != 0) {
    FUN_0040a240();
    FUN_0040b540(&stack0xfffff524);
  }
  fVar9 = (float10)_DAT_00558070;
  unaff_ESI[0xff4] = 1;
  fptan(fVar9);
  iVar3 = FUN_0053753c();
  if (iStack_c < 0) {
    iVar7 = iVar3 / 2 + iVar3 + iStack_10;
    iVar3 = -iVar3;
    unaff_ESI[0xff7] = 0x108;
    unaff_ESI[0xff8] = 4;
  }
  else {
    iVar7 = (iStack_10 - iVar3 / 2) - iVar3;
    unaff_ESI[0xff7] = 0x114;
    unaff_ESI[0xff8] = -4;
  }
  unaff_ESI[0xff6] = iVar3;
  unaff_ESI[0xff5] = iVar7;
  unaff_ESI[0xfed] = iVar7;
  if (cRam0055a4ac == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  iVar3 = PeekPacketChecksumState();
  (*pcVar8)(&DAT_005a9068);
  cVar1 = FUN_004065a0();
  if (cVar1 != '\0') {
    iVar3 = iVar3 + (iVar3 * 0x14) / 100;
  }
  cVar1 = FUN_004065a0();
  if (cVar1 != '\0') {
    iVar3 = iVar3 + (iVar3 * 0x14) / 100;
  }
  cVar1 = FUN_004065a0();
  if (cVar1 != '\0') {
    if (*(char *)(iVar2 + 0x651c) == '\x01') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    iVar2 = PeekPacketChecksumState();
    (*pcVar8)(&DAT_005a9068);
    iVar3 = iVar3 + iVar2;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(iVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00406530();
LAB_0047ca25:
  *unaff_FS_OFFSET = iStack_10;
  return;
}

