/* PanelManager_DispatchMouseMove - 0x0050f020 in the original binary.
 *
 * CUIPanelManager WM_MOUSEMOVE dispatch: walks the panel list (manager+4)
 * and calls each panel's mouse-move widget virtual. Named 2026-07-18 (WndProc case 0x200).
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Each list node's widget is dispatched through its own vtable slot 1
 * (+4) as __thiscall(this=widget, x, y) - the original loads
 * `mov ecx,[eax+8]` (the node's widget pointer) into ECX right before
 * `call [vtbl+4]` at 0x50f03f-0x50f045, which Ghidra's generic code()
 * cast dropped along with the widget `this`. The result accumulator is
 * NOT an OR: the original does a plain `mov bl,al` each iteration
 * (0x50f047), so the returned value is the LAST node's result, not a
 * sticky "any node handled it" flag as Ghidra's `if (c=='\x01') u=1;`
 * (reading an uninitialized cVar3) implied. */
typedef char (__fastcall *WidgetHitTestFn)(void *thisPtr,int dummyEDX,
                                            undefined4 x,undefined4 y);

undefined1 __thiscall PanelManager_DispatchMouseMove(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  char cVar3;
  undefined1 uVar4;

  puVar2 = *(undefined4 **)(param_1 + 4);
  uVar4 = 0;
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = puVar2 + 2;
    puVar2 = (undefined4 *)*puVar2;
    cVar3 = (*(WidgetHitTestFn *)(*(int *)*puVar1 + 4))
              ((void *)*puVar1,0,param_2,param_3);
    uVar4 = (undefined1)cVar3;
  }
  return uVar4;
}

