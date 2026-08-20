/* DeletePrimaryShot_Bullet15 - 0x0047b2c0 in the original binary.
 *
 * NAMED 2026-08-19 (was a FUN_ name).  slot 0, the scalar-deleting destructor of the PrimaryShot_Bullet15 class's
 * vtable.  The class was already fixed by a slot UNIQUE to that vtable (see
 * the InitPrimaryShot_Bullet15 / DestroyPrimaryShot_Bullet15 notes); this slot's role comes from the
 * CProjectile slot map in src/cxx/Projectile.h, and the name was only
 * assigned because this function too appears in exactly one vtable - a slot
 * shared between vtables would say nothing about which class it belongs to.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void * __thiscall DeletePrimaryShot_Bullet15(void *param_1,int param_2)

{
  DestroyPrimaryShot_Bullet15();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

