/* CheckBothGuardedBools - 0x00406710 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * BOTH CELLS RECOVERED AT 8 OF 36 SITES (2026-08-21).  The two guard cells
 * arrive in EAX and EDI, and the OFFSETS are effectively fixed across the
 * whole call graph: EAX is <obj> + 0xf3f at 35 of 36 sites and EDI is
 * <obj> + 0xf42 at 35 of 37.  Only the BASE varies, and it is always the
 * caller's object pointer (esi, ebp or ebx depending on the function).
 *
 * The base is not guessed.  guard_dominator_base.resolve() proves which write
 * reaches the site, and at 8 sites it resolves to `this` - so the cells are
 * (byte *)param_1 + 0xf3f and + 0xf42.  All 8 callers are
 * `__fastcall(int *param_1)` Detonate* functions, each with exactly ONE
 * zero-argument call site, so the pairing is forced rather than inferred, and
 * at every one EAX and EDI share the same base register.
 *
 * The other 28 sites are UNRESOLVED by the same analysis - the base comes
 * through a spill or a path the dominance check will not certify - and are
 * left bare.  That is the honest split: the offsets are known for all 36, but
 * an offset without a proven base is not a cell, and writing one that is
 * wrong is how this family previously ended up with 75 misassigned cells.
 *
 * Signature order follows the family (cells first), which is safe here
 * BECAUSE every remaining site passes nothing at all - there is no partial
 * argument list to keep aligned, unlike CheckGuardedBoolAnd where the bool
 * was already being passed and the cell had to be appended. */
#include "ghidra_types.h"


undefined4 CheckBothGuardedBools(byte *cellA,byte *cellB)

{
  char cVar1;
  char cVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((byte)((*cellA + cellA[1]) - 0x34) == cellA[2]) {
    cVar2 = '\x01' - ((cellA[1] >> (*cellA & 7) & 1) != 1);
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    cVar2 = '\0';
  }
  if ((byte)((*cellB + cellB[1]) - 0x34) == cellB[2]) {
    cVar1 = '\x01' - ((cellB[1] >> (*cellB & 7) & 1) != 1);
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    cVar1 = '\0';
  }
  if ((cVar2 != '\0') && (cVar1 != '\0')) {
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    return 1;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return 0;
}

