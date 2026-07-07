/* FUN_00420650 - 0x00420650 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00420650(int param_1,int param_2,int param_3)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint local_8;
  int local_4;
  
  local_8 = 0xffffffff;
  local_4 = -1;
  iVar5 = 0;
  do {
    if (iVar5 != param_3) {
      piVar1 = (int *)(param_1 + 0x459bc + (param_2 * 0x14 + iVar5) * 4);
      uVar2 = *(int *)(param_1 + 0x45c3c + (param_2 * 0x14 + iVar5) * 4) + *piVar1;
      uVar4 = 1;
      if (uVar2 != 0) {
        uVar4 = uVar2;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar4 = (uint)(*piVar1 * iVar3) / uVar4;
      if ((int)local_8 < (int)uVar4) {
        local_8 = uVar4;
        local_4 = iVar5;
      }
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 < 0x14);
  return local_4;
}

