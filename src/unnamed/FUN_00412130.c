/* FUN_00412130 - 0x00412130 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00412130(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  void *pvVar4;
  
LAB_00412140:
  do {
    while( true ) {
      if (DAT_00795074 == DAT_00795070) {
        return;
      }
      iVar1 = *(int *)(&DAT_00795078 + DAT_00795074 * 4);
      uVar2 = *(uint *)(&DAT_00795878 + DAT_00795074 * 4);
      iVar3 = *(int *)(&DAT_00796078 + DAT_00795074 * 4);
      DAT_00795074 = DAT_00795074 + 1 & 0x800001ff;
      if ((int)DAT_00795074 < 0) {
        DAT_00795074 = (DAT_00795074 - 1 | 0xfffffe00) + 1;
      }
      if (((g_stateChangeInProgress == 0) || (999999 < uVar2)) && (DAT_0056d108 == -1)) {
        (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x14))(iVar1,uVar2,iVar3);
      }
      pvVar4 = DAT_007934f4;
      if (iVar1 == 0) goto LAB_004122c7;
      if (iVar1 == 0x32) break;
      if (iVar1 == 0x65) {
        if (uVar2 == 3) {
          if (DAT_007934f4 != (void *)0x0) {
            FUN_00405930();
            _free(pvVar4);
          }
          DAT_007934f4 = (void *)0x0;
          DAT_00793529 = 1;
        }
        else {
          ShowErrorDialog(1);
          pvVar4 = DAT_007934f4;
          if (DAT_007934f4 != (void *)0x0) {
            iVar1 = *(int *)((int)DAT_007934f4 + 0x2004);
            *(undefined4 *)(iVar1 + 0x22c) = 1;
            if (*(SOCKET *)(iVar1 + 0x24) != 0xffffffff) {
              closesocket(*(SOCKET *)(iVar1 + 0x24));
            }
            *(undefined4 *)(iVar1 + 0x24) = 0xffffffff;
            *(undefined1 *)(iVar1 + 0x22a) = 0;
            *(undefined1 *)((int)pvVar4 + 0x2009) = 0;
          }
        }
      }
    }
  } while (((uVar2 != 0x1c) && (uVar2 != 0x9c)) || (g_stateChangeInProgress == 0));
  goto LAB_0041225f;
LAB_004122c7:
  if ((uVar2 == 1000000) && (iVar3 == 1000000)) {
LAB_0041225f:
    g_stateChangeInProgress = 0;
    RemoveWidget();
    _DAT_00e53c24 = 0;
    _DAT_00e53c28 = 799;
    _DAT_00e53c2c = 0;
    _DAT_00e53c30 = 599;
    if (DAT_0079350c != '\0') {
      g_pendingGameState = 0xf;
      g_stateChangeRequested = 0;
      DAT_0056d108 = 0;
      _DAT_007934d8 = 1;
    }
  }
  goto LAB_00412140;
}

