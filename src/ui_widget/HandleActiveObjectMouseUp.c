/* HandleActiveObjectMouseUp - 0x00406170 in the original binary.
 *
 * Mouse-button-up active-object hit-test: sole caller is WndProc's
 * WM_LBUTTONUP handler (case 0x202, 0x410344), preceded by `mov
 * edx,esi[mouseY]; mov ecx,edi[mouseX]; mov eax,0xe9be90[registry]`. On
 * a genuine release-over-the-pressed-object (state 1 "ready" or 5),
 * fires the click via EnqueueInputEvent(0, layer, id) - piVar1[1]/[2] are
 * the hit object's own +4/+8 fields, ButtonWidget.h's m_layer/m_id -
 * then plays the click sound and updates the object's visual state.
 *
 * FIXED (2026-07-13): part of the 5-function mouse-hit-test family (see
 * FindActiveObjectAt.c's header for the full trace of all 5). `in_EAX`
 * (registry) was already correctly identified but unpromoted; the
 * incoming ECX/EDX (mouseX/mouseY) were dropped entirely with no
 * placeholder at all - both are threaded straight through, unmodified,
 * into the `FindActiveObjectAt()` call. Promoted all three to explicit
 * parameters.
 */
#include "ghidra_types.h"


void HandleActiveObjectMouseUp(void *registry,int mouseX,int mouseY)

{
  int in_EAX = (int)registry;
  int *piVar1;

  piVar1 = (int *)FindActiveObjectAt(registry,mouseX,mouseY);
  *(undefined4 *)(in_EAX + 0xc) = 0;
  if (((piVar1 != (int *)0x0) && ((*(char *)(in_EAX + 0x14) == '\0' || (piVar1[1] == 1000000)))) &&
     ((piVar1[9] == 1 || (piVar1[9] == 5)))) {
    EnqueueInputEvent(0,piVar1[1],piVar1[2]);
    (**(code **)(*piVar1 + 4))(s_mouse_00551e70);
    AcquireSoundChannel(0);
  }
  return;
}

