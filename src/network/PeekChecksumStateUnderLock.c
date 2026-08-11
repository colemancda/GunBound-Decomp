/* PeekChecksumStateUnderLock - 0x0040a4d0 in the original binary.
 *
 * CValueGuard::Peek() under the family's shared lock. Unlike the rest of
 * the guard family (cell in a register), this wrapper takes its cell as a
 * REAL STACK PARAMETER - orig disasm (2026-08-11):
 *     0040a4d0: push esi
 *     0040a4d1: push 0x5a9068          ; EnterCriticalSection
 *     0040a4dc: mov  eax,[esp+8]       ; cell (the stack arg)
 *     0040a4e0: call 0x40a2e0          ; Peek, cell in EAX
 *     ...
 *     0040a4f5: ret  4                 ; callee-clean, 1 arg
 * - which is why Ghidra KEPT the argument at most call sites (1,615 of
 * 1,758 pass the cell already; the remaining argless sites are tracked
 * in tools/peekpacketchecksumstate_sites.json).
 *
 * DROPPED-CELL FIX (2026-08-11): the raw port declared this void(void)
 * and called PeekPacketChecksumState() argless, so the cell died here
 * even at the sites that passed it correctly. Now forwards it. The decl
 * in functions.h stays K&R until the tree-wide argless-site sweep lands
 * (see full-tree-sweep-on-prototype-promotion); PeekPacketChecksumState
 * is still the bring-up stub that ignores its argument and returns 0, so
 * this change is behavior-neutral until the CValueGuard::Peek flip. */
#include "ghidra_types.h"


undefined4 PeekChecksumStateUnderLock(void *cell)

{
  undefined4 uVar1;

  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState(cell);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return uVar1;
}
