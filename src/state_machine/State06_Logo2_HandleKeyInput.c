/* State06_Logo2_HandleKeyInput - 0x004433c0 in the original binary.
 *
 * CGameState vtable slot 6 (+0x18, "mouse/key message dispatch") for
 * Logo2. Despite the slot's generic name, this specific override only
 * reacts to WM_KEYDOWN/WM_SYSKEYDOWN/WM_CHAR-family messages (0x100,
 * 0x101, 0x104 - confirmed via the three `sub eax,N; je` comparisons
 * against msg): on any of those, clamps the frame counter at
 * this+4 (the same counter State06_Logo2_OnTick increments each tick
 * and checks against 0x28 to trigger the Title transition) down to
 * 0x27 if it's already past that - i.e. "any key press skips the rest
 * of the logo, letting the next tick's increment naturally trigger the
 * transition" rather than jumping state immediately itself.
 *
 * Was wired to the plain 0-arg NoOpMethod (a genuine mismatch: this
 * slot is real logic, and calling a 0-arg __cdecl NoOp through the
 * 3-arg __fastcall StateSlot6DispatchFn pointer type corrupted the
 * caller's stack on every keyboard/mouse message while Logo2 was
 * active - confirmed via debugger, this was the "exception spam" loop
 * following a WM_NCHITTEST/mouse-move message). See WndProc.c's
 * StateSlot6DispatchFn typedef for the call-site signature this must
 * match exactly (this in ECX, no EDX arg used, msg/wParam/lParam on
 * the stack, __fastcall with ret 0xc self-cleanup).
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall State06_Logo2_HandleKeyInput(int param_1,int dummyEDX,uint msg,uint wParam,uint lParam)

{
  (void)dummyEDX;
  (void)wParam;
  (void)lParam;
  if ((msg == 0x100) || (msg == 0x101) || (msg == 0x104)) {
    if (0x27 < *(int *)(param_1 + 4)) {
      *(int *)(param_1 + 4) = 0x27;
    }
  }
  return;
}
