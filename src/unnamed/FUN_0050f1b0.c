/* FUN_0050f1b0 - 0x0050f1b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined1 __thiscall FUN_0050f1b0(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  char cVar3;
  undefined1 uVar4;
  
  puVar2 = *(undefined4 **)(param_1 + 4);
  uVar4 = 0;
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = puVar2 + 2;
    puVar2 = (undefined4 *)*puVar2;
    cVar3 = (**(code **)(*(int *)*puVar1 + 0xc))(param_2,param_3);
    if (cVar3 == '\x01') {
      uVar4 = 1;
    }
  }
  return uVar4;
}

