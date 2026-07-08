/* FUN_0043a530 - 0x0043a530 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_0043a530(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  
  iVar3 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar1 = *(uint *)(iVar3 + 4);
  while( true ) {
    if (0x186a2 < uVar1) {
      return 0;
    }
    if (uVar1 == 0x186a2) break;
    iVar3 = *(int *)(iVar3 + 0x1c);
    uVar1 = *(uint *)(iVar3 + 4);
  }
  iVar2 = *(int *)(iVar3 + 0x10);
  while( true ) {
    if (iVar3 == iVar2) {
      return 0;
    }
    if (*(char *)(iVar2 + 0x14) == '\0') break;
    iVar2 = *(int *)(iVar2 + 0x10);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = _rand();
  *(char *)(iVar2 + 0xf3f) = (char)iVar3;
  iVar3 = _rand();
  *(byte *)(iVar2 + 0xf40) = (byte)iVar3;
  bVar4 = '\x01' << (*(byte *)(iVar2 + 0xf3f) & 7);
  bVar4 = ~bVar4 & (byte)iVar3 | bVar4;
  *(byte *)(iVar2 + 0xf40) = bVar4;
  *(byte *)(iVar2 + 0xf41) = bVar4 + *(byte *)(iVar2 + 0xf3f) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return 1;
}

