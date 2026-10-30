/* ChatLogPanel_OnCommand - 0x005057f0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-30), CERTAIN: CChatLogPanel's OnCommand override.
 * The original's vtable 0x557b94 holds this at slot 7 (+0x1c), and
 * 0x557b94 is installed by BuildChatLogPanel alone (`mov [reg],0x557b94`
 * at 0x5092ac), which src/cxx/Widget.h records as CChatLogPanel's
 * vtable. Widget.h's CWidget declares slot 7 as OnCommand(evt, id,
 * arg), "the event spine" children report to; the base slot-7 body is
 * Widget_OnCommandDefault (0x50eb10), which this tail-calls on every
 * path, and `ret 0xc` on every exit is the 3 stack words of that
 * signature with `this` in ECX. Its one already-named callee,
 * CChatLogPanel_SubmitWhisper, is reached from the whisper-input
 * Enter codes (evt 0 id 3, evt 0x1000), and evt 0 id 0 is the close-X
 * label BuildChatLogPanel creates as child id 0 (sets the +0x1d close
 * flag). Same `<Panel>_OnCommand` form as WorldListPanel_OnCommand.
 *
 * FIXED (2026-10-30): every Widget_OnCommandDefault call now passes
 * `this` (ECX = esi = this at 0x505823, 0x505843, 0x505858, 0x50587b).
 *
 * WIRED (2026-10-30): src/cxx/Panel.cpp's CChatLogPanel::OnCommand now
 * forwards here (vtable 0x557b94 slot 7).
 */
#include "ghidra_types.h"


void __thiscall ChatLogPanel_OnCommand(int param_1,uint param_2,int param_3,undefined4 param_4)

{
  if (param_2 < 0x1002) {
    if (param_2 == 0x1001) {
LAB_0050584f:
      *(undefined1 *)(param_1 + 0x1d) = 1;
      Widget_OnCommandDefault(param_1,param_2,param_3,param_4);
      return;
    }
    if (param_2 == 0) {
      if (param_3 == 0) goto LAB_0050584f;
      if (param_3 == 3) {
        CChatLogPanel_SubmitWhisper(param_1);
        Widget_OnCommandDefault(param_1,0,3,param_4);
        return;
      }
    }
    else if (param_2 == 0x1000) {
      CChatLogPanel_SubmitWhisper(param_1);
      Widget_OnCommandDefault(param_1,0x1000,param_3,param_4);
      return;
    }
  }
  else if ((param_2 == 0x2000) && (param_3 == 0)) {
    *(undefined4 *)(param_1 + 0x1048) = param_4;
  }
  Widget_OnCommandDefault(param_1,param_2,param_3,param_4);
  return;
}

