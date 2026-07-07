/* FUN_0040c670 - 0x0040c670 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void __fastcall FUN_0040c670(HINSTANCE param_1)

{
  HWND in_EAX;
  HWND hWnd;
  LONG LVar1;
  undefined4 *unaff_ESI;
  
  DAT_005b1c48 = unaff_ESI;
  *unaff_ESI = in_EAX;
  hWnd = CreateWindowExA(0,&DAT_00552084,(LPCSTR)0x0,0x40800000,0,0,800,0x18,in_EAX,(HMENU)0x0,
                         param_1,(LPVOID)0x0);
  unaff_ESI[1] = hWnd;
  LVar1 = GetWindowLongA(hWnd,-4);
  unaff_ESI[3] = LVar1;
  SetWindowLongA((HWND)unaff_ESI[1],-4,0x40c6f0);
  SetFocus((HWND)unaff_ESI[1]);
  *(undefined1 *)(unaff_ESI + 2) = 1;
  if (DAT_005b3438 == 1) {
    ImmDisableIME(0);
  }
  return;
}

