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
  undefined4 local_28c;
  undefined4 local_288;
  undefined4 local_284;
  undefined4 local_280;
  undefined4 local_27c;
  undefined4 local_278;
  undefined4 local_274;
  undefined4 local_230;
  char local_22c [16];
  undefined4 local_21c;
  undefined1 local_20c [520];
  undefined1 local_4;
  
  unaff_ESI = credKey;
  in_EAX = credStr;
  iVar2 = param_4;
  local_28c = 0x67452301;
  local_288 = 0xefcdab89;
  local_284 = 0x98badcfe;
  local_280 = 0x10325476;
  local_27c = 0xc3d2e1f0;
  local_278 = 0;
  local_274 = 0;
  local_230 = 0;
  uVar5 = 0;
  do {
    if (unaff_ESI[uVar5] == '\0') break;
    bVar3 = (char)uVar5 + 1;
    uVar5 = (uint)bVar3;
  } while (bVar3 < 0x10);
  Sha1Absorb(&local_28c);
  do {
    cVar1 = *in_EAX;
    in_EAX = in_EAX + 1;
  } while (cVar1 != '\0');
  Sha1Absorb(&local_28c);
  Sha1Absorb(&local_28c,&param_3);
  Sha1Final();
  uVar5 = FUN_004f48b0(3);
  if ((short)uVar5 == 1) {
    local_4 = 0;
    FUN_004f48b0(1);
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

