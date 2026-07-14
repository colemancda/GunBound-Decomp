/* DrawActiveObjectRegistry - 0x004062b0 in the original binary.
 *
 * PROMOTED (2026-07-13): walks `param_1` (one of the two active-object
 * registries, DAT_00e9be90/DAT_00e9c0fc) outer (layer) list, and for
 * layers whose own +4 "layer" field is <= 999999 (see
 * HandleActiveObjectMouseDown.c's note on that same 1000000 threshold),
 * calls every inner object's vtable slot 3 - `Draw()` (CButtonWidget.h) -
 * i.e. this is the registry's per-frame render pass. Called twice per
 * tick from GameTick.c (once per registry), both unconditionally and
 * again inside a state-specific branch at LAB_00413933.
 *
 * KNOWN BUG, NOT FIXED HERE: `unaff_BL` is a genuinely dropped register
 * (Ghidra never resolved a source for it) that selects between "draw
 * normal (<=999999) layers" and "draw only system (>999999) layers" -
 * every known call site (GameTick.c's four) calls this with zero
 * explicit arguments, so BL is READ UNINITIALIZED here; behavior is
 * whatever garbage happens to sit in BL at call time. Needs the same
 * per-call-site disassembly trace already done for
 * HandleActiveObjectMouseDown/Up's shared 1000000 threshold before this
 * can be promoted further - out of scope for this rename pass.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-
 * verified. See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"


void DrawActiveObjectRegistry(int param_1)

{
  int *piVar1;
  char unaff_BL;
  int *piVar2;
  
  piVar2 = (int *)(*(int **)(param_1 + 4))[7];
  if (piVar2 != *(int **)(param_1 + 4)) {
    do {
      piVar1 = (int *)piVar2[4];
      if (unaff_BL == '\0') {
        if (999999 < (uint)piVar1[1]) {
          return;
        }
joined_r0x004062dd:
        for (; piVar1 != piVar2; piVar1 = (int *)piVar1[4]) {
          (**(code **)(*piVar1 + 0xc))();
        }
      }
      else if (999999 < (uint)piVar1[1]) goto joined_r0x004062dd;
      piVar2 = (int *)piVar2[7];
    } while (piVar2 != *(int **)(param_1 + 4));
  }
  return;
}

