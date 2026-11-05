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


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */
/* WARNING: Type propagation algorithm not settling */

int DecryptedStoredStringCompareNoCase(undefined4 param_1,undefined4 param_2,int regEax)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffffff4;
  char cVar1;
  int iVar2;
  size_t asStack_1c [4];
  
  if (*(int *)(regEax + 0x27c) != 0) {
    iVar2 = *(int *)(regEax + 0x280) + 0x10;
    iVar2 = (int)(iVar2 + (iVar2 >> 0x1f & 0xfU)) >> 4;
    asStack_1c[3] = 0x4fce21;
    if (&stack0xfffffff4 != (undefined1 *)(iVar2 * 0x10)) {
      asStack_1c[iVar2 * -4 + 3] = 0x4fce2c;
      /* RECOVERED (2026-07-19): EBX = the alloca'd output block (orig
       * `mov ebx,esp` just before the call), EDI = regEax, this function's
       * own crypto context. */
      cVar1 = (char)FUN_004fce60((int)(&stack0xfffffff4 + iVar2 * -0x10),regEax);
      if (cVar1 != '\0') {
        asStack_1c[iVar2 * -4 + 3] = param_2;
        asStack_1c[iVar2 * -4 + 2] = param_1;
        asStack_1c[iVar2 * 0xfffffffcU + 1] = (size_t)(&stack0xfffffff4 + iVar2 * -0x10);
        asStack_1c[iVar2 * -4] = 0x4fce3e;
        iVar2 = __strnicmp((char *)asStack_1c[iVar2 * 0xfffffffcU + 1],
                           (char *)asStack_1c[iVar2 * -4 + 2],asStack_1c[iVar2 * -4 + 3]);
        return iVar2;
      }
    }
  }
  return -1;
}

