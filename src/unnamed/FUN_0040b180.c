/* FUN_0040b180 - 0x0040b180 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_0040b180(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_238 [28];
  int local_21c;
  undefined1 local_10;
  undefined4 local_c;
  uint local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * wasn't included in this function's own decompile. Same
   * rationale as entry/InitGame.c - see src/README.md. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_10 = 0;
  local_21c = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 1;
  iVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar1 >> (param_3 & 0x1f));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined1 *)(param_2 + 0x220) = 0;
  *(undefined4 *)(param_2 + 0x14) = 0;
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  local_4 = local_4 & 0xffffff00;
  if (local_21c != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_238);
  }
  return param_2;
}

