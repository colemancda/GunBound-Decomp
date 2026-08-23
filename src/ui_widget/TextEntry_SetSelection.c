/* TextEntry_SetSelection - 0x0040c8d0 in the original binary.
 *
 * Sets the selection range in a text-entry object's Win32 control.
 *
 * Sends EM_SETSEL (0xb1) to the HWND at regEax + 4, gated on the enable flag
 * at regEax + 8, with param_2 and param_3 as the start and end.  Its one
 * caller passes the string length for both, which is the idiom for moving the
 * caret to the end of the text - see State09_ReadyRoom_HandleChatInput.
 *
 * DROPPED REGISTER RECOVERED: EAX is g_sharedTextInputControl, loaded at its sole call
 * site (0x004d6621).  The object it points at has an HWND at +4 and an enable
 * flag at +8, which is consistent with the SendMessageA below.
 */
#include "ghidra_types.h"


void __fastcall TextEntry_SetSelection(undefined4 param_1,WPARAM param_2,LPARAM param_3,int regEax)

{
  
  if (*(char *)(regEax + 8) != '\0') {
    SendMessageA(*(HWND *)(regEax + 4),0xb1,param_2,param_3);
  }
  return;
}

