/* FUN_005099b0 - 0x005099b0 in the original binary.
 *
 * BRING-UP BYPASS (stubbed to a no-op): walks g_uiPanelManager's list at
 * +4, clearing byte +0x1e of each entry's [2] field (likely a
 * "dirty"/"hovered" flag reset between game states). in_EAX arrives via
 * a dropped EAX register - orig 0x412455: `mov eax, 0xe53c40`
 * (DAT_00e53c40 / g_uiPanelManager), same call sequence and same
 * not-yet-recovered PanelManager struct as FUN_005098e0 (see that
 * file's comment) - stubbed for the same reason, pending that
 * subsystem's real layout.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_005099b0(void)

{
  return;
}

