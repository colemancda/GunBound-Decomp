/* CheckGuardedBoolAnd - 0x00406610 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * SURVEYED 2026-08-20 - the missing argument is the GUARD CELL, and most of
 * the work is already cached.  cell is a byte* to a 3-byte guard cell (the
 * body checks (cell[0] + cell[1] - 0x34) == cell[2], the same shape as the
 * rest of the CValueGuard family), and 96 of the 100 call sites pass only the
 * bool, never the cell.  The signature this wants is
 * CheckGuardedBoolAnd(byte *cell, int value), matching how
 * PeekPacketChecksumBool already takes its cell.
 *
 * tools/guard_family_sites.json ALREADY HOLDS all 92 direct sites with their
 * EAX resolved by a previous angr pass: 78 as expressions such as
 * `&([edx + 0x3b968])`, and 14 marked <clobbered> because the base was not
 * tracked.  Those 14 are not really unresolved - they are the
 * g_clientContext-relative idiom this tree uses everywhere, `add eax,<off>`
 * after a load of [0x5b3484], written `&DAT_00xxxxxx + g_clientContext` in C.
 * Seven of them share one offset (0x67e3cc) AND one identical window,
 * `cmp byte ptr [eax + 0x45127], 2 / sete`, which gives them a distinctive
 * source-side anchor to pair against.
 *
 * NOT SWEPT HERE, deliberately.  This is the exact class where a naive zip of
 * cells onto sites previously put 75 PeekBool cells on the WRONG sites
 * (ac41638) - see the cvalueguard-migration notes - so any pass over these 92
 * has to go through tools/guard_callsite_verify.py rather than trusting the
 * ordering of the cache. The 78 resolved expressions also still need their
 * register mapped to a caller local per site, which is what
 * tools/guard_cell_resolve.py exists for.
 *
 * CELL RECOVERED AT 34 SITES (2026-08-21) FROM THE BOOL'S OWN OFFSET.  The
 * guard cell sits FOUR BYTES ABOVE the boolean it guards, so where the C
 * already passes the bool as `X[0x3d2] != 0` the cell is X + 0xf4c - derived
 * entirely from the argument already in the source, with no pairing and no
 * per-site disassembly.
 *
 * Checked against the cached resolver rows (tools/guard_family_sites.json):
 * of the 35 sites whose bool offset is derivable, 34 have bool_offset + 4
 * among the cell offsets their caller actually uses in the binary.  The one
 * exception is DetonateSuperShot_Bullet12, whose cache holds only the other
 * cell - left bare rather than forced.
 *
 * The cell is APPENDED rather than placed first (PeekPacketChecksumBool takes
 * its cell first) so that the 60 still-1-argument call sites keep compiling
 * against the K&R-empty declaration in functions.h.  Consistency with the
 * family loses to keeping a partial migration buildable.
 *
 * NOT RECOVERED: 40 sites pass a comparison rather than a field test
 * (`iVar5 < iVar6`), so there is no offset to derive from, and 4 pass nothing
 * at all.  Those need the cached rows paired to sites - which for this family
 * means extending guard_callsite_verify.py, since it only knows Peek,
 * PeekBool and Encode.  Cell offsets are overwhelmingly two values, 0xf4c and
 * 0x391b, and in 27 of the 33 two-site callers they appear in VA order
 * (0x391b, 0xf4c) - suggestive, but VA order is not source order, which is
 * exactly the trap that has to be verified rather than assumed. */
#include "ghidra_types.h"


undefined4 CheckGuardedBoolAnd(int param_1,byte *cell)

{
  
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if ((byte)((*cell + cell[1]) - 0x34) == cell[2]) {
    if (((cell[1] >> (*cell & 7) & 1) == 1) && (param_1 != '\0')) {
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      return 1;
    }
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return 0;
}

