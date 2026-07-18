/* PanelManager_DispatchRightMouseDown - 0x0050f1f0 in the original binary.
 *
 * CUIPanelManager WM_RBUTTONDOWN dispatch over the panel list.
 * Named 2026-07-18 (WndProc case 0x203).
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"

/* Panel widget virtual: this in ECX, x/y on the stack, returns char. Ghidra
 * dropped `this` via the generic code** cdecl cast - same erased-__thiscall
 * fix as PanelManager_DispatchMouseMove (2026-07-18). */
typedef char (__fastcall *WidgetHitTestFn)(void *thisPtr, int dummyEDX,
                                            undefined4 x, undefined4 y);


undefined1 __thiscall PanelManager_DispatchRightMouseDown(int param_1,undefined4 param_2,undefined4 param_3)

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
    cVar3 = (*(WidgetHitTestFn *)(*(int *)*puVar1 + 0x10))((void *)*puVar1,0,param_2,param_3);
    if (cVar3 == '\x01') {
      uVar4 = 1;
    }
  }
  return uVar4;
}

