/* FUN_0050cff0 - 0x0050cff0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0050cff0(int *param_1,uint param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  undefined4 *unaff_FS_OFFSET;
  int local_1c;
  int local_18;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0053be70;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if (param_2 < (uint)param_1[1]) {
    iVar1 = param_1[1];
    FUN_0044c7b0();
    local_18 = iVar1 * 0x450 + *param_1;
    if (param_4 != 0) {
      local_1c = param_4;
      do {
        FUN_00426810(local_18);
        local_18 = local_18 + 0x450;
        local_1c = local_1c + -1;
      } while (local_1c != 0);
    }
    _memmove((void *)((param_4 + param_2) * 0x450 + *param_1),(void *)(param_2 * 0x450 + *param_1),
             (iVar1 - param_2) * 0x450);
    local_8 = 0;
    FUN_0044c870(*param_1 + param_2 * 0x450,param_4);
  }
  else {
    FUN_0044c7b0();
  }
  uVar2 = param_2 + param_4;
  local_8 = 0xffffffff;
  for (; param_2 < uVar2; param_2 = param_2 + 1) {
    FUN_0044c740();
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

