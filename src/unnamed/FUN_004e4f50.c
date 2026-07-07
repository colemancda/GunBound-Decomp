/* FUN_004e4f50 - 0x004e4f50 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e4f50(undefined4 param_1,int param_2,undefined4 param_3)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = operator_new(0x38);
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    piVar1[2] = param_2;
    piVar1[1] = 0;
    piVar1[3] = 0;
    piVar1[4] = 0;
    *(undefined1 *)(piVar1 + 5) = 0;
    *(undefined1 *)((int)piVar1 + 0x15) = 0;
    piVar1[6] = -1;
    piVar1[7] = 0;
    *(undefined1 *)(piVar1 + 8) = 0;
    piVar1[10] = 0;
    piVar1[0xb] = 0;
    piVar1[9] = -1;
    *piVar1 = (int)&PTR_FUN_00556558;
  }
  iVar2 = FindPreloadedTextureByName(param_3);
  piVar1[7] = iVar2;
  (**(code **)(*piVar1 + 4))(s_normal_00552230);
  RegisterActiveObject();
  return;
}

