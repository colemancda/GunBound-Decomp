/* ComputeMobileGroundY - 0x0045c6e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall ComputeMobileGroundY(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *unaff_FS_OFFSET;
  bool bVar6;
  undefined1 local_688 [8];
  int local_680;
  int local_67c;
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
  iVar5 = param_1 + 0xf78;
  uVar2 = EncodeChecksumDeltaDiv(iVar5,local_678,2);
  iVar1 = param_1 + 0xb30;
  local_4 = 0;
  EncodeChecksumPairDiff(iVar1,local_454,uVar2);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_67c = param_1 + 0x90c;
  iVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped terrain/x/y args - angr-confirmed at
   * 0x45c798. y=EAX came from the PeekPacketChecksumState() return just
   * above (dropped by Ghidra, captured here as iVar6); x=EDI came from
   * the second Peek's return just above that (captured as iVar7). */
  local_680 = FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),iVar7,iVar6);
  local_4 = 0;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_688);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_688);
  }
  uVar2 = EncodeChecksumDeltaDiv(iVar5,local_454,2);
  local_4 = 2;
  EncodeChecksumPairDiff(iVar1,local_678,uVar2);
  local_4 = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar6 = local_680 == iVar3;
  local_4 = 2;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_688);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_688);
  }
  iVar3 = local_680;
  if (bVar6) {
    EncodeChecksumPairDiff(iVar1,local_678,iVar5);
    local_4 = 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped terrain/x/y args - angr-confirmed at
     * 0x45c93d. y=EAX came from the PeekPacketChecksumState() return just
     * above (dropped by Ghidra, captured here as iVar6); x=EDI came from
     * the second Peek's return just above that (captured as iVar7). */
    iVar4 = FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),iVar7,iVar6);
    local_4 = 0xffffffff;
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_688);
    }
    EncodeChecksumPairDiff(iVar1,local_678,iVar5);
    local_4 = 5;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_688);
    }
    iVar3 = local_680;
    if (iVar4 == iVar5) {
      EncodeChecksumDeltaAdd(iVar1,local_678,1);
      local_4 = 6;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      /* FIXED (2026-07-15): dropped terrain/x/y args - angr-confirmed at
       * 0x45ca5d. y=EAX came from the PeekPacketChecksumState() return
       * just above (dropped by Ghidra, captured here as iVar6); x=EDI
       * came from the second Peek's return just above that (captured as
       * iVar7). */
      iVar3 = FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),iVar7,iVar6);
      local_4 = 0xffffffff;
      if ((*(int *)(local_678 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound(local_688);
      }
      EncodeChecksumDeltaAdd(iVar1,local_230,1);
      local_4 = 7;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if ((*(int *)(local_230 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound(local_688);
      }
      if (iVar3 == iVar5) {
        iVar3 = PeekChecksumStateUnderLock(iVar1);
      }
    }
  }
  *unaff_FS_OFFSET = local_c;
  return iVar3;
}

