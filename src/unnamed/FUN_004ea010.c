/* FUN_004ea010 - 0x004ea010 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004ea010(undefined4 param_1,int param_2)

{
  int iVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  
  if (*(int *)(in_EAX + 0x9454 + param_2 * 4) != 0x1000) {
    iVar2 = *(int *)(in_EAX + 0x104c + param_2 * 4);
    iVar1 = *(int *)(in_EAX + 0x5050 + param_2 * 4);
    iVar3 = iVar2;
    if ((iVar1 != 0x1000) && (iVar3 = iVar1, iVar2 != 0x1000)) {
      if (*(int *)(in_EAX + 0x5050 + iVar2 * 4) != 0x1000) {
        do {
          iVar2 = *(int *)(in_EAX + 0x5050 + iVar2 * 4);
        } while (*(int *)(in_EAX + 0x5050 + iVar2 * 4) != 0x1000);
        *(undefined4 *)(in_EAX + 0x5050 + *(int *)(in_EAX + 0x9454 + iVar2 * 4) * 4) =
             *(undefined4 *)(in_EAX + 0x104c + iVar2 * 4);
        *(undefined4 *)(in_EAX + 0x9454 + *(int *)(in_EAX + 0x104c + iVar2 * 4) * 4) =
             *(undefined4 *)(in_EAX + 0x9454 + iVar2 * 4);
        *(undefined4 *)(in_EAX + 0x104c + iVar2 * 4) =
             *(undefined4 *)(in_EAX + 0x104c + param_2 * 4);
        *(int *)(in_EAX + 0x9454 + *(int *)(in_EAX + 0x104c + param_2 * 4) * 4) = iVar2;
      }
      *(undefined4 *)(in_EAX + 0x5050 + iVar2 * 4) = *(undefined4 *)(in_EAX + 0x5050 + param_2 * 4);
      *(int *)(in_EAX + 0x9454 + *(int *)(in_EAX + 0x5050 + param_2 * 4) * 4) = iVar2;
      iVar3 = iVar2;
    }
    *(undefined4 *)(in_EAX + 0x9454 + iVar3 * 4) = *(undefined4 *)(in_EAX + 0x9454 + param_2 * 4);
    iVar1 = *(int *)(in_EAX + 0x9454 + param_2 * 4);
    if (*(int *)(in_EAX + 0x5050 + iVar1 * 4) == param_2) {
      *(int *)(in_EAX + 0x5050 + iVar1 * 4) = iVar3;
      *(undefined4 *)(in_EAX + 0x9454 + param_2 * 4) = 0x1000;
      return;
    }
    *(int *)(in_EAX + 0x104c + iVar1 * 4) = iVar3;
    *(undefined4 *)(in_EAX + 0x9454 + param_2 * 4) = 0x1000;
  }
  return;
}

