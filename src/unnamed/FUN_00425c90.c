/* FUN_00425c90 - 0x00425c90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __fastcall
FUN_00425c90(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,int param_5)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_45c [8];
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  int local_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  iVar3 = DAT_005b3484;
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053aef6;
  *unaff_FS_OFFSET = &local_c;
  iVar3 = *(int *)(*(int *)(&DAT_006a7f8c + iVar3) + 0x1c);
  uVar1 = *(uint *)(iVar3 + 4);
  if (uVar1 < 0x186a7) {
    while (uVar1 != 0x186a6) {
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar1 = *(uint *)(iVar3 + 4);
      if (0x186a6 < uVar1) {
        *unaff_FS_OFFSET = local_c;
        return 0;
      }
    }
    uVar1 = *(uint *)(iVar3 + 0x10);
    uVar2 = *(uint *)(uVar1 + 8);
    while (uVar2 <= param_2) {
      if (uVar2 == param_2) {
        FUN_0040a6e0(uVar1 + 0x25c,local_454,param_3);
        local_4 = 0;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar3 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = 0xffffffff;
        if (local_440 != 0) {
          FUN_0040a240();
          FUN_0040b540(local_45c);
        }
        FUN_0040a6e0(uVar1 + 0x480,local_230,param_4);
        local_4 = 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar4 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = 0xffffffff;
        if (local_21c != 0) {
          FUN_0040a240();
          FUN_0040b540(local_45c);
        }
        *unaff_FS_OFFSET = local_c;
        return (param_5 * param_5 <= iVar3 * iVar3 + iVar4 * iVar4) - 1 & uVar1;
      }
      uVar1 = *(uint *)(uVar1 + 0x10);
      uVar2 = *(uint *)(uVar1 + 8);
    }
  }
  *unaff_FS_OFFSET = local_c;
  return 0;
}

