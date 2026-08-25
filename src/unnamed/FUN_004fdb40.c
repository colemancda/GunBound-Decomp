/* FUN_004fdb40 - 0x004fdb40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ECX PROMOTED (2026-08-25): the map-find call needs EAX = ecx + 0x1af0, and
 * ECX is this function's own incoming register, which Ghidra never modelled.
 * The function has NO call sites anywhere in the image, so there is no caller
 * to derive it from and none to update -- regEcx is declared so the find's
 * arguments can be written honestly.
 */
#include "ghidra_types.h"


bool FUN_004fdb40(int param_1,int regEcx)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  undefined1 local_1c [10];
  char local_12 [17];
  byte local_1;
  
  uVar2 = 0;
  do {
    bVar1 = (byte)uVar2;
    if (*(char *)(uVar2 + param_1) == '\0') break;
    bVar1 = bVar1 + 1;
    local_12[uVar2] = *(char *)(uVar2 + param_1);
    uVar2 = (uint)bVar1;
  } while (bVar1 < 0x10);
  local_1 = bVar1;
  local_12[bVar1] = '\0';
  iVar3 = StringMap_Find_1c(local_12,(uint *)local_1c,(undefined4 *)&param_1,(int *)(regEcx + 0x1af0),
                       (uint *)(local_1c + 4));
  return iVar3 == 0;
}

