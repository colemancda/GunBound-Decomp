/* TextEntry_RestoreChatInput - 0x00507e30 in the original binary.
 *
 * Restores the stashed chat-input text into the shared overlay EDIT control.
 *
 * The counterpart to ActivateLegacyTextInputField, which switches the shared
 * g_sharedTextInputControl control AWAY to some other field and stashes the chat input in
 * the g_chatInputActive / g_chatInputMaxLength / g_chatInputText triple (flag, caret+limit,
 * text).  This puts them back: EM_LIMITTEXT (0xc5), SetWindowTextA, then --
 * only if the control is live, per the flag at g_sharedTextInputControl + 8 -- EM_SETSEL
 * (0xb1) with the same position for both ends, and re-marks g_chatInputActive.
 *
 * PanelManager_DispatchMouseDown calls it when NO panel consumed the click,
 * which is what makes "restore" the right word rather than "activate":
 * clicking away from every panel hands the control back to the chat box.
 */
#include "ghidra_types.h"


void TextEntry_RestoreChatInput(void)

{
  if (g_chatInputActive == '\0') {
    SendMessageA(*(HWND *)(g_sharedTextInputControl + 4),0xc5,g_chatInputMaxLength,0);
    SetWindowTextA(*(HWND *)(g_sharedTextInputControl + 4),(LPCSTR)&g_chatInputText);
    if (*(char *)(g_sharedTextInputControl + 8) != '\0') {
      SendMessageA(*(HWND *)(g_sharedTextInputControl + 4),0xb1,g_chatInputMaxLength,g_chatInputMaxLength);
    }
    g_chatInputActive = 1;
    return;
  }
  g_chatInputActive = 1;
  return;
}

