/* BlitSpriteRowClipped - 0x004eb940 in the original binary.
 * (FUN_004eb940 in the notes below is BlitSpriteRowClipped's old symbol.)
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): its sole caller BlitSpriteClipped calls it
 * once per sprite row with the row width, the row's pixel pointer, the
 * destination y and the left edge x. The clip test uses the g_clipMinX /
 * g_clipMaxX / g_clipMinY / g_clipMaxY globals that BlitSpriteClipped's
 * own vertical clipping shares, and the copy goes to g_screenSurface at 16
 * bits per pixel (width * 2 bytes, pitch g_screenPitch).
 *
 * DROPPED REGISTER ARGUMENT (2026-07-14), 4th param, arrives in EAX -
 * confirmed via objdump at the real entry (0x4eb940-0x4eb965): `mov
 * ebp,[esp+0x8]` (row/y, the real 3rd stack arg), `mov esi,edx` (pixel
 * data), then `lea edi,[eax+ecx*1]` / `cmp edi,edx` - EAX is added
 * directly to ECX (the row-width count) for the right-edge clip check,
 * i.e. EAX is the LEFT edge (screen x), ECX is the run WIDTH - the exact
 * opposite of what BlitSpriteClipped.c's un-fixed call `FUN_004eb940(x,
 * puPixelRow,iVar2)` assumed (it passed x into param_1/ECX, the width
 * slot, and left the real width value - iRowStride, which BlitSpriteClipped
 * already has in a local by this point - never passed at all, with x itself
 * never reaching this function through any parameter). Promoted to an
 * explicit 4th `x` parameter; this is the ONLY call site, so no K&R-empty
 * compatibility declaration is needed.
 */
#include "ghidra_types.h"


void __fastcall BlitSpriteRowClipped(int width,undefined4 *param_2,int param_3,int x)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;

  if ((((g_clipMinY <= param_3) && (param_3 <= g_clipMaxY)) &&
      (g_clipMinX <= x + width)) && (x <= g_clipMaxX)) {
    if (x < g_clipMinX) {
      param_2 = (undefined4 *)((int)param_2 + (g_clipMinX - x) * 2);
      width = width + (x - g_clipMinX);
      x = g_clipMinX;
    }
    if (g_clipMaxX < x + width) {
      width = (g_clipMaxX - x) + 1;
    }
    uVar1 = width * 2 & (width * 2 < 0) - 1;
    puVar3 = (undefined4 *)(g_screenSurface + (g_screenPitch * param_3 + x) * 2);
    for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar3 = *param_2;
      param_2 = param_2 + 1;
      puVar3 = puVar3 + 1;
    }
    for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
      *(undefined1 *)puVar3 = *(undefined1 *)param_2;
      param_2 = (undefined4 *)((int)param_2 + 1);
      puVar3 = (undefined4 *)((int)puVar3 + 1);
    }
  }
  return;
}
