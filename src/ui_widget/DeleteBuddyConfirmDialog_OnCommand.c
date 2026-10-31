/* DeleteBuddyConfirmDialog_OnCommand - 0x00506430 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NAMED 2026-10-31 (was FUN_00506430). Slot 7 (OnCommand, +0x1c) of
 * vtable 0x557e40, which only BuildDeleteBuddyConfirmDialog installs
 * (the store at 0x508f27) - the confirm raised by the buddy panel's Del
 * label (Language.txt 4005, "You are about to remove '%s' from buddy
 * list.\nAre you sure?"). Label 0 calls DeleteBuddyByNickname with the
 * name stored at +0x50 (0x506456); labels 0 and 1 both set the +0x1d
 * close flag. Named after the builder, like
 * BuddyRequestDialog_OnCommand.
 */
#include "ghidra_types.h"


void __thiscall DeleteBuddyConfirmDialog_OnCommand(int param_1,int param_2,int param_3,undefined4 param_4)

{
  if (param_2 == 0) {
    if (param_3 == 0) {
      DeleteBuddyByNickname(&DAT_00e53e88,(char *)*(int *)(param_1 + 0x50));
    }
    else if (param_3 != 1) goto LAB_00506460;
    *(undefined1 *)(param_1 + 0x1d) = 1;
  }
LAB_00506460:
  Widget_OnCommandDefault(param_1,param_2,param_3,param_4);
  return;
}

