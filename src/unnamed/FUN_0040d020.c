/* FUN_0040d020 - 0x0040d020 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void __thiscall FUN_0040d020(int param_1,int param_2)

{
  SHORT SVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  if ((in_EAX == 0x100) && (*(int *)(param_2 + 8) != 0)) {
    if (param_1 == 9) {
      SVar1 = GetKeyState(0x10);
      iVar3 = *(int *)(param_2 + 8);
      if (SVar1 < 0) {
        iVar2 = *(int *)(iVar3 + 0xc);
        if (*(char *)(iVar2 + 0x15) != '\0') {
          iVar2 = *(int *)(iVar2 + 0xc);
        }
      }
      else {
        iVar2 = *(int *)(iVar3 + 0x10);
        if (*(char *)(iVar2 + 0x15) != '\0') {
          iVar2 = *(int *)(iVar2 + 0x10);
        }
      }
      if (((iVar2 == iVar3) || (*(int *)(iVar2 + 8) == -1)) &&
         (FUN_004f2da0(10,0,0), *(int *)(param_2 + 8) != 0)) {
        FUN_0040ccf0();
        *(undefined4 *)(param_2 + 8) = 0;
      }
      if ((*(int *)(param_2 + 8) != 0) && (iVar3 = FUN_004f30c0(), iVar3 != 0)) {
        FUN_0040ccf0();
        *(int *)(param_2 + 8) = iVar3;
        FUN_0040cc50();
        return;
      }
    }
    else {
      if (param_1 == 0xd) {
        if (*(char *)(*(int *)(*(int *)(param_2 + 8) + 0x10) + 0x15) == '\0') {
          iVar3 = FUN_004f30c0();
          if (iVar3 == 0) {
            return;
          }
          FUN_0040ccf0();
          *(int *)(param_2 + 8) = iVar3;
          FUN_0040cc50();
          return;
        }
        uVar4 = 10;
      }
      else {
        if (param_1 != 0x1b) {
          return;
        }
        uVar4 = 0xb;
      }
      FUN_004f2da0(uVar4,0,0);
      if (*(int *)(param_2 + 8) != 0) {
        FUN_0040ccf0();
        *(undefined4 *)(param_2 + 8) = 0;
      }
    }
  }
  return;
}

