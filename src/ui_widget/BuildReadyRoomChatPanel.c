/* BuildReadyRoomChatPanel - 0x005094f0 in the original binary.
 *
 * Builds the Ready Room chat-log panel (a 480x160 scrollbar-only CPanel, vtable 0x557ee0, at the bottom of the screen). Its row renderer draws color-coded chat messages. See docs/widgets.md. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * BuildReadyRoomChatPanel(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053ca9b) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  puVar1 = operator_new(0x90);
  local_4 = 0;
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    Panel_BaseConstructor(puVar1);
    *puVar1 = &PTR_LAB_00557ee0;
    *(undefined1 *)(puVar1 + 0xe) = 1;
    *(undefined1 *)((int)puVar1 + 5) = 1;
    *(undefined1 *)((int)puVar1 + 0x1e) = 1;
  }
  local_4 = 0xffffffff;
  puVar1[0x13] = 0;
  puVar1[9] = 2000;
  puVar1[0x11] = 10000;
  puVar1[0x12] = 0xb;
  puVar1[10] = 0x15;
  puVar1[0xb] = 0x181;
  puVar1[0xc] = 0x1e0;
  puVar1[0xd] = 0xa0;
  uVar2 = CreateScrollListWidget(param_1,0x1c7,0x33,0x12,0x45,9);
  Widget_AddChild(uVar2);
  PanelManager_Register(puVar1);
  return puVar1;
}

