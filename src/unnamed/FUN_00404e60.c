/* FUN_00404e60 - 0x00404e60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00404e60(void)

{
  int in_EAX;
  int iVar1;
  int iVar2;
  int *unaff_EDI;
  
  if (in_EAX == *unaff_EDI) {
    *(undefined4 *)(in_EAX + 0x104) = 1;
    return;
  }
  do {
    if (*(int *)(in_EAX + 0x104) != 1) break;
    iVar2 = *(int *)(in_EAX + 0x110);
    iVar1 = *(int *)(iVar2 + 0x108);
    if (in_EAX == iVar1) {
      iVar1 = *(int *)(iVar2 + 0x10c);
      if (*(int *)(iVar1 + 0x104) == 0) {
        *(undefined4 *)(iVar1 + 0x104) = 1;
        *(undefined4 *)(*(int *)(iVar1 + 0x110) + 0x104) = 0;
        FUN_00404c40();
        iVar2 = *(int *)(in_EAX + 0x110);
        iVar1 = *(int *)(iVar2 + 0x10c);
      }
      if ((*(int *)(*(int *)(iVar1 + 0x108) + 0x104) != 1) ||
         (*(int *)(*(int *)(iVar1 + 0x10c) + 0x104) != 1)) {
        if (*(int *)(*(int *)(iVar1 + 0x10c) + 0x104) == 1) {
          *(undefined4 *)(*(int *)(iVar1 + 0x108) + 0x104) = 1;
          *(undefined4 *)(iVar1 + 0x104) = 0;
          FUN_00404cd0();
          iVar2 = *(int *)(in_EAX + 0x110);
          iVar1 = *(int *)(iVar2 + 0x10c);
        }
        *(undefined4 *)(iVar1 + 0x104) = *(undefined4 *)(iVar2 + 0x104);
        *(undefined4 *)(*(int *)(in_EAX + 0x110) + 0x104) = 1;
        *(undefined4 *)(*(int *)(iVar1 + 0x10c) + 0x104) = 1;
        FUN_00404c40();
        goto LAB_0040501c;
      }
LAB_00404eeb:
      *(undefined4 *)(iVar1 + 0x104) = 0;
      in_EAX = *(int *)(in_EAX + 0x110);
    }
    else {
      if (*(int *)(iVar1 + 0x104) == 0) {
        *(undefined4 *)(iVar1 + 0x104) = 1;
        *(undefined4 *)(*(int *)(iVar1 + 0x110) + 0x104) = 0;
        FUN_00404cd0();
        iVar2 = *(int *)(in_EAX + 0x110);
        iVar1 = *(int *)(iVar2 + 0x108);
      }
      if ((*(int *)(*(int *)(iVar1 + 0x10c) + 0x104) == 1) &&
         (*(int *)(*(int *)(iVar1 + 0x108) + 0x104) == 1)) goto LAB_00404eeb;
      if (*(int *)(*(int *)(iVar1 + 0x108) + 0x104) == 1) {
        *(undefined4 *)(*(int *)(iVar1 + 0x10c) + 0x104) = 1;
        *(undefined4 *)(iVar1 + 0x104) = 0;
        FUN_00404c40();
        iVar2 = *(int *)(in_EAX + 0x110);
        iVar1 = *(int *)(iVar2 + 0x108);
      }
      *(undefined4 *)(iVar1 + 0x104) = *(undefined4 *)(iVar2 + 0x104);
      *(undefined4 *)(*(int *)(in_EAX + 0x110) + 0x104) = 1;
      *(undefined4 *)(*(int *)(iVar1 + 0x108) + 0x104) = 1;
      FUN_00404cd0();
LAB_0040501c:
      in_EAX = *unaff_EDI;
    }
  } while (in_EAX != *unaff_EDI);
  *(undefined4 *)(in_EAX + 0x104) = 1;
  return;
}

