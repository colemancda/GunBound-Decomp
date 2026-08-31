/* QueueTextureRegionSpans - 0x004ebaf0 in the original binary.
 *
 * Two-level tree lookup (param_2 selects a "registry group" node, then
 * param_1 selects a region/index node within it), followed by a
 * row-by-row span emit through QueueTextureRowSpan (0x4eba80). Exact
 * twin of QueueSpriteFrameSpans (0x4ed870): every call site is one
 * basic block that builds ONE argument list and then picks a twin with
 * `cmp byte [node+0x18],1`.
 *
 * FULL RECOVERY (2026-08-31): the original carries FOUR inputs -
 * ECX=param_1 (region index), EDX=param_2 (group), the pushed stack
 * slot is param_3 (x: read at 0x4ebb3a as [esp+0x10] under three saves,
 * biased by [node+0x28] and written back to its own slot at 0x4ebb4d),
 * and EAX is regEax (y: `mov edi,eax` at 0x4ebaf2, biased by
 * [node+0x2c]). An earlier pass had promoted EAX but placed it in the
 * stack slot as a 3rd parameter named `y`, leaving x dropped entirely;
 * both are now in their real positions. The interior loop was also
 * missing everything but the width: the binary passes ECX=x',
 * EDX=row pointer ([node+0x34] + clippedTopRows*width*2, stepped by
 * width*2 per row at 0x4ebbae), EAX=current row, and pushes the width
 * [node+0x20] (reloaded every iteration at 0x4ebba6).
 *
 * All 17 call sites recovered with it: DrawWindGauge's 14 (each
 * mirrors its QueueSpriteFrameSpans twin in the same block - the twin's
 * (index,x,y,group) maps to (index,group,x,y) here; the shared else at
 * 0x407b8f is reached from four blocks that each set ECX to the key the
 * C already spells uVar11, and 0x407c95 likewise from two),
 * DrawStageDecorationBase/Parallax's 2 (y appends spelled out by their
 * own corrected comments), and QueueSpriteSpansByContentId's tail
 * forward `mov [esp+4],ebx / jmp 0x4ebaf0` at 0x4eb933.
 * Raw/near-verbatim port of Ghidra's decompiler output otherwise, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 */
#include "ghidra_types.h"


undefined4 __fastcall QueueTextureRegionSpans(uint param_1,uint param_2,int param_3,int regEax)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
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
      uVar4 = *(uint *)(iVar2 + 0x20);
      iVar5 = regEax + *(int *)(iVar2 + 0x2c);
      iVar6 = (g_clipMinY - iVar5 < 0) - 1 & g_clipMinY - iVar5;
      iVar7 = *(int *)(iVar2 + 0x34) + (int)uVar4 * iVar6 * 2;
      iVar3 = *(int *)(iVar2 + 0x24) - iVar6;
      param_3 = param_3 + *(int *)(iVar2 + 0x28);
      if (iVar5 < g_clipMinY) {
        iVar5 = g_clipMinY;
      }
      if (g_clipMaxY < iVar3 + iVar5) {
        iVar3 = (g_clipMaxY - iVar5) + 1;
      }
      if (0 < iVar3) {
        do {
          QueueTextureRowSpan(param_3,iVar7,(int)uVar4,iVar5);
          uVar4 = *(uint *)(iVar2 + 0x20);
          iVar7 = iVar7 + (int)uVar4 * 2;
          iVar5 = iVar5 + 1;
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
