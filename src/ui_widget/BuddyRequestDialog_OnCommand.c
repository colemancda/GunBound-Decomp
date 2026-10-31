/* BuddyRequestDialog_OnCommand - 0x005063e0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NAMED 2026-10-31 (was FUN_005063e0). Slot 7 (OnCommand, +0x1c) of
 * vtable 0x557d50, which only BuildBuddyRequestDialog installs (the
 * store at 0x508d87) - the dialog raised for an incoming buddy request
 * (Language.txt 4001, "'%s'asks for your permission.\nDo you
 * accept?"). Label 0 calls AnswerBuddyRequestByNickname with 1, label 1
 * with 0 (push 1 / push 0 at 0x5063ff / 0x5063fb), each with the
 * requester's name from +0x50, then sets the +0x1d close flag that
 * PanelManager_Update's per-tick sweep destroys panels on. Named
 * after the builder, like AddBuddyDialog_OnCommand.
 */
#include "ghidra_types.h"


void __thiscall BuddyRequestDialog_OnCommand(int param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    if (param_3 == 0) {
      uVar1 = 1;
    }
    else {
      if (param_3 != 1) goto LAB_00506412;
      uVar1 = 0;
    }
    AnswerBuddyRequestByNickname(&DAT_00e53e88,uVar1,(char *)*(int *)(param_1 + 0x50));
    *(undefined1 *)(param_1 + 0x1d) = 1;
  }
LAB_00506412:
  Widget_OnCommandDefault(param_1,param_2,param_3,param_4);
  return;
}

