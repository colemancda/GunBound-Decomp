/* FUN_004e1170 - 0x004e1170 in the original binary.
 *
 * State02_ServerSelect vtable slot 5 - click/action handler. On
 * param_2==0 dispatches by param_4: 0 = quit-game request, 1 = open the
 * buddy panel, 2 = connect to the currently-highlighted server slot
 * (validates the slot is online, the SERVER button is enabled, and the
 * slot isn't full before calling ConnectToSelectedServer). No confirmed
 * real name/purpose beyond that. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ConnectToSelectedServer takes an explicit `serverIndex` 2nd parameter
 * (see that file's own header - a dropped-register-argument fix from
 * earlier this session); passes the highlighted slot (`iVar1`) here.
 */
#include "ghidra_types.h"


void __thiscall FUN_004e1170(int param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;

  if (param_2 == 0) {
    if (param_4 == 0) {
      g_pendingGameState = 0xf;
      g_stateChangeRequested = 0;
      DAT_0056d108 = 0;
      _DAT_007934d8 = 1;
      return;
    }
    if (param_4 == 1) {
      BuildBuddyPanel();
      return;
    }
    if ((((param_4 == 2) &&
         (iVar1 = *(int *)(param_1 + 8), *(char *)(g_clientContext + 0x3f809 + iVar1) != '\0')) &&
        (*(char *)(param_1 + 0x24) != '\0')) &&
       (*(ushort *)(g_clientContext + 0x410ca + iVar1 * 2) <
        *(ushort *)(g_clientContext + 0x410ea + iVar1 * 2))) {
      ConnectToSelectedServer(param_1,iVar1);
      *(undefined1 *)(param_1 + 6) = 0;
    }
  }
  return;
}
