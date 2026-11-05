/* ExplodePlayerMines - 0x0043c440 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_0043c440 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: Player slot
 * in EAX; walks the class-100003 (mine) layer of the active-object
 * registry for keys slot*8 .. slot*8+7 and fires vtable slot +0x20 on each
 * hit. Slot 8 of vtable 0x5563f0 (the Mine class installed by InitMine) is
 * ExplodeMine at 0x497ad0, and FindFreeMineKey documents the 8-key per-
 * player block. It does not unlink or delete. Callers AdvanceTurnQueue
 * (the player whose turn ended) and ProcessBattleAction's weapon-select-
 * sound action pass a player slot, as the first of the FUN_0043c440 /
 * FUN_0043c4a0 / RemoveIonAura run. LIKELY: the layer-class and slot
 * identities rest on FindFreeMineKey's header, and the callers' reason for
 * exploding is not independently documented.
 */
#include "ghidra_types.h"


void ExplodePlayerMines(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int in_EAX;
  int *piVar4;
  uint uVar5;
  
  uVar5 = in_EAX * 8;
  iVar1 = uVar5 + 8;
joined_r0x0043c44c:
  if (iVar1 <= (int)uVar5) {
    return;
  }
  iVar2 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar3 = *(uint *)(iVar2 + 4);
  while (uVar3 < 0x186a4) {
    if (uVar3 == 0x186a3) {
      piVar4 = *(int **)(iVar2 + 0x10);
      uVar3 = piVar4[2];
      if (uVar3 <= uVar5) goto LAB_0043c485;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar3 = *(uint *)(iVar2 + 4);
  }
  goto LAB_0043c498;
  while( true ) {
    piVar4 = (int *)piVar4[4];
    uVar3 = piVar4[2];
    if (uVar5 < uVar3) break;
LAB_0043c485:
    if (uVar3 == uVar5) {
      (**(code **)(*piVar4 + 0x20))();
      break;
    }
  }
LAB_0043c498:
  uVar5 = uVar5 + 1;
  goto joined_r0x0043c44c;
}

