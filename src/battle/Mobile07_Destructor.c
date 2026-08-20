/* Mobile07_Destructor - 0x00484fe0 in the original binary.
 *
 * NAMED 2026-08-19 (was a FUN_ name).  The mobile-type 07 destructor.  Its
 * whole body is the MSVC derived-destructor pattern - install this type's own
 * vtable, then chain to the base:
 *     *this = &PTR_FUN_005561ec;
 *     CMobile_BaseDestructor(this);
 * 0x5561ec is the vtable the census already labels with this type's
 * MainAction, which is what ties the destructor to the type.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void Mobile07_Destructor(void)

{
  undefined4 *in_EAX;
  
  *in_EAX = &PTR_FUN_005561ec;
  CMobile_BaseDestructor(in_EAX);
  return;
}

