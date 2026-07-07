/* FUN_0047fad0 - 0x0047fad0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0047fad0(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int unaff_EBX;
  code *pcVar5;
  int *unaff_ESI;
  undefined4 *unaff_FS_OFFSET;
  int unaff_retaddr;
  int aiStack_464 [2];
  uint uStack_45c;
  undefined4 local_458 [5];
  int iStack_444;
  undefined1 auStack_234 [20];
  int iStack_220;
  undefined4 uStack_18;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_00539aad;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_458[0] = 0;
  unaff_ESI[0xfef] = ((char)param_3 != '\0') + 1;
  (**(code **)(*unaff_ESI + 4))(&DAT_00553f90);
  iVar2 = GetPlayerRecordBySlot(DAT_005b3484);
  if (iVar2 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    pcVar5 = LeaveCriticalSection_exref;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar3 != 1) {
      *(undefined1 *)(unaff_ESI + 5) = 1;
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
    if (((char)unaff_ESI[0xfe8] != '\0') || (uVar4 = 0xffffff38, (char)unaff_ESI[0xff1] != '\0')) {
      uVar4 = 0xfffffdda;
    }
    aiStack_464[0] = FUN_0040a5f0(iVar2 + 0xb30,auStack_234,uVar4);
    puStack_8 = (undefined1 *)0x0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    unaff_EBX = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    aiStack_464[0] = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (*(int *)(&DAT_006a7724 + DAT_005b3484) + unaff_EBX < aiStack_464[0]) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      unaff_EBX = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = *(int *)(&DAT_006a7724 + DAT_005b3484) + unaff_EBX;
    }
    else {
      if (((char)unaff_ESI[0xfe8] != '\0') || (uVar4 = 0xffffff38, (char)unaff_ESI[0xff1] != '\0'))
      {
        uVar4 = 0xfffffdda;
      }
      FUN_0040a5f0(iVar2 + 0xb30,local_458,uVar4);
      puStack_8 = (undefined1 *)CONCAT31(puStack_8._1_3_,1);
      uStack_45c = 1;
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
    if (((uStack_45c & 1) != 0) && (iStack_444 != 0)) {
      FUN_0040a240();
      FUN_0040b540(aiStack_464);
      unaff_EBX = iStack_444;
    }
    puStack_8 = (undefined1 *)0xffffffff;
    pcVar5 = LeaveCriticalSection_exref;
    if (iStack_220 != 0) {
      FUN_0040a240();
      FUN_0040b540(aiStack_464);
      pcVar5 = LeaveCriticalSection_exref;
      unaff_EBX = iStack_220;
    }
  }
  unaff_ESI[0xfea] = unaff_retaddr;
  unaff_ESI[0xfeb] = param_1;
  *(undefined1 *)(unaff_ESI + 0xff1) = 0;
  *(undefined1 *)(unaff_ESI + 0xfe8) = param_2;
  unaff_ESI[0xfe9] = param_3;
  if (*(char *)(iVar2 + 0x651c) == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  iVar2 = PeekPacketChecksumState();
  (*pcVar5)(&DAT_005a9068);
  cVar1 = FUN_004065a0();
  if (cVar1 != '\0') {
    iVar2 = iVar2 + (iVar2 * 0x14) / 100;
  }
  cVar1 = FUN_004065a0();
  if (cVar1 != '\0') {
    iVar2 = iVar2 + (iVar2 * 0x14) / 100;
  }
  cVar1 = FUN_004065a0();
  if (cVar1 != '\0') {
    if (*(char *)(unaff_EBX + 0x651c) == '\x01') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    iVar3 = PeekPacketChecksumState();
    (*pcVar5)(&DAT_005a9068);
    iVar2 = iVar2 + iVar3;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(iVar2);
  (*pcVar5)(&DAT_005a9068);
  FUN_00406530();
  *unaff_FS_OFFSET = uStack_18;
  return;
}

