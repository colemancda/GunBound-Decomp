/* ScrambleChecksumGuardBytes - 0x0040a240 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * REGISTER ARGUMENTS IDENTIFIED (2026-08-20) - NOT SWEPT, and the reason is
 * worth stating because the site count makes it look like the obvious target.
 * All 1070 direct call sites were scanned:
 *     EBX  `mov ebx, 0x79376c` at ALL 1070 - i.e. &DAT_0079376c, and the body
 *          dereferences it (`*unaff_EBX`), so it is a POINTER TO the guard
 *          buffer base rather than the buffer
 *     EAX  a caller local at every site, no uniformity at all: 277 do
 *          `mov eax,edi`, the rest come from a dozen different stack slots
 * and the body is `buf[*EBX + EAX*0x10 + i] = rand()` for i in 0..0xf.
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


void ScrambleChecksumGuardBytes(void)

{
  int in_EAX;
  int iVar1;
  int *unaff_EBX;
  int iVar2;
  
  iVar2 = 0;
  do {
    iVar1 = _rand();
    *(char *)(*unaff_EBX + in_EAX * 0x10 + iVar2) = (char)iVar1;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x10);
  return;
}

