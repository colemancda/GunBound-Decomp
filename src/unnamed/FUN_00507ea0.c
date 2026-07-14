/* FUN_00507ea0 - 0x00507ea0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER ARGUMENT (2026-07-14): this function's own entry never
 * touches ECX (confirmed via objdump at 0x507ea0: only `mov eax,[esp+8]` /
 * `mov edx,[esp+4]` before pushing them and calling FUN_0050f060), so an
 * EARLIER session incorrectly concluded it "genuinely takes 2 stack args and
 * no `this`" and left it alone - see WndProc.c's now-corrected header
 * comment. But FUN_0050f060 (the function this one calls) IS __thiscall and
 * DOES need `this` in ECX - and the original's own caller (WndProc, case
 * 0x201) sets `mov ecx,0xe53c40` (g_uiPanelManager) immediately before
 * `call 0x507ea0`, with no ECX-clobbering instruction in between all the way
 * through to FUN_0050f060's own call - i.e. ECX is silently inherited across
 * this whole call chain in the original's straight-line asm. A recompiled
 * C->C call gives no such guarantee (ECX is caller-saved across an ordinary
 * call), so this was a genuine crash (NULL `this` reaching FUN_0050f060,
 * `*(this+4)` deref at param_1+4 with this=0). Promoted to take and forward
 * the panel-manager pointer explicitly - this is the ONLY call site (WndProc
 * case 0x201), so no K&R-empty compatibility declaration is needed.
 */
#include "ghidra_types.h"


char FUN_00507ea0(int uiPanelManager,undefined4 param_1,undefined4 param_2)

{
  char cVar1;

  cVar1 = FUN_0050f060(uiPanelManager,param_1,param_2);
  if (cVar1 == '\0') {
    FUN_00507e30();
  }
  return cVar1;
}

