/* FUN_00406170 - 0x00406170 in the original binary.
 *
 * Mouse-button-up widget hit-test: sole caller is WndProc's WM_LBUTTONUP
 * handler (case 0x202, 0x410344), preceded by `mov edx,esi[mouseY]; mov
 * ecx,edi[mouseX]; mov eax,0xe9be90[widget root]`.
 *
 * FIXED (2026-07-13): part of the 5-function mouse-hit-test family (see
 * FUN_0040cea0.c's header for the full trace of all 5). `in_EAX`
 * (widgetRoot) was already correctly identified but unpromoted; the
 * incoming ECX/EDX (mouseX/mouseY) were dropped entirely with no
 * placeholder at all - both are threaded straight through, unmodified,
 * into the `FUN_0040cea0()` call. Promoted all three to explicit
 * parameters.
 */
#include "ghidra_types.h"


void FUN_00406170(void *widgetRoot,int mouseX,int mouseY)

{
  int in_EAX = (int)widgetRoot;
  int *piVar1;

  piVar1 = (int *)FUN_0040cea0(widgetRoot,mouseX,mouseY);
  *(undefined4 *)(in_EAX + 0xc) = 0;
  if (((piVar1 != (int *)0x0) && ((*(char *)(in_EAX + 0x14) == '\0' || (piVar1[1] == 1000000)))) &&
     ((piVar1[9] == 1 || (piVar1[9] == 5)))) {
    FUN_004f2da0(0,piVar1[1],piVar1[2]);
    (**(code **)(*piVar1 + 4))(s_mouse_00551e70);
    AcquireSoundChannel(0);
  }
  return;
}

