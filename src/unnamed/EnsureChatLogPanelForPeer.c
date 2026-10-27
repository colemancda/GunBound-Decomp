/* EnsureChatLogPanelForPeer - 0x004025e0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-26), HIGH. Three callers - FUN_00507310, already-named
 * DisplayIncomingWhisper, and FUN_004024f0 - all funnel into this on the
 * roster container &DAT_00e53e88, right after a PanelManager_FindByName
 * miss (panel key 0x4e21 = 20001, BuildChatLogPanel's class per
 * docs/widgets.md). On that miss it finds-or-builds a throwaway roster
 * node for the peer via FindDirectLinkBuddyNode/operator_new(0x5c) -
 * stamped with the same vtable (&PTR_FUN_00551cb4) UpsertDirectLinkBuddyNode
 * uses - calls BuildChatLogPanel with it, and then frees the throwaway
 * node (vtable slot 0, `delete[]` flag 1) if it was newly allocated here
 * rather than found. So: ensure a chat-log panel exists for this peer,
 * building both the roster entry and the panel on first contact.
 */
#include "ghidra_types.h"


void EnsureChatLogPanelForPeer(undefined4 param_1,char *param_2)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  undefined4 *puVar4;
  
  iVar3 = PanelManager_FindByName((int)&g_uiPanelManager);
  if (iVar3 == 0) {
    puVar4 = (undefined4 *)FindDirectLinkBuddyNode(param_1, param_2);
    bVar2 = false;
    if (puVar4 == (undefined4 *)0x0) {
      puVar4 = operator_new(0x5c);
      if (puVar4 == (undefined4 *)0x0) {
        puVar4 = (undefined4 *)0x0;
      }
      else {
        puVar4[1] = 0;
        puVar4[2] = 0xffffffff;
        puVar4[3] = 0;
        puVar4[4] = 0;
        *(undefined1 *)(puVar4 + 5) = 0;
        *(undefined1 *)((int)puVar4 + 0x15) = 0;
        *puVar4 = &PTR_FUN_00551cb4;
        *(undefined1 *)(puVar4 + 0xc) = 0;
        *(undefined4 *)((int)puVar4 + 0x31) = 0xffffffff;
        *(undefined4 *)((int)puVar4 + 0x35) = 0xffffffff;
        *(undefined4 *)((int)puVar4 + 0x39) = 0xffffffff;
        *(undefined4 *)((int)puVar4 + 0x3d) = 0xffffffff;
      }
      iVar3 = 0x21 - (int)param_2;
      do {
        cVar1 = *param_2;
        param_2[(int)puVar4 + iVar3] = cVar1;
        param_2 = param_2 + 1;
      } while (cVar1 != '\0');
      *(undefined2 *)((int)puVar4 + 0x2e) = 500;
      bVar2 = true;
    }
    BuildChatLogPanel(&g_uiPanelManager,puVar4);
    if ((bVar2) && (puVar4 != (undefined4 *)0x0)) {
      (**(code **)*puVar4)(1);
    }
  }
  return;
}

