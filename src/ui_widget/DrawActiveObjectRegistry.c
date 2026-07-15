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
 *
 * FIXED (2026-07-14): the per-node Draw() dispatch (`(**(code**)(*piVar1
 * + 0xc))()`) dropped "this" entirely - zero args, callee reads garbage
 * off its own object. Confirmed via angr disassembly at 0x4062e0-0x4062e4:
 * `mov eax,[esi]; mov ecx,esi; call [eax+0xc]` - esi (the node, piVar1
 * here) is loaded into ECX immediately before the call, a genuine
 * __thiscall dispatch. Live-reproduced: a jump-to-NULL crash (EIP=0x0,
 * ECX=<node>, *(int*)node==0) once real Button widgets started existing
 * in the active-object registry for the first time this session (past
 * ServerSelect, once the broker handshake and SendSocketData fixes let
 * the client reach further UI). `unaff_BL` is a SEPARATE, still-
 * unresolved dropped register (see the KNOWN BUG note above) - not
 * touched here. */
#include "ghidra_types.h"

typedef void (__thiscall *DrawWidgetFn)(void *thisPtr);

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
          ((DrawWidgetFn)(*(void ***)piVar1)[3])(piVar1);
        }
      }
      else if (999999 < (uint)piVar1[1]) goto joined_r0x004062dd;
      piVar2 = (int *)piVar2[7];
    } while (piVar2 != *(int **)(param_1 + 4));
  }
  return;
}

