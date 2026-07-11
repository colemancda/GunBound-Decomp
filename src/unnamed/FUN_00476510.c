/* FUN_00476510 - 0x00476510 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00476510(void)

{
  int iVar1;
  byte bVar2;
  undefined4 *unaff_ESI;
  
  InitProjectile(unaff_ESI,0x186a2);
  *unaff_ESI = &PTR_FUN_00555f9c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = _rand();
  *(char *)((int)unaff_ESI + 0xf45) = (char)iVar1;
  iVar1 = _rand();
  *(byte *)((int)unaff_ESI + 0xf46) = (byte)iVar1;
  bVar2 = *(byte *)((int)unaff_ESI + 0xf45) & 7;
  bVar2 = ~('\x01' << bVar2) & (byte)iVar1 | '\0' << bVar2;
  *(byte *)((int)unaff_ESI + 0xf46) = bVar2;
  *(byte *)((int)unaff_ESI + 0xf47) = bVar2 + *(byte *)((int)unaff_ESI + 0xf45) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

