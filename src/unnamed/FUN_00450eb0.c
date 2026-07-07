/* FUN_00450eb0 - 0x00450eb0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall
FUN_00450eb0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,char param_5,
            undefined4 param_6,undefined4 param_7)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = *(int *)(*(int *)(param_1 + 4) + 0x1c);
  uVar2 = *(uint *)(iVar3 + 4);
  while( true ) {
    if (0x186a1 < uVar2) goto LAB_00450f11;
    if (uVar2 == 0x186a1) break;
    iVar3 = *(int *)(iVar3 + 0x1c);
    uVar2 = *(uint *)(iVar3 + 4);
  }
  iVar3 = *(int *)(iVar3 + 0x10);
  cVar1 = *(char *)(iVar3 + 0x15);
  while (cVar1 == '\0') {
    FUN_0045db20(iVar3,param_2,param_3,param_6,param_7);
    iVar3 = *(int *)(iVar3 + 0x10);
    cVar1 = *(char *)(iVar3 + 0x15);
  }
LAB_00450f11:
  iVar3 = *(int *)(*(int *)(param_1 + 4) + 0x1c);
  uVar2 = *(uint *)(iVar3 + 4);
  if (uVar2 < 0x186a7) {
LAB_00450f26:
    if (uVar2 != 0x186a6) goto code_r0x00450f28;
    iVar3 = *(int *)(iVar3 + 0x10);
    cVar1 = *(char *)(iVar3 + 0x15);
    while (cVar1 == '\0') {
      if (*(char *)(iVar3 + 0x14) == '\0') {
        FUN_00478cb0(iVar3,param_2,param_3);
      }
      iVar3 = *(int *)(iVar3 + 0x10);
      cVar1 = *(char *)(iVar3 + 0x15);
    }
  }
LAB_00450f65:
  if (param_5 != '\0') {
    iVar3 = *(int *)(*(int *)(param_1 + 4) + 0x1c);
    uVar2 = *(uint *)(iVar3 + 4);
    while (uVar2 < 0x186a4) {
      if (uVar2 == 0x186a3) {
        iVar3 = *(int *)(iVar3 + 0x10);
        cVar1 = *(char *)(iVar3 + 0x15);
        while (cVar1 == '\0') {
          if (*(char *)(iVar3 + 0x14) == '\0') {
            FUN_00499650(iVar3,param_2,param_3,param_4);
          }
          iVar3 = *(int *)(iVar3 + 0x10);
          cVar1 = *(char *)(iVar3 + 0x15);
        }
        break;
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar2 = *(uint *)(iVar3 + 4);
    }
  }
  iVar3 = *(int *)(*(int *)(param_1 + 4) + 0x1c);
  uVar2 = *(uint *)(iVar3 + 4);
  if (uVar2 < 0x30d43) {
    while (uVar2 != 0x30d42) {
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar2 = *(uint *)(iVar3 + 4);
      if (0x30d42 < uVar2) {
        return;
      }
    }
    iVar3 = *(int *)(iVar3 + 0x10);
    cVar1 = *(char *)(iVar3 + 0x15);
    while (cVar1 == '\0') {
      FUN_00477650(iVar3,param_2,param_3,param_4);
      iVar3 = *(int *)(iVar3 + 0x10);
      cVar1 = *(char *)(iVar3 + 0x15);
    }
  }
  return;
code_r0x00450f28:
  iVar3 = *(int *)(iVar3 + 0x1c);
  uVar2 = *(uint *)(iVar3 + 4);
  if (0x186a6 < uVar2) goto LAB_00450f65;
  goto LAB_00450f26;
}

