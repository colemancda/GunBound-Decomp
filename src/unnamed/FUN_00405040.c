/* FUN_00405040 - 0x00405040 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00405040(int param_1)

{
  int iVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  
  if (in_EAX != 0) {
    iVar3 = *(int *)(in_EAX + 0x108);
    iVar1 = *(int *)(param_1 + 0x14);
    if (iVar3 == iVar1) {
      iVar3 = *(int *)(in_EAX + 0x110);
      if (*(int *)(in_EAX + 0x110) != iVar1) {
        do {
          iVar2 = iVar3;
          iVar3 = iVar2;
          if (in_EAX != *(int *)(iVar2 + 0x108)) break;
          iVar3 = *(int *)(iVar2 + 0x110);
          in_EAX = iVar2;
        } while (iVar3 != iVar1);
        if (iVar3 != iVar1) {
          return iVar3;
        }
      }
    }
    else if (iVar3 != 0) {
      for (iVar2 = *(int *)(iVar3 + 0x10c); iVar2 != iVar1; iVar2 = *(int *)(iVar2 + 0x10c)) {
        iVar3 = iVar2;
      }
      return iVar3;
    }
  }
  return 0;
}

