/* ChannelUserListPanel_OnCommand - 0x00507460 in the original binary.
 *
 * CChannelUserListPanel's OnCommand (vtable 0x557cac slot 7, +0x1c).
 * Carved 2026-10-30 from the disassembly (50 bytes, 0x507460-0x507491):
 *
 *   mov eax,[esp+4]  ; evt
 *   cmp eax,0x2000
 *   mov edx,[esp+0xc] ; arg
 *   push esi / mov esi,[esp+0xc] ; id
 *   jne 0x507486 / test esi,esi / jne 0x507486
 *   push edi / mov edi,[0x5b3484] / mov [edi+0x5f2f3c],edx / pop edi
 *   push edx / push esi / push eax / call 0x50eb10 ; ECX still this
 *   pop esi / ret 0xc
 *
 * A scroll change (evt 0x2000) from child 0, the list's scrollbar, stores
 * the new position at g_clientContext + 0x5f2f3c. Every event then falls
 * through to the base Widget_OnCommandDefault. __thiscall in the
 * original, erased to cdecl here (`this` first). Wired as
 * CChannelUserListPanel::OnCommand in src/cxx/Panel.cpp.
 *
 * NAMED 2026-10-31, CERTAIN (was FUN_00507460). The evidence is the
 * vtable, not the body: the word at 0x557cac+0x1c is 0x507460, and
 * 0x557cac is stored only by BuildChannelUserListPanel (0x509dc2), the
 * builder of the CChannelUserListPanel (src/cxx/Widget.h). Slot 4 of
 * that same vtable is the already-named ChannelUserListPanel_HitTest,
 * and slot 7 is the CWidget::OnCommand(evt, id, arg) slot that the
 * sibling AvatarStorePanel_OnCommand / BuddyPanel_OnCommand occupy in
 * their own vtables.
 */
#include "ghidra_types.h"


void __thiscall ChannelUserListPanel_OnCommand(int param_1,int param_2,int param_3,int param_4)

{
  if ((param_2 == 0x2000) && (param_3 == 0)) {
    *(int *)(g_clientContext + 0x5f2f3c) = param_4;
  }
  Widget_OnCommandDefault(param_1,param_2,param_3,param_4);
  return;
}
