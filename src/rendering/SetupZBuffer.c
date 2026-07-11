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
 * The enum match key and result use a STANDALONE DDPIXELFORMAT (zfmt), not a
 * sub-object of a reused DDSURFACEDESC2: MSVC /O2 (FPO) computed
 * &desc.ddpfPixelFormat 8 bytes off from where GetSurfaceDesc had written the
 * format into the same reused local, so the callback compared the wrong dword
 * (a colour-key mask instead of the bit depth) and never matched -> the Z
 * CreateSurface then got a descriptor with no pixel format and faulted.
 *
 * Body is a hand-reconstruction, not a raw Ghidra port; see src/README.md.
 */
#include "ghidra_types.h"
#include <windows.h>

/* DDPIXELFORMAT +0xc is the dwRGBBitCount / dwZBufferBitDepth union; access it
 * by raw offset to avoid the anonymous-union member-name variance. */
#define PF_BITDEPTH(pf) (*(DWORD *)((char *)(pf) + 0xc))

/* Force frame pointers for this function. Under /O2 (FPO) MSVC 7.1 computes the
 * addresses of the large DDSURFACEDESC2 locals inconsistently across the COM
 * calls that adjust ESP (the function also dynamically aligns ESP), so a
 * descriptor filled by GetSurfaceDesc via &desc was read back 8 bytes off via
 * &desc.field elsewhere - the enum matched the wrong dword and CreateSurface
 * got a malformed descriptor. EBP-relative locals are stable, so keep them. */
#pragma optimize("y", off)


bool SetupZBuffer(void)
{
  D3DDEVICEDESC7 devDesc;
  DDSURFACEDESC2 bbDesc;   /* back-buffer descriptor */
  DDSURFACEDESC2 zDesc;    /* Z-buffer descriptor to create */
  DDPIXELFORMAT  zfmt;     /* enum match key in, matched Z format out */
  int hr;

  /* 1. Device caps. Z-buffer-less hidden-surface removal -> no Z-buffer needed. */
  (**(code **)(*g_pD3DDevice7 + 0xc))(g_pD3DDevice7, &devDesc);
  if ((devDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_ZBUFFERLESSHSR) != 0) {
    return true;
  }

  /* 2. Back-buffer descriptor: dimensions + display bit depth. */
  ZeroMemory(&bbDesc, sizeof(bbDesc));
  bbDesc.dwSize = sizeof(bbDesc);          /* 0x7c */
  (**(code **)(*g_pBackBufferSurface + 0x58))(g_pBackBufferSurface, &bbDesc);

  /* 3. Find a Z format. The callback matches zfmt+0xc against each enumerated
   *    format's +0xc; seed it with the display depth, then retry forcing 16-bit
   *    (orig 0x4efa2f). zfmt.dwSize stays 0 until a format is copied in. */
  ZeroMemory(&zfmt, sizeof(zfmt));
  PF_BITDEPTH(&zfmt) = PF_BITDEPTH(&bbDesc.ddpfPixelFormat);
  (**(code **)(*g_pDirect3D7 + 0x18))
      (g_pDirect3D7, &DAT_00f22504, FUN_004ef970, &zfmt);
  if (zfmt.dwSize == 0) {
    ZeroMemory(&zfmt, sizeof(zfmt));
    PF_BITDEPTH(&zfmt) = 0x10;            /* 16-bit depth */
    (**(code **)(*g_pDirect3D7 + 0x18))
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

  hr = (**(code **)(*g_pDirectDraw7 + 0x18))(g_pDirectDraw7, &zDesc, &g_pZBufferSurface, 0);
  if (hr < 0) {
    return false;
  }
  /* 5. Attach the Z-buffer to the back buffer. */
  hr = (**(code **)(*g_pBackBufferSurface + 0xc))(g_pBackBufferSurface, g_pZBufferSurface);
  if (hr < 0) {
    return false;
  }
  /* 6. Bind the back buffer (now with attached Z) as the render target. */
  hr = (**(code **)(*g_pD3DDevice7 + 0x20))(g_pD3DDevice7, g_pBackBufferSurface, 0);
  return hr >= 0;
}
