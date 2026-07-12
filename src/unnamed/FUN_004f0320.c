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
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f0320(void)

{
  int iVar1;
  void *pClipper;

  (**(code **)(*g_pPrimarySurface + 0x70))(g_pPrimarySurface,0);
  if (DAT_00588f4c != '\0') {
    iVar1 = (**(code **)(*g_pDirectDraw7 + 0x10))(g_pDirectDraw7,0,&pClipper,0);
    if (-1 < iVar1) {
      (**(code **)(*(int *)pClipper + 0x20))(pClipper,0,DAT_007935ec);
      (**(code **)(*g_pPrimarySurface + 0x70))(g_pPrimarySurface,pClipper);
      (**(code **)(*(int *)pClipper + 8))(pClipper);
    }
  }
  return;
}

