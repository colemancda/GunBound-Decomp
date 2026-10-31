/* PanelManager_BaseDestructorThunk - 0x0040d150 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-31 (was thunk_FUN_0050ee00). The bare `jmp 0x50ee00`
 * forward to PanelManager_BaseDestructor. Its two callers are the
 * derived panel manager's scalar-deleting destructor 0x507e10 (call at
 * 0x507e13) and the g_uiPanelManager atexit stub 0x543250 (jmp at
 * 0x543255). Thunk-suffix naming per CStringPair_DestroyThunk and
 * WorkerThreadProcThunk.
 *
 * (thunk_FUN_0050ee00 / FUN_0050ee00 below are now this function /
 * PanelManager_BaseDestructor.)
 * `thunk_FUN_0050ee00` - confirmed via objdump this is a PURE
 * `jmp 0x50ee00` tail-jump (no logic of its own at all), so it's byte-
 * for-byte the same function as FUN_0050ee00. See that file's own
 * header for the CI COMPILE-ERR FIX (2026-07-30) applied identically
 * here.
 *
 * NOTE (2026-10-31, not fixed here): this port inlines the target's
 * body instead of forwarding, and it still carries the SEH prologue
 * write through the uninitialised `unaff_FS_OFFSET` that
 * PanelManager_BaseDestructor's copy has had stripped.
 */
#include "ghidra_types.h"


void __fastcall PanelManager_BaseDestructorThunk(undefined4 *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  void *_Memory;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  puStack_8 = &LAB_0053778b;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  *param_1 = &PTR_FUN_00557f80;
  uStack_4 = 0;
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
  *unaff_FS_OFFSET = uStack_c;
  return;
}

