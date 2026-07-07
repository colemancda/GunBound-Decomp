/* FUN_004fe590 - 0x004fe590 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004fe590(undefined4 param_1,undefined4 *param_2)

{
  ushort uVar1;
  undefined4 *in_EAX;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  *param_2 = *in_EAX;
  param_2[1] = in_EAX[1];
  param_2[2] = in_EAX[2];
  *(undefined2 *)(param_2 + 3) = *(undefined2 *)(in_EAX + 3);
  uVar1 = *(ushort *)((int)in_EAX + 0xe);
  *(ushort *)((int)param_2 + 0xe) = uVar1;
  puVar3 = in_EAX + 4;
  puVar4 = param_2 + 4;
  for (uVar2 = (uint)(uVar1 >> 2); uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  for (uVar2 = uVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined1 *)puVar4 = *(undefined1 *)puVar3;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  }
  return;
}

