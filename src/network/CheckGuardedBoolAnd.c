/* CheckGuardedBoolAnd - 0x00406610 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * SURVEYED 2026-08-20 - the missing argument is the GUARD CELL, and most of
 * the work is already cached.  in_EAX is a byte* to a 3-byte guard cell (the
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
 */
#include "ghidra_types.h"


undefined4 CheckGuardedBoolAnd(int param_1)

{
  byte *in_EAX;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((byte)((*in_EAX + in_EAX[1]) - 0x34) == in_EAX[2]) {
    if (((in_EAX[1] >> (*in_EAX & 7) & 1) == 1) && (param_1 != '\0')) {
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      return 1;
    }
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return 0;
}

