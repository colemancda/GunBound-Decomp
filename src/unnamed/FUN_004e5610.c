/* FUN_004e5610 - 0x004e5610 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


bool FUN_004e5610(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int unaff_EBX;
  undefined4 *puVar5;
  undefined4 *puVar6;
  ushort *puVar7;
  
  iVar1 = recv(*(SOCKET *)(unaff_EBX + 0x24),
               (char *)(*(int *)(unaff_EBX + 0x4230) + 0x230 + unaff_EBX),
               0x4000 - *(int *)(unaff_EBX + 0x4230),0);
  if (iVar1 < 0) {
    iVar1 = WSAGetLastError();
    return iVar1 == 0x2733;
  }
  iVar1 = *(int *)(unaff_EBX + 0x4230) + iVar1;
  uVar2 = (uint)*(ushort *)(unaff_EBX + 0x230);
  *(int *)(unaff_EBX + 0x4230) = iVar1;
  if ((int)uVar2 <= iVar1) {
    while (1 < *(int *)(unaff_EBX + 0x4230)) {
      if (0x20000 < (int)(*(int *)(unaff_EBX + 0x2423c) + uVar2)) {
        if ((*(int *)(unaff_EBX + 0x24240 + *(int *)(unaff_EBX + 0x24238) * 4) <= (int)uVar2) &&
           (*(int *)(unaff_EBX + 0x24234) != *(int *)(unaff_EBX + 0x24238))) {
          if ((*(int *)(unaff_EBX + 0x22c) != 1) && (*(int *)(unaff_EBX + 0x20) != 0)) {
            FUN_004f2da0(0x65,*(undefined4 *)(unaff_EBX + 0x1c),0);
          }
          *(undefined4 *)(unaff_EBX + 0x22c) = 0;
          return false;
        }
        *(undefined4 *)(unaff_EBX + 0x2423c) = 0;
      }
      uVar4 = *(int *)(unaff_EBX + 0x24234) + 1U & 0x800000ff;
      if ((int)uVar4 < 0) {
        uVar4 = (uVar4 - 1 | 0xffffff00) + 1;
      }
      if (uVar4 == *(uint *)(unaff_EBX + 0x24238)) {
        if ((*(int *)(unaff_EBX + 0x22c) != 1) && (*(int *)(unaff_EBX + 0x20) != 0)) {
          FUN_004f2da0(0x65,*(undefined4 *)(unaff_EBX + 0x1c),0);
        }
        *(undefined4 *)(unaff_EBX + 0x22c) = 0;
        return false;
      }
      puVar5 = (undefined4 *)(unaff_EBX + 0x232);
      puVar6 = (undefined4 *)(*(int *)(unaff_EBX + 0x2423c) + 0x4234 + unaff_EBX);
      for (uVar3 = uVar2 - 2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      for (uVar3 = uVar2 - 2 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
        puVar5 = (undefined4 *)((int)puVar5 + 1);
        puVar6 = (undefined4 *)((int)puVar6 + 1);
      }
      *(undefined4 *)(unaff_EBX + 0x24240 + *(int *)(unaff_EBX + 0x24234) * 4) =
           *(undefined4 *)(unaff_EBX + 0x2423c);
      *(uint *)(unaff_EBX + 0x24640 + *(int *)(unaff_EBX + 0x24234) * 4) = uVar2 - 2;
      *(uint *)(unaff_EBX + 0x24234) = uVar4;
      *(uint *)(unaff_EBX + 0x2423c) = *(int *)(unaff_EBX + 0x2423c) + (uVar2 - 2);
      puVar5 = (undefined4 *)(uVar2 + 0x230 + unaff_EBX);
      puVar7 = (ushort *)(unaff_EBX + 0x230);
      for (uVar4 = 0x4000 - uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)puVar7 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar7 = puVar7 + 2;
      }
      for (uVar4 = 0x4000 - uVar2 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined1 *)puVar7 = *(undefined1 *)puVar5;
        puVar5 = (undefined4 *)((int)puVar5 + 1);
        puVar7 = (ushort *)((int)puVar7 + 1);
      }
      iVar1 = *(int *)(unaff_EBX + 0x4230) - uVar2;
      *(int *)(unaff_EBX + 0x4230) = iVar1;
      uVar2 = (uint)*(ushort *)(unaff_EBX + 0x230);
      if (iVar1 < (int)uVar2) {
        return true;
      }
    }
  }
  return true;
}

