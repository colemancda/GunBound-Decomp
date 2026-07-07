/* FUN_004f3060 - 0x004f3060 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004f3060(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar4 = (undefined4 *)(*(undefined4 **)(param_1 + 4))[7];
  if (puVar4 != *(undefined4 **)(param_1 + 4)) {
    do {
      puVar1 = (undefined4 *)puVar4[4];
      puVar2 = (undefined4 *)puVar4[7];
      while (puVar1 != puVar4) {
        puVar3 = (undefined4 *)*puVar1;
        puVar1 = (undefined4 *)puVar1[4];
        (*(code *)*puVar3)(1);
      }
      (**(code **)*puVar4)(1);
      puVar4 = puVar2;
    } while (puVar2 != *(undefined4 **)(param_1 + 4));
  }
  *(int *)(*(int *)(param_1 + 4) + 0x18) = *(int *)(param_1 + 4);
  *(int *)(*(int *)(param_1 + 4) + 0x1c) = *(int *)(param_1 + 4);
  return;
}

