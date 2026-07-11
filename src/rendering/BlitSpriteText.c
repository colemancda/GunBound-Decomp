/* BlitSpriteText - 0x004ed9f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall BlitSpriteText(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint unaff_ESI;
  
  iVar4 = 0;
  if (param_4 < 1) {
    return;
  }
LAB_004eda02:
  if (((*(char *)(param_3 + iVar4) != ' ') &&
      (uVar1 = *(char *)(param_3 + iVar4) + -0x30 + param_2, DAT_0079352c != 0)) &&
     (-1 < (int)uVar1)) {
    iVar3 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar2 = *(uint *)(iVar3 + 4);
    while (uVar2 <= unaff_ESI) {
      if (uVar2 == unaff_ESI) {
        iVar3 = *(int *)(iVar3 + 0x10);
        uVar2 = *(uint *)(iVar3 + 8);
        if (uVar2 <= uVar1) goto LAB_004eda4e;
        break;
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar2 = *(uint *)(iVar3 + 4);
    }
  }
  goto LAB_004eda7d;
  while( true ) {
    iVar3 = *(int *)(iVar3 + 0x10);
    uVar2 = *(uint *)(iVar3 + 8);
    if (uVar1 < uVar2) break;
LAB_004eda4e:
    if (uVar2 == uVar1) {
      if (*(char *)(iVar3 + 0x18) == '\x01') {
        BlitSprite16bpp(param_1);
      }
      else {
        BlitSpriteClipped(uVar1);
      }
      break;
    }
  }
LAB_004eda7d:
  iVar4 = iVar4 + 1;
  param_1 = param_1 + param_5;
  if (param_4 <= iVar4) {
    return;
  }
  goto LAB_004eda02;
}

