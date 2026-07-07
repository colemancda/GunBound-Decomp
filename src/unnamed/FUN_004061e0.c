/* FUN_004061e0 - 0x004061e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004061e0(void)

{
  int *piVar1;
  int iVar2;
  int in_EAX;
  int *piVar3;
  
  piVar3 = (int *)FUN_0040cea0();
  piVar1 = *(int **)(in_EAX + 8);
  if (piVar1 != piVar3) {
    if ((((piVar1 != (int *)0x0) && (iVar2 = piVar1[9], iVar2 != 3)) && (iVar2 != 4)) &&
       (iVar2 != 5)) {
      FUN_00405e30();
    }
    *(undefined4 *)(in_EAX + 8) = 0;
    if (piVar3 != (int *)0x0) {
      *(int **)(in_EAX + 8) = piVar3;
      if (((*(int **)(in_EAX + 0xc) == piVar3) && (piVar3[9] != 3)) && (piVar3[9] != 5)) {
        (**(code **)(*piVar3 + 4))(&DAT_00551e78);
      }
      if (((*(int *)(in_EAX + 0xc) == 0) && (iVar2 = piVar3[9], iVar2 != 3)) &&
         ((iVar2 != 4 && (iVar2 != 5)))) {
        (**(code **)(*piVar3 + 4))(s_mouse_00551e70);
        FUN_004ee9b0(0);
      }
      return 1;
    }
  }
  return 0;
}

