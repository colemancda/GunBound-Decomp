/* FUN_004785f0 - 0x004785f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004785f0(int param_1)

{
  short sVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
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
  cVar2 = FUN_004065a0();
  if (cVar2 == '\x01') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    goto LAB_00478a67;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0040a6e0(param_1 + 0x480,local_89c,uVar3);
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
  uVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0040a6e0(param_1 + 0x480,local_678,uVar3);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0040a6e0(param_1 + 0x25c,local_89c,uVar3);
  SUBFIELD(local_4,0,undefined1) = 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = FUN_004e4340();
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
  uVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0040a6e0(param_1 + 0x480,local_230,uVar3);
  local_4 = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8b0[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8b0[0] = FUN_0040a5f0(param_1 + 0x25c,local_454,local_8b0[0]);
  SUBFIELD(local_4,0,undefined1) = 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8b0[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = FUN_004e4340();
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
  local_8b0[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = local_8b0[0] + local_8a0;
  if (iVar6 < iVar4) {
    iVar7 = local_8a0;
    iVar8 = local_8a0;
    if (iVar5 <= iVar6) {
      if (iVar5 < iVar6) {
        iVar4 = local_8a0 * 2 - iVar5;
      }
      goto LAB_004789f7;
    }
  }
  else {
LAB_004789f7:
    iVar7 = iVar4;
    iVar8 = iVar5;
    if ((iVar6 < iVar5) && (iVar4 < iVar6)) {
      iVar8 = local_8a0 * 2 - iVar4;
    }
  }
  iVar4 = 0x14;
  for (iVar8 = iVar8 - iVar7;
      (((iVar4 < -0x7f || (0x80 < iVar4)) || (iVar8 < -0x7f)) || (0x80 < iVar8)); iVar8 = iVar8 / 2)
  {
    iVar4 = iVar4 / 2;
  }
  sVar1 = *(short *)(&DAT_00598e7e + (iVar8 * 0x100 + iVar4) * 2);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)sVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
LAB_00478a67:
  *unaff_FS_OFFSET = local_c;
  return;
}

