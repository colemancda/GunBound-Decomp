/* FUN_005098e0 - 0x005098e0 in the original binary.
 *
 * CPanelManager::PruneByKey - the sole caller ChangeGameState.c passes
 * threshold 10000, so on every state change this destroys every registered
 * panel whose key (+0x24) is BELOW 10000, i.e. the state-specific panels
 * (WorldList 0x2328, LobbyChat 0x2329, ChannelUserList 0x232a, ...), while
 * the shared BuddyPanel (key 20000) survives. `in_EAX` (the manager object)
 * arrives via a dropped EAX register - orig 0x412349 `mov eax,0xe53c40`
 * (g_uiPanelManager) before the call - promoted to an explicit parameter,
 * which is exactly what the sole caller already passes.
 *
 * RESTORED (2026-07-20): was a no-op stub whose comment claimed
 * g_uiPanelManager was a 1-byte placeholder. That is stale - the manager is
 * now the real sized object (globals.c: uint8_t g_uiPanelManager[0x1c]),
 * constructed by FUN_00507dc0 and populated by PanelManager_Register ->
 * PanelManager_PrependNode, so the node list at +4 is valid. With this
 * stubbed, entering the lobby never destroyed ServerSelect's panels: they
 * (and every prior state's panels) persisted and drew on top of / behind the
 * lobby's own panels - the duplicated-panels + garbled-tiles the live
 * original-vs-port lobby comparison showed (build/shots/).
 *
 * Faithful port of the 0x5098e0 disassembly. Intrusive doubly-linked list:
 * a node is {+0 next, +4 prev, +8 panel}; the manager holds head at +4, tail
 * at +8, count at +0xc, and a node free-list head at +0x14. A pruned node is
 * unlinked, pushed onto the free-list, its panel destroyed
 * (WidgetChildArray_Destroy = the +0x50e560 dtor) and freed; when the count
 * hits zero the whole pool is released (PanelManager_ReleasePool 0x509fd0).
 * The original advances to the next node BEFORE unlinking the current one.
 */
#include "ghidra_types.h"

void FUN_005098e0(int manager, int threshold)

{
  int *node;
  int *next;
  int *prev;
  int *panel;

  node = *(int **)(manager + 4);              /* list head */
  while (node != (int *)0x0) {
    panel = *(int **)((int)node + 8);
    next = *(int **)node;                      /* advance before any unlink */
    if (*(int *)((int)panel + 0x24) < threshold) {
      /* unlink `node` from the doubly-linked list */
      prev = *(int **)((int)node + 4);
      if (node == *(int **)(manager + 4)) {
        *(int **)(manager + 4) = next;         /* it was the head */
      }
      else {
        *(int **)prev = next;                  /* prev->next = next */
      }
      if (node == *(int **)(manager + 8)) {
        *(int **)(manager + 8) = prev;         /* it was the tail */
      }
      else {
        *(int **)((int)next + 4) = prev;       /* next->prev = prev */
      }
      /* push the freed node onto the manager's node free-list (+0x14) */
      *(int **)node = *(int **)(manager + 0x14);
      *(int **)(manager + 0x14) = node;
      *(int *)(manager + 0xc) = *(int *)(manager + 0xc) + -1;
      if (*(int *)(manager + 0xc) == 0) {
        PanelManager_ReleasePool((undefined4 *)(manager + 4));
      }
      WidgetChildArray_Destroy((undefined4 *)panel);
      _free(panel);
    }
    node = next;
  }
  return;
}
