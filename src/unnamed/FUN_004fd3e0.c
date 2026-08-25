/* FUN_004fd3e0 - 0x004fd3e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ECX PROMOTED (2026-08-25): the map-find call needs EAX = ecx + 0x1ac0, and
 * ECX is this function's own incoming register, which Ghidra never modelled.
 * The function has NO call sites anywhere in the image, so there is no caller
 * to derive it from and none to update -- regEcx is declared so the find's
 * arguments can be written honestly.
 */
#include "ghidra_types.h"


undefined4 FUN_004fd3e0(int param_1,undefined4 *param_2,int regEcx)

{
  undefined2 uVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  undefined1 local_1c [10];
  char local_12 [17];
  byte local_1;
  
  uVar3 = 0;
  do {
    bVar2 = (byte)uVar3;
    if (*(char *)(uVar3 + param_1) == '\0') break;
    bVar2 = bVar2 + 1;
    local_12[uVar3] = *(char *)(uVar3 + param_1);
    uVar3 = (uint)bVar2;
  } while (bVar2 < 0x10);
  local_1 = bVar2;
  local_12[bVar2] = '\0';
  iVar4 = StringMap_Find_28(local_12,(uint *)local_1c,(undefined4 *)&param_1,(int *)(regEcx + 0x1ac0),
                       (uint *)(local_1c + 4));
  if (iVar4 == 0) {
    return 0;
  }
  *param_2 = *(undefined4 *)(iVar4 + 0x12);
  param_2[1] = *(undefined4 *)(iVar4 + 0x16);
  param_2[2] = *(undefined4 *)(iVar4 + 0x1a);
  uVar1 = *(undefined2 *)(iVar4 + 0x1e);
  *(undefined2 *)(param_2 + 3) = uVar1;
  return CONCAT31((int3)(CONCAT22((short)((uint)(iVar4 + 0x12) >> 0x10),uVar1) >> 8),1);
}

