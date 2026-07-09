/* FUN_004986a0 - 0x004986a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_004986a0(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *unaff_FS_OFFSET;
  int local_8b0 [2];
  undefined1 local_8a8 [8];
  int local_8a0;
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
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00539797;
  *unaff_FS_OFFSET = &local_c;
  if (*(char *)(param_1 + 0x3fc4) != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = *(int *)(param_1 + 0x3fa4) + iVar1;
    iVar3 = iVar1 / iVar2;
    iVar1 = iVar1 % iVar2;
    *(int *)(param_1 + 0x3fa4) = iVar1;
    *(int *)(param_1 + 0x3fbc) = iVar1;
    goto LAB_00498b38;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0040a6e0(param_1 + 0x264,local_89c,uVar4);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8a0 = FUN_004e4340();
  local_4 = 0xffffffff;
  if (local_888 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_8b0);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0040a6e0(param_1 + 0x264,local_678,uVar4);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0040a6e0(param_1 + 0x40,local_89c,uVar4);
  SUBFIELD(local_4,0,undefined1) = 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = FUN_004e4340();
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),1);
  if (local_888 != 0) {
    FUN_0040a240();
    local_8b0[0] = local_888;
    FUN_0040b540(local_8a8);
  }
  local_4 = 0xffffffff;
  if (local_664 != 0) {
    FUN_0040a240();
    local_8b0[0] = local_664;
    FUN_0040b540(local_8a8);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0040a6e0(param_1 + 0x264,local_230,uVar4);
  local_4 = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8b0[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8b0[0] = FUN_0040a5f0(param_1 + 0x40,local_454,local_8b0[0]);
  SUBFIELD(local_4,0,undefined1) = 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8b0[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = FUN_004e4340();
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),3);
  local_8b0[0] = local_440;
  if (local_440 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_8a8);
  }
  local_4 = 0xffffffff;
  local_8b0[0] = local_21c;
  if (local_21c != 0) {
    FUN_0040a240();
    FUN_0040b540(local_8a8);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = iVar1 + local_8a0;
  if (iVar1 < iVar3) {
    iVar5 = local_8a0;
    iVar6 = local_8a0;
    if (iVar2 <= iVar1) {
      if (iVar2 < iVar1) {
        iVar3 = local_8a0 * 2 - iVar2;
      }
      goto LAB_00498abd;
    }
  }
  else {
LAB_00498abd:
    iVar5 = iVar3;
    iVar6 = iVar2;
    if ((iVar1 < iVar2) && (iVar3 < iVar1)) {
      iVar6 = local_8a0 * 2 - iVar3;
    }
  }
  iVar3 = 0x14;
  for (iVar6 = iVar6 - iVar5;
      (((iVar3 < -0x7f || (0x80 < iVar3)) || (iVar6 < -0x7f)) || (0x80 < iVar6)); iVar6 = iVar6 / 2)
  {
    iVar3 = iVar3 / 2;
  }
  iVar2 = (int)*(short *)(&DAT_00598e7e + (iVar6 * 0x100 + iVar3) * 2);
  *(int *)(param_1 + 0x3fa4) = iVar2;
  if (0x10e < iVar2) {
    iVar2 = iVar2 + -0x168;
  }
  *(int *)(param_1 + 0x3fa4) = -iVar2;
  iVar3 = -iVar2;
  if (*(int *)(param_1 + 0x3fa8) != 0) {
    iVar3 = iVar2;
  }
  *(int *)(param_1 + 0x3fbc) = iVar3;
LAB_00498b38:
  *unaff_FS_OFFSET = local_c;
  return iVar3;
}

