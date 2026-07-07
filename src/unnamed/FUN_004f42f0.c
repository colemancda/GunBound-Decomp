/* FUN_004f42f0 - 0x004f42f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f42f0(int param_1)

{
  int *piVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_00537748;
  *unaff_FS_OFFSET = &local_c;
  local_4 = 0;
  FUN_004f46b0();
  local_4 = 0xffffffff;
  piVar1 = *(int **)(param_1 + 0x110);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
  }
  *(undefined4 *)(param_1 + 0x110) = 0;
  *unaff_FS_OFFSET = local_c;
  return;
}

