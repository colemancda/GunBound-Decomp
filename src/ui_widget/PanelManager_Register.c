/* PanelManager_Register - 0x0050eea0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void PanelManager_Register(int param_1)

{
  int *piVar1;
  int in_EAX;
  int iVar2;
  
  piVar1 = (int *)(in_EAX + 4);
  if (*(char *)(param_1 + 5) == '\0') {
    iVar2 = FUN_0050f350(&param_1,*(undefined4 *)(in_EAX + 8),0);
    if (*(int **)(in_EAX + 8) != (int *)0x0) {
      **(int **)(in_EAX + 8) = iVar2;
      *(int *)(in_EAX + 8) = iVar2;
      return;
    }
    *piVar1 = iVar2;
    *(int *)(in_EAX + 8) = iVar2;
    return;
  }
  iVar2 = FUN_0050f350(&param_1,0,*piVar1);
  if (*piVar1 != 0) {
    *(int *)(*piVar1 + 4) = iVar2;
    *piVar1 = iVar2;
    return;
  }
  *(int *)(in_EAX + 8) = iVar2;
  *piVar1 = iVar2;
  return;
}

