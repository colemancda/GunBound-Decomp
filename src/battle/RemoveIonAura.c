/* RemoveIonAura - 0x0043c4f0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_0043c4f0 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: the layer it
 * walks is class id 0x186a5 (100005) of the battle entity registry
 * DAT_006a7f8c, which the layer map identifies as the per-mobile ion auras:
 * SpawnKnightIon stamps that id through InitProjectile(obj, 0x186a5) and
 * SpawnLaserIon / InitLaserIon do the same. Both spawners call it as their
 * first act, before building the new aura (so a replacement aura displaces
 * the old one), and AdvanceTurnQueue and ProcessBattleAction (the weapon-
 * select-sound action) call it as the third of a run FUN_0043c440,
 * FUN_0043c4a0, FUN_0043c4f0, one per layer. The body finds the 0x186a5
 * layer, scans its intrusive list for the object whose key at obj + 8
 * equals EDX, unlinks it (prev at +0xc, next at +0x10) and runs its virtual
 * slot 0 with 1, the scalar deleting destructor, so it removes the matching
 * aura. The key's meaning (owner mobile) is inferred from the spawner
 * usage, not shown; the other two members of the run are unnamed.
 *
 * BUG, reported not fixed: it is declared __fastcall(param_1, param_2) but
 * all four callers (SpawnLaserIon, SpawnKnightIon, AdvanceTurnQueue,
 * ProcessBattleAction) pass nothing. In the binary the two spawners set EDX
 * (mov edx,esi) from their own incoming arguments; the other two sites do
 * not visibly set it, so the key reaching the body is whatever EDX held.
 */
#include "ghidra_types.h"


void __fastcall RemoveIonAura(undefined4 param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  if (uVar1 < 0x186a6) {
    while (uVar1 != 0x186a5) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar1 = *(uint *)(iVar2 + 4);
      if (0x186a5 < uVar1) {
        return;
      }
    }
    puVar3 = *(undefined4 **)(iVar2 + 0x10);
    uVar1 = puVar3[2];
    if (uVar1 <= param_2) {
      while (uVar1 != param_2) {
        puVar3 = (undefined4 *)puVar3[4];
        uVar1 = puVar3[2];
        if (param_2 < uVar1) {
          return;
        }
      }
      *(undefined4 *)(puVar3[3] + 0x10) = puVar3[4];
      *(undefined4 *)(puVar3[4] + 0xc) = puVar3[3];
      (**(code **)*puVar3)(1);
    }
  }
  return;
}

