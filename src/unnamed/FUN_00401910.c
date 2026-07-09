/* FUN_00401910 - 0x00401910 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_00401910(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00537922;
  *unaff_FS_OFFSET = &local_c;
  FUN_004f2e40();
  local_4 = 0;
  param_1[2] = &PTR_LAB_00551cf4;
  *param_1 = &PTR_FUN_00551cf0;
  param_1[2] = &PTR_LAB_00551cb8;
  param_1[0x6f9] = 0;
  param_1[0x6fa] = 0;
  param_1[0x6fb] = 0;
  param_1[0x6fc] = 0;
  param_1[0x6fd] = 10;
  param_1[0x6fe] = 0;
  FUN_004fe420(0x3f400000,0x3e800000,0x40100000);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
  puVar3 = param_1 + 3;
  for (iVar2 = 0x300; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  param_1[0x304] = 0;
  param_1[0x303] = 0;
  param_1[0x3c8] = 0;
  param_1[0x3c9] = 0;
  puVar3 = param_1 + 0x3ca;
  for (iVar2 = 0x1a0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  param_1[0x56a] = 0;
  puVar3 = param_1 + 0x56b;
  for (iVar2 = 0x80; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  puVar3 = param_1 + 0x66b;
  for (iVar2 = 0x80; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  param_1[0x6eb] = 0xffffffff;
  *(undefined1 *)((int)param_1 + 0x1bbe) = 0;
  *(undefined1 *)(param_1 + 0x6f3) = 0;
  param_1[0x6f4] = 0;
  *(undefined1 *)(param_1 + 0x6f5) = 1;
  param_1[0x6f6] = 0;
  param_1[0x6f7] = 0;
  param_1[0x6f8] = 0;
  uVar1 = FUN_004fd090(param_1 + 2);
  param_1[0x6f7] = uVar1;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

