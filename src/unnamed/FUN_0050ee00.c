/* FUN_0050ee00 - 0x0050ee00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0050ee00(undefined4 *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  void *_Memory;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_0053778b;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &PTR_FUN_00557f80;
  local_4 = 0;
  if (param_1[3] != 0) {
    do {
      puVar2 = (undefined4 *)param_1[2];
      puVar3 = (undefined4 *)puVar2[1];
      _Memory = (void *)puVar2[2];
      param_1[2] = puVar3;
      if (puVar3 == (undefined4 *)0x0) {
        param_1[1] = 0;
      }
      else {
        *puVar3 = 0;
      }
      *puVar2 = param_1[5];
      param_1[5] = puVar2;
      piVar1 = param_1 + 3;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 == 0) {
        FUN_00509fd0();
      }
      if (_Memory != (void *)0x0) {
        FUN_0050e560();
        _free(_Memory);
      }
    } while (param_1[3] != 0);
  }
  FUN_00509fd0();
  *unaff_FS_OFFSET = local_c;
  return;
}

