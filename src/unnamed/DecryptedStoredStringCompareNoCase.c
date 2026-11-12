/* DecryptedStoredStringCompareNoCase - 0x004fcdf0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004fcdf0 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: Same shape
 * as DecryptStoredStringTo (0x4fcd80): EAX is the crypto context,
 * ciphertext at +0x27c and length at +0x280 is decrypted into a stack
 * block by DecryptContextBuffer (0x4fce60), then __strnicmp(decrypted,
 * param_1, param_2) is returned; -1 when no ciphertext is stored or the
 * decrypt fails. Its two callers, both in CommP2PReceiveDatagram, compare
 * the 0x10 byte field of a received datagram against it and treat a non-
 * zero result as a mismatch. LIKELY: the compare is certain, what the
 * stored string is is inferred.
 */
#include "ghidra_types.h"
#include <malloc.h>



int DecryptedStoredStringCompareNoCase(undefined4 param_1,undefined4 param_2,int regEax)

{
  int iVar2;
  char *pBlock;
  
  if (*(int *)(regEax + 0x27c) != 0) {
    iVar2 = *(int *)(regEax + 0x280) + 0x10;
    iVar2 = (int)(iVar2 + (iVar2 >> 0x1f & 0xfU)) >> 4;
    /* Real alloca of iVar2 * 16 bytes (orig 0x4fce01-0x4fce23); see
     * DecryptStoredStringTo for what the raw stack-array form did wrong. */
    pBlock = (char *)_alloca(iVar2 * 0x10);
    if (pBlock != (char *)0x0) {
      /* RECOVERED (2026-07-19): EBX = the alloca'd output block, EDI =
       * regEax, this function's own crypto context. */
      if ((char)DecryptContextBuffer((int)pBlock,regEax) != '\0') {
        return __strnicmp(pBlock,(char *)param_1,(size_t)param_2);
      }
    }
  }
  return -1;
}
