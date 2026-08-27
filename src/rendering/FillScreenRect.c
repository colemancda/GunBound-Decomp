/* FillScreenRect - 0x004eb800 in the original binary.
 *
 * Renamed from FillRect (its first assigned name) to FillScreenRect: it
 * collided with the real Win32 GDI FillRect(HDC, const RECT*, HBRUSH) that
 * <windows.h> already declares, breaking the whole build (C2373 redefinition)
 * for every file that includes both functions.h and windows.h.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ARGUMENTS RE-SLOTTED AND EAX RECOVERED (2026-08-27).  The full call is
 * FillScreenRect(topY, leftX, width, color, height): ECX is the top Y, EDX
 * the left X, the two pushed slots are the width and the 16-bit colour, and
 * EAX is the row count.  The port declared four parameters but every one of
 * the eleven sites passed only TWO -- the two pushes -- so width and colour
 * were landing in the Y and X slots.  This is a re-slot, not an append.
 *
 * The roles are fixed by the clipping, which pairs each value with its own
 * bound: EDX against g_clipMinX/g_clipMaxX ([0x793530]/[0x56df30]) and ECX
 * against g_clipMinY/g_clipMaxY ([0x793534]/[0x56df34]), with the width
 * adjusted alongside X and the height alongside Y.  EAX is read at 0x4eb80f
 * `mov edi,eax` with nothing writing it first, and it is the
 * `do { ... } while (in_EAX != 0)` row counter.  EBX, ESI, EDI and EBP are
 * all phantoms here (each written before any read), so the argument set is
 * exactly ECX, EDX, EAX plus the two stack slots.
 *
 * Four callers, eleven sites.  Two of them needed a value the original kept
 * live in a register across an intervening call, so RenderMobile and
 * FUN_00463630 each gain one local to carry it -- the width of the first bar
 * fill, which the second fill's Y offset is computed from.
 *
 * One site to be careful with: State11_InBattle_RenderPlayerRoster's Y is
 * local_1018[0], which is 0x216 only on the FIRST pass.  It is the roster-row
 * cursor, decremented by 0xf each time round the LAB_00409310 loop
 * (0x4095b6/0x4095be), which is exactly why the recovered argument has to be
 * the variable and not the constant it happens to hold first time through.
 *
 * A convention note, deliberately left alone: the original ends in a bare
 * `ret` with every caller doing its own `add esp,8`, i.e. caller-cleaned,
 * where MSVC's real __fastcall is callee-cleaned.  The declaration was
 * already __fastcall before this change and stays so; both sides are
 * recompiled, so the port is self-consistent even though it will not
 * byte-match the original here.
 */
#include "ghidra_types.h"


void __fastcall FillScreenRect(int param_1,int param_2,int param_3,int param_4,int regEax)

{
  int in_EAX = regEax;
  int iVar1;
  
  if (g_screenSurface != 0) {
    if (param_2 < g_clipMinX) {
      param_3 = param_3 + (param_2 - g_clipMinX);
      param_2 = g_clipMinX;
    }
    if (g_clipMaxX < param_2 + param_3) {
      param_3 = (g_clipMaxX - param_2) + 1;
    }
    if (0 < param_3) {
      if (param_1 < g_clipMinY) {
        in_EAX = in_EAX + (param_1 - g_clipMinY);
        param_1 = g_clipMinY;
      }
      if (g_clipMaxY < param_1 + in_EAX) {
        in_EAX = (g_clipMaxY - param_1) + 1;
      }
      if ((0 < in_EAX) &&
         (iVar1 = g_screenSurface + (g_screenPitch * param_1 + param_2) * 2, 0 < in_EAX)) {
        do {
          FillPixels16(iVar1,param_4,param_3);
          in_EAX = in_EAX + -1;
          iVar1 = iVar1 + g_screenPitch * 2;
        } while (in_EAX != 0);
      }
    }
  }
  return;
}

