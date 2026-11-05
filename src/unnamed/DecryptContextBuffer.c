/* DecryptContextBuffer - 0x004fce60 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004fce60 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: Called only
 * by DecryptStoredStringTo (0x4fcd80) and
 * DecryptedStoredStringCompareNoCase (0x4fcdf0), both of which allocate an
 * output block of the stored length rounded up to 16 and pass it in EBX
 * with the context in EDI. The loop walks the ciphertext at ctx+0x27c in
 * 16 byte steps (up to ctx+0x280) calling DecodeCipherBlock with the
 * context as the key schedule, returning 0 as soon as one block fails and
 * 1 otherwise. LIKELY: the cipher direction is taken from
 * DecodeCipherBlock's existing name; the bound is length + 1 rather than a
 * rounded block count.
 */
/* DROPPED-REGISTER FIX (2026-07-19): EBX (the output base) and EDI (the
 * crypto context holding the ciphertext buffer at +0x27c and its length at
 * +0x280) are incoming register arguments - both are read before any write
 * (orig 0x4fce60 `mov eax,[edi+0x280]`, 0x4fce76 `lea ecx,[esi+ebx]`).
 * Promoted to explicit parameters. */
#include "ghidra_types.h"


undefined4 DecryptContextBuffer(int outBase,int ctx)

{
  short sVar1;
  int unaff_EBX = outBase;
  int iVar2;
  int unaff_EDI = ctx;
  
  iVar2 = 0;
  if (0 < *(int *)(unaff_EDI + 0x280) + 1) {
    do {
      /* RECOVERED (2026-07-19), orig 0x4fce70-0x4fce7d:
       *   mov edx,[edi+0x27c] / add edx,esi   ; EDX = SOURCE (ctx buffer + off)
       *   lea ecx,[esi+ebx]                   ; ECX = OUTPUT (outBase + off)
       *   push edi / push ecx / call 0x4f5e10 ; schedule = ctx, output = ECX
       * The port passed only the output and dropped the SOURCE pointer, so it
       * decrypted whatever the dead ECX slot happened to hold. Same ABI as
       * every other cipher-block call site: (dead, source, output, schedule). */
      sVar1 = (short)DecodeCipherBlock(0,(uint *)(*(int *)(unaff_EDI + 0x27c) + iVar2),
                                       (uint *)(iVar2 + unaff_EBX),unaff_EDI);
      if (sVar1 != 1) {
        return 0;
      }
      iVar2 = iVar2 + 0x10;
    } while (iVar2 < *(int *)(unaff_EDI + 0x280) + 1);
  }
  return 1;
}

