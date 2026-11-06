/* ClearChannelUserList - 0x0041c1e0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): the fields it clears are the channel user
 * roster that the channel user-list panel reads.  RebuildChannelUserIndex
 * scans the 0x100 per-user occupied flags at ctx+0x41345 (cleared here by
 * the first 0x40-dword fill); RenderChannelUserRow draws each row from the
 * 13-byte name slots at ctx+0x41445 (0x340 dwords here = 256 x 13), the
 * 9-byte slots at ctx+0x43548 (0x240 dwords = 256 x 9) and the word icon
 * table at ctx+0x43e48 (0x80 dwords = 256 x 2); the last fill, ctx+0x44048,
 * is a second 256-word table.  ctx+0x41344 (cleared by the byte store) is
 * the byte Panel.cpp feeds to CreateScrollListWidget for the same panel.
 * Sole caller: State02_ServerSelect_OnTopButton (0x4e1421), in the
 * param_2 == 3 branch right after SendOutgoingPacket.
 * Unlike ClearChannelUserListAndScroll (0x41c230) it leaves the panel's
 * scroll position (ctx+0x5f2f3c) alone.
 *
 * Correction to the earlier note: EAX is not a hidden argument here.  The
 * function starts `push edi / xor eax,eax`, so EAX is written before it is
 * read (it is just the zero stored by the rep stosd); the old remark that
 * EAX is read first was wrong.  Only EDX (context) is real; ECX is phantom.
 *
 * DECLARED ARGUMENTS FILLED.  `ret 0` puts nothing on the stack, so param_1
 * (ECX) and param_2 (EDX) are both registers, and the sole call site
 * (0x004e1421) passed neither.  ECX is never set there and never read here,
 * so param_1 is a PHANTOM and takes 0; EDX is loaded from [0x5b3484].
 *
 * param_2 = g_clientContext is corroborated by the body rather than only by
 * the call site: every write here is param_2 + 0x41344 and up, the
 * arena-relative form.  Clearing 0x340 dwords at a fixed context offset only
 * makes sense against the context base.
 */
#include "ghidra_types.h"


void __fastcall ClearChannelUserList(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  *(undefined1 *)(param_2 + 0x41344) = 0;
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
  return;
}

