/* FUN_00451030 - 0x00451030 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00451030(int param_1)

{
  uint uVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(*(int *)(in_EAX + 4) + 0x1c);
  uVar1 = *(uint *)(iVar4 + 4);
  while( true ) {
    if (500 < uVar1) {
      return 0;
    }
    if (uVar1 == 500) break;
    iVar4 = *(int *)(iVar4 + 0x1c);
    uVar1 = *(uint *)(iVar4 + 4);
  }
  iVar4 = *(int *)(iVar4 + 0x10);
  if (*(char *)(iVar4 + 0x15) != '\0') {
    return 0;
  }
  while( true ) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = (int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2;
    if ((iVar2 - iVar3 < param_1) && (param_1 < iVar2 + iVar3)) break;
    iVar4 = *(int *)(iVar4 + 0x10);
    if (*(char *)(iVar4 + 0x15) != '\0') {
      return 0;
    }
  }
  return iVar4;
}

