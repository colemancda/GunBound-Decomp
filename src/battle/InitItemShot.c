/* InitItemShot - 0x00476510 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_00476510).  The ITEM SHOT projectile's
 * constructor: delegates to InitProjectile with class id 100002 and installs
 * vtable 0x555f9c.  Two independent things identify the class - SpawnItemShot's
 * sibling SpawnItemProjectile calls it directly as its constructor (orig
 * 0x4317eb `call 0x476510`, right after its operator_new(0x3fa8)), and slot 6
 * of 0x555f9c is DetonateItemShot, which appears in exactly ONE vtable.
 *
 * The 2026-08-19 constructor-naming pass skipped this one because its unique
 * slot carries no `_Bullet<N>` suffix to vote on; the slot is still unique, so
 * the identification is just as firm.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 *
 * DROPPED-REG FIX (2026-08-31): this arrives in ESI (SpawnItemProjectile's
 * `mov esi,eax` from operator_new right before the call), promoted to
 * regEsi; the ctor returns it (`mov eax,esi / pop ebx / ret` at 0x47659a),
 * so the fabricated `return 0` becomes `return regEsi`.
 */
#include "ghidra_types.h"


undefined4 * InitItemShot(undefined4 *regEsi)

{
  int iVar1;
  byte bVar2;

  InitProjectile(regEsi,0x186a2);
  *regEsi = &PTR_FUN_00555f9c;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = _rand();
  *(char *)((int)regEsi + 0xf45) = (char)iVar1;
  iVar1 = _rand();
  *(byte *)((int)regEsi + 0xf46) = (byte)iVar1;
  bVar2 = *(byte *)((int)regEsi + 0xf45) & 7;
  bVar2 = ~('\x01' << bVar2) & (byte)iVar1 | '\0' << bVar2;
  *(byte *)((int)regEsi + 0xf46) = bVar2;
  *(byte *)((int)regEsi + 0xf47) = bVar2 + *(byte *)((int)regEsi + 0xf45) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return regEsi;
}

