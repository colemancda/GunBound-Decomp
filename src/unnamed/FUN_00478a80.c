/* FUN_00478a80 - 0x00478a80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


char FUN_00478a80(int param_1,int param_2,int param_3)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_45c [8];
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [548];
  uint local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053ab71) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  if (*(char *)(param_1 + 0x14) == '\x01') {
    return '\0';
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaSub(param_1 + 0x25c,local_454,uVar2);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (local_440 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_45c);
  }
  if (iVar3 <= param_2) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaAdd(param_1 + 0x25c,local_454,uVar2);
    local_4 = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if (local_440 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(local_45c);
    }
    if (param_2 <= iVar3) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = EncodeChecksumDeltaSub(param_1 + 0x480,local_230,uVar2);
      local_4 = 2;
      iVar3 = PeekChecksumStateUnderLock(uVar2);
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      if (iVar3 <= param_3) {
        cVar1 = PacketChecksumLessThan(param_1 + 0x480,param_3);
        cVar1 = '\x01' - (cVar1 != '\0');
        goto LAB_00478c8e;
      }
    }
  }
  cVar1 = '\0';
LAB_00478c8e:
  return cVar1;
}

