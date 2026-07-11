/* SetupZBuffer - 0x004ef9a0 in the original binary.
 *
 * Attaches a Z-buffer to the Direct3D7 back buffer and binds it as the render
 * target. Reconstructed (like InitDirectDraw) from the original disassembly
 * because Ghidra emitted the DirectDraw/Direct3D COM calls as argument-less
 * `(**(code**)(*iface + off))()` and scattered the surface/caps descriptors
 * across disconnected stack locals. All six COM calls are rewritten with
 * explicit arguments and contiguous structs; argument order and descriptor
 * field values were recovered from orig 0x4ef9a0-0x4efa9e.
 *
 * Flow (all COM calls are raw vtable dispatch, matching InitDirectDraw's style):
 *   1. IDirect3DDevice7::GetCaps  (vtbl+0xc)  -> if the device advertises
 *      D3DPRASTERCAPS_ZBUFFERLESSHSR it needs no Z-buffer; succeed early.
 *   2. IDirectDrawSurface7::GetSurfaceDesc (vtbl+0x58) on the back buffer -
 *      recover its width/height and display bit depth.
 *   3. IDirect3D7::EnumZBufferFormats (vtbl+0x18): FUN_004ef970 (the callback)
 *      copies the first Z format whose bit depth (DDPIXELFORMAT +0xc) matches
 *      the context's +0xc into the context. Try the display depth, then 16-bit.
 *   4. IDirectDraw7::CreateSurface (vtbl+0x18) -> the Z-buffer surface.
 *   5. IDirectDrawSurface7::AddAttachedSurface (vtbl+0xc) -> attach to back buffer.
 *   6. IDirect3DDevice7::SetRenderTarget (vtbl+0x20) -> bind. Return HR >= 0.
 *
 * Two bugs had to be fixed to get this far, both verified against a live
 * GunBound.gme via tools/msvc-env/orig_launcher_susp.c + WINEDEBUG=+ddraw:
 *
 *  - The enum match key and result use a STANDALONE DDPIXELFORMAT (zfmt), not
 *    a sub-object of a reused DDSURFACEDESC2: MSVC /O2 (FPO) computed
 *    &desc.ddpfPixelFormat 8 bytes off from where GetSurfaceDesc had written
 *    the format into the same reused local, so the callback compared the
 *    wrong dword and never matched.
 *
 *  - EVERY vtable call below is dispatched through an EXPLICIT __stdcall
 *    function-pointer cast, not the generic `code` (K&R/unspecified-args)
 *    type used elsewhere in raw ports. `code()` has no prototype, so MSVC
 *    defaults it to __cdecl and emits a caller-side `add esp, N` after each
 *    call to pop the arguments *itself* pushed - but every one of these is a
 *    real COM vtable method, which is __stdcall and ALREADY pops its own
 *    args via `ret N` before returning. That's a double stack cleanup: each
 *    call leaves ESP N bytes higher than it should be, i.e. the local-
 *    variable "slack" between ESP and the saved EBP/return address shrinks
 *    a little more per call. This function makes six such calls in a row
 *    (more than most other raw ports), and by the sixth (SetRenderTarget)
 *    the accumulated drift was enough for the callee's own prologue to land
 *    its writes on our saved EBP, corrupting it - confirmed live: a hardware
 *    watchpoint on the saved-EBP stack slot fired from *inside ddraw.dll*
 *    during the SetRenderTarget call. Giving every call site its real
 *    prototype makes MSVC skip the redundant caller-side cleanup entirely.
 *
 * Body is a hand-reconstruction, not a raw Ghidra port; see src/README.md.
 */
#include "ghidra_types.h"
#include <windows.h>

/* DDPIXELFORMAT +0xc is the dwRGBBitCount / dwZBufferBitDepth union; access it
 * by raw offset to avoid the anonymous-union member-name variance. */
#define PF_BITDEPTH(pf) (*(DWORD *)((char *)(pf) + 0xc))

