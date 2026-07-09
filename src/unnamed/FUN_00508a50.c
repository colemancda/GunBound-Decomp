/* FUN_00508a50 - 0x00508a50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00508a50(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053ca9b) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  puVar2 = *(undefined4 **)(param_1 + 4);
  do {
    if (puVar2 == (undefined4 *)0x0) {
      puVar2 = operator_new(0x90);
      local_4 = 0;
      if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
      }
      else {
        Panel_BaseConstructor(puVar2);
        *puVar2 = &PTR_LAB_00557c0c;
        *(undefined1 *)(puVar2 + 0xe) = 1;
      }
      local_4 = 0xffffffff;
      puVar2[9] = 3;
      puVar2[0x13] = 0;
      puVar2[0x11] = 10000;
      puVar2[0x12] = 8;
      puVar2[10] = 0x139;
      puVar2[0xb] = 0xa0;
      puVar2[0xc] = 0xf3;
      puVar2[0xd] = 0xca;
      puVar3 = (undefined4 *)CreateTextEntryWidget(0,0x6a,0x48,0xb6,0xc,0x14);
      Widget_AddChild(puVar3);
      PanelManager_ClearAllFocus(param_1);
      (**(code **)*puVar3)(1);
      TextEntry_SetControlText();
      uVar4 = CreateLabelWidget(0,0x4ba,0xd5,0x76,0x52,0x22);
      Widget_AddChild(uVar4);
      uVar4 = CreateLabelWidget(1,0x4bb,0x80,0x76,0x52,0x22);
      Widget_AddChild(uVar4);
      PanelManager_Register(puVar2);
      break;
    }
    piVar1 = puVar2 + 2;
    puVar2 = (undefined4 *)*puVar2;
  } while ((*(int *)(*piVar1 + 0x20) != 0) || (*(int *)(*piVar1 + 0x24) != 3));
  return;
}

