/* FUN_004e8e30 - 0x004e8e30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e8e30(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 *param_4,
                 undefined1 param_5)

{
  undefined4 *puVar1;
  
  puVar1 = operator_new(0x10);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = param_1;
    puVar1[1] = param_2;
    puVar1[2] = param_3;
    *(undefined2 *)(puVar1 + 3) = *param_4;
    *(undefined1 *)((int)puVar1 + 0xe) = param_5;
    *(undefined1 *)((int)puVar1 + 0xf) = 0;
  }
  return;
}

