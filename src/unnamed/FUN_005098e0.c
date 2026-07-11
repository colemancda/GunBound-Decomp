/* FUN_005098e0 - 0x005098e0 in the original binary.
 *
 * BRING-UP BYPASS (stubbed to a no-op): sweeps g_uiPanelManager's
 * pooled-entry free list, releasing every entry older than param_1
 * ticks (sole caller ChangeGameState.c passes 10000). in_EAX (the
 * manager object) arrives via a dropped EAX register - orig 0x412349:
 * `mov eax, 0xe53c40` (DAT_00e53c40, renamed g_uiPanelManager) before
 * the call - promoted to an explicit parameter.
 *
 * g_uiPanelManager is currently a 1-byte placeholder scalar (real size/
 * layout not yet recovered - it's part of the Widget/PanelManager
 * subsystem another agent is actively migrating, see
 * WidgetChildArray_Destroy/PanelManager_ReleasePool). Walking its list
 * fields at +4/+8/+0x14 against that placeholder reads garbage
 * pointers and crashes (confirmed: fault reading *(_Memory+0x24) with
 * _Memory from the corrupt list). Stubbed until that subsystem's real
 * struct lands, to avoid colliding with its in-progress work.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_005098e0(int in_EAX, int param_1)

{
  (void)in_EAX;
  (void)param_1;
  return;
}

