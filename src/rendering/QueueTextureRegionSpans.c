/* QueueTextureRegionSpans - 0x004ebaf0 in the original binary.
 *
 * Two-level tree lookup (param_2 selects a "registry group" node, then
 * param_1 selects a region/index node within it), matching the same
 * dropped-register bug class as DrawHLine/BlitSpriteDirect/FindGround
 * HeightAtColumn: `y` (the row-window offset added at `iVar5 = in_EAX +
 * ...`) was dropped as `in_EAX` - confirmed via direct disassembly of
 * this function's own body at 0x4ebaf0 (ECX=param_1, EDX=param_2,
 * EAX=y). Promoted to an explicit 3rd param.
 *
 * Every known call site currently passes a single argument that, on
 * inspection, is really the (previously entirely absent) `y` value -
 * param_1/param_2 are usually small/fixed constants specific to each
 * caller's "registry group" (e.g. DrawStageDecorationBase/Parallax both
 * use group 0xea60, just different region indices 0/1) and were
 * entirely missing, not just mispositioned. See DrawStageDecorationBase
 * .c/DrawStageDecorationParallax.c for 2 confirmed, fixed examples.
 * DrawWindGauge.c's 14 call sites and QueueSpriteSpansByContentId.c's 1
 * remain unfixed - the former because several of its call sites turned
 * out to be Ghidra merging 2+ distinct machine call instructions (with
 * different constants) into a single C source line, a control-flow-
 * level reconstruction beyond simple argument-filling; the latter
 * because its `y` value is forwarded via a tail-jump from a register
 * (`unaff_EBX`) that function's own callers would need to resolve
 * first (a second dropped-register level, not attempted here).
 * Raw/near-verbatim port of Ghidra's decompiler output otherwise, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 */
#include "ghidra_types.h"


undefined4 __fastcall QueueTextureRegionSpans(uint param_1,uint param_2,int y)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  if (uVar1 <= param_2) {
    while (uVar1 != param_2) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar1 = *(uint *)(iVar2 + 4);
      if (param_2 < uVar1) {
        /* Ghidra emitted a bare `return;` in a value-returning function;
         * MSVC falls through with whatever's in EAX, gcc 14 rejects it
         * (-Wreturn-mismatch). This path's result is unused by callers -
         * return 0 to satisfy both toolchains without inventing a value. */
        return 0;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar1 = *(uint *)(iVar2 + 8);
    if (uVar1 <= param_1) {
      while (uVar1 != param_1) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar1 = *(uint *)(iVar2 + 8);
        if (param_1 < uVar1) {
          /* Ghidra emitted a bare `return;` in a value-returning function;
           * MSVC falls through with whatever's in EAX, gcc 14 rejects it
           * (-Wreturn-mismatch). This path's result is unused by callers -
           * return 0 to satisfy both toolchains without inventing a value. */
          return 0;
        }
      }
      uVar4 = *(undefined4 *)(iVar2 + 0x20);
      iVar5 = y + *(int *)(iVar2 + 0x2c);
      iVar3 = *(int *)(iVar2 + 0x24) - ((DAT_00793534 - iVar5 < 0) - 1 & DAT_00793534 - iVar5);
      if (iVar5 < DAT_00793534) {
        iVar5 = DAT_00793534;
      }
      if (DAT_0056df34 < iVar3 + iVar5) {
        iVar3 = (DAT_0056df34 - iVar5) + 1;
      }
      if (0 < iVar3) {
        do {
          QueueTextureRowSpan(uVar4);
          uVar4 = *(undefined4 *)(iVar2 + 0x20);
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
    }
  }
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

