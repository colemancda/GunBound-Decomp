/* Mobile15_Destructor - 0x00466fc0 in the original binary.
 *
 * DROPPED-REG FIX (2026-08-31): this arrives in EAX (the wrapper at
 * 0x466fa0 does mov esi,ecx / mov eax,esi before the call), promoted
 * to regEax - the same stereotype as the fifteen Mobile00-14 siblings
 * swept in dd65a54e; this one was missed in that batch's roster.
 *
 * NAMED 2026-08-19 (was a FUN_ name).  The mobile-type 15 destructor.  Its
 * whole body is the MSVC derived-destructor pattern - install this type's own
 * vtable, then chain to the base:
 *     *this = &PTR_FUN_00555d54;
 *     CMobile_BaseDestructor(this);
 * 0x555d54 is the vtable the census already labels with this type's
 * MainAction, which is what ties the destructor to the type.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void Mobile15_Destructor(undefined4 *regEax)

{
  
  *regEax = &PTR_FUN_00555d54;
  CMobile_BaseDestructor(regEax);
  return;
}

