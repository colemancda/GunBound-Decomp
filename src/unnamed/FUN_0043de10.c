/* FUN_0043de10 - 0x0043de10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0043de10(void)

{
  int iVar1;
  int *in_EAX;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  int *piVar6;
  
  puVar2 = (undefined4 *)(**(code **)(*(int *)*in_EAX + 0x10))();
  if ((-1 < in_EAX[3]) && (puVar2 == (undefined4 *)*in_EAX)) {
    LOCK();
    in_EAX[3] = in_EAX[3] + 1;
    UNLOCK();
    return;
  }
  iVar3 = (**(code **)*puVar2)(in_EAX[1],1);
  if (iVar3 == 0) {
    FUN_004058b0();
    return;
  }
  *(int *)(iVar3 + 4) = in_EAX[1];
  iVar1 = in_EAX[1];
  piVar5 = in_EAX + 4;
  piVar6 = (int *)(iVar3 + 0x10);
  for (uVar4 = iVar1 + 1U >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *piVar6 = *piVar5;
    piVar5 = piVar5 + 1;
    piVar6 = piVar6 + 1;
  }
  for (uVar4 = iVar1 + 1U & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(char *)piVar6 = (char)*piVar5;
    piVar5 = (int *)((int)piVar5 + 1);
    piVar6 = (int *)((int)piVar6 + 1);
  }
  return;
}

