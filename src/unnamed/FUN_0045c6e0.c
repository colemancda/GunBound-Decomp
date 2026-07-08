/* FUN_0045c6e0 - 0x0045c6e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_0045c6e0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *unaff_FS_OFFSET;
  bool bVar6;
  undefined1 local_688 [8];
  int local_680;
  int local_67c;
  undefined1 local_678 [20];
  int local_664;
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  int local_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00539f08;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  iVar5 = param_1 + 0xf78;
  uVar2 = FUN_0040a8c0(iVar5,local_678,2);
  iVar1 = param_1 + 0xb30;
  local_4 = 0;
  FUN_0040aca0(iVar1,local_454,uVar2);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_67c = param_1 + 0x90c;
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_680 = FUN_004e4340();
  local_4 = 0;
  if (local_440 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_688);
  }
  local_4 = 0xffffffff;
  if (local_664 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_688);
  }
  uVar2 = FUN_0040a8c0(iVar5,local_454,2);
  local_4 = 2;
  FUN_0040aca0(iVar1,local_678,uVar2);
  local_4 = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar6 = local_680 == iVar3;
  local_4 = 2;
  if (local_664 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_688);
  }
  local_4 = 0xffffffff;
  if (local_440 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_688);
  }
  iVar3 = local_680;
  if (bVar6) {
    FUN_0040aca0(iVar1,local_678,iVar5);
    local_4 = 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = FUN_004e4340();
    local_4 = 0xffffffff;
    if (local_664 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_688);
    }
    FUN_0040aca0(iVar1,local_678,iVar5);
    local_4 = 5;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if (local_664 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_688);
    }
    iVar3 = local_680;
    if (iVar4 == iVar5) {
      FUN_0040a5f0(iVar1,local_678,1);
      local_4 = 6;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = FUN_004e4340();
      local_4 = 0xffffffff;
      if (local_664 != 0) {
        FUN_0040a240();
        FUN_0040b540(local_688);
      }
      FUN_0040a5f0(iVar1,local_230,1);
      local_4 = 7;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if (local_21c != 0) {
        FUN_0040a240();
        FUN_0040b540(local_688);
      }
      if (iVar3 == iVar5) {
        iVar3 = FUN_0040a4d0(iVar1);
      }
    }
  }
  *unaff_FS_OFFSET = local_c;
  return iVar3;
}

