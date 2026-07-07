/* FUN_004059e0 - 0x004059e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004059e0(undefined4 param_1,uint param_2,undefined4 *param_3)

{
  int in_EAX;
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  uVar1 = ((int)param_2 < 0) - 1 & param_2;
  puVar3 = (undefined4 *)(*(int *)(in_EAX + 0x2000) + in_EAX);
  for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar3 = *param_3;
    param_3 = param_3 + 1;
    puVar3 = puVar3 + 1;
  }
  for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined1 *)puVar3 = *(undefined1 *)param_3;
    param_3 = (undefined4 *)((int)param_3 + 1);
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  }
  *(uint *)(in_EAX + 0x2000) = *(int *)(in_EAX + 0x2000) + param_2;
  return;
}

