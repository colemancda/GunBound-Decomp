/* FUN_004ea1b0 - 0x004ea1b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


ushort FUN_004ea1b0(void)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  int in_EAX;
  byte bVar4;
  uint uVar5;
  
  if (*(byte *)(in_EAX + 0xf6b2) < 9) {
    do {
      iVar3 = *(int *)(in_EAX + 0xf6c4);
      if (*(int *)(in_EAX + 0xf6c0) == iVar3) {
        uVar5 = 0xffffffff;
      }
      else {
        uVar5 = (uint)*(byte *)(*(int *)(in_EAX + 0xf6b8) + iVar3);
        *(int *)(in_EAX + 0xf6c4) = iVar3 + 1;
      }
      cVar1 = *(char *)(in_EAX + 0xf6b2);
      bVar4 = cVar1 + 8;
      *(byte *)(in_EAX + 0xf6b2) = bVar4;
      *(ushort *)(in_EAX + 0xf6b0) =
           *(ushort *)(in_EAX + 0xf6b0) | (ushort)(uVar5 << (8U - cVar1 & 0x1f));
    } while (bVar4 < 9);
  }
  uVar2 = *(ushort *)(in_EAX + 0xf6b0);
  *(ushort *)(in_EAX + 0xf6b0) = uVar2 << 8;
  *(char *)(in_EAX + 0xf6b2) = *(char *)(in_EAX + 0xf6b2) + -8;
  return uVar2 >> 8;
}

