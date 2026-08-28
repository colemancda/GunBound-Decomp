/* FUN_0040c8f0 - 0x0040c8f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EDI RECOVERED (2026-08-25) by uniformity: every call site in the original
 * loads the same value into it (`mov edi,[0x7934e4]`), so no site pairing is
 * needed -- there is nothing to match up, and the answer cannot be corrupted
 * by Ghidra's block reordering.  All 4 binary sites agree; 3 are ported and
 * the fourth, 0x40cab2, sits in a function that has not been carved.
*
 * DROPPED REGISTERS RECOVERED (2026-08-27): in_EAX and unaff_ESI are
 * EM_GETSEL's two OUT parameters -- `SendMessageA(hwnd, 0xb0, (WPARAM)ESI,
 * (LPARAM)EAX)` is EM_GETSEL(lpdwStart, lpdwEnd) -- so ESI receives the
 * selection start and EAX the end, and the callee zeroes both through those
 * pointers when the message fails.  Every site passes the addresses of two
 * adjacent int locals (`lea` at all three, never a load).
 *
 * Each caller holds exactly one site, so nothing rests on ordering, and each
 * caller's frame is anchored twice against its own source:
 *   - State11_InBattle_RenderPlayerRoster: the GetWindowTextA buffer pins
 *     frame+0x34 = local_1008, which fixes frame+0x18 = local_1024 and
 *     frame+0x24 = local_1018 (that file's own header already identifies
 *     [esp+0x18] as local_1024).
 *   - State09_ReadyRoom_RenderStatusOverlay: the same buffer pins frame+0x20
 *     = aCStack_80, giving frame+0x18 = iStack_88 and frame+0x14 = iStack_8c.
 *   - FUN_005071a0: `mov esi,[esp+0xc]` right after the call is that file's
 *     `iVar3 = local_8`, which fixes the pair as local_8 and local_4.
 * In all three the ESI local is the one the source then tests against -1,
 * which is the selection-start check.
 *
 * A fourth binary site at 0x40cab2 has no source counterpart: it lies in an
 * address gap between PROGRESS.csv entries, i.e. in code that is not ported.
 * count_call_args.py reports 3 where callsite_regs.py reports 4.
 */
#include "ghidra_types.h"


void FUN_0040c8f0(int param_1,LONG param_2,int param_3,int regEdi,undefined4 *regEax,
                  int *regEsi)

{
  undefined4 *in_EAX = regEax;
  LRESULT LVar1;
  HIMC pHVar2;
  int *unaff_ESI = regEsi;
  tagCOMPOSITIONFORM *lpCompForm;
  tagCOMPOSITIONFORM local_1c;
  
  if (*(char *)(regEdi + 8) != '\0') {
    LVar1 = SendMessageA(*(HWND *)(regEdi + 4),0xb0,(WPARAM)unaff_ESI,(LPARAM)in_EAX);
    if (LVar1 == -1) {
      *in_EAX = 0;
      *unaff_ESI = 0;
    }
    local_1c.ptCurrentPos.x = param_1 + (*unaff_ESI - param_3) * 6;
    lpCompForm = &local_1c;
    local_1c.dwStyle = 2;
    local_1c.ptCurrentPos.y = param_2;
    pHVar2 = ImmGetContext(*(HWND *)(regEdi + 4));
    ImmSetCompositionWindow(pHVar2,lpCompForm);
    return;
  }
  *in_EAX = 0;
  *unaff_ESI = 0;
  return;
}

