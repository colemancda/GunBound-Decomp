/* AddBuddyDialog_SubmitBuddyName - 0x00505580 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NAMED 2026-10-31 (was FUN_00505580). Its sole caller is
 * AddBuddyDialog_OnCommand (call at 0x50573e), on the ADD label or the
 * edit box's Enter. It copies the edit box into +0x50, then: a name
 * FindDirectLinkBuddyNode already finds gets Language.txt 4004, "'%s'is
 * already registered." (push 0xfa4 at 0x50563f); the player's own
 * nickname (g_clientContext+0x23330) gets 4007, "You cannot add your
 * name to your  list." (push 0xfa7 at 0x505615); anything else goes to
 * SendBuddyRequestByNickname (0x505634). It then clears the edit box.
 * "SubmitBuddyName" follows EnterRoomNumberDialog_SubmitRoomNumber and
 * RoomTitleDialog_SubmitTitle: the dialog prefix plus the field it
 * submits.
 *
 * (FUN_00402ad0 below is now SendBuddyRequestByNickname.)
 *
 * FUN_00401bb0 CALL SITE RECOVERED (2026-10-27), part of naming that
 * function FindDirectLinkBuddyNode: at 0x5055ec the only stack push is
 * the literal container `&DAT_00e53e88`, and EBX - the lookup-key
 * register - was already set at 0x5055e2 by `mov ebx,[ebp+0x50]`, i.e.
 * `*(char **)(param_1 + 0x50)`, the same buddy-name pointer this
 * function reads again right after (0x50563b) and passes to
 * FUN_00402ad0.
 */
#include "ghidra_types.h"


void AddBuddyDialog_SubmitBuddyName(int param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  char local_100 [256];
  
  uVar2 = Widget_FindChildIndex(param_1,0,2);
  if (uVar2 != 0xffffffff) {
    if (*(uint *)(param_1 + 0x10) <= uVar2) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    pcVar5 = (char *)(*(int *)(*(int *)(param_1 + 0xc) + uVar2 * 4) + 0x38);
    pcVar4 = pcVar5;
    if (pcVar5 != (char *)0x0) {
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
    }
    AssignStringBuffer(param_1 + 0x50,pcVar5);
  }
  if (*(int *)(*(int *)(param_1 + 0x50) + -0xc) != 0) {
    iVar3 = FindDirectLinkBuddyNode(&DAT_00e53e88, *(char **)(param_1 + 0x50));
    if (iVar3 == 0) {
      iVar3 = __mbsicmp(*(uchar **)(param_1 + 0x50),(uchar *)(g_clientContext + 0x23330));
      if (iVar3 != 0) {
        SendBuddyRequestByNickname(&DAT_00e53e88,&DAT_0054b460,*(char **)(param_1 + 0x50));
        goto LAB_0050566b;
      }
      pcVar4 = (char *)GetLocalizedString(&g_localizedStringTable,0xfa7);
    }
    else {
      uVar8 = *(undefined4 *)(param_1 + 0x50);
      pcVar4 = (char *)GetLocalizedString(&g_localizedStringTable,0xfa4);
      _sprintf(local_100,pcVar4,uVar8);
      pcVar4 = local_100;
    }
    BuildItemTooltipPanel(&g_uiPanelManager,pcVar4);
  }
LAB_0050566b:
  if (uVar2 < *(uint *)(param_1 + 0x10)) {
    iVar3 = *(int *)(*(int *)(param_1 + 0xc) + uVar2 * 4);
    if (*(char *)(iVar3 + 4) != '\0') {
      SetWindowTextA(*(HWND *)(g_sharedTextInputControl + 4),&DAT_00551cb1);
    }
    puVar7 = (undefined4 *)(iVar3 + 0x38);
    for (iVar6 = 0x40; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = 0;
      puVar7 = puVar7 + 1;
    }
    *(undefined4 *)(iVar3 + 0x13c) = 0;
    return;
  }
                    /* WARNING: Subroutine does not return */
  ThrowCxxException(0x80070057);
}

