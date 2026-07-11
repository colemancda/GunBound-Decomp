/* FUN_00451270 - 0x00451270 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_00451270(undefined4 *param_1)

{
  byte bVar1;
  int iVar2;
  byte bVar3;
  
  InitProjectile(param_1,0x186a2);
  *param_1 = &PTR_FUN_00555bd0;
  InitGuardedBool();
  InitGuardedBool();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = _rand();
  *(byte *)(param_1 + 0xfe7) = (byte)iVar2;
  iVar2 = _rand();
  bVar1 = *(byte *)(param_1 + 0xfe7);
  *(byte *)((int)param_1 + 0x3f9d) = (byte)iVar2;
  bVar3 = '\x01' << (bVar1 & 7);
  bVar3 = ~bVar3 & (byte)iVar2 | bVar3;
  *(byte *)((int)param_1 + 0x3f9d) = bVar3;
  *(byte *)((int)param_1 + 0x3f9e) = bVar3 + bVar1 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = _rand();
  *(byte *)((int)param_1 + 0x3f9f) = (byte)iVar2;
  iVar2 = _rand();
  bVar1 = *(byte *)((int)param_1 + 0x3f9f);
  *(byte *)(param_1 + 0xfe8) = (byte)iVar2;
  bVar3 = bVar1 & 7;
  bVar3 = ~('\x01' << bVar3) & (byte)iVar2 | '\0' << bVar3;
  *(byte *)(param_1 + 0xfe8) = bVar3;
  *(byte *)((int)param_1 + 0x3fa1) = bVar3 + bVar1 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return param_1;
}

