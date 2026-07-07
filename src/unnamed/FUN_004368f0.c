/* FUN_004368f0 - 0x004368f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004368f0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 *puVar2;
  
  cVar1 = FUN_004065a0();
  if (cVar1 == '\0') {
    puVar2 = operator_new(0x4c);
    if (puVar2 == (undefined4 *)0x0) {
      puVar2 = (undefined4 *)0x0;
    }
    else {
      puVar2[1] = 0x30d54;
      puVar2[2] = 0xffffffff;
      puVar2[3] = 0;
      puVar2[4] = 0;
      *(undefined1 *)(puVar2 + 5) = 0;
      *(undefined1 *)((int)puVar2 + 0x15) = 0;
      puVar2[6] = 0xffffffff;
      puVar2[7] = 0;
      *(undefined1 *)(puVar2 + 8) = 0;
      puVar2[10] = 0;
      puVar2[0xb] = 0;
      puVar2[9] = 0xffffffff;
      *puVar2 = &PTR_FUN_00555f04;
      puVar2[0x10] = 0;
      puVar2[0x12] = 0;
    }
    puVar2[0xf] = param_2;
    puVar2[0xe] = param_1;
    puVar2[0x11] = param_3;
    RegisterActiveObject();
  }
  return;
}

