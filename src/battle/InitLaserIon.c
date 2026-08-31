/* InitLaserIon - 0x0047f9e0 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_0047f9e0).  Constructor for the LASER ion aura
 * (see SpawnLaserIon, its only caller): delegates to
 * InitProjectile(this, 0x186a5) - class id 100005 - and installs vtable
 * 0x556110.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 *
 * DROPPED-REG FIX (2026-08-31): this arrives in ESI (SpawnLaserIon's
 * `mov esi,eax` from operator_new right before the call), promoted to
 * regEsi; the ctor returns it (`mov eax,esi / ret` at 0x47fa27), so the
 * fabricated `return 0` becomes `return regEsi`.
 */
#include "ghidra_types.h"


undefined4 * InitLaserIon(undefined4 *regEsi)

{
  InitProjectile(regEsi,0x186a5);
  regEsi[0xfec] = 0;
  regEsi[0xfea] = 0;
  regEsi[0xfeb] = 0;
  *(undefined1 *)(regEsi + 0xfe8) = 0;
  regEsi[0xfef] = 0;
  *(undefined1 *)(regEsi + 0xff1) = 0;
  *(undefined1 *)(regEsi + 0xff8) = 0;
  *regEsi = &PTR_FUN_00556110;
  regEsi[0xff0] = 0xffffffff;
  return regEsi;
}

