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

/* The released object's vtable slot 1 (CButtonWidget::SetState) is a real
 * C++ __thiscall (orig 0x4061be: `mov ecx,esi`(this=object) / `push
 * 0x551e70`(name) / `call [edx+4]`) - fix its dropped `this` with the
 * __fastcall + dummy-EDX idiom. */
typedef void (__fastcall *WidgetSetStateFn)(void *thisPtr, int dummyEDX, void *name);

void HandleActiveObjectMouseUp(void *registry,int mouseX,int mouseY)

{
  int in_EAX = (int)registry;
  int *piVar1;

  piVar1 = (int *)FindActiveObjectAt(registry,mouseX,mouseY);
  *(undefined4 *)(in_EAX + 0xc) = 0;
  if (((piVar1 != (int *)0x0) && ((*(char *)(in_EAX + 0x14) == '\0' || (piVar1[1] == 1000000)))) &&
     ((piVar1[9] == 1 || (piVar1[9] == 5)))) {
    /* FIXED (2026-07-18): the click fire had TWO dropped args (orig
     * 0x4061a5-0x4061c0). (1) EnqueueInputEvent's queue object arrives in
     * EAX = *(registry+0x10) (the input-event ring) - the port passed 0,
     * corrupting the ring push; recovered it. (2) the slot-1 SetState
     * dispatch dropped `this` (see the typedef above). Both are what made a
     * real BUDDY/EXIT/SERVER release crash instead of firing OnCommand. */
    EnqueueInputEvent(*(uint **)(in_EAX + 0x10),0,piVar1[1],piVar1[2]);
    (*(WidgetSetStateFn *)(*piVar1 + 4))(piVar1,0,(void *)s_mouse_00551e70);
    AcquireSoundChannel(0);
  }
  return;
}

