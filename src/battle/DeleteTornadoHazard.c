/* DeleteTornadoHazard - 0x004ac650 in the original binary.
 *
 * NAMED 2026-08-19 (was a FUN_ name).  CTornadoHazard's scalar-deleting
 * destructor and slot 0 of vtable 0x5565e4 - the address src/cxx/Hazards.h
 * already documents for that slot.  Canonical shape:
 *     DestroyTornadoHazard(this); if (flags & 1) _free(this); return this;
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void * __thiscall DeleteTornadoHazard(void *param_1,int param_2)

{
  DestroyTornadoHazard(param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

