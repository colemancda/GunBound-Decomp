/* FUN_00499650 - 0x00499650 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00499650(int *param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *unaff_FS_OFFSET;
  int local_690 [2];
  int local_688 [2];
  undefined1 local_680 [8];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053d23c;
  *unaff_FS_OFFSET = &local_c;
  cVar1 = PeekPacketChecksumBool();
  if ((cVar1 == '\0') && ((char)param_1[5] == '\0')) {
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
    if ((*(int *)(local_454 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_688);
    }
    local_4 = 0xffffffff;
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_688);
    }
    EncodeChecksumDeltaSub(param_1 + 0x10,local_678,param_2);
    local_4 = 2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_688[0] = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_690);
    }
    EncodeChecksumDeltaSub(param_1 + 0x99,local_230,param_3);
    local_4 = 3;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    local_690[0] = iVar5;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if ((*(int *)(local_230 + 0x14)) != 0) {
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
      *(undefined1 *)(param_1 + 0xf) = *(undefined1 *)(param_4 + 0x3c);
      (**(code **)(*param_1 + 0x20))();
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

