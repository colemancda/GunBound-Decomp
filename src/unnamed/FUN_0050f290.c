/* FUN_0050f290 - 0x0050f290 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0050f290(int *param_1)

{
  int *piVar1;
  int *_Memory;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  piVar1 = param_1 + 1;
  piVar2 = (int *)*piVar1;
  while (piVar4 = piVar2, piVar4 != (int *)0x0) {
    _Memory = (int *)piVar4[2];
    piVar2 = (int *)*piVar4;
    (**(code **)(*_Memory + 0x20))();
    if (*(char *)((int)_Memory + 0x1d) != '\0') {
      if (piVar4 == (int *)*piVar1) {
        *piVar1 = *piVar4;
      }
      else {
        *(int *)piVar4[1] = *piVar4;
      }
      if (piVar4 == (int *)param_1[2]) {
        param_1[2] = piVar4[1];
      }
      else {
        *(int *)(*piVar4 + 4) = piVar4[1];
      }
      *piVar4 = param_1[5];
      iVar3 = param_1[3];
      param_1[5] = (int)piVar4;
      param_1[3] = iVar3 + -1;
      if (iVar3 + -1 == 0) {
        PanelManager_ReleasePool();
      }
      (**(code **)(*param_1 + 0x18))();
      WidgetChildArray_Destroy();
      _free(_Memory);
    }
  }
  return;
}

