/* FUN_0050f060 - 0x0050f060 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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

char __thiscall FUN_0050f060(int param_1,undefined4 param_2,undefined4 param_3)

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
              Widget_ClearPressedRecursive();
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
      Widget_ClearPressedRecursive();
      uVar6 = uVar6 + 1;
    } while (uVar6 < (uint)piVar1[4]);
  }
LAB_0050f13f:
                    /* WARNING: Subroutine does not return */
  ThrowCxxException(0x80070057);
}

