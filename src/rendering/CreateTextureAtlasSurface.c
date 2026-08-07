/* CreateTextureAtlasSurface - 0x004f0230 in the original binary.
 *
 * Creates one 256x256 DirectDraw atlas surface: fills a 0x7c-byte
 * DDSURFACEDESC2, picks the pixel-format template by format id, and
 * calls IDirectDraw7::CreateSurface (g_pDirectDraw7 vtable +0x18).
 * NAMED (2026-07-18) from that behavior; called by InitTextureAtlasPage.
 *
 * RECONSTRUCTED (2026-08-06) from the 0x4f0230-0x4f02bc disassembly,
 * fixing three bugs in the raw port - the same classes already fixed in
 * InitDirectDraw.c / SetupZBuffer.c:
 *
 *   1. Split-struct: the DDSURFACEDESC2 was scattered across five
 *      disconnected stack locals (local_88[18], local_40[8], local_20,
 *      local_1c, local_10) that only form the real 0x7c struct if MSVC
 *      happens to place them contiguously in exactly that order - and
 *      the zero-loop wrote 0x1f dwords (0x7c bytes) through the first
 *      one regardless. The Ghidra local names ARE the frame offsets and
 *      they map exactly onto the real layout: local_40 = +0x48
 *      ddpfPixelFormat, local_20/1c = +0x68/+0x6c ddsCaps.dwCaps/dwCaps2,
 *      local_10 = +0x78 dwTextureStage. Rebuilt as one real struct.
 *
 *   2. Discarded HRESULT: the port returned `-1 < iVar1` with iVar1
 *      always 0 after the copy loop - i.e. unconditionally true, the
 *      CreateSurface result thrown away. The original does `test eax,eax;
 *      setge al` - it returns hr >= 0. With the old always-true return,
 *      a failed CreateSurface left page+0x110 NULL and InitTextureAtlas
 *      Page's success path ran anyway - the NULL-vtable-slot crash the
 *      AVATAR click currently hits arrived through exactly this.
 *
 *   3. Generic `code()` COM dispatch: cdecl-defaulted, so MSVC may emit
 *      a caller-side `add esp,0x10` after a callee that already popped
 *      its own args (`ret 0x10`) - the double-cleanup ESP drift class.
 *      Now an explicit __stdcall CreateSurfaceFn through VTBL slot 6.
 *
 * Field values, byte-recovered from the original:
 *   dwSize   0x7c      dwFlags 0x101007 = DDSD_CAPS|DDSD_HEIGHT|
 *                      DDSD_WIDTH|DDSD_PIXELFORMAT|DDSD_TEXTURESTAGE
 *   dwHeight/dwWidth 0x100
 *   ddsCaps.dwCaps  0x4001000 = DDSCAPS_TEXTURE|DDSCAPS_NONLOCALVIDMEM
 *   ddsCaps.dwCaps2 0x10     = DDSCAPS2_TEXTUREMANAGE
 *   dwTextureStage  1
 *   ddpfPixelFormat: 0x20 bytes copied from DAT_006777e8 (format id != 0,
 *   the ARGB4444 match) or DAT_00677544 (format id 0, the RGB565 match) -
 *   both filled at init time by EnumTextureFormatsCallback.
 *
 * Convention note: in the original this is ECX-unused/EDX=outSurface
 * with the format id as a caller-cleaned stack dword (plain `ret`; the
 * sole caller does `add esp,4`). Our port declares MSVC __fastcall,
 * which is callee-cleaned instead - fine, because the one caller
 * (InitTextureAtlasPage) is also our code and both sides agree. */
#include "ghidra_types.h"
#include <windows.h>

typedef HRESULT (WINAPI *CreateSurfaceFn)(void *, DDSURFACEDESC2 *, void **, IUnknown *);
/* Nth pointer-sized vtable slot (N = byte offset / 4). */
#define VTBL(iface, n) (*(void ***)(iface))[n]

bool __fastcall CreateTextureAtlasSurface(undefined4 param_1,undefined4 param_2,int param_3)

{
  HRESULT hr;
  int iVar1;
  uint32_t *src;
  uint32_t *dst;
  DDSURFACEDESC2 ddsd;

  (void)param_1;                          /* ECX unused in the original */
  ZeroMemory(&ddsd, sizeof(ddsd));
  ddsd.dwSize = sizeof(ddsd);             /* 0x7c */
  ddsd.dwFlags = 0x101007;                /* CAPS|HEIGHT|WIDTH|PIXELFORMAT|TEXTURESTAGE */
  ddsd.dwHeight = 0x100;
  ddsd.dwWidth = 0x100;
  ddsd.ddsCaps.dwCaps = 0x4001000;        /* TEXTURE|NONLOCALVIDMEM */
  ddsd.ddsCaps.dwCaps2 = 0x10;            /* TEXTUREMANAGE */
  ddsd.dwTextureStage = 1;
  src = ((char)param_3 == '\0') ? DAT_00677544 : DAT_006777e8;
  dst = (uint32_t *)&ddsd.ddpfPixelFormat;
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    *dst = *src;
    src = src + 1;
    dst = dst + 1;
  }
  hr = ((CreateSurfaceFn)VTBL(g_pDirectDraw7, 6))
                    (g_pDirectDraw7, &ddsd, (void **)param_2, 0);
  return hr >= 0;
}
