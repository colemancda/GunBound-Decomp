/* FUN_004e9e90 - 0x004e9e90 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e9e90(void)

{
  byte bVar1;
  uint uVar2;
  int in_EAX;
  int iVar3;
  uint uVar4;
  int unaff_ESI;
  int iVar5;
  
  bVar1 = *(byte *)(unaff_ESI + 8 + in_EAX);
  *(undefined4 *)(in_EAX + 0x104c + unaff_ESI * 4) = 0x1000;
  *(undefined4 *)(in_EAX + 0x5050 + unaff_ESI * 4) = 0x1000;
  iVar5 = 1;
  iVar3 = bVar1 + 0x1001;
  *(undefined4 *)(in_EAX + 0x1048) = 0;
  do {
    if (iVar5 < 0) {
      iVar5 = *(int *)(in_EAX + 0x104c + iVar3 * 4);
      if (iVar5 == 0x1000) {
        *(int *)(in_EAX + 0x104c + iVar3 * 4) = unaff_ESI;
        *(int *)(in_EAX + 0x9454 + unaff_ESI * 4) = iVar3;
        return;
      }
    }
    else {
      iVar5 = *(int *)(in_EAX + 0x5050 + iVar3 * 4);
      if (iVar5 == 0x1000) {
        *(int *)(in_EAX + 0x5050 + iVar3 * 4) = unaff_ESI;
        *(int *)(in_EAX + 0x9454 + unaff_ESI * 4) = iVar3;
        return;
      }
    }
    iVar3 = iVar5;
    uVar4 = 1;
    do {
      iVar5 = (uint)*(byte *)(uVar4 + unaff_ESI + 8 + in_EAX) -
              (uint)*(byte *)(iVar3 + 8 + in_EAX + uVar4);
      if (iVar5 != 0) break;
      uVar4 = uVar4 + 1;
    } while ((int)uVar4 < 0x3c);
    if (2 < (int)uVar4) {
      uVar2 = *(uint *)(in_EAX + 0x1048);
      if (*(uint *)(in_EAX + 0x1048) < uVar4) {
        *(uint *)(in_EAX + 0x1044) = (unaff_ESI - iVar3 & 0xfffU) - 1;
        *(uint *)(in_EAX + 0x1048) = uVar4;
        uVar2 = uVar4;
        if (0x3b < uVar4) {
          *(undefined4 *)(in_EAX + 0x9454 + unaff_ESI * 4) =
               *(undefined4 *)(in_EAX + 0x9454 + iVar3 * 4);
          *(undefined4 *)(in_EAX + 0x104c + unaff_ESI * 4) =
               *(undefined4 *)(in_EAX + 0x104c + iVar3 * 4);
          *(undefined4 *)(in_EAX + 0x5050 + unaff_ESI * 4) =
               *(undefined4 *)(in_EAX + 0x5050 + iVar3 * 4);
          *(int *)(in_EAX + 0x9454 + *(int *)(in_EAX + 0x104c + iVar3 * 4) * 4) = unaff_ESI;
          *(int *)(in_EAX + 0x9454 + *(int *)(in_EAX + 0x5050 + iVar3 * 4) * 4) = unaff_ESI;
          iVar5 = *(int *)(in_EAX + 0x9454 + iVar3 * 4);
          if (*(int *)(in_EAX + 0x5050 + iVar5 * 4) != iVar3) {
            *(int *)(in_EAX + 0x104c + iVar5 * 4) = unaff_ESI;
            *(undefined4 *)(in_EAX + 0x9454 + iVar3 * 4) = 0x1000;
            return;
          }
          *(int *)(in_EAX + 0x5050 + iVar5 * 4) = unaff_ESI;
          *(undefined4 *)(in_EAX + 0x9454 + iVar3 * 4) = 0x1000;
          return;
        }
      }
      if ((uVar4 == uVar2) &&
         (uVar4 = (unaff_ESI - iVar3 & 0xfffU) - 1, uVar4 < *(uint *)(in_EAX + 0x1044))) {
        *(uint *)(in_EAX + 0x1044) = uVar4;
      }
    }
  } while( true );
}

