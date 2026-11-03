/* FUN_00543250 - 0x00543250 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIX (2026-11-03): the g_uiPanelManager atexit stub. 0x543250 is
 * `mov ecx,0xe53c40 / jmp 0x40d150`: `this` = &g_uiPanelManager in ECX,
 * then the thunk to PanelManager_BaseDestructor. The port called the
 * thunk with no argument (its K&R-empty prototype hid it); it now passes
 * &g_uiPanelManager. The static initializer at 0x540dc0 registers this
 * stub (push 0x543250 at 0x540dca).
 */
#include "ghidra_types.h"


void FUN_00543250(void)

{
  PanelManager_BaseDestructorThunk((undefined4 *)&g_uiPanelManager);
  return;
}

