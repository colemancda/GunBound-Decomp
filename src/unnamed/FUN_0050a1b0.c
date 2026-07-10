/* FUN_0050a1b0 - 0x0050a1b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __thiscall FUN_0050a1b0(int param_1,int param_2,int param_3)

{
  undefined *puVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  undefined4 extraout_EAX;
  uint uVar5;
  
  puVar1 = g_gameStateVTableArray[7];
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = CONCAT31((int3)((uint)extraout_EAX >> 8),iVar4 != 0);
  if (iVar4 == 0) {
    uVar5 = PeekPacketChecksumBool();
    if ((char)uVar5 != '\x01') {
      uVar5 = PeekPacketChecksumBool();
      if (((char)uVar5 != '\x01') && (uVar5 = g_stateChangeInProgress, g_stateChangeInProgress == 0)
         ) {
        iVar4 = FUN_0050cdb0();
        if ((iVar4 != -1) &&
           ((uint)(*(int *)(puVar1 + 0x454) + iVar4) < *(uint *)(g_clientContext + 0x44e24))) {
          QueueOutgoingPacketField(iVar4);
          *(undefined1 *)(param_1 + 0x90) = 1;
          FUN_0050ce60(param_1);
          FUN_0050cdf0(param_1);
        }
        cVar2 = FUN_005052b0();
        cVar3 = FUN_00505430(param_2,param_3);
        if ((cVar2 == '\0') && (cVar3 == '\0')) {
          QueueOutgoingPacketField(0xffffffff);
          FUN_0050cdf0(param_1);
        }
        if ((((0x239 < param_2) && (param_2 < 0x275)) && (0x2b < param_3)) && (param_3 < 0x67)) {
          puVar1[0x31484] = 1;
        }
        if ((cVar3 == '\0') && (cVar2 == '\0')) {
          return 0;
        }
        return 1;
      }
    }
  }
  return uVar5 & 0xffffff00;
}

