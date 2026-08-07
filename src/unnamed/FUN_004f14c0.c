/* FUN_004f14c0 - 0x004f14c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-`this` FIX (2026-08-06): the call to DestroySpriteFrame() below had
 * dropped its `this` argument entirely - the original passes `this` in
 * ESI (`mov esi,ecx` then a bare `call`, a genuine __thiscall pair; see
 * DestroySpriteFrame.c for the full writeup and live-debug evidence). Restored
 * as an explicit parameter. */
#include "ghidra_types.h"


void * __thiscall FUN_004f14c0(void *param_1,int param_2)

{
  DestroySpriteFrame(param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

