/* RenderWrappedText - 0x0041b4b0 in the original binary.
 *
 * Word-wraps a text string into a render buffer at (x, y) within a given wrap width. Used for the server-list descriptions and the error/message dialogs. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int RenderWrappedText(int param_1,char *param_2,int param_3,int param_4,int param_5,int param_6)

{
  char cVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int local_8;
  int local_4;
  
  iVar3 = 0;
  local_8 = 0;
  local_4 = 0;
  pcVar4 = param_2;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  if ((int)pcVar4 - (int)(param_2 + 1) <= param_5) {
    pcVar4 = param_2;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    param_5 = (int)pcVar4 - (int)(param_2 + 1);
  }
  iVar8 = 0;
  if (0 < param_5) {
    iVar9 = 0;
    pcVar4 = param_2;
    do {
      cVar1 = *pcVar4;
      pcVar5 = pcVar4;
      do {
        cVar2 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar2 != '\0');
      iVar6 = (int)pcVar5 - (int)(pcVar4 + 1);
      iVar7 = 0;
      iVar8 = iVar6;
      if (0 < iVar6) {
        do {
          iVar8 = iVar7;
          if ((pcVar4[iVar7] == ' ') || (pcVar4[iVar7] == '\n')) break;
          iVar7 = iVar7 + 1;
          iVar8 = iVar6;
        } while (iVar7 < iVar6);
      }
      if ((iVar3 == 0) && ((cVar1 == ' ' || (cVar1 == '\n')))) {
LAB_0041b65f:
        local_4 = local_4 + 1;
        pcVar4 = pcVar4 + 1;
      }
      else {
        if ((param_4 < iVar8 + iVar3) && (iVar8 < param_4)) {
          pcVar5 = (char *)(iVar9 + iVar3 + -1 + param_1);
          if (*pcVar5 == ' ') {
            *pcVar5 = '\0';
          }
          local_8 = local_8 + 1;
          iVar9 = iVar9 + param_3;
          iVar3 = 0;
        }
        if (-1 < cVar1) {
          if (cVar1 != '\r') {
            if (cVar1 == '\n') {
              if (param_6 == '\x01') {
                if (iVar3 != 0) {
LAB_0041b640:
                  pcVar5 = (char *)(iVar3 + iVar9 + -1 + param_1);
                  if (*pcVar5 == ' ') {
                    *pcVar5 = '\0';
                  }
                }
                local_8 = local_8 + 1;
                iVar9 = iVar9 + param_3;
                iVar3 = 0;
              }
            }
            else if (((cVar1 == '\\') && (param_2[local_4 + 1] == 'n')) && (param_6 == '\x01')) {
              if ((iVar3 != 0) && (pcVar5 = (char *)(iVar3 + iVar9 + -1 + param_1), *pcVar5 == ' '))
              {
                *pcVar5 = '\0';
              }
              local_8 = local_8 + 1;
              iVar9 = iVar9 + param_3;
              iVar3 = 0;
              local_4 = local_4 + 1;
              pcVar4 = pcVar4 + 1;
            }
            else {
              iVar8 = iVar9 + iVar3;
              iVar3 = iVar3 + 1;
              *(char *)(iVar8 + param_1) = cVar1;
              if (param_4 + -1 < iVar3) goto LAB_0041b640;
            }
          }
          goto LAB_0041b65f;
        }
        if (param_4 < iVar3 + 2) {
          local_8 = local_8 + 1;
          iVar9 = iVar9 + param_3;
          iVar3 = 0;
        }
        pcVar5 = (char *)(param_1 + iVar9 + iVar3);
        *pcVar5 = cVar1;
        iVar8 = local_4 + 1;
        local_4 = local_4 + 2;
        iVar3 = iVar3 + 2;
        pcVar5[1] = param_2[iVar8];
        pcVar4 = pcVar4 + 2;
      }
      iVar8 = local_8;
    } while (local_4 < param_5);
  }
  iVar3 = iVar3 + iVar8 * param_3;
  if (*(char *)(iVar3 + -1 + param_1) == ' ') {
    *(undefined1 *)(iVar3 + -1 + param_1) = 0;
  }
  return (uint)(*(char *)(iVar8 * param_3 + param_1) != '\0') + iVar8;
}

