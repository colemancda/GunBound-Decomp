/* FUN_0044c460 - 0x0044c460 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0044c460(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  int in_EAX;
  int iVar4;
  uint unaff_EDI;
  int local_8;
  int local_4;
  
  bVar3 = false;
  local_8 = 0;
  if (param_4 < 1) {
    return;
  }
  local_4 = param_4;
LAB_0044c490:
  if (local_4 % 3 == 0) {
    if ((((bVar3) && (DAT_0079352c != 0)) && (-1 < in_EAX)) && (iVar4 = FUN_004f30c0(), iVar4 != 0))
    {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(param_1);
      }
      else {
        BlitSpriteClipped();
      }
    }
    param_1 = param_1 + param_6;
  }
  if (*(char *)(local_8 + param_3) != ' ') {
    uVar1 = *(char *)(local_8 + param_3) + -0x30 + param_2;
    bVar3 = true;
    if ((DAT_0079352c != 0) && (-1 < (int)uVar1)) {
      iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar2 = *(uint *)(iVar4 + 4);
      while (uVar2 <= unaff_EDI) {
        if (uVar2 == unaff_EDI) {
          iVar4 = *(int *)(iVar4 + 0x10);
          uVar2 = *(uint *)(iVar4 + 8);
          if (uVar2 <= uVar1) goto LAB_0044c53f;
          break;
        }
        iVar4 = *(int *)(iVar4 + 0x1c);
        uVar2 = *(uint *)(iVar4 + 4);
      }
    }
  }
  goto LAB_0044c56e;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    uVar2 = *(uint *)(iVar4 + 8);
    if (uVar1 < uVar2) break;
LAB_0044c53f:
    if (uVar2 == uVar1) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(param_1);
      }
      else {
        BlitSpriteClipped(uVar1);
      }
      break;
    }
  }
LAB_0044c56e:
  param_1 = param_1 + param_5;
  local_8 = local_8 + 1;
  local_4 = local_4 + -1;
  if (param_4 <= local_8) {
    return;
  }
  goto LAB_0044c490;
}

