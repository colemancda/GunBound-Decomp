/* FUN_0045f300 - 0x0045f300 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 5 argless PeekPacketChecksumState() calls.  ESI is loaded
 * once at 0x45f32c/0x45f333 as param_1 + 0x62f8 and never reassigned, so
 * C34 (0x45f33b) and the C85/C91 pair (0x45f578 / 0x45f54a) all read that
 * cell.  C44 and C66 read EDI, which each branch had just set from the
 * return value of the 0x40a8c0 delta-div helper (the
 * EncodeChecksumDeltaDiv two lines above each) -- and that helper RETURNS
 * ITS SECOND ARGUMENT, so they are the branch's own stack scratch cell,
 * local_89c and local_ac0 respectively.
 *
 * NOTE: Ghidra emitted BOTH if/else pairs in the reverse of address order,
 * so the sites were matched by landmark rather than position: the
 * `local_4 = 4` store lands at 0x45f455 (just before 0x45f461) and
 * `local_4 = 1` at 0x45f387 (just before 0x45f393), and the trailing
 * DAT_005a9624 table load at 0x45f56b follows the 0x45f54a peek, not the
 * 0x45f578 one.  The pairings above are the landmark-correct ones.
 */
#include "ghidra_types.h"


int FUN_0045f300(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *unaff_FS_OFFSET;
  int local_acc;
  undefined1 local_ac8 [8];
  undefined1 local_ac0 [548];
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00539a17;
  *unaff_FS_OFFSET = &local_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState((void *)(param_1 + 0x62f8));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 < 1) {
    uVar3 = EncodeChecksumNegate(param_1 + 0x62f8,local_230);
    local_4 = 2;
    uVar3 = EncodeChecksumDeltaSub(uVar3,local_678,4);
    local_4 = 3;
    EncodeChecksumDeltaDiv(uVar3,local_89c,10);
    local_4 = 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_acc = PeekPacketChecksumState((void *)(local_89c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 3;
    if ((*(int *)(local_89c + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_89c + 0x14),&DAT_0079376c);
      TreeLowerBound(local_ac8);
    }
    local_4 = 2;
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&DAT_0079376c);
      TreeLowerBound(local_ac8);
    }
    local_4 = 0xffffffff;
    if ((*(int *)(local_230 + 0x14)) == 0) goto LAB_0045f51b;
    ScrambleChecksumGuardBytes();
  }
  else {
    uVar3 = EncodeChecksumDeltaAdd(param_1 + 0x62f8,local_454,4);
    local_4 = 0;
    EncodeChecksumDeltaDiv(uVar3,local_ac0,10);
    local_4 = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_acc = PeekPacketChecksumState((void *)(local_ac0));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0;
    if ((*(int *)(local_ac0 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_ac0 + 0x14),&DAT_0079376c);
      TreeLowerBound(local_ac8);
    }
    local_4 = 0xffffffff;
    if ((*(int *)(local_454 + 0x14)) == 0) goto LAB_0045f51b;
    ScrambleChecksumGuardBytes();
  }
  TreeLowerBound(local_ac8);
LAB_0045f51b:
  if (5 < local_acc) {
    local_acc = 6;
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)(param_1 + 0x62f8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = *(int *)(&DAT_005a9640 + (local_acc % 7) * 4);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)(param_1 + 0x62f8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = *(int *)(&DAT_005a9624 + (local_acc % 7) * 4);
  }
  if (iVar4 < 1) {
    iVar2 = -iVar2;
  }
  *unaff_FS_OFFSET = local_c;
  return iVar2;
}

