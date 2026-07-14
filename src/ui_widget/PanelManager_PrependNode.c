/* PanelManager_PrependNode - 0x0050f350 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-14): `in_EAX` is the same dropped manager pointer
 * already fixed on this function's only caller, PanelManager_Register -
 * confirmed via objdump at PrependNode's real entry (0x50f350-0x50f351):
 * `mov esi,eax` (manager) right at entry. Promoted to a real leading
 * parameter, forwarded on into PanelManager_GrowNodePool (its own
 * dropped `unaff_ESI` fixed alongside this).
 *
 * NOTE: the value Register passes here is `manager+4` (its own local
 * `piVar1`, i.e. the manager's list-head slot address), NOT the raw
 * manager pointer - confirmed via objdump at Register's own real body
 * (0x50eea0: `lea esi,[eax+4]` right at entry, `mov eax,esi` immediately
 * before both of its `call 0x50f350` sites). This function's own +0xc/
 * +0x10/+0x14 offsets (and GrowNodePool's) are all relative to that
 * already-shifted base, not the manager object's true start.
 */
#include "ghidra_types.h"


undefined4 PanelManager_PrependNode(void *manager,undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int in_EAX;

  in_EAX = (int)manager;
  PanelManager_GrowNodePool(manager);
  puVar1 = *(undefined4 **)(in_EAX + 0x10);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[2] = *param_1;
  }
  *(undefined4 *)(in_EAX + 0x10) = *puVar1;
  puVar1[1] = param_2;
  *puVar1 = param_3;
  *(int *)(in_EAX + 8) = *(int *)(in_EAX + 8) + 1;
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

