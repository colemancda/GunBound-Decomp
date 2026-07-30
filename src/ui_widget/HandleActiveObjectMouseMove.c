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
 *
 * SetButtonStateByIndex CALL-SITE FIX (2026-07-30): the hover-out dispatch
 * (`piVar1` losing hover) was calling `SetButtonStateByIndex()` with zero args -
 * confirmed via objdump (orig 0x40620a-0x40620c) that ECX (still
 * `piVar1` here) and EAX=0 are its real `this`/stateIndex args. This
 * fires on every mouse-move that leaves a previously-hovered widget, so
 * the dropped `this` (reading garbage, then dereferencing it as a
 * vtable pointer) crashed live the first time any button's hover state
 * actually got exercised in this bring-up - reproduced via the AVATAR
 * button, but not specific to it. See SetButtonStateByIndex.c's own header. This
 * ALONE did not fix the crash - see the next entry for the real cause.
 *
 * AcquireSoundChannel CALL-SITE FIX (2026-07-30): the hover-IN dispatch's
 * `AcquireSoundChannel(0)` was dropping that function's own real 1st
 * argument (a `.xes` sound-name string). Confirmed via objdump (orig
 * 0x406267-0x406273): `mov eax,[esi+0x48]` (esi=piVar3, +0x48=
 * CButtonWidget::m_unk48), `mov edi,[eax*8+0x56d0f8]` - a 2-entry
 * {selectSound,pushSound} table (see globals.c's g_buttonSoundNameTable) - then
 * `push 0x0; call AcquireSoundChannel`. Diagnostic instrumentation this
 * session confirmed the vtable dispatch above (SetState) and its whole
 * string table were already 100% correct and uncorrupted - the crash
 * only appeared AFTER that, inside AcquireSoundChannel, once it walked
 * `unaff_EDI` as a string: with no real argument supplied, EDI held
 * whatever WndProc's own prologue had left in it (0x200/WM_MOUSEMOVE,
 * the message code itself - explains why every crash dump this session
 * showed EDI=0x200 no matter which button was hovered), and walking
 * that as a "string" then feeding the resulting garbage into a nested
 * vtable dispatch (see AcquireSoundChannel.c's own header) is what
 * actually jumped into unrelated stack memory. `piVar3[18]` is m_unk48;
 * every State03_GameRoomList button passes CreateButtonWidget's arg11=0,
 * so this always resolves to g_buttonSoundNameTable[0] = "bselect1.xes".
 *
 * NOTE: this fix is real and independently confirmed (temporary
 * diagnostic instrumentation showed AcquireSoundChannel now returning
 * cleanly, string table 100% intact) but it did NOT resolve the live
 * AVATAR/BUDDY hover crash - re-tested after this fix, byte-identical
 * crash still reproduces (EIP=0x76fb0c, EDI=0x200). Also ruled out this
 * session: WndProc's OTHER WM_MOUSEMOVE dispatch, PanelManager_
 * DispatchMouseMove (walked its whole panel list with the same kind of
 * instrumentation - every panel's OnMouseMove returns cleanly, 0). The
 * real crash site is somewhere else entirely - not proven to even be
 * WM_MOUSEMOVE-triggered at all, despite EDI=0x200 in every crash dump
 * (that may just be stale/leftover, not causal). See
 * bringup-frontier-mouse-hittest.md memory for the full ruled-out list.
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
      SetButtonStateByIndex(piVar1,0);
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
        AcquireSoundChannel((char *)g_buttonSoundNameTable[piVar3[18] * 2],0);
      }
      return 1;
    }
  }
  return 0;
}
