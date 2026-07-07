/* FUN_0050f350 - 0x0050f350 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0050f350(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int in_EAX;
  
  FUN_0050f390();
  puVar1 = *(undefined4 **)(in_EAX + 0x10);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[2] = *param_1;
  }
  *(undefined4 *)(in_EAX + 0x10) = *puVar1;
  puVar1[1] = param_2;
  *puVar1 = param_3;
  *(int *)(in_EAX + 8) = *(int *)(in_EAX + 8) + 1;
  return;
}

