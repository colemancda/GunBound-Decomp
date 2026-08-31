/* InitShot2_Bullet8 - 0x004a7000 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_004a7000).  Constructor for one per-weapon PROJECTILE
 * class: it delegates to InitProjectile(this, 0x186a2) - class id 100002,
 * stamped at object +0x4 - and installs vtable 0x556524.
 *
 * The bullet identity comes from that vtable's slots.  Slots SHARED with
 * other projectile vtables carry no information (that is how the multi-class
 * virtuals like DetonateSuperShot_Bullet2_8_11 are named in the first place),
 * so only slots UNIQUE to this vtable were used, and every one of them agrees
 * on a single role and bullet number.  See the commit for the census.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 *
 * DROPPED-REG FIX (2026-08-31): `this` arrives in ESI (Ghidra's regEsi),
 * promoted to the regEsi parameter; the binary tail `mov eax,esi` makes the
 * return value the object itself, replacing the fabricated return-0.
 */
#include "ghidra_types.h"


undefined4 * InitShot2_Bullet8(undefined4 *regEsi)

{
  InitProjectile(regEsi,0x186a2);
  *regEsi = &PTR_FUN_00556524;
  return regEsi;
}

