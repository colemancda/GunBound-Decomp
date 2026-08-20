/* DeleteMobile - 0x0045a540 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_0045a540).  CMobile's scalar-deleting destructor
 * and its vtable slot 0, in the canonical MSVC shape:
 *     CMobile_BaseDestructor(this); if (flags & 1) _free(this); return this;
 * Named to match the DeleteJewel / DeletePoisonedBaseObject convention the
 * other slot-0 entries already use.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void * __thiscall DeleteMobile(void *param_1,int param_2)

{
  CMobile_BaseDestructor(param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

