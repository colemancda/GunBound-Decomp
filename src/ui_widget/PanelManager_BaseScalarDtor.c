/* PanelManager_BaseScalarDtor - 0x0050ede0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NAMED 2026-10-31 (was FUN_0050ede0). Slot 0 of the base panel-manager
 * vtable 0x557f80, the table PanelManager_BaseDestructor stores. The
 * body is MSVC's scalar deleting destructor shape: `mov esi,ecx`,
 * `call 0x50ee00` (PanelManager_BaseDestructor, directly, 0x50ede3),
 * `test byte [esp+8],1` and free `this` when set, return `this`,
 * `ret 4` - the same sequence as PanelManager_ScalarDtor (0x507e10,
 * slot 0 of the derived 0x557cfc) except that one calls through the
 * 0x40d150 thunk. "Base" marks the base-class member, as in
 * PanelManager_BaseDestructor.
 *
 * FIX (2026-11-03): the call to PanelManager_BaseDestructor passed
 * nothing. 0x50ede1 `mov esi,ecx` copies `this` but leaves ECX intact,
 * and 0x50ede3 `call 0x50ee00` reaches the destructor with ECX = `this`;
 * 0x50ee17 `mov ebx,ecx` is its first use. Its port is __fastcall
 * (this in ECX), so it now gets `this`, and its prototype in functions.h
 * is no longer an empty K&R list that hid the missing argument.
 */
#include "ghidra_types.h"


void * __thiscall PanelManager_BaseScalarDtor(void *param_1,int param_2)

{
  PanelManager_BaseDestructor((undefined4 *)param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

