/* FUN_0047fee0 - 0x0047fee0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0047fee0(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *unaff_ESI;
  undefined4 *unaff_FS_OFFSET;
  int unaff_retaddr;
  int aiStack_688 [2];
  uint uStack_680;
  undefined4 local_67c [5];
  int iStack_668;
  undefined1 auStack_458 [20];
  int iStack_444;
  undefined1 auStack_234 [20];
  int iStack_220;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_00539a68;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_67c[0] = 0;
  unaff_ESI[0xfef] = 3;
  (**(code **)(*unaff_ESI + 4))(&DAT_00553f90);
  iVar2 = GetPlayerRecordBySlot(g_clientContext);
  if (iVar2 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar3 != 1) {
      *(undefined1 *)(unaff_ESI + 5) = 1;
      goto LAB_004802f3;
    }
  }
  iVar3 = iVar2 + 0xb30;
  *(undefined1 *)(unaff_ESI + 0xff8) = 0;
  *(undefined1 *)(unaff_ESI + 0xff1) = 1;
  aiStack_688[0] = EncodeChecksumDeltaSub(iVar3,auStack_234,400);
  puStack_8 = (undefined1 *)0x0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  aiStack_688[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (*(int *)(&DAT_006a7724 + g_clientContext) + iVar4 < aiStack_688[0]) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = *(int *)(&DAT_006a7724 + g_clientContext) + iVar4;
  }
  else {
    EncodeChecksumDeltaSub(iVar3,auStack_458,400);
    puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
    uStack_680 = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EncodeChecksumDeltaSub(iVar3,local_67c,iVar4);
  puStack_8 = (undefined1 *)0x2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
  unaff_ESI[0xff2] = iVar3;
  if (iStack_668 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(aiStack_688);
  }
  puStack_8 = (undefined1 *)0x0;
  if (((uStack_680 & 1) != 0) && (iStack_444 != 0)) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(aiStack_688);
  }
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_220 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(aiStack_688);
  }
  unaff_ESI[0xff3] = 1;
  if (*(char *)(iVar2 + 0x651c) == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    iVar3 = iVar3 + (iVar3 * 0x14) / 100;
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    iVar3 = iVar3 + (iVar3 * 0x14) / 100;
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    if (*(char *)(iVar2 + 0x651c) == '\x01') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = iVar3 + iVar2;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(iVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  fptan((float10)_DAT_00558070);
  iVar2 = FloatToInt64();
  if (param_1 < 0) {
    iVar3 = iVar2 / 2 + iVar2 + unaff_retaddr;
    iVar2 = -iVar2;
    unaff_ESI[0xff6] = 0x108;
    unaff_ESI[0xff7] = 4;
  }
  else {
    iVar3 = (unaff_retaddr - iVar2 / 2) - iVar2;
    unaff_ESI[0xff6] = 0x114;
    unaff_ESI[0xff7] = -4;
  }
  unaff_ESI[0xff4] = iVar3;
  unaff_ESI[0xfed] = iVar3;
  unaff_ESI[0xff5] = iVar2;
  FUN_00406530();
LAB_004802f3:
  *unaff_FS_OFFSET = uStack_10;
  return;
}

