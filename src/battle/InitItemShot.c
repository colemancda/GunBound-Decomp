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
 */
#include "ghidra_types.h"


undefined4 InitItemShot(void)

{
  int iVar1;
  byte bVar2;
  undefined4 *unaff_ESI;
  
  InitProjectile(unaff_ESI,0x186a2);
  *unaff_ESI = &PTR_FUN_00555f9c;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = _rand();
  *(char *)((int)unaff_ESI + 0xf45) = (char)iVar1;
  iVar1 = _rand();
  *(byte *)((int)unaff_ESI + 0xf46) = (byte)iVar1;
  bVar2 = *(byte *)((int)unaff_ESI + 0xf45) & 7;
  bVar2 = ~('\x01' << bVar2) & (byte)iVar1 | '\0' << bVar2;
  *(byte *)((int)unaff_ESI + 0xf46) = bVar2;
  *(byte *)((int)unaff_ESI + 0xf47) = bVar2 + *(byte *)((int)unaff_ESI + 0xf45) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

