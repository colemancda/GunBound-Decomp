/* TextEntry_FetchSelectionAndPlaceImeCaret - 0x0040c8f0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
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
 *
 * The shared overlay EDIT control's caret query: it hands the caller the
 * current selection range and, in the same breath, tells the IME where on
 * screen that caret is.
 *
 * regEdi is the control block FUN_0040c670 fills in - InitGame is what
 * allocates it, operator_new(0x10) at 0x40f36e feeding the call at
 * 0x40f385 - with +0x04 the child EDIT HWND and +0x08 the "ready" byte,
 * the same layout FetchActiveTextInputText, CommitActiveTextInput and
 * SyncActiveTextInput read. All four binary sites load it from
 * g_sharedTextInputControl (mov edi,[0x7934e4]).
 *
 * Message 0xb0 is EM_GETSEL, and the push order at 0x40c900-0x40c907 puts
 * regEsi in wParam (lpdwStart) and regEax in lParam (lpdwEnd), so regEsi
 * comes back as the selection start and regEax as the end. That pairing
 * is confirmed independently of any register recovery by an inlined twin
 * of this entire routine at 0x44297a-0x4429e8 inside
 * State10_Loading_Render, where the same helper was emitted with its
 * arguments folded to constants: the wParam local is the one the code
 * reads back for the multiply, and the composition point comes out as
 * (start * 6 + 0xca, 0x21b). This is the read half of
 * TextEntry_SetSelection at 0x40c8d0, which sends EM_SETSEL (0xb1)
 * through the same SendMessageA slot at 0x544258.
 *
 * The IME half is what earns the second verb. local_1c is a
 * tagCOMPOSITIONFORM with dwStyle 2 = CFS_POINT and ptCurrentPos =
 * (param_1 + (selStart - param_3) * 6, param_2), handed to
 * ImmSetCompositionWindow on that same HWND's HIMC (0x52020a and
 * 0x52021c are the ImmGetContext/ImmSetCompositionWindow thunks). At
 * three of the four sites param_1/param_2 are exactly where the caller
 * draws that field's text - State11_InBattle_RenderPlayerRoster passes
 * (0xca,0x21b) and blits at BlitRLESprite(0xca,0x21b,...), FUN_005071a0
 * passes its widget's +0x28/+0x2c and blits at (+0x28 - scroll, +0x2c) -
 * and 6 is the same fixed glyph advance each caller uses for its own
 * caret rectangle (State11: FUN_004eb7a0(start * 6 + 0xca,
 * (end - start) * 6 + 2, 0xc); FUN_005071a0: start * 6 - scroll + x).
 * The point given to the IMM API is therefore the character cell the
 * caller is about to paint the caret in, which is what puts an inline
 * composition string over the game's chat line instead of at the
 * invisible 800x24 child control's origin. FUN_0040c6f0, that control's
 * WNDPROC, is the other half of the same story: it reads the composition
 * string with ImmGetCompositionStringA and publishes DAT_007934c4, the
 * "composing" gate the key handlers test.
 *
 * Both outputs are consumed at every site: the selection drives each
 * caller's caret/highlight rectangle, and the two text-widget callers
 * additionally clamp their horizontal scroll from it.
 *
 * TWO ORIGINAL QUIRKS, ported faithfully. First, param_3 is subtracted
 * BEFORE the *6, i.e. used as a character index, while the two
 * text-widget callers pass a scroll offset held in PIXELS (FUN_005071a0's
 * +0x13c and the uncarved 0x40ca20's +0x454 are both assigned selStart*6
 * within a few instructions of the call); it cancels at the two
 * state-machine sites, which pass 0. Second,
 * State09_ReadyRoom_RenderStatusOverlay passes State11's (0xca,0x21b)
 * while drawing its own chat line and caret box at (0x51,0x16f) (orig
 * 0x4da395-0x4da3e2), so at that one site the composition window is
 * parked nowhere near the text it belongs to.
 *
 * The fourth binary site, 0x40cab2, sits in an uncarved function at
 * 0x40ca20 - an address gap in PROGRESS.csv between
 * DeletePoisonedBaseObject and FUN_0040cc50 - that is a third text-field
 * draw of the same shape as FUN_005071a0: SetClipRect first, string at
 * +0x48, scroll at +0x454. count_call_args.py reports 3 sites where
 * callsite_regs.py reports 4.
 *
 * Register provenance (2026-08-25/27, unchanged by this rename): EDI is
 * uniform across all four sites, so no site pairing was needed; EAX and
 * ESI are lea'd addresses of two int locals (a lea at all three ported
 * sites, never a load), each anchored to its caller's frame by that
 * caller's own GetWindowTextA buffer. They are adjacent at only two of
 * them - frame+0x14/+0x18 in State09_ReadyRoom_RenderStatusOverlay and
 * frame+0xc/+0x10 in FUN_005071a0. The State11 pair is frame+0x18 and
 * frame+0x24 (Ghidra's local_1024 and local_1018), 0xc apart. The
 * callee never writes -1 through either pointer - it writes EM_GETSEL's
 * values, or 0 on failure and when the control is not ready - so each
 * caller's "== -1 then use strlen" fallback is defensive only.
 */
#include "ghidra_types.h"


void TextEntry_FetchSelectionAndPlaceImeCaret(int param_1,LONG param_2,int param_3,int regEdi,undefined4 *regEax,
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

