/* FUN_0050f840 - 0x0050f840 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0050f840(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_2 + 0x38) - *(int *)(param_2 + 0x3c);
  param_1 = param_1 + *(int *)(param_2 + 0x40);
  iVar2 = iVar1;
  if (param_1 <= iVar1) {
    iVar2 = param_1;
  }
  if (iVar2 < 0) {
    iVar1 = 0;
  }
  else if (param_1 <= iVar1) {
    iVar1 = param_1;
  }
  if (iVar1 != *(int *)(param_2 + 0x40)) {
    *(int *)(param_2 + 0x40) = iVar1;
    if (*(int **)(param_2 + 8) != (int *)0x0) {
      (**(code **)(**(int **)(param_2 + 8) + 0x1c))(0x2000,*(undefined4 *)(param_2 + 0x24),iVar1);
    }
  }
  return;
}

