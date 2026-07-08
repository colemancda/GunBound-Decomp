/* FUN_0040bfd0 - 0x0040bfd0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_0040bfd0(int param_1,uint param_2,uint param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537850) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  uVar4 = param_2 | 0xf;
  if (uVar4 != 0xffffffff) {
    uVar1 = *(uint *)(param_1 + 0x18);
    uVar3 = uVar1 >> 1;
    param_2 = uVar4;
    if ((uVar4 / 3 < uVar3) && (uVar1 <= -uVar3 - 2)) {
      param_2 = uVar3 + uVar1;
    }
  }
  local_8 = 0;
  puVar2 = operator_new(param_2 + 1);
  if (param_3 != 0) {
    if (*(uint *)(param_1 + 0x18) < 0x10) {
      puVar5 = (undefined4 *)(param_1 + 4);
    }
    else {
      puVar5 = *(undefined4 **)(param_1 + 4);
    }
    puVar6 = puVar2;
    for (uVar4 = param_3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    for (uVar4 = param_3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
      puVar5 = (undefined4 *)((int)puVar5 + 1);
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
  }
  if (0xf < *(uint *)(param_1 + 0x18)) {
    _free(*(void **)(param_1 + 4));
  }
  puVar5 = (undefined4 *)(param_1 + 4);
  *(undefined1 *)puVar5 = 0;
  *puVar5 = puVar2;
  *(uint *)(param_1 + 0x18) = param_2;
  *(uint *)(param_1 + 0x14) = param_3;
  if (0xf < param_2) {
    puVar5 = puVar2;
  }
  *(undefined1 *)((int)puVar5 + param_3) = 0;
  return;
}

