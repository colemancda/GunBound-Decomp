/* HandleActiveObjectMouseDown - 0x00406120 in the original binary.
 *
 * Mouse-button-down active-object hit-test: sole caller is WndProc's
 * WM_LBUTTONDOWN handler (case 0x201, 0x4102de and 0x410303 - both call
 * sites), each preceded by `mov edi,0xe9be90[registry]` with mouseX/
 * mouseY unchanged from WndProc's own locals. `piVar2[1] == 1000000`
 * special-cases the hit object's own +4 "layer" field (ButtonWidget.h's
 * m_layer, documented there as "always 0 at every observed call site" -
 * this appears to be the one exception, worth reconciling whenever that
 * class gets its next pass).
 *
 * FIXED (2026-07-13): part of the 5-function mouse-hit-test family (see
 * FindActiveObjectAt.c's header for the full trace of all 5). `unaff_EDI`
 * (registry) was already correctly identified but unpromoted; the
 * incoming ESI/EDX (mouseX/mouseY) were dropped entirely with no
 * placeholder at all - both are threaded straight through, unmodified,
 * into the `FindActiveObjectAt()` call. Promoted all three to explicit
 * parameters.
 */
#include "ghidra_types.h"

/* The pressed active object's vtable slot 1 (CButtonWidget::SetState) is a
 * genuine C++ __thiscall (orig 0x40615a: `mov ecx,eax`(this=object) / `push
 * 0x551e78`(state name) / `call [edx+4]`). Ghidra's `(**(code**)(*piVar2+4))
 * (&DAT_00551e78)` cdecl cast DROPPED `this`, so on a BUDDY/EXIT/SERVER
 * button click SetState ran with a bogus `this`. Fixed with the __fastcall +
 * dummy-EDX idiom (same as WidgetSetModeNameFn in
 * State02_ServerSelect_ProcessPacket.c). */
typedef void (__fastcall *WidgetSetStateFn)(void *thisPtr, int dummyEDX, void *name);


undefined4 HandleActiveObjectMouseDown(void *registry,int mouseX,int mouseY)

{
  int iVar1;
  int *piVar2;
  int unaff_EDI = (int)registry;

  piVar2 = (int *)FindActiveObjectAt(registry,mouseX,mouseY);
  if ((piVar2 != (int *)0x0) && ((*(char *)(unaff_EDI + 0x14) == '\0' || (piVar2[1] == 1000000)))) {
    iVar1 = piVar2[9];
    if ((iVar1 != 3) && ((iVar1 != 4 && (iVar1 != 5)))) {
      *(int **)(unaff_EDI + 0xc) = piVar2;
      (*(WidgetSetStateFn *)(*piVar2 + 4))(piVar2,0,&DAT_00551e78);
    }
    return 1;
  }
  return 0;
}