typedef HRESULT (WINAPI *GetCapsFn)(void *, D3DDEVICEDESC7 *);
typedef HRESULT (WINAPI *GetSurfaceDescFn)(void *, DDSURFACEDESC2 *);
typedef HRESULT (WINAPI *EnumZBufferFormatsFn)(void *, REFCLSID, LPD3DENUMPIXELFORMATSCALLBACK, LPVOID);
typedef HRESULT (WINAPI *CreateSurfaceFn)(void *, DDSURFACEDESC2 *, void **, IUnknown *);
typedef HRESULT (WINAPI *AddAttachedSurfaceFn)(void *, void *);
typedef HRESULT (WINAPI *SetRenderTargetFn)(void *, void *, DWORD);


bool SetupZBuffer(void)
{
  D3DDEVICEDESC7 devDesc;
  DDSURFACEDESC2 bbDesc;   /* back-buffer descriptor */
  DDSURFACEDESC2 zDesc;    /* Z-buffer descriptor to create */
  DDPIXELFORMAT  zfmt;     /* enum match key in, matched Z format out */
  int hr;

  /* 1. Device caps. Z-buffer-less hidden-surface removal -> no Z-buffer needed. */
  ((GetCapsFn)(*(void ***)g_pD3DDevice7)[3])(g_pD3DDevice7, &devDesc);
  if ((devDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_ZBUFFERLESSHSR) != 0) {
    return true;
  }

  /* 2. Back-buffer descriptor: dimensions + display bit depth. */
  ZeroMemory(&bbDesc, sizeof(bbDesc));
  bbDesc.dwSize = sizeof(bbDesc);          /* 0x7c */
  ((GetSurfaceDescFn)(*(void ***)g_pBackBufferSurface)[0x16])(g_pBackBufferSurface, &bbDesc);

  /* 3. Find a Z format. The callback matches zfmt+0xc against each enumerated
   *    format's +0xc; seed it with the display depth, then retry forcing 16-bit
   *    (orig 0x4efa2f). zfmt.dwSize stays 0 until a format is copied in. */
  ZeroMemory(&zfmt, sizeof(zfmt));
  PF_BITDEPTH(&zfmt) = PF_BITDEPTH(&bbDesc.ddpfPixelFormat);
  ((EnumZBufferFormatsFn)(*(void ***)g_pDirect3D7)[6])
      (g_pDirect3D7, &DAT_00f22504, FUN_004ef970, &zfmt);
  if (zfmt.dwSize == 0) {
    ZeroMemory(&zfmt, sizeof(zfmt));
    PF_BITDEPTH(&zfmt) = 0x10;            /* 16-bit depth */
    ((EnumZBufferFormatsFn)(*(void ***)g_pDirect3D7)[6])
        (g_pDirect3D7, &DAT_00f22504, FUN_004ef970, &zfmt);
    if (zfmt.dwSize == 0) {
      return false;
    }
  }

  /* 4. Create the Z-buffer sized to the back buffer, using the matched format. */
  ZeroMemory(&zDesc, sizeof(zDesc));
  zDesc.dwSize = sizeof(zDesc);
  zDesc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT; /* 0x1007 */
  zDesc.dwWidth = bbDesc.dwWidth;
  zDesc.dwHeight = bbDesc.dwHeight;
  zDesc.ddpfPixelFormat = zfmt;
  zDesc.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_VIDEOMEMORY;           /* 0x24000 */

  hr = ((CreateSurfaceFn)(*(void ***)g_pDirectDraw7)[6])
           (g_pDirectDraw7, &zDesc, (void **)&g_pZBufferSurface, 0);
  if (hr < 0) {
    return false;
  }
  /* 5. Attach the Z-buffer to the back buffer. */
  hr = ((AddAttachedSurfaceFn)(*(void ***)g_pBackBufferSurface)[3])
           (g_pBackBufferSurface, g_pZBufferSurface);
  if (hr < 0) {
    return false;
  }
  /* 6. Bind the back buffer (now with attached Z) as the render target. */
  hr = ((SetRenderTargetFn)(*(void ***)g_pD3DDevice7)[8])
           (g_pD3DDevice7, g_pBackBufferSurface, 0);
  return hr >= 0;
}
