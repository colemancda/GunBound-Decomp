/* FUN_00413ee0 - 0x00413ee0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00413ee0(ushort *param_1)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  ushort *in_EAX;
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

