/* DrawRectOutline - 0x004eb7a0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004eb7a0 mean this function.)
 *
 * NAMED (2026-11-05), CERTAIN. Evidence from outside the body: its four
 * callees are the already-named DrawHLine (0x4eb5d0, top and bottom edge)
 * and DrawVLine (left and right edge), so the four edges form a rectangle
 * outline with x, width and height on the stack, y in ESI and the colour in
 * EAX. The callers confirm the shape: TextEntry_Update and
 * State11_InBattle_RenderPlayerRoster pass (column * 6 + base, span * 6,
 * 0xc), a text-selection or caret rectangle one row tall (the ReadyRoom
 * status overlay inlines the same call), and RenderMobile, its C++ twin in
 * Mobile.cpp and FUN_00463630 pass (x + 1, 0x4e, 5), a 78 by 5 box. It
 * draws the outline only.
 */
#include "ghidra_types.h"


void DrawRectOutline(int param_1,int param_2,int param_3)

{
  /* DROPPED-REG FIX (2026-08-28): a rectangle-outline helper - two
   * DrawHLine calls for the top and bottom edges, two DrawVLine calls for
   * the left and right - whose every argument Ghidra dropped.
   *
   * Three arrive on the stack and are now declared. `mov edx,[esp+8]` at
   * 0x4eb7a0, before any push, is param_2, the width; `mov ebp,[esp+0xc]`
   * at 0x4eb7a6 with ebx and ebp pushed reaches entry+4, param_1, the x;
   * `mov eax,[esp+0x1c]` at 0x4eb7b7 with three saves plus the colour word
   * outstanding reaches entry+0xc, param_3, the height. The function ends
   * in a bare `ret`, so all three are caller-cleaned. All five ported call
   * sites (and the C++ twin's own extern in Mobile.cpp) already pass
   * exactly these three, so declaring them changes no caller.
   *
   * Two more arrive in registers and are this function's own outstanding
   * dropped-register gap, left as Ghidra locals: EAX, captured by
   * `mov ebx,eax` at 0x4eb7aa - the colour, pushed for both DrawHLine
   * calls and consumed as BX by both DrawVLine calls - and ESI, captured
   * by `mov edi,esi` at 0x4eb7ae, the top row y.
   *
   * The four edges, read off the register setup at each call: top row
   * edi = esi; bottom row `lea edi,[esi+eax-1]` at 0x4eb7bf with
   * eax = param_3; left column edi = ebp = param_1; right column
   * `lea edi,[ecx+ebp-1]` at 0x4eb7df with ecx = param_2. Both DrawVLine
   * calls take ecx = param_3 as their run length, reloaded at 0x4eb7cb
   * and 0x4eb7e3 from the same entry+0xc slot at different depths. The
   * two pushed colour words are retired together by `add esp,8` at
   * 0x4eb7cf, which is what makes that stack argument easy to lose. */
  int in_EAX;
  int unaff_ESI;

  DrawHLine(0,param_2,in_EAX,param_1,unaff_ESI);
  DrawHLine(0,param_2,in_EAX,param_1,(unaff_ESI + param_3) + -1);
  DrawVLine(param_3,unaff_ESI,in_EAX,param_1);
  DrawVLine(param_3,unaff_ESI,in_EAX,(param_2 + param_1) + -1);
  return;
}

