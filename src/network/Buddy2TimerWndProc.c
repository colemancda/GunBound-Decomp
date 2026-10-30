/* Buddy2TimerWndProc - 0x004fdaa0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_004fdaa0).  The window procedure of
 * the "CBuddy2 Timer Receiving Window". CommP2POwner_ProcessPacket
 * creates that window (CreateWindowExA with title 0x557b74 at 0x501a53),
 * stores the CBuddy2 object (its this - 0x2f4) in GWL_USERDATA
 * (SetWindowLongA(hwnd, -0x15, ...) at 0x501a73), installs this function
 * with `push 0x4fdaa0 / push -4 / call esi` = SetWindowLongA(hwnd,
 * GWL_WNDPROC) at 0x501a7b-0x501a83, and arms SetTimer(hwnd, 0x14d,
 * 60000) at 0x501aa6, storing the id at its +0x17c4 = CBuddy2+0x1ab8.
 * This reads the object back with GetWindowLongA(hwnd, -0x15) and on
 * WM_TIMER (0x113) for exactly that id (wParam == [obj+0x1ab8]) does the
 * keepalive check; everything else goes to DefWindowProcA.
 *
 * Named on the CommP2PNotifyWndProc / CommEngineNotifyWndProc pattern:
 * the owning class from the window title with its C prefix dropped
 * ("CCommP2P Notify Window" -> CommP2P..., "CCommEngine Notify Window"
 * -> CommEngine...), so "CBuddy2 Timer Receiving Window" -> Buddy2Timer.
 *
 * The check: while the session flag [obj+0x1a70] is set, if time(0) has
 * passed [obj+0x1abc] + 600 - 90.0 (_DAT_00558048 is the double 90.0),
 * call FUN_005024a0(0). [obj+0x1abc] is the clock FUN_00502500 and
 * FUN_005024a0 stamp on every frame they send, and FUN_005024a0 sends a
 * bare [len=4][opcode] frame through CommConnectionSendOrQueue - so an
 * idle CBuddy2 connection gets an empty opcode-0 frame roughly every 510
 * seconds, checked once a minute.
 *
 * DROPPED REGISTER FIXED (2026-10-30): the FUN_005024a0 call also passes
 * ESI = the GWL_USERDATA object (`mov esi,eax` at 0x4fdab6, unchanged to
 * the call at 0x4fdb11 - ESI is callee-saved across the time() call).
 * FUN_005024a0 now takes it as its trailing regEsi and this call passes
 * LVar2.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* FIXED (2026-07-20): a WNDPROC installed via SetWindowLongA(GWL_WNDPROC);
 * __stdcall, confirmed by `ret 0x10` at every return in the original.
 * Ghidra emitted __cdecl, and the install site passed the literal
 * original-binary address instead of this symbol. Same bug class as
 * CommP2PNotifyWndProc. */
LRESULT __stdcall Buddy2TimerWndProc(HWND param_1,UINT param_2,WPARAM param_3,LPARAM param_4)

{
  double dVar1;
  LONG LVar2;
  __time32_t _Var3;
  LRESULT LVar4;
  
  LVar2 = GetWindowLongA(param_1,-0x15);
  if ((param_2 == 0x113) && (param_3 == *(WPARAM *)(LVar2 + 0x1ab8))) {
    if (*(char *)(LVar2 + 0x1a70) != '\0') {
      dVar1 = (double)(*(int *)(LVar2 + 0x1abc) + 600) - _DAT_00558048;
      _Var3 = FID_conflict___time32((__time32_t *)0x0);
      if (dVar1 < (double)_Var3) {
        /* 0x4fdb0f: push 0 (opcode); ESI = LVar2, the GWL_USERDATA object
         * (`mov esi,eax` at 0x4fdab6) */
        FUN_005024a0(0,LVar2);
      }
    }
    return 0;
  }
  LVar4 = DefWindowProcA(param_1,param_2,param_3,param_4);
  return LVar4;
}

