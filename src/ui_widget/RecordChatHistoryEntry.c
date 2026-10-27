/* FUN_00423050 - 0x00423050 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00423050(int param_1,byte *param_2)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  byte *pbVar7;
  char *pcVar8;
  byte *pbVar9;
  bool bVar10;
  
  iVar6 = 0;
  *(int *)(&DAT_005f3760 + param_1) = *(int *)(&DAT_005f375c + param_1);
  if (0 < *(int *)(&DAT_005f375c + param_1)) {
    pbVar3 = &DAT_005f325c + param_1;
    pbVar7 = param_2;
    pbVar9 = pbVar3;
LAB_00423076:
    do {
      bVar1 = *pbVar3;
      bVar10 = bVar1 < *pbVar7;
      if (bVar1 == *pbVar7) {
        if (bVar1 != 0) {
          bVar1 = pbVar3[1];
          bVar10 = bVar1 < pbVar7[1];
          if (bVar1 != pbVar7[1]) goto LAB_0042309a;
          pbVar3 = pbVar3 + 2;
          pbVar7 = pbVar7 + 2;
          if (bVar1 != 0) goto LAB_00423076;
        }
        iVar4 = 0;
      }
      else {
LAB_0042309a:
        iVar4 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
      }
      if (iVar4 == 0) {
        return;
      }
      iVar6 = iVar6 + 1;
      pbVar3 = pbVar9 + 0x80;
      pbVar7 = param_2;
      pbVar9 = pbVar3;
    } while (iVar6 < *(int *)(&DAT_005f375c + param_1));
  }
  if (*(int *)(&DAT_005f375c + param_1) == 10) {
    pcVar5 = &DAT_005f32dc + param_1;
    iVar6 = 9;
    pcVar8 = pcVar5;
    do {
      do {
        cVar2 = *pcVar5;
        pcVar5[-0x80] = cVar2;
        pcVar5 = pcVar5 + 1;
      } while (cVar2 != '\0');
      pcVar5 = pcVar8 + 0x80;
      iVar6 = iVar6 + -1;
      pcVar8 = pcVar5;
    } while (iVar6 != 0);
    *(undefined4 *)(&DAT_005f375c + param_1) = 9;
  }
  pbVar3 = &DAT_005f325c + param_1 + *(int *)(&DAT_005f375c + param_1) * 0x80;
  do {
    bVar1 = *param_2;
    param_2 = param_2 + 1;
    *pbVar3 = bVar1;
    pbVar3 = pbVar3 + 1;
  } while (bVar1 != 0);
  iVar6 = *(int *)(&DAT_005f375c + param_1);
  *(int *)(&DAT_005f375c + param_1) = iVar6 + 1;
  *(int *)(&DAT_005f3760 + param_1) = iVar6 + 1;
  return;
}

