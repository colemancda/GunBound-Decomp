/* PresentFrame - 0x004f0070 in the original binary.
 *
 * Flips the primary surface: (re)attach the clipper, Blt the back buffer
 * to the primary surface (DDBLT_WAIT), and on DDERR_SURFACELOST restore
 * all three surfaces and rebind the render target before retrying.
 *
 * Every COM vtable call was originally emitted through the generic
 * `code**` cast, which - like InitDirectDraw.c and SetupZBuffer.c before
 * this fix - makes MSVC treat the call as __cdecl and add a redundant
 * caller-side stack cleanup after each call, since the real methods
 * (IDirectDrawSurface7::SetClipper/Blt/Restore, IDirect3DDevice7::
 * SetRenderTarget) are __stdcall and already pop their own args. This
 * function makes 6 such calls on the SURFACELOST path - the same
 * accumulating-drift hazard documented in SetupZBuffer.c's header - so
 * every call site is now cast through an explicit WINAPI-typed function
 * pointer, matching that file's established idiom. No argument values or
 * call order changed; confirmed against orig 0x4f0070-0x4f00f5, which
 * matches this file's existing arguments/branch structure exactly.
 */
#include "ghidra_types.h"
#include <windows.h>

typedef HRESULT (WINAPI *SetClipperFn)(void *, void *);
typedef HRESULT (WINAPI *BltFn)(void *, LPRECT, void *, LPRECT, DWORD, LPDDBLTFX);
typedef HRESULT (WINAPI *RestoreFn)(void *);
typedef HRESULT (WINAPI *SetRenderTargetFn)(void *, void *, DWORD);


bool PresentFrame(void)

{
  int iVar1;

  ((SetClipperFn)(*(void ***)g_pPrimarySurface)[0x1c])(g_pPrimarySurface,g_pClipper);
  iVar1 = ((BltFn)(*(void ***)g_pPrimarySurface)[5])
                    (g_pPrimarySurface,(LPRECT)&DAT_006773b4,g_pBackBufferSurface,0,0x1000000,0);
  if (iVar1 == -0x7789fe3e) {
    ((RestoreFn)(*(void ***)g_pPrimarySurface)[0x1b])(g_pPrimarySurface);
    ((RestoreFn)(*(void ***)g_pBackBufferSurface)[0x1b])(g_pBackBufferSurface);
    ((RestoreFn)(*(void ***)g_pZBufferSurface)[0x1b])(g_pZBufferSurface);
    iVar1 = ((SetRenderTargetFn)(*(void ***)g_pD3DDevice7)[8])(g_pD3DDevice7,g_pBackBufferSurface,0);
    if (iVar1 < 0) {
      return false;
    }
  }
  return iVar1 == 0;
}

