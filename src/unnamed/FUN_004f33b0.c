/* FUN_004f33b0 - 0x004f33b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004f33b0(undefined4 *param_1)

{
  void *_Memory;
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_00537818;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &PTR_FUN_00557538;
  local_4 = 0;
  if ((*(char *)(param_1 + 0x82) != '\0') &&
     (_Memory = (void *)param_1[0x83], _Memory != (void *)0x0)) {
    FUN_004f2a10();
    _free(_Memory);
  }
  puVar1 = (undefined4 *)param_1[0x35];
  *(undefined1 *)(param_1 + 0x82) = 0;
  while (puVar1 != (undefined4 *)0x0) {
    puVar2 = (undefined4 *)*puVar1;
    puVar1 = (undefined4 *)puVar1[0x36];
    (*(code *)*puVar2)(1);
  }
  *param_1 = &PTR_LAB_0055752c;
  *unaff_FS_OFFSET = local_c;
  return;
}

