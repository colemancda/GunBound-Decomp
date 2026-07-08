/* FUN_00458a00 - 0x00458a00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00458a00(int *param_1,int *param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7,char param_8,char param_9)

{
  char cVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (param_4 != 0) {
    param_7 = param_7 - param_6 * in_EAX;
    iVar4 = param_4 - in_EAX;
    if (iVar4 < param_4) {
      param_3 = iVar4 * param_5 + param_3;
      iVar2 = g_clientContext;
      while( true ) {
        param_7 = param_7 + param_6;
        iVar3 = param_7 >> 0x10;
        if (((((param_8 != '\0') && (-1 < iVar3)) && (iVar3 < *(int *)(&DAT_006a7720 + iVar2))) &&
            ((-1 < param_3 && (param_3 < *(int *)(&DAT_006a7724 + iVar2))))) &&
           (*(char *)(param_3 * *(int *)(&DAT_006a7720 + iVar2) + *(int *)(&DAT_006a773c + iVar2) +
                     iVar3) != '\0')) {
          *param_1 = iVar3;
          *param_2 = param_3;
          return;
        }
        if ((param_9 != '\0') &&
           (cVar1 = FUN_00450e10(param_3), iVar2 = g_clientContext, cVar1 != '\0')) break;
        iVar4 = iVar4 + 1;
        param_3 = param_3 + param_5;
        if (param_4 <= iVar4) {
          return;
        }
      }
      *param_1 = iVar3;
      *param_2 = param_3;
    }
  }
  return;
}

