/* DrawSprite - 0x004eb890 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * Ghidra read the sole argument as `in_EAX`, meaning it was silently
 * dropped at every call site instead of being passed through. Confirmed
 * via objdump at the function's own entry (0x4eb890: `push esi; mov
 * esi,eax; ...`) - the incoming value arrives in EAX, is saved across
 * the FindSpriteFrame() call, and is reloaded into EAX again right
 * before the BlitSprite16bpp()/BlitSpriteClipped() tail calls (e.g.
 * `mov eax,esi` at 0x4eb8b6/0x4eb8c3). Promoted to a real `int param_1`.
 *
 * FindSpriteFrame()'s own EDX/ESI key inputs are NOT set up before the
 * call at 0x4eb8a5 - they pass through untouched from whatever this
 * function's own caller happened to leave in those registers. That is
 * FindSpriteFrame's own pre-existing incomplete-signature issue (see
 * its header comment); not something this function's fix can address.
 *
 * Call-site recovery: of the 16 calls in the original binary, this pass
 * fixed the ones with an unambiguous single EAX value recoverable
 * directly from the call site's own disassembly (GameTick.c;
 * FUN_00505f10.c both sites; RenderPlayerNameplate.c's first 3 of 4).
 * The remaining sites were left unfixed (still call DrawSprite()
 * argless) because recovering their value correctly requires first
 * fixing an unrelated, pre-existing bug in that *caller*, not just
 * adding an argument here:
 *   - RenderPlayerNameplate.c's 4th call (0x4dbd39): the two paths that
 *     reach it in the original binary read *different* struct fields
 *     (+0x449ba vs +0x45914) than the single `if` condition Ghidra
 *     emitted in the decompiled C - the C control flow itself needs
 *     correcting first.
 *   - FUN_00408180.c's 5 calls (0x4082c6/0x4082e2/0x408491/0x40851b/
 *     0x40856c): the two at 0x4082c6/0x4082e2 need the return value of
 *     that file's own PeekChecksumStateUnderLock() call, which the
 *     current decompiled source discards.
 *   - RenderMobile.c's 3 calls (0x46350b/0x463589/0x4635cd): 0x463589
 *     and 0x4635cd both need `*(int *)(param_1 + 0xae38)`, a field
 *     Ghidra never surfaced as a named variable anywhere in that file;
 *     0x46350b's value is loop-carried across iterations in a register
 *     the decompiled C loop body doesn't preserve.
 *   - A 16th call (0x4ac113) is inside a function that isn't ported to
 *     src/ yet at all (only reachable via a shared field offset match
 *     in State11_InBattle_Render.c), so there is no call site to fix.
 *
 * 2026-07-14: recovered the FULL real signature - `y`/`x` (EDI/EBX) and
 * FindSpriteFrame's outerKey/innerKey (EDX/ESI) are ALL genuine pass-
 * through parameters from DrawSprite's own caller, not internal locals -
 * confirmed via objdump at 0x4eb890 (this function never writes EDX/ESI
 * itself before the FindSpriteFrame call) cross-referenced against
 * GameTick.c's own call site (orig 0x413655-0x413664: `mov edi,0x12c /
 * mov ebx,0x190 / mov edx,0x398` immediately before `call 0x4eb890`, ESI
 * left at 0 by an unrelated loop earlier in GameTick). functions.h keeps
 * the K&R-empty declaration (matching FindSpriteFrame/BlitSprite16bpp's
 * own precedent for hot multi-call-site functions) so the other 11
 * not-yet-recovered call sites in this port still compile - they under-
 * supply 4 args and read stack garbage for y/x/outerKey/innerKey, exactly
 * as they already read register garbage today, so this is strictly no
 * worse for them. Only GameTick.c's call site (the one blocking bring-up
 * progress) was updated to pass the real recovered values.
 */
#include "ghidra_types.h"


void DrawSprite(int param_1,int y,int x,int outerKey,int innerKey)

{
  int iVar1;

  if ((DAT_0079352c != 0) && (-1 < param_1)) {
    iVar1 = FindSpriteFrame((int)&DAT_00ea0e18,outerKey,innerKey);
    if (iVar1 != 0) {
      if (*(char *)(iVar1 + 0x18) == '\x01') {
        BlitSprite16bpp(param_1,x,y,outerKey);
        return;
      }
      BlitSpriteClipped(param_1,x,y,outerKey);
    }
  }
  return;
}

