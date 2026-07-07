/* FUN_004d34f0 - 0x004d34f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004d34f0(undefined4 param_1,uint param_2,undefined4 *param_3)

{
  int in_EAX;
  uint uVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(in_EAX + 0x44da + *(int *)(in_EAX + 0x84d8));
  for (uVar1 = param_2 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar2 = *param_3;
    param_3 = param_3 + 1;
    puVar2 = puVar2 + 1;
  }
  for (uVar1 = param_2 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined1 *)puVar2 = *(undefined1 *)param_3;
    param_3 = (undefined4 *)((int)param_3 + 1);
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  }
  *(uint *)(in_EAX + 0x84d8) = *(int *)(in_EAX + 0x84d8) + param_2;
  return;
}

