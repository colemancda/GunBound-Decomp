/* CInputDevice_BaseDestructor - 0x004ee1f0 in the original binary.
 *
 * Renamed with confidence: this is the base destructor (poisons `this`'s
 * vtable pointer, no other cleanup - same idiom as CGameState_
 * BaseDestructor.c) for the DirectInput device-wrapper class that backs
 * both g_keyboardDeviceTimerBlock (0xe52810) and g_mouseDeviceTimerBlock
 * (0xe53698) - see include/globals.h's "DirectInput device singletons"
 * comment. Confirmed via a whole-binary scan for this function's own
 * address as a vtable-slot DWORD literal: it's slot 0 of two adjacent
 * 10-entry vtables (0x55745c/0x557484) whose slot 1 is FUN_004edd70
 * ("DirectInput keyboard-device acquisition") and FUN_004ee270
 * ("DirectInput mouse-device acquisition") respectively - and,
 * independently, two compiler-generated global-object destructor thunks
 * in the excluded msvc_crt_atl/ tree (FUN_00543260/FUN_00543270, kept
 * as reference only per that directory's README) hard-code `mov
 * ecx,0xe52810`/`mov ecx,0xe53698` immediately before tail-jumping into
 * this exact function - i.e. these are literally the atexit cleanup
 * thunks for the keyboard/mouse singletons.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output otherwise, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 */
#include "ghidra_types.h"


void __fastcall CInputDevice_BaseDestructor(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_00557434;
  return;
}
