/* AddRejoinBlockedRoom - 0x00422f10 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00422f10 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: Appends the
 * pair (param_1 = ctx + 0x3f804, param_2 = ctx + 0x44e60, the current
 * channel and room number) to three parallel 0x40 entry arrays at ctx +
 * 0x5f2f58, +0x5f3058 and +0x5f3158 with the count at +0x5f3258, stamping
 * GetTickCount() / 1000 + 300 as an expiry, and does nothing once the list
 * is full. The list is read back by SendJoinRoomChecked (returns without
 * sending the 0x2110 join when the room is listed) and
 * EnterRoomNumberDialog_SubmitRoomNumber (refuses the typed room number
 * when listed), and expired entries are removed by
 * PruneExpiredRejoinBlockedRooms (0x422f70) from GameTick. The four
 * callers (State11_InBattle_ProcessPacket, State11_InBattle_HandleKeyInput
 * x2, State09_ReadyRoom_ProcessBattleAction) each call it right after
 * SendOutgoingPacket, and three of them then reset +0x44e60 to -1. LIKELY:
 * that a listed room is one the client may not join again for five minutes
 * is read from the two readers; why those callers create the entry is not
 * shown.
 *
 * ARGUMENTS RE-SLOTTED AND THE DROPPED REGISTER RECOVERED.  `ret 4` gives one
 * stack argument, so param_1 arrives in ECX and param_2 is the push; ESI is a
 * third input Ghidra left as a local.  All four call sites agree:
 *
 *   ecx = [ctx + 0x3f804]   -> param_1
 *   push [ctx + 0x44e60]    -> param_2   (via EDX at three sites, EAX at one)
 *   esi = [0x5b3484]        -> regEsi = g_clientContext
 *
 * The port had been passing *(g_clientContext + 0x44e60) as param_1.  That is
 * the right value in the wrong slot -- it belongs in param_2 -- so the two
 * fields were being written swapped, with param_2 taking whatever was in the
 * caller's stack.
 *
 * The body appends to three parallel arrays based at regEsi (+0x5f2f58,
 * +0x5f3058, +0x5f3158) with the count at +0x5f3258 and a hard cap of 0x40,
 * stamping GetTickCount()/1000 + 300 -- a five-minute expiry.
 */
#include "ghidra_types.h"


void __thiscall AddRejoinBlockedRoom(undefined4 param_1,undefined4 param_2,int regEsi)

{
  DWORD DVar1;
  
  if (*(int *)(&DAT_005f3258 + regEsi) < 0x40) {
    *(undefined4 *)(&DAT_005f2f58 + *(int *)(&DAT_005f3258 + regEsi) * 4 + regEsi) = param_1;
    *(undefined4 *)(&DAT_005f3058 + *(int *)(&DAT_005f3258 + regEsi) * 4 + regEsi) = param_2;
    DVar1 = GetTickCount();
    *(uint *)(&DAT_005f3158 + *(int *)(&DAT_005f3258 + regEsi) * 4 + regEsi) =
         DVar1 / 1000 + 300;
    *(int *)(&DAT_005f3258 + regEsi) = *(int *)(&DAT_005f3258 + regEsi) + 1;
  }
  return;
}

