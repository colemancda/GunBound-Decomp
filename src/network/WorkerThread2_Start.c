/* WorkerThread2_Start - 0x00415530 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00415530 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. The same member as WorkerThread_Start
 * (0x415500) over a second control block: it sets a running flag,
 * __beginthreads a proc thunk with the block as the argument, stores the
 * handle at block + 4 and clears the flag again if the thread did not
 * start, returning whether it began. The differences are the flag offset
 * (+0xc here, +0x10 there) and the thunk (0x4156c0 instead of 0x4156b0).
 * The layout is recorded for this block by globals.c (DAT_007a767c, 'same
 * shape as DAT_00e9c334 ... but the running flag is at +0xc here'), written
 * before this function was looked at, and its sole caller InitGame starts
 * it right after WorkerThread_Start. The subsystem the thread serves is not
 * known, so the name only says it is the second of the pair; the 2 is a
 * discriminator against the existing WorkerThread_* family, not a role.
 */
#include "ghidra_types.h"


/* Original passes ESI=&DAT_007a767c (a fixed global control block, orig
 * 0x40f39d) - Ghidra dropped it as unaff_ESI. Promoted to an explicit
 * parameter; the sole caller (InitGame.c) now passes it directly. */
bool WorkerThread2_Start(void *unaff_ESI)

{
  uintptr_t uVar1;

  *(undefined1 *)((int)unaff_ESI + 0xc) = 1;
  uVar1 = __beginthread(WorkerThread2ProcThunk,0,unaff_ESI);
  *(uintptr_t *)((int)unaff_ESI + 4) = uVar1;
  if (uVar1 == 0) {
    *(undefined1 *)((int)unaff_ESI + 0xc) = 0;
  }
  return uVar1 != 0;
}

