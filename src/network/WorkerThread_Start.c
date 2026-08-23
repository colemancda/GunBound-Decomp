/* WorkerThread_Start - 0x00415500 in the original binary.
 *
 * Starts a worker thread for a control block, and rolls back on failure.
 *
 * Sets the running flag at +0x10, calls __beginthread with
 * WorkerThreadProcThunk and the block as the thread argument, stores the
 * resulting handle at +4, and clears the flag again if the start failed.
 * Returns whether the thread began.
 *
 * The offsets are not read off this function alone: globals.c already records
 * this exact layout -- "+4 thread handle (uintptr_t), +8/+0xc two wait
 * handles, +0x10 running flag" -- for the block these three functions share.
 */
#include "ghidra_types.h"


/* Original passes ESI=&DAT_00e9c334 (a fixed global control block, orig
 * 0x40f38e) - Ghidra dropped it as unaff_ESI. Promoted to an explicit
 * parameter; the sole caller (InitGame.c) now passes it directly. */
bool WorkerThread_Start(void *unaff_ESI)

{
  uintptr_t uVar1;

  *(undefined1 *)((int)unaff_ESI + 0x10) = 1;
  uVar1 = __beginthread(WorkerThreadProcThunk,0,unaff_ESI);
  *(uintptr_t *)((int)unaff_ESI + 4) = uVar1;
  if (uVar1 == 0) {
    *(undefined1 *)((int)unaff_ESI + 0x10) = 0;
  }
  return uVar1 != 0;
}

