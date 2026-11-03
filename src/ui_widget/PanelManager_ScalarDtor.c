/* PanelManager_ScalarDtor - 0x00507e10 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NAMED 2026-10-31 (was FUN_00507e10). Slot 0 of vtable 0x557cfc, the
 * one g_uiPanelManager's constructor 0x507dc0 stores (globals_sized.c's
 * PTR_FUN_00557cfc). The body is MSVC's scalar deleting destructor
 * shape: `mov esi,ecx`, call the destructor (here the 0x40d150 thunk to
 * PanelManager_BaseDestructor, 0x507e13), `test byte [esp+8],1` and free
 * `this` when set, return `this`, `ret 4`. "ScalarDtor" follows
 * DropCaseProjectile_ScalarDtor and the other *_ScalarDtor names; the
 * base vtable 0x557f80's own slot 0 is PanelManager_BaseScalarDtor.
 *
 * FIX (2026-11-03): the call to PanelManager_BaseDestructorThunk passed
 * nothing. 0x507e11 `mov esi,ecx` leaves ECX = `this`, and 0x507e13
 * `call 0x40d150` (a bare `jmp 0x50ee00`) reaches the destructor with it;
 * 0x50ee17 `mov ebx,ecx` is its first use. Both ports are __fastcall
 * (this in ECX), so the call now passes `this`, and the K&R-empty
 * prototype that hid the gap is now a full one.
 */
#include "ghidra_types.h"


void * __thiscall PanelManager_ScalarDtor(void *param_1,int param_2)

{
  PanelManager_BaseDestructorThunk((undefined4 *)param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

