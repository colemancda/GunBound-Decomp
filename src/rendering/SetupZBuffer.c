/* SetupZBuffer - 0x004ef9a0 in the original binary.
 *
 * Attaches a Z-buffer to the Direct3D7 back buffer and binds it as the render
 * target. Reconstructed (like InitDirectDraw) from the original disassembly
 * because Ghidra emitted the DirectDraw/Direct3D COM calls as argument-less
 * `(**(code**)(*iface + off))()` and scattered the surface/caps descriptors
 * across disconnected stack locals (piStack_*, auStack_130, aiStack_140). Against
 * native ddraw that faults: the vtable methods read uninitialised stack for
 * their args and the CreateSurface descriptor is malformed. All six COM calls
 * are rewritten with explicit arguments and contiguous structs; argument order
 * and descriptor field values were recovered from orig 0x4ef9a0-0x4efa9e.
 *
 * Flow (all COM calls are raw vtable dispatch, matching InitDirectDraw's style):
 *   1. IDirect3DDevice7::GetCaps  (vtbl+0xc)  -> if the device advertises
 *      D3DPRASTERCAPS_ZBUFFERLESSHSR it needs no Z-buffer; succeed early.
 *   2. IDirectDrawSurface7::GetSurfaceDesc (vtbl+0x58) on the back buffer -
 *      the Z-buffer reuses its width/height AND its pixel-format dwRGBBitCount
 *      is left in place as the enum match key (only dwSize is cleared).
 *   3. IDirect3D7::EnumZBufferFormats (vtbl+0x18): FUN_004ef970 (the callback)
 *      copies the first format whose bit-depth matches into ddpfPixelFormat.
 *      If none match the display depth, retry forcing 16-bit; else fail.
 *   4. IDirectDraw7::CreateSurface (vtbl+0x18) -> the Z-buffer surface.
 *   5. IDirectDrawSurface7::AddAttachedSurface (vtbl+0xc) -> attach to back buffer.
 *   6. IDirect3DDevice7::SetRenderTarget (vtbl+0x20) -> bind. Return HR >= 0.
 *
 * Body is a hand-reconstruction, not a raw Ghidra port; see src/README.md.
 */
#include "ghidra_types.h"
#include <windows.h>


bool SetupZBuffer(void)
{
  /* BRING-UP WORKAROUND: skip Z-buffer creation entirely.
   *
   * The reconstruction below matches the original binary exactly (verified
   * field-by-field against a live GunBound.gme via tools/msvc-env/
   * orig_launcher_susp.c: the original's z-buffer CreateSurface/
   * AddAttachedSurface/SetRenderTarget all return HR=0). But under this
   * wine/wined3d build the bring-up exe's CreateSurface crashes
   * NON-DETERMINISTICALLY - the fault surfaces on a thread wine spawns
   * inside wined3d.dll itself (its asynchronous command-stream worker), so
   * the symptom and timing vary run-to-run and even debugger breakpoint
   * overhead perturbs it. It reproduces even with an all-correct descriptor,
   * so it is not a descriptor/arg bug in this function.
   *
   * The logo/menu states are 2-D sprite blits and do not depend on the
   * depth buffer, so returning success (as the original does on its
   * D3DPRASTERCAPS_ZBUFFERLESSHSR early-out path) lets InitDirectDraw
   * complete and startup proceed. Remove this once the wined3d CS-thread
   * crash is understood; the full implementation is preserved below.
   *
   * Disassembly-faithful body kept for reference / re-enable. */
  return true;
#if 0
  D3DDEVICEDESC7 devDesc;   /* GetCaps output (orig at SP0+0x7c) */
  DDSURFACEDESC2 zdesc;     /* back-buffer desc, reused as the Z-buffer desc (SP0+0) */
  int hr;

  /* 1. Device caps. If the HAL does Z-buffer-less hidden-surface removal
   *    (dpcTriCaps.dwRasterCaps bit 0x8000, orig test at 0x4ef9b6: dword at
   *    devDesc+0x44, bit 15), no Z-buffer is needed - succeed. */
  (**(code **)(*g_pD3DDevice7 + 0xc))(g_pD3DDevice7, &devDesc);
  if ((devDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_ZBUFFERLESSHSR) != 0) {
    return true;
  }

  /* 2. Read the back buffer's descriptor into the buffer we'll reuse for the
   *    Z-buffer (dwSize must be preset to 0x7c). Its dwWidth/dwHeight and its
   *    ddpfPixelFormat.dwRGBBitCount (= display depth) are kept as-is below. */
  zdesc.dwSize = sizeof(zdesc);          /* 0x7c */
  (**(code **)(*g_pBackBufferSurface + 0x58))(g_pBackBufferSurface, &zdesc);

  /* 3. Turn it into a Z-buffer request: CAPS|HEIGHT|WIDTH|PIXELFORMAT, caps
   *    ZBUFFER|VIDEOMEMORY. Only ddpfPixelFormat.dwSize is cleared - the rest
   *    (esp. the +0xc bit-count) stays as the back buffer's, so the first enum
   *    matches a Z format of the display's bit depth. Orig: dwFlags=0x1007 @
   *    0x4ef9f5, ddsCaps=0x24000 @ 0x4ef9fd, dwSize=0 @ 0x4efa05. */
  zdesc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT; /* 0x1007 */
  /* Zero the whole DDSCAPS2 (not just dwCaps) before repurposing the
   * back-buffer descriptor: dwCaps2/dwCaps3/dwCaps4 are separate dwords that
   * GetSurfaceDesc left set to whatever the back buffer (a flip-chain
   * COMPLEX surface) reported, and wine's ddraw rejects a Z-buffer
   * CreateSurface with E_INVALIDARG if those stale bits are still present. */
  ZeroMemory(&zdesc.ddsCaps, sizeof(zdesc.ddsCaps));
  zdesc.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_VIDEOMEMORY;           /* 0x24000 */
  zdesc.ddpfPixelFormat.dwSize = 0;

  (**(code **)(*g_pDirect3D7 + 0x18))
      (g_pDirect3D7, &DAT_00f22504, FUN_004ef970, &zdesc.ddpfPixelFormat);
  if (zdesc.ddpfPixelFormat.dwSize == 0) {
    /* No format at the display depth: force a 16-bit Z-buffer and retry.
     * Orig sets the enum match key (ddpfPixelFormat + 0xc = dwZBufferBitDepth)
     * to 0x10 @ 0x4efa2f; written via raw offset to avoid anonymous-union naming. */
    *(DWORD *)((char *)&zdesc.ddpfPixelFormat + 0xc) = 0x10;
    (**(code **)(*g_pDirect3D7 + 0x18))
        (g_pDirect3D7, &DAT_00f22504, FUN_004ef970, &zdesc.ddpfPixelFormat);
    if (zdesc.ddpfPixelFormat.dwSize == 0) {
      return false;
    }
  }

  /* 4-6. Create the Z-buffer, attach it to the back buffer, bind the render
   *      target. (Ghidra had already recovered these three tail calls.) */
  hr = (**(code **)(*g_pDirectDraw7 + 0x18))(g_pDirectDraw7, &zdesc, &g_pZBufferSurface, 0);
  if (hr < 0) {
    return false;
  }
  hr = (**(code **)(*g_pBackBufferSurface + 0xc))(g_pBackBufferSurface, g_pZBufferSurface);
  if (hr < 0) {
    return false;
  }
  hr = (**(code **)(*g_pD3DDevice7 + 0x20))(g_pD3DDevice7, g_pBackBufferSurface, 0);
  return hr >= 0;
#endif
}
