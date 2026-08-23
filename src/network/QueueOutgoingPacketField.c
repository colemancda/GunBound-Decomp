/* QueueOutgoingPacketField - 0x0040a470 in the original binary.
 *
 * CValueGuard encode under the family's shared lock: cell in EAX, value
 * as a real stack parameter - orig disasm (2026-08-11):
 *     0040a470: push edi
 *     0040a471: push 0x5a9068
 *     0040a476: mov  edi,eax          ; cell (EAX) -> EDI for the inner call
 *     0040a478: call [0x5440a0]       ; EnterCriticalSection
 *     0040a47e: mov  eax,[esp+8]      ; value (the stack arg)
 *     0040a482: push eax
 *     0040a483: call 0x40a380         ; EncodeOutgoingPacketField(cell=EDI, value)
 *     ...
 *     0040a496: ret  4
 * i.e. the exact lock-wrapper twin of PeekChecksumStateUnderLock, on the
 * encode side.
 *
 * DROPPED-CELL FIX (2026-08-11): the raw port declared this (value)-only -
 * the EAX cell died here for every caller. Promoted to (cell, value); the
 * decl in functions.h stays K&R until the tree-wide 1-arg-caller sweep
 * lands (cells recoverable by scanning `call 0x40a470` sites tracking EAX
 * - see tools/scan_peekpacketchecksumstate.py for the technique and
 * cvalueguard migration notes). EncodeOutgoingPacketField is still the
 * bring-up no-op auto-stub, so this change is behavior-neutral until the
 * ValueGuard.obj flip. */
#include "ghidra_types.h"
#include <windows.h>


undefined4 QueueOutgoingPacketField(void *cell,undefined4 value)

{
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField(cell,value);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}
