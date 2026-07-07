/* FUN_0044fd00 - 0x0044fd00 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * __fastcall FUN_0044fd00(undefined4 param_1,undefined4 *param_2)

{
  undefined4 in_EAX;
  int iVar1;
  undefined4 *puVar2;
  
  param_2[2] = in_EAX;
  param_2[6] = 0xffffffff;
  param_2[9] = 0xffffffff;
  param_2[3] = 0;
  param_2[4] = 0;
  *(undefined1 *)(param_2 + 5) = 0;
  *(undefined1 *)((int)param_2 + 0x15) = 0;
  param_2[7] = 0;
  *(undefined1 *)(param_2 + 8) = 0;
  param_2[10] = 0;
  param_2[0xb] = 0;
  param_2[0x10] = 0;
  param_2[1] = 500000;
  *param_2 = &PTR_FUN_00555b54;
  puVar2 = param_2 + 0x11;
  for (iVar1 = 100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = param_2 + 0xb7;
  for (iVar1 = 100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_2[0xb5] = 0;
  param_2[0xb6] = 0;
  return param_2;
}

