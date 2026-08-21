/* ScrambleChecksumGuardBytes - 0x0040a240 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * BOTH REGISTER ARGUMENTS RECOVERED (2026-08-21), 1001 of 1123 call sites.
 * The signature is (int slot, int *guardTable) and the body is now
 * `*(char *)(*guardTable + slot * 0x10 + i) = rand()` for i in 0..0xf - i.e.
 * CORRECT, not merely better: the port used to dereference an uninitialised
 * pointer and write 16 bytes through it.
 *
 * HOW THE SLOT WAS RECOVERED, after I had written it off (see the retracted
 * note below).  At 1052 of the 1070 direct call sites the disassembly is
 * `test <reg>,<reg>` plus a conditional jump immediately before the call, and
 * the C keeps the tested value one line up:
 *
 *     if (param_1[0x33f1] != 0) {
 *         ScrambleChecksumGuardBytes();
 *         TreeLowerBound(local_14);
 *     }
 *
 * so the argument is the enclosing if's subject - available locally at every
 * site, with no pairing, no per-site disassembly and no frame calibration.
 * 0x33f1 * 4 = 0xcfc4 matches that site's `mov edi,[esi+0xcfc4]` exactly.
 * Extract the condition with BALANCED PARENS: a regex cannot span
 * `if ((*(int *)(local_454 + 0x14)) != 0)` and silently misses 44% of them.
 *
 * Corroboration that does not depend on the rule: at 332 object-relative
 * sites the offset in the C expression equals the offset of the load feeding
 * that site's test.  Watch which register that load targets - it is usually
 * NOT eax (`mov edi,[esi+off]` then `mov eax,edi`), so a check looking only
 * for `mov eax` reports zero matches.  And src/cxx/Mobile.cpp now reads
 * `ScrambleChecksumGuardBytes(g454.tableHandle, &DAT_0079376c)`, where
 * `tableHandle` is a field name an earlier session picked independently.
 *
 * RETRACTED (2026-08-20): the note that used to stand here argued this
 * function was not worth sweeping, because EBX is the literal 0x79376c at all
 * 1070 sites while EAX is a caller local at every one, so fixing EBX alone
 * would only move the wild write from a garbage base to a real base at a
 * garbage offset.  The measurement was right and the conclusion was wrong:
 * EAX has no uniform SOURCE EXPRESSION but a perfectly uniform STRUCTURAL
 * ROLE, which cost nothing to check and was never checked - Mobile.cpp's own
 * header had already written the pattern down.  A register whose callers all
 * compute it differently is not the same thing as a register that cannot be
 * recovered.
 *
 * 122 sites remain bare: 9 have no enclosing if, the rest use
 * pointer-comparison (`p != (byte *)0x0`) or compound conditions.
 *
 * So the port currently DEREFERENCES AN UNINITIALISED POINTER and writes 16
 * bytes through it.  Fixing EBX alone - which is the part that would sweep
 * mechanically across all 1070 sites - does NOT make that write safe, because
 * the offset EAX*0x10 stays garbage; it only moves the wild write from a
 * garbage base to a real base at a garbage offset.  1070 edits for no change
 * in behaviour and 1070 chances to introduce an error is a bad trade, so the
 * EBX half is deliberately left until EAX can be recovered with it.
 */
#include "ghidra_types.h"


void ScrambleChecksumGuardBytes(int slot,int *guardTable)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    iVar1 = _rand();
    *(char *)(*guardTable + slot * 0x10 + iVar2) = (char)iVar1;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x10);
  return;
}

