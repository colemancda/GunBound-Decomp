/* FUN_004049a0 - 0x004049a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_004049a0(void)

{
  int iVar1;
  undefined4 in_EAX;
  int iVar2;
  int iVar3;
  int iVar4;
  int *unaff_EDI;
  
  iVar2 = FUN_00404dd0(in_EAX);
  *(undefined4 *)(iVar2 + 0x104) = 0;
  iVar4 = iVar2;
  if (iVar2 != *unaff_EDI) {
    do {
      iVar1 = *(int *)(iVar4 + 0x110);
      if (*(int *)(iVar1 + 0x104) != 0) break;
      iVar3 = *(int *)(*(int *)(iVar1 + 0x110) + 0x108);
      if (iVar1 == iVar3) {
        iVar3 = *(int *)(*(int *)(iVar1 + 0x110) + 0x10c);
        if ((iVar3 == 0) || (*(int *)(iVar3 + 0x104) != 0)) {
          if (iVar4 == *(int *)(iVar1 + 0x10c)) {
            FUN_00404c40();
            iVar4 = iVar1;
          }
          *(undefined4 *)(*(int *)(iVar4 + 0x110) + 0x104) = 1;
          *(undefined4 *)(*(int *)(*(int *)(iVar4 + 0x110) + 0x110) + 0x104) = 0;
          FUN_00404cd0();
        }
        else {
LAB_00404a08:
          *(undefined4 *)(*(int *)(iVar4 + 0x110) + 0x104) = 1;
          *(undefined4 *)(iVar3 + 0x104) = 1;
          *(undefined4 *)(*(int *)(*(int *)(iVar4 + 0x110) + 0x110) + 0x104) = 0;
          iVar4 = *(int *)(*(int *)(iVar4 + 0x110) + 0x110);
        }
      }
      else {
        if ((iVar3 != 0) && (*(int *)(iVar3 + 0x104) == 0)) goto LAB_00404a08;
        if (iVar4 == *(int *)(iVar1 + 0x108)) {
          FUN_00404cd0();
          iVar4 = iVar1;
        }
        *(undefined4 *)(*(int *)(iVar4 + 0x110) + 0x104) = 1;
        *(undefined4 *)(*(int *)(*(int *)(iVar4 + 0x110) + 0x110) + 0x104) = 0;
        FUN_00404c40();
      }
    } while (iVar4 != *unaff_EDI);
  }
  *(undefined4 *)(*unaff_EDI + 0x104) = 1;
  *(int *)(*unaff_EDI + 0x110) = unaff_EDI[5];
  return iVar2;
}

