/* DisplayLocalizedChatMessage - 0x00413af0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-26), HIGH. Both call sites (ParseChatSlashCommand.c,
 * ClearMuteList.c) pass a GetLocalizedString() result straight in, so the
 * input is always a localized string table lookup rather than raw network
 * text. The body splits that string on a literal "\n" or a real newline
 * and dispatches each line through
 * g_gameStateVTableArray[g_currentGameState]'s +0x28 slot - the same
 * "append a chat line" virtual that ParseChatSlashCommand's own inline
 * uses (local_1a0 sites), BeginNewTurn, BuildItemLoadout, and the state
 * machine's ProcessBattleAction/ProcessPacket handlers all call with the
 * same (text, 2, colorFlag) shape. So this is a local/system chat-line
 * display helper fed by the localization table, not a packet receive
 * path.
 */
#include "ghidra_types.h"


void DisplayLocalizedChatMessage(char *regEdi)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  undefined4 uVar6;
  char local_400 [1024];
  
  iVar3 = 0;
  iVar5 = 0;
  bVar2 = true;
  cVar1 = *regEdi;
  while (cVar1 != '\0') {
    cVar1 = regEdi[iVar5];
    if ((cVar1 == '\\') && (regEdi[iVar5 + 1] == 'n')) {
      local_400[iVar3] = '\0';
      if (bVar2) {
        piVar4 = (int *)g_gameStateVTableArray[g_currentGameState];
        uVar6 = 6;
      }
      else {
        piVar4 = (int *)g_gameStateVTableArray[g_currentGameState];
        uVar6 = 0;
      }
      (**(code **)(*piVar4 + 0x28))(local_400,2,uVar6);
      iVar3 = 0;
      iVar5 = iVar5 + 2;
      bVar2 = false;
    }
    else if (cVar1 == '\n') {
      piVar4 = (int *)g_gameStateVTableArray[g_currentGameState];
      local_400[iVar3] = '\0';
      if (bVar2) {
        (**(code **)(*piVar4 + 0x28))(local_400,2,6);
        iVar3 = 0;
        iVar5 = iVar5 + 1;
        bVar2 = false;
      }
      else {
        (**(code **)(*piVar4 + 0x28))(local_400,2,0);
        iVar3 = 0;
        iVar5 = iVar5 + 1;
        bVar2 = false;
      }
    }
    else {
      local_400[iVar3] = cVar1;
      iVar3 = iVar3 + 1;
      iVar5 = iVar5 + 1;
    }
    cVar1 = regEdi[iVar5];
  }
  piVar4 = (int *)g_gameStateVTableArray[g_currentGameState];
  local_400[iVar3] = '\0';
  if (bVar2) {
    (**(code **)(*piVar4 + 0x28))(local_400,2,6);
    return;
  }
  (**(code **)(*piVar4 + 0x28))(local_400,2,0);
  return;
}

