/* PanelManager_BaseDispatchMouseDown - 0x0050f060 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NAMED 2026-10-31 (was FUN_0050f060). Slot 2 of the base panel-manager
 * vtable 0x557f80 - the one PanelManager_BaseDestructor stores - whose
 * other slots are the PanelManager_Dispatch* family (1 MouseMove,
 * 3 MouseUp, 4 RightMouseDown, 5 RightMouseUp, 7 KeyDown, 8 KeyUp).
 * g_uiPanelManager's own vtable 0x557cfc overrides slot 2 with
 * PanelManager_DispatchMouseDown (0x507ea0), which calls this
 * (0x507eab) and falls back to TextEntry_RestoreChatInput when it
 * returns 0 - the derived override wrapping its base member. "Base"
 * marks that relation, as in PanelManager_BaseDestructor and the
 * tree's CMobile_BaseDestructor; the body offers the click to each
 * managed panel's slot 2 (CWidget::OnMouseDown) and moves the panel
 * that takes it to the list head when its +5 byte is set.
 *
 * Widget_ClearPressedRecursive CHILD RECOVERED (2026-10-30): both loops
 * (0x50f09e-0x50f0a4 and 0x50f11a-0x50f120) are `mov eax,[esi+0xc] /
 * mov ecx,[eax+edi*4] / call 0x50e790`, ESI = the panel (piVar1), so each
 * call takes child[i] in ECX. The port called it with nothing.
 */
#include "ghidra_types.h"

/* The per-panel WM_LBUTTONDOWN hit-test/dispatch: vtable slot 2
 * (CWidget::OnMouseDown, this in ECX, x/y on the stack, returns char).
 * Ghidra rendered it as the generic `(**(code**)(*piVar1+8))(x,y)` cdecl
 * cast, which DROPS `this` (the widget) - so the C++ widget method ran with
 * `this` == its own vtable pointer and faulted writing m_focused (this+4)
 * into rdata on the first BUDDY/EXIT/SERVER-button click. Same erased-
 * __thiscall class as PanelManager_DispatchMouseMove's WidgetHitTestFn;
 * fixed with the __fastcall + dummy-EDX idiom, and the dropped char return
 * (orig 0x50f0c4 `test al,al`) is captured too. */
typedef char (__fastcall *WidgetMouseDownFn)(void *thisPtr, int dummyEDX,
                                             undefined4 x, undefined4 y);

char __thiscall PanelManager_BaseDispatchMouseDown(int param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  char cVar4;
  char cVar5;
  uint uVar6;
  
  cVar5 = '\0';
  piVar3 = *(int **)(param_1 + 4);
  while( true ) {
    do {
      while( true ) {
        while( true ) {
          if (piVar3 == (int *)0x0) {
            return cVar5;
          }
          piVar1 = (int *)piVar3[2];
          piVar2 = (int *)*piVar3;
          if (cVar5 != '\x01') break;
          uVar6 = 0;
          *(undefined1 *)(piVar1 + 1) = 0;
          piVar3 = piVar2;
          if (piVar1[4] != 0) {
            if (piVar1[4] == 0) goto LAB_0050f13f;
            do {
              Widget_ClearPressedRecursive(*(int *)(piVar1[3] + uVar6 * 4));
              uVar6 = uVar6 + 1;
            } while (uVar6 < (uint)piVar1[4]);
          }
        }
        cVar4 = (*(WidgetMouseDownFn *)(*piVar1 + 8))((void *)piVar1,0,param_2,param_3);
        if (cVar4 == '\0') break;
        if ((*(char *)((int)piVar1 + 5) != '\0') && (piVar3 != *(int **)(param_1 + 4))) {
          if (*piVar3 == 0) {
            *(int *)(param_1 + 8) = piVar3[1];
          }
          else {
            *(int *)(*piVar3 + 4) = piVar3[1];
          }
          *(int *)piVar3[1] = *piVar3;
          *(int **)(*(int *)(param_1 + 4) + 4) = piVar3;
          *piVar3 = *(int *)(param_1 + 4);
          piVar3[1] = 0;
          *(int **)(param_1 + 4) = piVar3;
        }
        cVar5 = '\x01';
        piVar3 = piVar2;
      }
      uVar6 = 0;
      *(undefined1 *)(piVar1 + 1) = 0;
      piVar3 = piVar2;
    } while (piVar1[4] == 0);
    if (piVar1[4] == 0) break;
    do {
      Widget_ClearPressedRecursive(*(int *)(piVar1[3] + uVar6 * 4));
      uVar6 = uVar6 + 1;
    } while (uVar6 < (uint)piVar1[4]);
  }
LAB_0050f13f:
                    /* WARNING: Subroutine does not return */
  ThrowCxxException(0x80070057);
}

