/* FUN_004f2f00 - 0x004f2f00 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_004f2f00(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint unaff_ESI;
  
  puVar3 = operator_new(0x20);
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    puVar3[1] = unaff_ESI;
    puVar3[2] = 0xffffffff;
    puVar3[3] = 0;
    puVar3[4] = 0;
    *(undefined1 *)(puVar3 + 5) = 0;
    *puVar3 = &PTR_FUN_00557530;
    *(undefined1 *)((int)puVar3 + 0x15) = 1;
    puVar3[6] = 0;
    puVar3[7] = 0;
  }
  iVar1 = *(int *)(*(int *)(param_1 + 4) + 0x1c);
  uVar2 = *(uint *)(iVar1 + 4);
  while( true ) {
    if (unaff_ESI < uVar2) {
      puVar3[7] = iVar1;
      puVar3[6] = *(undefined4 *)(iVar1 + 0x18);
      *(undefined4 **)(*(int *)(iVar1 + 0x18) + 0x1c) = puVar3;
      *(undefined4 **)(iVar1 + 0x18) = puVar3;
      puVar3[4] = puVar3;
      puVar3[3] = puVar3;
      return puVar3;
    }
    if (uVar2 == unaff_ESI) break;
    iVar1 = *(int *)(iVar1 + 0x1c);
    uVar2 = *(uint *)(iVar1 + 4);
  }
  if (puVar3 != (undefined4 *)0x0) {
    (**(code **)*puVar3)(1);
  }
  return (undefined4 *)0x0;
}

