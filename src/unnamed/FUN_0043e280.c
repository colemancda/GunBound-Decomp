/* FUN_0043e280 - 0x0043e280 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0043e280(undefined4 param_1,int param_2,short *param_3)

{
  int iVar1;
  
  iVar1 = DAT_007934e8;
  if (param_2 < 0x4000) {
    if (param_2 == 0x3fff) {
      *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
      *(undefined2 *)(iVar1 + 0x4d4) = 0x2000;
      *(undefined2 *)(iVar1 + 0x4d6) = 0xffff;
      *(int *)(iVar1 + 0x44d0) = *(int *)(iVar1 + 0x44d0) + 2;
      SendOutgoingPacket();
      *(undefined4 *)(g_clientContext + 0x44e60) = 0xffffffff;
      return;
    }
    if (param_2 == 0x2001) {
      if (*param_3 == 0) {
        (**(code **)(*(int *)g_gameStateVTableArray[0xb] + 0x20))();
        g_pendingGameState = 3;
        g_stateChangeRequested = 0;
        DAT_0056d108 = 0;
        _DAT_007934d8 = 1;
        if (DAT_007934f4 == 0) {
          FUN_00404410(&DAT_00e53e88);
          return;
        }
        FUN_00405ba0();
        return;
      }
    }
    else if (param_2 == 0x3233) {
      if (*param_3 != 0) {
        *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
        *(undefined2 *)(iVar1 + 0x4d4) = 0x2000;
        *(undefined2 *)(iVar1 + 0x4d6) = 0xffff;
        *(int *)(iVar1 + 0x44d0) = *(int *)(iVar1 + 0x44d0) + 2;
        SendOutgoingPacket();
        *(undefined4 *)(g_clientContext + 0x44e60) = 0xffffffff;
        return;
      }
      (**(code **)(*(int *)g_gameStateVTableArray[0xb] + 0x20))();
      g_pendingGameState = 9;
      g_stateChangeRequested = 0;
      DAT_0056d108 = 0;
      _DAT_007934d8 = 1;
      QueueBroadcastEvent(0x8103);
      BroadcastQueuedEvent();
      if (*(int *)(&DAT_006a64b4 + g_clientContext) != -1) {
        FUN_004eeae0();
        *(undefined4 *)(&DAT_006a64b4 + g_clientContext) = 0xffffffff;
      }
    }
  }
  else if ((param_2 == 0x4410) && (g_pendingGameState != 3)) {
    *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3232;
    *(undefined4 *)(iVar1 + 0x44d0) = 6;
    SendOutgoingPacket();
    return;
  }
  return;
}

