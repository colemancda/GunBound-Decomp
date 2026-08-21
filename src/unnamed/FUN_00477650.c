/* FUN_00477650 - 0x00477650 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 6 argless PeekPacketChecksumState() calls, from
 * tools/guard_cell_resolve.py.  Three cells are chained returns the
 * decompile discarded - the round's opening EncodeChecksumDeltaAdd /
 * DeltaSub / DeltaSub - captured in a new uVar8.  The others are
 * &DAT_00e9ba40, &DAT_00796aa0, and param_4+0x2f74 (read back through
 * the arg's frame slot; param_4 is the same object whose +0x2908 cell
 * the round-1 DeltaDiv already passes explicitly).  This function and
 * its twin (FUN_00477650/FUN_00499650) check each other cell for cell.
 */
#include "ghidra_types.h"


void FUN_00477650(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar8;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int local_690 [2];
  int local_688 [2];
  undefined1 local_680 [8];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  int local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053d23c) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. local_4's
   * `._0_1_`/`._1_3_` partial-field accesses are rewritten as plain
   * int operations, same reasoning as FUN_004174c0.c's fix. */
  cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x14) == '\0')) {
    uVar2 = EncodeChecksumDeltaDiv(param_4 + 0x2908,local_678,2);
    local_4 = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = EncodeChecksumDeltaAdd(uVar2,local_454,uVar3);
    local_4 = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0;
    if ((*(int *)(local_454 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&DAT_0079376c);
      TreeLowerBound(local_688);
    }
    local_4 = 0xffffffff;
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&DAT_0079376c);
      TreeLowerBound(local_688);
    }
    uVar8 = EncodeChecksumDeltaSub(param_1 + 0x40,local_678,param_2);
    local_4 = 2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_688[0] = PeekPacketChecksumState((void *)uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&DAT_0079376c);
      TreeLowerBound(local_690);
    }
    uVar8 = EncodeChecksumDeltaSub(param_1 + 0x264,local_230,param_3);
    local_4 = 3;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)uVar8);
    local_690[0] = iVar5;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if ((*(int *)(local_230 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_230 + 0x14),&DAT_0079376c);
      TreeLowerBound(local_680);
      iVar5 = local_690[0];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_690[0] = PeekPacketChecksumState((void *)&DAT_00796aa0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState((void *)(param_4 + 0x2f74));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = (local_690[0] * local_688[0]) / iVar6;
    if (iVar5 * iVar5 + iVar6 * iVar6 < iVar4 * iVar4) {
      FUN_00477140();
    }
  }
  return;
}

