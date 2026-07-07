/* FUN_0043c550 - 0x0043c550 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_0043c550(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  char cVar3;
  int iVar4;
  
  iVar1 = *(int *)(*(int *)(&DAT_006a7f8c + DAT_005b3484) + 0x1c);
  uVar2 = *(uint *)(iVar1 + 4);
  while( true ) {
    if (0x186a1 < uVar2) {
      return 0xffffffff;
    }
    if (uVar2 == 0x186a1) break;
    iVar1 = *(int *)(iVar1 + 0x1c);
    uVar2 = *(uint *)(iVar1 + 4);
  }
  iVar4 = *(int *)(iVar1 + 0x10);
  if (iVar1 == iVar4) {
    return 0xffffffff;
  }
  while( true ) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((byte)(*(byte *)(iVar4 + 0x908) + *(byte *)(iVar4 + 0x909) + -0x34) ==
        *(char *)(iVar4 + 0x90a)) {
      cVar3 = '\x01' - ((*(byte *)(iVar4 + 0x909) >> (*(byte *)(iVar4 + 0x908) & 7) & 1) != 1);
    }
    else {
      DAT_00793514 = 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      cVar3 = '\0';
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((cVar3 == '\x01') && (cVar3 = FUN_0045d640(param_1,param_2), cVar3 != '\0')) break;
    iVar4 = *(int *)(iVar4 + 0x10);
    if (iVar1 == iVar4) {
      return 0xffffffff;
    }
  }
  return *(uint *)(iVar4 + 8) & 7;
}

