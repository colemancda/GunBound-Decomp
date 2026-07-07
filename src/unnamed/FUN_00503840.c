/* FUN_00503840 - 0x00503840 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

bool __fastcall FUN_00503840(uint param_1,char *param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  char local_1780 [6000];
  uint local_10;
  undefined4 uStack_c;
  
  uStack_c = 0x503850;
  if (((int)param_1 < 1) || (6000 < (int)param_1)) {
    return false;
  }
  if (*(int *)(param_3 + 0x28) == 0) {
    while (iVar2 = send(*(SOCKET *)(param_3 + 8),param_2,param_1,0), iVar2 != -1) {
      param_1 = param_1 - iVar2;
      param_2 = param_2 + iVar2;
      if ((int)param_1 < 1) {
        return true;
      }
    }
    iVar2 = WSAGetLastError();
    if (iVar2 != 0x2733) {
      return false;
    }
  }
  uVar1 = *(undefined4 *)(param_3 + 0x24);
  pcVar4 = local_1780;
  for (uVar3 = param_1 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)param_2;
    param_2 = param_2 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar3 = param_1 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar4 = *param_2;
    param_2 = param_2 + 1;
    pcVar4 = pcVar4 + 1;
  }
  local_10 = param_1;
  iVar2 = FUN_00504420(local_1780,uVar1,0);
  if (*(int **)(param_3 + 0x24) != (int *)0x0) {
    **(int **)(param_3 + 0x24) = iVar2;
    *(int *)(param_3 + 0x24) = iVar2;
    return iVar2 != 0;
  }
  *(int *)(param_3 + 0x20) = iVar2;
  *(int *)(param_3 + 0x24) = iVar2;
  return iVar2 != 0;
}

