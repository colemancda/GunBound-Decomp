/* DeleteJewel - 0x004780c0 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_004780c0).  CJewel's scalar-deleting destructor
 * and slot 0 of vtable 0x555fdc - see src/cxx/Jewel.h, which the same day's
 * Tier-1 coverage pass promoted.  31 bytes.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void * __thiscall DeleteJewel(void *param_1,int param_2)

{
  FUN_004780e0(param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

