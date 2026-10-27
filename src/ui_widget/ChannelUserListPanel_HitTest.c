/* ChannelUserListPanel_HitTest - 0x00507310 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-27), HIGH, CORRECTED FROM THE PROPOSED "OnMouseUp".
 * docs/vtable_census.txt places this at vtable 0x557cac slot 4, with
 * slot 9 the already-named RenderChannelUserRow on the same table -
 * src/cxx/Widget.h/.cpp identify that vtable as CChannelUserListPanel's
 * (builder 0x509d80) and confirm RenderChannelUserRow is its slot-9
 * Update override. Slot 4, not slot 3, is where this class's sibling
 * CLobbyChatPanel (vtable 0x557cd4, differing from this one only at
 * slots 4/7/9) still carries the UNMODIFIED base Widget_HitTest
 * (0x50e9c0) - and Widget.h's own comment on that virtual spells slot
 * 4 out explicitly as "Widget_HitTest - rect test then child
 * broadcast". Slot 3 (Widget_OnMouseUp) is untouched in
 * BOTH vtables, so this overrides HitTest, not OnMouseUp. The body's
 * tail is the clincher: after the row-click side effect below, it runs
 * the exact own-rect test Widget_HitTestSelf documents as "the
 * widget's own-rect half of Widget_HitTest" - same m_hidden (+0x1e)
 * gate, same +0x28/+0x30 and +0x2c/+0x34 strict-inequality bounds,
 * same bool result - and returns it unconditionally, matching
 * CWidget::HitTest's contract exactly.
 *
 * Ahead of that rect test, when (param_2,param_3) lands in one of the
 * panel's 7 user rows (columns param_1+0x28+9..+0xa5, rows starting at
 * param_1+0x2c+0x25 and stepping 0x1e), and the row's name differs from
 * the local player's own nickname, it opens that user's whisper panel
 * via EnsureChatLogPanelForPeer - the same per-row click action
 * RenderChannelUserRow draws the row for. So this HitTest override
 * does double duty: triggering the row's whisper-open click as a side
 * effect of being queried, then still returning the generic
 * contains-point test every CWidget::HitTest caller expects.
 */
#include "ghidra_types.h"


undefined4 __thiscall ChannelUserListPanel_HitTest(int param_1,int param_2,int param_3)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = *(int *)(param_1 + 0x2c) + 0x25;
  if ((*(int *)(param_1 + 0x28) + 9 < param_2) && (param_2 < *(int *)(param_1 + 0x28) + 0xa5)) {
    iVar5 = 0;
    do {
      if ((iVar4 < param_3) && (param_3 < iVar4 + 0x19)) {
        iVar4 = *(int *)(g_clientContext + 0x44248 +
                        (*(int *)(&DAT_005f2f3c + g_clientContext) + iVar5) * 4);
        puVar2 = DAT_00e53c44;
        if (iVar4 != -1) goto joined_r0x00507384;
        break;
      }
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0x1e;
    } while (iVar5 < 7);
  }
  goto LAB_00507427;
  while( true ) {
    piVar1 = puVar2 + 2;
    puVar2 = (undefined4 *)*puVar2;
    if ((*(int *)(*piVar1 + 0x20) == 0) && (*(int *)(*piVar1 + 0x24) == 10000)) break;
joined_r0x00507384:
    if (puVar2 == (undefined4 *)0x0) {
      iVar4 = __stricmp((char *)(iVar4 * 0xd + 0x41445 + g_clientContext),
                        (char *)(g_clientContext + 0x23330));
      if (iVar4 != 0) {
        EnsureChatLogPanelForPeer(&DAT_00e53e88,
                     *(int *)(g_clientContext + 0x44248 +
                             (*(int *)(&DAT_005f2f3c + g_clientContext) + iVar5) * 4) * 0xd + 0x41445 +
                     g_clientContext);
      }
      goto LAB_00507427;
    }
  }
  iVar4 = Widget_FindChildIndex();
  if (iVar4 != -1) {
    /* DROPPED-REG FIX 2026-08-28: FUN_005056c0's EBX is the widget this
       function's list walk just found - `mov ebx,[ecx+8]` at 0x507388,
       which is *piVar1 here, and the same value the Widget_FindChildIndex
       above receives in ECX (`mov ecx,ebx` at 0x5073f1). */
    FUN_005056c0((char *)(*(int *)(g_clientContext + 0x44248 +
                         (*(int *)(&DAT_005f2f3c + g_clientContext) + iVar5) * 4) * 0xd + 0x41445 +
                 g_clientContext),*piVar1);
  }
LAB_00507427:
  uVar3 = 0;
  if ((((*(char *)(param_1 + 0x1e) == '\0') && (*(int *)(param_1 + 0x28) < param_2)) &&
      (param_2 < *(int *)(param_1 + 0x30) + *(int *)(param_1 + 0x28))) &&
     ((*(int *)(param_1 + 0x2c) < param_3 &&
      (param_3 < *(int *)(param_1 + 0x34) + *(int *)(param_1 + 0x2c))))) {
    uVar3 = 1;
  }
  return uVar3;
}

