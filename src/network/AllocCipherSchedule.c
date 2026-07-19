/* AllocCipherSchedule - 0x004f6f10 in the original binary.
 *
 * Allocates one packet-cipher context: a 0x210-byte block holding the
 * Rijndael key schedule (0x00..0x207), the 2-bit cipher mode byte at
 * +0x208 (see RijndaelSetKey, which stores it at ctx[0x82]), and the
 * connection's packet-checksum base at +0x20c. EncodePacketBlocks reads
 * that trailing dword to build each block's tag
 * (tag = opcode + *(int *)(schedule + 0x20c)), so a context whose +0x20c
 * is not stamped produces packets the server rejects with a checksum
 * mismatch. InitConnectionObject builds the same layout inline for its
 * three connection objects, taking the base from DAT_0056dc30[index].
 *
 * Was FUN_004f6f10.
 *
 * RECOVERED (2026-07-18) from the original's 8 instructions at 0x4f6f10:
 *   1. The checksum base arrives in ESI (`mov [eax+0x20c], esi` at
 *      0x4f6f28) - a dropped register argument Ghidra emitted as an
 *      uninitialised `unaff_ESI`, so the port stamped +0x20c with garbage.
 *   2. The allocated pointer is the RETURN VALUE - it stays live in EAX
 *      from the `call operator new` at 0x4f6f15 through the bare `ret` at
 *      0x4f6f2e. Ghidra emitted a bare `return;`, which the port had
 *      turned into `return 0`, so the sole caller stored a null schedule.
 * Both are promoted to an explicit parameter / real return value here.
 *
 * The null-allocation path is a fault in the original too (0x4f6f2f
 * `xor eax,eax` then `mov [eax+0x20c],esi` dereferences 0x20c); it is
 * preserved verbatim rather than "fixed", to keep the port faithful.
 */
#include "ghidra_types.h"


void * AllocCipherSchedule(undefined4 checksumBase)

{
  void *pvVar1;

  pvVar1 = operator_new(0x210);
  if (pvVar1 != (void *)0x0) {
    *(undefined1 *)((int)pvVar1 + 0x208) = 0;
    *(undefined4 *)((int)pvVar1 + 0x20c) = checksumBase;
    return pvVar1;
  }
  uRam0000020c = checksumBase;
  return (void *)0x0;
}
