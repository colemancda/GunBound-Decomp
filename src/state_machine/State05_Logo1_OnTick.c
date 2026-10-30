/* State05_Logo1_OnTick - 0x00443540 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_00443540).  Slot 9 (+0x24) of
 * State05's vtable 0x555590, read from the original's .rdata (slots 7/8
 * are State05_Logo1_OnEnter/OnExit).  GameTick calls that slot once per
 * tick (src/entry/GameTick.c).  It is the twin of State06_Logo2_OnTick
 * (0x443330), slot 9 of the next logo state: bump the frame counter at
 * this+4 that State05_Logo1_OnEnter zeroes, and at 0x28 ticks request
 * the next state - ChangeGameState(6), i.e. Logo2, where Logo2's own
 * OnTick requests state 1 (Title).  ChangeGameState's state number is
 * ESI in the original (`mov esi,6` at 0x44354f).
 */
#include "ghidra_types.h"


void __fastcall State05_Logo1_OnTick(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 4) + 1;
  *(int *)(param_1 + 4) = iVar1;
  if (iVar1 == 0x28) {
    g_pendingGameState = 6;
    g_stateChangeRequested = 1;
    ChangeGameState(6);
  }
  return;
}

