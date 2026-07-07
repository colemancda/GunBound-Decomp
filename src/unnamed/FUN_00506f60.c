/* FUN_00506f60 - 0x00506f60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00506f60(void)

{
  char cVar1;
  int iVar2;
  char *unaff_ESI;
  int unaff_EDI;
  HWND hWnd;
  LPCSTR lpString;
  
  if (*(char *)(unaff_EDI + 4) != '\0') {
    if (unaff_ESI == (char *)0x0) {
      hWnd = *(HWND *)(DAT_007934e4 + 4);
      lpString = &DAT_00551cb1;
    }
    else {
      hWnd = *(HWND *)(DAT_007934e4 + 4);
      lpString = unaff_ESI;
    }
    SetWindowTextA(hWnd,lpString);
  }
  iVar2 = (unaff_EDI + 0x38) - (int)unaff_ESI;
  do {
    cVar1 = *unaff_ESI;
    unaff_ESI[iVar2] = cVar1;
    unaff_ESI = unaff_ESI + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)(unaff_EDI + 0x13c) = 0;
  return;
}

