/* Mobile01_Destructor - 0x00488ab0 in the original binary.
 *
 * NAMED 2026-08-19 (was a FUN_ name).  The mobile-type 01 destructor.  Its
 * whole body is the MSVC derived-destructor pattern - install this type's own
 * vtable, then chain to the base:
 *     *this = &PTR_FUN_00556230;
 *     CMobile_BaseDestructor(this);
 * 0x556230 is the vtable the census already labels with this type's
 * MainAction, which is what ties the destructor to the type.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 *
 * DROPPED-REG FIX (2026-08-31): this arrives in EAX (the wrapper's
 * `mov eax,esi`), promoted to regEax.
 */
#include "ghidra_types.h"


void Mobile01_Destructor(undefined4 *regEax)

{
  *regEax = &PTR_FUN_00556230;
  CMobile_BaseDestructor(regEax);
  return;
}

