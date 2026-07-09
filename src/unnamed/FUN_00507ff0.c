/* FUN_00507ff0 - 0x00507ff0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 *
FUN_00507ff0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined2 param_6)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar1 = operator_new(0x53c);
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
    *puVar1 = &PTR_LAB_00557f30;
    puVar1[8] = 3;
  }
  puVar1[9] = 0;
  puVar1[10] = param_1;
  puVar1[0xb] = param_2;
  puVar1[0xd] = param_4;
  *(undefined2 *)(puVar1 + 0xe) = param_6;
  puVar1[0xc] = param_3;
  puVar3 = (undefined4 *)((int)puVar1 + 0x3a);
  for (iVar2 = 0x140; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  RenderWrappedText((undefined4 *)((int)puVar1 + 0x3a),param_5,0x80,(int)puVar1[0xc] / 6,0x500,1);
  return puVar1;
}

