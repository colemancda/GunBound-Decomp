/* State01_Title_HandleKeyInput - 0x004e5340 in the original binary.
 *
 * CGameState vtable slot 6 (+0x18, "mouse/key message dispatch") for
 * Title. Same shape as State06_Logo2_HandleKeyInput (0x4433c0): on
 * WM_KEYDOWN/WM_SYSKEYDOWN/WM_CHAR-family messages (0x100, 0x101,
 * 0x104), clamps the frame counter at this+4 down to 0x3b if it's
 * already past that - State01_Title_OnTick checks this same counter
 * against 0x3c to trigger the ServerSelect transition, so this is
 * "any key press skips the rest of the title screen."
 *
 * Was wired to the plain 0-arg NoOpMethod - same calling-convention
 * mismatch bug as State06_Logo2's slot 6 (see that file's header for
 * the full writeup); this slot needed the same fix once Title is
 * actually reached, which it isn't in the confirmed startup path today
 * (Logo2 always runs first) - fixed alongside as the identical known
 * pattern, not from an independently observed crash on this state.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall State01_Title_HandleKeyInput(int param_1,int dummyEDX,uint msg,uint wParam,uint lParam)

{
  (void)dummyEDX;
  (void)wParam;
  (void)lParam;
  if ((msg == 0x100) || (msg == 0x101) || (msg == 0x104)) {
    if (0x3b < *(int *)(param_1 + 4)) {
      *(int *)(param_1 + 4) = 0x3b;
    }
  }
  return;
}
