/* FUN_0050f230 - 0x0050f230 in the original binary.
 *
 * The panel manager's WM_KEYDOWN dispatch: walks the registered panel
 * list (manager+4, nodes chained via +0, panel object at node+8) and
 * calls each panel's key-input virtual (vtable slot 5, +0x14) with the
 * VK code, OR-ing a "handled" flag from each panel's return value.
 * Called from WndProc's WM_KEYDOWN case.
 *
 * DROPPED-`this` + DROPPED-RETURN FIX (2026-07-17): Ghidra emitted the
 * per-panel call as `(**(code**)(...))(param_2)` - passing ONLY the VK
 * and no `this`, and reading an uninitialised `cVar3` in place of the
 * call's return value. Confirmed at orig 0x50f242-0x50f24d: `mov ecx,
 * [eax+8]` loads the panel object into ECX (the __thiscall `this`),
 * `push edi` pushes the VK, `call [eax+0x14]`, then `cmp al,1` tests the
 * returned handled-flag. Left unfixed, `this` came through as the VK
 * value itself (0xd for Enter), so the panel handler dereferenced
 * *(0x0000000d + field) - the write-to-0x0000000D / wild-jump crash the
 * moment a key was pressed at ServerSelect. Pass the panel object as
 * the explicit leading `this` (ghidra_types.h erases __thiscall to
 * and capture the return. The panel's slot-5 target is a real C++
 * __thiscall method (CWidget::DispatchKey, `this` in ECX, one stack arg,
 * `ret 4`), NOT a cdecl-with-explicit-this C port, so it must be called
 * with the __fastcall + literal-0 dummy-EDX idiom (ghidra_types.h keeps
 * __fastcall real under MSVC but erases __thiscall) - same pattern as
 * WndProc.c's StateSlot6DispatchFn. `this` -> ECX, dummy -> EDX, VK ->
 * the single stack slot the callee cleans.
 */
#include "ghidra_types.h"

typedef undefined1 (__fastcall *PanelKeyHandlerFn)(void *thisPtr, int dummyEDX, undefined4 key);

undefined1 __thiscall FUN_0050f230(int param_1,undefined4 param_2)

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
    cVar3 = (*(PanelKeyHandlerFn *)(*(int *)*puVar1 + 0x14))((void *)*puVar1,0,param_2);
    if (cVar3 == '\x01') {
      uVar4 = 1;
    }
  }
  return uVar4;
}

