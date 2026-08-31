/* DestroyItemShot - 0x004765c0 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_004765c0).  The item shot's derived destructor -
 * install its own vtable, chain to the base:
 *     *this = &PTR_FUN_00555f9c;
 *     DestroyProjectile(this);
 * 0x555f9c is InitItemShot's vtable, whose slot 6 (DetonateItemShot) is unique
 * to it.
 * DROPPED-REG FIX (2026-08-31): this arrives in EAX (the wrapper does
 * mov eax,esi right before the call), promoted to the regEax parameter.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void DestroyItemShot(undefined4 *regEax)

{
  *regEax = &PTR_FUN_00555f9c;
  DestroyProjectile(regEax);
  return;
}

