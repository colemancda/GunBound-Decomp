/* InitDirectDraw - 0x004efaa0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "xfs.h"
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* Every call below dispatches through an EXPLICIT __stdcall function-pointer
 * cast, not the generic `code` (K&R/unspecified-args) type used elsewhere in
 * raw ports. `code()` has no prototype, so MSVC defaults it to __cdecl and
 * emits a caller-side `add esp, N` after some of these calls to pop the
 * arguments it *itself* pushed - but every one of these is a real COM vtable
 * method, which is __stdcall and ALREADY pops its own args via `ret N` before
 * returning. That is a double stack cleanup: the call leaves ESP N bytes
 * higher than it should be, shrinking the slack between ESP and the saved
 * EBP/return address by N bytes. Confirmed live (hardware watchpoint on the
 * saved-EBP stack slot, fired from inside ddraw.dll) that this corrupts the
 * caller's frame once enough such calls accumulate in one function - see
 * SetupZBuffer.c for the full writeup. Giving every call site its real
 * prototype makes MSVC skip the redundant caller-side cleanup entirely. */
typedef HRESULT (WINAPI *QueryInterfaceFn)(void *, REFIID, void **);
typedef HRESULT (WINAPI *SetCooperativeLevelFn)(void *, HWND, DWORD);
typedef HRESULT (WINAPI *SetDisplayModeFn)(void *, DWORD, DWORD, DWORD, DWORD, DWORD);
typedef HRESULT (WINAPI *CreateSurfaceFn)(void *, DDSURFACEDESC2 *, void **, IUnknown *);
typedef HRESULT (WINAPI *GetAttachedSurfaceFn)(void *, DDSCAPS2 *, void **);
typedef HRESULT (WINAPI *CreateClipperFn)(void *, DWORD, void **, IUnknown *);
typedef HRESULT (WINAPI *SetHWndFn)(void *, DWORD, HWND);
typedef HRESULT (WINAPI *SetClipperFn)(void *, void *);
typedef HRESULT (WINAPI *CreateDeviceFn)(void *, REFCLSID, void *, void **);
typedef HRESULT (WINAPI *SetViewportFn)(void *, void *);
typedef HRESULT (WINAPI *EnumTextureFormatsFn)(void *, void *, LPVOID);
typedef HRESULT (WINAPI *GetAvailableVidMemFn)(void *, DDSCAPS2 *, DWORD *, DWORD *);
typedef HRESULT (WINAPI *SetRenderStateFn)(void *, DWORD, DWORD);
typedef HRESULT (WINAPI *SetTextureStageStateFn)(void *, DWORD, DWORD, DWORD);

/* Nth pointer-sized vtable slot (N = byte offset / 4). */
#define VTBL(iface, n) (*(void ***)(iface))[n]

byte InitDirectDraw(undefined4 param_1, HWND hWnd)

