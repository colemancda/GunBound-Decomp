/* DecodeCipherBlocks - 0x004fcd50 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-11-04), CERTAIN. Runs DecodeCipherBlock (0x4f5e10) over
 * count 16-byte blocks, source (EDX) to destination (ECX), advancing both
 * by 0x10 with one key schedule - the mirror of EncodeCipherBlocks
 * (0x4fcd20). Caller evidence: CommP2PReceiveDatagram builds the schedule
 * with RijndaelSetKey in mode 2 (the encrypt side,
 * SendEncryptedP2PDatagram, uses mode 1 for the same key derivation,
 * Sha1Final over nonce and id) and then calls this on the datagram body
 * past the 4-byte nonce, with the block count it has computed.
 *
 * RECOVERED (2026-07-19): byte-for-byte the same shape as FUN_004fcd20 but
 * calling DecodeCipherBlock (0x4f5e10) instead. Ghidra dropped the EAX block
 * count and the EDX SOURCE pointer, collapsing source and destination:
 *   0x4fcd52 mov ebp,[esp+0xc]   ; arg1 = SCHEDULE
 *   0x4fcd57 mov ebx,eax         ; EAX = block COUNT
 *   0x4fcd5c mov edi,ecx         ; ECX = DEST   (advances 0x10 @0x4fcd71)
 *   0x4fcd5e mov esi,edx         ; EDX = SOURCE (advances 0x10 @0x4fcd6e)
 *   loop: push ebp / push edi / mov edx,esi / call 0x4f5e10
 */
#include "ghidra_types.h"


void __thiscall DecodeCipherBlocks(int param_1,int schedule,uint *source,int count)

{
  if (0 < count) {
    do {
      DecodeCipherBlock(0,source,(uint *)param_1,schedule);
      param_1 = param_1 + 0x10;
      source = source + 4;      /* 4 dwords = 0x10 bytes */
      count = count + -1;
    } while (count != 0);
  }
  return;
}
