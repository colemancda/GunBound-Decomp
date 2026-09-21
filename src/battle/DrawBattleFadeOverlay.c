/* DrawBattleFadeOverlay - 0x004edb50 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NAMED (2026-09-21). Its sole caller (State11_InBattle_Render.c)
 * builds param_1 (`uBattleFadeAlpha`) from a per-battle-state fade
 * value - state 1 ramps DAT_005f376c up, state 6 ramps it down, any
 * other state uses the fixed default 0xc0000000 - packed into the top
 * byte of an ARGB colour, and passes it here alongside a fixed 0x31f x
 * 0x257 rectangle. This writes a 4-vertex D3DFVF quad (XYZRHW +
 * diffuse) at DAT_00ea0e28.. and issues
 * `IDirect3DDevice7::DrawPrimitive` (vtable slot 100,
 * D3DPT_TRIANGLEFAN) over it - i.e. it draws the full-screen alpha
 * overlay used for the battle-state fade in/out.
 *
 * SIGNATURE FIX (2026-09-21, no-prototype sweep). Ghidra's
 * `__fastcall FUN_004edb50(undefined4 param_1,int param_2,...)` was
 * wrong in TWO ways at once, on the FUN_0051b667 model (dfaf3f76):
 * `param_1` is a phantom - never read anywhere in the body - while the
 * real first value, EAX, was dropped into an unnamed `in_EAX` local
 * instead of being a formal parameter. Evidence: the entry reads
 * `[esp+4]`/`[esp+8]`/`[esp+0xc]` directly (no ECX capture at all,
 * ruling out real fastcall/thiscall) while EDX is used immediately
 * without ever being set within the function (0x4edb58 `add ecx,edx`,
 * i.e. a genuine but unmodelled register argument), and EAX is likewise
 * read (0x4edb92 first use) without ever being set - both are real
 * caller-supplied values, not ABI artifacts. The epilogue is a bare
 * `ret` (0x4edc07, no operand) - caller-cleaned, i.e. plain cdecl, not
 * fastcall. Renumbered: old param_2 (real, via EDX) is the new
 * param_2; old param_3/param_4/param_5 (real, the 3 stack args) keep
 * their names; old phantom param_1 is dropped and EAX is promoted to
 * the new leading param_1 (was `in_EAX`). The sole caller
 * (State11_InBattle_Render.c) previously called this argless; see its
 * own header note for the register reconstruction.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void DrawBattleFadeOverlay(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  DAT_00ea0e28 = (float)param_3 * _DAT_00557fc0 * _DAT_00588f50;
  DAT_00ea0e2c = (float)param_4 * _DAT_00557fbc * _DAT_00588f54;
  _DAT_00ea0e4c = (float)(param_3 + param_2) * _DAT_00557fc0 * _DAT_00588f50;
  DAT_00ea0e74 = (float)(param_4 + param_5) * _DAT_00557fbc * _DAT_00588f54;
  _DAT_00ea0e38 = param_1;
  _DAT_00ea0e50 = DAT_00ea0e2c;
  _DAT_00ea0e5c = param_1;
  DAT_00ea0e70 = _DAT_00ea0e4c;
  _DAT_00ea0e80 = param_1;
  _DAT_00ea0e94 = DAT_00ea0e28;
  _DAT_00ea0e98 = DAT_00ea0e74;
  _DAT_00ea0ea4 = param_1;
  (**(code **)(*g_pD3DDevice7 + 100))(g_pD3DDevice7,6,0x244,&DAT_00ea0e28,4,1);
  return;
}

