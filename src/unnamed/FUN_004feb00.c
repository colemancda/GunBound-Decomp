/* FUN_004feb00 - 0x004feb00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

bool __thiscall
FUN_004feb00(char *param_1,int param_2,int param_3,sockaddr *param_4,undefined4 param_5)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  /* COALESCED (2026-07-18): same scattered-SHA-context fix as
   * EncodeHandshakeBlock - the context must be one contiguous 0x60 bytes
   * (local_19dc..local_1980 = offsets 0..0x5c). See Sha1Absorb.c. */
  uint shaCtx[0x18];
  undefined1 local_197c [0x20c];  /* schedule is 0x20c - see BuildSystemInfoBlob */
  undefined1 local_1774;
  undefined2 local_1770;
  undefined1 local_176e [16];
  char local_175e [16];
  undefined4 local_174e;
  undefined4 uStack_4;
  
  uStack_4 = 0x4feb0a;
  local_1774 = 0;
  cVar1 = FUN_004fcd80(local_176e,0x10);
  if (cVar1 == '\0') {
    return false;
  }
  _strncpy(local_175e,param_1,0x10);
  local_174e = param_5;
  iVar3 = ((int)(*(ushort *)(param_3 + 0xe) + 0x1f) >> 4) * 0x10;
  if (0x173a < iVar3 - 0x10U) {
    return false;
  }
  shaCtx[0] = 0x67452301;
  shaCtx[1] = 0xefcdab89;
  shaCtx[2] = 0x98badcfe;
  shaCtx[3] = 0x10325476;
  shaCtx[4] = 0xc3d2e1f0;
  shaCtx[5] = 0;            /* +0x14 bit count lo */
  shaCtx[6] = 0;            /* +0x18 bit count hi */
  shaCtx[0x17] = 0;         /* +0x5c partial byte count */
  /* DROPPED length arg (2026-07-18), same class as EncodeHandshakeBlock -
   * see Sha1Absorb.c. This is a P2P/UDP handshake path NOT exercised by the
   * ServerSelect->world-login route, so the lengths are best-effort from the
   * buffer semantics: (1) the 16-byte nonce in local_176e (FUN_004fcd80(..,
   * 0x10)); (2) strlen(param_1) - the key string this loop scans; (3) the
   * 4-byte &param_5 trailer. */
  Sha1Absorb((int)shaCtx,(byte *)local_176e,0x10);
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  Sha1Absorb((int)shaCtx,(byte *)param_1,(uint)(pcVar2 - param_1) - 1);
  Sha1Absorb((int)shaCtx,(byte *)&param_5,4);
  Sha1Final((int)shaCtx);
  /* RECOVERED, orig 0x4fec29-0x4fec39: key = ECX = the SHA-1 digest (shaCtx),
   * EDX=0x10, EDI=[esp+0x84] = local_197c (the schedule FUN_004fcd20 uses). */
  RijndaelSetKey((uint *)shaCtx,0x10,1,(uint *)local_197c);
  FUN_004fcd20(local_197c);
  uVar4 = iVar3 + 0x26;
  local_1770 = (undefined2)uVar4;
  iVar3 = sendto(*(SOCKET *)(param_2 + 0x288),(char *)&local_1770,uVar4 & 0xffff,0,param_4,0x10);
  return iVar3 != -1;
}

