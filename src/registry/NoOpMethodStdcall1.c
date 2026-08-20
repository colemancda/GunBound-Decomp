/* NoOpMethodStdcall1 - 0x004038b0 in the original binary.
 *
 * A no-op vtable slot filler that takes one stack argument and cleans it up
 * itself (`ret 4`), unlike the plain-ret NoOpMethod (0x429800).  The two are
 * NOT interchangeable: getting the pop wrong unbalances the caller's stack.
 * Used as the "refill"/tick no-op for DirectSound streaming objects that
 * aren't yet bound to a real channel (see PTR_LAB_005574e0/e8/cc's slot 0 in
 * globals.c).
 *
 * DISASM (2026-08-19): the whole function is the single instruction `ret 4`;
 * 0x4038b3 onward is int3 padding.  Ghidra never carved it - it is reachable
 * only through vtables, and a vtable-reference scan finds 14 of them, wider
 * than the three sound tables globals.c currently spells out.
 *
 * OPEN - CALLING CONVENTION: `ret 4` means ECX=this plus ONE STACK argument,
 * which in this tree is spelled with the __fastcall+dummy-EDX idiom
 * (see src/README.md).  The signature below instead puts the argument in EDX,
 * so MSVC compiles it to `ret 0`.  That is self-consistent as long as every
 * dispatch site agrees - and functions.h declares it with an EMPTY parameter
 * list, so nothing is checked.  Left alone deliberately: the body is a no-op,
 * so the only thing at stake is stack balance, and the fix has to be made at
 * the same time as the dispatch sites, which have not been traced yet.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall NoOpMethodStdcall1(void *thisPtr, undefined4 param_1)

{
  (void)thisPtr;
  (void)param_1;
  return;
}
