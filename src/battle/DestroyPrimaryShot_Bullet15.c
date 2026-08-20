/* DestroyPrimaryShot_Bullet15 - 0x0047b2e0 in the original binary.
 *
 * NAMED 2026-08-19 (was a FUN_ name).  A per-weapon projectile destructor, in
 * the same MSVC derived-destructor shape as the CMobile family:
 *     *this = &PTR_FUN_00556058;   install this class's own vtable
 *     DestroyProjectile(this);      chain to the base
 * The bullet identity comes from that vtable, using only slots UNIQUE to it -
 * slots shared between projectile vtables carry no information.  See the
 * commit that named the 33 projectile constructors for the method.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void DestroyPrimaryShot_Bullet15(void)

{
  undefined4 *in_EAX;
  
  *in_EAX = &PTR_FUN_00556058;
  DestroyProjectile(in_EAX);
  return;
}

