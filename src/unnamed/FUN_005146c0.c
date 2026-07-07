/* FUN_005146c0 - 0x005146c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_005146c0(char *param_1,uint param_2,undefined4 *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  if (10000 < param_2) {
    param_2 = 10000;
  }
  *param_3 = 0;
  if (*param_1 == -1) {
    if ((param_1[1] & 0xf0U) == 0xf0) {
      bVar1 = false;
    }
    else {
      if ((param_1[1] & 0xf0U) != 0xe0) {
        return 0;
      }
      bVar1 = true;
    }
    *param_3 = 1;
    if (bVar1) {
      *param_3 = 2;
    }
    param_3[1] = ((byte)param_1[1] & 8) >> 3;
    param_3[2] = (byte)param_1[1] >> 1 & 3;
    iVar5 = param_3[2];
    param_3[3] = (byte)param_1[1] & 1;
    param_3[4] = (uint)((byte)param_1[2] >> 4);
    param_3[5] = ((byte)param_1[2] & 0xc) >> 2;
    param_3[6] = (byte)param_1[2] >> 1 & 1;
    param_3[7] = (byte)param_1[2] & 1;
    param_3[8] = (uint)((byte)param_1[3] >> 6);
    param_3[9] = ((byte)param_1[3] & 0x30) >> 4;
    param_3[10] = ((byte)param_1[3] & 8) >> 3;
    param_3[0xb] = ((byte)param_1[3] & 4) >> 2;
    param_3[0xc] = (byte)param_1[3] & 3;
    if ((0 < iVar5) && (iVar5 < 4)) {
      iVar2 = param_3[4];
      if (0 < iVar2) {
        if (iVar5 == 3) {
          return (*(int *)(&DAT_00563bec + (param_3[1] * 0x10 + iVar2) * 4) * 0xf0) /
                 *(int *)(&DAT_00563bcc + (param_3[5] + param_3[1] * 4) * 4) << 2;
        }
        if (iVar5 == 2) {
          iVar5 = param_3[1];
          iVar2 = *(int *)(&DAT_00563b4c + (iVar5 * 0x10 + iVar2) * 4);
        }
        else {
          if (iVar5 != 1) {
            return 0;
          }
          iVar5 = param_3[1];
          if (iVar5 == 0) {
            if (!bVar1) {
              return (*(int *)(&DAT_00563c6c + iVar2 * 4) * 0x5a0) /
                     *(int *)(&DAT_00563bcc + param_3[5] * 4);
            }
            return (*(int *)(&DAT_00563c6c + iVar2 * 4) * 0xb40) /
                   *(int *)(&DAT_00563bcc + param_3[5] * 4);
          }
          iVar2 = *(int *)(&DAT_00563c6c + (iVar5 * 0x10 + iVar2) * 4);
        }
        return (iVar2 * 0xb40) / *(int *)(&DAT_00563bcc + (param_3[5] + iVar5 * 4) * 4);
      }
      iVar5 = 0x18;
      param_3 = (undefined4 *)0x1;
      if ((param_1[1] & 6U) == 6) {
        param_3 = (undefined4 *)0x4;
      }
      uVar4 = (byte)param_1[2] >> 1 & 1;
      iVar2 = param_2 - 3;
      do {
        if (iVar5 < iVar2) {
          do {
            if ((*param_1 == param_1[iVar5]) && (iVar6 = iVar5, param_1[1] == param_1[iVar5 + 1]))
            goto LAB_005148dd;
            iVar5 = iVar5 + 1;
          } while (iVar5 < iVar2);
        }
        iVar6 = 0;
LAB_005148dd:
        iVar5 = iVar6 + 1;
        iVar6 = iVar6 - uVar4;
        if (iVar6 < 1) {
          return 0;
        }
        iVar7 = 0;
        iVar3 = uVar4 * (int)param_3 + iVar6;
        if (iVar3 <= iVar2) {
          do {
            if ((*param_1 != param_1[iVar3]) || (param_1[1] != param_1[iVar3 + 1])) {
              iVar7 = -iVar7;
              break;
            }
            iVar7 = iVar7 + 1;
            iVar3 = iVar3 + ((byte)param_1[iVar3 + 2] >> 1 & 1) * (int)param_3 + iVar6;
          } while (iVar3 <= iVar2);
        }
        if (0 < iVar7) {
          return iVar6;
        }
        if (1999 < iVar5) {
          return 0;
        }
      } while( true );
    }
  }
  return 0;
}

