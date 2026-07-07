/* FUN_0043c3c0 - 0x0043c3c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0043c3c0(void)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar4 = *(int *)(*(int *)(&DAT_006a7f8c + DAT_005b3484) + 0x1c);
  uVar1 = *(uint *)(iVar4 + 4);
  if (uVar1 < 0x186a4) {
    while (uVar1 != 0x186a3) {
      iVar4 = *(int *)(iVar4 + 0x1c);
      uVar1 = *(uint *)(iVar4 + 4);
      if (0x186a3 < uVar1) {
        return;
      }
    }
    for (iVar2 = *(int *)(iVar4 + 0x10); iVar4 != iVar2; iVar2 = *(int *)(iVar2 + 0x10)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      *(undefined4 *)(iVar2 + 0x3fac) = uVar3;
      *(undefined4 *)(iVar2 + 0x3fd0) = 0;
      *(undefined4 *)(iVar2 + 0x3fb0) = 0;
    }
  }
  return;
}

