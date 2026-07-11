/* FindStringNoCase - 0x00401610 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FindStringNoCase(void)

{
  int iVar1;
  char *unaff_EBX;
  int iVar2;
  int *unaff_EDI;
  
  iVar2 = 0;
  if (0 < *unaff_EDI) {
    do {
      iVar1 = __stricmp(unaff_EBX,*(char **)(unaff_EDI[1] + iVar2 * 4));
      if (iVar1 == 0) {
        return iVar2;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < *unaff_EDI);
  }
  return -1;
}

