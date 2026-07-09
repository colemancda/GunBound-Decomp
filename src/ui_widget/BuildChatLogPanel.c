/* BuildChatLogPanel - 0x00509260 in the original binary.
 *
 * Builds the chat-log panel (a 0x1050-byte object embedding a ~4 KB history buffer, plus a text-entry). See docs/widgets.md panel catalog. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void BuildChatLogPanel(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  char *pcVar7;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053795b;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  puVar2 = operator_new(0x1050);
  local_4 = 0;
  if (puVar2 == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)0x0;
  }
  else {
    FUN_00505760(puVar2);
    *puVar2 = &PTR_LAB_00557b94;
    puVar5 = puVar2 + 0x2a;
    for (iVar6 = 1000; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    puVar2[0x412] = 0;
    puVar2[0x413] = 0;
  }
  local_4 = 0xffffffff;
  pcVar7 = (char *)(param_2 + 0x21);
  puVar2[9] = 0x4e21;
  puVar2[0x13] = 0;
  puVar2[0x11] = 0x2c6;
  puVar2[0x12] = 0;
  puVar2[10] = 0x21d;
  puVar2[0xb] = 0x110;
  puVar2[0xc] = 0xfe;
  puVar2[0xd] = 0x123;
  pcVar3 = pcVar7;
  do {
    cVar1 = *pcVar3;
    pcVar3[(int)puVar2 + (0x90 - (int)pcVar7)] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  uVar4 = CreateLabelWidget(0,0x2c7,0xdf,7,0x16,0x14);
  Widget_AddChild(uVar4);
  puVar5 = (undefined4 *)CreateTextEntryWidget(0,0x13,0x109,0xd3,0xc,0x50);
  Widget_AddChild(puVar5);
  PanelManager_ClearAllFocus(param_1);
  if (g_currentGameState != 0xb) {
    (**(code **)*puVar5)(1);
  }
  uVar4 = FUN_00507ff0(0x57,0xb,0x91,0xc,pcVar7,0xffff);
  Widget_AddChild(uVar4);
  uVar4 = CreateScrollListWidget(param_1,0xe3,0x44,0x12,0x9d,0xe);
  Widget_AddChild(uVar4);
  PanelManager_Register(puVar2);
  *unaff_FS_OFFSET = uStack_c;
  return;
}

