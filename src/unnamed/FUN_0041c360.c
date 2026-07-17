/* FUN_0041c360 - 0x0041c360 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_0041c360(int param_1,int param_2,int param_3)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_8a4 [8];
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053b030;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_2 = param_2 + param_1 * 0xb1ac;
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (0x5a < iVar3 - iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    iVar3 = ((iVar3 - iVar4) + -0x5a) / 2;
    EncodeOutgoingPacketField(iVar5 - iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar4 - iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  uVar2 = EncodeChecksumPairDiff(param_2 + 0xf09f0,local_89c,param_2 + 0xf0c14);
  local_4 = 0;
  uVar2 = EncodeChecksumDeltaDiv(uVar2,local_678,2);
  local_4 = 1;
  EncodeChecksumPairSum(uVar2,local_454,param_2 + 0xf0c14);
  local_4 = 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 1;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a4);
  }
  local_4 = 0;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a4);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a4);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 < iVar3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 < iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 < iVar3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 < iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (0x5a < iVar3 - iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    iVar3 = ((iVar3 - iVar4) + -0x5a) / 2;
    EncodeOutgoingPacketField(iVar5 - iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar4 - iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  uVar2 = EncodeChecksumPairDiff(param_2 + 0xf16c8,local_454,param_2 + 0xf18ec);
  local_4 = 3;
  uVar2 = EncodeChecksumDeltaDiv(uVar2,local_678,2);
  local_4 = 4;
  EncodeChecksumPairSum(uVar2,local_89c,param_2 + 0xf18ec);
  local_4 = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 4;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a4);
  }
  local_4 = 3;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a4);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a4);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 < iVar3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 < iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 < iVar3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 < iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (0x5a < iVar3 - iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    iVar3 = ((iVar3 - iVar4) + -0x5a) / 2;
    EncodeOutgoingPacketField(iVar5 - iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar4 - iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  uVar2 = EncodeChecksumPairDiff(param_2 + 0xf23a0,local_454,param_2 + 0xf25c4);
  local_4 = 6;
  uVar2 = EncodeChecksumDeltaDiv(uVar2,local_678,2);
  local_4 = 7;
  EncodeChecksumPairSum(uVar2,local_89c,param_2 + 0xf25c4);
  local_4 = 8;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 7;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a4);
  }
  local_4 = 6;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a4);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a4);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 < iVar3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 < iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 < iVar3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 < iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  uVar2 = EncodeChecksumPairDiff(param_3 + 0x22c0,local_454,param_3 + 0x24e4);
  local_4 = 9;
  uVar2 = EncodeChecksumDeltaDiv(uVar2,local_678,2);
  local_4 = 10;
  EncodeChecksumPairSum(uVar2,local_89c,param_3 + 0x24e4);
  local_4 = 0xb;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 10;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a4);
  }
  local_4 = 9;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a4);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a4);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaSub(param_3 + 0x6520,local_89c,(iVar3 << 3) / 10);
  local_4 = 0xc;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a4);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaAdd(param_3 + 0x6744,local_89c,iVar4 * iVar3);
  local_4 = 0xd;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a4);
  }
  EncodeChecksumPairSum(param_3 + 0x6744,local_89c,param_3 + 0x6db0);
  local_4 = 0xe;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a4);
  }
  if (2000 < iVar3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(2000 - iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 < iVar3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaAdd(param_3 + 0x8de8,local_230,(iVar3 * 0x19) / 10);
  local_4 = 0xf;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_230 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8a4);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool((bVar1 & 8) == 8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool((bVar1 & 4) == 4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool((bVar1 & 2) == 2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool(CONCAT31((int3)((uVar6 & 0xffffff01) >> 8),
                        '\x01' - ((char)(uVar6 & 0xffffff01) != '\x01')));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *unaff_FS_OFFSET = local_c;
  return;
}

