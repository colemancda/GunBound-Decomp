/* FUN_004d34a0 - 0x004d34a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004d34a0(undefined4 param_1,undefined4 param_2)

{
  int in_EAX;
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  uVar2 = *(uint *)(in_EAX + 0x44d0);
  *(uint *)(in_EAX + 0x84d4) = uVar2;
  puVar3 = (undefined4 *)(in_EAX + 0x4d0);
  puVar4 = (undefined4 *)(in_EAX + 0x44d4);
  for (uVar1 = uVar2 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined1 *)puVar4 = *(undefined1 *)puVar3;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  }
  *(undefined4 *)(in_EAX + 0x84d8) = param_1;
  *(undefined4 *)(in_EAX + 0x84dc) = param_2;
  return;
}

