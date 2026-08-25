/* FUN_0042b010 - 0x0042b010 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0042b010(int regEdi)

{
  byte bVar1;
  int iVar2;
  byte bVar3;
  
  InitGuardedBool();
  *(undefined4 *)(regEdi + 8) = 0;
  *(undefined4 *)(regEdi + 0xc) = 0;
  *(undefined4 *)(regEdi + 0x10) = 0;
  *(undefined4 *)(regEdi + 0x14) = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = _rand();
  *(byte *)(regEdi + 4) = (byte)iVar2;
  iVar2 = _rand();
  bVar1 = *(byte *)(regEdi + 4);
  *(byte *)(regEdi + 5) = (byte)iVar2;
  bVar3 = bVar1 & 7;
  bVar3 = ~('\x01' << bVar3) & (byte)iVar2 | '\0' << bVar3;
  *(byte *)(regEdi + 5) = bVar3;
  *(byte *)(regEdi + 6) = bVar3 + bVar1 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return;
}

