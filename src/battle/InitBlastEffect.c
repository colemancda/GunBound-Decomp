/* InitBlastEffect - 0x004aa830 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_004aa830).  Constructor for the 0x3fa0-byte BLAST
 * effect object.  All three of its callers are blast spawns that allocate
 * exactly that size and then hand the object to it: SpawnBlastEffect
 * (0x431d90, the terrain blast with the "<N>blast.xes" table), FUN_00432320
 * (its sibling, same table and same "flame%d%d" state) and
 * SpawnLightningBlastEffect (0x434fc0, "lightningblast.xes").  It delegates
 * to InitProjectile with class id 100002 and installs vtable 0x55656c.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
*
 * DROPPED REGISTER RECOVERED (2026-08-27): unaff_ESI is the object being
 * initialised.  The first statement hands it to InitProjectile as the object
 * and the second stamps its vtable through it, and the function RETURNS it
 * (`mov eax,esi` at 0x4aa8ba) -- which is why the callers assign the result
 * and then index it.
 *
 * All three sites are the same idiom and each is witnessed by its own
 * caller's source: `operator_new(0x3fa0)` on the line above, a null check,
 * and `mov esi,eax` inside the non-null branch immediately before the call.
 * So ESI is the allocation the caller already names -- pvVar2, pvVar4,
 * pvVar2 -- and nothing rests on pairing, since all three callers hold one
 * site each.
 */
#include "ghidra_types.h"


undefined4 InitBlastEffect(undefined4 *regEsi)

{
  int iVar1;
  byte bVar2;
  undefined4 *unaff_ESI = regEsi;
  
  InitProjectile(unaff_ESI,0x186a2);
  *unaff_ESI = &PTR_FUN_0055656c;
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

