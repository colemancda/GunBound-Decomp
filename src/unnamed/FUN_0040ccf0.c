/* FUN_0040ccf0 - 0x0040ccf0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_0040ccf0(void)

{
  int iVar1;
  int unaff_EDI;
  
  if (*(char *)(DAT_007934e4 + 8) != '\0') {
    iVar1 = GetWindowTextA(*(HWND *)(DAT_007934e4 + 4),(LPSTR)(unaff_EDI + 0x48),0x80);
    if (iVar1 != 0) goto LAB_0040cd17;
  }
  *(LPSTR)(unaff_EDI + 0x48) = '\0';
LAB_0040cd17:
  SetWindowTextA(*(HWND *)(DAT_007934e4 + 4),&DAT_00551cb1);
  *(undefined4 *)(unaff_EDI + 0x448) = 0;
  return;
}

