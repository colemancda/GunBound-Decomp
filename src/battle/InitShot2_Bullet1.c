/* InitShot2_Bullet1 - 0x00468860 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_00468860).  Constructor for one per-weapon PROJECTILE
 * class: it delegates to InitProjectile(this, 0x186a2) - class id 100002,
 * stamped at object +0x4 - and installs vtable 0x555dac.
 *
 * The bullet identity comes from that vtable's slots.  Slots SHARED with
 * other projectile vtables carry no information (that is how the multi-class
 * virtuals like DetonateSuperShot_Bullet2_8_11 are named in the first place),
 * so only slots UNIQUE to this vtable were used, and every one of them agrees
 * on a single role and bullet number.  See the commit for the census.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


undefined4 InitShot2_Bullet1(void)

{
  undefined4 *unaff_ESI;
  
  InitProjectile(unaff_ESI,0x186a2);
  *unaff_ESI = &PTR_FUN_00555dac;
  *(undefined1 *)(unaff_ESI + 0xfe7) = 0;
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