{
  int iVar4;
  FARPROC pFVar3;
  IMAGE_DOS_HEADER *pIVar6;
  D3DVIEWPORT7 viewport;
  /* Real Win32 surface-description structs. The Ghidra decompile scattered
   * these fields across disconnected stack locals (auStack_a4/uStack_90/
   * uStack_3c/aiStack_b4), so CreateSurface saw a malformed DDSURFACEDESC2
   * (dwBackBufferCount=0, ddsCaps=0) and faulted in ddraw's HAL. Rebuilt as
   * contiguous structs; field values recovered from orig 0x4efb81-0x4efcd0. */
  DDSURFACEDESC2 ddsd;
  DDSCAPS2 ddscaps;
  DDSCAPS2 vidMemCaps;
  DWORD vidMemTotal, vidMemFree;

  /* The main game window handle arrived in EAX in the original (a dropped
   * register arg in Ghidra's port); InitGame passes it explicitly now.
   * SetCooperativeLevel below needs a valid HWND or it returns 0x80070018. */
  DAT_007935ec = (uint32_t)hWnd;
  g_hDDrawDll = LoadLibraryA(s_ddraw_dll_00557510);
  if (g_hDDrawDll == (HMODULE)0x0) {
    return 0x1a;
  }
  pFVar3 = GetProcAddress(g_hDDrawDll,s_DirectDrawCreateEx_005574fc);
  /* DirectDrawCreateEx(lpGuid=NULL, lplpDD=&g_pDirectDraw7, iid=IID_IDirectDraw7,
   * pUnkOuter=NULL). Ghidra emitted this as an argless `(*pFVar3)()`; the real
   * argument push order was recovered from the original at 0x4efae2-0x4efaee
   * (push NULL / &IID_IDirectDraw7 / &g_pDirectDraw7 / NULL). Without the args
   * ddraw reads uninitialised stack for the requested IID and faults at
   * ddraw+0x21d5a (NULL deref while walking its interface list). */
  iVar4 = ((HRESULT (WINAPI *)(GUID *, LPVOID *, REFIID, IUnknown *))pFVar3)
              (NULL, (LPVOID *)&g_pDirectDraw7, &IID_IDirectDraw7, NULL);
  if (iVar4 < 0) {
    return 0x19;
  }
  iVar4 = ((SetCooperativeLevelFn)VTBL(g_pDirectDraw7, 0x14))
                    (g_pDirectDraw7, (HWND)DAT_007935ec, (DAT_00588f4c == '\0') ? 0xc13 : 0xc08);
  if (iVar4 < 0) {
    return 0x18;
  }
  if (DAT_00588f4c == '\0') {
    /* SetDisplayMode(width, height, bpp, refresh, flags). The original passed
     * ftol(DAT_00588f50) / ftol(DAT_00588f54) for width/height - FloatToInt64
     * is _ftol, fed the float via the x87 stack (a `flds` the recompiled
     * argless call never emits, so it returned garbage/0 and the mode came out
     * 0x0x0). DAT_00588f50/54 are now real floats; convert them directly. */
    iVar4 = ((SetDisplayModeFn)VTBL(g_pDirectDraw7, 0x15))
                      (g_pDirectDraw7, (DWORD)DAT_00588f50, (DWORD)DAT_00588f54,
                       DAT_00588f60, DAT_00588f48, 0);
    if (iVar4 < 0) {
      return 0x1c;
    }
  }
  ZeroMemory(&ddsd, sizeof(ddsd));
  ddsd.dwSize = sizeof(ddsd);                         /* 0x7c */
  if (DAT_00588f4c == '\0') {
    /* fullscreen: complex flip chain, primary surface + one back buffer */
    _DAT_006773b4 = 0;
    _DAT_006773bc = 800;
    _DAT_006773b8 = 0;
    _DAT_006773c0 = 600;
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;   /* 0x21 */
    ddsd.dwBackBufferCount = 1;
    /* PRIMARYSURFACE|FLIP|COMPLEX|3DDEVICE|VIDEOMEMORY */
    ddsd.ddsCaps.dwCaps = 0x6218;
  }
  else {
    GetClientRect(DAT_007935ec,(LPRECT)&DAT_006773b4);
    ClientToScreen(DAT_007935ec,(LPPOINT)&DAT_006773b4);
    ClientToScreen(DAT_007935ec,(LPPOINT)&DAT_006773bc);
    ddsd.dwFlags = DDSD_CAPS;                          /* 0x1 */
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;      /* 0x200 */
  }
  iVar4 = ((CreateSurfaceFn)VTBL(g_pDirectDraw7, 6))
                    (g_pDirectDraw7, &ddsd, (void **)&g_pPrimarySurface, 0);
  if (iVar4 < 0) {
    return 0x1d;
  }
  if (DAT_00588f4c == '\0') {
    /* fullscreen: fetch the attached back buffer of the flip chain */
    ZeroMemory(&ddscaps, sizeof(ddscaps));
    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;              /* 0x4 */
    iVar4 = ((GetAttachedSurfaceFn)VTBL(g_pPrimarySurface, 0xc))
                      (g_pPrimarySurface, &ddscaps, (void **)&g_pBackBufferSurface);
    if (iVar4 < 0) {
      return 0x1f;
    }
  }
  else {
    /* windowed: create a separate off-screen back buffer sized to the client.
     * FloatToInt64 is an ftol-style helper the original fed via the x87 stack
     * (flds DAT_00588f50/DAT_00588f54); the register/FPU arg is a Ghidra
     * artifact left as-is - windowed mode is not the bring-up path. */
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;  /* 0x7 */
    ddsd.dwWidth = (DWORD)FloatToInt64();
    ddsd.dwHeight = (DWORD)FloatToInt64();
    ddsd.ddsCaps.dwCaps = 0x2040;                     /* 3DDEVICE|OFFSCREENPLAIN */
    iVar4 = ((CreateSurfaceFn)VTBL(g_pDirectDraw7, 6))
                      (g_pDirectDraw7, &ddsd, (void **)&g_pBackBufferSurface, 0);
    if (iVar4 < 0) {
      return 0x1e;
    }
  }
  ((CreateClipperFn)VTBL(g_pDirectDraw7, 4))(g_pDirectDraw7, 0, (void **)&g_pClipper, 0);
  ((SetHWndFn)VTBL(g_pClipper, 8))(g_pClipper, 0, DAT_007935ec);
  ((SetClipperFn)VTBL(g_pBackBufferSurface, 0x1c))(g_pBackBufferSurface, g_pClipper);
  iVar4 = ((QueryInterfaceFn)VTBL(g_pDirectDraw7, 0))
                    (g_pDirectDraw7, &IID_IDirect3D7, (void **)&g_pDirect3D7);
  if (iVar4 < 0) {
    return 0x20;
  }
  iVar4 = ((CreateDeviceFn)VTBL(g_pDirect3D7, 4))
                    (g_pDirect3D7, &DAT_00f22504, g_pBackBufferSurface, (void **)&g_pD3DDevice7);
  if (iVar4 < 0) {
    return 0x21;
  }
  /* D3DVIEWPORT7{dwX=0, dwY=0, dwWidth, dwHeight, dvMinZ=0.0, dvMaxZ=1.0}.
   * Recovered from the original's disconnected locals at 0x4efd7a-0x4efd9d:
   * width/height came from the SAME ftol(DAT_00588f50/54) pair used for
   * SetDisplayMode, dvMinZ=0 and dvMaxZ=1.0 (bit pattern 0x3f800000). */
  ZeroMemory(&viewport, sizeof(viewport));
  viewport.dwWidth = (DWORD)DAT_00588f50;
  viewport.dwHeight = (DWORD)DAT_00588f54;
  viewport.dvMaxZ = 1.0f;
  iVar4 = ((SetViewportFn)VTBL(g_pD3DDevice7, 0xd))(g_pD3DDevice7, &viewport);
  if (iVar4 < 0) {
    return 0x22;
  }
  pIVar6 = (IMAGE_DOS_HEADER *)g_pD3DDevice7;
  iVar4 = ((EnumTextureFormatsFn)VTBL(g_pD3DDevice7, 4))
                    (g_pD3DDevice7, EnumTextureFormatsCallback, 0);
  if (iVar4 < 0) {
    return 0x23;
  }
  /* DDSCAPS2{dwCaps=DDSCAPS_TEXTURE, rest 0}; recovered from orig 0x4efd2e-0x4efd52. */
  ZeroMemory(&vidMemCaps, sizeof(vidMemCaps));
  vidMemCaps.dwCaps = DDSCAPS_TEXTURE;
  ((GetAvailableVidMemFn)VTBL(g_pDirectDraw7, 0x17))
      (g_pDirectDraw7, &vidMemCaps, &vidMemTotal, &vidMemFree);
  if (pIVar6 < &IMAGE_DOS_HEADER_00400000) {
    return 0x1b;
  }
  FUN_004f3e40();
  FUN_004f3a00();
  ((SetRenderStateFn)VTBL(g_pD3DDevice7, 0x14))(g_pD3DDevice7,0x13,5);
  ((SetRenderStateFn)VTBL(g_pD3DDevice7, 0x14))(g_pD3DDevice7,0x14,6);
  ((SetRenderStateFn)VTBL(g_pD3DDevice7, 0x14))(g_pD3DDevice7,0x28,1);
  ((SetTextureStageStateFn)VTBL(g_pD3DDevice7, 0x25))(g_pD3DDevice7,0,0x10,5);
  ((SetTextureStageStateFn)VTBL(g_pD3DDevice7, 0x25))(g_pD3DDevice7,0,0x11,3);
  ((SetTextureStageStateFn)VTBL(g_pD3DDevice7, 0x25))(g_pD3DDevice7,1,0x10,5);
  ((SetTextureStageStateFn)VTBL(g_pD3DDevice7, 0x25))(g_pD3DDevice7,1,0x11,3);
  ((SetTextureStageStateFn)VTBL(g_pD3DDevice7, 0x25))(g_pD3DDevice7,0,2,2);
  ((SetTextureStageStateFn)VTBL(g_pD3DDevice7, 0x25))(g_pD3DDevice7,0,3,0);
  ((SetTextureStageStateFn)VTBL(g_pD3DDevice7, 0x25))(g_pD3DDevice7,0,5,2);
  ((SetTextureStageStateFn)VTBL(g_pD3DDevice7, 0x25))(g_pD3DDevice7,0,6,0);
  ((SetTextureStageStateFn)VTBL(g_pD3DDevice7, 0x25))(g_pD3DDevice7,0,1,4);
  ((SetTextureStageStateFn)VTBL(g_pD3DDevice7, 0x25))(g_pD3DDevice7,0,4,4);
  ((SetRenderStateFn)VTBL(g_pD3DDevice7, 0x14))(g_pD3DDevice7,8,3);
  ((SetRenderStateFn)VTBL(g_pD3DDevice7, 0x14))(g_pD3DDevice7,0x88,1);
  OpenXFSArchive(&g_graphicsArchive,param_1,1,0);
  _DAT_00f23658 = 600;
  _DAT_00f23654 = 800;
  ZeroMemory(DAT_00f22650, sizeof(DAT_00f22650));
  _DAT_00f23650 = 0;
  g_nCompositorLayer = 0;
  return SetupZBuffer() ? 0 : 100;
}
