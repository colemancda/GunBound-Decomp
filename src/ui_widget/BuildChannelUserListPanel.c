/* BuildChannelUserListPanel - 0x00509d80 in the original binary.
 *
 * Builds the lobby channel user-list panel (a 209-wide scrollbar-only CPanel, vtable 0x557cac). Its row renderer draws up to 7 users, each with a status flag, a rank/level icon, and a name - traced from the data source (g_clientContext arrays +0x44248 index / +0x42949 flags / +0x43e48 rank). See docs/widgets.md. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * BuildChannelUserListPanel(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ca9b;
  *unaff_FS_OFFSET = &local_c;
  puVar1 = operator_new(0x90);
  local_4 = 0;
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    FUN_00505760(puVar1);
    *puVar1 = &PTR_LAB_00557cac;
    *(undefined1 *)(puVar1 + 0xe) = 1;
    *(undefined1 *)((int)puVar1 + 5) = 0;
  }
  local_4 = 0xffffffff;
  puVar1[9] = 0x232a;
  puVar1[0x13] = 0;
  puVar1[0x11] = 0x2712;
  puVar1[0x12] = 0;
  puVar1[10] = 0x23c;
  puVar1[0xb] = 0x11f;
  puVar1[0xc] = 0xd1;
  puVar1[0xd] = 0x103;
  uVar2 = CreateScrollListWidget(param_1,0xb3,0x3f,0x12,0x9a,7);
  Widget_AddChild(uVar2);
  PanelManager_Register(puVar1);
  *unaff_FS_OFFSET = local_c;
  return puVar1;
}

