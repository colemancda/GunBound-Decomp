/* FUN_004ea580 - 0x004ea580 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ea580(int param_1)

{
  uint *puVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  if (*(int *)(in_EAX + 0xde28) == 0x8000) {
    FUN_004ea3b0();
  }
  iVar4 = *(int *)(in_EAX + 0xe7fc + param_1 * 4);
  do {
    uVar5 = *(int *)(in_EAX + 0xd460 + iVar4 * 4) + 1;
    *(uint *)(in_EAX + 0xd460 + iVar4 * 4) = uVar5;
    if (*(uint *)(in_EAX + 0xd464 + iVar4 * 4) < uVar5) {
      iVar2 = iVar4 + 1;
      iVar6 = in_EAX + 0xd460 + iVar2 * 4;
      do {
        iVar3 = iVar2 + 1;
        if ((uVar5 <= *(uint *)(iVar6 + 4)) || (iVar3 = iVar2 + 2, uVar5 <= *(uint *)(iVar6 + 8)))
        break;
        puVar1 = (uint *)(iVar6 + 0xc);
        iVar6 = iVar6 + 0xc;
        iVar2 = iVar2 + 3;
        iVar3 = iVar2;
      } while (*puVar1 < uVar5);
      iVar6 = iVar3 + -1;
      *(undefined4 *)(in_EAX + 0xd460 + iVar4 * 4) = *(undefined4 *)(in_EAX + 0xd45c + iVar3 * 4);
      *(uint *)(in_EAX + 0xd460 + iVar6 * 4) = uVar5;
      iVar2 = *(int *)(in_EAX + 0xece4 + iVar4 * 4);
      *(int *)(in_EAX + 0xde30 + iVar2 * 4) = iVar6;
      if (iVar2 < 0x273) {
        *(int *)(in_EAX + 0xde34 + iVar2 * 4) = iVar6;
      }
      iVar3 = *(int *)(in_EAX + 0xece4 + iVar6 * 4);
      *(int *)(in_EAX + 0xece4 + iVar6 * 4) = iVar2;
      *(int *)(in_EAX + 0xde30 + iVar3 * 4) = iVar4;
      if (iVar3 < 0x273) {
        *(int *)(in_EAX + 0xde34 + iVar3 * 4) = iVar4;
      }
      *(int *)(in_EAX + 0xece4 + iVar4 * 4) = iVar3;
      iVar4 = *(int *)(in_EAX + 0xde30 + iVar6 * 4);
    }
    else {
      iVar4 = *(int *)(in_EAX + 0xde30 + iVar4 * 4);
    }
    if (iVar4 == 0) {
      return;
    }
  } while( true );
}

