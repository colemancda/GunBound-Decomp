/* DeleteSuperMine - 0x00491b10 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_00491b10).  The super mine's scalar-deleting
 * destructor and slot 0 of vtable 0x556380:
 *     DestroySuperMine(this); if (flags & 1) _free(this); return this;
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void * __thiscall DeleteSuperMine(void *param_1,int param_2)

{
  DestroySuperMine((undefined4 *)param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

