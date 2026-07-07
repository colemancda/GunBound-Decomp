/* FUN_0040cc50 - 0x0040cc50 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0040cc50(void)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  int unaff_EBX;
  HWND hWnd;
  LPCSTR lpString;
  
  SendMessageA(*(HWND *)(DAT_007934e4 + 4),0xc5,*(WPARAM *)(unaff_EBX + 0x44c),0);
  pcVar3 = (char *)(unaff_EBX + 0x48);
  if (pcVar3 == (char *)0x0) {
    hWnd = *(HWND *)(DAT_007934e4 + 4);
    lpString = &DAT_00551cb1;
  }
  else {
    hWnd = *(HWND *)(DAT_007934e4 + 4);
    lpString = pcVar3;
  }
  SetWindowTextA(hWnd,lpString);
  pcVar2 = pcVar3;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  if (*(char *)(DAT_007934e4 + 8) != '\0') {
    SendMessageA(*(HWND *)(DAT_007934e4 + 4),0xb1,(int)pcVar3 - (unaff_EBX + 0x49),
                 (int)pcVar2 - (unaff_EBX + 0x49));
  }
  *(undefined4 *)(unaff_EBX + 0x448) = 2;
  return;
}

