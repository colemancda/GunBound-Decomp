/* FUN_00443700 - 0x00443700 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_00443700(undefined4 *param_1,int *param_2,int *param_3,int regEsi)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  int *piVar4;
  
  piVar4 = param_3;
  puVar3 = param_1;
  piVar1 = *(int **)(regEsi + 4);
  piVar2 = param_2;
  if ((param_2 == (int *)*piVar1) && (param_3 == piVar1)) {
    FUN_00443ba0(piVar1[1]);
    *(int *)(*(int *)(regEsi + 4) + 4) = *(int *)(regEsi + 4);
    *(undefined4 *)(regEsi + 8) = 0;
    *(undefined4 *)*(undefined4 *)(regEsi + 4) = *(undefined4 *)(regEsi + 4);
    *(int *)(*(int *)(regEsi + 4) + 8) = *(int *)(regEsi + 4);
    *puVar3 = **(undefined4 **)(regEsi + 4);
    return puVar3;
  }
  while (piVar2 != piVar4) {
    param_2 = piVar2;
    FUN_00443780();
    FUN_00443840(regEsi,&param_1,piVar2);
    piVar2 = param_2;
  }
  *puVar3 = piVar2;
  return puVar3;
}

