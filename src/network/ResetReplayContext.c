/* ResetReplayContext - 0x004e7430 in the original binary.
 *
 * RENAMED (2026-07-19) from FUN_004e7430. Resets the broadcast/replay
 * context (g_replayContext, the 0x454f9-byte object at DAT_00e55ce0) back to
 * its idle state: zeroes the 0x40-byte header block at +0x18, the cursor
 * trio at +0x138/+0x13c/+0x140, the 0x1000-byte table at +0x42de0, the pair
 * at +0x40bd0/+0x40bd4 and the event counters at +0x44de4/+0x44de8,
 * InterlockedExchange-clears the lock word at +0x44de0, and sets the eight
 * per-slot handles at +0x454c4..+0x454e0 to -1 (the family's "no peer"
 * sentinel). All 3 call sites pass &g_replayContext (`mov esi,0xe55ce0`).
 * Called on channel entry (State03_GameRoomList_ProcessPacket) and from the
 * replay writer.
 */
/* DROPPED-REGISTER FIX (2026-07-19): the object this clears is addressed by
 * ESI, an incoming register arg Ghidra emitted as an uninitialised
 * `unaff_ESI` - so the port wrote through a null base and faulted on the
 * write to 0x48 the moment the join->lobby path first exercised it. All 3
 * call sites load `mov esi, 0xe55ce0` = &g_replayContext (the 0x454f9-byte
 * broadcast/replay context; this clears fields up to +0x454e0, inside it).
 * Promoted to an explicit parameter. */
#include "ghidra_types.h"


void ResetReplayContext(int ctx)

{
  int iVar1;
  int unaff_ESI = ctx;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(unaff_ESI + 0x18);
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)(unaff_ESI + 0x13c) = 0;
  *(undefined4 *)(unaff_ESI + 0x140) = 0;
  *(undefined4 *)(unaff_ESI + 0x138) = 0;
  puVar2 = (undefined4 *)(unaff_ESI + 0x42de0);
  for (iVar1 = 0x400; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)(unaff_ESI + 0x40bd0) = 0;
  *(undefined4 *)(unaff_ESI + 0x40bd4) = 0;
  *(undefined4 *)(unaff_ESI + 0x44de4) = 0;
  *(undefined4 *)(unaff_ESI + 0x44de8) = 0;
  InterlockedExchange((LONG *)(unaff_ESI + 0x44de0),0);
  *(undefined4 *)(unaff_ESI + 0x454c4) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x454c8) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x454cc) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x454d0) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x454d4) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x454d8) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x454dc) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x454e0) = 0xffffffff;
  return;
}

