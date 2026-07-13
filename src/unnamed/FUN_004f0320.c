/* FUN_004f0320 - 0x004f0320 in the original binary.
 *
 * Re-derives a fresh clipper for the primary surface (called from
 * ChangeGameState, likely on a display-mode/window change): clears the
 * primary surface's current clipper (SetClipper(NULL)), then - in
 * windowed mode only (DAT_00588f4c != 0) - creates a brand new
 * IDirectDrawClipper via IDirectDraw7::CreateClipper (vtable slot 4,
 * +0x10 bytes), binds it to the game window (IDirectDrawClipper::
 * SetHWnd, slot 8, +0x20), attaches it to the primary surface
 * (IDirectDrawSurface7::SetClipper, slot 0x1c, +0x70), then releases
 * the local reference (IUnknown::Release, slot 2, +8) since SetClipper
 * already AddRef'd it.
 *
 * Fully re-traced from orig 0x4f0320-0x4f037a with explicit stack-slot
 * bookkeeping (Ghidra's decompile mis-modeled the single reserved local
 * as two separate pseudo-locals and dropped every argument on both
 * SetClipper calls): the earlier port called SetClipper(this) with no
 * clipper argument at all, and separately passed g_pDirectDraw7 instead
 * of the freshly-created clipper on the second call - both silently
 * wrote/read garbage where Wine's ddraw.dll then asserted
 * (iface->lpVtbl == &ddraw_clipper_vtbl) on the bad pointer.
 *
 * CALLING-CONVENTION CAST MISMATCH: all four calls below (SetClipper x2,
 * CreateClipper, SetHWnd, Release) are real COM vtable methods -
 * __stdcall, self-cleaning via `ret N`. The generic `code()` cast used
 * here defaults to __cdecl, so the compiler emits a redundant
 * caller-side `add esp, N` after each call - confirmed via the compiled
 * object (`add esp,0x8` immediately after the first SetClipper call),
 * which corrupts the stack by N bytes too many (the exact bug already
 * documented/fixed in InitDirectDraw.c/SetupZBuffer.c/GameTick.c). This
 * silently clobbered the return address ChangeGameState's call to this
 * function relies on, crashing on return with eip pointing at garbage
 * instead of back into ChangeGameState - confirmed via debugger.
 * Fixed with explicit WINAPI typedefs matching InitDirectDraw.c's
 * established idiom.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"
#include <windows.h>

#define VTBL(iface, n) (*(void ***)(iface))[n]
typedef HRESULT (WINAPI *SetClipperFn)(void *, void *);
typedef HRESULT (WINAPI *CreateClipperFn)(void *, DWORD, void **, IUnknown *);
typedef HRESULT (WINAPI *SetHWndFn)(void *, DWORD, HWND);
typedef ULONG (WINAPI *ReleaseFn)(void *);

void FUN_004f0320(void)

{
  int iVar1;
  void *pClipper;

  ((SetClipperFn)VTBL(g_pPrimarySurface, 0x1c))(g_pPrimarySurface,0);
  if (DAT_00588f4c != '\0') {
    iVar1 = ((CreateClipperFn)VTBL(g_pDirectDraw7, 4))(g_pDirectDraw7,0,&pClipper,0);
    if (-1 < iVar1) {
      ((SetHWndFn)VTBL(pClipper, 8))(pClipper,0,DAT_007935ec);
      ((SetClipperFn)VTBL(g_pPrimarySurface, 0x1c))(g_pPrimarySurface,pClipper);
      ((ReleaseFn)VTBL(pClipper, 2))(pClipper);
    }
  }
  return;
}

