/* ReadyRoomChatPanel_OnCommand - 0x0050d160 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-30), CERTAIN: CReadyRoomChatPanel's OnCommand
 * override. The original's vtable 0x557ee0 holds this at slot 7
 * (+0x1c); that vtable is installed only by BuildReadyRoomChatPanel
 * (0x509537) and src/cxx/Widget.h records it as CReadyRoomChatPanel's
 * (its slot 9 is the already-named RenderReadyRoomChatRow). Widget.h
 * declares slot 7 as CWidget::OnCommand(evt, id, arg); the body ends in
 * the base slot-7 body Widget_OnCommandDefault (0x50eb10). Its one
 * action, evt 0x2000 id 0 (the scrollbar's position report, the panel's
 * only child per docs/widgets.md), stores the position at ctx+0x3b97c -
 * the same cell LobbyChatPanel_OnCommand writes for its own scrollbar.
 *
 * FIXED (2026-10-30), from the disassembly of 0x50d160-0x50d1f7:
 *  1. MISSING `this`. The port was a plain cdecl (evt, id, arg). The
 *     original saves ECX (`mov esi,ecx` at 0x50d17c), hands it back as
 *     ECX to Widget_OnCommandDefault (`mov ecx,esi` at 0x50d1be), and
 *     returns with `ret 0xc` - __thiscall with three stack words, the
 *     signature every sibling slot-7 port already has. `this` is now
 *     the leading param_1 and the old params shift up by one.
 *  2. SEH-PROLOGUE ARTIFACT. `push -1 / push 0x537938 / mov eax,fs:[0]
 *     ... mov fs:[0],esp` is the standard MSVC exception frame; the port
 *     wrote through Ghidra's uninitialised unaff_FS_OFFSET. Stripped,
 *     as in WidgetChildArray_Destroy.c and LobbyChatPanel_OnCommand.c.
 *
 * FIXED (2026-10-30): the Widget_OnCommandDefault call now passes `this`
 * (ECX = esi = this at 0x50d1c0).
 *
 * Noted, not fixed: the CAtlStringMgr calls
 * keep Ghidra's argument lists - the allocator at 0x50d184 takes
 * ECX = &DAT_005b1444, and the release at 0x50d1e6 takes ECX = the
 * manager read from the string header and one pushed word, the header.
 *
 * WIRED (2026-10-30): src/cxx/Panel.cpp's CReadyRoomChatPanel::OnCommand now forwards here
 * (vtable 0x557ee0 slot 7).
 */
#include "ghidra_types.h"


void __thiscall ReadyRoomChatPanel_OnCommand(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped (0x50d160-0x50d16e
   * and the fs:[0] restore at 0x50d1e9) - see the header. */
  puVar3 = (undefined4 *)(**(code **)(DAT_005b1444 + 0xc))();
  puVar4 = puVar3 + 4;
  uStack_4 = 0;
  if ((param_2 == 0x2000) && (param_3 == 0)) {
    *(undefined4 *)(g_clientContext + 0x3b97c) = param_4;
  }
  Widget_OnCommandDefault(param_1,param_2,param_3,param_4);
  uStack_4 = 0xffffffff;
  piVar1 = puVar3 + 3;
  LOCK();
  iVar2 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar2 == 1 || iVar2 + -1 < 0) {
    (**(code **)(*(int *)*puVar3 + 4))(puVar3,puVar4);
  }
  return;
}
