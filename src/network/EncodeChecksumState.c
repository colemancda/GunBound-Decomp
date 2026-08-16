/* EncodeChecksumState - 0x0040a4a0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 *
 * DROPPED-PARAMETER FIX (2026-07-30): this function itself takes one
 * argument (the guard cell), not zero - confirmed via objdump
 * (0x40a4a0-0x40a4cb): `mov edi,eax` at entry (before any stack access)
 * loads the incoming arg into EDI, `mov eax,[esp+8]` later reloads the
 * SAME value (the saved EDI, after 2 pushes) to pass to
 * PeekPacketChecksumState, and `ret 4` cleans up one caller-pushed slot.
 * Every one of this function's 100+ real call sites across the tree
 * already passes exactly 1 argument (uVar1/piVar1/param_1+offset/etc.),
 * and src/cxx/Mobile.cpp/Projectile.cpp both carry their own local
 * 1-param forward declarations for it (`void *cell` / `unsigned int
 * value`) - this file's own `(void)` signature was the only holdout,
 * silently reading garbage for a value every one of those callers
 * already provides correctly.
 *
 * EncodeOutgoingPacketField's `self` is this same cell (EDI is reused
 * unmodified as its dropped self arg - same call-site shape as every
 * other EncodeOutgoingPacketField caller in this family). Does NOT wire
 * the cell into PeekPacketChecksumState - that function is a deliberate
 * bring-up stub (always returns 0, ignores its own dropped-EAX cell arg)
 * per its own header; wiring it here would have no effect until the
 * larger CValueGuard migration that file already defers to lands.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): the internal
 * PeekPacketChecksumState() call reads param_1, the cell the original loads
 * with `mov eax,[esp+8]`.  All 131 call sites already pass that cell.
 */
#include "ghidra_types.h"
#include <windows.h>


undefined4 EncodeChecksumState(int param_1)

{
  undefined4 uVar1;

  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState((void *)(param_1));
  EncodeOutgoingPacketField((void *)param_1,uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* bare `return;` in a value-returning function - MSVC falls through
   * with whatever's in EAX (here, uVar1, still live from the call
   * above); gcc 14 errors on this (-Wreturn-mismatch). Matches this
   * function's own C++ promotion, CValueGuard::Encode() in
   * src/cxx/ValueGuard.cpp, which returns the peeked value. */
  return uVar1;
}
