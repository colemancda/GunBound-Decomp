/* FUN_004d0fd0 - 0x004d0fd0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004d0fd0(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_8a4 [8];
  undefined1 local_89c [20];
  int local_888;
  undefined1 local_678 [20];
  int local_664;
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  int local_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  iVar1 = g_clientContext;
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053dfcc;
  *unaff_FS_OFFSET = &local_c;
  iVar1 = GetPlayerRecordBySlot(iVar1);
  if (iVar1 != 0) {
    *(undefined4 *)(*(int *)(iVar1 + 0xc) + 0x10) = *(undefined4 *)(iVar1 + 0x10);
    *(undefined4 *)(*(int *)(iVar1 + 0x10) + 0xc) = *(undefined4 *)(iVar1 + 0xc);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0042b0b0((uint)param_1,param_2,uVar3,uVar2,*(undefined4 *)(iVar1 + 0xae2c),
                 *(undefined4 *)(iVar1 + 0xae38),*(undefined4 *)(iVar1 + 0xae3c),iVar1 + 0xae15,
                 iVar1 + 0xae22,*(undefined4 *)(iVar1 + 0xae30),*(undefined4 *)(iVar1 + 0xae34),1);
    iVar4 = GetPlayerRecordBySlot(g_clientContext);
    if (iVar4 != 0) {
      *(int *)(g_clientContext + 0x621e4) = iVar4;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (param_1 == uVar5) {
        *(int *)(g_clientContext + 0x621e0) = iVar4;
      }
      FUN_00406530();
      FUN_00406530();
      FUN_00406530();
      FUN_00406530();
      FUN_00406530();
      FUN_00406530();
      FUN_00406530();
      FUN_00406530();
      FUN_00406530();
      FUN_00406530();
      FUN_00406530();
      FUN_00406530();
      FUN_00406530();
      FUN_00406530();
      FUN_00406530();
      FUN_00406530();
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_0040b490(iVar4 + 0x8318,iVar1 + 0x853c);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_00406530();
      *(undefined2 *)(iVar4 + 0xbfbc) = *(undefined2 *)(iVar1 + 0xbfbc);
      *(undefined1 *)(iVar4 + 0xae68) = *(undefined1 *)(iVar1 + 0xae68);
      *(undefined4 *)(iVar4 + 0xb094) = *(undefined4 *)(iVar1 + 0xb094);
      *(undefined4 *)(iVar4 + 0xb098) = *(undefined4 *)(iVar1 + 0xb098);
      *(undefined4 *)(iVar4 + 0xb09c) = *(undefined4 *)(iVar1 + 0xb09c);
      *(undefined4 *)(iVar4 + 0xb0a0) = *(undefined4 *)(iVar1 + 0xb0a0);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      *(undefined4 *)(iVar1 + 0xbfe4) = 200;
      *(undefined4 *)(iVar4 + 0xbfe0) = 200;
      uVar2 = FUN_0040aba0(iVar1 + 0x6744,local_230,iVar1 + 0x6db0);
      local_4 = 0;
      uVar3 = FUN_0040aba0(iVar1 + 0x6968,local_678,iVar1 + 0x6fd4);
      local_4._0_1_ = 1;
      uVar3 = FUN_0040ada0(iVar4 + 0x6744,local_454,uVar3);
      local_4._0_1_ = 2;
      FUN_0040aea0(uVar3,local_89c,uVar2);
      local_4._0_1_ = 3;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4._0_1_ = 2;
      if (local_888 != 0) {
        FUN_0040a240();
        FUN_0040b540(local_8a4);
      }
      local_4._0_1_ = 1;
      if (local_440 != 0) {
        FUN_0040a240();
        FUN_0040b540(local_8a4);
      }
      local_4 = (uint)local_4._1_3_ << 8;
      if (local_664 != 0) {
        FUN_0040a240();
        FUN_0040b540(local_8a4);
      }
      local_4 = 0xffffffff;
      if (local_21c != 0) {
        FUN_0040a240();
        FUN_0040b540(local_8a4);
      }
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

