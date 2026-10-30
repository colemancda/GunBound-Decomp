/* ChatLogPanel_Update - 0x00505890 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-30), CERTAIN: CChatLogPanel's slot-9 Update override.
 * The original's vtable 0x557b94 (installed only by BuildChatLogPanel,
 * 0x5092ac; CChatLogPanel's per src/cxx/Widget.h) holds this at slot 9
 * (+0x24), the slot Widget.h declares as CWidget::Update. It has the
 * shape of the other slot-9 panel overrides - CBuddyPanel::Update
 * (0x505df0) and CLobbyChatPanel::Update (0x5078f0): the m_hidden
 * (+0x1e) gate, Widget_DrawSelf for the frame,
 * then the panel's rows. The rows are the 0x28-byte lines of the
 * history buffer Widget.h places at +0xa8, offset by +0x1048 - the
 * value ChatLogPanel_OnCommand stores from the scrollbar's evt-0x2000
 * position report.
 *
 * WIRED (2026-10-30): src/cxx/Panel.cpp's CChatLogPanel::Update now forwards here
 * (vtable 0x557b94 slot 9).
 *
 * FIXED (2026-10-30): the row index's scroll clamp was inverted (it
 * used the +0x1048 offset only when negative); see the site comment.
 */
#include "ghidra_types.h"


void __fastcall ChatLogPanel_Update(int param_1)

{
  int iVar1;
  int iVar2;

  if (*(char *)(param_1 + 0x1e) == '\0') {
    Widget_DrawSelf(param_1);
    iVar1 = 0x2a;
    iVar2 = 0;
    do {
      int iVar3;
      int index;
      iVar3 = *(int *)(param_1 + 0x1048);
      /* BlitRLESprite's dropped args recovered via objdump at 0x5058b0-
       * 0x5058dd (this function is at 0x00505890): ECX at the call is
       * `*(int*)(param_1+0x28) + 0x11` (the widget's own x field, +0x28,
       * per Widget_DrawSelf.c's identical field use, plus a fixed 0x11
       * offset) - constant across loop iterations, unlike RenderRoomLabel's
       * advancing cursor. EAX (rleData) is a pointer into a 40(0x28)-byte-
       * stride array based at param_1+0xa8, indexed by
       * (iVar3<0 ? iVar3 : 0) + iVar2 (iVar2 being this loop's running
       * iteration count, iVar3 read from param_1+0x1048 - a widget field
       * also touched by sibling FUN_00505900.c as a scroll/index bias). */
      /* CORRECTED (2026-10-30): the select above is inverted. 0x5058b0-
       * 0x5058ca is `test eax,eax / setl cl / dec ecx / and eax,ecx` -
       * ECX = 0 when the offset is negative, -1 otherwise - so a negative
       * +0x1048 clamps to 0 and a non-negative one is used as-is. */
      index = (iVar3 < 0 ? 0 : iVar3) + iVar2;
      BlitRLESprite(*(int *)(param_1 + 0x28) + 0x11,*(int *)(param_1 + 0x2c) + iVar1,0xffff,
                    (byte *)(param_1 + 0xa8 + index * 0x28));
      iVar1 = iVar1 + 0xe;
      iVar2 = iVar2 + 1;
    } while (iVar1 < 0xfc);
  }
  return;
}

