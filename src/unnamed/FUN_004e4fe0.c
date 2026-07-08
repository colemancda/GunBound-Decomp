/* FUN_004e4fe0 - 0x004e4fe0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall
FUN_004e4fe0(int param_1,int param_2,int *param_3,int *param_4,int param_5,char param_6,char param_7
            )

{
  bool bVar1;
  char cVar2;
  int in_EAX;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  iVar7 = *param_3;
  uVar3 = param_1 - iVar7 >> 0x1f;
  uVar4 = in_EAX - *param_4 >> 0x1f;
  iVar8 = ((param_1 - iVar7 ^ uVar3) - uVar3) + 1;
  iVar6 = ((in_EAX - *param_4 ^ uVar4) - uVar4) + 1;
  if (iVar6 < iVar8) {
    iVar6 = *param_4 - in_EAX;
    bVar1 = param_1 <= iVar7;
    iVar7 = in_EAX * 0x10000;
    if (param_1 <= *(int *)(param_2 + 0x18)) {
      iVar5 = g_clientContext;
      do {
        iVar7 = iVar7 + ((iVar6 * 0x10000) / iVar8) * param_5;
        in_EAX = iVar7 >> 0x10;
        if (param_1 < 0) {
          return 0;
        }
        if (in_EAX < -500) {
          return 0;
        }
        if (*(int *)(param_2 + 0x1c) < in_EAX) {
          return 0;
        }
        if (((((param_6 != '\0') && (param_1 < *(int *)(&DAT_006a7720 + iVar5))) && (-1 < in_EAX))
            && ((in_EAX < *(int *)(&DAT_006a7724 + iVar5) &&
                (*(char *)(*(int *)(&DAT_006a7720 + iVar5) * in_EAX +
                           *(int *)(&DAT_006a773c + iVar5) + param_1) != '\0')))) ||
           ((param_7 != '\0' && (cVar2 = FUN_00450e10(in_EAX), iVar5 = g_clientContext, cVar2 != '\0'))
           )) {
LAB_004e51d2:
          *param_3 = param_1;
          *param_4 = in_EAX;
          return 1;
        }
        param_1 = param_1 + ((uint)bVar1 * 2 + -1) * param_5;
      } while (param_1 <= *(int *)(param_2 + 0x18));
    }
  }
  else {
    bVar1 = in_EAX <= *param_4;
    iVar6 = (((iVar7 - param_1) * 0x10000) / iVar6) * param_5;
    iVar7 = param_1 * 0x10000 + iVar6;
    param_1 = iVar7 >> 0x10;
    if (param_1 <= *(int *)(param_2 + 0x18)) {
      iVar8 = g_clientContext;
      while (((-1 < param_1 && (-0x1f5 < in_EAX)) && (in_EAX <= *(int *)(param_2 + 0x1c)))) {
        if ((((param_6 != '\0') && (param_1 < *(int *)(&DAT_006a7720 + iVar8))) &&
            ((-1 < in_EAX &&
             ((in_EAX < *(int *)(&DAT_006a7724 + iVar8) &&
              (*(char *)(*(int *)(&DAT_006a7720 + iVar8) * in_EAX + *(int *)(&DAT_006a773c + iVar8)
                        + param_1) != '\0')))))) ||
           ((param_7 != '\0' && (cVar2 = FUN_00450e10(in_EAX), iVar8 = g_clientContext, cVar2 != '\0'))
           )) goto LAB_004e51d2;
        iVar7 = iVar7 + iVar6;
        in_EAX = in_EAX + ((uint)bVar1 * 2 + -1) * param_5;
        param_1 = iVar7 >> 0x10;
        if (*(int *)(param_2 + 0x18) < param_1) {
          return 0;
        }
      }
    }
  }
  return 0;
}

