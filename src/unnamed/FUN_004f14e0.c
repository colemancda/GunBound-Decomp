/* FUN_004f14e0 - 0x004f14e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-`this` FIX (2026-08-06): Ghidra's `unaff_ESI` marks a register
 * read without any assignment in this function - the AVATAR-click crash
 * chain traced (live, via winedbg breakpoint logging every call through
 * State03_GameRoomList_OnExit's dtor-loop) to this exact function. The
 * original (verified via angr disasm of orig/GunBound.gme) passes `this`
 * in ESI: FUN_004f14c0 does `mov esi,ecx` then `call FUN_004f14e0` with
 * no further setup - a genuine __thiscall pair, `this` threaded through
 * ESI across the call. Our port dropped that argument entirely
 * (`FUN_004f14e0();`, zero args) - `unaff_ESI` read whatever garbage
 * MSVC's register allocator happened to leave in ESI at that program
 * point instead, and `*unaff_ESI = &PTR_FUN_00557524` / `*unaff_ESI =
 * &PTR_LAB_0055752c` (this function's own vtable-reset writes) went
 * through that garbage pointer. Confirmed the corruption's exact target:
 * a live breakpoint at the dtor-loop's `call dword ptr [ecx]` (ecx =
 * &PTR_FUN_00557524, the shared destructor-vtable slot, 0x490110 in the
 * 2026-07-31 build) showed the slot's contents flip from the correct
 * 0x46db00 (FUN_004f14c0's own linked address) to 0x60cdfc - the linked
 * address of `_PTR_LAB_0055752c` - between the first and second call in
 * the loop: this function's stray write landed exactly on the shared
 * vtable slot's own storage, not on the intended (dropped) object. Fixed
 * by recovering `this` as a real parameter, passed explicitly from
 * FUN_004f14c0 (see that file). */
#include "ghidra_types.h"


void FUN_004f14e0(void *param_1)

{
  undefined4 *puVar1 = (undefined4 *)param_1;

  *puVar1 = &PTR_FUN_00557524;
  if ((void *)puVar1[0xd] != (void *)0x0) {
    _free((void *)puVar1[0xd]);
  }
  puVar1[0xd] = 0;
  if ((void *)puVar1[0xe] != (void *)0x0) {
    _free((void *)puVar1[0xe]);
  }
  puVar1[0xe] = 0;
  *puVar1 = &PTR_LAB_0055752c;
  return;
}

