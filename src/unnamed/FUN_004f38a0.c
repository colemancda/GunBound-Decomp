/* FUN_004f38a0 - 0x004f38a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004f38a0(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  if (*(char *)(param_1 + 0xdc) == '\x01') {
    puVar2 = (undefined4 *)FUN_004f1f50();
    puVar4 = (undefined4 *)(param_1 + 0x120);
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar2 = (undefined4 *)FUN_004f1f50();
    puVar4 = (undefined4 *)(param_1 + 0x160);
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
  }
  for (piVar1 = *(int **)(param_1 + 0xd4); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[0x36]) {
    (**(code **)(*piVar1 + 0x10))();
  }
  return;
}

