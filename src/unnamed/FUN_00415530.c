/* FUN_00415530 - 0x00415530 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Original passes ESI=&DAT_007a767c (a fixed global control block, orig
 * 0x40f39d) - Ghidra dropped it as unaff_ESI. Promoted to an explicit
 * parameter; the sole caller (InitGame.c) now passes it directly. */
bool FUN_00415530(void *unaff_ESI)

{
  uintptr_t uVar1;

  *(undefined1 *)((int)unaff_ESI + 0xc) = 1;
  uVar1 = __beginthread(FUN_004156c0,0,unaff_ESI);
  *(uintptr_t *)((int)unaff_ESI + 4) = uVar1;
  if (uVar1 == 0) {
    *(undefined1 *)((int)unaff_ESI + 0xc) = 0;
  }
  return uVar1 != 0;
}

