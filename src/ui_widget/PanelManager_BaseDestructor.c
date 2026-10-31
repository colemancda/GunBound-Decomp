/* PanelManager_BaseDestructor - 0x0050ee00 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NAMED 2026-10-31 (was FUN_0050ee00). The destructor of the panel
 * manager's base class: it stores the base vtable 0x557f80 (0x50ee1d),
 * the table whose slots are the PanelManager_Dispatch* family, then
 * drains the panel list - WidgetChildArray_Destroy and free on each
 * panel - and releases the node pool with PanelManager_ReleasePool.
 * Its callers are the base scalar-deleting destructor 0x50ede0 (slot 0
 * of 0x557f80, `call 0x50ee00` at 0x50ede3) and, through the
 * `jmp 0x50ee00` thunk at 0x40d150, the derived one 0x507e10 (slot 0 of
 * g_uiPanelManager's 0x557cfc) and the atexit stub 0x543250, which is
 * `mov ecx,0xe53c40` (&g_uiPanelManager) / `jmp 0x40d150` and which the
 * static initializer at 0x540dc0 registers (push 0x543250 at 0x540dca)
 * right after constructing g_uiPanelManager with 0x507dc0. The
 * <Class>_BaseDestructor form follows CMobile_BaseDestructor and
 * CGameState_BaseDestructor.
 *
 * (FUN_0050f290 below is now PanelManager_Update. The
 * `thunk_FUN_0040d150` below means thunk_FUN_0050ee00, the 0x40d150
 * thunk.)
 *
 * CI COMPILE-ERR FIX (2026-07-30): PanelManager_ReleasePool/
 * WidgetChildArray_Destroy were given real 1-param prototypes in an
 * earlier pass (see FUN_0050f290.c's header) but this file's three call
 * sites were never updated. Confirmed via objdump (orig 0x50ee62/
 * 0x50ee6f/0x50ee89): both PanelManager_ReleasePool calls use
 * `this`=`param_1+4` (byte offset - `param_1+1` in this file's own
 * undefined4* indexing), WidgetChildArray_Destroy uses `this`=`_Memory`
 * (already correctly computed a few lines above, just never threaded
 * through). `thunk_FUN_0040d150` (src/unnamed/FUN_0040d150.c) is a pure
 * `jmp 0x50ee00` tail-jump to this exact function - same fix applied
 * there identically.
 */
#include "ghidra_types.h"


void __fastcall PanelManager_BaseDestructor(undefined4 *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  void *_Memory;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053778b) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  *param_1 = &PTR_FUN_00557f80;
  local_4 = 0;
  if (param_1[3] != 0) {
    do {
      puVar2 = (undefined4 *)param_1[2];
      puVar3 = (undefined4 *)puVar2[1];
      _Memory = (void *)puVar2[2];
      param_1[2] = puVar3;
      if (puVar3 == (undefined4 *)0x0) {
        param_1[1] = 0;
      }
      else {
        *puVar3 = 0;
      }
      *puVar2 = param_1[5];
      param_1[5] = puVar2;
      piVar1 = param_1 + 3;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 == 0) {
        PanelManager_ReleasePool(param_1 + 1);
      }
      if (_Memory != (void *)0x0) {
        WidgetChildArray_Destroy((undefined4 *)_Memory);
        _free(_Memory);
      }
    } while (param_1[3] != 0);
  }
  PanelManager_ReleasePool(param_1 + 1);
  return;
}

