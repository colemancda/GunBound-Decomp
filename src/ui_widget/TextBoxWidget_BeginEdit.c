/* TextBoxWidget_BeginEdit - 0x0040cc50 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_0040cc50 mean this function.)
 *
 * NAMED (2026-11-04), LIKELY. Puts a text box into edit mode: limits the
 * shared edit control (g_sharedTextInputControl, +4 is its window) to the
 * box's length limit at +0x44c with EM_LIMITTEXT (0xC5), copies the box's
 * text at +0x48 into it with SetWindowTextA, puts the caret at the end of
 * the text with EM_SETSEL (0xB1) when the control's flag at +8 is set, and
 * sets the box's mode at +0x448 to 2. TextBoxWidget_Draw's header names
 * mode 2 as the focused state (it switches on +0x448 and takes the
 * TextEntry_FetchSelectionAndPlaceImeCaret arm for 2), and
 * InitTextBoxWidget stores the limit at +0x44c. Callers:
 * HandleBackgroundActiveObjectMouseDown, FUN_0040cf80 and FUN_0040d020
 * each call it right after committing the previously active box with
 * CommitActiveTextInput and storing the new box in the registry's +8 slot
 * - the begin half of that commit/begin pairing. LIKELY: "BeginEdit" is
 * the role the callers give it; no library name applies.
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


void TextBoxWidget_BeginEdit(int regEbx)

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

