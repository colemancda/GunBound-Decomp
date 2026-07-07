/* FUN_004ea230 - 0x004ea230 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004ea230(uint param_1,int param_2)

{
  int in_EAX;
  byte bVar1;
  int iVar2;
  byte bVar3;
  char cVar4;
  
  bVar3 = *(byte *)(in_EAX + 0xf6b6);
  bVar1 = bVar3 + param_2;
  *(byte *)(in_EAX + 0xf6b6) = bVar1;
  *(ushort *)(in_EAX + 0xf6b4) = *(ushort *)(in_EAX + 0xf6b4) | (ushort)(param_1 >> (bVar3 & 0x1f));
  if (7 < bVar1) {
    *(undefined1 *)(*(int *)(in_EAX + 0xf6bc) + *(int *)(in_EAX + 0xf6c8)) =
         *(undefined1 *)(in_EAX + 0xf6b5);
    bVar3 = *(char *)(in_EAX + 0xf6b6) - 8;
    iVar2 = *(int *)(in_EAX + 0xf6c8) + 1;
    *(byte *)(in_EAX + 0xf6b6) = bVar3;
    *(int *)(in_EAX + 0xf6c8) = iVar2;
    if (7 < bVar3) {
      *(undefined1 *)(iVar2 + *(int *)(in_EAX + 0xf6bc)) = *(undefined1 *)(in_EAX + 0xf6b4);
      cVar4 = *(char *)(in_EAX + 0xf6b6) + -8;
      *(int *)(in_EAX + 0xf6c8) = *(int *)(in_EAX + 0xf6c8) + 1;
      *(char *)(in_EAX + 0xf6b6) = cVar4;
      *(int *)(in_EAX + 4) = *(int *)(in_EAX + 4) + 2;
      *(short *)(in_EAX + 0xf6b4) = (short)(param_1 << (param_2 - cVar4 & 0x1fU));
      return;
    }
    *(ushort *)(in_EAX + 0xf6b4) = (ushort)*(byte *)(in_EAX + 0xf6b4) << 8;
    *(int *)(in_EAX + 4) = *(int *)(in_EAX + 4) + 1;
  }
  return;
}

