/* FUN_0040cc50 - 0x0040cc50 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EBX PROMOTED (2026-10-30): the first instruction, 0x40cc50
 * `mov eax,[ebx+0x44c]`, reads EBX with no prior write, and the body ends
 * with `mov [ebx+0x448],2; ret` (cdecl, no stack args). EBX is the text box
 * that just took focus. All four callers set it to the value they just stored
 * into the registry's +8 slot: 0x40ce89 (HandleBackgroundActiveObjectMouseDown,
 * ebx = FindActiveObjectAt's result from 0x40ce5d), 0x40cfce (FUN_0040cf80,
 * ebx = the matched node from 0x40cfa3/0x40cfaf), and 0x40d0c8/0x40d11d
 * (FUN_0040d020, `mov ebx,esi` at 0x40d0c3/0x40d118). The port read an
 * uninitialised unaff_EBX.
 */
#include "ghidra_types.h"


void FUN_0040cc50(int regEbx)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  int unaff_EBX = regEbx;
  HWND hWnd;
  LPCSTR lpString;
  
  SendMessageA(*(HWND *)(g_sharedTextInputControl + 4),0xc5,*(WPARAM *)(unaff_EBX + 0x44c),0);
  pcVar3 = (char *)(unaff_EBX + 0x48);
  if (pcVar3 == (char *)0x0) {
    hWnd = *(HWND *)(g_sharedTextInputControl + 4);
    lpString = &DAT_00551cb1;
  }
  else {
    hWnd = *(HWND *)(g_sharedTextInputControl + 4);
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
  if (*(char *)(g_sharedTextInputControl + 8) != '\0') {
    SendMessageA(*(HWND *)(g_sharedTextInputControl + 4),0xb1,(int)pcVar3 - (unaff_EBX + 0x49),
                 (int)pcVar2 - (unaff_EBX + 0x49));
  }
  *(undefined4 *)(unaff_EBX + 0x448) = 2;
  return;
}

