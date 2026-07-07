/* FUN_0040c880 - 0x0040c880 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0040c880(void)

{
  int in_EAX;
  int iVar1;
  LPSTR unaff_ESI;
  
  if (*(char *)(in_EAX + 8) == '\0') {
    *unaff_ESI = '\0';
  }
  else {
    iVar1 = GetWindowTextA(*(HWND *)(in_EAX + 4),unaff_ESI,0x80);
    if (iVar1 == 0) {
      *unaff_ESI = '\0';
      return;
    }
  }
  return;
}

