/* FUN_004fdc80 - 0x004fdc80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004fdc80(void)

{
  HWND hWnd;
  undefined4 *unaff_ESI;
  
  *unaff_ESI = &PTR_LAB_00557598;
  unaff_ESI[1] = 0;
  unaff_ESI[2] = 0;
  unaff_ESI[3] = 0;
  unaff_ESI[4] = 0;
  unaff_ESI[5] = 0;
  unaff_ESI[6] = 10;
  unaff_ESI[7] = 0xffffffff;
  *(undefined1 *)(unaff_ESI + 9) = 0;
  hWnd = CreateWindowExA(0,s_STATIC_00557b50,s_CCommEngine_Notify_Window_00557b58,0x80000000,0,0,0,0
                         ,(HWND)0x0,(HMENU)0x0,(HINSTANCE)0x0,(LPVOID)0x0);
  unaff_ESI[8] = hWnd;
  if (hWnd != (HWND)0x0) {
    SetWindowLongA(hWnd,-0x15,(LONG)unaff_ESI);
    SetWindowLongA((HWND)unaff_ESI[8],-4,(LONG)FUN_004fe6f0);
  }
  return;
}

