/* SyncChatTypingState - 0x00409990 in the original binary.
 *
 * RENAMED (2026-07-30): fetches the shared overlay EDIT-control's current
 * text into a local scratch buffer (same g_sharedTextInputControl singleton
 * CommitActiveTextInput/FetchActiveTextInputText use) and records into
 * `thisObj+5` whether it came back non-empty (a "was the player mid-typing
 * a chat message" flag). If `keepText` is false, additionally clears the
 * shared control's text outright - the ESC-to-cancel-chat path
 * (`State11_InBattle_HandleMouseInput.c`'s VK_ESCAPE handler calls this
 * with keepText=0). Params were already explicit in the raw port (no
 * dropped-register bug here, unlike its siblings in this same rename
 * pass) - only the name/signature documentation was missing.
 */
#include "ghidra_types.h"


/* WARNING: Type propagation algorithm not settling */

void SyncChatTypingState(int thisObj,int keepText)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  CHAR local_100 [256];
  
  if (*(char *)(g_sharedTextInputControl + 8) != '\0') {
    iVar2 = GetWindowTextA(*(HWND *)(g_sharedTextInputControl + 4),local_100,0x80);
    if (iVar2 != 0) goto LAB_004099bf;
  }
  local_100[0] = '\0';
LAB_004099bf:
  pcVar3 = local_100;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  *(bool *)(thisObj + 5) = pcVar3 != (char *)((int)local_100 + 1U);
  if (keepText == '\0') {
    SetWindowTextA(*(HWND *)(g_sharedTextInputControl + 4),&DAT_00551cb1);
  }
  return;
}

