/* FUN_0040cea0 - 0x0040cea0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_0040cea0(undefined4 param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int in_EAX;
  int unaff_ESI;
  
  iVar2 = *(int *)(*(int *)(in_EAX + 4) + 0x1c);
  do {
    if (iVar2 == *(int *)(in_EAX + 4)) {
      return 0;
    }
    iVar3 = *(int *)(iVar2 + 0x10);
    cVar1 = *(char *)(iVar3 + 0x15);
    while (cVar1 == '\0') {
      if ((((*(int *)(iVar3 + 0x38) < unaff_ESI) &&
           (unaff_ESI < *(int *)(iVar3 + 0x40) + *(int *)(iVar3 + 0x38))) &&
          (*(int *)(iVar3 + 0x3c) < param_2)) &&
         (param_2 < *(int *)(iVar3 + 0x44) + *(int *)(iVar3 + 0x3c))) {
        return iVar3;
      }
      iVar3 = *(int *)(iVar3 + 0x10);
      cVar1 = *(char *)(iVar3 + 0x15);
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
  } while( true );
}

