/* FUN_004ac400 - 0x004ac400 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_004ac400(int param_1)

{
  undefined4 uVar1;
  undefined1 local_238 [8];
  undefined1 local_230 [20];
  int local_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053df6b) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  EncodeChecksumDeltaSub(param_1 + 0x4c,local_230,1);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (local_21c != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_238);
  }
  return uVar1;
}

