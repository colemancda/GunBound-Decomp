/* PanelManager_Register - 0x0050eea0 in the original binary.
 *
 * __stdcall confirmed by the original's epilogue (`ret 0x4` on every
 * return path, callee cleans up its one 4-byte argument) - a plain
 * declaration here would default to __cdecl and leave a caller-side
 * stack-cleanup mismatch.
 *
 * in_EAX is a genuinely separate dropped register from param_1 (orig
 * 0x50eeaa: `leal 0x4(%eax), %esi` uses a DIFFERENT %eax than the one
 * holding param_1), not yet recovered - deferred since 17+ call sites
 * across src/ui_widget/ and the actively-migrating src/cxx/Panel.cpp
 * would each need tracing to confirm what object is in EAX at the call.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __stdcall PanelManager_Register(int param_1)

{
  int *piVar1;
  int in_EAX;
  int iVar2;
  
  piVar1 = (int *)(in_EAX + 4);
  if (*(char *)(param_1 + 5) == '\0') {
    iVar2 = PanelManager_PrependNode(&param_1,*(undefined4 *)(in_EAX + 8),0);
    if (*(int **)(in_EAX + 8) != (int *)0x0) {
      **(int **)(in_EAX + 8) = iVar2;
      *(int *)(in_EAX + 8) = iVar2;
      return;
    }
    *piVar1 = iVar2;
    *(int *)(in_EAX + 8) = iVar2;
    return;
  }
  iVar2 = PanelManager_PrependNode(&param_1,0,*piVar1);
  if (*piVar1 != 0) {
    *(int *)(*piVar1 + 4) = iVar2;
    *piVar1 = iVar2;
    return;
  }
  *(int *)(in_EAX + 8) = iVar2;
  *piVar1 = iVar2;
  return;
}

