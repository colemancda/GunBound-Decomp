/* FUN_00402020 - 0x00402020 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_00402020(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  short unaff_DI;
  
  iVar4 = 0;
  for (iVar2 = *(int *)(*(int *)(param_1 + 4) + 0x1c); iVar2 != *(int *)(param_1 + 4);
      iVar2 = *(int *)(iVar2 + 0x1c)) {
    iVar3 = *(int *)(iVar2 + 0x10);
    cVar1 = *(char *)(iVar3 + 0x15);
    while (cVar1 == '\0') {
      if ((*(char *)(iVar3 + 0x30) == '\x12') && (unaff_DI == *(short *)(iVar3 + 0x31))) {
        iVar4 = iVar4 + 1;
      }
      iVar3 = *(int *)(iVar3 + 0x10);
      cVar1 = *(char *)(iVar3 + 0x15);
    }
  }
  return iVar4;
}

