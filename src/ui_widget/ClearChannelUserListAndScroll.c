/* ClearChannelUserListAndScroll - 0x0041c230 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): it clears the same channel roster as
 * ClearChannelUserList (0x41c1e0) - occupied flags ctx+0x41345, 13-byte
 * names +0x41445, 9-byte names +0x43548, icon word tables +0x43e48 and
 * +0x44048, count byte +0x41344 (see that file for the readers) - and in
 * addition stores 0 to ctx+0x5f2f3c.  That dword is the user-list panel's
 * scroll position: ChannelUserListPanel_OnCommand writes the new position
 * there, and RenderChannelUserRow and ChannelUserListPanel_HitTest add it
 * to the row number (`(*(ctx+0x5f2f3c) + row) * 4` into the +0x44248 index
 * table).  Sole caller WriteReplayEventRecord (0x410dda, packet 0x2001 arm)
 * calls it immediately before ClearChatLog.
 *
 * Calling convention as ClearChatLog: phantom ECX, context in EDX
 * (`mov edx,edi` at 0x410dce, edi = g_clientContext); the call site used
 * to pass nothing and now passes (0, g_clientContext).
 */
#include "ghidra_types.h"


void __fastcall ClearChannelUserListAndScroll(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(param_2 + 0x41345);
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_2 + 0x41445);
  for (iVar1 = 0x340; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_2 + 0x43548);
  for (iVar1 = 0x240; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_2 + 0x43e48);
  for (iVar1 = 0x80; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_2 + 0x44048);
  for (iVar1 = 0x80; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)(param_2 + 0x41344) = 0;
  *(undefined4 *)(&DAT_005f2f3c + param_2) = 0;
  return;
}

