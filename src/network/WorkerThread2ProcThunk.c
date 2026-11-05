/* WorkerThread2ProcThunk - 0x004156c0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004156c0 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. __beginthread entry thunk for the second
 * worker block: WorkerThread2_Start passes its address to __beginthread
 * with the control block as the argument, and the body only forwards that
 * argument to the wait loop (WorkerThread2EventLoop, 0x415810). Same shape
 * as WorkerThreadProcThunk (0x4156b0), the first block's thunk, which sits
 * 0x10 bytes before it. The 2 marks it as the twin's partner and says
 * nothing about the subsystem.
 */
#include "ghidra_types.h"


/* __beginthread thread proc; receives the control-block pointer __beginthread
 * was given (see FUN_00415530.c) as its normal __cdecl argument and forwards
 * it to the wait loop. */
void WorkerThread2ProcThunk(void *param_1)

{
  WorkerThread2EventLoop(param_1);
  return;
}

