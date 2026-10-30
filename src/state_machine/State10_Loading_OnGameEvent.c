/* State10_Loading_OnGameEvent - 0x0043e700 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_0043e700).  Slot 3 (+0xc) of
 * State10's vtable 0x554018, read from the original's .rdata.  The only
 * dispatch of that slot on a game state is PumpBattleActions' drain of
 * the game-event ring that QueueGameEvent fills: at 0x412cd4/0x412cdb it
 * loads EBX from the value ring (0x793fa0) and EDI from the event-code
 * ring (0x7937a0), then `push ebx; push edi; call [edx+0xc]` (0x412dd9-
 * 0x412ddb) with ECX = the current state.  So the first stack argument
 * here is the event code and the second its value; `ret 8` matches.
 * Event code 1 - which BroadcastRingEvent queues as QueueGameEvent(1,0)
 * once a broadcast round settles - sets the byte at this+0x14c that
 * State10_Loading_OnEnter clears.
 *
 * The scoping pass proposed State10_Loading_OnActivate, after the
 * same-slot sibling State09_ReadyRoom_OnActivate.  Nothing outside
 * either function says "activate"; the caller says game event, so the
 * name follows the caller.  The sibling names for this slot already
 * disagree (State02_ServerSelect_OnTopButton is slot 3 too, and its
 * param_2 == 3/4 cases are the event codes ProcessUdpProbeDatagram and
 * UdpProbeWorkerThread queue), and neither was touched here.
 */
#include "ghidra_types.h"


void __thiscall State10_Loading_OnGameEvent(int param_1,int param_2)

{
  if (param_2 == 1) {
    *(undefined1 *)(param_1 + 0x14c) = 1;
  }
  return;
}

