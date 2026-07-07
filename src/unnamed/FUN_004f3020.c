/* FUN_004f3020 - 0x004f3020 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f3020(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int unaff_EBX;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)(*(undefined4 **)(unaff_EBX + 4))[7];
  if (puVar3 != *(undefined4 **)(unaff_EBX + 4)) {
    do {
      puVar1 = (undefined4 *)puVar3[4];
      while (puVar1 != puVar3) {
        puVar2 = (undefined4 *)*puVar1;
        puVar1 = (undefined4 *)puVar1[4];
        (*(code *)*puVar2)(1);
      }
      puVar3[3] = puVar3;
      puVar3[4] = puVar3;
      puVar3 = (undefined4 *)puVar3[7];
    } while (puVar3 != *(undefined4 **)(unaff_EBX + 4));
  }
  return;
}

