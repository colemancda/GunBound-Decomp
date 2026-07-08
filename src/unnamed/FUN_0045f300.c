/* FUN_0045f300 - 0x0045f300 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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
  undefined1 local_ac0 [20];
  int local_aac;
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
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00539a17;
  *unaff_FS_OFFSET = &local_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 < 1) {
    uVar3 = FUN_0040a500(param_1 + 0x62f8,local_230);
    local_4 = 2;
    uVar3 = FUN_0040a6e0(uVar3,local_678,4);
    local_4 = 3;
    FUN_0040a8c0(uVar3,local_89c,10);
    local_4 = 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_acc = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 3;
    if (local_888 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_ac8);
    }
    local_4 = 2;
    if (local_664 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_ac8);
    }
    local_4 = 0xffffffff;
    if (local_21c == 0) goto LAB_0045f51b;
    FUN_0040a240();
  }
  else {
    uVar3 = FUN_0040a5f0(param_1 + 0x62f8,local_454,4);
    local_4 = 0;
    FUN_0040a8c0(uVar3,local_ac0,10);
    local_4 = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_acc = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0;
    if (local_aac != 0) {
      FUN_0040a240();
      FUN_0040b540(local_ac8);
    }
    local_4 = 0xffffffff;
    if (local_440 == 0) goto LAB_0045f51b;
    FUN_0040a240();
  }
  FUN_0040b540(local_ac8);
LAB_0045f51b:
  if (5 < local_acc) {
    local_acc = 6;
  }
  cVar1 = FUN_004065a0();
  if (cVar1 == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = *(int *)(&DAT_005a9640 + (local_acc % 7) * 4);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = *(int *)(&DAT_005a9624 + (local_acc % 7) * 4);
  }
  if (iVar4 < 1) {
    iVar2 = -iVar2;
  }
  *unaff_FS_OFFSET = local_c;
  return iVar2;
}

