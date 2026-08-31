/* FUN_004ea1b0 - 0x004ea1b0 in the original binary.
 *
 * The LZHUF decoder's GetByte, raw-port side (src/lzhuf/GetByte.c is
 * the clean reimplementation of this same address). DROPPED-REG FIX
 * (2026-08-31): the decode context arrives in EAX, promoted to regEax;
 * the one raw-port caller (FUN_004ea6e0) passes its own context.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


ushort FUN_004ea1b0(int regEax)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  byte bVar4;
  uint uVar5;
  
  if (*(byte *)(regEax + 0xf6b2) < 9) {
    do {
      iVar3 = *(int *)(regEax + 0xf6c4);
      if (*(int *)(regEax + 0xf6c0) == iVar3) {
        uVar5 = 0xffffffff;
      }
      else {
        uVar5 = (uint)*(byte *)(*(int *)(regEax + 0xf6b8) + iVar3);
        *(int *)(regEax + 0xf6c4) = iVar3 + 1;
      }
      cVar1 = *(char *)(regEax + 0xf6b2);
      bVar4 = cVar1 + 8;
      *(byte *)(regEax + 0xf6b2) = bVar4;
      *(ushort *)(regEax + 0xf6b0) =
           *(ushort *)(regEax + 0xf6b0) | (ushort)(uVar5 << (8U - cVar1 & 0x1f));
    } while (bVar4 < 9);
  }
  uVar2 = *(ushort *)(regEax + 0xf6b0);
  *(ushort *)(regEax + 0xf6b0) = uVar2 << 8;
  *(char *)(regEax + 0xf6b2) = *(char *)(regEax + 0xf6b2) + -8;
  return uVar2 >> 8;
}

