/* EncodeIncrementedChecksum - 0x0040b030 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_0040b030 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: Disasm
 * 0x40b030: takes the cell in EAX, under g_valueGuardLock does
 * Encode(cell, Peek(cell) + 1), no stack arguments. Its decrement twin
 * EncodeDecrementedChecksum is already named and the existing header here
 * already calls this the increment twin. Callers (TickJewelFrame,
 * FUN_0045cb50, State11_InBattle_HandleFireInput,
 * State11_InBattle_ProcessBattleAction, Mobile.cpp) each pass a single
 * guarded cell and nothing else.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): the cell arrives in
 * EAX and was dropped from both calls; the original (0x40b030) has no stack
 * arguments at all - it is the increment twin of EncodeDecrementedChecksum:
 * self.Encode(self.Peek() + 1).  All 10 callers fixed alongside.
 */
#include "ghidra_types.h"


void EncodeIncrementedChecksum(void *self)

{
  int iVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState(self);
  EncodeOutgoingPacketField(self, iVar1 + 1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return;
}

