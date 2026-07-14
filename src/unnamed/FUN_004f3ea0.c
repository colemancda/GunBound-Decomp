/* FUN_004f3ea0 - 0x004f3ea0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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

void FUN_004f3ea0(void)

{
  *(undefined4 *)(DAT_00792190 + 0x7c) = 0;
  DAT_00793660 = 1;
  if (DAT_00793611 != '\0') {
    (*(D3DSetRenderStateFn *)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x1b,0);
  }
  DAT_00793611 = 0;
  return;
}

