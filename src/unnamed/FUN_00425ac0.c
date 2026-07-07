/* FUN_00425ac0 - 0x00425ac0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_00425ac0(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_680 [8];
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
  puStack_8 = &LAB_0053af21;
  *unaff_FS_OFFSET = &local_c;
  uVar1 = GetPlayerRecordBySlot(param_1);
  uVar5 = 0;
  if (uVar1 != 0) {
    FUN_0040a6e0(uVar1 + 0x90c,local_454,param_2);
    local_4 = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if (local_440 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_680);
    }
    uVar3 = FUN_0040a6e0(uVar1 + 0xb30,local_230,10);
    local_4 = 1;
    FUN_0040a6e0(uVar3,local_678,param_3);
    local_4._0_1_ = 2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = CONCAT31(local_4._1_3_,1);
    if (local_664 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_680);
    }
    local_4 = 0xffffffff;
    if (local_21c != 0) {
      FUN_0040a240();
      FUN_0040b540(local_680);
    }
    uVar5 = (param_4 * param_4 <= iVar4 * iVar4 + iVar2 * iVar2) - 1 & uVar1;
  }
  *unaff_FS_OFFSET = local_c;
  return uVar5;
}

