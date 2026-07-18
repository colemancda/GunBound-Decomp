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

/* VTABLE-DISPATCH CONVENTION (fixed 2026-07-18): slot 2 is the widget's
 * 0-argument per-frame Tick(). The raw `(**(code**)(*piVar1+8))()` cast is
 * __cdecl with NO args - it drops `this` entirely, so a real C++ widget's
 * Tick (e.g. CButtonWidget::Tick -> AdvanceSpriteAnimation) ran on whatever
 * was left in ECX instead of the node, and never advanced the button's own
 * sprite-frame index (+0x30) - leaving it uninitialised garbage so
 * DrawButtonWidget's `frame >= 0` / FindSpriteFrame gates failed and the
 * flat ServerSelect buttons (EXIT/BUDDY/SERVER) drew nothing. The original
 * (0x406299) is `mov ecx,esi` / `call [eax+8]` - `this` in ECX. Since the
 * callee is a genuine C++ method, dispatch via __fastcall(this) (ABI-
 * identical to __thiscall for a 0-arg method; __fastcall is honored under
 * real MSVC, __thiscall would be erased - see DrawActiveObjectRegistry.c). */
typedef void (__fastcall *TickWidgetFn)(void *thisPtr);

void TickActiveObjectRegistry(int param_1)

{
  int *piVar1;
  int *piVar2;

  piVar2 = (int *)(*(int **)(param_1 + 4))[7];
  if (piVar2 != *(int **)(param_1 + 4)) {
    do {
      for (piVar1 = (int *)piVar2[4]; piVar1 != piVar2; piVar1 = (int *)piVar1[4]) {
        ((TickWidgetFn)(*(void ***)piVar1)[2])(piVar1);
      }
      piVar2 = (int *)piVar2[7];
    } while (piVar2 != *(int **)(param_1 + 4));
  }
  return;
}
