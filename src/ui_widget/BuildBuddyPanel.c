/* BuildBuddyPanel - 0x00509110 in the original binary.
 *
 * Builds (or re-shows) the shared buddy-list panel. Registered with the global
 * panel manager (g_uiPanelManager) and used from the lobby, ready room, and
 * WndProc. It's a **singleton**: the function first walks the manager's panel
 * list for one keyed 20000 and, if found, just re-shows it (sets +0x1d = 1)
 * instead of rebuilding.
 *
 * The panel object is 0x94 bytes (vtable PTR_LAB_00557be4), key 20000, at
 * (0x238, 0xb) = (568,11), size 0xd3 x 0x10b = 211x267 (top-right of screen).
 * Resource IDs are the contiguous block 0x2bc-0x2bf. Children (positions are
 * panel-relative):
 *   CreateLabelWidget(1, 0x2bd, 0x5e, 7, 0x27, 0x14)  -> "Add" button  (94,7) 39x20
 *   CreateLabelWidget(2, 0x2be, 0x89, 7, 0x27, 0x14)  -> "Del" button  (137,7) 39x20
 *   CreateLabelWidget(0, 0x2bf, 0xb4, 7, 0x16, 0x14)  -> close (X)     (180,7) 22x20
 *   CreateScrollListWidget(mgr, 0xb7, 0x49, 0x12, 0x98, 7) -> buddy-list
 *                                                        scrollbar (183,73)
 *                                                        18x152, page size 7
 * The "n/n" buddy count/title uses resource 0x2bc (panel field +0x44 = 700).
 * The buddy list rows themselves are drawn by the panel, not child widgets.
 * See docs/widgets.md panel catalog and docs/screens/02_server_select.md.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 BuildBuddyPanel(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int unaff_ESI;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053795b) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  puVar2 = *(undefined4 **)(unaff_ESI + 4);
  do {
    if (puVar2 == (undefined4 *)0x0) {
      puVar2 = operator_new(0x94);
      local_4 = 0;
      if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
      }
      else {
        FUN_00505760(puVar2);
        *puVar2 = &PTR_LAB_00557be4;
        puVar2[0x24] = 0xffffffff;
      }
      local_4 = 0xffffffff;
      puVar2[9] = 20000;
      puVar2[0x13] = 0;
      puVar2[0x11] = 700;
      puVar2[0x12] = 0;
      puVar2[10] = 0x238;
      puVar2[0xb] = 0xb;
      puVar2[0xc] = 0xd3;
      puVar2[0xd] = 0x10b;
      uVar3 = CreateLabelWidget(0,0x2bf,0xb4,7,0x16,0x14);
      Widget_AddChild(uVar3);
      uVar3 = CreateLabelWidget(1,0x2bd,0x5e,7,0x27,0x14);
      Widget_AddChild(uVar3);
      uVar3 = CreateLabelWidget(2,0x2be,0x89,7,0x27,0x14);
      Widget_AddChild(uVar3);
      uVar3 = CreateScrollListWidget(unaff_ESI,0xb7,0x49,0x12,0x98,7);
      Widget_AddChild(uVar3);
      FUN_0050eea0(puVar2);
      return;
    }
    iVar1 = puVar2[2];
    puVar2 = (undefined4 *)*puVar2;
  } while ((*(int *)(iVar1 + 0x20) != 0) || (*(int *)(iVar1 + 0x24) != 20000));
  *(undefined1 *)(iVar1 + 0x1d) = 1;
  return;
}

