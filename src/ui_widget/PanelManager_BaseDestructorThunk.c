/* PanelManager_BaseDestructorThunk - 0x0040d150 in the original binary.
 *
 * NAMED 2026-10-31 (was thunk_FUN_0050ee00). The bare `jmp 0x50ee00`
 * forward to PanelManager_BaseDestructor. Its two callers are the
 * derived panel manager's scalar-deleting destructor 0x507e10 (call at
 * 0x507e13) and the g_uiPanelManager atexit stub 0x543250 (jmp at
 * 0x543255). Thunk-suffix naming per CStringPair_DestroyThunk and
 * WorkerThreadProcThunk.
 *
 * FIX (2026-11-03): now a real thunk. The whole function is
 * `0x40d150 jmp 0x50ee00` (5 bytes, then int3 padding), so `this`
 * arrives in ECX and goes straight on to PanelManager_BaseDestructor in
 * ECX. The port used to inline a copy of the destructor body, and that
 * copy still carried the SEH-prologue artifact - `uStack_c =
 * *unaff_FS_OFFSET; *unaff_FS_OFFSET = &uStack_c;` through an
 * uninitialised pointer (the fs:[0] link of 0x50ee00-0x50ee0e) - which
 * PanelManager_BaseDestructor's own copy had already stripped. It now
 * forwards `this` to PanelManager_BaseDestructor, both __fastcall.
 */
#include "ghidra_types.h"


void __fastcall PanelManager_BaseDestructorThunk(undefined4 *param_1)

{
  PanelManager_BaseDestructor(param_1);
  return;
}
