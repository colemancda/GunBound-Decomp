/* FUN_00414070 - 0x00414070 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void __fastcall FUN_00414070(undefined4 param_1,uint param_2,int param_3)

{
  uint in_EAX;
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 local_c;
  undefined4 local_4;
  
  iVar1 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar2 = *(uint *)(iVar1 + 4);
  if (uVar2 <= param_2) {
    while (uVar2 != param_2) {
      iVar1 = *(int *)(iVar1 + 0x1c);
      uVar2 = *(uint *)(iVar1 + 4);
      if (param_2 < uVar2) {
        return;
      }
    }
    iVar1 = *(int *)(iVar1 + 0x10);
    uVar2 = *(uint *)(iVar1 + 8);
    if (uVar2 <= in_EAX) {
      while (uVar2 != in_EAX) {
        iVar1 = *(int *)(iVar1 + 0x10);
        uVar2 = *(uint *)(iVar1 + 8);
        if (in_EAX < uVar2) {
          return;
        }
      }
      uVar2 = *(int *)(iVar1 + 0x2c) + 0x40;
      iVar4 = *(int *)(iVar1 + 0x28) + 0x40;
      iVar3 = *(int *)(iVar1 + 0x20);
      local_4 = *(int *)(iVar1 + 0x24) - (((int)-uVar2 < 0) - 1 & -uVar2);
      uVar2 = uVar2 & ((int)uVar2 < 0) - 1;
      if (0x7f < (int)(local_4 + uVar2)) {
        local_4 = 0x7f - uVar2;
      }
      if (iVar4 < 0) {
        iVar3 = iVar3 + iVar4;
        iVar4 = 0;
      }
      if (0x7f < iVar4 + iVar3) {
        iVar3 = 0x7f - iVar4;
      }
      if (0 < local_4) {
        param_3 = param_3 + (uVar2 * 0x80 + iVar4) * 2;
        do {
          iVar1 = param_3;
          local_c = iVar3;
          if (0 < iVar3) {
            do {
              FUN_00413ee0(iVar1);
              local_c = local_c + -1;
              iVar1 = iVar1 + 2;
            } while (local_c != 0);
          }
          param_3 = param_3 + 0x100;
          local_4 = local_4 + -1;
        } while (local_4 != 0);
      }
    }
  }
  return;
}

