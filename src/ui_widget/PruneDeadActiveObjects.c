/* PruneDeadActiveObjects - 0x004f3100 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004f3100 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: The registry
 * walk is the same ring-of-rings TickActiveObjectLayers uses (regEbx + 4
 * is the head, layer links at +0x1c, object ring at +0x10), and it is
 * called straight after TickActiveObjectLayers in
 * State09_ReadyRoom_OnTick, State11_InBattle_OnTick and the third caller
 * FUN_0043c860. It unlinks every object whose byte at +0x14 is non-zero
 * and calls the object's vtable slot 0 with 1 (the deleting destructor).
 * The +0x14 byte is the flag the object tickers set when finished:
 * ExplodeSuperShot_Bullet*, TickFlameEffect, TickRiderEffect and others
 * mark the object dead through param_1[5] = 1, and src/cxx/Effects.cpp
 * records it as m_dead with the comment that the registry prunes it.
 * src/cxx/PLAN.md already calls this function the active-object container
 * GC.
 */
#include "ghidra_types.h"


void PruneDeadActiveObjects(int regEbx)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)(*(undefined4 **)(regEbx + 4))[7];
  if (puVar3 != *(undefined4 **)(regEbx + 4)) {
    do {
      puVar1 = (undefined4 *)puVar3[4];
      while (puVar2 = puVar1, puVar2 != puVar3) {
        puVar1 = (undefined4 *)puVar2[4];
        if (*(char *)(puVar2 + 5) != '\0') {
          *(undefined4 **)(puVar2[3] + 0x10) = puVar1;
          *(undefined4 *)(puVar2[4] + 0xc) = puVar2[3];
          (**(code **)*puVar2)(1);
        }
      }
      puVar3 = (undefined4 *)puVar3[7];
    } while (puVar3 != *(undefined4 **)(regEbx + 4));
  }
  return;
}

