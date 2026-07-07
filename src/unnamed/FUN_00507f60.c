/* FUN_00507f60 - 0x00507f60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00507f60(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar1 = operator_new(0x140);
  puVar2 = (undefined4 *)0x0;
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    *(undefined1 *)(puVar1 + 1) = 0;
    puVar1[2] = 0;
    *(undefined1 *)(puVar1 + 7) = 1;
    *(undefined1 *)((int)puVar1 + 0x1d) = 0;
    *(undefined1 *)((int)puVar1 + 0x1e) = 0;
    *puVar1 = &PTR_LAB_00557c84;
    puVar1[8] = 2;
    puVar2 = puVar1 + 0xe;
    for (iVar3 = 0x40; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    puVar1[0x4e] = 0;
    puVar1[0x4f] = 0;
    puVar2 = puVar1;
  }
  puVar2[9] = param_1;
  puVar2[10] = param_2;
  puVar2[0xb] = param_3;
  puVar2[0xc] = param_4;
  puVar2[0xd] = param_5;
  puVar2[0x4e] = param_6;
  return;
}

