/* FUN_00507ee0 - 0x00507ee0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00507ee0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  undefined4 *puVar1;
  
  puVar1 = operator_new(0x40);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    *(undefined1 *)(puVar1 + 1) = 0;
    puVar1[2] = 0;
    *(undefined1 *)(puVar1 + 7) = 1;
    *(undefined1 *)((int)puVar1 + 0x1d) = 0;
    *(undefined1 *)((int)puVar1 + 0x1e) = 0;
    puVar1[8] = 1;
    *(undefined1 *)(puVar1 + 0xe) = 0;
    *(undefined1 *)((int)puVar1 + 0x39) = 0;
    *(undefined1 *)((int)puVar1 + 0x3a) = 0;
    *puVar1 = &PTR_LAB_00557da0;
  }
  puVar1[9] = param_1;
  puVar1[0xf] = param_2;
  puVar1[10] = param_3;
  puVar1[0xb] = param_4;
  puVar1[0xc] = param_5;
  puVar1[0xd] = param_6;
  return;
}

