/* FUN_004f37b0 - 0x004f37b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004f37b0(int *param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined4 unaff_retaddr;
  
  piVar1 = param_1 + 0x38;
  if (param_1[0x32] == 0) {
    piVar3 = piVar1;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar3 = 0;
      piVar3 = piVar3 + 1;
    }
    param_1[0x47] = 0x3f800000;
    param_1[0x42] = 0x3f800000;
    param_1[0x3d] = 0x3f800000;
    *piVar1 = 0x3f800000;
  }
  else {
    FUN_004e95c0(param_1[0x33],piVar1);
  }
  if (param_1[0x34] == 0) {
    FUN_004f3440();
    FUN_004f1f50();
    FUN_004f2240();
  }
  else {
    FUN_004f1f50();
    FUN_004f2240();
    param_1[0x26] = param_1[0x44];
    param_1[0x27] = param_1[0x45];
    param_1[0x28] = param_1[0x46];
  }
  if (param_1[0x31] != 0) {
    FUN_004f3540();
  }
  (**(code **)(*param_1 + 4))(param_1[0x33]);
  for (piVar1 = (int *)param_1[0x35]; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[0x36]) {
    (**(code **)(*piVar1 + 0xc))(unaff_retaddr);
  }
  return;
}

