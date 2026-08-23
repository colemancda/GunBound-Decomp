/* BlitSpriteClipped - 0x004eb9c0 in the original binary.
 *
 * Ghidra dropped TWO of this function's real inputs and, as a result,
 * omitted the x/pixel-pointer computation entirely:
 *
 *   - The y coordinate arrived in EAX and was read as `in_EAX` (same
 *     shape as the already-fixed DrawSprite()/BlitSprite16bpp() sibling
 *     calls in this same source file's original neighborhood).
 *   - The x coordinate arrived in ECX and wasn't surfaced as a variable
 *     AT ALL - Ghidra's decompile never referenced it, silently
 *     dropping the frame's horizontal position and the pixel pointer
 *     that depends on it.
 *
 * Confirmed via objdump at the function's own entry (0x4eb9c0):
 *   mov esi,[esp+0x10]   ; esi = param_1 (stack arg: sprite/frame index)
 *   mov edi,eax          ; edi = y (EAX register arg)
 *   mov ebx,ecx          ; ebx = x (ECX register arg)
 *   ...
 *   add edi,[esi+0x2c]   ; iVar2 = y + frame->yBase   (kept by Ghidra)
 *   add ebx,[esi+0x28]   ; x    = x + frame->xBase    (DROPPED by Ghidra)
 *   mov ebp,[esi+0x20]           ; ebp = frame->rowStride
 *   ebp = ebp * skipRows          ; (skipRows = same masked-subtract Ghidra
 *                                    already kept as part of `local_4`)
 *   ebp = [esi+0x34] + ebp * 2   ; starting pixel-row pointer (DROPPED -
 *                                   Ghidra never surfaced this variable)
 * and in the per-row loop at 0x4eba54:
 *   push edi             ; 3rd/stack arg = current row index (iVar2)
 *   mov edx,ebp          ; 2nd arg (EDX) = pixel-row pointer, advanced by
 *                           `ebp += frame->rowStride*2` after each call
 *   mov eax,ebx          ; 4th arg (EAX) = x
 *   call FUN_004eb940
 * FIXED (2026-07-14): the call above is 4 real args, not 3 - `ecx` (the
 * 1st/width slot) holds `frame->rowStride` the whole time (loaded once at
 * 0x4eb9fd, never touched again before the loop), NOT `x`. The earlier
 * recovery here mis-mapped EAX's role onto FUN_004eb940's declared param_1
 * (its real width slot) and never passed x through any parameter at all -
 * see FUN_004eb940.c's own header for the fix on that side. Now passes
 * (iRowStride, puPixelRow, iVar2, x) matching the real 4-arg signature.
 *
 * The call site in RenderPlayerNameplate.c confirms the x/y recovery
 * independently: `BlitSpriteClipped(7)` there sits right next to its
 * BlitSprite16bpp() sibling call `BlitSprite16bpp(iVar2 + 99, iVar5 +
 * 0x20)` for the same frame - i.e. x = iVar2+99, y = iVar5+0x20 - and
 * BlitSprite16bpp(param_1,param_2) already takes (x, y) in that order.
 * That file's two BlitSpriteClipped() call sites were updated to match;
 * `include/functions.h` still declares this function with empty parens
 * (no prototype-enforced arg count), so the many other call sites across
 * src/ that still pass only `frame` keep compiling and behave exactly as
 * before (x/y arrive as whatever was already in ECX/EAX at each of
 * those call sites) - recovering all of them is out of scope for this
 * pass; see DrawSprite.c's header comment for the established precedent
 * of only fixing call sites with an unambiguous recoverable value.
 *
 * FIXED (2026-07-14): the internal FindSpriteFrame() re-lookup was ALSO a
 * zero-arg dropped-register-argument stub, same class as BlitSprite16bpp.c's
 * sibling bug. Confirmed via objdump at 0x4eb9c0: entry does `mov
 * esi,[esp+0x10]` (ESI = this function's own `frame` stack arg, left
 * untouched through the call), then immediately before `call 0x4f30c0` sets
 * `mov eax,0xea0e18` (container = &g_spriteRegistry) with no EDX write in
 * between - EDX (outer key) is inherited live from the caller. An EARLIER
 * fix hardcoded EDX=10000 here, verified only against State06_Logo2_Render's
 * specific call site - WRONG in general, since EDX is a genuine per-caller
 * pass-through, not a constant (live-reproduced: ServerSelect's world-list
 * panel's own outer key is 0x2711, and this hardcoded 10000 silently made
 * its background sprite fail to draw even though the panel's own, separate,
 * correctly-keyed FindSpriteFrame lookup succeeded). Promoted to a real
 * trailing `outerKey` parameter; every currently-3-arg (already frame/x/y-
 * migrated) call site updated to pass its real key - see each site's own
 * recovery. functions.h stays K&R-empty so the ~290 still-2-arg
 * (frame not yet even recovered) call sites keep compiling unchanged.
 *
 * CALLING CONVENTION RECOVERED (2026-08-20).  The original is __cdecl (`ret`,
 * not `ret N`) with ONE stack argument and THREE register ones, and the entry
 * pins every role:
 *     mov esi,[esp+0x10] / test esi,esi / jl <exit>   the stack arg is FRAME
 *                                                     (the `-1 < frame` test)
 *     mov edi,eax        then  add edi,[frame+0x2c]   EAX is Y
 *     mov ebx,ecx        then  add ebx,[frame+0x28]   ECX is X
 *     (edx untouched before)  call FindSpriteFrame    EDX is OUTERKEY
 * matching this port's own (frame, x, y, outerKey) parameter order.
 *
 * Scanning all 217 direct call sites: FRAME is an immediate at 190 and
 * OUTERKEY at 198, but X and Y almost always come from a caller local.
 * Cached in tools/blitspriteclipped_regs.json.
 *
 * WHERE X AND Y ACTUALLY COME FROM.  180 of the 217 sites sit in one shape:
 *     if (FindSpriteFrame(...)) {
 *       if (frame->flags == 1) BlitSprite16bpp(A, B);
 *       else                   BlitSpriteClipped(F);
 *     }
 * Both branches receive the SAME x and y - the if-branch through the stack,
 * where Ghidra modelled them, and the else-branch through ECX/EAX, where it
 * did not.  So the sibling call already carries the expressions this one
 * needs, and no new analysis is required to recover them.
 *
 * TRAP - A BACKWARD SCAN CROSSES BRANCH BOUNDARIES.  Reading back from the
 * else-branch call for "the last instruction that writes EAX" walks straight
 * into the IF-branch and reports `mov eax,esi` (the frame), when the real
 * incoming EAX is whatever the value was at the branch point - the Y computed
 * before the test.  It looks authoritative and it is wrong at 16 of the 19
 * sites in FUN_0050ae40.c alone.  ECX, EDX and the pushed frame ARE reliable,
 * because they are set inside the else-branch itself.  This is the same
 * inherited-across-a-branch-target hazard already recorded for
 * HandleTurnTimeoutSlot.
 *
 * SECOND PASS extended this to every caller by keying on the FRAME LITERAL
 * instead of position: pair the C's BlitSpriteClipped(F) with the
 * disassembled sites whose pushed frame is F, require the counts to agree,
 * and require every candidate with that frame to carry the SAME outerKey - in
 * which case it does not matter which is which, because the values applied
 * are identical. Being keyed on a value rather than an ordinal, it is immune
 * to the block reordering that makes FUN_0044a000.c unsafe for
 * position-matching, and that file contributed 10 sites. 31 more sites across
 * 9 files; running total 65.
 *
 * THIRD PASS adds 5 more on a different sufficiency argument: where EVERY
 * remaining site in a function carries the SAME literal outerKey, the pairing
 * question disappears - it does not matter which C call maps to which binary
 * call, because the value applied is identical either way, and the frame is
 * already correct in the source. That holds for only 3 files (FUN_0041bce0,
 * FUN_00477930, FUN_004e2b20); most callers mix two to four different
 * outerKeys, so for them the pairing has to be settled first.
 *
 * WHERE THIS STANDS, counted properly with tools/count_call_args.py (the
 * running totals in the three commit messages were each measured with a
 * different ad-hoc grep and none of them is right): there are 227 call sites
 * in the tree, of which 121 now pass all four arguments and 106 do not - 90
 * passing one, 14 passing none, 2 passing three. 70 of those 121 were fixed
 * by these three passes; the rest already carried their arguments.
 *
 * FOURTH PASS uses the cheapest rule of the four and needs no disassembly at
 * all: where a block's FindSpriteFrame call has ALREADY been recovered, it
 * hands this one both values directly - the outerKey is the same key, and the
 * frame is the very frame just looked up, because the block looks a frame up
 * and then blits it.  There is no pairing question because the two calls are
 * in the same block.  5 more sites, and at every one the frame the source
 * already passed agreed with the frame in the lookup.  One site was skipped
 * on that check rather than forced: BlitSpriteClipped(cVar6) sitting after a
 * lookup of frame 4, which means the window had spanned into a neighbouring
 * block.  126 of 227 sites now complete.
 *
 * The two functions unlock each other, so the productive move is to alternate
 * the two derivations until neither yields. RUN TO A FIXED POINT (2026-08-20)
 * it converged after one iteration, which is the useful negative result: the
 * mutual unlock is exhausted, and everything still open needs information
 * neither function has - x and y coming from a caller local, or blocks where
 * neither side is known.
 *
 * A last forced-pairing rule closed 2 more: where a function has exactly ONE
 * still-incomplete variable-frame call in the source and exactly ONE
 * disassembled site whose frame was not an immediate, the pairing has no
 * freedom left in it.
 *
 * FINAL STATE for this session: 128 of 227 BlitSpriteClipped sites complete
 * (99 open), and 102 of 192 FindSpriteFrame sites (90 open). Counts from
 * tools/count_call_args.py, which is the only counter in this tree that gets
 * multi-line calls and nested parentheses right.
 *
 * The frame-7 site skipped in the first instalment IS included, on different
 * evidence rather than by relaxing the rule: at 0x50afa4 both branches read x
 * from the SAME stack slot ([esp+0x1c] in the else-branch, the same slot at
 * one-push depth in the if-branch), and `mov edx,0x2713` at 0x50afa8
 * dominates both, so frame, x and outerKey are all pinned without needing a
 * FindSpriteFrame call to compare against.
 *
 * FIRST INSTALMENT: 34 sites in FUN_0050ae40.c and FUN_0050be20.c, 17 each.
 * X and Y lifted from the sibling BlitSprite16bpp; FRAME and OUTERKEY from
 * the disassembly.  Every one is cross-checked: the OUTERKEY recovered here
 * must equal the outerKey of the FindSpriteFrame call in the SAME block,
 * since that is the value this function forwards to it.  All 34 agree.
 *
 * The one site per file that is skipped (frame 7) is skipped for a real
 * reason, not a tooling gap: the compiler INLINED the lookup there - the
 * `while (true) { p = *(p+0x10); k = *(p+8); ... }` walk in the caller is
 * FindSpriteFrame's own inner-list loop - so there is no call to cross-check
 * against, and it was left alone rather than applied unverified.
 *
 * SEPARATE DEFECT FOUND, NOT FIXED HERE: the sibling BlitSprite16bpp call
 * sites are MISALIGNED BY ONE SLOT.  Its real arguments are EAX=frame,
 * stack1=x, stack2=y, EDX=outerKey, but the C calls it as
 * `BlitSprite16bpp(x, y)`, which fills its declared (frame, param_1) - so an
 * X COORDINATE is being passed as the frame index that its own body hands to
 * FindSpriteFrame.  That affects its whole call fan-out and needs its own
 * sweep.
 */
