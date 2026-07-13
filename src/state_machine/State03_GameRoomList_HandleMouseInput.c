/* State03_GameRoomList_HandleMouseInput - 0x00428b90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall State03_GameRoomList_HandleMouseInput(int param_1,uint param_2,undefined4 param_3,uint param_4)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  
  if (param_2 < 0x204) {
    if (param_2 == 0x203) {
      iVar3 = RoomCardHitTest(param_4 >> 0x10,0);
      if (iVar3 != -1) {
        cVar2 = FUN_00406400();
        if (cVar2 == '\x01') {
          FUN_004f2da0();
          return;
        }
      }
    }
    else if ((param_2 != 0x100) && (param_2 == 0x201)) {
      iVar3 = RoomCardHitTest(param_4 >> 0x10,0);
      if (iVar3 != -1) {
        *(int *)(param_1 + 4) = iVar3;
        InvokeWidget(5,1);
      }
      *(undefined4 *)(param_1 + 0x124) = 0xffffffff;
      FUN_00507d50();
      return;
    }
  }
  else if (param_2 == 0x204) {
    iVar4 = RoomCardHitTest(param_4 >> 0x10,1);
    iVar1 = DAT_007934e8;
    iVar3 = g_clientContext;
    if ((iVar4 != -1) && (*(int *)(g_clientContext + 0x4464c + iVar4 * 4) == 1)) {
      *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
      *(undefined2 *)(iVar1 + 0x4d4) = 0x2104;
      *(undefined2 *)(iVar1 + 0x4d6) = *(undefined2 *)(iVar3 + 0x44664 + iVar4 * 4);
      *(int *)(iVar1 + 0x44d0) = *(int *)(iVar1 + 0x44d0) + 2;
      SendOutgoingPacket(iVar1);
      *(int *)(param_1 + 0x124) = iVar4;
      puVar5 = (undefined4 *)(param_1 + 0x220);
      for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      puVar5 = (undefined4 *)(param_1 + 0x1b8);
      for (iVar3 = 0x1a; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      return;
    }
    *(undefined4 *)(param_1 + 0x124) = 0xffffffff;
  }
  return;
}

