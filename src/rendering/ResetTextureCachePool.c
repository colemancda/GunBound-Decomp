/* ResetTextureCachePool - 0x004f3ea0 in the original binary.
 *
 * NAMED (batch 35), LIKELY (was FUN_004f3ea0).  Resets the per-frame draw-
 * record pool to its freshly initialised state.  InitTextureCachePool
 * (0x4f3e40) takes record 0 from AllocTextureCacheNode (whose bump index
 * is DAT_00793660, 0x80-byte records, 1024 per block) as the head record
 * DAT_00792190 and zeroes its +0x7c list pointer.  This function writes
 * exactly those two things back - head+0x7c = 0 and the bump index = 1
 * (record 0 stays allocated) - so every record handed out since is
 * released and the list is emptied.  FUN_004f3ee0, run later in the same
 * frame, walks that +0x7c list to flush the queued sprites.  Callers:
 * GameTick calls it twice, each immediately after a successful
 * IDirect3DDevice7::BeginScene (vtable +0x14) and before invoking the
 * state's render virtual (+0x30 / +0x38).  It also forces D3D render state
 * 0x1b (ALPHABLENDENABLE) off through SetRenderState (vtable +0x50) when
 * the shadow flag DAT_00793611 says it is on, and clears that flag; the
 * flush function sets it back to 1 before drawing.  The alpha-blend reset
 * is a side effect, so "DisableAlphaBlend" would have hidden the pool
 * reset.  LIKELY: the +0x7c list is read as a draw queue from
 * FUN_004f3ee0, which is still unnamed.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"
#include <windows.h>

/* STACK-CORRUPTING CALLING-CONVENTION BUG, same class as InitDirectDraw.c/
 * SetupZBuffer.c/GameTick.c: IDirect3DDevice7::SetRenderState is __stdcall;
 * the generic `code()` cast made MSVC treat it as __cdecl and emit a
 * redundant caller-side stack cleanup, drifting ESP for the rest of
 * GameTick's render tail. Fixed via an explicit WINAPI-typed function
 * pointer, matching that established idiom (same typedef as GameTick.c's
 * own D3DSetRenderStateFn). */
typedef HRESULT (WINAPI *D3DSetRenderStateFn)(void *thisPtr, DWORD state, DWORD value);

void ResetTextureCachePool(void)

{
  *(undefined4 *)(DAT_00792190 + 0x7c) = 0;
  DAT_00793660 = 1;
  if (DAT_00793611 != '\0') {
    (*(D3DSetRenderStateFn *)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x1b,0);
  }
  DAT_00793611 = 0;
  return;
}

