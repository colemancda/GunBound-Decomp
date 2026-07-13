/* FUN_00406120 - 0x00406120 in the original binary.
 *
 * Mouse-button-down widget hit-test: sole caller is WndProc's WM_LBUTTONDOWN
 * handler (case 0x201, 0x4102de and 0x410303 - both call sites), each
 * preceded by `mov edi,0xe9be90[widget root]` with mouseX/mouseY unchanged
 * from WndProc's own locals.
 *
 * FIXED (2026-07-13): part of the 5-function mouse-hit-test family (see
 * FUN_0040cea0.c's header for the full trace of all 5). `unaff_EDI`
 * (widgetRoot) was already correctly identified but unpromoted; the
 * incoming ESI/EDX (mouseX/mouseY) were dropped entirely with no
 * placeholder at all - both are threaded straight through, unmodified,
 * into the `FUN_0040cea0()` call. Promoted all three to explicit
 * parameters.
 */
#include "ghidra_types.h"


undefined4 FUN_00406120(void *widgetRoot,int mouseX,int mouseY)

{
  int iVar1;
  int *piVar2;
  int unaff_EDI = (int)widgetRoot;

  piVar2 = (int *)FUN_0040cea0(widgetRoot,mouseX,mouseY);
  if ((piVar2 != (int *)0x0) && ((*(char *)(unaff_EDI + 0x14) == '\0' || (piVar2[1] == 1000000)))) {
    iVar1 = piVar2[9];
    if ((iVar1 != 3) && ((iVar1 != 4 && (iVar1 != 5)))) {
      *(int **)(unaff_EDI + 0xc) = piVar2;
      (**(code **)(*piVar2 + 4))(&DAT_00551e78);
    }
    return 1;
  }
  return 0;
}

