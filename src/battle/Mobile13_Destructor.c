/* Mobile13_Destructor - 0x0046cba0 in the original binary.
 *
 * NAMED 2026-08-19 (was a FUN_ name).  The mobile-type 13 destructor.  Its
 * whole body is the MSVC derived-destructor pattern - install this type's own
 * vtable, then chain to the base:
 *     *this = &PTR_FUN_00555e54;
 *     CMobile_BaseDestructor(this);
 * 0x555e54 is the vtable the census already labels with this type's
 * MainAction, which is what ties the destructor to the type.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void Mobile13_Destructor(void)

{
  undefined4 *in_EAX;
  
  *in_EAX = &PTR_FUN_00555e54;
  CMobile_BaseDestructor(in_EAX);
  return;
}

