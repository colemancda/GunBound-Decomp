/* HandleActiveObjectMouseMove - 0x004061e0 in the original binary.
 *
 * Mouse-hit-test dispatcher: sole caller is WndProc's WM_MOUSEMOVE handler
 * (0x41023a-0x41023f: `mov edx,esi[mouseY]; mov ecx,edi[mouseX]; mov
 * eax,0xe9be90[registry]; call 0x4061e0`), tracking which active object
 * (see globals.c/ButtonWidget.h - these are CButtonWidget instances) the
 * mouse is currently over, firing enter/leave visual-state callbacks
 * through the found object's own vtable slot 1 (SetState).
 *
 * FIXED (2026-07-13): part of the 5-function mouse-hit-test family (see
 * FindActiveObjectAt.c's header for the full trace of all 5). `in_EAX`
 * (registry) was already correctly identified but unpromoted; ECX/EDX
 * (mouseX/mouseY) were dropped entirely with no placeholder at all -
 * both are threaded straight through, unmodified, into the
 * `FindActiveObjectAt()` call. Promoted all three to explicit parameters.
 */
#include "ghidra_types.h"

/* slot 1 (CButtonWidget::SetState), a real C++ __thiscall - fix the dropped
 * `this` with the __fastcall + dummy-EDX idiom (2026-07-18). */
typedef void (__fastcall *WidgetSetStateFn)(void *thisPtr, int dummyEDX, void *name);


undefined4 HandleActiveObjectMouseMove(void *registry,int mouseX,int mouseY)

{
  int *piVar1;
  int iVar2;
  int in_EAX = (int)registry;
  int *piVar3;

  piVar3 = (int *)FindActiveObjectAt(registry,mouseX,mouseY);
  piVar1 = *(int **)(in_EAX + 8);
  if (piVar1 != piVar3) {
    if ((((piVar1 != (int *)0x0) && (iVar2 = piVar1[9], iVar2 != 3)) && (iVar2 != 4)) &&
       (iVar2 != 5)) {
      FUN_00405e30();
    }
    *(undefined4 *)(in_EAX + 8) = 0;
    if (piVar3 != (int *)0x0) {
      *(int **)(in_EAX + 8) = piVar3;
      if (((*(int **)(in_EAX + 0xc) == piVar3) && (piVar3[9] != 3)) && (piVar3[9] != 5)) {
        (*(WidgetSetStateFn *)(*piVar3 + 4))(piVar3,0,&DAT_00551e78);
      }
      if (((*(int *)(in_EAX + 0xc) == 0) && (iVar2 = piVar3[9], iVar2 != 3)) &&
         ((iVar2 != 4 && (iVar2 != 5)))) {
        (*(WidgetSetStateFn *)(*piVar3 + 4))(piVar3,0,(void *)s_mouse_00551e70);
        AcquireSoundChannel(0);
      }
      return 1;
    }
  }
  return 0;
}

