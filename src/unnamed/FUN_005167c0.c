/* FUN_005167c0 - 0x005167c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_005167c0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  undefined4 *puVar6;
  float10 fVar7;
  double dVar8;
  int local_2c;
  int local_28;
  
  iVar3 = 0;
  if (DAT_00563df0 != 0) {
    iVar1 = FUN_0051a420();
    dVar8 = FID_conflict__cos(1.0);
    dVar8 = dVar8 * _DAT_005448e0;
    iVar5 = 0x10;
    local_28 = 5;
    do {
      if (0 < iVar5) {
        pfVar4 = (float *)(iVar1 + iVar3 * 4);
        local_2c = 1;
        iVar3 = iVar3 + iVar5;
        iVar2 = iVar5;
        do {
          fVar7 = (float10)FUN_00527cb4((double)local_2c * (dVar8 / (double)(iVar5 * 4)));
          local_2c = local_2c + 2;
          *pfVar4 = (float)((float10)_DAT_005448d8 / fVar7);
          pfVar4 = pfVar4 + 1;
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
      iVar5 = iVar5 / 2;
      local_28 = local_28 + -1;
    } while (local_28 != 0);
    DAT_00563df0 = 0;
  }
  DAT_005ae93c = 0;
  puVar6 = &DAT_005ae940;
  for (iVar3 = 0x200; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  puVar6 = &DAT_005af144;
  for (iVar3 = 0x200; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  DAT_005af140 = 0;
  return;
}

