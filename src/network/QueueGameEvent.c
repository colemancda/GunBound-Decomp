/* QueueGameEvent - 0x004e5dc0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Enqueues one (eventCode, value) pair into the global game-event ring -
 * the writer side of the ring PumpBattleActions drains: PumpBattleActions
 * reads `g_gameEventTypeRing[g_gameEventRingReadIndex]` /
 * `g_gameEventDataRing[g_gameEventRingReadIndex]`, advances
 * g_gameEventRingReadIndex with the SAME `+1 & 0x800001ff` wraparound mask
 * this function uses on the write side, and then either feeds specific
 * codes into QueueBroadcastEvent/BroadcastQueuedEvent or dispatches
 * (eventCode, value) into the current game state's own vtable slot 0xc,
 * which PumpBattleActions' own header already describes as the
 * "event-code,value" virtual. That is also why the parameters are named
 * eventCode/value here rather than param_1/param_2.
 *
 * DROPPED REGISTER ARGUMENT RESOLVED, NOT PARAMETERISED (2026-10-26).
 * in_EAX is the ring's base - its first word, in_EAX[0], is the one
 * `g_gameEventRingWriteIndex != 0x800001ff`-masked index that PumpBattleActions
 * reads as g_gameEventRingWriteIndex itself, its second word in_EAX[1] is
 * the read-index limit this function checks the write against
 * (g_gameEventRingReadIndex, the very next global in src/globals.c), and
 * in_EAX[2+idx]/in_EAX[0x202+idx] land exactly on g_gameEventTypeRing/
 * g_gameEventDataRing's byte offsets (+8 and +0x808) that PumpBattleActions
 * indexes the same way. All 6 call sites were disassembled (callsite_regs.py
 * reports the immediately-preceding instruction as a cmp/test, not the real
 * mov, so this needed a manual look): every one of them loads EAX from
 * `[ctx + 0x44ff0]`, the field InitGame.c sets EXACTLY ONCE, to
 * `&g_gameEventRingWriteIndex` - there is no other write to that field
 * anywhere in the tree, so the register is bound directly to the global
 * rather than threaded through as a parameter (the same treatment
 * BroadcastQueuedEvent's header gives a register that resolves to one
 * invariant global at every site).
 */
#include "ghidra_types.h"


void QueueGameEvent(uint eventCode,uint value)

{
  uint *in_EAX = &g_gameEventRingWriteIndex;
  uint uVar1;

  uVar1 = *in_EAX + 1 & 0x800001ff;
  if ((int)uVar1 < 0) {
    uVar1 = (uVar1 - 1 | 0xfffffe00) + 1;
  }
  if (uVar1 != in_EAX[1]) {
    in_EAX[*in_EAX + 2] = eventCode;
    in_EAX[*in_EAX + 0x202] = value;
    *in_EAX = uVar1;
  }
  return;
}

