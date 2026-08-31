/* FUN_004ea670 - 0x004ea670 in the original binary.
 *
 * The LZHUF DecodeChar, raw-port side (src/lzhuf/DecodeChar.c is the
 * clean reimplementation of this same address). DROPPED-REG FIX
 * (2026-08-31): the context arrives in ESI, promoted to regEsi, and is
 * passed on to GetBit (EAX) and LZHUFUpdate (EAX). Its only binary
 * caller is DecodeLZHUFBlock (0x4eaba0) at 0x4eac17, which the tree
 * covers with the reimplementation - no raw C caller exists.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_004ea670(int regEsi)

{
  int iVar1;
  uint uVar2;
  
  for (uVar2 = *(uint *)(regEsi + 0xf6ac); uVar2 < 0x273;
      uVar2 = *(uint *)(regEsi + 0xece4 + uVar2 * 4)) {
    if (*(char *)(regEsi + 0xf6b2) == '\0') {
      iVar1 = FUN_004ea120(regEsi);
      uVar2 = uVar2 + iVar1;
    }
    else {
      *(char *)(regEsi + 0xf6b2) = *(char *)(regEsi + 0xf6b2) + -1;
      if (*(short *)(regEsi + 0xf6b0) < 0) {
        uVar2 = uVar2 + 1;
      }
      *(short *)(regEsi + 0xf6b0) = *(short *)(regEsi + 0xf6b0) * 2;
    }
  }
  LZHUFUpdate(uVar2 - 0x273,regEsi);
  return uVar2 - 0x273;
}

