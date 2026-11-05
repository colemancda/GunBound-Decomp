/* CommP2POwner_SendBuddyStatus - 0x004fd590 in the original binary.
 *
 * NAMING (batch 22, was FUN_004fd590): Slot 6 of vtable 0x5575c8; relays
 * type 0xc051, whose receiver is MessengerNotify_OnBuddyStatus
 * (UpdateBuddyStatus); MessengerNotify_OnStatusQuery and the DLNoticeFn
 * callers dispatch through this slot.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

uint __thiscall CommP2POwner_SendBuddyStatus(int param_1,undefined4 param_2,undefined4 *param_3,char *param_4)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  undefined4 local_1778;
  undefined4 local_1774;
  undefined4 local_1770;
  undefined4 local_176c;
  undefined4 local_1768;
  undefined4 local_1764;
  char local_1760 [5972];
  undefined4 uStack_c;
  
  uStack_c = 0x4fd5a0;
  if (*(char *)(param_1 + 0x1a70) != '\0') {
    pcVar2 = param_4 + 1;
    pcVar3 = param_4;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    uVar4 = (int)pcVar3 - (int)pcVar2;
    if ((int)uVar4 < 0x81) {
      local_1778 = *param_3;
      local_1774 = param_3[1];
      local_1770 = param_3[2];
      local_176c = param_3[3];
      local_1768 = param_3[4];
      local_1764 = param_3[5];
      pcVar2 = local_1760;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar2 = *(undefined4 *)param_4;
        param_4 = param_4 + 4;
        pcVar2 = pcVar2 + 4;
      }
      for (uVar5 = uVar4 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar2 = *param_4;
        param_4 = param_4 + 1;
        pcVar2 = pcVar2 + 1;
      }
      uVar4 = FUN_004fcf10(&local_1778,
                           local_1760 +
                           CONCAT22((short)(uVar4 >> 0x10),(short)uVar4 - (short)&local_1778),
                           0xc051,(int *)param_1,param_2);
      return uVar4;
    }
  }
  /* 0x4fd5d3 xor al,al; ret 0xc -- not connected, or name longer than 0x80:
     returns false. */
  return 0;
}

