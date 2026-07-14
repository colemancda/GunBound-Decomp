/* TickActiveObjectRegistry - 0x00406280 in the original binary.
 *
 * PROMOTED (2026-07-13): the per-frame Tick pass over an active-object
 * registry, sibling to DrawActiveObjectRegistry.c (0x4062b0). Walks the
 * registry's outer (layer) list at `param_1`, and for every inner object
 * calls its vtable slot 2 (byte +8) - the per-frame Tick/update hook.
 * Slot 2 = per-frame tick is the consistent vtable convention across this
 * codebase (Mobile.h SimulateMobileFrame, Projectile.h AnimateProjectileTick,
 * both "slot 2 +0x08: per-frame animate tick"); DrawActiveObjectRegistry's
 * render pass is the adjacent slot 3 (+0xc). Unlike Draw, this pass has no
 * layer-threshold filter - it ticks every object unconditionally.
 *
 * DROPPED-ARGUMENT FIX: Ghidra rendered `param_1` as `unaff_EBX` - a register
 * it never resolved a source for - and typed the function `void`, so the raw
 * port read EBX uninitialized and faulted on the first list deref. Recovered
 * from the sole call site in GameTick (orig 0x413130): 0x4132a4 does
 * `mov ebx, 0xe9be90` immediately before `call 0x406280` at 0x4132a9, and the
 * intervening 0x50f290 call preserves EBX, so the argument is &DAT_00e9be90 -
 * the first active-object registry (the same one DrawActiveObjectRegistry and
 * the mouse-hit-test family walk). It is called once per tick, on that one
 * registry only (DrawActiveObjectRegistry runs on both).
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-
 * verified. See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"


void TickActiveObjectRegistry(int param_1)

{
  int *piVar1;
  int *piVar2;

  piVar2 = (int *)(*(int **)(param_1 + 4))[7];
  if (piVar2 != *(int **)(param_1 + 4)) {
    do {
      for (piVar1 = (int *)piVar2[4]; piVar1 != piVar2; piVar1 = (int *)piVar1[4]) {
        (**(code **)(*piVar1 + 8))();
      }
      piVar2 = (int *)piVar2[7];
    } while (piVar2 != *(int **)(param_1 + 4));
  }
  return;
}
