/* TextEntry_RestoreChatInput - 0x00507e30 in the original binary.
 *
 * Restores the stashed chat-input text into the shared overlay EDIT control.
 *
 * The counterpart to ActivateLegacyTextInputField, which switches the shared
 * DAT_007934e4 control AWAY to some other field and stashes the chat input in
 * the DAT_007933b8 / DAT_007933bc / DAT_007933c0 triple (flag, caret+limit,
 * text).  This puts them back: EM_LIMITTEXT (0xc5), SetWindowTextA, then --
 * only if the control is live, per the flag at DAT_007934e4 + 8 -- EM_SETSEL
 * (0xb1) with the same position for both ends, and re-marks DAT_007933b8.
 *
 * PanelManager_DispatchMouseDown calls it when NO panel consumed the click,
 * which is what makes "restore" the right word rather than "activate":
 * clicking away from every panel hands the control back to the chat box.
 */
#include "ghidra_types.h"


void TextEntry_RestoreChatInput(void)

{
  if (DAT_007933b8 == '\0') {
    SendMessageA(*(HWND *)(DAT_007934e4 + 4),0xc5,DAT_007933bc,0);
    SetWindowTextA(*(HWND *)(DAT_007934e4 + 4),(LPCSTR)&DAT_007933c0);
    if (*(char *)(DAT_007934e4 + 8) != '\0') {
      SendMessageA(*(HWND *)(DAT_007934e4 + 4),0xb1,DAT_007933bc,DAT_007933bc);
    }
    DAT_007933b8 = 1;
    return;
  }
  DAT_007933b8 = 1;
  return;
}

