/* DestroySuperMine - 0x00491b30 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_00491b30).  The SUPER MINE's derived destructor -
 * install its own vtable, chain to the mine base:
 *     *this = &PTR_FUN_00556380;
 *     CMine_BaseDestructor(this);
 * 0x556380 is the vtable SpawnSuperMine installs (SpawnSuperMine.c line 57),
 * which is what identifies the class; SpawnMine leaves InitMine's 0x5563f0 in
 * place, so the super variant is the only one that overrides.
 * DROPPED-REG FIX (2026-08-31): this arrives in EAX (the wrapper does
 * mov eax,esi right before the call), promoted to the regEax parameter.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void DestroySuperMine(undefined4 *regEax)

{
  *regEax = &PTR_FUN_00556380;
  CMine_BaseDestructor(regEax);
  return;
}

