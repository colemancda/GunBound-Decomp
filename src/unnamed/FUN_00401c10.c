/* FUN_00401c10 - 0x00401c10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00401c10(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int in_EAX;
  int iVar4;
  int unaff_EDI;
  
  iVar2 = *(int *)(*(int *)(in_EAX + 4) + 0x1c);
  iVar4 = 0;
  do {
    if (iVar2 == *(int *)(in_EAX + 4)) {
      return 0;
    }
    iVar3 = *(int *)(iVar2 + 0x10);
    cVar1 = *(char *)(iVar3 + 0x15);
    while (cVar1 == '\0') {
      if (iVar4 == unaff_EDI) {
        return iVar3;
      }
      iVar3 = *(int *)(iVar3 + 0x10);
      iVar4 = iVar4 + 1;
      cVar1 = *(char *)(iVar3 + 0x15);
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
  } while( true );
}

