/* FUN_0043dd40 - 0x0043dd40 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_0043dd40(undefined4 param_1)

{
  char cVar1;
  char *in_EAX;
  int iVar2;
  char *pcVar3;
  
  iVar2 = FUN_0043e060();
  if (iVar2 == 0) {
    iVar2 = FUN_0043de70(param_1);
    return iVar2;
  }
  pcVar3 = in_EAX;
  if (in_EAX != (char *)0x0) {
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    FUN_004056c0(iVar2 + 4,in_EAX);
    return iVar2;
  }
  FUN_004056c0(iVar2 + 4,0);
  return iVar2;
}

