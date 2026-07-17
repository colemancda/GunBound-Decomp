/* FUN_0050f260 - 0x0050f260 in the original binary.
 *
 * The panel manager's WM_KEYUP dispatch - the exact sibling of
 * FUN_0050f230 (WM_KEYDOWN) but calling each panel's key-up virtual
 * (vtable slot 6, +0x18). Same dropped-`this` + dropped-return bug and
 * fix - see FUN_0050f230.c's header. Confirmed at orig 0x50f272-0x50f27d
 * (`mov ecx,[eax+8]; push edi; call [eax+0x18]; cmp al,1`). Also fixed
 * its WndProc call site, which passed only the VK and dropped the
 * manager `this` (WndProc.c's WM_KEYUP case).
 */
#include "ghidra_types.h"

/* Real C++ __thiscall callee (CWidget::DispatchMouse), so __fastcall +
 * dummy-EDX idiom - see FUN_0050f230.c. */
typedef undefined1 (__fastcall *PanelKeyHandlerFn)(void *thisPtr, int dummyEDX, undefined4 key);

undefined1 __thiscall FUN_0050f260(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined1 cVar3;
  undefined1 uVar4;

  puVar2 = *(undefined4 **)(param_1 + 4);
  uVar4 = 0;
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = puVar2 + 2;
    puVar2 = (undefined4 *)*puVar2;
    cVar3 = (*(PanelKeyHandlerFn *)(*(int *)*puVar1 + 0x18))((void *)*puVar1,0,param_2);
    if (cVar3 == '\x01') {
      uVar4 = 1;
    }
  }
  return uVar4;
}

