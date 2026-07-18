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
 * FIXED (2026-07-17): the dropped `unaff_BL` register - which selects
 * "draw normal (<999999) layers" vs "draw only system (>=999999) layers"
 * - is now the explicit `drawHighPriority` parameter (see the recovery in
 * the function-body comment below). This was the last thing keeping the
 * ServerSelect buttons (and every normal widget) off-screen: GameTick's
 * main draw pass ran with garbage BL and skipped the whole normal band.
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

/* VTABLE-DISPATCH CONVENTION (fixed 2026-07-18): slot 3 is the widget's
 * 0-argument Draw(). It MUST be __fastcall, not __thiscall: ghidra_types.h
 * erases __thiscall unconditionally (it's a C++-only keyword and this tree
 * compiles as C), so a __thiscall pointer here silently became __cdecl -
 * the node got pushed on the stack and ECX was left holding the call-target
 * base (the vtable). Draw()/DrawButtonWidget then ran with `this` == &vtable
 * and read sprite fields out of rdata (no crash, but nothing drew, which is
 * why registered buttons stayed invisible). For a 0-stack-arg method,
 * __fastcall(this) is ABI-identical to __thiscall(this): `this` in ECX,
 * `ret 0`. __fastcall IS honored under real MSVC (see ghidra_types.h). */
typedef void (__fastcall *DrawWidgetFn)(void *thisPtr);

/* DROPPED-REGISTER FIX (2026-07-17): `drawHighPriority` (BL in the
 * original) was read as an uninitialised `unaff_BL` - it selects which
 * priority band to draw. BL=0 draws NORMAL widgets (node priority
 * [node+4] < 999999 = 0xf4240) - this is where every Button lives; BL=1
 * draws the high-priority overlay band (>= 999999). GameTick calls it
 * `xor bl,bl` for the main pass (0x413604) and `mov bl,1` for the overlay
 * pass (0x413938). With BL uninitialised the main pass ran with garbage
 * and skipped the whole normal band, so no button (or any normal widget)
 * ever drew. Promoted to an explicit parameter. */
void DrawActiveObjectRegistry(int param_1, int drawHighPriority)

{
  int *piVar1;
  int *piVar2;

  piVar2 = (int *)(*(int **)(param_1 + 4))[7];
  if (piVar2 != *(int **)(param_1 + 4)) {
    do {
      piVar1 = (int *)piVar2[4];
      if (drawHighPriority == 0) {
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

