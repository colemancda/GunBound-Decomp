/* DeleteMine - 0x00497870 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_00497870).  CMine's scalar-deleting destructor,
 * in the canonical MSVC shape:
 *     CMine_BaseDestructor(this); if (flags & 1) _free(this); return this;
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void * __thiscall DeleteMine(void *param_1,int param_2)

{
  CMine_BaseDestructor(param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

