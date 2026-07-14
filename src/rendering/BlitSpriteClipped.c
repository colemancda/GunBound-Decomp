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
 * `mov eax,0xea0e18` (container = &DAT_00ea0e18) with no EDX write in
 * between - EDX (outer key) is inherited live from the caller, matching
 * State06_Logo2_Render's already-fixed `FindSpriteFrame((int)&DAT_00ea0e18,
 * 10000,frameIndex)` call, which leaves EDX=10000 live across its
 * subsequent BlitSpriteClipped() call. Passed explicitly here rather than
 * relying on register survival across the intervening C code.
 */
#include "ghidra_types.h"
#include <windows.h>


undefined4 BlitSpriteClipped(int frame,int x,int y)

{
  int iVar1;
  int iVar2;
  int local_4;
  int iRowStride;
  undefined4 *puPixelRow;

  if (((DAT_0079352c != 0) && (-1 < frame)) &&
     (iVar1 = FindSpriteFrame((int)&DAT_00ea0e18,10000,frame), iVar1 != 0)) {
    iVar2 = y + *(int *)(iVar1 + 0x2c);
    x = x + *(int *)(iVar1 + 0x28);
    iRowStride = *(int *)(iVar1 + 0x20);
    local_4 = *(int *)(iVar1 + 0x24) - ((DAT_00793534 - iVar2 < 0) - 1 & DAT_00793534 - iVar2);
    puPixelRow = (undefined4 *)
                 (*(int *)(iVar1 + 0x34) +
                  iRowStride * ((DAT_00793534 - iVar2 < 0) - 1 & DAT_00793534 - iVar2) * 2);
    if (iVar2 < DAT_00793534) {
      iVar2 = DAT_00793534;
    }
    if (DAT_0056df34 < local_4 + iVar2) {
      local_4 = (DAT_0056df34 - iVar2) + 1;
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

