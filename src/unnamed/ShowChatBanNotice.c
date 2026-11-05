/* ShowChatBanNotice - 0x00426230 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00426230 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: the call
 * sites (State09_ReadyRoom_HandleChatInput, State10_Loading_HandleChatInput
 * and its C++ twin CState10Loading::OnKeyInput,
 * State11_InBattle_HandleMouseInput) sit in the Enter-key send path and
 * call this in the arm taken when the guard bool at ctx+0x6aa678 is set,
 * INSTEAD of the arm that word-filters and broadcasts the typed line (the
 * other arm reports localized strings 0x202 and 0x205 through the same
 * state vtable slot 0x28). The message is Language string 0x204 formatted
 * with the player nickname at ctx+0x23330, hours and minutes taken from the
 * guarded countdown cell at ctx+0x6aa67c (ticks / 20, then h and m). The
 * scoping pass read string 516 as "%s is prohibited from talking(%d hour
 * %02d minutes left)"; that text is not extractable from this tree
 * (Language.txt lives in the packed assets) so it was NOT re-read here,
 * which is why this is LIKELY. The format shape (one %s, a %d, a %02d) does
 * match the three arguments passed. The older note in State10_Loading.cpp
 * calling this the playback-mode chat path is a guess, not evidence.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): the client context
 * arrives in EAX (`mov esi,eax` at 0x42623d) - Ghidra kept the artifact name
 * in_EAX and even used it (`in_EAX + 0x23330`), so it is simply made the
 * parameter.  The peek reads ctx + 0x6aa67c (the elapsed-time cell; the body
 * formats it as h:m).  All 6 callers pass g_clientContext now.
 */
#include "ghidra_types.h"


void ShowChatBanNotice(int in_EAX)

{
  int iVar1;
  uint uVar2;
  char *_Format;
  undefined4 uVar3;
  int iVar4;
  char local_400 [1024];
  
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(in_EAX + 0x6aa67c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar2 = (uint)(iVar1 / 0x14) / 0xe10;
  iVar4 = in_EAX + 0x23330;
  uVar3 = (undefined4)(((ulonglong)(uint)(iVar1 / 0x14) % 0xe10) / 0x3c);
  _Format = (char *)GetLocalizedString(&g_localizedStringTable,0x204);
  _sprintf(local_400,_Format,iVar4,uVar2,uVar3);
  (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))(g_gameStateVTableArray[g_currentGameState],local_400,2,6);
  return;
}

