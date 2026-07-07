/* FUN_004e8eb0 - 0x004e8eb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004e8eb0(undefined4 param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  piVar4 = (int *)*param_2;
  if (*(char *)((int)piVar4 + 0xf) != '\0') {
    *param_2 = piVar4[2];
    return;
  }
  iVar2 = *piVar4;
  if (*(char *)(iVar2 + 0xf) == '\0') {
    cVar1 = *(char *)(*(int *)(iVar2 + 8) + 0xf);
    iVar3 = *(int *)(iVar2 + 8);
    while (cVar1 == '\0') {
      cVar1 = *(char *)(*(int *)(iVar3 + 8) + 0xf);
      iVar2 = iVar3;
      iVar3 = *(int *)(iVar3 + 8);
    }
    *param_2 = iVar2;
    return;
  }
  piVar4 = (int *)piVar4[1];
  if (*(char *)((int)piVar4 + 0xf) == '\0') {
    do {
      if (*param_2 != *piVar4) break;
      *param_2 = (int)piVar4;
      piVar4 = (int *)piVar4[1];
    } while (*(char *)((int)piVar4 + 0xf) == '\0');
    if (*(char *)((int)piVar4 + 0xf) == '\0') {
      *param_2 = (int)piVar4;
    }
  }
  return;
}

