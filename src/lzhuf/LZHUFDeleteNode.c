/* LZHUFDeleteNode - 0x004ea010 in the original binary.
 *
 * Classic LZSS DeleteNode(): splices a node out of the lson/rson/dad
 * match tree (arrays at state+0x104c/+0x5050/+0x9454, NIL sentinel
 * 0x1000). NAMED (2026-07-18).
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall LZHUFDeleteNode(undefined4 param_1,int param_2)

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