#include "ghidra_types.h"
#include <windows.h>


undefined4 BlitSpriteClipped(int frame,int x,int y,int outerKey)

{
  int iVar1;
  int iVar2;
  int local_4;
  int iRowStride;
  undefined4 *puPixelRow;
  int clipTop;
  int topSkip;

  if (((g_screenSurface != 0) && (-1 < frame)) &&
     (iVar1 = FindSpriteFrame((int)&g_spriteRegistry,outerKey,frame), iVar1 != 0)) {
    iVar2 = y + *(int *)(iVar1 + 0x2c);
    x = x + *(int *)(iVar1 + 0x28);
    iRowStride = *(int *)(iVar1 + 0x20);
    /* FIXED (2026-07-20): `(clipTop - iVar2 < 0) - 1 & clipTop - iVar2` is a
     * branchless "max(0, clipTop-iVar2)" idiom, matching the original's
     * `test eax,eax`/`sets dl`/`dec edx`/`and edx,eax` sign-check sequence -
     * it needs SIGNED subtraction. g_clipMinY is declared uint32_t, so
     * without going through a signed local first, `g_clipMinY - iVar2` is
     * computed as UNSIGNED and wraps instead of going negative (e.g.
     * clipTop=0, iVar2=18 -> wraps to 0xffffffee, not -18), making `< 0`
     * permanently false. That silently inflates local_4 (rows-to-draw) by
     * iVar2's magnitude - e.g. a 22-row frame at y=18 computed local_4=40
     * instead of 22 - so the per-row loop in FUN_004eb940 read 18 rows of
     * heap memory past the sprite's pixel buffer and blitted it to screen,
     * and puPixelRow's own start offset was equally wrong. This was the
     * root cause of the lobby's sprite-sheet garbage: every frame drawn
     * through this (the +0x18==0/"clipped") path was affected, while the
     * +0x18==1 path (BlitSprite16bpp, a plain `if` branch, no masking
     * trick) was unaffected - explaining why sibling buttons at the
     * identical position (e.g. the buddy panel's Del) render clean while
     * others (Add, close-X) render as noise. Verified live: a probe on
     * this exact call for the buddy Add button (frame h=22, y=18,
     * clipTop=0) printed local_4=40 before this fix. */
    clipTop = (int)g_clipMinY;
    topSkip = (clipTop - iVar2 < 0) ? 0 : clipTop - iVar2;
    local_4 = *(int *)(iVar1 + 0x24) - topSkip;
    puPixelRow = (undefined4 *)
                 (*(int *)(iVar1 + 0x34) +
                  iRowStride * topSkip * 2);
    if (iVar2 < clipTop) {
      iVar2 = clipTop;
    }
    if (g_clipMaxY < local_4 + iVar2) {
      local_4 = (g_clipMaxY - iVar2) + 1;
    }
    if (0 < local_4) {
      do {
        FUN_004eb940(iRowStride,puPixelRow,iVar2,x);
        puPixelRow = (undefined4 *)((int)puPixelRow + iRowStride * 2);
        iVar2 = iVar2 + 1;
        local_4 = local_4 + -1;
      } while (local_4 != 0);
    }
  }
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

