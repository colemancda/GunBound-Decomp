/* FUN_0041ee10 - 0x0041ee10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0041ee10(undefined4 param_1,int param_2)

{
  undefined1 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined2 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *local_14;
  undefined4 *local_10;
  
  if (0 < *(int *)(param_2 + 0x58b60)) {
    puVar1 = (undefined1 *)(param_2 + 0x58c4a);
    puVar5 = (undefined2 *)(param_2 + 0x5917c);
    puVar2 = (undefined4 *)(param_2 + 0x59154);
    puVar3 = (undefined4 *)(param_2 + 0x58b64);
    local_14 = (undefined4 *)(param_2 + 0x58bbe);
    local_10 = (undefined4 *)(param_2 + 0x58c54);
    do {
      *puVar3 = *(undefined4 *)((int)puVar3 + 9);
      puVar3[1] = *(undefined4 *)((int)puVar3 + 0xd);
      *(undefined1 *)(puVar3 + 2) = *(undefined1 *)((int)puVar3 + 0x11);
      *local_14 = *(undefined4 *)((int)local_14 + 0xe);
      local_14[1] = *(undefined4 *)((int)local_14 + 0x12);
      local_14[2] = *(undefined4 *)((int)local_14 + 0x16);
      *(undefined2 *)(local_14 + 3) = *(undefined2 *)((int)local_14 + 0x1a);
      *puVar1 = puVar1[1];
      puVar6 = local_10 + 0x20;
      puVar7 = local_10;
      for (iVar4 = 0x20; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar7 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
      }
      *puVar2 = puVar2[1];
      *puVar5 = puVar5[1];
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
      puVar1 = puVar1 + 1;
      puVar3 = (undefined4 *)((int)puVar3 + 9);
      local_14 = (undefined4 *)((int)local_14 + 0xe);
      local_10 = local_10 + 0x20;
    } while ((int)(puVar1 + (-0x58c4a - param_2)) < *(int *)(param_2 + 0x58b60));
  }
  puVar2 = (undefined4 *)(*(int *)(param_2 + 0x58b60) * 9 + 0x58b64 + param_2);
  *puVar2 = 0;
  puVar2[1] = 0;
  *(undefined1 *)(puVar2 + 2) = 0;
  puVar2 = (undefined4 *)((*(int *)(param_2 + 0x58b60) + 0x6569) * 0xe + param_2);
  *puVar2 = 0;
  puVar2[1] = 0;
  puVar2[2] = 0;
  *(undefined1 *)(puVar2 + 3) = 0;
  *(undefined1 *)(param_2 + 0x58c4a + *(int *)(param_2 + 0x58b60)) = 0;
  *(undefined2 *)(param_2 + 0x5917c + *(int *)(param_2 + 0x58b60) * 2) = 0;
  puVar2 = (undefined4 *)(*(int *)(param_2 + 0x58b60) * 0x80 + 0x58c54 + param_2);
  for (iVar4 = 0x20; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)(param_2 + 0x59154 + *(int *)(param_2 + 0x58b60) * 4) = 0xffffffff;
  *(int *)(param_2 + 0x58b60) = *(int *)(param_2 + 0x58b60) + -1;
  return;
}

