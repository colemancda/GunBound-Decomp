/* FUN_004ea6e0 - 0x004ea6e0 in the original binary.
 *
 * The LZHUF DecodePosition, raw-port side (src/lzhuf/DecodePosition.c
 * is the clean reimplementation of this same address). DROPPED-REG FIX
 * (2026-08-31): the context arrives in ESI, promoted to regEsi, and is
 * passed on to GetByte/GetBit (EAX). Its only binary caller is
 * DecodeLZHUFBlock (0x4eaba0) at 0x4eac56 - no raw C caller exists.
 * The d_code/d_len lookups now index the verified 256-byte tables in
 * src/lzhuf/lzhuf_tables.c instead of the one-byte DAT_0056dd30/
 * DAT_0056de30 scalars this port used to overrun (same data, right
 * extent - see that file's transcription-bug history note).
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"
#include "../lzhuf/lzhuf_internal.h"


uint FUN_004ea6e0(int regEsi)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = FUN_004ea1b0(regEsi);
  bVar1 = lzhuf_d_code[uVar2 & 0xffff];
  for (iVar3 = (byte)lzhuf_d_len[uVar2 & 0xffff] - 2; iVar3 != 0; iVar3 = iVar3 + -1) {
    uVar2 = uVar2 * 2;
    if (*(char *)(regEsi + 0xf6b2) == '\0') {
      iVar4 = FUN_004ea120(regEsi);
      uVar2 = uVar2 + iVar4;
    }
    else {
      *(char *)(regEsi + 0xf6b2) = *(char *)(regEsi + 0xf6b2) + -1;
      if (*(short *)(regEsi + 0xf6b0) < 0) {
        uVar2 = uVar2 + 1;
      }
      *(short *)(regEsi + 0xf6b0) = *(short *)(regEsi + 0xf6b0) * 2;
    }
  }
  return uVar2 & 0x3f | (uint)bVar1 << 6;
}

