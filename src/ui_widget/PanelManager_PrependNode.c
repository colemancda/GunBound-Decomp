/* PanelManager_PrependNode - 0x0050f350 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * `in_EAX` here is the SAME dropped manager pointer already documented
 * (not yet fixed) on this function's only caller, PanelManager_Register
 * - confirmed via objdump that Register's own call site does `mov
 * eax,esi` (its own unresolved `in_EAX`, offset +4) right before
 * `call PanelManager_PrependNode`, i.e. this is one bug split across
 * two functions, not a separate one. See PanelManager_Register.c's
 * header for the full trace and why it's deferred pending a manager-
 * class reconstruction.
 */
#include "ghidra_types.h"


undefined4 PanelManager_PrependNode(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int in_EAX;
  
  PanelManager_GrowNodePool();
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

