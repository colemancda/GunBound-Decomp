/* FUN_00405810 - 0x00405810 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00405810(int *param_1,undefined4 *param_2)

{
  int *piVar1;
  int iVar2;
  int in_EAX;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  
  param_2 = (undefined4 *)*param_2;
  iVar2 = param_2[-3];
  (**(code **)(*(int *)param_2[-4] + 0x10))();
  (**(code **)*puVar3)();
  if (iVar4 == 0) {
    FUN_004058b0();
  }
  if (iVar2 < in_EAX) {
    in_EAX = iVar2;
  }
  puVar6 = (undefined4 *)(iVar4 + 0x10);
  puVar3 = param_2;
  for (uVar5 = in_EAX + 1U >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *puVar6 = *puVar3;
    puVar6 = puVar6 + 1;
    puVar3 = puVar3 + 1;
  }
  for (uVar5 = in_EAX + 1U & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined1 *)puVar6 = *(undefined1 *)puVar3;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
    puVar6 = (undefined4 *)((int)puVar6 + 1);
  }
  *(int *)(iVar4 + 4) = iVar2;
  piVar1 = param_2 + -1;
  LOCK();
  iVar2 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar2 == 1 || iVar2 + -1 < 0) {
    (**(code **)(*(int *)param_2[-4] + 4))(param_2 + -4);
  }
  *param_1 = iVar4 + 0x10;
  return;
}

