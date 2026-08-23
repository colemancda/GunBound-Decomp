/* BlendPixels16 - 0x004f2740 in the original binary.
 *
 * Additively blends a solid colour over a run of 16bpp pixels.
 *
 * The blending twin of FillPixels16, which it sits immediately after in the
 * original (0x004f26f0 then 0x004f2740) and whose argument shape it shares:
 * (dest, colour, count).  Where FillPixels16 stores the colour, this halves
 * both operands (>> 1 with the 0x7bef7bef / 0xe79ce79c channel masks), adds
 * them, and re-saturates - two pixels per 32-bit word, with the odd trailing
 * pixel handled separately.
 *
 * Named from that pairing rather than from the arithmetic alone: the masks
 * identify the format as 16bpp with 5/6/5-shaped channels, but it is the
 * shared signature and adjacency with FillPixels16, and the fact that
 * DrawBlendedHLine calls this at the byte-identical address expression
 * DrawHLine passes to FillPixels16, that fix what it is FOR.
 */
#include "ghidra_types.h"


void BlendPixels16(uint *param_1,int param_2,uint param_3)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uStack_20;
  
  if (param_3 != 0) {
    uStack_20 = CONCAT22(param_2,param_2);
    uVar4 = (uStack_20 & 0xe79ce79c) >> 2;
    for (uVar3 = param_3 >> 1; uVar3 != 0; uVar3 = uVar3 - 1) {
      uVar2 = (*param_1 >> 1 & 0x7bef7bef) + uVar4;
      if ((uVar2 & 0x80000000) != 0) {
        uVar2 = uVar2 | 0x78000000;
      }
      if ((uVar2 & 0x4000000) != 0) {
        uVar2 = uVar2 | 0x3e00000;
      }
      if ((uVar2 & 0x100000) != 0) {
        uVar2 = uVar2 | 0xf0000;
      }
      if ((uVar2 & 0x8000) != 0) {
        uVar2 = uVar2 | 0x7800;
      }
      if ((uVar2 & 0x400) != 0) {
        uVar2 = uVar2 | 0x3e0;
      }
      if ((uVar2 & 0x10) != 0) {
        uVar2 = uVar2 | 0xf;
      }
      *param_1 = uVar2 << 1;
      param_1 = param_1 + 1;
    }
    if ((param_3 & 1) != 0) {
      uVar1 = ((ushort)*param_1 >> 1 & 0x7bef) + (short)uVar4;
      if ((uVar1 & 0x8000) != 0) {
        uVar1 = uVar1 | 0x7800;
      }
      if ((uVar1 & 0x400) != 0) {
        uVar1 = uVar1 | 0x3e0;
      }
      if ((uVar1 & 0x10) != 0) {
        uVar1 = uVar1 | 0xf;
      }
      *(ushort *)param_1 = uVar1 << 1;
    }
  }
  return;
}

