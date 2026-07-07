/* FUN_004257b0 - 0x004257b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004257b0(void)

{
  uint uVar1;
  uint *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint local_20 [8];
  
  iVar4 = 0;
  puVar2 = local_20;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *puVar2 = uVar1;
    iVar4 = iVar4 + 0x224;
    puVar2 = puVar2 + 1;
  } while (iVar4 < 0x1120);
  iVar4 = 1;
  puVar2 = local_20;
  iVar3 = 7;
  iVar5 = iVar4;
  do {
    for (; iVar4 < 8; iVar4 = iVar4 + 1) {
      uVar1 = *puVar2;
      if (local_20[iVar4] < uVar1) {
        *puVar2 = local_20[iVar4];
        local_20[iVar4] = uVar1;
      }
    }
    iVar4 = iVar5 + 1;
    puVar2 = puVar2 + 1;
    iVar3 = iVar3 + -1;
    iVar5 = iVar4;
  } while (iVar3 != 0);
  return local_20[1];
}

