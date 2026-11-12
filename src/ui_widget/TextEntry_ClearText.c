/* TextEntry_ClearText - 0x00506f30 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00506f30 mean this function.)
 *
 * NAMED (batch 48), HIGH. The reset half of the TextEntry object whose
 * other members are already named. Layout matches TextEntry_SetControlText
 * (0x506f60), which this precedes in the binary: +4 is the has-an-HWND
 * flag that gates SetWindowTextA on the shared control, +0x38 the
 * 0x100-byte text buffer and +0x13c the cursor field. This one writes the
 * empty string at DAT_00551cb1 (the same one TextEntry_PushTextToControl
 * substitutes for NULL) to the control, zeroes the buffer and the cursor.
 * Its sole caller, LobbyChatPanel_OnCommand, calls it on the chat input
 * child right after sending the chat packet. ESI = the text entry (dropped
 * register, promoted as regEsi).
 */
#include "ghidra_types.h"


void TextEntry_ClearText(int regEsi)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (*(char *)(regEsi + 4) != '\0') {
    SetWindowTextA(*(HWND *)(g_sharedTextInputControl + 4),&DAT_00551cb1);
  }
  puVar2 = (undefined4 *)(regEsi + 0x38);
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)(regEsi + 0x13c) = 0;
  return;
}

