/* AcquireSoundChannel - 0x004ee9b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-EDI FIX (2026-07-30): `unaff_EDI` is a real 1st argument - a
 * `.xes` sound-effect filename string, walked char-by-char to find its
 * length - dropped by Ghidra at ALL ~150 call sites across the tree (a
 * systemic gap, not specific to this file; the K&R-empty decl in
 * functions.h reflects that). Confirmed via objdump at the one call site
 * actually reachable in current live testing (HandleActiveObjectMouseMove.c,
 * orig 0x406267-0x406273): `mov eax,[esi+0x48]` (esi=the hovered
 * CButtonWidget, +0x48=m_unk48), `mov edi,[eax*8+0x56d0f8]` (a 2-entry
 * {selectSound,pushSound} table - see globals.c's g_buttonSoundNameTable), then
 * `push 0x0; call 0x4ee9b0` - i.e. `(soundName, flag)`. Every
 * State03_GameRoomList button passes CreateButtonWidget's arg11=0, so
 * m_unk48 is always 0 for lobby buttons, and this always resolves to
 * "bselect1.xes". Without a real string, `unaff_EDI` held whatever was
 * left in EDI from much earlier in the call chain (WndProc's own `mov
 * edi,msg` - 0x200/WM_MOUSEMOVE), and the char-walk + subsequent
 * `(**(code**)(**(...)+8))(uVar3)` vtable-style dispatch on that garbage
 * eventually jumped into unrelated stack memory - the AVATAR/BUDDY hover
 * crash chased earlier this session.
 *
 * `flag` (the caller's pushed 2nd arg) IS read, just not by this
 * function's own top-level logic - confirmed via the rest of the same
 * disasm (0x4eea01-0x4eea0d): `mov edx,[esp+0xc]` reloads it from the
 * stack and forwards it, together with `edi`(soundName)/`esi`(channel
 * index), into the found channel object's own vtable slot 2 -
 * `channelObj->vtbl[2](channelIndex, soundName, flag)`. The raw
 * decompile already had this call (`(**(code**)(**(...)+8))(uVar3)`) but
 * silently dropped its other 2 args the same way; `code` is this
 * project's K&R-unspecified-args function type, so adding args to an
 * existing `(code**)`-cast call is syntactically free.
 *
 * Only the one call site on the current live path is fixed here
 * (HandleActiveObjectMouseMove.c); the ~149 others (all battle/mobile
 * code, unreached yet) keep their existing 1-arg calls against the
 * K&R-empty decl - fixing those needs each site's own `soundName` traced,
 * deferred as a separate sweep.
 */
#include "ghidra_types.h"


uint AcquireSoundChannel(char *soundName,int flag)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  char *unaff_EDI = soundName;

  if ((unaff_EDI != (char *)0x0) && (DAT_0079354b != '\0')) {
    pcVar1 = unaff_EDI + 1;
    do {
      cVar2 = *unaff_EDI;
      unaff_EDI = unaff_EDI + 1;
    } while (cVar2 != '\0');
    if (unaff_EDI != pcVar1) {
      uVar3 = 1;
      if (1 < DAT_00793560) {
        do {
          if (*(char *)(*(int *)(DAT_00793554 + uVar3 * 4) + 0x4c) == '\0') break;
          uVar3 = uVar3 + 1;
        } while (uVar3 < DAT_00793560);
      }
      if (uVar3 != DAT_00793560) {
        cVar2 = (**(code **)(**(int **)(DAT_00793554 + uVar3 * 4) + 8))(uVar3,soundName,flag);
        if (cVar2 == '\0') {
          uVar3 = 0xffffffff;
        }
        return uVar3;
      }
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}
