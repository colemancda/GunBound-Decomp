/* FUN_005095d0 - 0x005095d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_005095d0(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  char *pcVar4;
  undefined4 uVar5;
  char *pcVar6;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar7;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053be8b;
  *unaff_FS_OFFSET = &local_c;
  puVar3 = *(undefined4 **)(param_1 + 4);
  do {
    if (puVar3 == (undefined4 *)0x0) goto LAB_0050961f;
    iVar2 = puVar3[2];
    puVar3 = (undefined4 *)*puVar3;
  } while ((*(int *)(iVar2 + 0x20) != 0) || (*(int *)(iVar2 + 0x24) != 40000));
  *(undefined1 *)(iVar2 + 0x1d) = 1;
LAB_0050961f:
  puVar3 = operator_new(0x110);
  local_4 = 0;
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    Panel_BaseConstructor(puVar3);
    *puVar3 = &PTR_LAB_00557c5c;
    *(undefined1 *)(puVar3 + 0xe) = 1;
  }
  uVar5 = g_clientContext;
  local_4 = 0xffffffff;
  puVar3[9] = 40000;
  puVar3[0x13] = 0;
  puVar3[0x11] = 10000;
  puVar3[0x12] = 10;
  puVar3[10] = 0x156;
  puVar3[0xb] = 0x17d;
  puVar3[0xc] = 0xab;
  puVar3[0xd] = 0x8b;
  pcVar4 = (char *)FUN_0041eb10(uVar5,param_2);
  pcVar6 = (char *)(puVar3 + 0x24);
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    *pcVar6 = cVar1;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  uVar7 = 0xffff;
  uVar5 = FUN_0041eb80(g_clientContext,param_2);
  uVar5 = CreateStaticTextWidget(0x17,0x22,0x8c,0x4c,uVar5,uVar7);
  Widget_AddChild(uVar5);
  PanelManager_Register(puVar3);
  *unaff_FS_OFFSET = local_c;
  return;
}

