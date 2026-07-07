/* FUN_004e93e0 - 0x004e93e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e93e0(char param_1)

{
  short sVar1;
  short sVar2;
  short *psVar3;
  uint uVar4;
  int iVar5;
  int unaff_EBX;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 *local_8;
  int local_4;
  
  if ((DAT_0079352c != 0) && (local_4 = 0, 0 < *(int *)(unaff_EBX + 0x1008))) {
    local_8 = (undefined4 *)(unaff_EBX + 0x100c);
    iVar6 = DAT_0079352c;
    do {
      psVar3 = (short *)*local_8;
      iVar5 = 0;
      if (0 < *(int *)(unaff_EBX + 0x1004)) {
        do {
          if ((char)psVar3[2] == param_1) {
            sVar1 = *psVar3;
            sVar2 = psVar3[1];
            puVar7 = *(undefined4 **)(psVar3 + 4);
            puVar8 = (undefined4 *)(iVar6 + iVar5 * 2);
            for (uVar4 = ((int)sVar2 - (int)sVar1 & 0x7fffffffU) >> 1; uVar4 != 0; uVar4 = uVar4 - 1
                ) {
              *puVar8 = *puVar7;
              puVar7 = puVar7 + 1;
              puVar8 = puVar8 + 1;
            }
            for (uVar4 = ((int)sVar2 - (int)sVar1) * 2 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
              *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
              puVar7 = (undefined4 *)((int)puVar7 + 1);
              puVar8 = (undefined4 *)((int)puVar8 + 1);
            }
          }
          iVar5 = (int)psVar3[1];
          psVar3 = *(short **)(psVar3 + 6);
        } while (iVar5 < *(int *)(unaff_EBX + 0x1004));
      }
      local_4 = local_4 + 1;
      iVar6 = iVar6 + DAT_005b3620 * 2;
      local_8 = local_8 + 1;
    } while (local_4 < *(int *)(unaff_EBX + 0x1008));
  }
  return;
}

