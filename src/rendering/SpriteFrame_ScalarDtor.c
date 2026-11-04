/* SpriteFrame_ScalarDtor - 0x004f14c0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004f14c0 mean this function.)
 *
 * NAMED (2026-11-04), CERTAIN. Slot 0 of the vtable at 0x557524, whose
 * .data word reads 0x4f14c0 and which docs/vtable_census.txt shows with 8
 * installs - the stamps made by the 0x50-byte sprite-frame builders
 * (LoadSpriteSet, LoadAvatarSprites, ComposeAvatarSprites and the other
 * loaders DestroySpriteFrame's header lists). The body is the compiler's
 * scalar-deleting-destructor shape: call DestroySpriteFrame (0x4f14e0,
 * already named) with this in ESI, release the object with the CRT free
 * (call at 0x4f14d0) when bit 0 of the flags word on the stack is set,
 * return this, ret 4. The registry teardown loops in the OnExit handlers
 * of states 1, 2, 3, 5, 6, 7, 9 and 10 reach it through slot 0 of each
 * node. Named after the sibling PanelManager_ScalarDtor /
 * KnightFlameShot_ScalarDtor.
 *
 * DROPPED-`this` FIX (2026-08-06): the call to DestroySpriteFrame() below had
 * dropped its `this` argument entirely - the original passes `this` in
 * ESI (`mov esi,ecx` then a bare `call`, a genuine __thiscall pair; see
 * DestroySpriteFrame.c for the full writeup and live-debug evidence). Restored
 * as an explicit parameter. */
#include "ghidra_types.h"


void * __thiscall SpriteFrame_ScalarDtor(void *param_1,int param_2)

{
  DestroySpriteFrame(param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

