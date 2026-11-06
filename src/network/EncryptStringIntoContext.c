/* EncryptStringIntoContext - 0x005051e0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_005051e0 mean this function.)
 *
 * Evidence (HIGH, from the storage layout shared with the named
 * decryptor). EDX is a 0x284-byte crypto context: it receives a 16-byte
 * key schedule (RijndaelSetKey on a key built from four FUN_00504d80
 * calls, orig 0x5051f7-0x505211), then a realloc'd buffer at +0x27c holding
 * the ciphertext (EncodeCipherBlock per 16-byte block; the last block is
 * strncpy'd into a zero-padded local first) and the plaintext length at
 * +0x280. Those are exactly the cells DecryptStoredStringTo (0x4fcd80)
 * reads: buffer +0x27c, length +0x280, same context. The callers
 * CommP2POwnerConnect (contexts +0x1b20 and +0x1da4, 0x284 apart like the
 * two contexts CommP2POwner_ProcessPacket decrypts) and CreateBoundSocket
 * feed it a NUL-terminated string (length = end - start - 1). "String"
 * rests on that caller use; what the strings are is not established.
 */
/* DROPPED-REGISTER FIX (2026-07-19): EAX (the source plaintext pointer) is
 * an incoming register argument - orig 0x5051eb `mov [esp+0x10],eax` stashes
 * it at entry and both cipher calls read it back. Promoted to an explicit
 * trailing parameter. Both EncodeCipherBlock calls were also passing 2 of 4
 * arguments with the source omitted; recovered below. */
#include "ghidra_types.h"


void __fastcall EncryptStringIntoContext(int param_1,int param_2,char *src)

{
  char *in_EAX = src;
  undefined4 uVar1;
  void *pvVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  char *local_14;
  char local_10 [16];
  
  uVar4 = 0;
  do {
    uVar1 = FUN_00504d80();
    *(undefined4 *)(local_10 + uVar4 * 4) = uVar1;
    uVar4 = uVar4 + 1;
  } while (uVar4 < 4);
  /* RECOVERED, orig 0x5051e7-0x505211: key = ECX = local_10 (the 16 bytes
   * just built above), EDX=0x10, EDI = EDX-at-entry = param_2 - the same
   * crypto context the EncodeCipherBlock calls below use. */
  RijndaelSetKey((uint *)local_10,0x10,3,(uint *)param_2);
  iVar5 = (int)(param_1 + 0x10 + (param_1 + 0x10 >> 0x1f & 0xfU)) >> 4;
  pvVar2 = _realloc(*(void **)(param_2 + 0x27c),iVar5 << 4);
  iVar3 = 0;
  *(int *)(param_2 + 0x280) = param_1;
  *(void **)(param_2 + 0x27c) = pvVar2;
  local_14 = in_EAX;
  if (0 < iVar5) {
    do {
      if (iVar3 == iVar5 + -1) {
        _strncpy(local_10,local_14,0x10);
        /* RECOVERED, orig 0x50526a-0x50526e: `lea edx,[esp+0x28]` (EDX = the
         * strncpy'd 16-byte tail block) / `push edi` (schedule) / `push ebx`
         * (output). The port dropped the source entirely. */
        EncodeCipherBlock(0,(uint *)local_10,(uint *)pvVar2,param_2);
      }
      else {
        /* RECOVERED, orig 0x505278-0x50527e: `mov edx,[esp+0x10]` (EDX = the
         * current source block) / `push edi` (schedule) / `push ebx` (output). */
        EncodeCipherBlock(0,(uint *)local_14,(uint *)pvVar2,param_2);
      }
      iVar3 = iVar3 + 1;
      local_14 = local_14 + 0x10;
      pvVar2 = (void *)((int)pvVar2 + 0x10);
    } while (iVar3 < iVar5);
  }
  return;
}

