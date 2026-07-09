/* BuildWorldListPanel - 0x005099d0 in the original binary.
 *
 * Builds the Server/Channel Select screen's "WORLD LIST" panel (called only
 * from State02_ServerSelect_OnEnter). Allocates a ~545x530 panel object
 * (vtable PTR_LAB_00557f08) at (0xb,0xd) and adds three children: two panel
 * buttons (msg 0x44c = "View All", msg 0x44d = "Friends") and a scroll-list
 * widget (CreateScrollListWidget) that spans the panel. Registers the panel
 * with the global UI panel manager (g_uiPanelManager). This is the scrollable
 * server browser seen on screen; see docs/screens/02_server_select.md.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * BuildWorldListPanel(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053ca9b) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  puVar1 = operator_new(0x94);
  local_4 = 0;
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    FUN_00505760(puVar1);
    *puVar1 = &PTR_LAB_00557f08;
    puVar1[0x24] = 0xffffffff;
    *(undefined1 *)(puVar1 + 0xe) = 1;
    *(undefined1 *)((int)puVar1 + 5) = 0;
  }
  local_4 = 0xffffffff;
  puVar1[9] = 9000;
  puVar1[0x13] = 0;
  puVar1[0x11] = 0x2711;
  puVar1[0x12] = 0;
  puVar1[10] = 0xb;
  puVar1[0xb] = 0xd;
  puVar1[0xc] = 0x221;
  puVar1[0xd] = 0x212;
  iVar2 = CreateLabelWidget(0,0x44c,0x145,0x1eb,0x4a,0x1a);
  *(undefined1 *)(iVar2 + 0x3a) = 1;
  Widget_AddChild(iVar2);
  uVar3 = CreateLabelWidget(1,0x44d,0x1a3,0x1eb,0x4a,0x1a);
  Widget_AddChild(uVar3);
  uVar3 = CreateScrollListWidget(param_1,0x203,0x4a,0x12,0x179,0);
  Widget_AddChild(uVar3);
  FUN_0050eea0(puVar1);
  return puVar1;
}

