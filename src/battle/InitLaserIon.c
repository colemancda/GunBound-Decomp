/* InitLaserIon - 0x0047f9e0 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_0047f9e0).  Constructor for the LASER ion aura
 * (see SpawnLaserIon, its only caller): delegates to
 * InitProjectile(this, 0x186a5) - class id 100005 - and installs vtable
 * 0x556110.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


undefined4 InitLaserIon(void)

{
  undefined4 *unaff_ESI;
  
  InitProjectile(unaff_ESI,0x186a5);
  unaff_ESI[0xfec] = 0;
  unaff_ESI[0xfea] = 0;
  unaff_ESI[0xfeb] = 0;
  *(undefined1 *)(unaff_ESI + 0xfe8) = 0;
  unaff_ESI[0xfef] = 0;
  *(undefined1 *)(unaff_ESI + 0xff1) = 0;
  *(undefined1 *)(unaff_ESI + 0xff8) = 0;
  *unaff_ESI = &PTR_FUN_00556110;
  unaff_ESI[0xff0] = 0xffffffff;
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

