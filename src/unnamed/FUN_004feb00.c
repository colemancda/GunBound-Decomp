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
  undefined4 local_19dc;
  undefined4 local_19d8;
  undefined4 local_19d4;
  undefined4 local_19d0;
  undefined4 local_19cc;
  undefined4 local_19c8;
  undefined4 local_19c4;
  undefined4 local_1980;
  undefined1 local_197c [520];
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
  local_19dc = 0x67452301;
  local_19d8 = 0xefcdab89;
  local_19d4 = 0x98badcfe;
  local_19d0 = 0x10325476;
  local_19cc = 0xc3d2e1f0;
  local_19c8 = 0;
  local_19c4 = 0;
  local_1980 = 0;
  /* DROPPED length arg (2026-07-18), same class as EncodeHandshakeBlock -
   * see Sha1Absorb.c. This is a P2P/UDP handshake path NOT exercised by the
   * ServerSelect->world-login route, so the lengths are best-effort from the
   * buffer semantics: (1) the 16-byte nonce in local_176e (FUN_004fcd80(..,
   * 0x10)); (2) strlen(param_1) - the key string this loop scans; (3) the
   * 4-byte &param_5 trailer. */
  Sha1Absorb((int)&local_19dc,(byte *)local_176e,0x10);
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  Sha1Absorb((int)&local_19dc,(byte *)param_1,(uint)(pcVar2 - param_1) - 1);
  Sha1Absorb((int)&local_19dc,(byte *)&param_5,4);
  Sha1Final();
  RijndaelSetKey(1);
  FUN_004fcd20(local_197c);
  uVar4 = iVar3 + 0x26;
  local_1770 = (undefined2)uVar4;
  iVar3 = sendto(*(SOCKET *)(param_2 + 0x288),(char *)&local_1770,uVar4 & 0xffff,0,param_4,0x10);
  return iVar3 != -1;
}

