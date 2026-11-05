/* CommP2POwner_SendBuddyAnswer - 0x004fd7c0 in the original binary.
 *
 * NAMING (batch 22, was FUN_004fd7c0): Slot 9 of vtable 0x5575c8, reached
 * by AnswerBuddyRequestByNickname; relays type 0xc042 plus the accept
 * byte, whose receiver is MessengerNotify_OnBuddyAnswer (language strings
 * 4002 agreed / 4003 rejected).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined1 __thiscall CommP2POwner_SendBuddyAnswer(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  
  if (*(char *)(param_1 + 0x1a70) == '\0') {
    return 0;
  }
  cVar1 = (char)FUN_004fcf10(&param_3,1,0xc042,(int *)param_1,param_2);
  /* 0x4fd7ec test al,al uses the AL returned by 0x4fcf10. */
  if (cVar1 == '\0') {
    return 0;
  }
  if (param_3 != '\0') {
    FUN_004fcee0((char *)param_2,param_1);
  }
  return 1;
}

