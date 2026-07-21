/* FUN_004fecb0 - 0x004fecb0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* FIXED (2026-07-20): this is the "CCommP2P Notify Window" window procedure,
 * installed via SetWindowLongA(hWnd, GWL_WNDPROC) in
 * InitCommP2PNotifyWindow.c. A WNDPROC is __stdcall (callee-cleans), and the
 * original confirms it: every return in 0x4fecb0 is `ret 0x10` (4 args x 4
 * bytes; the tail helper at 0x4fedaf is the `ret 8` one). Ghidra emitted it as
 * __cdecl, so when user32 called it the stack was never cleaned - and the call
 * site passed the literal original-binary address 0x4fecb0 rather than this
 * symbol, so wine jumped into whatever our relink put there. */
LRESULT __stdcall FUN_004fecb0(HWND param_1,UINT param_2,WPARAM param_3,uint param_4)

{
  LONG LVar1;
  LRESULT LVar2;
  
  LVar1 = GetWindowLongA(param_1,-0x15);
  if (param_2 == 0x54d) {
    if ((param_3 == *(WPARAM *)(LVar1 + 0x288)) && ((short)param_4 == 1)) {
      FUN_004ff770(LVar1,param_4 >> 0x10);
    }
    return 0;
  }
  if (param_2 == 0x113) {
    if (param_3 == *(WPARAM *)(LVar1 + 0x2c4)) {
      FUN_004ffe80(LVar1);
      return 0;
    }
    if (param_3 == *(WPARAM *)(LVar1 + 0x2c0)) {
      FUN_004ffbe0(LVar1);
      return 0;
    }
  }
  LVar2 = DefWindowProcA(param_1,param_2,param_3,param_4);
  return LVar2;
}

