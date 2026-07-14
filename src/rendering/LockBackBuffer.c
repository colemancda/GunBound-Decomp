/* LockBackBuffer - 0x004f02c0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 *
 * The vtable call at offset 100 (0x64) is IDirectDrawSurface7::Lock,
 * a __stdcall COM method (HRESULT Lock(LPRECT,LPDDSURFACEDESC2,DWORD,
 * HANDLE)). Ghidra's generic `code()` cast defaults to __cdecl, which
 * makes the caller emit a redundant `add esp,0x14` after the call even
 * though the __stdcall callee already popped its own args - shifting
 * ESP for the rest of the function. See InitDirectDraw.c's header
 * comment / SetupZBuffer.c for the confirmed writeup of this bug
 * class. Fixed by casting through an explicit WINAPI/__stdcall
 * typedef instead, matching the established idiom.
 */
#include "ghidra_types.h"
#include <windows.h>
#include <string.h>

typedef HRESULT (WINAPI *LockFn)(void *, LPRECT, LPDDSURFACEDESC2, DWORD, HANDLE);

/* STACK-OVERFLOW FIX: Ghidra recovered only three of this frame's locals
 * (uStack_8c / local_88[4] / uStack_78 = 0x18 bytes), but the zero-fill loop
 * writes 0x1f dwords = 0x7c bytes - the size of the DDSURFACEDESC2 that
 * IDirectDrawSurface7::Lock fills. The original reserves a 0x84-byte frame
 * for it (orig 0x4f02c6 `sub esp,0x84`); the under-sized port buffer let the
 * fill and Lock clobber the return address and this function's own incoming
 * param_1/param_2, so the success-path `*param_1 = ...` faulted writing
 * through a smashed (NULL) pointer. Replaced with a correctly-sized desc
 * buffer. Field offsets read back are taken verbatim from the original's tail
 * (orig 0x4f0303/0x4f030a): param_1 <- desc+0x24 (lpSurface), param_2 <-
 * desc+0x10 (lPitch) - GameTick consumes them as the locked surface pointer
 * (checked != 0) and its pitch (halved to 16bpp pixels). */

undefined4 LockBackBuffer(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  undefined1 descBuf [0x7c];   /* DDSURFACEDESC2 */

  memset(descBuf, 0, sizeof(descBuf));
  *(undefined4 *)descBuf = 0x7c;   /* dwSize */
  iVar1 = (*(LockFn *)(*g_pBackBufferSurface + 100))
            (g_pBackBufferSurface,0,(LPDDSURFACEDESC2)descBuf,0,0);
  if (iVar1 < 0) {
    return 0;
  }
  *param_1 = *(undefined4 *)(descBuf + 0x24);   /* lpSurface */
  *param_2 = *(undefined4 *)(descBuf + 0x10);   /* lPitch */
  return 1;
}

