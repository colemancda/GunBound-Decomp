/* FUN_00413ee0 - 0x00413ee0 in the original binary.
 *
 * Per-pixel ARGB4444 alpha blend of one source texel over one canvas
 * texel (used by FUN_00414070's avatar-part compositing loop): alpha 0
 * = skip, alpha 0xf = copy, else channel-wise (src*a + dst*(15-a))/15,
 * preserving the destination's alpha nibble when it is non-zero.
 *
 * DROPPED-EAX FIX (2026-08-06): the SOURCE texel pointer arrives in EAX
 * (orig 0x414160-0x414163: `push ebx (dest); mov eax,edi (src); call`,
 * caller-cleaned) - Ghidra kept it as an unassigned `in_EAX` artifact
 * and the sole caller passed only the destination, so every blend read
 * its source through a garbage register. Recovered as an explicit
 * second parameter; the sole caller (FUN_00414070) is our own code, so
 * plain cdecl on both sides is self-consistent. */
#include "ghidra_types.h"


void FUN_00413ee0(ushort *param_1,ushort *src)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  ushort *in_EAX = src;
  ushort uVar6;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar7;
  
  uVar1 = *in_EAX;
  uVar6 = uVar1 >> 0xc;
  uVar7 = (uint)uVar6;
  if (uVar6 != 0) {
    if (uVar6 == 0xf) {
      *param_1 = uVar1;
      return;
    }
    uVar8 = (uint)*param_1;
    uVar10 = 0xf - uVar7 & 0xffff;
    uVar9 = (uint)uVar1;
    uVar5 = (ushort)(((uVar8 & 0xf) * uVar10) / 0xf) & 0xf;
    uVar2 = (ushort)(((uVar9 & 0xf00) * uVar7) / 0xf) & 0xf00;
    uVar3 = (ushort)(((uVar8 & 0xf00) * uVar10) / 0xf) & 0xf00;
    uVar4 = (ushort)(((uVar9 & 0xf) * uVar7) / 0xf) & 0xf;
    uVar1 = ((ushort)(((uVar9 & 0xf0) * uVar7) / 0xf) & 0xf0) +
            ((ushort)(((uVar8 & 0xf0) * uVar10) / 0xf) & 0xf0);
    if ((*param_1 & 0xf000) == 0) {
      *param_1 = uVar4 + uVar5 | uVar1 | uVar2 + uVar3 | uVar6 << 0xc;
      return;
    }
    *param_1 = uVar4 + uVar5 | uVar1 | uVar2 + uVar3 | *param_1 & 0xf000;
  }
  return;
}

