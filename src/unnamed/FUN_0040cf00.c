/* FUN_0040cf00 - 0x0040cf00 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_0040cf00(void)

{
  LPSTR lpString;
  int in_EAX;
  int iVar1;
  
  if ((*(int *)(in_EAX + 8) != 0) &&
     ((lpString = (LPSTR)(*(int *)(in_EAX + 8) + 0x48), *(char *)(DAT_007934e4 + 8) == '\0' ||
      (iVar1 = GetWindowTextA(*(HWND *)(DAT_007934e4 + 4),lpString,0x80), iVar1 == 0)))) {
    *lpString = '\0';
  }
  return;
}

