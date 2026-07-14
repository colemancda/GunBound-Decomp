/* FUN_004edaa0 - 0x004edaa0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"
#include <windows.h>

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* STACK-CORRUPTING CALLING-CONVENTION BUG, same class as InitDirectDraw.c/
 * SetupZBuffer.c/GameTick.c: the vtable call below is IDirect3DDevice7::
 * DrawPrimitive(D3DPRIMITIVETYPE,DWORD,LPVOID,DWORD,DWORD), a __stdcall COM
 * method. The generic `code()` cast made MSVC treat it as __cdecl and emit a
 * redundant caller-side `add esp,0x14` after the call (the callee already
 * popped its own args), drifting ESP for the remainder of the function/caller
 * chain - this is GameTick's render tail, so the drift corrupts whatever the
 * caller does next. Fixed via an explicit WINAPI-typed function pointer,
 * matching that established idiom. */
typedef HRESULT (WINAPI *DrawPrimitiveFn)(void *, DWORD, DWORD, LPVOID, DWORD, DWORD);

/* `color` (the vertex diffuse-color field, applied to all 3 quad corners)
 * was read as an uninitialized `in_EAX` local - Ghidra dropped it as a
 * 7th, register-passed (EAX) argument. Recovered via objdump at both of
 * GameTick.c's call sites (orig 0x41374f/0x413784): `mov eax,0xff000000`
 * immediately before each call, no intervening EAX write. */
void FUN_004edaa0(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,undefined4 color)

{
  DAT_00ea0e28 = (float)param_1 * _DAT_00557fc0 * _DAT_00588f50;
  DAT_00ea0e2c = (float)param_2 * _DAT_00557fbc * _DAT_00588f54;
  _DAT_00ea0e4c = (float)param_3 * _DAT_00557fc0 * _DAT_00588f50;
  _DAT_00ea0e50 = (float)param_4 * _DAT_00557fbc * _DAT_00588f54;
  DAT_00ea0e70 = (float)param_5 * _DAT_00557fc0 * _DAT_00588f50;
  DAT_00ea0e74 = (float)param_6 * _DAT_00557fbc * _DAT_00588f54;
  _DAT_00ea0e38 = color;
  _DAT_00ea0e5c = color;
  _DAT_00ea0e80 = color;
  (*(DrawPrimitiveFn *)(*g_pD3DDevice7 + 100))(g_pD3DDevice7,6,0x244,&DAT_00ea0e28,3,1);
  return;
}

