/* State11_InBattle_AppendChatLine - 0x004c1b90 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_004c1b90).  Slot 10 (+0x28) of
 * State11's vtable 0x5566d8, read from the original's .rdata - the slot
 * State10 and State03 fill with State10_Loading_AppendChatLine (0x442240)
 * and State09 with AppendReadyRoomStatusMessage.  Its callers hand it a
 * finished chat line: GameTick sprintf's GetLocalizedString(9000) into a
 * buffer and calls slot 10 with (text, 2, 6); ParseChatSlashCommand and
 * WriteReplayEventRecord call the same slot with (text, 2, n).  `ret 0xc`
 * (0x4c1c7f) matches those three stack arguments.  Here the line lands
 * in the in-battle chat history that State11_InBattle_RenderHud (slot 15)
 * draws: text copied to ctx+0x58c54 + n*0x80, type byte at ctx+0x58c4a,
 * the third argument at ctx+0x5917c, line count at ctx+0x58b60 (shifted
 * through FUN_0041ee10 once it passes 8).
 *
 * ARCHITECTURE.md's State 11 vtable table calls this slot a "chat
 * character-input helper"; the body copies a whole NUL-terminated line
 * and bumps the line count, so that description is out of date.
 */
#include "ghidra_types.h"


void __thiscall State11_InBattle_AppendChatLine(int param_1,char *param_2,int param_3,int param_4)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  
  iVar2 = g_clientContext;
  if (8 < *(int *)(g_clientContext + 0x58b60)) {
    FUN_0041ee10();
  }
  *(undefined1 *)(*(int *)(iVar2 + 0x58b60) * 9 + 0x58b64 + iVar2) = 0;
  *(undefined1 *)((*(int *)(iVar2 + 0x58b60) + 0x6569) * 0xe + iVar2) = 0;
  if (param_3 == '\x02') {
    cVar1 = *param_2;
    if (cVar1 != '!') {
      if (cVar1 == '@') {
        param_3 = '\n';
      }
      else if (cVar1 == '#') {
        param_3 = '\v';
      }
      else if (cVar1 == '$') {
        param_3 = '\f';
      }
      else if (cVar1 == '%') {
        param_3 = '\r';
      }
      else if (cVar1 == '^') {
        param_3 = '\x0e';
      }
      else if (cVar1 == '&') {
        param_3 = '\x0f';
      }
      else {
        if (cVar1 != '*') goto LAB_004c1c21;
        param_3 = '\x10';
      }
    }
    param_2 = param_2 + 1;
  }
LAB_004c1c21:
  *(char *)(iVar2 + 0x58c4a + *(int *)(iVar2 + 0x58b60)) = param_3;
  *(int *)(iVar2 + 0x59154 + *(int *)(iVar2 + 0x58b60) * 4) = *(int *)(param_1 + 0xc) + 300;
  *(undefined2 *)(iVar2 + 0x5917c + *(int *)(iVar2 + 0x58b60) * 2) = param_4;
  pcVar3 = (char *)(*(int *)(iVar2 + 0x58b60) * 0x80 + 0x58c54 + iVar2);
  do {
    cVar1 = *param_2;
    param_2 = param_2 + 1;
    *pcVar3 = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  *(int *)(iVar2 + 0x58b60) = *(int *)(iVar2 + 0x58b60) + 1;
  return;
}

