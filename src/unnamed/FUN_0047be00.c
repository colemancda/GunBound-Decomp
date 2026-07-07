/* FUN_0047be00 - 0x0047be00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0047be00(undefined4 *param_1)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  uStack_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_0053c03a;
  *unaff_FS_OFFSET = &uStack_c;
  *param_1 = &PTR_FUN_00556078;
  local_4 = 0;
  iVar1 = param_1[0xff0];
  if (DAT_00793549 != '\0') {
    if (iVar1 != -1) {
      (**(code **)(**(int **)(DAT_00793554 + iVar1 * 4) + 0xc))();
    }
    if (iVar1 == 0) {
      DAT_00793568 = 0;
    }
  }
  param_1[0xff0] = 0xffffffff;
  local_4 = 0xffffffff;
  FUN_00455570(param_1);
  *unaff_FS_OFFSET = uStack_c;
  return;
}

