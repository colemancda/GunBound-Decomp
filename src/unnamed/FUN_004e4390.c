/* FUN_004e4390 - 0x004e4390 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_004e4390(void)

{
  int iVar1;
  int in_EAX;
  char *pcVar2;
  int unaff_ESI;
  int unaff_EDI;
  
  if ((-1 < unaff_EDI) && (iVar1 = *(int *)(unaff_ESI + 0x18), unaff_EDI < iVar1)) {
    if (*(int *)(unaff_ESI + 0x1c) <= in_EAX) {
      in_EAX = *(int *)(unaff_ESI + 0x1c) + -1;
    }
    pcVar2 = (char *)(iVar1 * in_EAX + *(int *)(unaff_ESI + 0x34) + unaff_EDI);
    while( true ) {
      if (in_EAX < 0) {
        return -10000;
      }
      if (*pcVar2 != '\0') break;
      pcVar2 = pcVar2 + -iVar1;
      in_EAX = in_EAX + -1;
    }
    return in_EAX;
  }
  return -10000;
}

