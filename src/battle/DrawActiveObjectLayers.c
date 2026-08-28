/* DrawActiveObjectLayers - 0x00450860 in the original binary.
 *
 * Draws every object in an active-object registry, layer by layer.
 *
 * NAMED 2026-08-27.  It is the twin of TickActiveObjectLayers (0x4507d0):
 * the same walk over the same structure -- an outer list of layer nodes
 * chained through +0x1c, each holding an inner object chain through +0x10
 * with +0x15 marking that chain's terminator -- differing only in the
 * virtual it dispatches.  The tick takes slot 2 (+8); this takes slot 3
 * (+0xc), `mov eax,[esi]` / `mov ecx,esi` / `call [eax+0xc]` at
 * 0x450880-0x450884.
 *
 * Slot 3 is the render half of that vtable convention, and the census says
 * so rather than the body: in docs/vtable_census.txt 17 game-class vtables
 * carry RenderMobile at slot 3, beside RenderJewel, RenderTornadoHazard,
 * RenderLightningHazard, RenderFirewallHazard and DrawSuperFlameEffect --
 * the same classes whose slot 2 carries AnimateProjectileTick (27) and
 * SimulateMobileFrame (17), the two names TickActiveObjectLayers rests on.
 * DrawActiveObjectRegistry (0x4062b0) already reads slot 3 as `Draw()` on
 * the widget side.
 *
 * The callers agree and none of them is a tick: three sites in
 * DrawStageDecorationParallax and one in
 * State09_ReadyRoom_RenderStatusOverlay.
 *
 * The name completes a 2x2 the tree already draws, Tick/Draw x
 * Registry/Layers.  "Registry" (TickActiveObjectRegistry 0x406280,
 * DrawActiveObjectRegistry 0x4062b0) is the widget registry at
 * g_activeObjectRegistry, and only its Draw half filters layers against the
 * 1000000 threshold; "Layers" is this collection, walked unconditionally.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): unaff_EBX is the active-object
 * LAYER COLLECTION this walks -- the body reads `*(int *)(unaff_EBX + 4)` as
 * the list head and uses it as the loop terminator, exactly as
 * TickActiveObjectLayers (0x4507d0) does.  The two are the same walk over the
 * same structure differing only in the virtual they dispatch: slot 2 (+8) for
 * the tick, slot 3 (+0xc) here, i.e. this is the DRAW half.
 *
 * Two distinct collections across the four sites, and neither needs an
 * ordering assumption:
 *   - State09_ReadyRoom_RenderStatusOverlay passes g_clientContext +
 *     0x6a7f88 (`mov ebx,[0x5b3484]` / `add ebx,0x6a7f88` at 0x4da435), the
 *     same list the weather-hazard spawners and TickActiveObjectLayers name.
 *   - DrawStageDecorationParallax passes param_1 + 0x85c at all THREE of its
 *     sites -- one identical `lea ebx,[ebp + 0x85c]` before each -- so they
 *     share one value and pairing them individually is unnecessary.  EBP is
 *     that function's param_1: `push ebx` / `push ebp` then
 *     `mov ebp,[esp+0xc]` is E+4, and the C's own `*(int *)(param_1 + 8)` and
 *     `*(int *)(param_1 + 0x18)` reads confirm param_1 is the object base.
 */
#include "ghidra_types.h"


void DrawActiveObjectLayers(int regEbx)

{
  char cVar1;
  int *piVar2;
  int unaff_EBX = regEbx;
  int iVar3;
  
  iVar3 = *(int *)(*(int *)(unaff_EBX + 4) + 0x1c);
  if (iVar3 != *(int *)(unaff_EBX + 4)) {
    do {
      piVar2 = *(int **)(iVar3 + 0x10);
      cVar1 = *(char *)((int)piVar2 + 0x15);
      while (cVar1 == '\0') {
        (**(code **)(*piVar2 + 0xc))();
        piVar2 = (int *)piVar2[4];
        cVar1 = *(char *)((int)piVar2 + 0x15);
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
    } while (iVar3 != *(int *)(unaff_EBX + 4));
  }
  return;
}

