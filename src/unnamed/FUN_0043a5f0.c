/* FUN_0043a5f0 - 0x0043a5f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_0043a5f0(void)

{
  uint uVar1;
  int *piVar2;
  undefined4 uVar3;
  int *piVar4;
  
  piVar4 = *(int **)(*(int *)(&DAT_006a7f8c + DAT_005b3484) + 0x1c);
  uVar1 = piVar4[1];
  if (uVar1 < 0x186a2) {
    while (uVar1 != 0x186a1) {
      piVar4 = (int *)piVar4[7];
      uVar1 = piVar4[1];
      if (0x186a1 < uVar1) {
        return;
      }
    }
    for (piVar2 = (int *)piVar4[4]; piVar4 != piVar2; piVar2 = (int *)piVar2[4]) {
      uVar3 = (**(code **)(*piVar2 + 0x14))();
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
  }
  return;
}

