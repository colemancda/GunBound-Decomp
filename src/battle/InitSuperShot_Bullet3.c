/* InitSuperShot_Bullet3 - 0x0048b3f0 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_0048b3f0).  Constructor for one per-weapon PROJECTILE
 * class: it delegates to InitProjectile(this, 0x186a2) - class id 100002,
 * stamped at object +0x4 - and installs vtable 0x556284.
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
 * DROPPED-REG FIX (2026-08-31): `this` arrives in ESI (Ghidra's unaff_ESI),
 * promoted to parameter regEsi; the binary tail is `mov eax,esi / ret`, so
 * the return value is the object itself.
 */
#include "ghidra_types.h"


undefined4 * InitSuperShot_Bullet3(undefined4 *regEsi)

{
  InitProjectile(regEsi,0x186a2);
  *(undefined1 *)(regEsi + 0xfe7) = 0;
  regEsi[0xfe8] = 0;
  *regEsi = &PTR_FUN_00556284;
  regEsi[0xfe9] = 4;
  return regEsi;
}

