/* CChatLogPanel_SubmitWhisper - 0x00505ad0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-02), LIKELY. `param_1` is a CChatLogPanel* (src/cxx/
 * Widget.h, same class/offsets as the sibling AppendChatLogPanelLine,
 * which this function also calls with its own `param_1` as `this`).
 * CChatLogPanel's own header already documents `m_partnerName` at +0x90
 * as "copied from the partner record" - i.e. this panel is a 1:1 whisper
 * panel bound to a single partner, not the general broadcast chat log.
 *
 * This reads the pending input line out of the panel's currently-active
 * child row (via Widget_FindChildIndex + the row's +0x38 text field),
 * stashes it in the panel's own ATL CString slot (`+0x50`,
 * `char *m_strings[16]` in CPanel), and if non-empty runs it through
 * CheckChatWordFilter: a filter hit appends a localized "message
 * blocked" notice (string table id 0x202) into the panel's own history
 * via AppendChatLogPanelLine with an empty sender prefix; otherwise (and
 * after one more gate, FUN_00415230) it forwards `(partner=+0x90,
 * text=+0x50)` to FUN_00402720, which resolves the partner by nickname
 * (FindUserIdByNickname) and sends the message as a direct-link, in-room
 * relay, or server-mediated whisper - a private send, not a channel
 * broadcast. Either way it then clears the input row's text buffer and
 * the shared text-entry control. Its sole callers (FUN_005057f0, this
 * panel's OnCommand) invoke it on the "Enter pressed" (evt 0, id 3) and
 * evt 0x1000 command codes - the same OnCommand-triggered shape as the
 * already-named CreateRoomDialog_SubmitCreateRoom /
 * EnterRoomNumberDialog_SubmitRoomNumber, hence the same `_Submit<Noun>`
 * naming. LIKELY rather than CERTAIN: FUN_00415230's own gate and the
 * exact wire shape of FUN_00402720's send are not independently
 * confirmed here.
 */
#include "ghidra_types.h"


void CChatLogPanel_SubmitWhisper(int param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  
  uVar2 = Widget_FindChildIndex();
  if (uVar2 != 0xffffffff) {
    if (*(uint *)(param_1 + 0x10) <= uVar2) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    pcVar5 = (char *)(*(int *)(*(int *)(param_1 + 0xc) + uVar2 * 4) + 0x38);
    pcVar3 = pcVar5;
    if (pcVar5 != (char *)0x0) {
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
    }
    AssignStringBuffer(param_1 + 0x50,pcVar5);
  }
  if (*(int *)(*(int *)(param_1 + 0x50) + -0xc) != 0) {
    cVar1 = CheckChatWordFilter(*(int *)(param_1 + 0x50));
    if (cVar1 == '\x01') {
      pcVar5 = (char *)GetLocalizedString(&g_localizedStringTable,0x202);
      pcVar3 = pcVar5 + 1;
      do {
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
      iVar4 = (int)pcVar5 - (int)pcVar3;
      uVar8 = 0x202;
    }
    else {
      cVar1 = FUN_00415230();
      if (cVar1 == '\0') {
        FUN_00402720(&DAT_00e53e88,param_1 + 0x90,*(undefined4 *)(param_1 + 0x50));
        goto LAB_00505bbe;
      }
      pcVar5 = (char *)GetLocalizedString(&g_localizedStringTable,0x205);
      pcVar3 = pcVar5 + 1;
      do {
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
      iVar4 = (int)pcVar5 - (int)pcVar3;
      uVar8 = 0x205;
    }
    uVar8 = GetLocalizedString(&g_localizedStringTable,uVar8);
    /* DROPPED-ARGUMENT FIX (2026-09-21): FUN_00505900 is __fastcall with
     * 2 register args (ECX,EDX) ahead of these 2 stack args, which is
     * all this call ever passed. Orig 0x505b71/0x505b6c: `mov ecx,ebp`
     * where ebp = this function's own param_1 (set at entry, 0x505ad2);
     * `mov edx,0x551cb1` - the literal address of the pre-existing
     * empty-string global &DAT_00551cb1 (see src/globals.c and its
     * other callers), i.e. an empty sender-name prefix for this
     * system-style message. */
    AppendChatLogPanelLine(param_1,&DAT_00551cb1,uVar8,iVar4);
  }
LAB_00505bbe:
  if (uVar2 < *(uint *)(param_1 + 0x10)) {
    iVar4 = *(int *)(*(int *)(param_1 + 0xc) + uVar2 * 4);
    if (*(char *)(iVar4 + 4) != '\0') {
      SetWindowTextA(*(HWND *)(g_sharedTextInputControl + 4),&DAT_00551cb1);
    }
    puVar7 = (undefined4 *)(iVar4 + 0x38);
    for (iVar6 = 0x40; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = 0;
      puVar7 = puVar7 + 1;
    }
    *(undefined4 *)(iVar4 + 0x13c) = 0;
    return;
  }
                    /* WARNING: Subroutine does not return */
  ThrowCxxException(0x80070057);
}

