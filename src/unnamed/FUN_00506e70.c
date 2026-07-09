/* FUN_00506e70 - 0x00506e70 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00506e70(void)

{
  int in_EAX;
  int iVar1;
  HWND hWnd;
  LPCSTR lpString;
  
  if (*(int *)(in_EAX + 8) != 0) {
    FUN_0050e820();
  }
  if (DAT_007933b8 == '\x01') {
    if (*(char *)(DAT_007934e4 + 8) != '\0') {
      iVar1 = GetWindowTextA(*(HWND *)(DAT_007934e4 + 4),(LPSTR)&DAT_007933c0,0x80);
      if (iVar1 != 0) goto LAB_00506eb8;
    }
    SUBFIELD(DAT_007933c0,0,undefined1) = 0;
  }
LAB_00506eb8:
  DAT_007933b8 = 0;
  SendMessageA(*(HWND *)(DAT_007934e4 + 4),0xc5,*(WPARAM *)(in_EAX + 0x138),0);
  lpString = (LPCSTR)(in_EAX + 0x38);
  if (lpString == (LPCSTR)0x0) {
    hWnd = *(HWND *)(DAT_007934e4 + 4);
    lpString = &DAT_00551cb1;
  }
  else {
    hWnd = *(HWND *)(DAT_007934e4 + 4);
  }
  SetWindowTextA(hWnd,lpString);
  if (*(char *)(DAT_007934e4 + 8) != '\0') {
    SendMessageA(*(HWND *)(DAT_007934e4 + 4),0xb1,*(WPARAM *)(in_EAX + 0x138),
                 *(WPARAM *)(in_EAX + 0x138));
  }
  return;
}

