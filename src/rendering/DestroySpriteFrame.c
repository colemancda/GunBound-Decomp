/* DestroySpriteFrame - 0x004f14e0 in the original binary (was FUN_004f14e0).
 *
 * The sprite-frame destructor: releases the two lazily-allocated buffers
 * a frame owns and resets its vtable pointer. NAMED (2026-08-06).
 *
 * The object is the 0x50-byte sprite frame built by every sprite-loading
 * path - LoadSpriteSet (one per frame in a set), FUN_004f18c0,
 * FUN_004f1a50, LoadAvatarSprites and ComposeAvatarSprites all
 * `operator_new(0x50)` it and stamp slot 0 with `&PTR_FUN_00557524`.
 * ReadSpriteFrameRecord fills it, and the two pointers freed below are
 * exactly the buffers it allocates: **+0x34 the pixel buffer** and
 * **+0x38 the mask buffer** (see that file, which documents both by
 * name). Both are zeroed at construction and NULL-checked here, which is
 * why a frame that never got as far as decoding still destroys cleanly.
 *
 * The vtable is written twice on purpose - that is the standard MSVC
 * destructor shape, not a bug: slot 0 is set to this class's own vtable
 * on entry, then to the base-class sentinel `PTR_LAB_0055752c` on exit
 * (the inlined base destructor; that same sentinel appears at the end of
 * ~10 other destructors in this tree). `FUN_004f14c0` is the matching
 * scalar-deleting destructor - it calls this, then `_free`s the object
 * itself when its flag bit is set.
 *
 * DROPPED-`this` FIX (2026-08-06): Ghidra's `unaff_ESI` marks a register
 * read without any assignment in this function - the AVATAR-click crash
 * chain traced (live, via winedbg breakpoint logging every call through
 * State03_GameRoomList_OnExit's dtor-loop) to this exact function. The
 * original (verified via angr disasm of orig/GunBound.gme) passes `this`
 * in ESI: FUN_004f14c0 does `mov esi,ecx` then `call DestroySpriteFrame`
 * with no further setup - a genuine __thiscall pair, `this` threaded through
 * ESI across the call. Our port dropped that argument entirely
 * (`DestroySpriteFrame();`, zero args) - `unaff_ESI` read whatever garbage
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


void DestroySpriteFrame(void *param_1)

{
  undefined4 *puVar1 = (undefined4 *)param_1;

  *puVar1 = &PTR_FUN_00557524;          /* this class's own vtable */
  if ((void *)puVar1[0xd] != (void *)0x0) {   /* +0x34: pixel buffer */
    _free((void *)puVar1[0xd]);
  }
  puVar1[0xd] = 0;
  if ((void *)puVar1[0xe] != (void *)0x0) {   /* +0x38: mask buffer */
    _free((void *)puVar1[0xe]);
  }
  puVar1[0xe] = 0;
  *puVar1 = &PTR_LAB_0055752c;          /* inlined base dtor's vtable */
  return;
}

