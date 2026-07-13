/* FUN_0040ce50 - 0x0040ce50 in the original binary.
 *
 * Mouse-button-down fallback path (the "missed every widget, retarget the
 * default/background object" branch): sole caller is WndProc's
 * WM_LBUTTONDOWN handler (case 0x201's else-branch, 0x4102ea), right
 * after `push 0xe9c0fc; mov edx,ebx[mouseY]` with mouseX (ESI) unchanged
 * from WndProc's own locals.
 *
 * FIXED (2026-07-13): part of the 5-function mouse-hit-test family (see
 * FUN_0040cea0.c's header for the full trace of all 5). Unlike its 3
 * siblings, `param_1` here doubles as BOTH the widget-tree root passed
 * into FUN_0040cea0's EAX slot AND this function's own struct pointer
 * (its +8 field gets the hit-test result written into it) - a single
 * pointer serving both roles, confirmed via objdump (`mov eax,ebp[=
 * param_1]; call 0x40cea0` immediately followed by body code that reads/
 * writes `[ebp+8]`). The incoming ESI/EDX (mouseX/mouseY) were dropped
 * entirely with no placeholder at all - both are threaded straight
 * through, unmodified, into the `FUN_0040cea0()` call. Promoted both to
 * explicit trailing parameters (param_1's own position/meaning is
 * unchanged).
 */
#include "ghidra_types.h"


undefined4 FUN_0040ce50(int param_1,int mouseX,int mouseY)

{
  int iVar1;

  iVar1 = FUN_0040cea0((void *)param_1,mouseX,mouseY);
  if (iVar1 == 0) {
    return 0;
  }
  if (*(int *)(iVar1 + 0x448) != 1) {
    if (*(int *)(param_1 + 8) != 0) {
      FUN_0040ccf0();
    }
    *(int *)(param_1 + 8) = iVar1;
    FUN_0040cc50();
  }
  return 1;
}

