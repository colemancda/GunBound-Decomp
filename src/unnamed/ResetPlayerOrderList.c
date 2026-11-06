/* ResetPlayerOrderList - 0x00415ca0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): the 9-dword block it writes (slots 0..7 =
 * identity, dword 8 = 0) is the ClientContext_Constructor initialisation
 * inlined: lines writing ctx+0x4737c..0x47398 = 0..7 and ctx+0x4739c = 0.
 * The 8 slots hold player slot numbers and +0x4739c is a count; the
 * callers keep that count in step - WriteReplayEventRecord (packet 0x3010)
 * and State03_GameRoomList_ProcessPacket do `ctx[0x4739c] += 1` and then
 * MovePlayerToOrderTail(slot, ctx+0x4737c), packet 0x3020 moves then does
 * `-= 1` - and RenderPlayerNameplate finds a slot's position in this table
 * and compares it to the active-player count byte at ctx+0x45124.  The two
 * callers here (0x4271be and 0x427a9a, both in
 * State03_GameRoomList_ProcessPacket) run in the same reset sequences
 * as ClearChatLog and ResetReplayContext, so this puts the list back to
 * identity with nothing active.  EAX = ctx+0x4737c (`add eax,0x4737c` /
 * `lea eax,[edx+0x4737c]`).  "Order" is the soft part of the name: the
 * table is a player-slot ordering (join order, active slots first), but
 * no already-named function says so in words.
 */
#include "ghidra_types.h"


void ResetPlayerOrderList(undefined4 *regEax)

{
  
  *regEax = 0;
  regEax[1] = 1;
  regEax[2] = 2;
  regEax[3] = 3;
  regEax[4] = 4;
  regEax[5] = 5;
  regEax[6] = 6;
  regEax[7] = 7;
  regEax[8] = 0;
  return;
}

