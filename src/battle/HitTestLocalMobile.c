/* HitTestLocalMobile - 0x00425ac0 in the original binary.
 *
 * RENAMED (2026-08-17, from FUN_00425ac0): fetches the local player record and guard-computes (mobileX - x) and (mobileY-10 - y) deltas; returns the record when the point is within range, else 0 - the detonation hit-test every Simulate/Detonate twin calls before the +0x908/+0xbff7 peeks.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: both are chained returns of the DeltaSub immediately above them
 * (0x425b0e, 0x425bac), discarded by the decompile and captured in a
 * new uVar8.
 */
#include "ghidra_types.h"


uint HitTestLocalMobile(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  uint uVar1;
  undefined4 uVar8;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_680 [8];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053af21;
  *unaff_FS_OFFSET = &local_c;
  uVar1 = GetPlayerRecordBySlot(param_1);
  uVar5 = 0;
  if (uVar1 != 0) {
    uVar8 = EncodeChecksumDeltaSub(uVar1 + 0x90c,local_454,param_2);
    local_4 = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState((void *)uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if ((*(int *)(local_454 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&DAT_0079376c);
      TreeLowerBound(local_680);
    }
    uVar3 = EncodeChecksumDeltaSub(uVar1 + 0xb30,local_230,10);
    local_4 = 1;
    uVar8 = EncodeChecksumDeltaSub(uVar3,local_678,param_3);
    SUBFIELD(local_4,0,undefined1) = 2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),1);
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&DAT_0079376c);
      TreeLowerBound(local_680);
    }
    local_4 = 0xffffffff;
    if ((*(int *)(local_230 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_230 + 0x14),&DAT_0079376c);
      TreeLowerBound(local_680);
    }
    uVar5 = (param_4 * param_4 <= iVar4 * iVar4 + iVar2 * iVar2) - 1 & uVar1;
  }
  *unaff_FS_OFFSET = local_c;
  return uVar5;
}

