/* FUN_00508b90 - 0x00508b90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00508b90(void)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int unaff_EDI;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar6;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053795b;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  puVar2 = *(undefined4 **)(unaff_EDI + 4);
  do {
    if (puVar2 == (undefined4 *)0x0) {
      puVar2 = operator_new(0xa8);
      local_4 = 0;
      if (puVar2 == (undefined4 *)0x0) {
        puVar5 = (undefined4 *)0x0;
      }
      else {
        Panel_BaseConstructor(puVar2);
        *puVar2 = &PTR_LAB_00557e68;
        puVar5 = puVar2;
      }
      local_4 = 0xffffffff;
      puVar5[9] = 10000;
      puVar5[0x13] = 0;
      puVar5[0x11] = 0x2c6;
      puVar5[0x12] = 1;
      puVar5[10] = 0x119;
      puVar5[0xb] = 0xce;
      puVar5[0xc] = 0xf1;
      puVar5[0xd] = 0x94;
      puVar3 = (undefined4 *)CreateTextEntryWidget(0,0x32,0x58,0x8c,0xc,0xc);
      Widget_AddChild(puVar3);
      PanelManager_ClearAllFocus(unaff_EDI);
      (**(code **)*puVar3)(1);
      uVar4 = CreateLabelWidget(0,0x2c8,0x42,0x6b,0x4a,0x1a);
      Widget_AddChild(uVar4);
      uVar4 = CreateLabelWidget(1,0x2c9,0x97,0x6b,0x4a,0x1a);
      Widget_AddChild(uVar4);
      uVar6 = 0xffff;
      uVar4 = GetLocalizedString(&DAT_00796eec,4000);
      uVar4 = FUN_00507ff0(0x15,0x2d,200,0x1e,uVar4,uVar6);
      Widget_AddChild(uVar4);
      PanelManager_Register(puVar5);
      *unaff_FS_OFFSET = puVar2;
      return;
    }
    piVar1 = puVar2 + 2;
    puVar2 = (undefined4 *)*puVar2;
  } while ((*(int *)(*piVar1 + 0x20) != 0) || (*(int *)(*piVar1 + 0x24) != 10000));
  PanelManager_BringToFront();
  *unaff_FS_OFFSET = local_c;
  return;
}

