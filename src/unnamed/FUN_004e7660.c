/* FUN_004e7660 - 0x004e7660 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __fastcall FUN_004e7660(undefined4 param_1,int param_2,undefined4 *param_3,undefined4 *param_4)

{
  ushort uVar1;
  uint in_EAX;
  uint uVar2;
  ushort *puVar3;
  
  uVar2 = in_EAX & 0xffffff00;
  if (*(int *)(param_2 + 0x40bd4) != *(int *)(param_2 + 0x40bd0)) {
    puVar3 = (ushort *)(*(int *)(param_2 + 0x40bd4) * 0x200 + 0x3d0 + param_2);
    uVar1 = *puVar3;
    for (uVar2 = (uint)(uVar1 >> 2); uVar2 != 0; uVar2 = uVar2 - 1) {
      *param_3 = *(undefined4 *)puVar3;
      puVar3 = puVar3 + 2;
      param_3 = param_3 + 1;
    }
    for (uVar2 = uVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(char *)param_3 = (char)*puVar3;
      puVar3 = (ushort *)((int)puVar3 + 1);
      param_3 = (undefined4 *)((int)param_3 + 1);
    }
    *param_4 = *(undefined4 *)(param_2 + 0x403d0 + *(int *)(param_2 + 0x40bd4) * 4);
    uVar2 = *(int *)(param_2 + 0x40bd4) + 1U & 0x800001ff;
    if ((int)uVar2 < 0) {
      uVar2 = (uVar2 - 1 | 0xfffffe00) + 1;
    }
    *(uint *)(param_2 + 0x40bd4) = uVar2;
    uVar2 = CONCAT31((int3)(uVar2 >> 8),1);
  }
  return uVar2;
}

