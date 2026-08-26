/* FUN_004507d0 - 0x004507d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EBX RECOVERED (2026-08-25): the list to walk.  Two sites take the
 * g_clientContext + 0x6a7f88 active-object list -- the one the weather-hazard
 * spawners already name -- and the third takes `lea ebx,[esi+0x85c]` where ESI
 * is FUN_004e39b0's own regEsi, a parameter that function already has.  All
 * three are determined without touching a caller frame.
 */
#include "ghidra_types.h"


void FUN_004507d0(int regEbx)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = *(int *)(*(int *)(regEbx + 4) + 0x1c);
  if (iVar3 != *(int *)(regEbx + 4)) {
    do {
      piVar2 = *(int **)(iVar3 + 0x10);
      cVar1 = *(char *)((int)piVar2 + 0x15);
      while (cVar1 == '\0') {
        (**(code **)(*piVar2 + 8))();
        piVar2 = (int *)piVar2[4];
        cVar1 = *(char *)((int)piVar2 + 0x15);
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
    } while (iVar3 != *(int *)(regEbx + 4));
  }
  return;
}

