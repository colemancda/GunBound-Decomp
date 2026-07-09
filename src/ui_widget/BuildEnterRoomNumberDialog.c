/* BuildEnterRoomNumberDialog - 0x005087b0 in the original binary.
 *
 * Builds the lobby 'enter room by number' dialog (labels + a numeric text field + OK/Cancel). See docs/widgets.md and docs/screens/03_game_room_list.md. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall BuildEnterRoomNumberDialog(undefined4 param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int unaff_EDI;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053795b) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  puVar2 = *(undefined4 **)(unaff_EDI + 4);
  do {
    if (puVar2 == (undefined4 *)0x0) {
      puVar2 = operator_new(0x90);
      local_4 = 0;
      if (puVar2 == (undefined4 *)0x0) {
        puVar5 = (undefined4 *)0x0;
      }
      else {
        puVar3 = puVar2;
        FUN_00505760(puVar2);
        *puVar2 = &PTR_LAB_00557df0;
        puVar5 = puVar2;
        puVar2 = puVar3;
      }
      local_4 = 0xffffffff;
      puVar5[9] = 1;
      puVar5[0x13] = 0;
      puVar5[0x11] = 0x2715;
      puVar5[0x12] = 0;
      puVar5[10] = 0xf3;
      puVar5[0xb] = 0xca;
      puVar5[0xc] = 0x13a;
      puVar5[0xd] = 0xa0;
      puVar3 = (undefined4 *)CreateTextEntryWidget(0,99,0x32,0xb4,0xc,4);
      Widget_AddChild(puVar3);
      FUN_0050efa0(unaff_EDI);
      (**(code **)*puVar3)(1);
      uVar4 = CreateTextEntryWidget(1,99,0x54,0xb4,0xc,4);
      Widget_AddChild(uVar4);
      uVar4 = CreateLabelWidget(0,0x579,0xd5,0x76,0x52,0x22);
      Widget_AddChild(uVar4);
      uVar4 = CreateLabelWidget(1,0x578,0x80,0x76,0x52,0x22);
      Widget_AddChild(uVar4);
      FUN_0050eea0(puVar5);
      return;
    }
    piVar1 = puVar2 + 2;
    puVar2 = (undefined4 *)*puVar2;
  } while ((*(int *)(*piVar1 + 0x20) != 0) || (*(int *)(*piVar1 + 0x24) != 1));
  FUN_00509960(param_1);
  return;
}

