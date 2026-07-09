/* FUN_004ed870 - 0x004ed870 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_004ed870(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  int in_EAX;
  int iVar3;
  ushort *puVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  ushort *puVar8;
  ushort *puVar9;
  int local_c;
  int local_8;
  
  if (((DAT_0079352c != 0) && (-1 < param_1)) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
    iVar2 = *(int *)(iVar3 + 0x28);
    iVar7 = in_EAX + *(int *)(iVar3 + 0x2c);
    puVar4 = *(ushort **)(iVar3 + 0x34);
    iVar3 = *(int *)(iVar3 + 0x24);
    iVar5 = 0;
    local_8 = iVar3;
    if (iVar7 < DAT_00793534) {
      iVar5 = DAT_00793534 - iVar7;
      iVar7 = iVar7 + iVar5;
      local_8 = iVar3 - iVar5;
    }
    if (DAT_0056df34 < local_8 + iVar7) {
      local_8 = (DAT_0056df34 - iVar7) + 1;
    }
    if (iVar5 <= iVar3) {
      if (0 < iVar5) {
        do {
          iVar5 = iVar5 + -1;
          puVar4 = puVar4 + *puVar4;
        } while (iVar5 != 0);
      }
      iVar3 = DAT_0056df30;
      if (0 < local_8) {
        do {
          uVar1 = puVar4[1];
          puVar8 = puVar4 + 2;
          puVar4 = puVar4 + *puVar4;
          local_c = 0;
          if (uVar1 != 0) {
            do {
              uVar6 = (uint)puVar8[1];
              iVar7 = (uint)*puVar8 + param_2 + iVar2;
              iVar5 = uVar6 + iVar7;
              if (iVar3 < iVar7) break;
              if (DAT_00793530 < iVar5) {
                if (iVar7 < DAT_00793530) {
                  if (iVar3 < iVar5) {
                    iVar5 = iVar3 + 1;
                  }
                  puVar9 = puVar8 + (DAT_00793530 - iVar7) + 2;
                  iVar7 = DAT_00793530;
                }
                else {
                  if (iVar3 < iVar5) {
                    FUN_004e9130(iVar7,iVar3 + 1,puVar8 + 2);
                    iVar3 = DAT_0056df30;
                    break;
                  }
                  puVar9 = puVar8 + 2;
                }
                FUN_004e9130(iVar7,iVar5,puVar9);
                uVar6 = (uint)puVar8[1];
                iVar3 = DAT_0056df30;
              }
              puVar8 = puVar8 + uVar6 + 2;
              local_c = local_c + 1;
            } while (local_c < (int)(uint)uVar1);
          }
          local_8 = local_8 + -1;
        } while (local_8 != 0);
      }
    }
  }
  return;
}

