/* EncodeHandshakeBlock - 0x004f6f40 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REGISTER FIX (2026-07-17): `unaff_ESI` and `in_EAX` were
 * dropped-register arguments, not real Ghidra artifacts - confirmed via
 * disassembly that the sole caller (AppendEncodedBlock, 0x4d2570) loads
 * two of its own genuine stack parameters into ESI and EAX and forwards
 * them here unclobbered (orig 0x4d257a `mov esi,[esp+0x28]`, 0x4d2596
 * `mov eax,[esp+0x40]`, both live at the 0x4d259a call). They are the
 * login handshake's credential buffers: `credKey` (ESI) is scanned as a
 * <=16-byte string and strncpy'd into the cipher block, `credStr` (EAX)
 * as a null-terminated string; both are SHA1-absorbed before
 * EncodeCipherBlock. Promoted to explicit trailing parameters and
 * threaded through AppendEncodedBlock from the 0x1001 handler in
 * State02_ServerSelect_ProcessPacket (which fills them via
 * BuildSystemInfoBlob). Before this fix the recompiled binary read ESI/
 * EAX uninitialised and faulted at +0x15 scanning a garbage pointer.
 *
 * param_1/param_2 remain unused by this function (the disassembly never
 * references them); the caller still supplies them for ABI fidelity.
 */
#include "ghidra_types.h"


uint EncodeHandshakeBlock(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,
                         char *credKey,char *credStr)

{
  char cVar1;
  int iVar2;
  byte bVar3;
  short sVar4;
  char *in_EAX;
  uint uVar5;
  char *unaff_ESI;
  /* COALESCED (2026-07-18): the SHA-1 context MUST be ONE contiguous 0x60-byte
   * block - Sha1Absorb/Sha1Final index it at +0x14/+0x18 (bit count), +0x1c
   * (the 0x40-byte block buffer) and +0x5c (partial byte count). Ghidra split
   * the original's single stack context into separate named locals
   * (local_28c..local_230 - the names ARE the real stack offsets, and
   * 0x28c-0x230 = 0x5c exactly), but MSVC scatters separate locals, so
   * &local_28c+0x5c was NOT the zeroed partial count - it was uninitialised
   * stack. That made Sha1Absorb's block index explode (eax=0x1f7d7432) into a
   * wild write, faulting right after the dropped-length fix. */
  uint shaCtx[0x18];
  char local_22c [16];
  undefined4 local_21c;
  undefined1 local_20c [520];
  undefined1 local_4;
  
  unaff_ESI = credKey;
  in_EAX = credStr;
  iVar2 = param_4;
  shaCtx[0] = 0x67452301;   /* +0x00 H0 */
  shaCtx[1] = 0xefcdab89;   /* +0x04 H1 */
  shaCtx[2] = 0x98badcfe;   /* +0x08 H2 */
  shaCtx[3] = 0x10325476;   /* +0x0c H3 */
  shaCtx[4] = 0xc3d2e1f0;   /* +0x10 H4 */
  shaCtx[5] = 0;            /* +0x14 bit count lo */
  shaCtx[6] = 0;            /* +0x18 bit count hi */
  shaCtx[0x17] = 0;         /* +0x5c partial byte count */
  uVar5 = 0;
  do {
    if (unaff_ESI[uVar5] == '\0') break;
    bVar3 = (char)uVar5 + 1;
    uVar5 = (uint)bVar3;
  } while (bVar3 < 0x10);
  /* DROPPED ARGS (2026-07-18): the original passes each Sha1Absorb its
   * buffer (ESI/stack) and byte count (EAX); Ghidra dropped both on the
   * first two calls and the length on the third. Recovered from orig
   * 0x4f6fa0-0x4f6fdc: (1) credKey, its capped-16 length uVar5; (2) credStr,
   * its strlen; (3) &param_3 (the 4-byte trailer), length 4. See Sha1Absorb.c. */
  Sha1Absorb((int)shaCtx,(byte *)unaff_ESI,uVar5);
  {
    char *credStrStart = in_EAX;
    do {
      cVar1 = *in_EAX;
      in_EAX = in_EAX + 1;
    } while (cVar1 != '\0');
    Sha1Absorb((int)shaCtx,(byte *)credStrStart,(uint)(in_EAX - credStrStart) - 1);
  }
  Sha1Absorb((int)shaCtx,(byte *)&param_3,4);
  Sha1Final((int)shaCtx);
  uVar5 = RijndaelSetKey(3);
  if ((short)uVar5 == 1) {
    local_4 = 0;
    RijndaelSetKey(1);
    _strncpy(local_22c,unaff_ESI,0x10);
    local_21c = param_3;
    sVar4 = EncodeCipherBlock(iVar2,local_20c);
    if ((sVar4 == 1) && (sVar4 = EncodeCipherBlock(iVar2 + 0x10,local_20c), sVar4 == 1)) {
      return 1;
    }
    return 0;
  }
  return uVar5 & 0xffffff00;
}

