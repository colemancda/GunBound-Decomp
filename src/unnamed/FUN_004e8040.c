/* FUN_004e8040 - 0x004e8040 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004e8040(undefined1 param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  ushort *in_EAX;
  uint uVar4;
  undefined4 *puVar5;
  
  iVar3 = DAT_007934e8;
  *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
  *(undefined2 *)(iVar3 + 0x4d4) = 0x4500;
  *(undefined2 *)(iVar3 + 0x4d6) = 1;
  iVar2 = *(int *)(iVar3 + 0x44d0);
  *(int *)(iVar3 + 0x44d0) = iVar2 + 2;
  *(undefined1 *)(iVar2 + 0x4d2 + iVar3) = param_1;
  iVar2 = *(int *)(iVar3 + 0x44d0);
  *(int *)(iVar3 + 0x44d0) = iVar2 + 1;
  uVar1 = *in_EAX;
  puVar5 = (undefined4 *)(iVar2 + 0x4d1 + iVar3);
  for (uVar4 = (uint)(uVar1 >> 2); uVar4 != 0; uVar4 = uVar4 - 1) {
    *puVar5 = *(undefined4 *)in_EAX;
    in_EAX = in_EAX + 2;
    puVar5 = puVar5 + 1;
  }
  for (uVar4 = uVar1 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(char *)puVar5 = (char)*in_EAX;
    in_EAX = (ushort *)((int)in_EAX + 1);
    puVar5 = (undefined4 *)((int)puVar5 + 1);
  }
  *(uint *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + (uint)uVar1;
  FUN_004d2680();
  return;
}

