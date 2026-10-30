/* CommP2PNotifyWndProc - 0x004fecb0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-29, CERTAIN (was FUN_004fecb0).  InitCommP2PNotifyWindow
 * installs it as the WNDPROC of the "CCommP2P Notify Window" it creates
 * (`push 0x4fecb0; push -4; ...; call esi` = SetWindowLongA(hwnd,
 * GWL_WNDPROC) at 0x4fdfb7-0x4fdfbf), after storing the CCommP2P
 * sub-object in GWL_USERDATA, which this reads back first
 * (GetWindowLongA(hwnd, -0x15) at 0x4fecb8).  It is the P2P twin of
 * CommEngineNotifyWndProc: message 0x54d is the code CreateBoundSocket
 * registers with WSAAsyncSelect for the UDP socket at +0x288, and on
 * that socket with WSAGETSELECTEVENT == FD_READ (1) it calls
 * CommP2PReceiveDatagram(obj, WSAGETSELECTERROR).  WM_TIMER (0x113)
 * for the timer ids at +0x2c4/+0x2c0 goes to FUN_004ffe80/FUN_004ffbe0;
 * everything else goes to DefWindowProcA.
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
LRESULT __stdcall CommP2PNotifyWndProc(HWND param_1,UINT param_2,WPARAM param_3,uint param_4)

{
  LONG LVar1;
  LRESULT LVar2;
  
  LVar1 = GetWindowLongA(param_1,-0x15);
  if (param_2 == 0x54d) {
    if ((param_3 == *(WPARAM *)(LVar1 + 0x288)) && ((short)param_4 == 1)) {
      CommP2PReceiveDatagram(LVar1,param_4 >> 0x10);
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

