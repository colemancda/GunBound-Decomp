/* FUN_0040bda0 - 0x0040bda0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __thiscall FUN_0040bda0(int param_1,uint param_2,uint param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  if (*(uint *)(param_1 + 0x14) < param_2) {
    FUN_00520251();
  }
  uVar2 = *(int *)(param_1 + 0x14) - param_2;
  if (uVar2 < param_3) {
    param_3 = uVar2;
  }
  if (param_3 != 0) {
    puVar5 = (undefined4 *)(param_1 + 4);
    puVar4 = puVar5;
    puVar1 = puVar5;
    if (0xf < *(uint *)(param_1 + 0x18)) {
      puVar4 = (undefined4 *)*puVar5;
      puVar1 = (undefined4 *)*puVar5;
    }
    _memmove((void *)((int)puVar4 + param_2),(void *)((int)puVar1 + param_3 + param_2),
             uVar2 - param_3);
    iVar3 = *(int *)(param_1 + 0x14) - param_3;
    *(int *)(param_1 + 0x14) = iVar3;
    if (0xf < *(uint *)(param_1 + 0x18)) {
      puVar5 = (undefined4 *)*puVar5;
    }
    *(undefined1 *)((int)puVar5 + iVar3) = 0;
  }
  return param_1;
}

