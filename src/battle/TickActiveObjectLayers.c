/* TickActiveObjectLayers - 0x004507d0 in the original binary.
 *
 * Ticks every object in an active-object registry, layer by layer.
 *
 * NAMED 2026-08-26.  The structure is the registry CreateActiveObjectLayer
 * already documents: an outer list of "layer" nodes (walked here via +0x1c),
 * each holding an inner chain of objects (walked via +0x10), with +0x15
 * marking the chain terminator.
 *
 * What makes this a TICK rather than an unspecified visit is the vtable slot.
 * It dispatches slot 2 (+8) on every object, and slot 2 is already named
 * across the registry's classes in docs/vtable_census.txt: 27 vtables carry
 * AnimateProjectileTick there and 17 carry SimulateMobileFrame -- the
 * per-frame advance, under two names because projectiles and mobiles advance
 * differently.
 *
 * Its callers agree: State11_InBattle_OnTick and State09_ReadyRoom_OnTick both
 * pass g_clientContext + 0x6a7f88, the active-object list the weather-hazard
 * spawners name in their own headers, and the third caller (FUN_004e39b0,
 * itself reached from State11_InBattle_OnTick) passes its own object + 0x85c.
 *
 * EBX RECOVERED (2026-08-25): the list to walk.  Two sites take the
 * g_clientContext + 0x6a7f88 active-object list -- the one the weather-hazard
 * spawners already name -- and the third takes `lea ebx,[esi+0x85c]` where ESI
 * is FUN_004e39b0's own regEsi, a parameter that function already has.  All
 * three are determined without touching a caller frame.
 */
#include "ghidra_types.h"


void TickActiveObjectLayers(int regEbx)

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

