/* ActivateLegacyTextInputField - 0x00506e70 in the original binary.
 *
 * RENAMED (2026-07-30): switches the shared overlay EDIT-control singleton
 * (g_sharedTextInputControl: +0x04 HWND, +0x08 live/visible flag) over to represent
 * THIS "legacy" (non-C++, State09/10/11 flat-buffer) text field object:
 * first flushes the OLD field's pending text into the shared
 * g_chatInputActive/g_chatInputText chat-input pair (same commit-then-reset shape
 * as CommitActiveTextInput, just targeting the legacy globals instead of a
 * C++ widget's own field), then applies THIS object's max length (+0x138,
 * via EM_LIMITTEXT/0xc5) and default/current text (+0x38, an embedded
 * char buffer - not a pointer field, confirmed below) to the real Win32
 * control, and finally - if the control is live - positions the caret via
 * EM_SETSEL/0xb1 to (maxLen, maxLen).
 *
 * DROPPED-ARGUMENT FIX (2026-07-30): `unaff_EAX` is this function's real
 * `this` - confirmed via objdump (orig 0x506e70-0x506e74): `push ebx; push
 * esi; mov esi,eax` is the entry sequence, EAX live-in with no prior
 * write, immediately cached into ESI for the rest of the function - cdecl,
 * single register arg. No live callers currently port-side (Ghidra shows
 * 2 xrefs in the original, neither traced yet) - functions.h stays
 * K&R-empty until one is found and wired.
 *
 * NOT A BUG (verified, left as-is): `lpString = (LPCSTR)(in_EAX + 0x38);
 * if (lpString == 0)` looks like a decompiler mis-read of a pointer field,
 * but objdump (orig 0x506edd-0x506ee2) shows `lea eax,[esi+0x38]; cmp
 * eax,ebx(=0)` - a genuine address-of compared against 0, byte-identical
 * dead branch in the original too (an `esi+0x38` LEA can only be null if
 * `esi==-0x38`). +0x38 is this object's own embedded text buffer, not a
 * pointer field.
 */
#include "ghidra_types.h"


void ActivateLegacyTextInputField(int thisObj)

{
  int in_EAX = thisObj;
  int iVar1;
  HWND hWnd;
  LPCSTR lpString;

  if (*(int *)(in_EAX + 8) != 0) {
    FUN_0050e820(in_EAX,*(int *)(in_EAX + 8));
  }
  if (g_chatInputActive == '\x01') {
    if (*(char *)(g_sharedTextInputControl + 8) != '\0') {
      iVar1 = GetWindowTextA(*(HWND *)(g_sharedTextInputControl + 4),(LPSTR)&g_chatInputText,0x80);
      if (iVar1 != 0) goto LAB_00506eb8;
    }
    SUBFIELD(g_chatInputText,0,undefined1) = 0;
  }
LAB_00506eb8:
  g_chatInputActive = 0;
  SendMessageA(*(HWND *)(g_sharedTextInputControl + 4),0xc5,*(WPARAM *)(in_EAX + 0x138),0);
  lpString = (LPCSTR)(in_EAX + 0x38);
  if (lpString == (LPCSTR)0x0) {
    hWnd = *(HWND *)(g_sharedTextInputControl + 4);
    lpString = &DAT_00551cb1;
  }
  else {
    hWnd = *(HWND *)(g_sharedTextInputControl + 4);
  }
  SetWindowTextA(hWnd,lpString);
  if (*(char *)(g_sharedTextInputControl + 8) != '\0') {
    SendMessageA(*(HWND *)(g_sharedTextInputControl + 4),0xb1,*(WPARAM *)(in_EAX + 0x138),
                 *(WPARAM *)(in_EAX + 0x138));
  }
  return;
}

