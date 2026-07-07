/* FUN_0040bee0 - 0x0040bee0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __thiscall FUN_0040bee0(int param_1,undefined4 *param_2,uint param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  
  uVar4 = *(uint *)(param_1 + 0x18);
  if (uVar4 < 0x10) {
    puVar1 = (undefined4 *)(param_1 + 4);
  }
  else {
    puVar1 = *(undefined4 **)(param_1 + 4);
  }
  if (puVar1 <= param_2) {
    puVar1 = (undefined4 *)(param_1 + 4);
    puVar3 = puVar1;
    if (0xf < uVar4) {
      puVar3 = (undefined4 *)*puVar1;
    }
    if (param_2 < (undefined4 *)(*(int *)(param_1 + 0x14) + (int)puVar3)) {
      if (0xf < uVar4) {
        puVar1 = (undefined4 *)*puVar1;
      }
      iVar2 = FUN_0040b9f0(param_1,(int)param_2 - (int)puVar1,param_3);
      return iVar2;
    }
  }
  if (param_3 == 0xffffffff) {
    FUN_00520291();
  }
  if (*(uint *)(param_1 + 0x18) < param_3) {
    FUN_0040bfd0(param_3,*(undefined4 *)(param_1 + 0x14));
  }
  else if (param_3 == 0) {
    *(undefined4 *)(param_1 + 0x14) = 0;
    if (*(uint *)(param_1 + 0x18) < 0x10) {
      *(undefined1 *)(param_1 + 4) = 0;
      return param_1;
    }
    **(undefined1 **)(param_1 + 4) = 0;
    return param_1;
  }
  if (param_3 != 0) {
    if (*(uint *)(param_1 + 0x18) < 0x10) {
      puVar1 = (undefined4 *)(param_1 + 4);
    }
    else {
      puVar1 = *(undefined4 **)(param_1 + 4);
    }
    for (uVar4 = param_3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar1 = *param_2;
      param_2 = param_2 + 1;
      puVar1 = puVar1 + 1;
    }
    for (uVar4 = param_3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined1 *)puVar1 = *(undefined1 *)param_2;
      param_2 = (undefined4 *)((int)param_2 + 1);
      puVar1 = (undefined4 *)((int)puVar1 + 1);
    }
    *(uint *)(param_1 + 0x14) = param_3;
    if (0xf < *(uint *)(param_1 + 0x18)) {
      *(undefined1 *)(*(int *)(param_1 + 4) + param_3) = 0;
      return param_1;
    }
    *(undefined1 *)(param_1 + 4 + param_3) = 0;
  }
  return param_1;
}

