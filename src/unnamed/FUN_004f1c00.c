/* FUN_004f1c00 - 0x004f1c00 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004f1c00(uint param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int in_EAX;
  undefined4 *puVar4;
  
  puVar4 = *(undefined4 **)(*(int *)(in_EAX + 4) + 0x1c);
  uVar1 = puVar4[1];
  if (uVar1 <= param_1) {
    while (uVar1 != param_1) {
      puVar4 = (undefined4 *)puVar4[7];
      uVar1 = puVar4[1];
      if (param_1 < uVar1) {
        return;
      }
    }
    puVar2 = (undefined4 *)puVar4[4];
    while (puVar2 != puVar4) {
      puVar3 = (undefined4 *)*puVar2;
      puVar2 = (undefined4 *)puVar2[4];
      (*(code *)*puVar3)(1);
    }
    puVar4[3] = puVar4;
    puVar4[4] = puVar4;
  }
  return;
}

