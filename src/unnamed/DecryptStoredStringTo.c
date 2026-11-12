/* DecryptStoredStringTo - 0x004fcd80 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004fcd80 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: EAX is a
 * 0x284 byte crypto context (see the DROPPED-REGISTER note) holding a
 * ciphertext buffer at +0x27c and its length at +0x280. The body allocas
 * the rounded-up length on the stack, decrypts into it with
 * DecryptContextBuffer (0x4fce60, the 16 byte block loop over
 * DecodeCipherBlock) and on success strncpy's n bytes to the caller
 * buffer, returning 1, or 0 when no ciphertext is stored. The four callers
 * are in the P2P datagram path (CommP2POnKeepAliveTimer,
 * CommP2POwner_ProcessPacket x3, SendEncryptedP2PDatagram,
 * CommP2PReceiveDatagram); they pass a 0x10, 0x11 or 0x15 byte destination
 * and length, and SendEncryptedP2PDatagram's header calls the 0x10 byte
 * result a nonce. Its sibling DecryptedStoredStringCompareNoCase
 * (0x4fcdf0) is the same decrypt followed by __strnicmp. LIKELY: the
 * plaintext is a string by the strncpy/strnicmp use, but what the stored
 * value is beyond a 16 byte nonce-like block is not shown.
 *
 * DROPPED-REGISTER FIX (2026-08-27): EAX is an incoming register
 * argument, the crypto/session context. Orig 0x4fcd85 `mov edi,eax` is
 * its first use and precedes any write, and the body then reads
 * *(edi+0x27c) (the ciphertext buffer) and *(edi+0x280) (its length)
 * before handing EDI on to FUN_004fce60. The callee's `ret 8` matches
 * the two declared stack parameters, so this is a clean APPEND, not a
 * re-slot. Promoted to a trailing regEax parameter; every one of the 6
 * call sites passes the base of a 0x284-byte context object. The size
 * comes from CommP2POwner_ProcessPacket, whose two contexts at param_1+0x182c and
 * param_1+0x1ab0 are exactly 0x284 apart, and is corroborated by the
 * three callers that keep a SOCKET in the ENCLOSING object immediately
 * past the context, at ctx+0x284: param_2+0x288 in SendEncryptedP2PDatagram and
 * param_1[0xa2] in CommP2PReceiveDatagram / CommP2POnKeepAliveTimer, all
 * three with ctx = base+4. Sibling FUN_004fcdf0 has the identical
 * EAX-is-the-context shape and was fixed the same way.
 */
#include "ghidra_types.h"
#include <malloc.h>



undefined4 DecryptStoredStringTo(undefined4 param_1,undefined4 param_2,int regEax)

{
  int in_EAX = regEax;
  int iVar2;
  char *pBlock;
  
  if (*(int *)(in_EAX + 0x27c) != 0) {
    iVar2 = *(int *)(in_EAX + 0x280) + 0x10;
    iVar2 = (int)(iVar2 + (iVar2 >> 0x1f & 0xfU)) >> 4;
    /* The original (0x4fcd91-0x4fcdb3) allocas iVar2 * 16 bytes (the size
     * rounded to 16, then to 4) and keeps the block in EBX. The raw port
     * wrote the call's return addresses into a four-word local array at
     * negative indices and took a block address from the address of a one
     * byte local, so the decrypt wrote below the frame. A real alloca is
     * what the original does. */
    pBlock = (char *)_alloca(iVar2 * 0x10);
    if (pBlock != (char *)0x0) {
      /* RECOVERED (2026-07-19): EBX = the alloca'd output block (orig
       * `mov ebx,esp` just before the call), EDI = in_EAX, this function's
       * own crypto context. */
      if ((char)DecryptContextBuffer((int)pBlock,in_EAX) != '\0') {
        _strncpy((char *)param_1,pBlock,(size_t)param_2);
        return 1;
      }
    }
  }
  return 0;
}
