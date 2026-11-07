/* FUN_005099b0 - 0x005099b0 in the original binary.
 *
 * Clears the byte at +0x1e of every panel on the UI panel manager's list.
 * ChangeGameState calls it right before the new state's OnEnter. The
 * manager arrives in EAX (orig 0x412455: `mov eax, 0xe53c40` =
 * g_uiPanelManager, then `call 0x5099b0` at 0x41245a). Disassembly
 * 0x5099b0-0x5099ce: node = mgr[+4]; if (node) do { cur = node;
 * node = *node; *(byte *)(cur[+8] + 0x1e) = 0; } while (node); the same
 * list shape PanelManager_PruneBelowId walks (head at +4, next at node+0,
 * panel at node+8). RESTORED 2026-11-06: this was a no-op bring-up stub.
 */
#include "ghidra_types.h"


void FUN_005099b0(int manager)

{
  int *node;
  int *cur;

  node = *(int **)(manager + 4);
  if (node != (int *)0x0) {
    do {
      cur = node;
      node = (int *)*node;
      *(undefined1 *)(cur[2] + 0x1e) = 0;
    } while (node != (int *)0x0);
  }
  return;
}
