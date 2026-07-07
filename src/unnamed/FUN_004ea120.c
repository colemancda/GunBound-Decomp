/* FUN_004ea120 - 0x004ea120 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


bool FUN_004ea120(void)

{
  char cVar1;
  short sVar2;
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
      if ((short)uVar5 < 0) {
        uVar5 = 0;
      }
      cVar1 = *(char *)(in_EAX + 0xf6b2);
      bVar4 = cVar1 + 8;
      *(byte *)(in_EAX + 0xf6b2) = bVar4;
      *(ushort *)(in_EAX + 0xf6b0) =
           *(ushort *)(in_EAX + 0xf6b0) | (ushort)(uVar5 << (8U - cVar1 & 0x1f));
    } while (bVar4 < 9);
  }
  sVar2 = *(short *)(in_EAX + 0xf6b0);
  *(short *)(in_EAX + 0xf6b0) = sVar2 * 2;
  *(char *)(in_EAX + 0xf6b2) = *(char *)(in_EAX + 0xf6b2) + -1;
  return sVar2 < 0;
}

