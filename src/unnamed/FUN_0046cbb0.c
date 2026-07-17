/* FUN_0046cbb0 - 0x0046cbb0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_0046cbb0(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 *unaff_FS_OFFSET;
  bool bVar4;
  int local_68c;
  int local_688 [2];
  undefined1 local_680 [8];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00539f08;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uVar1 = EncodeChecksumDeltaDiv(param_1 + 0xf78,local_678,2);
  local_4 = 0;
  EncodeChecksumPairDiff(param_1 + 0xb30,local_454,uVar1);
  SUBFIELD(local_4,0,undefined1) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_68c = FindGroundHeightAtColumn();
  local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_688);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_688);
  }
  uVar1 = EncodeChecksumDeltaDiv(param_1 + 0xf78,local_454,2);
  local_4 = 2;
  EncodeChecksumPairDiff(param_1 + 0xb30,local_678,uVar1);
  SUBFIELD(local_4,0,undefined1) = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_688);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_688);
  }
  if (local_68c == iVar2) {
    EncodeChecksumPairDiff(param_1 + 0xb30,local_678,param_1 + 0xf78);
    local_4 = 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_688[0] = FindGroundHeightAtColumn();
    local_4 = 0xffffffff;
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_680);
    }
    EncodeChecksumPairDiff(param_1 + 0xb30,local_678,param_1 + 0xf78);
    local_4 = 5;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = (*(int *)(local_678 + 0x14));
    bVar4 = local_688[0] == iVar3;
    local_4 = 0xffffffff;
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      local_688[0] = iVar2;
      TreeLowerBound(local_680);
    }
    if (bVar4) {
      EncodeChecksumDeltaAdd(param_1 + 0xb30,local_678,1);
      local_4 = 6;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_688[0] = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_68c = FindGroundHeightAtColumn();
      local_4 = 0xffffffff;
      if ((*(int *)(local_678 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes();
        local_688[0] = (*(int *)(local_678 + 0x14));
        TreeLowerBound(local_680);
      }
      EncodeChecksumDeltaAdd(param_1 + 0xb30,local_230,1);
      local_4 = 7;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if ((*(int *)(local_230 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes();
        local_688[0] = (*(int *)(local_230 + 0x14));
        TreeLowerBound(local_680);
      }
      if (local_68c == iVar2) {
        local_68c = PeekChecksumStateUnderLock(param_1 + 0xb30);
      }
    }
  }
  iVar2 = *(int *)(param_1 + 0x24);
  *unaff_FS_OFFSET = local_c;
  return local_68c - ((iVar2 == 0xe) - 1 & 0x14);
}

