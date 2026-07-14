/* ReadSpriteFrameRecord - 0x004f1520 in the original binary.
 *
 * PROMOTED (2026-07-14): reads one sprite frame's fixed header fields (a
 * handful of 1-byte and 4-byte fields at fixed offsets into the frame
 * object `frame`), then its pixel/mask payload buffers, from the XFS read
 * cursor `readState`. Sole caller LoadSpriteSet.c already holds both
 * (readState in EDI, the freshly-allocated frame object in ESI per orig
 * 0x408d5a/0x408ddb) but was calling this with zero arguments - promoted
 * to explicit parameters (same class as this file's other dropped-arg
 * fixes).
 *
 * DEEPER DROPPED-ARGUMENT BUG (2026-07-14): every one of this function's
 * ~15 ReadXFSEntryByte() calls was ALSO missing its 3rd argument (the byte
 * count). ReadXFSEntryByte's real calling convention (confirmed against
 * orig 0x4f1520-0x4f16e2's disassembly) passes count via EAX
 * (`mov eax,N; call 0x4f06c0`), loaded immediately before each call - not
 * a 3rd stack slot - so this file's raw port, calling through
 * functions.h's K&R-empty `uint ReadXFSEntryByte();` declaration with only
 * 2 arguments, read whatever garbage happened to be in EAX as the byte
 * count on every single call. For the two payload-buffer reads (into the
 * freshly `operator_new`'d buffers at frame+0x34/+0x38) that garbage count
 * could be enormous, causing ReadXFSEntryByte to write arbitrarily far
 * past the allocated buffer - a real heap-corruption bug (confirmed via a
 * targeted trace: the corruption manifested several allocations later, as
 * a crash deep inside a routine libc calloc/RtlAllocateHeap call, the
 * classic delayed-heap-corruption signature). Fixed by passing the real
 * count at all 15 call sites, each recovered from the disassembly's
 * `mov eax,N` immediately preceding that call:
 *   +0x18/+0x1b/+0x1a/+0x19: 1 byte each (note the non-sequential order -
 *     these are 4 distinct sub-byte fields, not a 4-byte run)
 *   +0x20/+0x24/+0x28/+0x2c/+0x30/+0x44/+0x48/+0x4c/+0x3c: 4 bytes each
 *   frame+0x34 (pixel buffer): count = the SAME adjusted size just used to
 *     operator_new() it (orig re-reads it back from frame+0x3c, which the
 *     adjustment step wrote in place - matches this file's own `uVar3`)
 *   frame+0x38 (mask buffer): count = the RAW size at frame+0x40 (orig
 *     reloads it un-rounded here, unlike the rounded-down value used for
 *     the operator_new() call just above - ported as-is, matching the
 *     original exactly, not "fixed" to be consistent)
 *   +0x3c (re-read after the CreateCompatibleDC-ish 0x4f08a0 helper): 1 byte
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-
 * verified beyond the above. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 ReadSpriteFrameRecord(void *readState, int frame)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  void *pvVar4;

  iVar2 = ReadXFSEntryByte(readState,(void *)(frame + 0x18),1);
  if ((((iVar2 == -2) || (iVar2 = ReadXFSEntryByte(readState,(void *)(frame + 0x1b),1), iVar2 == -2)) ||
      (iVar2 = ReadXFSEntryByte(readState,(void *)(frame + 0x1a),1), iVar2 == -2)) ||
     (((iVar2 = ReadXFSEntryByte(readState,(void *)(frame + 0x19),1), iVar2 == -2 ||
       (iVar2 = ReadXFSEntryByte(readState,(void *)(frame + 0x20),4), iVar2 == -2)) ||
      ((iVar2 = ReadXFSEntryByte(readState,(void *)(frame + 0x24),4), iVar2 == -2 ||
       ((iVar2 = ReadXFSEntryByte(readState,(void *)(frame + 0x28),4), iVar2 == -2 ||
        (iVar2 = ReadXFSEntryByte(readState,(void *)(frame + 0x2c),4), iVar2 == -2)))))))) {
    return 0xffffffff;
  }
  iVar2 = ReadXFSEntryByte(readState,(char *)(frame + 0x30),4);
  if ((iVar2 != -2) &&
     (((iVar2 = ReadXFSEntryByte(readState,(void *)(frame + 0x44),4), iVar2 != -2 &&
       (iVar2 = ReadXFSEntryByte(readState,(void *)(frame + 0x48),4), iVar2 != -2)) &&
      (iVar2 = ReadXFSEntryByte(readState,(void *)(frame + 0x4c),4), iVar2 != -2)))) {
    puVar1 = (uint *)(frame + 0x3c);
    iVar2 = ReadXFSEntryByte(readState,puVar1,4);
    if (iVar2 != -2) {
      uVar3 = *puVar1;
      if ((uVar3 & 1) != 0) {
        uVar3 = uVar3 + 1;
      }
      *puVar1 = uVar3;
      if ((*(int *)(frame + 4) == 60000) && (*(int *)(frame + 8) == 0)) {
        uVar3 = uVar3 * 2;
      }
      else {
        uVar3 = uVar3 & 0xfffffffe;
      }
      pvVar4 = operator_new(uVar3);
      *(void **)(frame + 0x34) = pvVar4;
      iVar2 = ReadXFSEntryByte(readState,pvVar4,uVar3);
      if (iVar2 != -2) {
        if (*(char *)(frame + 0x30) == '\0') {
          return 0;
        }
        iVar2 = ReadXFSEntryByte(readState,(uint *)(frame + 0x40),4);
        if (iVar2 != -2) {
          uVar3 = *(uint *)(frame + 0x40);
          pvVar4 = operator_new(uVar3 & 0xfffffffe);
          *(void **)(frame + 0x38) = pvVar4;
          iVar2 = ReadXFSEntryByte(readState,pvVar4,uVar3);
          if (iVar2 != -2) {
            return 0;
          }
        }
      }
    }
    return 0xffffffff;
  }
  return 0xffffffff;
}
