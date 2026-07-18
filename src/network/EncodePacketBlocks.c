/* EncodePacketBlocks - 0x004f70b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* RECOVERED (2026-07-18): the original is
 *   EncodePacketBlocks(input=ECX, inputLen=EAX, schedule, opcode, output, capacity)
 * - Ghidra dropped BOTH register args (ECX/`unaff_EBX`, and EAX/`in_EAX`), and
 * functions.h declared it with an EMPTY parameter list on top of that. Without
 * the input pointer it encrypted an UNINITIALISED 0x5000-byte scratch buffer,
 * which EncodePacketBody then copied back over the real payload - that is why
 * the login packet reached the world server with a correct header (len 0x66,
 * opcode 0x1010) and an ALL-ZERO body, and why the server always decoded the
 * same constant garbage username.
 *
 * Per 16-byte cipher block the original stages [4-byte tag][12 input bytes]
 * (orig 0x4f7100-0x4f711c: the three input dwords land at block+4/+8/+0xc and
 * the tag at block+0), where tag = opcode + *(int *)(schedule + 0x20c) - a
 * per-connection sequence counter living just past the key schedule. Input
 * advances 0xc and output 0x10 per block (0x4f712f/0x4f7132). */
undefined4 EncodePacketBlocks(byte *input,int inputLen,int schedule,ushort opcode,int output,
                             int capacity)

{
  short sVar1;
  int iVar2;
  int iVar3;
  uint blk [4];

  iVar2 = inputLen / 0xc;
  if ((inputLen % 0xc == 0) && (iVar2 * 0x10 <= capacity)) {
    iVar3 = 0;
    if (0 < iVar2) {
      do {
        blk[0] = (uint)opcode + *(int *)(schedule + 0x20c);   /* tag  */
        blk[1] = *(uint *)(input);
        blk[2] = *(uint *)(input + 4);
        blk[3] = *(uint *)(input + 8);
        sVar1 = (short)EncodeCipherBlock(0,blk,(uint *)output,schedule);
        if (sVar1 != 1) {
          return 0;
        }
        iVar3 = iVar3 + 1;
        input = input + 0xc;
        output = output + 0x10;
      } while (iVar3 < iVar2);
    }
    return 1;
  }
  return 0;
}
