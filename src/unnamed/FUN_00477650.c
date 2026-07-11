/* FUN_00477650 - 0x00477650 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00477650(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int local_690 [2];
  int local_688 [2];
  undefined1 local_680 [8];
  undefined1 local_678 [20];
  int local_664;
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  int local_21c;
  int local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053d23c) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. local_4's
   * `._0_1_`/`._1_3_` partial-field accesses are rewritten as plain
   * int operations, same reasoning as FUN_004174c0.c's fix. */
  cVar1 = PeekPacketChecksumBool();
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x14) == '\0')) {
    uVar2 = EncodeChecksumDeltaDiv(param_4 + 0x2908,local_678,2);
    local_4 = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaAdd(uVar2,local_454,uVar3);
    local_4 = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0;
    if (local_440 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_688);
    }
    local_4 = 0xffffffff;
    if (local_664 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_688);
    }
    EncodeChecksumDeltaSub(param_1 + 0x40,local_678,param_2);
    local_4 = 2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_688[0] = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if (local_664 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_690);
    }
    EncodeChecksumDeltaSub(param_1 + 0x264,local_230,param_3);
    local_4 = 3;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    local_690[0] = iVar5;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if (local_21c != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_680);
      iVar5 = local_690[0];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_690[0] = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = (local_690[0] * local_688[0]) / iVar6;
    if (iVar5 * iVar5 + iVar6 * iVar6 < iVar4 * iVar4) {
      FUN_00477140();
    }
  }
  return;
}

