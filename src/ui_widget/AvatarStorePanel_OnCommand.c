/* AvatarStorePanel_OnCommand - 0x0050a980 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-30), CERTAIN: CAvatarStorePanel's OnCommand override.
 * The original's vtable 0x557eb8 holds this at slot 7 (+0x1c), the
 * slot src/cxx/Widget.h declares as CWidget::OnCommand(evt, id, arg);
 * the vtable is installed only by BuildAvatarStorePanel (0x509ea5),
 * and Widget.h records it as CAvatarStorePanel's. `this` arrives in
 * ECX (`mov esi,ecx` at 0x50a992), both exits are `ret 0xc`, and both
 * end in the base slot-7 body Widget_OnCommandDefault with ECX = this.
 * Evt 0x2000 id 0 is the report from the panel's scrollbar (the id-0
 * CreateScrollListWidget BuildAvatarStorePanel sizes from the catalog
 * count at ctx+0x44e24): the position becomes the page base at
 * state7+0x454 that AvatarStorePanel_HitTest adds to its row index.
 * Evt 0 ids 0, 2 and 3 post input events 0x14, 0x16 and 0x1a.
 *
 * FIXED (2026-10-30): the Widget_OnCommandDefault calls now pass `this`
 * (ECX = esi = this at 0x50a9be and 0x50a9fd).
 *
 * Noted, not fixed: the EnqueueInputEvent
 * call drops its leading queue argument - EAX = 0x795070, the
 * g_inputEventRing base, at 0x50a9ec, with stack words (0, *this,
 * code). That dropped EAX is the open per-site recovery
 * EnqueueInputEvent.c tracks, shared with EnterRoomNumberDialog_OnCommand.
 * Panel.cpp declares no CAvatarStorePanel::OnCommand.
 */
#include "ghidra_types.h"


void __thiscall AvatarStorePanel_OnCommand(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  puVar1 = g_gameStateVTableArray[7];
  if (param_2 == 0) {
    if (param_3 == 0) {
      uVar2 = *param_1;
      uVar3 = 0x14;
    }
    else if (param_3 == 2) {
      uVar2 = *param_1;
      uVar3 = 0x16;
    }
    else {
      if (param_3 != 3) goto LAB_0050a9f8;
      uVar2 = *param_1;
      uVar3 = 0x1a;
    }
    EnqueueInputEvent(0,uVar2,uVar3);
  }
  else if ((param_2 == 0x2000) && (param_3 == 0)) {
    *(undefined4 *)(g_gameStateVTableArray[7] + 0x454) = param_4;
    FUN_0044b0b0(puVar1);
    RefreshConnectionStatusLabel(param_1);
    Widget_OnCommandDefault((int)param_1,0x2000,0,param_4);
    return;
  }
LAB_0050a9f8:
  Widget_OnCommandDefault((int)param_1,param_2,param_3,param_4);
  return;
}

