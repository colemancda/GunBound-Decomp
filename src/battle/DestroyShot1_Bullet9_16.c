/* DestroyShot1_Bullet9_16 - 0x0046e590 in the original binary.
 *
 * NAMED 2026-08-19 (was a FUN_ name).  A per-weapon projectile destructor, in
 * the same MSVC derived-destructor shape as the CMobile family:
 *     *this = &PTR_FUN_00555e88;   install this class's own vtable
 *     DestroyProjectile(this);      chain to the base
 * The bullet identity comes from that vtable, using only slots UNIQUE to it -
 * slots shared between projectile vtables carry no information.  See the
 * commit that named the 33 projectile constructors for the method.
 *
 * DROPPED-REG FIX (2026-08-31): this arrives in EAX (the wrapper does
 * mov eax,esi right before the call), promoted to the regEax parameter.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void DestroyShot1_Bullet9_16(undefined4 *regEax)

{
  *regEax = &PTR_FUN_00555e88;
  DestroyProjectile(regEax);
  return;
}

