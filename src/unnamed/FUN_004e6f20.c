/* FUN_004e6f20 - 0x004e6f20 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e6f20(undefined4 *param_1,uint param_2)

{
  int in_EAX;
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 local_400 [256];
  
  FUN_004f48b0(2);
  iVar1 = (int)(param_2 + ((int)param_2 >> 0x1f & 0xfU)) >> 4;
  if (0 < iVar1) {
    puVar3 = param_1;
    do {
      FUN_004f5e10((undefined1 *)(((int)local_400 - (int)param_1) + (int)puVar3),in_EAX + 0x44ff8);
      puVar3 = puVar3 + 4;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  param_2 = param_2 & ((int)param_2 < 0) - 1;
  puVar3 = local_400;
  for (uVar2 = param_2 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *param_1 = *puVar3;
    puVar3 = puVar3 + 1;
    param_1 = param_1 + 1;
  }
  for (param_2 = param_2 & 3; param_2 != 0; param_2 = param_2 - 1) {
    *(undefined1 *)param_1 = *(undefined1 *)puVar3;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
    param_1 = (undefined4 *)((int)param_1 + 1);
  }
  return;
}

