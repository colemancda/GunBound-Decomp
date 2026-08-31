/* FUN_004ea120 - 0x004ea120 in the original binary.
 *
 * The LZHUF decoder's GetBit, raw-port side (src/lzhuf/GetBit.c is the
 * clean lzhuf_state reimplementation of this same address). DROPPED-REG
 * FIX (2026-08-31): the decode context arrives in EAX (bit buffer
 * +0xf6b0, bit count +0xf6b2, source +0xf6b8/+0xf6c0/+0xf6c4), promoted
 * to regEax; both raw-port callers (FUN_004ea670/FUN_004ea6e0) pass
 * their own promoted context.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


bool FUN_004ea120(int regEax)

{
  char cVar1;
  short sVar2;
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
      if ((short)uVar5 < 0) {
        uVar5 = 0;
      }
      cVar1 = *(char *)(regEax + 0xf6b2);
      bVar4 = cVar1 + 8;
      *(byte *)(regEax + 0xf6b2) = bVar4;
      *(ushort *)(regEax + 0xf6b0) =
           *(ushort *)(regEax + 0xf6b0) | (ushort)(uVar5 << (8U - cVar1 & 0x1f));
    } while (bVar4 < 9);
  }
  sVar2 = *(short *)(regEax + 0xf6b0);
  *(short *)(regEax + 0xf6b0) = sVar2 * 2;
  *(char *)(regEax + 0xf6b2) = *(char *)(regEax + 0xf6b2) + -1;
  return sVar2 < 0;
}

