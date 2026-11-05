/* RefillSoundStreamBuffer - 0x004eec70 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004eec70 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: EBX is a
 * streaming sound object (DecodeSoundBufferChunk's param_1, whose other
 * fields +0x38 / +0x54 / +0xa4 it also uses). Called three times from
 * DecodeSoundBufferChunk, each time as the gate before consuming more
 * input from the stream, and its result (non-zero = more data) controls
 * whether decoding continues. It clamps the consumed offset at +0xa4 to 0,
 * and when that is below the buffered length +0xa0 moves the unconsumed
 * remainder to the front of the buffer +0x98 (memmove through +0x9c), then
 * pulls more bytes in with ReadXFSEntryByte(stream +0x50, buffer +
 * offset); on EOF (-1) it zeroes the length +0xa0 and returns 0, otherwise
 * it advances +0xa4 and resets the read pointer +0x9c to the buffer start.
 * LIKELY: the roles of +0x9c/+0xa0/+0xa4 are read from this and its single
 * caller.
 */
#include "ghidra_types.h"


undefined4 RefillSoundStreamBuffer(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int unaff_EBX;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  if (*(int *)(unaff_EBX + 0xa4) < 0) {
    *(undefined4 *)(unaff_EBX + 0xa4) = 0;
  }
  uVar2 = *(uint *)(unaff_EBX + 0xa4);
  if ((int)uVar2 < *(int *)(unaff_EBX + 0xa0)) {
    uVar2 = ((int)uVar2 < 0) - 1 & uVar2;
    puVar4 = *(undefined4 **)(unaff_EBX + 0x9c);
    puVar5 = *(undefined4 **)(unaff_EBX + 0x98);
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
    iVar1 = ReadXFSEntryByte(*(undefined4 *)(unaff_EBX + 0x50),
                             *(int *)(unaff_EBX + 0x98) + *(int *)(unaff_EBX + 0xa4));
    if (iVar1 == -1) {
      *(undefined4 *)(unaff_EBX + 0xa0) = 0;
      return 0;
    }
    *(int *)(unaff_EBX + 0xa4) = *(int *)(unaff_EBX + 0xa4) + iVar1;
    *(undefined4 *)(unaff_EBX + 0x9c) = *(undefined4 *)(unaff_EBX + 0x98);
  }
  return 1;
}

