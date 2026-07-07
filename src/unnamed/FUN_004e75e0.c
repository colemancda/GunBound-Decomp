/* FUN_004e75e0 - 0x004e75e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_004e75e0(ushort *param_1,int param_2)

{
  ushort uVar1;
  int in_EAX;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  if (7 < param_2) {
    return 1;
  }
  uVar3 = *(int *)(in_EAX + 0x40bd0) + 1U & 0x800001ff;
  if ((int)uVar3 < 0) {
    uVar3 = (uVar3 - 1 | 0xfffffe00) + 1;
  }
  if (uVar3 != *(uint *)(in_EAX + 0x40bd4)) {
    uVar1 = *param_1;
    puVar4 = (undefined4 *)(*(int *)(in_EAX + 0x40bd0) * 0x200 + 0x3d0 + in_EAX);
    for (uVar2 = (uint)(uVar1 >> 2); uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar4 = *(undefined4 *)param_1;
      param_1 = param_1 + 2;
      puVar4 = puVar4 + 1;
    }
    for (uVar2 = uVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(char *)puVar4 = (char)*param_1;
      param_1 = (ushort *)((int)param_1 + 1);
      puVar4 = (undefined4 *)((int)puVar4 + 1);
    }
    *(int *)(in_EAX + 0x403d0 + *(int *)(in_EAX + 0x40bd0) * 4) = param_2;
    *(uint *)(in_EAX + 0x40bd0) = uVar3;
    return 1;
  }
  return 0;
}

