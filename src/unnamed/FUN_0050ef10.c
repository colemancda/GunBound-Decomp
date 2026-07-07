/* FUN_0050ef10 - 0x0050ef10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_0050ef10(int *param_1)

{
  int *piVar1;
  void *_Memory;
  int *piVar2;
  int iVar3;
  int in_EAX;
  int *piVar4;
  int unaff_EBX;
  
  piVar1 = param_1 + 1;
  piVar4 = (int *)*piVar1;
  if (piVar4 != (int *)0x0) {
    while( true ) {
      _Memory = (void *)piVar4[2];
      piVar2 = (int *)*piVar4;
      if ((*(int *)((int)_Memory + 0x20) == in_EAX) && (*(int *)((int)_Memory + 0x24) == unaff_EBX))
      break;
      piVar4 = piVar2;
      if (piVar2 == (int *)0x0) {
        return;
      }
    }
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
      FUN_00509fd0();
    }
    (**(code **)(*param_1 + 0x18))();
    FUN_0050e560();
    _free(_Memory);
  }
  return;
}

